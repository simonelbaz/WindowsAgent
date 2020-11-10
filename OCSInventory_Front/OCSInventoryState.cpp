//====================================================================================
// Open Computer and Software Inventory Next Generation
// Copyright (C) 2010 OCS Inventory Team. All rights reserved.
// Web: http://www.ocsinventory-ng.org

// This code is open source and may be copied and modified as long as the source
// code is always made freely available.
// Please refer to the General Public Licence V2 http://www.gnu.org/ or Licence.txt
//====================================================================================

// OCSInventoryState.cpp: implementation of the COCSInventoryState class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "OCSInventoryState.h"
#include "OcsUtils.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

COCSInventoryState::COCSInventoryState()
{
	Clear();
}

COCSInventoryState::~COCSInventoryState()
{
	Clear();
}

void COCSInventoryState::Clear()
{
	m_csHardware.Empty();
	m_csBios.Empty();
	m_csMemories.Empty();
	m_csSlots.Empty();
	m_csRegistry.Empty();
	m_csControllers.Empty();
	m_csMonitors.Empty();
	m_csPorts.Empty();
	m_csStorages.Empty();
	m_csDrives.Empty();
	m_csInputs.Empty();
	m_csModems.Empty();
	m_csNetworks.Empty();
	m_csPrinters.Empty();
	m_csSounds.Empty();
	m_csVideos.Empty();
	m_csSoftwares.Empty();
	m_csVirtualMachines.Empty();
	m_csCPUs.Empty();
}

LPUTSTR COCSInventoryState::GetHardware()
{
	return m_csHardware;
}

LPUTSTR COCSInventoryState::GetBios()
{
	return m_csBios;
}

LPUTSTR COCSInventoryState::GetMemories()
{
	return m_csMemories;
}

LPUTSTR COCSInventoryState::GetSlots()
{
	return m_csSlots;
}

LPUTSTR COCSInventoryState::GetRegistry()
{
	return m_csRegistry;
}

LPUTSTR COCSInventoryState::GetControllers()
{
	return m_csControllers;
}

LPUTSTR COCSInventoryState::GetMonitors()
{
	return m_csMonitors;
}

LPUTSTR COCSInventoryState::GetPorts()
{
	return m_csPorts;
}

LPUTSTR COCSInventoryState::GetStorages()
{
	return m_csStorages;
}

LPUTSTR COCSInventoryState::GetDrives()
{
	return m_csDrives;
}

LPUTSTR COCSInventoryState::GetInputs()
{
	return m_csInputs;
}

LPUTSTR COCSInventoryState::GetModems()
{
	return m_csModems;
}

LPUTSTR COCSInventoryState::GetNetworks()
{
	return m_csNetworks;
}

LPUTSTR COCSInventoryState::GetPrinters()
{
	return m_csPrinters;
}

LPUTSTR COCSInventoryState::GetSounds()
{
	return m_csSounds;
}

LPUTSTR COCSInventoryState::GetVideos()
{
	return m_csVideos;
}

LPUTSTR COCSInventoryState::GetSoftwares()
{
	return m_csSoftwares;
}

LPUTSTR COCSInventoryState::GetVirtualMachines()
{
	return m_csVirtualMachines;
}

LPUTSTR COCSInventoryState::GetCPUs()
{
	return m_csCPUs;
}

BOOL COCSInventoryState::ParseFromXML( CMarkup* pXml, LPUTSTR lpstrSection)
{
	try
	{
		TiXmlElement *pState, *pNode;

		pXml->ResetPos();
		pState = pXml->FindFirstElem( lpstrSection);

		pXml->ResetPos( pState);
		pNode = pXml->FindFirstElem( _T( "HARDWARE"));		
		m_csHardware = pXml->GetData( pNode);

		pXml->ResetPos( pState);
		pNode = pXml->FindFirstElem( _T( "BIOS"));
		m_csBios = pXml->GetData( pNode);

		pXml->ResetPos( pState);
		pNode = pXml->FindFirstElem( _T( "MEMORIES"));
		m_csMemories = pXml->GetData( pNode);

		pXml->ResetPos( pState);
		pNode = pXml->FindFirstElem( _T( "SLOTS"));
		m_csSlots = pXml->GetData( pNode);

		pXml->ResetPos( pState);
		pNode = pXml->FindFirstElem( _T( "REGISTRY"));
		m_csRegistry = pXml->GetData( pNode);

		pXml->ResetPos( pState);
		pNode = pXml->FindFirstElem( _T( "CONTROLLERS"));
		m_csControllers = pXml->GetData( pNode);

		pXml->ResetPos( pState);
		pNode = pXml->FindFirstElem( _T( "MONITORS"));
		m_csMonitors = pXml->GetData( pNode);

		pXml->ResetPos( pState);
		pNode = pXml->FindFirstElem( _T( "PORTS"));
		m_csPorts = pXml->GetData( pNode);

		pXml->ResetPos( pState);
		pNode = pXml->FindFirstElem( _T( "STORAGES"));
		m_csStorages = pXml->GetData( pNode);

		pXml->ResetPos( pState);
		pNode = pXml->FindFirstElem( _T( "DRIVES"));
		m_csDrives = pXml->GetData( pNode);

		pXml->ResetPos( pState);
		pNode = pXml->FindFirstElem( _T( "INPUTS"));
		m_csInputs = pXml->GetData( pNode);

		pXml->ResetPos( pState);
		pNode = pXml->FindFirstElem( _T( "MODEMS"));
		m_csModems = pXml->GetData( pNode);

		pXml->ResetPos( pState);
		pNode = pXml->FindFirstElem( _T( "NETWORKS"));
		m_csNetworks = pXml->GetData( pNode);

		pXml->ResetPos( pState);
		pNode = pXml->FindFirstElem( _T( "PRINTERS"));
		m_csPrinters = pXml->GetData( pNode);

		pXml->ResetPos( pState);
		pNode = pXml->FindFirstElem( _T( "SOUNDS"));
		m_csSounds = pXml->GetData( pNode);

		pXml->ResetPos( pState);
		pNode = pXml->FindFirstElem( _T( "VIDEOS"));
		m_csVideos = pXml->GetData( pNode);

		pXml->ResetPos( pState);
		pNode = pXml->FindFirstElem( _T( "SOFTWARES"));
		m_csSoftwares = pXml->GetData( pNode);

		pXml->ResetPos( pState);
		pNode = pXml->FindFirstElem( _T( "VIRTUALMACHINES"));
		m_csVirtualMachines = pXml->GetData( pNode);

		pXml->ResetPos( pState);
		pNode = pXml->FindFirstElem( _T( "CPUS"));
		m_csCPUs = pXml->GetData( pNode);

		return TRUE;
	}
	catch (CException *pEx)
	{
		pEx->Delete();
		return FALSE;
	}
}

BOOL COCSInventoryState::FormatXML(CMarkup* pXml, LPUTSTR lpstrSection)
{
	pXml->AddElem( lpstrSection);
		pXml->AddChildElem( _T( "HARDWARE"),m_csHardware);
		pXml->AddChildElem( _T( "BIOS"), m_csBios);
		pXml->AddChildElem( _T( "MEMORIES"),m_csMemories);
		pXml->AddChildElem( _T( "SLOTS"),m_csSlots);
		pXml->AddChildElem( _T( "REGISTRY"),m_csRegistry);
		pXml->AddChildElem( _T( "CONTROLLERS"),m_csControllers);
		pXml->AddChildElem( _T( "MONITORS"),m_csMonitors);
		pXml->AddChildElem( _T( "PORTS"),m_csPorts);
		pXml->AddChildElem( _T( "STORAGES"),m_csStorages);
		pXml->AddChildElem( _T( "DRIVES"),m_csDrives);
		pXml->AddChildElem( _T( "INPUTS"),m_csInputs);
		pXml->AddChildElem( _T( "MODEMS"),m_csModems);
		pXml->AddChildElem( _T( "NETWORKS"),m_csNetworks);
		pXml->AddChildElem( _T( "PRINTERS"),m_csPrinters);
		pXml->AddChildElem( _T( "SOUNDS"),m_csSounds);
		pXml->AddChildElem( _T( "VIDEOS"),m_csVideos);
		pXml->AddChildElem( _T( "SOFTWARES"),m_csSoftwares);
		pXml->AddChildElem( _T( "VIRTUALMACHINES"),m_csVirtualMachines);
		pXml->AddChildElem( _T( "CPUS"),m_csCPUs);
	pXml->OutOfElem();
	return TRUE;
}

void COCSInventoryState::SetHardware( LPUTSTR lpstrValue)
{
	m_csHardware = lpstrValue;
}

void COCSInventoryState::SetBios( LPUTSTR lpstrValue)
{
	m_csBios = lpstrValue;
}

void COCSInventoryState::SetMemories( LPUTSTR lpstrValue)
{
	m_csMemories = lpstrValue;
}

void COCSInventoryState::SetSlots( LPUTSTR lpstrValue)
{
	m_csSlots = lpstrValue;
}

void COCSInventoryState::SetRegistry( LPUTSTR lpstrValue)
{
	m_csRegistry = lpstrValue;
}

void COCSInventoryState::SetControllers( LPUTSTR lpstrValue)
{
	m_csControllers = lpstrValue;
}

void COCSInventoryState::SetMonitors( LPUTSTR lpstrValue)
{
	m_csMonitors = lpstrValue;
}

void COCSInventoryState::SetPorts( LPUTSTR lpstrValue)
{
	m_csPorts = lpstrValue;
}

void COCSInventoryState::SetStorages( LPUTSTR lpstrValue)
{
	m_csStorages = lpstrValue;
}

void COCSInventoryState::SetDrives( LPUTSTR lpstrValue)
{
	m_csDrives = lpstrValue;
}

void COCSInventoryState::SetInputs( LPUTSTR lpstrValue)
{
	m_csInputs = lpstrValue;
}

void COCSInventoryState::SetModems( LPUTSTR lpstrValue)
{
	m_csModems = lpstrValue;
}

void COCSInventoryState::SetNetworks( LPUTSTR lpstrValue)
{
	m_csNetworks = lpstrValue;
}

void COCSInventoryState::SetPrinters( LPUTSTR lpstrValue)
{
	m_csPrinters = lpstrValue;
}

void COCSInventoryState::SetSounds( LPUTSTR lpstrValue)
{
	m_csSounds = lpstrValue;
}

void COCSInventoryState::SetVideos( LPUTSTR lpstrValue)
{
	m_csVideos = lpstrValue;
}

void COCSInventoryState::SetSoftwares( LPUTSTR lpstrValue)
{
	m_csSoftwares = lpstrValue;
}

void COCSInventoryState::SetVirtualMachines( LPUTSTR lpstrValue)
{
	m_csVirtualMachines = lpstrValue;
}

void COCSInventoryState::SetCPUs( LPUTSTR lpstrValue)
{
	m_csCPUs = lpstrValue;
}

BOOL COCSInventoryState::ReadFromFile(LPUTSTR lpstrFilename, LPUTSTR lpstrSection)
{
	CMarkup	myXml;

	// Fill Device hardware properties from string
	if (!myXml.LoadFile( lpstrFilename))
		return FALSE;
	if (!ParseFromXML( &myXml, lpstrSection))
		return FALSE;
	return TRUE;
}

BOOL COCSInventoryState::WriteToFile(LPUTSTR lpstrFilename, LPUTSTR lpstrSection)
{
	CMarkup	myXml;
	TiXmlElement *pNode, *pTemp;

	// Load current state file
	if (myXml.LoadFile( lpstrFilename))
	{
		// File already exists, so remove existing section from XML 
		myXml.ResetPos();
		pNode = myXml.FindFirstElem( lpstrSection);
		while (pNode)
		{
			pTemp = pNode;
			pNode = myXml.FindNextElem( lpstrSection, pTemp);
			myXml.DeleteElem( pTemp);
		}
	}
	// Add new section
	myXml.ResetPos();
	if (!FormatXML( &myXml, lpstrSection))
		return FALSE;
	// Save state file
	if (!myXml.SaveFile( lpstrFilename))
		return FALSE;
	return TRUE;
}
