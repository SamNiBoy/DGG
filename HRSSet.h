// HRSSet.h : interface of the CCUSTOMERSet class
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_HRSSET_H__EB620118_061C_4EA1_8266_7B94ECDDA6CA__INCLUDED_)
#define AFX_HRSSET_H__EB620118_061C_4EA1_8266_7B94ECDDA6CA__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

class CCUSTOMERSet : public CRecordset
{
public:
	CCUSTOMERSet();
	DECLARE_DYNAMIC(CCUSTOMERSet)

// Field/Param Data
	//{{AFX_FIELD(CCUSTOMERSet, CRecordset)
	CString m_sCustomerId;
	CString m_sCustomerName;
	CString m_sCustomerSex;
	int     m_iCustomerAge;
    CString m_sCustomerTelphone;
	CString m_sCustomerEmail;
	CString m_sCustomerAddress;
	int     m_iCustomerLevel;
	CString m_sCustomerDescription;
	CTime m_dCustomerJoinDate;
	//}}AFX_FIELD
	//CLongBinary	m_Pic;
// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CCUSTOMERSet)
	public:
	virtual CString GetDefaultConnect();	// Default connection string
	virtual CString GetDefaultSQL(); 	// default SQL for Recordset
	virtual void DoFieldExchange(CFieldExchange* pFX);	// RFX support
	virtual BOOL Open(UINT nOpenType = snapshot, LPCTSTR lpszSql = NULL, DWORD dwOptions = none);
	//}}AFX_VIRTUAL

// Implementation
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_HRSSET_H__EB620118_061C_4EA1_8266_7B94ECDDA6CA__INCLUDED_)

