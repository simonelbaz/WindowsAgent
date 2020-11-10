//====================================================================================
// Open Computer and Software Inventory Next Generation
// Copyright (C) 2010 OCS Inventory Team. All rights reserved.
// Web: http://www.ocsinventory-ng.org

// This code is open source and may be copied and modified as long as the source
// code is always made freely available.
// Please refer to the General Public Licence V2 http://www.gnu.org/ or Licence.txt
//====================================================================================

// Response.cpp: implementation of the CResponse class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "Response.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CResponse::CResponse(CByteArray* rawConnexionResult) : CResponseAbstract(rawConnexionResult)
{

}

CResponse::~CResponse()
{

}
