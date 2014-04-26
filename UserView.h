#if !defined(AFX_USERVIEW_H__C9E71293_2605_4A94_84FC_793AC3243290__INCLUDED_)
#define AFX_USERVIEW_H__C9E71293_2605_4A94_84FC_793AC3243290__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// UserView.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CUserView record view

#include "UserSet.h"

class CUserView : public CRecordView
{
protected:
	CUserView();           // protected constructor used by dynamic creation
	DECLARE_DYNCREATE(CUserView)

// Form Data
public:
	//{{AFX_DATA(CUserView)
	enum { IDD = IDD_USER_FORM };
	CUserSet* m_pSet;
	//}}AFX_DATA

// Attributes
public:

// Operations
public:
	BOOL CheckRequired();
	CUserSet* GetRecordset();


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CUserView)
		// NOTE - the ClassWizard will add and remove member functions here.
	public:
	virtual CRecordset* OnGetRecordset();
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	virtual void OnInitialUpdate();
	//}}AFX_VIRTUAL

// Implementation
protected:
	virtual ~CUserView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

	// Generated message map functions
	//{{AFX_MSG(CUserView)
	afx_msg void OnBtnUserquery();
	afx_msg void OnBtnUserclear();
	afx_msg void OnBtnUseradd();
	afx_msg void OnBtnUsermodify();
	afx_msg void OnBtnUserdel();
	afx_msg void OnBtnQueryuser();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_USERVIEW_H__C9E71293_2605_4A94_84FC_793AC3243290__INCLUDED_)
