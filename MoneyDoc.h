// UserDoc.h: interface for the CMoneyDoc class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_MONEYDOC_H__D2208BCA_EA02_463C_9FD7_D4825C223AE7__INCLUDED_)
#define AFX_MONEYbDOC_H__D2208BCA_EA02_463C_9FD7_D4825C223AE7__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
#include"moneyset.h"

class CMoneyDoc : public CDocument  
{
protected:
	DECLARE_DYNCREATE(CMoneyDoc)
public:
	CMoneySet m_MoneySet;
public:
	static CString DecodePassword(CString unreadable);
	static CString EncodePassword(CString readable);

	CMoneyDoc();
	virtual ~CMoneyDoc();
protected:
	DECLARE_MESSAGE_MAP()
};

#endif // !defined(AFX_USERDOC_H__D2208BCA_EA02_463C_9FD7_D4825C223AE7__INCLUDED_)
