//====================================================================================
// Open Computer and Software Inventory Next Generation
// Copyright (C) 2010 OCS Inventory Team. All rights reserved.
// Web: http://www.ocsinventory-ng.org

// This code is open source and may be copied and modified as long as the source
// code is always made freely available.
// Please refer to the General Public Licence V2 http://www.gnu.org/ or Licence.txt
//====================================================================================

// OcsUtils.h : main header file for the OcsUtils
//
#ifndef _OCS_UTILS_H_INCLUDED_
#define  _OCS_UTILS_H_INCLUDED_

#pragma once

#if defined (_MSC_VER)
#include "stdafx.h"
#endif
#include "OCSInventoryFrontClasses.h"

// Transform UNICODE string to ANSI string
CStringA OCSINVENTORYFRONT_API GetAnsiFromUnicode(LPUTSTR a_wstrString);

// Transform ANSI string to UNICODE string
CStringW OCSINVENTORYFRONT_API GetUnicodeFromAnsi(LPCSTR a_strString);

// Transform Unicode source text string to UTF8
CStringA OCSINVENTORYFRONT_API GetUTF8FromUnicode( LPUTSTR a_wstrString);

// Transform UTF-8 source text string to Unicode
CStringW OCSINVENTORYFRONT_API GetUnicodeFromUTF8( LPCSTR a_strString);

// Ensure if a string if UTF8 encoded
BOOL OCSINVENTORYFRONT_API isValidUTF8( LPCSTR a_strString);

// Create directory (and every missing parent directories if needed)
BOOL OCSINVENTORYFRONT_API directoryCreate( LPUTSTR lpstrDir);

// Delete directory (and every file or sub directory)
BOOL OCSINVENTORYFRONT_API directoryDelete( LPUTSTR lpstrDir);

// Check if file or directory exists
BOOL OCSINVENTORYFRONT_API fileExists( LPUTSTR lpstrFile);

// Get Partition Free Space in bytes
__int64 OCSINVENTORYFRONT_API GetDiskFree( LPUTSTR lpstrDrive);

// Load file content into CByteArray
CByteArray OCSINVENTORYFRONT_API * LoadFileToByteArray( LPUTSTR lpstrFilename);

// Write CByteArray content into file
BOOL OCSINVENTORYFRONT_API WriteByteArrayToFile( CByteArray* pByte, LPUTSTR lpstrFilename);

// Load file into a text buffer (using file specified encoding)
BOOL OCSINVENTORYFRONT_API LoadFileToText( CString &csBuffer, LPUTSTR lpstrFilename);

// Write text buffer into file using default OS charset
BOOL OCSINVENTORYFRONT_API WriteTextToFile( LPUTSTR lpstrText, LPUTSTR lpstrFilename);

// Write text buffer into UTF-8 encoded file
BOOL OCSINVENTORYFRONT_API WriteTextToUTF8File( LPUTSTR lpstrText, LPUTSTR lpstrFilename);

// Write content into file
BOOL OCSINVENTORYFRONT_API WriteVoidToFile( LPCVOID lpVoid, UINT uLength, LPUTSTR lpstrFilename);

// Compute digest on a file, using algorithm lpstralgo, and return result encode in base64 or hexa
BOOL OCSINVENTORYFRONT_API fileDigest( LPUTSTR lpstrFile, CString &csDigest, LPUTSTR lpstrAlgo = _T( "sha1"), BOOL bBase64 = TRUE);

// Check wether a string is hex encoded or not
BOOL OCSINVENTORYFRONT_API is_hex( LPUTSTR lpstrString);

// Encode pBuffer (uLength bytes long) into hexadecimal, and put result into CString
BOOL OCSINVENTORYFRONT_API hex_encode( LPBYTE pBuffer, UINT uLength, CString &csHex);

// Decode CString hexadecimal encoded, and put result into a BYTE array of uLength elements
// You MUST free this pointer when no more needed
LPBYTE OCSINVENTORYFRONT_API hex_decode( CString &csHex, UINT *uLength);

// Check wether a string is base64 encoded or not
BOOL OCSINVENTORYFRONT_API is_base64( CString myString);

// Encode pBuffer (uLength bytes long) into base64, and put result into CString
BOOL OCSINVENTORYFRONT_API base64_encode( LPBYTE pBuffer, UINT uLength, CString &csBase64);

// Decode null terminated string, and put result into a BYTE array of uLength elements
// You MUST free this pointer when no more needed
LPBYTE OCSINVENTORYFRONT_API base64_decode( LPUTSTR lpstrBase64, UINT *uLength);

// Check wether a string is printable or not
BOOL OCSINVENTORYFRONT_API is_printable( CString myString);

#endif // _OCS_UTILS_H_INCLUDED_
