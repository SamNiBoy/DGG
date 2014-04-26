// BoxSet.cpp : implementation file
//

#include "stdafx.h"
#include "HRS.h"
#include "itemSet.h"
#include "dbmanger.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CItemSet

IMPLEMENT_DYNAMIC(CItemSet, CRecordset)

CItemSet::CItemSet()
: CRecordset(&CDbManger::db)
{
	//{{AFX_FIELD_INIT(CItemSet)
	m_nFields = 10;
	m_itemid = _T("");
	m_ownerid = _T("");
	m_name = _T("");
	m_price = 0.0f;
	m_qty = 0;
	m_initqty = 0;
	m_discnt =0.0f;
	m_description = _T("");
	//}}AFX_FIELD_INIT
	//m_nDefaultType = snapshot;
	this->m_strFilter = " 1 = 2";
	m_mandte=m_expdte=m_mandte.GetCurrentTime();
}

CString CItemSet::GetDefaultConnect()
{
	return CDbManger::db.GetConnect();
}

CString CItemSet::GetDefaultSQL()
{
	return _T("[dbo].[item]");
}

void CItemSet::DoFieldExchange(CFieldExchange* pFX)
{
	//{{AFX_FIELD_MAP(CItemSet)
	pFX->SetFieldType(CFieldExchange::outputColumn);
	RFX_Text(pFX, _T("[itemid]"), m_itemid);
	RFX_Text(pFX, _T("[ownerid]"), m_ownerid);
	RFX_Text(pFX, _T("[name]"), m_name);
	RFX_Int(pFX, _T("[qty]"), m_qty);
	RFX_Int(pFX, _T("[initqty]"), m_initqty);
	RFX_Single(pFX, _T("[price]"), m_price);
	RFX_Single(pFX, _T("[discnt]"), m_discnt);
	RFX_Text(pFX, _T("[description]"), m_description);
	RFX_Date(pFX, _T("[mandte]"), m_mandte);
	RFX_Date(pFX, _T("[expdte]"), m_expdte);
	//}}AFX_FIELD_MAP
	m_itemid.TrimLeft();
	m_itemid.TrimRight();
	m_ownerid.TrimLeft();
	m_ownerid.TrimRight();
	m_name.TrimLeft();
	m_name.TrimRight();
	m_description.TrimLeft();
	m_description.TrimRight();
}

/////////////////////////////////////////////////////////////////////////////
// CItemSet diagnostics

#ifdef _DEBUG
void CItemSet::AssertValid() const
{
	CRecordset::AssertValid();
}

void CItemSet::Dump(CDumpContext& dc) const
{
	CRecordset::Dump(dc);
}
#endif //_DEBUG
