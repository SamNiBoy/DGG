// SaleSet.cpp : implementation file
//

#include "stdafx.h"
#include "HRS.h"
#include "SaleSet.h"
#include "dbmanger.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CSaleSet

IMPLEMENT_DYNAMIC(CSaleSet, CRecordset)

CSaleSet::CSaleSet()
: CRecordset(&CDbManger::db)
{
	//{{AFX_FIELD_INIT(CSaleSet)
	m_saleid = _T("");
	m_boxid = _T("");
	m_itemid = _T("");
	m_itemname = _T("");
	m_saleprice = 0.0f;
	m_saletotprice = 0.0f;
	m_saletotqty = 0;
	m_description = _T("");
	m_nFields = 9;
	//}}AFX_FIELD_INIT
	//m_nDefaultType = snapshot;
	this->m_strFilter = " 1 = 2";
	m_saledate=m_saledate.GetCurrentTime();
}


CString CSaleSet::GetDefaultConnect()
{
	return CDbManger::db.GetConnect();
}

CString CSaleSet::GetDefaultSQL()
{
	return _T("[dbo].[Sale]");
}

void CSaleSet::DoFieldExchange(CFieldExchange* pFX)
{
	//{{AFX_FIELD_MAP(CSaleSet)
	pFX->SetFieldType(CFieldExchange::outputColumn);
	RFX_Text(pFX, _T("[saleid]"), m_saleid);
	RFX_Text(pFX, _T("[boxid]"), m_boxid);
	RFX_Text(pFX, _T("[itemid]"), m_itemid);
	RFX_Text(pFX, _T("[itemname]"), m_itemname);
	RFX_Single(pFX, _T("[price]"), m_saleprice);
	RFX_Single(pFX, _T("[totprice]"), m_saletotprice);
	RFX_Int(pFX, _T("[totqty]"), m_saletotqty);
	RFX_Text(pFX, _T("[description]"), m_description);
	RFX_Date(pFX, _T("[saledate]"), m_saledate);
	//}}AFX_FIELD_MAP
	m_saleid.TrimLeft();
	m_saleid.TrimRight();
	m_boxid.TrimLeft();
	m_boxid.TrimRight();
	m_itemid.TrimLeft();
	m_itemid.TrimRight();
	m_itemname.TrimLeft();
	m_itemname.TrimRight();
	m_description.TrimLeft();
	m_description.TrimRight();
}

/////////////////////////////////////////////////////////////////////////////
// CSaleSet diagnostics

#ifdef _DEBUG
void CSaleSet::AssertValid() const
{
	CRecordset::AssertValid();
}

void CSaleSet::Dump(CDumpContext& dc) const
{
	CRecordset::Dump(dc);
}
#endif //_DEBUG
