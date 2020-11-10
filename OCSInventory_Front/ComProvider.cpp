//====================================================================================
// Open Computer and Software Inventory Next Generation
// Copyright (C) 2010 OCS Inventory Team. All rights reserved.
// Web: http://www.ocsinventory-ng.org

// This code is open source and may be copied and modified as long as the source
// code is always made freely available.
// Please refer to the General Public Licence V2 http://www.gnu.org/ or Licence.txt
//====================================================================================

// ComProvider.cpp: implementation of the CComProvider class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "ComProvider.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CComProvider::CComProvider()
{
	m_hComProvider = NULL;
	m_pNewServerConfig = NULL;
	m_pDeleteServerConfig = NULL;
	m_pNewServerConnexion = NULL;
	m_pDeleteServerConnexion = NULL;
	m_csName = _T( "N/A");
	m_csVersion = _T( "N/A");
}

CComProvider::~CComProvider()
{
	unload();
}

BOOL CComProvider::load(LPUTSTR lpstrProvider)
{
	CLog *pLogger = getOcsLogger();

	try
	{
		CFileVersion fileVer;

		unload();

		pLogger->log( LOG_PRIORITY_DEBUG,  _T( "COM PROVIDER => Loading Communication Provider <%s>"), lpstrProvider);
		if ((m_hComProvider = LoadLibrary( lpstrProvider)) == NULL)
		{
			pLogger->log( LOG_PRIORITY_WARNING,  _T( "COM PROVIDER => Unable to load library <%s>, %s"), lpstrProvider, LookupError( GetLastError()));
			return FALSE;
		}
		if ((m_pNewServerConfig = (NEW_SERVER_CONFIG_OBJECT)GetProcAddress( m_hComProvider, "newServerConfig")) == NULL)
		{
			pLogger->log( LOG_PRIORITY_WARNING,  _T( "COM PROVIDER => No newServerConfig hook for Communication Provider <%s>, %s"), lpstrProvider, LookupError( GetLastError()));
			FreeLibrary( m_hComProvider);
			return FALSE;
		}
		if ((m_pDeleteServerConfig = (DELETE_SERVER_CONFIG_OBJECT)GetProcAddress( m_hComProvider, "deleteServerConfig")) == NULL)
		{
			pLogger->log( LOG_PRIORITY_WARNING,  _T( "COM PROVIDER => No deleteServerConfig hook for Communication Provider <%s>, %s"), lpstrProvider, LookupError( GetLastError()));
			FreeLibrary( m_hComProvider);
			return FALSE;
		}
		if ((m_pNewServerConnexion = (NEW_SERVER_OBJECT)GetProcAddress( m_hComProvider, "newServerConnexion")) == NULL)
		{
			pLogger->log( LOG_PRIORITY_WARNING,  _T( "COM PROVIDER => No newServerConnexion hook for Communication Provider <%s>, %s"), lpstrProvider, LookupError( GetLastError()));
			FreeLibrary( m_hComProvider);
			return FALSE;
		}
		if ((m_pDeleteServerConnexion = (DELETE_SERVER_OBJECT)GetProcAddress( m_hComProvider, "deleteServerConnexion")) == NULL)
		{
			pLogger->log( LOG_PRIORITY_WARNING,  _T( "COM PROVIDER => No deleteServerConnexion hook for Communication Provider <%s>, %s"), lpstrProvider, LookupError( GetLastError()));
			FreeLibrary( m_hComProvider);
			return FALSE;
		}
		// Open application file to get version from file
		if (fileVer.Open( lpstrProvider))
		{
			m_csName = fileVer.GetFileDescription();
			m_csVersion = fileVer.GetFixedFileVersion();
			fileVer.Close();
		}
		else
		{
			m_csName = _T( "N/A");
			m_csVersion = _T( "N/A");
		}
		return TRUE;
	}
	catch (CException *pEx)
	{
		pLogger->log( LOG_PRIORITY_WARNING,  _T( "COM PROVIDER => Error while loading provider DLL <%s>, %s"), lpstrProvider, LookupError( pEx));
		pEx->Delete();
		return FALSE;
	}
}

BOOL CComProvider::unload()
{
	if (m_hComProvider)
		FreeLibrary( m_hComProvider);
	m_csName = _T( "N/A");
	m_csVersion = _T( "N/A");
	return TRUE;
}

LPUTSTR CComProvider::getName()
{
	return m_csName;
}

LPUTSTR CComProvider::getVersion()
{
	return m_csVersion;
}

CServerConfig * CComProvider::newConfig( LPUTSTR lpstrFile, LPUTSTR lpstrSection)
{
	return (*m_pNewServerConfig)( lpstrFile, lpstrSection);
}

BOOL CComProvider::saveConfig( CServerConfig *pConfig, LPUTSTR lpstrFile, LPUTSTR lpstrSection)
{
	SAVE_SERVER_CONFIG_OBJECT pSaveServerConfig;

	ASSERT(pConfig);

	if ((pSaveServerConfig = (SAVE_SERVER_CONFIG_OBJECT)GetProcAddress( m_hComProvider, "saveServerConfig")) == NULL)
	{
		return FALSE;
	}
	return (*pSaveServerConfig) (pConfig, lpstrFile, lpstrSection);
}

void CComProvider::deleteConfig(CServerConfig *pConfig)
{
	if (pConfig)
		(*m_pDeleteServerConfig)( pConfig);
}

CConnexionAbstract * CComProvider::newConnexion( CServerConfig *pConfig)
{
	if (pConfig)
		return (*m_pNewServerConnexion) (pConfig);
	return NULL;
}

void CComProvider::deleteConnexion( CConnexionAbstract *pCon)
{
	if (pCon)
		(*m_pDeleteServerConnexion)( pCon);
}
