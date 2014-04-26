// UserDoc.h: interface for the CUserDoc class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_USERDOC_H__D2208BCA_EA02_463C_9FD7_D4825C223AE7__INCLUDED_)
#define AFX_USERDOC_H__D2208BCA_EA02_463C_9FD7_D4825C223AE7__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
#include"Userset.h"

class CUserDoc : public CDocument  
{
protected:
	DECLARE_DYNCREATE(CUserDoc)
public:
	CUserSet m_UserSet;
public:
	static CString DecodePassword(CString unreadable);
	static CString EncodePassword(CString readable);

	CUserDoc();
	virtual ~CUserDoc();
protected:
	DECLARE_MESSAGE_MAP()
};

#endif // !defined(AFX_USERDOC_H__D2208BCA_EA02_463C_9FD7_D4825C223AE7__INCLUDED_)
