//====================================================================================
// Open Computer and Software Inventory Next Generation
// Copyright (C) 2010 OCS Inventory Team. All rights reserved.
// Web: http://www.ocsinventory-ng.org

// This code is open source and may be copied and modified as long as the source
// code is always made freely available.
// Please refer to the General Public Licence V2 http://www.gnu.org/ or Licence.txt
//====================================================================================

// Config.cpp: implementation of the CConfig class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "Config.h"
#include "Markup.h"
#include "OcsUtils.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CConfig::CConfig()
{
	Clear();
	// Load settings from config file
	load();
}

CConfig::~CConfig()
{
}

void CConfig::Clear()
{
	// Initialize default settings
	m_bForce = FALSE;
	m_uDebug = 0;
	m_csLocal.Empty();
	m_csXml.Empty();
	m_bNoTag = FALSE;
	m_bNoSoftware = FALSE;
	m_csTag.Empty();
	m_bHKCU = FALSE;
	m_bUID = FALSE;
	m_bNotify = FALSE;
	m_csIpDisc.Empty();
	m_csIpDiscLat.Empty();
	m_bFastIp = FALSE;
	m_csVersion.Empty();
}

LPUTSTR CConfig::getVersion()
{
	return m_csVersion;
}

void CConfig::setVersion(LPUTSTR lpstrVersion)
{
	m_csVersion = lpstrVersion;
}

UINT CConfig::isDebugRequired()
{
	return m_uDebug;
}

BOOL CConfig::isFastIpRequired()
{
	return m_bFastIp;
}

BOOL CConfig::isForceInventoryRequired()
{
	return m_bForce;
}

BOOL CConfig::isHkcuRequired()
{
	return m_bHKCU;
}

BOOL CConfig::isLocalRequired()
{
	return !m_csLocal.IsEmpty();
}

LPUTSTR CConfig::getLocalInventoryFolder()
{
	return m_csLocal;
}

BOOL CConfig::isNoTagRequired()
{
	return m_bNoTag;
}

LPUTSTR CConfig::getTagText()
{
	return m_csTag;
}

BOOL CConfig::isTagTextProvided()
{
	return !m_csTag.IsEmpty();
}

BOOL CConfig::isNewUidRequired()
{
	return m_bUID;
}

BOOL CConfig::isNotifyRequired()
{
	return m_bNotify;
}

BOOL CConfig::isNoSoftwareRequired()
{
	return m_bNoSoftware;
}

LPUTSTR CConfig::getConfigFile()
{
	return m_csConfigFile;
}

BOOL CConfig::isIpDiscoverRequired()
{
	return !m_csIpDisc.IsEmpty();
}

LPUTSTR CConfig::getIpDiscoverNetwork()
{
	return m_csIpDisc;
}

BOOL CConfig::isIpDiscoverLatencyProvided()
{
	return !m_csIpDiscLat.IsEmpty();
}

LPUTSTR CConfig::getIpDiscoverLatency()
{
	return m_csIpDiscLat;
}

BOOL CConfig::isXmlRequired()
{
	return !m_csXml.IsEmpty();
}

LPUTSTR CConfig::getXmlFolder()
{
	return m_csXml;
}

LPUTSTR CConfig::getCommunicationProvider()
{
	return m_csComProvider;
}

BOOL CConfig::load( LPUTSTR lpstrFile)
{
	CString csBuffer;

	// First, set config file to load
	setConfigFile( lpstrFile);
	// Debug
	m_uDebug = (UINT)GetPrivateProfileInt( OCS_AGENT_SECTION, _T( "Debug"), FALSE, m_csConfigFile);
	// Local inventory mode, get path to folder to store .ocs file
	GetPrivateProfileString( OCS_AGENT_SECTION, _T( "Local"), _T( ""), m_csLocal.GetBuffer( 1024), 1024, m_csConfigFile);
	m_csLocal.ReleaseBuffer();
	//  Scan for installed software or not
	m_bNoSoftware = (BOOL)GetPrivateProfileInt( OCS_AGENT_SECTION, _T( "NoSoftware"), FALSE, m_csConfigFile);
	//  Scanning HKEY_CURRENT_USER hive for printers and software
	m_bHKCU = (BOOL)GetPrivateProfileInt( OCS_AGENT_SECTION, _T( "HKCU"), FALSE, m_csConfigFile);
	//  Disable prompting user for TAG value
	m_bNoTag = (BOOL)GetPrivateProfileInt( OCS_AGENT_SECTION, _T( "NoTAG"), FALSE, m_csConfigFile);
	// Force IP Discover for the specified network
	GetPrivateProfileString( OCS_AGENT_SECTION, _T( "IpDisc"), _T( ""), m_csIpDisc.GetBuffer( 1024), 1024, m_csConfigFile);
	m_csIpDisc.ReleaseBuffer();
	// Communication provider to use
	GetPrivateProfileString( OCS_AGENT_SECTION, _T( "ComProvider"), OCS_DEFAULT_PROVIDER, csBuffer.GetBuffer( 1024), 1024, m_csConfigFile);
	csBuffer.ReleaseBuffer();
	setCommunicationProvider( csBuffer);
	return TRUE;
}

BOOL CConfig::save( LPUTSTR lpstrFile)
{
	CString csBuffer;
	BOOL	bResult;

	try
	{
		// First, set config file to load
		setConfigFile( lpstrFile);
		// Debug
		csBuffer.Format( _T( "%u"), m_uDebug);
		bResult = WritePrivateProfileString( OCS_AGENT_SECTION, _T( "Debug"), csBuffer, m_csConfigFile);
		// Local inventory mode, get path to folder to store .ocs file
		bResult = bResult && WritePrivateProfileString( OCS_AGENT_SECTION, _T( "Local"), m_csLocal, m_csConfigFile);
		//  Scan for installed software or not
		csBuffer.Format( _T( "%u"), m_bNoSoftware);
		bResult = bResult && WritePrivateProfileString( OCS_AGENT_SECTION, _T( "NoSoftware"), csBuffer, m_csConfigFile);
		//  Scanning HKEY_CURRENT_USER hive for printers and software
		csBuffer.Format( _T( "%u"), m_bHKCU);
		bResult = bResult && WritePrivateProfileString( OCS_AGENT_SECTION, _T( "HKCU"), csBuffer, m_csConfigFile);
		//  Disable prompting user for TAG value
		csBuffer.Format( _T( "%u"), m_bNoTag);
		bResult = bResult && WritePrivateProfileString( OCS_AGENT_SECTION, _T( "NoTAG"), csBuffer, m_csConfigFile);
		// Force IP Discover for the specified network
		bResult = bResult && WritePrivateProfileString( OCS_AGENT_SECTION, _T( "IpDisc"), m_csIpDisc, m_csConfigFile);
		// Communication provider to use
		CFile comFile( m_csComProvider, CFile::modeRead);
		bResult = bResult && WritePrivateProfileString( OCS_AGENT_SECTION, _T( "ComProvider"), comFile.GetFileName(), m_csConfigFile);
		return bResult;
	}
	catch (CException *pEx)
	{
		pEx->Delete();
		return FALSE;
	}
}

void CConfig::setConfigFile(LPUTSTR lpstrFile)
{
	if (lpstrFile == NULL)
		m_csConfigFile.Format( _T( "%s\\%s"), getDataFolder(), OCS_CONFIG_FILENAME);
	else
		m_csConfigFile = lpstrFile;
}

void CConfig::setLocalInventory(LPUTSTR lpstrFolder)
{
	if ((lpstrFolder == NULL) || (_tcslen( lpstrFolder) == 0))
		m_csLocal = getDataFolder();
	else
		m_csLocal = lpstrFolder;
}

void CConfig::setTagText(LPUTSTR lpstrText)
{
	m_csTag = lpstrText;
}

void CConfig::setDebugRequired( UINT uDebug)
{
	m_uDebug = uDebug;
}

void CConfig::setFastIpRequired(BOOL bFast)
{
	m_bFastIp = bFast;
}

void CConfig::setForceInventoryRequired(BOOL bForce)
{
	m_bForce = bForce;
}

void CConfig::setHkcuRequired(BOOL bHKCU)
{
	m_bHKCU = bHKCU;
}

void CConfig::setIpDiscoverRequired(LPUTSTR lpstrNetwork)
{
	m_csIpDisc = lpstrNetwork;
}

void CConfig::setIpDiscoverLatency(LPUTSTR lpstrLatency)
{
	m_csIpDiscLat = lpstrLatency;
}

void CConfig::setNewUID(BOOL bNew)
{
	m_bUID = bNew;
}

void CConfig::setNotify(BOOL bNotify)
{
	m_bNotify = bNotify;
}

void CConfig::setNoSoftwareRequired(BOOL bNoSoftware)
{
	m_bNoSoftware = bNoSoftware;
}

void CConfig::setNoTagRequired(BOOL bNoTag)
{
	m_bNoTag = bNoTag;
}

void CConfig::setXmlFolder(LPUTSTR lpstrFolder)
{
	if ((lpstrFolder == NULL) || (_tcslen( lpstrFolder) == 0))
		m_csXml = getDataFolder();
	else
		m_csXml = lpstrFolder;
}

void CConfig::setCommunicationProvider( LPUTSTR lpstrDll)
{
	if (lpstrDll == NULL)
		m_csComProvider.Format( _T( "%s\\%s"), getInstallFolder(), OCS_DEFAULT_PROVIDER);
	else
		m_csComProvider.Format( _T( "%s\\%s"), getInstallFolder(), lpstrDll);
}

BOOL CConfig::writeAccountInfos( LPUTSTR lpstrName, LPUTSTR lpstrValue)
{
	CString	csAccountFile,
			csName;
	CMarkup myXml;
	BOOL	bFound = FALSE;
	TiXmlElement *pXmlAccount,
				*pXmlElement;

	ASSERT( lpstrName);
	ASSERT( lpstrValue);

	csAccountFile.Format( _T( "%s\\%s"), getDataFolder(), OCS_ACCOUNTINFO_FILENAME);
	// Load file into XML object and try to find if account info not already set
	if (myXml.LoadFile( csAccountFile))
	{
		// Search ACCOUNTINFO node under root node
		pXmlAccount = myXml.FindFirstElem( _T( "ACCOUNTINFO"));
		while (pXmlAccount)
		{
			// Search if this this the good KEYNAME
			if ((pXmlElement = myXml.FindFirstElem( _T( "KEYNAME"), pXmlAccount)) == NULL)
				continue;
			csName = myXml.GetData( pXmlElement);
			if (csName.CompareNoCase( lpstrName) == 0)
			{
				// Found the same KEYNAME, so set the value of KEYVALUE node in this ACCOUNTINFO
				bFound = TRUE;
				if (pXmlElement = myXml.FindFirstElem( _T( "KEYVALUE"), pXmlAccount))
					// KEYVALUE node exists, update the value
					myXml.SetData( lpstrValue);
				else
				{
					// KEYVALUE node does not exists => add it 
					myXml.ResetPos( pXmlAccount);
					myXml.AddChildElem( _T( "KEYVALUE"), lpstrValue);
				}
			}
			// Search next ACCOUNTINFO node
			pXmlAccount = myXml.FindNextElem( _T( "ACCOUNTINFO"), pXmlAccount);
		}
	}
	if (!bFound)
	{
		// Error loading file or no ACCOUNTINFO for this KEYNAME => we have to add it
		myXml.ResetPos();
		myXml.AddElem( _T( "ACCOUNTINFO"));
		myXml.AddChildElem( _T( "KEYNAME"), lpstrName);
		myXml.AddChildElem( _T( "KEYVALUE"), lpstrValue);
		myXml.OutOfElem();				
	}
	// Save XML to file (need to remove system and hidden attributes if file exists)
	if (fileExists( csAccountFile))
		SetFileAttributes( csAccountFile, FILE_ATTRIBUTE_NORMAL);
	if (myXml.SaveFile( csAccountFile))
		// Saved, reset system and hidden attributes
		return SetFileAttributes( csAccountFile, FILE_ATTRIBUTE_HIDDEN|FILE_ATTRIBUTE_SYSTEM);
	// Error saving file
	return FALSE;

}
