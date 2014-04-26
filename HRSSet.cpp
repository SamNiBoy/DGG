// HRSSet.cpp : implementation of the CCUSTOMERSet class
//

#include "stdafx.h"
#include "HRS.h"
#include "HRSSet.h"
#include "dbmanger.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CCUSTOMERSet implementation

IMPLEMENT_DYNAMIC(CCUSTOMERSet, CRecordset)

CCUSTOMERSet::CCUSTOMERSet()
: CRecordset(&CDbManger::db)
{
	//{{AFX_FIELD_INIT(CCUSTOMERSet)
	m_nFields = 10;
	m_iCustomerAge = 0;
	m_iCustomerLevel = 0;
	//}}AFX_FIELD_INIT
	//m_nDefaultType = snapshot;
	this->m_strFilter = " 1=2 ";
	m_dCustomerJoinDate = CTime::GetCurrentTime();
}

CString CCUSTOMERSet::GetDefaultConnect()
{
	//AfxMessageBox(CDbManger::db.GetConnect());
	return CDbManger::db.GetConnect();
	//return _T("ODBC;DSN=DGG");
}

CString CCUSTOMERSet::GetDefaultSQL()
{
	return _T("[dbo].[customer]");
}

void CCUSTOMERSet::DoFieldExchange(CFieldExchange* pFX)
{
	//{{AFX_FIELD_MAP(CCUSTOMERSet)
	pFX->SetFieldType(CFieldExchange::outputColumn);
	RFX_Text(pFX, _T("[customerid]"), m_sCustomerId);
	RFX_Text(pFX, _T("[name]"), m_sCustomerName);
	RFX_Text(pFX, _T("[sex]"), m_sCustomerSex);
	RFX_Int(pFX, _T("[age]"), m_iCustomerAge);
	RFX_Text(pFX, _T("[tel]"), m_sCustomerTelphone);
    RFX_Text(pFX, _T("[email]"), m_sCustomerEmail);
	RFX_Text(pFX, _T("[address]"), m_sCustomerAddress);
	RFX_Int(pFX, _T("[loylevel]"), m_iCustomerLevel);
	RFX_Text(pFX, _T("[description]"), m_sCustomerDescription);
	RFX_Date(pFX, _T("[joindate]"), m_dCustomerJoinDate);
	//RFX_LongBinary(pFX, _T("[Pic]"), m_Pic);
	//}}AFX_FIELD_MAP
	m_sCustomerId.TrimLeft();
	m_sCustomerId.TrimRight();
	m_sCustomerName.TrimLeft();
	m_sCustomerName.TrimRight();
	m_sCustomerSex.TrimLeft();
	m_sCustomerSex.TrimRight();
	m_sCustomerTelphone.TrimLeft();
	m_sCustomerTelphone.TrimRight();
	m_sCustomerEmail.TrimLeft();
	m_sCustomerEmail.TrimRight();
	m_sCustomerAddress.TrimLeft();
	m_sCustomerAddress.TrimRight();
	m_sCustomerDescription.TrimLeft();
	m_sCustomerDescription.TrimRight();
}

/////////////////////////////////////////////////////////////////////////////
// CCUSTOMERSet diagnostics

#ifdef _DEBUG
void CCUSTOMERSet::AssertValid() const
{
	CRecordset::AssertValid();
}

void CCUSTOMERSet::Dump(CDumpContext& dc) const
{
	CRecordset::Dump(dc);

}
#endif //_DEBUG

BOOL CCUSTOMERSet::Open(UINT nOpenType, LPCTSTR lpszSql, DWORD dwOptions) 
{
	// TODO: Add your specialized code here and/or call the base class
	//m_nFields = 10;
    //nOpenType &= CRecordset::dynamic;
	BOOL retcod = CRecordset::Open(nOpenType, lpszSql, dwOptions);

	return retcod;
}
