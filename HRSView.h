// HRSView.h : interface of the CCUSTOMERView class
//
/////////////////////////////////////////////////////////////////////////////
//{{AFX_INCLUDES()

//}}AFX_INCLUDES
#include"queryview.h"
#include"hrsset.h"
#include"hrsdoc.h"
#if !defined(AFX_HRSVIEW_H__CF3C79A5_1D12_4B7B_863F_AE84A946616E__INCLUDED_)
#define AFX_HRSVIEW_H__CF3C79A5_1D12_4B7B_863F_AE84A946616E__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

class CHRSSet;

class CCUSTOMERView : public CRecordView
{
protected: // create from serialization only
	CCUSTOMERView();
	DECLARE_DYNCREATE(CCUSTOMERView)

public:
	//{{AFX_DATA(CCUSTOMERView)
	enum { IDD = IDD_CUSTOMER_FORM };
	CButton	m_cIncludeItem;
	CButton	m_cIncludeCustomer;
	CButton	m_cIncludeBox;
	CButton	m_cCurCustomer;
	CCUSTOMERSet* m_pSet;
	CString	m_sSearch_by_Name;
	//}}AFX_DATA
	/*CString	m_sCustomerName;
	
	CString	m_sCustomerAddress;
	CString	m_sCustomerDescription;
	CString	m_sCustomerEmail;
	int		m_iCustomerLevel;
	CString	m_sCustomerTelphone;
	CString	m_sCustomerSex;
	int		m_iCustomerAge;*/
// Attributes
public:
	CCUSTOMERDoc* GetDocument();

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CCUSTOMERView)
	public:
	virtual CRecordset* OnGetRecordset();
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
	virtual BOOL IsSelected(const CObject* pDocItem) const;
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	virtual void OnInitialUpdate(); // called first time after construct
	virtual BOOL OnPreparePrinting(CPrintInfo* pInfo);
	virtual void OnBeginPrinting(CDC* pDC, CPrintInfo* pInfo);
	virtual void OnEndPrinting(CDC* pDC, CPrintInfo* pInfo);
	virtual void OnDraw(CDC* pDC);
	//}}AFX_VIRTUAL

// Implementation
public:
	BOOL BuildSql(CQueryView *pQV);
	BOOL CheckRequired();
	//HBITMAP m_hbmp;
	virtual ~CCUSTOMERView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	//{{AFX_MSG(CCUSTOMERView)
	afx_msg void OnBtnModify();
	afx_msg void OnBtnAdd();
	afx_msg void OnBtnDel();
	afx_msg void OnBtnClear();
	afx_msg void OnBtnSearchByName();
	afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);
	afx_msg void OnBtnUploadPic();
	afx_msg void OnBtnCustomerQuery();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

#ifndef _DEBUG  // debug version in HRSView.cpp
inline CCUSTOMERDoc* CCUSTOMERView::GetDocument()
   { return (CCUSTOMERDoc*)m_pDocument; }
#endif

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_HRSVIEW_H__CF3C79A5_1D12_4B7B_863F_AE84A946616E__INCLUDED_)
