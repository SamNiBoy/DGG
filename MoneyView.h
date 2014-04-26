#if !defined(AFX_MONEYVIEW_H__C9E71293_2605_4A94_84FC_793AC3243290__INCLUDED_)
#define AFX_MONEYVIEW_H__C9E71293_2605_4A94_84FC_793AC3243290__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// MoneyView.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CMoneyView record view

#include "moneySet.h"
#include "queryview.h"

class CMoneyView : public CRecordView
{
protected:
	CMoneyView();           // protected constructor used by dynamic creation
	DECLARE_DYNCREATE(CMoneyView)

// Form Data
public:
	//{{AFX_DATA(CMoneyView)
	enum { IDD = IDD_MONEY_FORM };
	CComboBox	m_cmbQueryClass;
	CComboBox	m_cmbClass;
	CMoneySet * m_pSet;
	CTime	m_CostBegDte;
	CTime	m_CostEndDte;
	//}}AFX_DATA

// Attributes
public:

// Operations
public:
	BOOL CheckRequired();
	CMoneySet* GetRecordset();
	BOOL CMoneyView::BuildSql(CQueryView * pQV);


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CMoneyView)
		// NOTE - the ClassWizard will add and remove member functions here.
	public:
	virtual CRecordset* OnGetRecordset();
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	virtual void OnInitialUpdate();
	//}}AFX_VIRTUAL

// Implementation
protected:
	virtual ~CMoneyView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

	// Generated message map functions
	//{{AFX_MSG(CMoneyView)
	afx_msg void OnBtnMoneyquery();
	afx_msg void OnBtnMoneyclear();
	afx_msg void OnBtnMoneyadd();
	afx_msg void OnBtnMoneymodify();
	afx_msg void OnBtnMoneydel();
	afx_msg void OnBtnMoneyInfoquery();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_MoneyVIEW_H__C9E71293_2605_4A94_84FC_793AC3243290__INCLUDED_)
