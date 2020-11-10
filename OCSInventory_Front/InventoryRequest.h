//====================================================================================
// Open Computer and Software Inventory Next Generation
// Copyright (C) 2010 OCS Inventory Team. All rights reserved.
// Web: http://www.ocsinventory-ng.org

// This code is open source and may be copied and modified as long as the source
// code is always made freely available.
// Please refer to the General Public Licence V2 http://www.gnu.org/ or Licence.txt
//====================================================================================

// InventoryRequest.h: interface for the CInventoryRequest class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_INVENTORYREQUEST_H__84CE64C5_1C6B_4E05_8981_FA8D80E4D3A1__INCLUDED_)
#define AFX_INVENTORYREQUEST_H__84CE64C5_1C6B_4E05_8981_FA8D80E4D3A1__INCLUDED_

#pragma once

#include "OCSInventory Front Classes.h"
#include "Markup.h"
#include "RequestAbstract.h"
#include "OCSInventoryState.h"
#include "Sysinfo.h"
#include "XMLInteract.h"


class OCSINVENTORYFRONT_API CInventoryRequest : public CRequestAbstract  
{
public: //Methods

	//Standards constructor and destructor
	// Optionally, enable notify mode to send only important information changes, such as IP information
	CInventoryRequest( BOOL bNotify = FALSE);
	virtual ~CInventoryRequest();

	// Enable agent to specify a tag
	void setTag(CString);
	// Do some action when request successfully executed
	void setSuccess();

public: //Attributes

	// Inventory storing object interaction
	CXMLInteract		*m_pTheDB;			
	// General device properties
	CDeviceProperties m_Device;
	// BIOS information
	CBios		 m_BIOS;
	// List of CPU info
	CCpuList m_CpuList;
	// List of Input devices info
	CInputDeviceList m_InputList;
	// List of Logical Drives (Volume name, File system, Total size, Free space...)
	CLogicalDriveList m_DriveList;
	// List of Memory slots
	CMemorySlotList m_MemoryList;
	// List of Modems
	CModemList m_ModemList;
	// List of Monitors
	CMonitorList m_MonitorList;
	// List of Network adapters
	CNetworkAdapterList m_NetworkList;
	// List of Printers
	CPrinterList m_PrinterList;
	// List of Device registry values info
	CRegistryValueList m_RegistryList;
	// List of Software
	CSoftwareList m_SoftwareList;
	// List of Sound Devices
	CSoundDeviceList m_SoundList;
	// List of Storage devices (Floppy disk, IDE Disk, SCSI Disk, CD-Rom...)
	CStoragePeripheralList m_StorageList;
	// List of System Controllers (Floppy, IDE, SCSI, USB, IEEE1394, PCMCIA, SATA)
	CSystemControllerList m_SystemControllerList;
	// List of System Slots (PCI, AGP...)
	CSystemSlotList m_SlotList;
	// List of ports
	CSystemPortList m_PortList;
	// List of Video adapters
	CVideoAdapterList m_VideoList;

private: // Attributes
	// The pointer to the sysinfo object
	CSysInfo	*m_pSysInfo;
	// Inventory state for detecting changes
	COCSInventoryState	*m_pState;			
	COCSInventoryState	*m_pPluginState;
	// Device TAG
	CString m_csTag;
	// Is /NOTIFY enabled, to force notifying mode because service detects inventory changes
	BOOL	m_bNotify;

private: // Methods
	// Initialize inventory object
	BOOL initInventory();
	// Inventory the computer using SysInfo.dll
	BOOL runInventory();
	// Build the inventory CHECKSUM
	// Return TRUE is inventory state changed
	BOOL isStateChanged();
	// Insert download history into inventory
	BOOL loadDownloadHistory();
	// Search recursively in directory lpstrDir for files with extension in comma separated list lpstrExtension
	// Excluding folders in comma separated list lpstrFolderToSkip
	// Returns the number of files in folder and subfolders
	LONG SearchFilesInDirectory( LPUTSTR lpstrDir, LPUTSTR lpstrExtension = NULL, LPUTSTR lpstrFolderToSkip = NULL);
	// Is file name has extension from a coma separated list in csExtension
	BOOL IsExtensionToSearch( LPUTSTR lpstrFilename, LPUTSTR lpstrExtension);
	// Is folder name is in a coma separated list in csFolderToSkip
	BOOL IsExcludeFolder( LPUTSTR lpstrFolder, LPUTSTR lpstrFolderToSkip);
	// Finalize inventory
	BOOL final();
	// Update the last_state file
	BOOL writeLastInventoryState();
};

#endif // !defined(AFX_INVENTORYREQUEST_H__84CE64C5_1C6B_4E05_8981_FA8D80E4D3A1__INCLUDED_)
