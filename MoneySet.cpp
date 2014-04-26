// UserSet.cpp : implementation file
//

#include "stdafx.h"
#include "hrs.h"
#include "moneySet.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CMoneySet

IMPLEMENT_DYNAMIC(CMoneySet, CRecordset)

CMoneySet::CMoneySet(CDatabase* pdb)
	: CRecordset(pdb)
{
	//{{AFX_FIELD_INIT(CMoneySet)
	m_costid = _T("");
	m_class = _T("");
	m_coster = _T("");
	m_description = _T("");
	m_qty = 0.0;
	m_nFields = 6;
	//}}AFX_FIELD_INIT
	m_date = CTime::GetCurrentTime();
	m_nDefaultType = dynaset;
	m_strFilter = " 1= 2 ";
}


CString CMoneySet::GetDefaultConnect()
{
	return _T("ODBC;DSN=dgg");
}

CString CMoneySet::GetDefaultSQL()
{
	return _T("[dbo].[cost]");
}

void CMoneySet::DoFieldExchange(CFieldExchange* pFX)
{
	//{{AFX_FIELD_MAP(CMoneySet)
	pFX->SetFieldType(CFieldExchange::outputColumn);
	RFX_Text(pFX, _T("[costid]"), m_costid);
	RFX_Text(pFX, _T("[class]"), m_class);
	RFX_Text(pFX, _T("[coster]"), m_coster);
	RFX_Double(pFX, _T("[qty]"), m_qty);
	RFX_Date(pFX, _T("[date]"), m_date);
	RFX_Text(pFX, _T("[description]"), m_description);
	//}}AFX_FIELD_MAP
}

/////////////////////////////////////////////////////////////////////////////
// CMoneySet diagnostics

#ifdef _DEBUG
void CMoneySet::AssertValid() const
{
	CRecordset::AssertValid();
}

void CMoneySet::Dump(CDumpContext& dc) const
{
	CRecordset::Dump(dc);
}
#endif //_DEBUG
