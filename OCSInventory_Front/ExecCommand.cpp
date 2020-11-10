//====================================================================================
// Open Computer and Software Inventory Next Generation
// Copyright (C) 2010 OCS Inventory Team. All rights reserved.
// Web: http://www.ocsinventory-ng.org

// This code is open source and may be copied and modified as long as the source
// code is always made freely available.
// Please refer to the General Public Licence V2 http://www.gnu.org/ or Licence.txt
//====================================================================================

// ExecCommand.cpp: implementation for the CExecCommand class.
//////////////////////////////////////////////////////////////////////

#include "StdAfx.h"
#include "ExecCommand.h"
#include "OcsUtils.h"
#include <io.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <share.h>
#include <Tlhelp32.h>

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

#if ( _MSC_VER >= 1300 )
// Visual studio .NET or higher
#include <stddef.h>
#define TO_INTPTR(x) ((intptr_t)(x))
#else // Visual Studio 6
#define TO_INTPTR(x) ((long)(x))
#endif

// Utility class describing a process running in memory 
class CProcessProps : public CObject
{
public:
	CProcessProps();
	~CProcessProps();

	void set( DWORD64 dwProcessID, DWORD64 dwParentID, LPUTSTR lpstrImagePath);
	void setRunning( BOOL bRunning = TRUE);

	DWORD64 getProcessID();
	DWORD64 getParentID();
	LPUTSTR getImagePath();
	BOOL isRunning();

protected:
	DWORD64 m_dwProcessID;
	DWORD64 m_dwParentID;
	CString m_csImagePath;
	BOOL	m_bRunning;
};


CProcessProps::CProcessProps()
{
	m_dwProcessID = -1;
	m_dwParentID = -1;
	m_csImagePath.Empty();
	m_bRunning = FALSE;
}

CProcessProps::~CProcessProps()
{
}

void CProcessProps::set( DWORD64 dwProcessID, DWORD64 dwParentID, LPUTSTR lpstrImagePath)
{
	m_dwProcessID = dwProcessID;
	m_dwParentID = dwParentID;
	m_csImagePath = lpstrImagePath;
	m_bRunning = TRUE;
}

void CProcessProps::setRunning( BOOL bRunning)
{
	m_bRunning = bRunning;
}

DWORD64 CProcessProps::getProcessID()
{
	return m_dwProcessID;
}

DWORD64 CProcessProps::getParentID()
{
	return m_dwParentID;
}

LPUTSTR CProcessProps::getImagePath()
{
	return m_csImagePath;
}

BOOL CProcessProps::isRunning()
{
	return m_bRunning;
}

CExecCommand::CExecCommand()
{
    initialize();
	m_dwTimeout = INFINITE;
	m_bComspec = TRUE;
}

CExecCommand::~CExecCommand()
{
	closeHandles();
}

void CExecCommand::initialize()
{
	m_hProcessHandle = NULL;
	m_hChildStdinRd = NULL;
	m_hChildStdinWr = NULL;
	m_hChildStdoutRd = NULL;
	m_hChildStdoutWr = NULL;
	m_hChildStdinWrDup = NULL;
	m_hChildStdoutRdDup = NULL;
	m_fdFileStdOut = NULL;
	m_fdStdOut = NULL;
    m_nExitValue = -1;
	m_csOutputA.Empty();
}

void CExecCommand::setTimeout( DWORD64 dwTimeout)
{
	if (dwTimeout == 0)
		// Timeout MUS be greater than zero
		dwTimeout = INFINITE;
	m_dwTimeout = dwTimeout;
}

void CExecCommand::useComspec( BOOL bUse)
{
	m_bComspec = bUse;
}

void CExecCommand::setOutputFile( LPUTSTR lpstrFile)
{
	if (lpstrFile)
		m_csOutputFileA = CT2CA( lpstrFile);
	else
		m_csOutputFileA.Empty();
}

LPCSTR CExecCommand::getOutput()
{
	return m_csOutputA;
}

int CExecCommand::getExitValue()
{ 
	return m_nExitValue;
}

BOOL CExecCommand::closeHandles()
{
	BOOL bRet = TRUE;

	if (m_fdFileStdOut > 0)
	{
		_close( m_fdFileStdOut);
		m_fdFileStdOut = NULL;
	}
	if (m_fdStdOut > 0)
	{
		_close( m_fdStdOut);
		m_fdStdOut = NULL;
		// This will close this as well: this->hChildStdoutRdDup
//		m_hChildStdoutRdDup = NULL;
	}
	if (m_hChildStdinRd && !CloseHandle( m_hChildStdinRd))
	{
		bRet = FALSE;
	}
	m_hChildStdinRd = NULL;
	if (m_hChildStdinWr && !CloseHandle( m_hChildStdinWr))
	{
		bRet = FALSE;
	}
	m_hChildStdinWr = NULL;
	if (m_hChildStdoutRd && !CloseHandle( m_hChildStdoutRd))
	{
		bRet = FALSE;
	}
	m_hChildStdoutRd = NULL;
	if (m_hChildStdoutWr && !CloseHandle( m_hChildStdoutWr))
	{
		bRet = FALSE;
	}
	m_hChildStdoutWr = NULL;
	if (m_hProcessHandle && !CloseHandle( m_hProcessHandle))
	{
		bRet = FALSE;
	}
	m_hProcessHandle = NULL;
	return bRet;
}

DWORD64 CExecCommand::realCreateProcess(LPUTSTR lpstrCommand, LPUTSTR lpstrPath, BOOL bCapture)
{
	PROCESS_INFORMATION piProcInfo;
	STARTUPINFO		siStartInfo;
	CString			csComspec,
					csCommand;
	static DWORD64	dwProcessID = 0;
    PVOID			pOldWow64Value = NULL;

	ASSERT( lpstrCommand);

	if (m_bComspec)
	{
		// Find COMSPEC environnement variable to start process
		if (!csComspec.GetEnvironmentVariable( _T( "COMSPEC")))
		{
			/*
			* Oh gag, we're on Win9x or using COMMAND.COM. Not supported
			*/
			m_csOutputA.Format( "Get COMSPEC Error: %s", GetAnsiFromUnicode( LookupError( GetLastError())));
			return 0;
		}
		csCommand.Format( _T( "\"%s\" /c %s"), csComspec, lpstrCommand);
	}
	else
		// Do not use COMSPEC to start process => full path for command must be provided
		csCommand = lpstrCommand;

	ZeroMemory(&siStartInfo, sizeof(STARTUPINFO));
	siStartInfo.cb = sizeof(STARTUPINFO);
	if (bCapture)
	{
		// Capture stdin/stdout/stderr
		siStartInfo.dwFlags = STARTF_USESTDHANDLES | STARTF_USESHOWWINDOW;
		siStartInfo.hStdInput = m_hChildStdinRd;
		siStartInfo.hStdOutput = m_hChildStdoutWr;
		siStartInfo.hStdError = m_hChildStdoutWr;
	}
	else
		// No capture
		siStartInfo.dwFlags = STARTF_USESHOWWINDOW;
	siStartInfo.wShowWindow = SW_HIDE;

	if (!CreateProcess( NULL, csCommand.GetBuffer(), NULL, NULL, TRUE,
					0, //CREATE_NEW_CONSOLE,
					NULL, lpstrPath, &siStartInfo, &piProcInfo)) 
	{
		m_csOutputA.Format( "CreateProcess Error: %s", GetAnsiFromUnicode( LookupError( GetLastError())));
		return 0;
	}
	// Close the handles now so anyone waiting is woken.
	CloseHandle( piProcInfo.hThread);
	// Return process handle
	m_hProcessHandle = piProcInfo.hProcess;
	dwProcessID = piProcInfo.dwProcessId;
	return dwProcessID;
}

BOOL CExecCommand::startProcessCapture(LPUTSTR lpstrCommand, LPUTSTR lpstrPath)
{
	SECURITY_ATTRIBUTES saAttr;

	ASSERT( lpstrCommand);
	initialize();

	saAttr.nLength = sizeof(SECURITY_ATTRIBUTES);
	saAttr.bInheritHandle = TRUE;
	saAttr.lpSecurityDescriptor = NULL;

	////////////////////////////////////////////////////////////////
	// Capture stdin
	if (!CreatePipe(&m_hChildStdinRd, &m_hChildStdinWr, &saAttr, 0))
	{
		m_csOutputA.Format( "CreatePipe Error: %s", GetAnsiFromUnicode( LookupError( GetLastError())));
		return FALSE;
	}
	/* Create new output read handle and the input write handle. Set
	* the inheritance properties to FALSE. Otherwise, the child inherits
	* these handles; resulting in non-closeable handles to the pipes
	* being created. */
	if (!DuplicateHandle( GetCurrentProcess(), m_hChildStdinWr, GetCurrentProcess(), &m_hChildStdinWrDup, 0,
		 FALSE, DUPLICATE_SAME_ACCESS))
	{
		m_csOutputA.Format( "DuplicateHandle Error");
		return FALSE;
	}

	// Close the inheritable version of ChildStdin that we're using.
	CloseHandle( m_hChildStdinWr);
	m_hChildStdinWr = NULL;

	////////////////////////////////////////////////////////////////
	// Capture stdout and stderr
	if (!CreatePipe(&m_hChildStdoutRd, &m_hChildStdoutWr, &saAttr, 0))
	{
		m_csOutputA.Format( "CreatePipe Error: %s", GetAnsiFromUnicode( LookupError( GetLastError())));
		return FALSE;
	}
	if (!DuplicateHandle( GetCurrentProcess(), m_hChildStdoutRd, GetCurrentProcess(), &m_hChildStdoutRdDup, 0,
		 FALSE, DUPLICATE_SAME_ACCESS))
	{
		m_csOutputA.Format( "DuplicateHandle Error");
		return FALSE;
	}

	// Close the inheritable version of ChildStdout that we're using.
	CloseHandle( m_hChildStdoutRd);
	m_hChildStdoutRd = NULL;

	// Associates a C run-time file descriptor with an existing operating-system file handle
	// It's easier to use for the console
	if ((m_fdStdOut = _open_osfhandle(TO_INTPTR(m_hChildStdoutRdDup), _O_RDONLY|_O_TEXT)) == -1)
	{
		m_csOutputA.Format( "_open_osfhandle Error");
		return FALSE;
	}

	// Open file to store command output if needed 
	if (!m_csOutputFileA.IsEmpty())
	{
		if (_sopen_s( &m_fdFileStdOut, m_csOutputFileA, _O_CREAT|_O_TRUNC|_O_WRONLY|_O_BINARY, _SH_DENYNO, _S_IREAD | _S_IWRITE))
		{
			m_csOutputA.Format( "Can't open file <%s> for writing command output", m_csOutputFileA);
			return FALSE;
		}
	}
	return TRUE;
}

int CExecCommand::execWait( LPUTSTR lpstrCommand, LPUTSTR lpstrPath, BOOL bCapture)
{
	ASSERT( lpstrCommand);

	try
	{
		initialize();
		// Initialize environnement for capturing stdout and stderr if asked
		if (bCapture && !startProcessCapture( lpstrCommand, lpstrPath))
		{
			closeHandles();
			return EXEC_ERROR_START_COMMAND;
		}
		// Now start process
		if (realCreateProcess( lpstrCommand, lpstrPath, bCapture) == 0) 
		{
			closeHandles();
			return EXEC_ERROR_START_COMMAND;
		}
		// Wait for process ending, capturing stdout/stderr if needed
		if (!wait( bCapture))
		{
			closeHandles();
			if (m_nExitValue == STILL_ACTIVE)
				return EXEC_ERROR_TIMEOUT_COMMAND;
			return EXEC_ERROR_WAIT_COMMAND;
		}
		closeHandles();
		return EXEC_SUCCESSFULL;
	}
	catch( CException *pEx)
	{
		pEx->Delete();
		closeHandles();
		m_csOutputA = "Unhandled exception Error";
		return EXEC_ERROR_START_COMMAND;
	}
}

int CExecCommand::execNoWait( LPUTSTR lpstrCommand, LPUTSTR lpstrPath)
{
	try
	{
		ASSERT( lpstrCommand);
		
		// Start process
		initialize();
		if (realCreateProcess( lpstrCommand, lpstrPath) == 0) 
		{
			closeHandles();
			return EXEC_ERROR_START_COMMAND;
		}
		closeHandles();
		return EXEC_SUCCESSFULL;
	}
	catch (CException *pEx)
	{
		pEx->Delete();
		closeHandles();
		m_csOutputA = "Unhandled exception Error";
		return EXEC_ERROR_START_COMMAND;
	}
}

BOOL  CExecCommand::wait( BOOL bCapture)
{
	int		nResult = -1;
	DWORD64	dwExitCode,
			dwTime = 0;
	char	bBuffer[1024];
	int		nLength;
	struct _stat fsOut;
	BOOL	bWait = TRUE;

	m_csOutputA = "";

	// While timeout is not reached
	while (bWait)
	{
		// Each 200 millisecond, store stdout and stderr
		if (WaitForSingleObject( m_hProcessHandle, 200) == WAIT_FAILED)
		{
			m_csOutputA.Format( "WaitForSingleObject Error: %s", GetAnsiFromUnicode( LookupError( GetLastError())));
			m_nExitValue = -1;
			return FALSE; 
		}
		dwTime += 200;
		if ((m_dwTimeout != INFINITE) && (dwTime >= m_dwTimeout))
			// Timeout reached
			bWait = FALSE;
		if (bCapture && (_fstat( m_fdStdOut, &fsOut) == 0) && (fsOut.st_size > 0))
		{
			// We are capturing ouput and there is something to read
			nLength = _read( m_fdStdOut, bBuffer, 1023);
			bBuffer[nLength] = 0;
			if (m_fdFileStdOut == NULL)
				// In memory output store
				m_csOutputA.AppendFormat( "%s", bBuffer);
			else
			{
				// Store output to file
				if (_write( m_fdFileStdOut, bBuffer, nLength) != nLength)
				{
					m_csOutputA.AppendFormat( "Failed to write output to file <%s>", m_csOutputFileA);
				}
			}
		}
		// Check if process still active
		if (!GetExitCodeProcess( m_hProcessHandle, &dwExitCode) || (dwExitCode != STILL_ACTIVE))
		{
			// Process not active, exit loop
			bWait = FALSE;
			break;
		}
	}
	// Process ended => Capture last console output if needed
	while (bCapture && (_fstat( m_fdStdOut, &fsOut) == 0) && (fsOut.st_size > 0))
	{
		// We are capturing ouput and there is still something to read
		nLength = _read( m_fdStdOut, bBuffer, 1023);
		bBuffer[nLength] = 0;
		if (m_fdFileStdOut == NULL)
			// In memory output store
			m_csOutputA.AppendFormat( "%s", bBuffer);
		else
		{
			// Store output to file
			if (_write( m_fdFileStdOut, bBuffer, nLength) != nLength)
			{
				m_csOutputA.AppendFormat( "Failed to write output to file <%s>", m_csOutputFileA);
			}
		}
	}
	if (m_fdFileStdOut != NULL)
	{
		_close( m_fdFileStdOut);
		m_fdFileStdOut = NULL;
	}
	// Get process exit code
	if (GetExitCodeProcess( m_hProcessHandle, &dwExitCode)) 
	{
		nResult = dwExitCode;
		if (dwExitCode == STILL_ACTIVE)
			m_csOutputA.Format( "Command execution timeout of %lu milliseconds reached", m_dwTimeout);
	} 
	else 
	{
		m_csOutputA.Format( "GetExitCode Error: %s", GetAnsiFromUnicode( LookupError( GetLastError())));
		nResult = -1;
	}
	m_nExitValue = nResult;
	return (nResult >= 0);
}

int CExecCommand::execWaitForAllChilds( LPUTSTR lpstrCommand, LPUTSTR lpstrPath)
{
	CObArray		myProcessList;
	CProcessProps	*pProcess;
	DWORD64			dwExitCode,
					dwProcessID,
					dwTime = 0;

	try
	{
		ASSERT( lpstrCommand);

		// Start process
		initialize();
		if ((dwProcessID = realCreateProcess( lpstrCommand, lpstrPath)) == 0) 
		{
			closeHandles();
			return EXEC_ERROR_START_COMMAND;
		}
		// We need high priority on OS to follow thread/process created by main command
		SetPriorityClass( GetCurrentProcess(), HIGH_PRIORITY_CLASS);
		// Store first process
		pProcess = new CProcessProps();
		pProcess->set( dwProcessID, GetCurrentProcessId(), lpstrCommand);
		myProcessList.Add( pProcess);
		// While there is running processes or timeout not reached
		while ((myProcessList.GetCount() > 0) && (dwTime < m_dwTimeout))
		{
			// Parse memory processes for new childs process or terminated processes
			if (!parseRunningProcesses( &myProcessList))
			{
				SetPriorityClass( GetCurrentProcess(), NORMAL_PRIORITY_CLASS);
				m_csOutputA.Format( "Parse running processes Error: %s", GetAnsiFromUnicode( LookupError( GetLastError())));
				freeProcessList( &myProcessList);
				closeHandles();
				return EXEC_ERROR_WAIT_COMMAND;
			}
			Sleep( EXEC_WAIT_CHECK_LATENCY);
			dwTime += EXEC_WAIT_CHECK_LATENCY;
		}
		freeProcessList( &myProcessList);
		// Now return to normal prioity
		SetPriorityClass( GetCurrentProcess(), NORMAL_PRIORITY_CLASS);
		// check time out
		if (dwTime >= m_dwTimeout)
		{
			// Time out reached
			m_nExitValue = STILL_ACTIVE;
			m_csOutputA.Format( "Command execution timeout of %lu milliseconds reached", m_dwTimeout);
			closeHandles();
			return EXEC_ERROR_TIMEOUT_COMMAND;
		}
		// Get exit code
		if (GetExitCodeProcess( m_hProcessHandle, &dwExitCode)) 
		{
			m_nExitValue = dwExitCode;
		}
		else
		{
			m_nExitValue = -1;
			m_csOutputA.Format( "GetExitCode Error: %s", GetAnsiFromUnicode( LookupError( GetLastError())));
			closeHandles();
			return EXEC_ERROR_WAIT_COMMAND;
		}
		closeHandles();
		return EXEC_SUCCESSFULL;
	}
	catch (CException *pEx)
	{
		pEx->Delete();
		closeHandles();
		m_csOutputA = "Unhandled exception Error";
		return EXEC_ERROR_START_COMMAND;
	}
}

BOOL CExecCommand::parseRunningProcesses( CObArray *pProcessList)
{
    HANDLE			hSnapshot = NULL; 
    BOOL			bRet      = FALSE; 
    PROCESSENTRY32	pe32; 
	INT_PTR 		uIndex;
	CProcessProps	*pProc;

	try
	{
		// Take a snapshot of running processes
		if ((hSnapshot = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0)) == INVALID_HANDLE_VALUE) 
			return FALSE; 
		pe32.dwSize = sizeof(PROCESSENTRY32); 
		// By default, set all already listed processes as not running
		for (uIndex=0; uIndex<pProcessList->GetCount(); uIndex++)
		{
			pProc = (CProcessProps *) pProcessList->GetAt( uIndex);
			pProc->setRunning( FALSE);
		}
		// Check each process in memory
		for (bRet = Process32First(hSnapshot, &pe32); bRet; bRet = Process32Next(hSnapshot, &pe32))
		{
			// Check if process is already listed and set it is running
			if (!isProcessListed( pProcessList, pe32.th32ProcessID))
			{
				// This is not a listed process, is the parent listed
				if (isProcessListed( pProcessList, pe32.th32ParentProcessID))
				{
					// Parent process is listed, so register we have to wait for this process
					pProc = new CProcessProps;
					pProc->set( pe32.th32ProcessID, pe32.th32ParentProcessID, pe32.szExeFile);
					pProcessList->Add( pProc);
				}
			}
		}
		CloseHandle( hSnapshot);
		hSnapshot = NULL;
		// Now, remove from list all processes not running
		for (uIndex=0; uIndex<pProcessList->GetCount(); uIndex++)
		{
			pProc = (CProcessProps *) pProcessList->GetAt( uIndex);
			if (!pProc->isRunning())
			{
				pProcessList->RemoveAt( uIndex);
				delete pProc;
			}
		}
		return TRUE;
	}
	catch (CException *pEx)
	{
		if (hSnapshot != NULL)
			CloseHandle( hSnapshot);
		pEx->Delete();
		return FALSE;
	}
}

BOOL CExecCommand::isProcessListed( CObArray *pProcessList, DWORD64 dwProcessID)
{
	INT_PTR 		uIndex;
	CProcessProps	*pProc;

	for (uIndex=0; uIndex<pProcessList->GetCount(); uIndex++)
	{
		pProc = (CProcessProps *) pProcessList->GetAt( uIndex);
		if (pProc->getProcessID() == dwProcessID)
		{
			pProc->setRunning();
			return TRUE;
		}
	}
	return FALSE;
}

BOOL CExecCommand::freeProcessList( CObArray *pProcessList)
{
	INT_PTR 		uIndex;
	CProcessProps	*pProc;

	try
	{
		// By default, set all already listed processes as not running
		for (uIndex=0; uIndex<pProcessList->GetCount(); uIndex++)
		{
			pProc = (CProcessProps *) pProcessList->GetAt( uIndex);
			delete pProc;
		}
		pProcessList->RemoveAll();
		return TRUE;
	}
	catch (CException *pEx)
	{
		pEx->Delete();
		return FALSE;
	}
}
