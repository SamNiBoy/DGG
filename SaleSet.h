#if !defined(AFX_SaleSET_H__A9041C98_3DB5_478A_AF26_7E72BE34E27B__INCLUDED_)
#define AFX_SaleSET_H__A9041C98_3DB5_478A_AF26_7E72BE34E27B__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// SaleSet.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CSaleSet recordset

class CSaleSet : public CRecordset
{
public:
	CSaleSet();
	DECLARE_DYNAMIC(CSaleSet)

// Field/Param Data
	//{{AFX_FIELD(CSaleSet, CRecordset)
	CString	m_saleid;
	CString	m_boxid;
	CString	m_itemid;
	CString	m_itemname;
	float	m_saleprice;
	float	m_saletotprice;
	int	m_saletotqty;
	CTime   m_saledate;
	CString	m_description;
	//}}AFX_FIELD


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CSaleSet)
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

#endif // !defined(AFX_SaleSET_H__A9041C98_3DB5_478A_AF26_7E72BE34E27B__INCLUDED_)
