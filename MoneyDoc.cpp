// UserDoc.cpp: implementation of the CMoneyDoc class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "hrs.h"
#include "MoneyDoc.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////
IMPLEMENT_DYNCREATE(CMoneyDoc, CDocument)

BEGIN_MESSAGE_MAP(CMoneyDoc, CDocument)
	//{{AFX_MSG_MAP(CCUSTOMERDoc)
		// NOTE - the ClassWizard will add and remove mapping macros here.
		//    DO NOT EDIT what you see in these blocks of generated code!
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

CMoneyDoc::CMoneyDoc()
{

}

CMoneyDoc::~CMoneyDoc()
{

}

CString CMoneyDoc::EncodePassword(CString readable)
{
	TCHAR c;
	for(int i=0; i< readable.GetLength();i++)
	{
		c = readable.GetAt(i);
		c = (c+i)%256;
		readable.SetAt(i,c);
	}
	return readable;

}

CString CMoneyDoc::DecodePassword(CString unreadable)
{
	TCHAR c;
	for(int i=0; i< unreadable.GetLength();i++)
	{
		c = unreadable.GetAt(i);
		c = (c-i+256)%256;
		unreadable.SetAt(i,c);
	}
	return unreadable;
}
