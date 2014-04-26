#if !defined(AFX_ITEMSET_H__A9041C98_3DB5_478A_AF26_7E72BE34E27B__INCLUDED_)
#define AFX_ITEMSET_H__A9041C98_3DB5_478A_AF26_7E72BE34E27B__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// BoxSet.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CItemSet recordset

class CItemSet : public CRecordset
{
public:
	CItemSet();
	DECLARE_DYNAMIC(CItemSet)

// Field/Param Data
	//{{AFX_FIELD(CItemSet, CRecordset)
	CString	m_itemid;
	CString	m_ownerid;
	CString m_name;
	float	m_price;
	int     m_qty;
	int     m_initqty;
	float   m_discnt;
	CString	m_description;
	CTime   m_mandte;
	CTime   m_expdte;
	//}}AFX_FIELD


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CItemSet)
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

#endif // !defined(AFX_BOXSET_H__A9041C98_3DB5_478A_AF26_7E72BE34E27B__INCLUDED_)
