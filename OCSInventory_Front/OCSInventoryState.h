//====================================================================================
// Open Computer and Software Inventory Next Generation
// Copyright (C) 2010 OCS Inventory Team. All rights reserved.
// Web: http://www.ocsinventory-ng.org

// This code is open source and may be copied and modified as long as the source
// code is always made freely available.
// Please refer to the General Public Licence V2 http://www.gnu.org/ or Licence.txt
//====================================================================================

// OCSInventoryState.h: interface for the COCSInventoryState class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_OCSINVENTORYSTATE_H__6E5FC8FF_1785_4745_A1A0_D2BEC9248343__INCLUDED_)
#define AFX_OCSINVENTORYSTATE_H__6E5FC8FF_1785_4745_A1A0_D2BEC9248343__INCLUDED_

#pragma once

#include "OCSInventory Front.h"
#include "Markup.h"

// State file
#define OCS_LAST_STATE_FILE			_T( "last_state")
// State sections
#define OCS_STATE_STANDARD_SECTION	_T( "LAST_STATE")
#define OCS_STATE_PLUGIN_SECTION	_T( "PLUGIN_STATE")

// To apply to checksum with an OR
#define OCS_CHECKSUM_HARDWARE		1
#define OCS_CHECKSUM_BIOS			2
#define OCS_CHECKSUM_MEMORIES		4
#define OCS_CHECKSUM_SLOTS			8
#define OCS_CHECKSUM_REGISTRY		16
#define OCS_CHECKSUM_CONTROLLERS	32
#define OCS_CHECKSUM_MONITORS		64
#define OCS_CHECKSUM_PORTS			128
#define OCS_CHECKSUM_STORAGES		256
#define OCS_CHECKSUM_DRIVES			512
#define OCS_CHECKSUM_INPUTS			1024
#define OCS_CHECKSUM_MODEMS			2048
#define OCS_CHECKSUM_NETWORKS		4096
#define OCS_CHECKSUM_PRINTERS		8192
#define OCS_CHECKSUM_SOUNDS			16384
#define OCS_CHECKSUM_VIDEOS			32768
#define OCS_CHECKSUM_SOFTWARES		65536
#define OCS_CHECKSUM_VIRTUALMACHINES 131072
#define OCS_CHECKSUM_CPUS			262144

class OCSINVENTORYFRONT_API COCSInventoryState  
{
public: // Methods
	//////////////////////////////////
	// Standard constructor/destructor
	//////////////////////////////////
	COCSInventoryState();
	virtual ~COCSInventoryState();

	//////////////////////////////////
	// Get attributes values
	//////////////////////////////////
	LPUTSTR GetHardware();
	LPUTSTR GetBios();
	LPUTSTR GetMemories();
	LPUTSTR GetSlots();
	LPUTSTR GetRegistry();
	LPUTSTR GetControllers();
	LPUTSTR GetMonitors();
	LPUTSTR GetPorts();
	LPUTSTR GetStorages();
	LPUTSTR GetDrives();
	LPUTSTR GetInputs();
	LPUTSTR GetModems();
	LPUTSTR GetNetworks();
	LPUTSTR GetPrinters();
	LPUTSTR GetSounds();
	LPUTSTR GetVideos();
	LPUTSTR GetSoftwares();
	LPUTSTR GetVirtualMachines();
	LPUTSTR GetCPUs();

	//////////////////////////////////
	// Set attributes values
	//////////////////////////////////

	// Clear info
	void Clear();

	void SetHardware( LPUTSTR lpstrValue);
	void SetBios( LPUTSTR lpstrValue);
	void SetMemories( LPUTSTR lpstrValue);
	void SetSlots( LPUTSTR lpstrValue);
	void SetRegistry( LPUTSTR lpstrValue);
	void SetControllers( LPUTSTR lpstrValue);
	void SetMonitors( LPUTSTR lpstrValue);
	void SetPorts( LPUTSTR lpstrValue);
	void SetStorages( LPUTSTR lpstrValue);
	void SetDrives( LPUTSTR lpstrValue);
	void SetInputs( LPUTSTR lpstrValue);
	void SetModems( LPUTSTR lpstrValue);
	void SetNetworks( LPUTSTR lpstrValue);
	void SetPrinters( LPUTSTR lpstrValue);
	void SetSounds( LPUTSTR lpstrValue);
	void SetVideos( LPUTSTR lpstrValue);
	void SetSoftwares( LPUTSTR lpstrValue);
	void SetVirtualMachines( LPUTSTR lpstrValue);
	void SetCPUs( LPUTSTR lpstrValue);

	//////////////////////////////////
	// File last_state functions
	//////////////////////////////////

	BOOL ReadFromFile(LPUTSTR lpstrFilename, LPUTSTR lpstrSection = OCS_STATE_STANDARD_SECTION);
	BOOL WriteToFile( LPUTSTR lpstrFilename, LPUTSTR lpstrSection = OCS_STATE_STANDARD_SECTION);

protected: // Methods
	// Format information in a XML string
	BOOL FormatXML( CMarkup* pXml, LPUTSTR lpstrSection = OCS_STATE_STANDARD_SECTION);
	// Read information in a XML string
	BOOL ParseFromXML( CMarkup* pXml, LPUTSTR lpstrSection = OCS_STATE_STANDARD_SECTION);

protected: // Attributes
	CString m_csHardware;
	CString m_csBios;
	CString m_csMemories;
	CString m_csSlots;
	CString m_csRegistry;
	CString m_csControllers;
	CString m_csMonitors;
	CString m_csPorts;
	CString m_csStorages;
	CString m_csDrives;
	CString m_csInputs;
	CString m_csModems;
	CString m_csNetworks;
	CString m_csPrinters;
	CString m_csSounds;
	CString m_csVideos;
	CString m_csSoftwares;
	CString m_csVirtualMachines;
	CString m_csCPUs;
};

#endif // !defined(AFX_OCSINVENTORYSTATE_H__6E5FC8FF_1785_4745_A1A0_D2BEC9248343__INCLUDED_)
