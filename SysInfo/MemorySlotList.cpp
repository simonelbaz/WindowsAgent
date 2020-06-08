//====================================================================================
// Open Computer and Software Inventory Next Generation
// Copyright (C) 2010 OCS Inventory Team. All rights reserved.
// Web: http://www.ocsinventory-ng.org

// This code is open source and may be copied and modified as long as the source
// code is always made freely available.
// Please refer to the General Public Licence V2 http://www.gnu.org/ or Licence.txt
//====================================================================================

// MemorySlotList.cpp: implementation of the CMemorySlotList class.
//
//////////////////////////////////////////////////////////////////////
#include "stdafx.h"
#include "MemorySlot.h"
#include "MemorySlotList.h"
#include "OcsCrypto.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////
CMemorySlotList::CMemorySlotList()
{
}

CMemorySlotList::~CMemorySlotList()
{
}

LPCTSTR CMemorySlotList::GetHash()
{
	COcsCrypto	myHash;
	CMemorySlot myObject;
	POSITION	pos;
	BOOL		bContinue;
	static CString		csToHash;

	if (GetCount() == 0)
		return NULL;
	if (!myHash.HashInit())
		return NULL;
	pos = GetHeadPosition();
	bContinue = (pos != NULL);
	if (bContinue)
		// There is one record => get the first
		myObject = GetNext( pos);
	while (bContinue)
	{
		csToHash.Format( _T( "%s%s%s%s%s%s%u%s"), myObject.GetCaption(), myObject.GetDescription(),
						 myObject.GetCapacity(), myObject.GetUsage(), myObject.GetType(),
						 myObject.GetSpeed(), myObject.GetSlotNumber(), myObject.GetSN());
		myHash.HashUpdate( csToHash);
		bContinue = (pos != NULL);
		if (bContinue)
			myObject = GetNext( pos);
	}
	return myHash.HashFinal();
}

ULONG CMemorySlotList::GetTotalMemory()
{
	CMemorySlot myObject;
	POSITION	pos;
	ULONG		ulTotal = 0;

	pos = GetHeadPosition();
	while (pos)
	{
		myObject = GetNext( pos);
		if (myObject.GetCapacity())
			ulTotal += _ttol( myObject.GetCapacity());
	}
	return ulTotal;
}
