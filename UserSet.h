#if !defined(AFX_USERSET_H__3F3A7584_3F11_4FD9_9FAC_7C87140B719D__INCLUDED_)
#define AFX_USERSET_H__3F3A7584_3F11_4FD9_9FAC_7C87140B719D__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// UserSet.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CUserSet recordset

class CUserSet : public CRecordset
{
public:
	CUserSet(CDatabase* pDatabase = NULL);
	DECLARE_DYNAMIC(CUserSet)

// Field/Param Data
	//{{AFX_FIELD(CUserSet, CRecordset)
	CString	m_userid;
	CString	m_password;
	CString	m_name;
	CString	m_sex;
	int		m_age;
	int		m_isadmin;
	CString	m_address;
	CString	m_tel;
	CString	m_email;
	//}}AFX_FIELD


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CUserSet)
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
