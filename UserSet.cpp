// UserSet.cpp : implementation file
//

#include "stdafx.h"
#include "hrs.h"
#include "UserSet.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CUserSet

IMPLEMENT_DYNAMIC(CUserSet, CRecordset)

CUserSet::CUserSet(CDatabase* pdb)
	: CRecordset(pdb)
{
	//{{AFX_FIELD_INIT(CUserSet)
	m_userid = _T("");
	m_password = _T("");
	m_name = _T("");
	m_sex = _T("");
	m_age = 0;
	m_isadmin = 0;
	m_address = _T("");
	m_tel = _T("");
	m_email = _T("");
	m_nFields = 9;
	//}}AFX_FIELD_INIT
	m_nDefaultType = dynaset;
	m_strFilter = " 1= 2 ";
}


CString CUserSet::GetDefaultConnect()
{
	return _T("ODBC;DSN=dgg");
}

CString CUserSet::GetDefaultSQL()
{
	return _T("[dbo].[shopowner]");
}

void CUserSet::DoFieldExchange(CFieldExchange* pFX)
{
	//{{AFX_FIELD_MAP(CUserSet)
	pFX->SetFieldType(CFieldExchange::outputColumn);
	RFX_Text(pFX, _T("[userid]"), m_userid);
	RFX_Text(pFX, _T("[password]"), m_password);
	RFX_Text(pFX, _T("[name]"), m_name);
	RFX_Text(pFX, _T("[sex]"), m_sex);
	RFX_Int(pFX, _T("[age]"), m_age);
	RFX_Int(pFX, _T("[isadmin]"), m_isadmin);
	RFX_Text(pFX, _T("[address]"), m_address);
	RFX_Text(pFX, _T("[tel]"), m_tel);
	RFX_Text(pFX, _T("[email]"), m_email);
	//}}AFX_FIELD_MAP
}

/////////////////////////////////////////////////////////////////////////////
// CUserSet diagnostics

#ifdef _DEBUG
void CUserSet::AssertValid() const
{
	CRecordset::AssertValid();
}

void CUserSet::Dump(CDumpContext& dc) const
{
	CRecordset::Dump(dc);
}
#endif //_DEBUG
