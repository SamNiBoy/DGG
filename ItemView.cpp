// BoxView.cpp : implementation file
//

#include "stdafx.h"
#include "HRS.h"
#include "ItemView.h"
#include "DlgFindList.h"
#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CItemView

IMPLEMENT_DYNCREATE(CItemView, CRecordView)

CItemView::CItemView()
	: CRecordView(CItemView::IDD)
{
	//{{AFX_DATA_INIT(CItemView)
	//}}AFX_DATA_INIT
}

CItemView::~CItemView()
{
}

void CItemView::DoDataExchange(CDataExchange* pDX)
{
	CRecordView::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CItemView)
	DDX_Text(pDX, IDC_EDT_ITEMID, m_pSet->m_itemid);
	DDX_Text(pDX, IDC_EDT_ITEMOWNERID, m_pSet->m_ownerid);
	DDX_Text(pDX, IDC_EDT_ITEMNAME, m_pSet->m_name);
	DDX_Text(pDX, IDC_EDT_ITEMDISCNT, m_pSet->m_discnt);
	DDX_Text(pDX, IDC_EDT_ITEMPRICE, m_pSet->m_price);
	DDX_Text(pDX, IDC_EDT_ITEMQTY, m_pSet->m_qty);
	DDX_Text(pDX, IDC_EDT_ITEMINITQTY, m_pSet->m_initqty);
	DDX_Text(pDX, IDC_EDT_ITEMDESCRIPTION, m_pSet->m_description);
	DDX_DateTimeCtrl(pDX, IDC_DATETIMEPICKER_MANDTE, m_pSet->m_mandte);
	DDX_DateTimeCtrl(pDX, IDC_DATETIMEPICKER_EXPDTE, m_pSet->m_expdte);
	//}}AFX_DATA_MAP
}

#ifdef _DEBUG
CItemDoc* CItemView::GetDocument() // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CItemDoc)));
	return (CItemDoc*)m_pDocument;
}
#endif

CRecordset* CItemView::OnGetRecordset()
{
	return m_pSet;
}

BEGIN_MESSAGE_MAP(CItemView, CRecordView)
	//{{AFX_MSG_MAP(CItemView)
	ON_BN_CLICKED(IDC_BTN_ITEMQUERY, OnBtnItemquery)
	ON_BN_CLICKED(IDC_BTN_ITEMADD, OnBtnItemadd)
	ON_BN_CLICKED(IDC_BTN_ITEMMODIFY, OnBtnItemmodify)
	ON_BN_CLICKED(IDC_BTN_ITEMDEL, OnBtnItemdel)
	ON_BN_CLICKED(IDC_BTN_ITEMCLEAR, OnBtnItemclear)
	ON_BN_CLICKED(IDC_BTN_ITEMOWNERQUERY, OnBtnItemownerquery)
	ON_EN_KILLFOCUS(IDC_EDT_ITEMDISCNT, OnKillfocusEdtItemdiscnt)
	ON_EN_KILLFOCUS(IDC_EDT_ITEMPRICE, OnKillfocusEdtItemprice)
	ON_EN_KILLFOCUS(IDC_EDT_ITEMQTY, OnKillfocusEdtItemqty)
	ON_BN_CLICKED(IDC_BTN_ITEMINFOQUERY, OnBtnIteminfoquery)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CItemView diagnostics

#ifdef _DEBUG
void CItemView::AssertValid() const
{
	CRecordView::AssertValid();
}

void CItemView::Dump(CDumpContext& dc) const
{
	CRecordView::Dump(dc);
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CItemView message handlers

void CItemView::OnInitialUpdate() 
{
	
	// TODO: Add your specialized code here and/or call the base class
	m_pSet = &GetDocument()->m_ItemSet;
	CSize s(1000,1000);
	this->SetScrollSizes(MM_TEXT,s);
	CRecordView::OnInitialUpdate();
	m_pSet->Close();
}

void CItemView::OnBtnItemquery() 
{
	// TODO: Add your control notification handler code here
	CString name, filter;
	GetDlgItemText(IDC_EDT_ITEMNAME, name);
	name.TrimLeft();
	name.TrimRight();
	if(name.GetLength()>0)
	{
		filter = " name like '%"+name+"%'";
	}
	else
	{
		filter = " 1 = 1 ";
	}

	CDlgFindList finder("item", filter, "name", "itemid", this);

	if(finder.DoModal() == IDCANCEL)
		return;

	m_pSet->m_strFilter.Format(" itemid = '%s'", finder.m_sSelectedId);

	m_pSet->Close();
	m_pSet->Open();
	if(!m_pSet->IsEOF())
	{
		//m_sCustomerName = m_pSet->m_sCustomerName;
		m_pSet->MoveFirst();
		UpdateData(FALSE);
	}
	if(m_pSet->IsEOF())
	{
		this->MessageBox("没有找到记录!");
	}
}

void CItemView::OnBtnItemadd() 
{
	// TODO: Add your control notification handler code here
	
	if(!m_pSet->IsOpen())
	{
		m_pSet->Open();
	}
	if(!m_pSet->CanUpdate())
	{
		this->MessageBox("不能添加记录！");
		return;
	}
	else
	{
		if(CheckRequired())
		{
		    m_pSet->AddNew();
		    UpdateData();
			m_pSet->m_itemid=CDbManger::GenerateNewID("ITEMID");
			UpdateData(false);
		    m_pSet->Update();
			CString itemid;
			GetDlgItemText(IDC_EDT_ITEMID, itemid);
			CDbManger::RePrepareRecordset(m_pSet, "itemid", itemid);
			UpdateData(false);
		}
	}
}

BOOL CItemView::CheckRequired()
{
	CString name;
	GetDlgItemText(IDC_EDT_ITEMNAME, name);
	name.TrimLeft();
	name.TrimRight();
	if(!name.GetLength())
	{
		AfxMessageBox("请输入物品名称!", MB_OK|MB_ICONERROR);
		return FALSE;
	}
	CString price;
	GetDlgItemText(IDC_EDT_ITEMPRICE, price);
	price.TrimLeft();
	price.TrimRight();
	if(!price.GetLength())
	{
		AfxMessageBox("请输入物品价格!", MB_OK|MB_ICONERROR);
		return FALSE;
	}
	else if(atof(price)<=0)
	{
		AfxMessageBox("物品价格必须大于0！");
		return FALSE;
	}
	CString ownerid;
	GetDlgItemText(IDC_EDT_ITEMOWNERID, ownerid);
	ownerid.TrimLeft();
	ownerid.TrimRight();
	if(!ownerid.GetLength())
	{
		AfxMessageBox("请输入物主编号!", MB_OK|MB_ICONERROR);
		return FALSE;
	}

	CString qty;
	GetDlgItemText(IDC_EDT_ITEMQTY, qty);
	qty.TrimLeft();
	qty.TrimRight();
	if(!qty.GetLength())
	{
		AfxMessageBox("请输入物品数量!", MB_OK|MB_ICONERROR);
		return FALSE;
	}
	else if(atoi(qty)<0)
	{
		AfxMessageBox("物品数量必须大于等于0！");
		return FALSE;
	}
	CString discnt;
	GetDlgItemText(IDC_EDT_ITEMDISCNT, discnt);
	discnt.TrimLeft();
	discnt.TrimRight();
	if(!discnt.GetLength())
	{
		AfxMessageBox("请输入折扣信息!", MB_OK|MB_ICONERROR);
		return FALSE;
	}
	else if(atof(discnt)<=0 || atof(discnt)>1.0)
	{
		AfxMessageBox("物品折扣必须大于0小于等于1！");
		return FALSE;
	}
	return TRUE;

}

void CItemView::OnBtnItemmodify() 
{
	// TODO: Add your control notification handler code here
	if(!m_pSet->IsOpen())
	{
		AfxMessageBox("请先查询记录，再修改！");
		return;
	}
	if(!m_pSet->CanUpdate())
	{
		this->MessageBox("不能修改记录！");
		return;
	}
	else
	{
		if(CheckRequired())
		{
		    m_pSet->Edit();
		    UpdateData();
	        m_pSet->Update();
			CString itemid;
			GetDlgItemText(IDC_EDT_ITEMID, itemid);
			CDbManger::RePrepareRecordset(m_pSet, "itemid", itemid);
			UpdateData(false);
		}
	}	
}

void CItemView::OnBtnItemdel() 
{
	// TODO: Add your control notification handler code here
	if(!m_pSet->IsOpen())
	{
		AfxMessageBox("请先查询记录，再删除！");
		return;
	}
	if(!m_pSet->CanUpdate())
	{
		this->MessageBox("不能删除记录！");
		return;
	}
	else
	{
	    m_pSet->Delete();
		OnBtnItemclear();
		m_pSet->Close();

	}	
}

void CItemView::OnBtnItemclear() 
{
	// TODO: Add your control notification handler code here
	m_pSet->Close();
	SetDlgItemText(IDC_EDT_ITEMID,"");
	SetDlgItemText(IDC_EDT_ITEMOWNERID,"");
	SetDlgItemText(IDC_EDT_ITEMPRICE,"");
	SetDlgItemText(IDC_EDT_ITEMDESCRIPTION,"");
	SetDlgItemText(IDC_EDT_ITEMNAME,"");
	SetDlgItemText(IDC_EDT_ITEMDISCNT,"");
	SetDlgItemText(IDC_EDT_ITEMQTY,"");
	SetDlgItemText(IDC_EDT_ITEMINITQTY,"");
	SetDlgItemText(IDC_DATETIMEPICKER_MANDTE,"");
	SetDlgItemText(IDC_DATETIMEPICKER_EXPDTE,"");
}


void CItemView::OnBtnItemownerquery() 
{
	// TODO: Add your control notification handler code here
	CString ownerid, filter;
	GetDlgItemText(IDC_EDT_ITEMOWNERID, ownerid);
	ownerid.TrimLeft();
	ownerid.TrimRight();
	if(ownerid.GetLength()>0)
	{
		filter = " customerid like '%"+ownerid+"%'";
	}
	else
	{
		filter = " 1 = 1 ";
	}

	CDlgFindList finder("customer", filter, "name", "customerid", this);

	if(finder.DoModal() == IDCANCEL)
		return;
	SetDlgItemText(IDC_EDT_ITEMOWNERID, finder.m_sSelectedId);
}

void CItemView::OnKillfocusEdtItemdiscnt() 
{
	// TODO: Add your control notification handler code here
	CString price, qty, discnt;
	int iqty;
	double fprice, fdiscnt, ftotprice;
	GetDlgItemText(IDC_EDT_ITEMPRICE, price);
	GetDlgItemText(IDC_EDT_ITEMQTY, qty);
	GetDlgItemText(IDC_EDT_ITEMDISCNT, discnt);
	iqty = atoi(qty);
	fprice = atof(price);
	fdiscnt = atof(discnt);

	ftotprice = iqty * fprice * fdiscnt;

	CString totprice;
	totprice.Format("%0.2lf", ftotprice);

	SetDlgItemText(IDC_EDT_ITEMTOTPRICE, totprice);	
}

void CItemView::OnKillfocusEdtItemprice() 
{
	// TODO: Add your control notification handler code here
	CString price, qty, discnt;
	int iqty;
	double fprice, fdiscnt, ftotprice;
	GetDlgItemText(IDC_EDT_ITEMPRICE, price);
	GetDlgItemText(IDC_EDT_ITEMQTY, qty);
	GetDlgItemText(IDC_EDT_ITEMDISCNT, discnt);
	iqty = atoi(qty);
	fprice = atof(price);
	fdiscnt = atof(discnt);

	ftotprice = iqty * fprice * fdiscnt;

	CString totprice;
	totprice.Format("%0.2lf", ftotprice);

	SetDlgItemText(IDC_EDT_ITEMTOTPRICE, totprice);		
}

void CItemView::OnKillfocusEdtItemqty() 
{
	// TODO: Add your control notification handler code here
	CString price, qty, discnt;
	int iqty;
	double fprice, fdiscnt, ftotprice;
	GetDlgItemText(IDC_EDT_ITEMPRICE, price);
	GetDlgItemText(IDC_EDT_ITEMQTY, qty);
	GetDlgItemText(IDC_EDT_ITEMDISCNT, discnt);
	iqty = atoi(qty);
	fprice = atof(price);
	fdiscnt = atof(discnt);

	ftotprice = iqty * fprice * fdiscnt;

	CString totprice;
	totprice.Format("%0.2lf", ftotprice);

	SetDlgItemText(IDC_EDT_ITEMTOTPRICE, totprice);		
}

void CItemView::OnBtnIteminfoquery() 
{
	// TODO: Add your control notification handler code here
    CItemDoc *pDoc=GetDocument();
	POSITION pos = pDoc->GetFirstViewPosition();
	CView *pV = NULL;
	while(pos)
	{
		pV = pDoc->GetNextView(pos);
		if(pV->IsKindOf(RUNTIME_CLASS(CQueryView)))
			break;
	}
	CQueryView *pQV = (CQueryView*) pV;


	if (BuildSql(pQV))
	{
	    TRACE("sql: %s \n where: %s\n", pQV->m_sQuerySql, pQV->m_sFilter);
		pQV->QueryRecordset();
	    pDoc->UpdateAllViews(this);
	}	
}

BOOL CItemView::BuildSql(CQueryView *pQV)
{
	pQV->m_sQuerySql = "";
	pQV->m_sFilter = " where 1=1 ";
	CString filter = " and 1=1 ";

	CString itemid, ownerid;
	GetDlgItemText(IDC_EDT_ITEMIDQUERY, itemid);
	GetDlgItemText(IDC_EDT_ITEMOWNERIDQUERY, ownerid);
	itemid.TrimLeft();
	itemid.TrimRight();
	ownerid.TrimLeft();
	ownerid.TrimRight();

	if(itemid.GetLength()>0)
	{
		filter = " and i.itemid = '"+itemid+"'";
	}
	if(ownerid.GetLength()>0)
	{
		filter = filter + " and i.ownerid = '"+ownerid+"'";
	}

	pQV->m_sQuerySql = "select i.itemid 物品编号, " 
		               "       i.name 物品名称,  "
					   "       c.customerid 物主编号, "
					   "       c.name 物主名称,  "
	                   "       i.price 物品价格, "
					   "       i.qty 物品数量, "
					   "       i.discnt 折扣, "
					   "       i.initqty 进货数量,"
					   "       i.initqty - i.qty 销售数量"
	                   "  from item i "
					   "  join customer c "
					   "    on i.ownerid = c.customerid ";

	pQV->m_sFilter = " where 1 = 1 "+ filter;
	pQV->m_sTitle = "物品库存信息";
	pQV->m_sFootSql = "select count(c.itemid) 物品总数,sum(c.price*c.qty)总价值 from item c ";
	pQV->m_sFootFilter = " where 1 = 1 " + filter;
	
	return TRUE;
}
