#if !defined(AFX_SaleVIEW_H__F5CBC169_2B0A_40B9_91DD_5DE240A96540__INCLUDED_)
#define AFX_SaleVIEW_H__F5CBC169_2B0A_40B9_91DD_5DE240A96540__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// SaleView.h : header file
//
#include"Saledoc.h"

/////////////////////////////////////////////////////////////////////////////
// CSaleView form view

#ifndef __AFXEXT_H__
#include <afxext.h>
#endif

class CSaleView : public CRecordView
{
protected:
	CSaleView();           // protected constructor used by dynamic creation
	DECLARE_DYNCREATE(CSaleView)

// Form Data
public:
	//{{AFX_DATA(CSaleView)
	enum { IDD = IDD_SALE_FORM };
	CSaleSet* m_pSet;
	CTime	m_dteSaleFrom;
	CTime	m_dteSaleTo;
	//}}AFX_DATA

// Attributes
public:
	CSaleDoc* GetDocument();
// Operations
public:
	BOOL CallBackItem(CString itemid, CString boxid, CString qty, BOOL bPutToBox);
	BOOL SaleOutItem(CString itemid, CString boxid, CString qty);
	void ListSaleRecords(CString filter);
	BOOL CheckRequired();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CSaleView)
	public:
	virtual CRecordset* OnGetRecordset();
	virtual void OnInitialUpdate();
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	virtual ~CSaleView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

	// Generated message map functions
	//{{AFX_MSG(CSaleView)
	afx_msg void OnBtnSalequery();
	afx_msg void OnBtnSaleadd();
	afx_msg void OnBtnSalemodify();
	afx_msg void OnBtnSaledel();
	afx_msg void OnBtnSaleclear();
	afx_msg void OnChangeEdtSaleqty();
	afx_msg void OnKillfocusEdtBarcode();
	afx_msg void OnKillfocusEdtSaleitemid();
	afx_msg void OnBtnSaleitemquery();
	afx_msg void OnItemclickLstSalerecord(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnClickLstSalerecord(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnBtnSaleidquery();
	afx_msg void OnBtnSaleinfoquery();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

#ifndef _DEBUG  // debug version in HRSView.cpp
inline CSaleDoc* CSaleView::GetDocument()
   { return (CSaleDoc*)m_pDocument; }
#endif
/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_SaleVIEW_H__F5CBC169_2B0A_40B9_91DD_5DE240A96540__INCLUDED_)
