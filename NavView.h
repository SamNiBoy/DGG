#if !defined(AFX_NAVVIEW_H__54C8C134_7B30_4271_842B_A231A69EC235__INCLUDED_)
#define AFX_NAVVIEW_H__54C8C134_7B30_4271_842B_A231A69EC235__INCLUDED_

#include "staticbox.h"
#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// NavView.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CNavView form view

#ifndef __AFXEXT_H__
#include <afxext.h>
#endif

class CNavView : public CFormView
{
public:
	CNavView();           // protected constructor used by dynamic creation
	DECLARE_DYNCREATE(CNavView)

// Form Data
public:
	//{{AFX_DATA(CNavView)
	enum { IDD = IDD_DLG_NAV };
	CStaticBox	m_cUser;
	CStaticBox	m_cSale;
	CStaticBox	m_cMoney;
	CStaticBox	m_cItem;
	CStaticBox	m_cBox;
	CStaticBox	m_cCustomer;
	//}}AFX_DATA

// Attributes
public:
	int m_iIconWidth;
	int m_iIconHeight;
	int m_iViewWidth;
	int m_iViewHeight;



// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CNavView)
	public:
	virtual BOOL Create(LPCTSTR lpszClassName, LPCTSTR lpszWindowName, DWORD dwStyle, const RECT& rect, CWnd* pParentWnd, UINT nID, CCreateContext* pContext = NULL);
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	virtual void OnInitialUpdate();
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
	virtual void OnDraw(CDC* pDC);
	//}}AFX_VIRTUAL

// Implementation
public:
	void CenterBoxs(int w, int h);
	virtual ~CNavView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

	// Generated message map functions
	//{{AFX_MSG(CNavView)
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);
	afx_msg void OnPaint();
	afx_msg void OnVScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar);
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_NAVVIEW_H__54C8C134_7B30_4271_842B_A231A69EC235__INCLUDED_)
