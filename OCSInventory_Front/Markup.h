//====================================================================================
// Open Computer and Software Inventory Next Generation
// Copyright (C) 2010 OCS Inventory Team. All rights reserved.
// Web: http://www.ocsinventory-ng.org

// This code is open source and may be copied and modified as long as the source
// code is always made freely available.
// Please refer to the General Public Licence V2 http://www.gnu.org/ or Licence.txt
//====================================================================================

// Markup.h: interface for the CMarkup class.
//

#if !defined(AFX_MARKUP_H__948A2705_9E68_11D2_A0BF_00105A27C570__INCLUDED_)
#define AFX_MARKUP_H__948A2705_9E68_11D2_A0BF_00105A27C570__INCLUDED_

#pragma once

#include "OCSInventoryFrontClasses.h"
#include "tinyxml.h"
#include "tinystr.h"

class OCSINVENTORYFRONT_API CMarkup  
{
	/* This class encapulate TinyXML lib to have an easy way manage OCS XML doc
	   We use 2 pointers to navigate through XML document:
	   - Current node, the main XML node of the document we are dealing with
	   - Child node, a child node of main node we are managing
	   */
public:
	CMarkup();
	virtual ~CMarkup();

	// Load XML document from file
	BOOL LoadFile( LPUTSTR lpstrFile);
	// Save XML document to file
	BOOL SaveFile( LPUTSTR lpstrFile);

	// Get XML document in UTF-8 text format
	LPCSTR GetDoc();
	// Get XML document in TinyXML object
	TiXmlDocument *GetTiXmlDocument();
	// Set XML document from text string (may be UTF-8 or not)
	BOOL SetDoc( LPCSTR szDoc);
	BOOL SetDoc( LPCWSTR szDoc);
	// Set XML document from TinyXML object
	BOOL SetTinyXmlDocument( TiXmlDocument *pDoc);
	// Add XML into current working node
	BOOL AddXml( CMarkup *pSource);

	// Add an XML node as child of current working XML node, and set it as new working node
	TiXmlElement *AddElem( LPUTSTR szName, LPUTSTR szValue=NULL);
	TiXmlElement *AddElem( LPUTSTR szName, LONG lValue);
	// Add an XML node as child of current working XML node, leave current working node as is
	TiXmlElement *AddChildElem( LPUTSTR szName, LPUTSTR szValue=NULL);
	TiXmlElement *AddChildElem( LPUTSTR szName, LONG lValue);
	// Set/Add value to the current working node
	BOOL SetData( LPUTSTR lpstrValue);
	BOOL SetData( LONG lValue);
	// Set/Add an attribute value to current working XML node
	BOOL SetAttrib( LPUTSTR szName, LPUTSTR szValue);
	BOOL SetAttrib( LPUTSTR szName, LONG lValue);
	BOOL AddAttrib( LPUTSTR szName, LPUTSTR szValue) {return SetAttrib( szName, szValue);};
	BOOL AddAttrib( LPUTSTR szName, LONG lValue) {return SetAttrib( szName, lValue);};
	// Set first child node as new working XML node
	TiXmlElement *IntoElem();
	// Set parent XML node as new working node
	TiXmlElement *OutOfElem();
	// Remove all childs named szName of provided node (current working XML node if null)
	BOOL RemoveChildElem( LPUTSTR szName, TiXmlElement *pXmlNode = NULL); 
	// Start search on child nodes of provided node (current working XML node if null), 
	// and set first node found as new working node
	TiXmlElement *FindFirstElem( LPUTSTR szName, TiXmlElement *pXmlNode = NULL);
	// Continue search from provided node (current working node if null)
	TiXmlElement *FindNextElem( LPUTSTR szName, TiXmlElement *pXmlNode = NULL);
	// Set position of current working XML node (if null, set it to document node)
	TiXmlElement *ResetPos( TiXmlElement *pXmlNode = NULL);
	// Get Text of XML Node (use current working XML node if null)
	LPUTSTR GetData( TiXmlElement *pXmlNode = NULL);
	// Get attribute value of current working XML node
	LPUTSTR GetAttrib( LPUTSTR szName);

	// Delete all allocated nodes under an XML node, and including this XML node
	void DeleteElem( TiXmlNode *pNode);

protected:
	TiXmlDocument *m_pDoc;			// XML document
	TiXmlElement  *m_pCurrentNode;	// XML node we are currently working with
};

#endif // !defined(AFX_MARKUP_H__948A2705_9E68_11D2_A0BF_00105A27C570__INCLUDED_)
