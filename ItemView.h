#if !defined(AFX_ITEMVIEW_H__F5CBC169_2B0A_40B9_91DD_5DE240A96540__INCLUDED_)
#define AFX_ITEMVIEW_H__F5CBC169_2B0A_40B9_91DD_5DE240A96540__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// BoxView.h : header file
//
#include"itemdoc.h"
#include"queryview.h"

/////////////////////////////////////////////////////////////////////////////
// CItemView form view

#ifndef __AFXEXT_H__
#include <afxext.h>
#endif

class CItemView : public CRecordView
{
protected:
	CItemView();           // protected constructor used by dynamic creation
	DECLARE_DYNCREATE(CItemView)

// Form Data
public:
	//{{AFX_DATA(CItemView)
	enum { IDD = IDD_ITEM_FORM };
	CItemSet* m_pSet;
	//}}AFX_DATA

// Attributes
public:
	CItemDoc* GetDocument();
// Operations
public:
	BOOL BuildSql(CQueryView * pQV);
	BOOL CheckRequired();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CItemView)
	public:
	virtual CRecordset* OnGetRecordset();
	virtual void OnInitialUpdate();
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	virtual ~CItemView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

	// Generated message map functions
	//{{AFX_MSG(CItemView)
	afx_msg void OnBtnItemquery();
	afx_msg void OnBtnItemadd();
	afx_msg void OnBtnItemmodify();
	afx_msg void OnBtnItemdel();
	afx_msg void OnBtnItemclear();
	afx_msg void OnBtnItemownerquery();
	afx_msg void OnKillfocusEdtItemdiscnt();
	afx_msg void OnKillfocusEdtItemprice();
	afx_msg void OnKillfocusEdtItemqty();
	afx_msg void OnBtnIteminfoquery();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

#ifndef _DEBUG  // debug version in HRSView.cpp
inline CItemDoc* CItemView::GetDocument()
   { return (CItemDoc*)m_pDocument; }
#endif
/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_BOXVIEW_H__F5CBC169_2B0A_40B9_91DD_5DE240A96540__INCLUDED_)
