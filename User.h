// User.h: interface for the CUser class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_USER_H__F3090B55_E429_4A41_A6BF_9561F6670C7D__INCLUDED_)
#define AFX_USER_H__F3090B55_E429_4A41_A6BF_9561F6670C7D__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

class CUser  
{
public:
	CString m_sUserName;
	bool m_bAdmin_flg;
public:
	CUser();
	virtual ~CUser();

};

#endif // !defined(AFX_USER_H__F3090B55_E429_4A41_A6BF_9561F6670C7D__INCLUDED_)
