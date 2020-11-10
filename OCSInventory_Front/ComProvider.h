//====================================================================================
// Open Computer and Software Inventory Next Generation
// Copyright (C) 2010 OCS Inventory Team. All rights reserved.
// Web: http://www.ocsinventory-ng.org

// This code is open source and may be copied and modified as long as the source
// code is always made freely available.
// Please refer to the General Public Licence V2 http://www.gnu.org/ or Licence.txt
//====================================================================================

// ComProvider.h: interface for the CComProvider class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_COMPROVIDER_H__70CCD6F0_1E98_4836_BDF1_E69D133E21A8__INCLUDED_)
#define AFX_COMPROVIDER_H__70CCD6F0_1E98_4836_BDF1_E69D133E21A8__INCLUDED_


#pragma once

#include "OCSInventoryFrontClasses.h"
#include "Log.h"
#include "ConnexionAbstract.h"
#include "ServerConfig.h"
#include "Provider Classes.h"

#ifdef __cplusplus
extern "C" {
#endif

typedef OCS_PROVIDER_API CServerConfig * (*NEW_SERVER_CONFIG_OBJECT)( LPUTSTR, LPUTSTR);
typedef OCS_PROVIDER_API BOOL (*SAVE_SERVER_CONFIG_OBJECT)( CServerConfig *, LPUTSTR, LPUTSTR);
typedef OCS_PROVIDER_API void (*DELETE_SERVER_CONFIG_OBJECT)(CServerConfig *);

typedef OCS_PROVIDER_API CConnexionAbstract * (*NEW_SERVER_OBJECT)(CServerConfig *);
typedef OCS_PROVIDER_API void (*DELETE_SERVER_OBJECT)(CConnexionAbstract *);

#ifdef __cplusplus
};
#endif

class OCSINVENTORYFRONT_API CComProvider 
{
public:
	CComProvider();
	virtual ~CComProvider();

	// Dynamically load communication provider 
	BOOL load( LPUTSTR lpstrProvider);
	BOOL unload();

	// Get provider name and version 
	LPUTSTR getName();
	LPUTSTR getVersion();

	// Create, save and delete server configuration
	CServerConfig * newConfig( LPUTSTR lpstrFile = NULL, LPUTSTR lpstrSection = OCS_HTTP_PROVIDER_SECTION);
	BOOL saveConfig( CServerConfig *pConfig, LPUTSTR lpstrFile = NULL, LPUTSTR lpstrSection = OCS_HTTP_PROVIDER_SECTION);
	void deleteConfig( CServerConfig *pConfig);

	// Create and delete connexion to server, using server configuration
	CConnexionAbstract * newConnexion( CServerConfig *pConfig);
	void deleteConnexion( CConnexionAbstract *pCon);

protected:
	// Communication provider instance DLL
	HINSTANCE m_hComProvider;
	NEW_SERVER_CONFIG_OBJECT m_pNewServerConfig;
	DELETE_SERVER_CONFIG_OBJECT m_pDeleteServerConfig;
	NEW_SERVER_OBJECT m_pNewServerConnexion;
	DELETE_SERVER_OBJECT m_pDeleteServerConnexion;
	CString m_csVersion;
	CString m_csName;
};

#endif // !defined(AFX_COMPROVIDER_H__70CCD6F0_1E98_4836_BDF1_E69D133E21A8__INCLUDED_)
