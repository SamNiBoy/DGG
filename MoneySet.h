#if !defined(AFX_MONEYSET_H__3F3A7584_3F11_4FD9_9FAC_7C87140B719D__INCLUDED_)
#define AFX_MONEYSET_H__3F3A7584_3F11_4FD9_9FAC_7C87140B719D__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// UserSet.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CMoneySet recordset

class CMoneySet : public CRecordset
{
public:
	CMoneySet(CDatabase* pDatabase = NULL);
	DECLARE_DYNAMIC(CMoneySet)

// Field/Param Data
	//{{AFX_FIELD(CMoneySet, CRecordset)
	CString	m_costid;
	CString	m_class;
	CTime   m_date;
	CString	m_coster;
	double  m_qty;
	CString m_description;
	//}}AFX_FIELD


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CMoneySet)
	public:
	virtual CString GetDefaultConnect();    // Default connection string
	virtual CString GetDefaultSQL();    // Default SQL for Recordset
	virtual void DoFieldExchange(CFieldExchange* pFX);  // RFX support
	//}}AFX_VIRTUAL

// Implementation
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_USERSET_H__3F3A7584_3F11_4FD9_9FAC_7C87140B719D__INCLUDED_)
