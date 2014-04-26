// BoxSet.cpp : implementation file
//

#include "stdafx.h"
#include "HRS.h"
#include "BoxSet.h"
#include "dbmanger.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CBoxSet

IMPLEMENT_DYNAMIC(CBoxSet, CRecordset)

CBoxSet::CBoxSet()
: CRecordset(&CDbManger::db)
{
	//{{AFX_FIELD_INIT(CBoxSet)
	m_boxid = _T("");
	m_ownerid = _T("");
	m_rentprice = 0.0f;
	m_description = _T("");
	m_nFields = 4;
	//}}AFX_FIELD_INIT
	//m_nDefaultType = snapshot;
	this->m_strFilter = " 1 = 2";
}


CString CBoxSet::GetDefaultConnect()
{
	return CDbManger::db.GetConnect();
}

CString CBoxSet::GetDefaultSQL()
{
	return _T("[dbo].[box]");
}

void CBoxSet::DoFieldExchange(CFieldExchange* pFX)
{
	//{{AFX_FIELD_MAP(CBoxSet)
	pFX->SetFieldType(CFieldExchange::outputColumn);
	RFX_Text(pFX, _T("[boxid]"), m_boxid);
	RFX_Text(pFX, _T("[ownerid]"), m_ownerid);
	RFX_Single(pFX, _T("[rentprice]"), m_rentprice);
	RFX_Text(pFX, _T("[description]"), m_description);
	//}}AFX_FIELD_MAP
	m_boxid.TrimLeft();
	m_boxid.TrimRight();
	m_ownerid.TrimLeft();
	m_ownerid.TrimRight();
	m_description.TrimLeft();
	m_description.TrimRight();

}

/////////////////////////////////////////////////////////////////////////////
// CBoxSet diagnostics

#ifdef _DEBUG
void CBoxSet::AssertValid() const
{
	CRecordset::AssertValid();
}

void CBoxSet::Dump(CDumpContext& dc) const
{
	CRecordset::Dump(dc);
}
#endif //_DEBUG
