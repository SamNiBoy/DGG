// HRS.h : main header file for the HRS application
//

#if !defined(AFX_HRS_H__0E9FD131_53B1_4E8B_87AC_205C7DE5907B__INCLUDED_)
#define AFX_HRS_H__0E9FD131_53B1_4E8B_87AC_205C7DE5907B__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"       // main symbols
#include "dbmanger.h"
#include "queryview.h"
/////////////////////////////////////////////////////////////////////////////
// CHRSApp:
// See HRS.cpp for the implementation of this class
//


class CHRSApp : public CWinApp
{
public:
	CHRSApp();
    HCURSOR m_BTHand;
	friend class CQueryView;
// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CHRSApp)
	public:
	virtual BOOL InitInstance();
	virtual int ExitInstance();
	//}}AFX_VIRTUAL

// Implementation
	//{{AFX_MSG(CHRSApp)
	afx_msg void OnAppAbout();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_HRS_H__0E9FD131_53B1_4E8B_87AC_205C7DE5907B__INCLUDED_)
