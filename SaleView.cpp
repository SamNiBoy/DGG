// SaleView.cpp : implementation file
//

#include "stdafx.h"
#include "HRS.h"
#include "SaleView.h"
#include "queryview.h"
#include "dlgfindlist.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CSaleView

IMPLEMENT_DYNCREATE(CSaleView, CRecordView)

CSaleView::CSaleView()
	: CRecordView(CSaleView::IDD)
{
	//{{AFX_DATA_INIT(CSaleView)
	//}}AFX_DATA_INIT
	m_dteSaleFrom = CTime::GetCurrentTime();
	m_dteSaleTo = CTime::GetCurrentTime();
}

CSaleView::~CSaleView()
{
}

void CSaleView::DoDataExchange(CDataExchange* pDX)
{
	CRecordView::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CSaleView)
	DDX_Text(pDX, IDC_EDT_SALEID, m_pSet->m_saleid);
	DDX_Text(pDX, IDC_EDT_SALEBOXID, m_pSet->m_boxid);
	DDX_Text(pDX, IDC_EDT_SALEITEMID, m_pSet->m_itemid);
	DDX_Text(pDX, IDC_EDT_SALEITEMNAME, m_pSet->m_itemname);
	DDX_Text(pDX, IDC_EDT_SALEPRICE, m_pSet->m_saleprice);
	DDX_Text(pDX, IDC_EDT_SALETOTPRICE, m_pSet->m_saletotprice);
	DDX_Text(pDX, IDC_EDT_SALEQTY, m_pSet->m_saletotqty);
	DDX_Text(pDX, IDC_EDT_SALEDESCRIPTION, m_pSet->m_description);
	DDX_DateTimeCtrl(pDX, IDC_DATETIMEPICKER_SALEDATE, m_pSet->m_saledate);
	DDX_DateTimeCtrl(pDX, IDC_DATETIMEPICKER_SALEDATEFROM, m_dteSaleFrom);
	DDX_DateTimeCtrl(pDX, IDC_DATETIMEPICKER_SALEDATETO, m_dteSaleTo);
	//}}AFX_DATA_MAP
}
#ifdef _DEBUG
CSaleDoc* CSaleView::GetDocument() // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CSaleDoc)));
	return (CSaleDoc*)m_pDocument;
}
#endif
CRecordset* CSaleView::OnGetRecordset()
{
	return m_pSet;
}

BEGIN_MESSAGE_MAP(CSaleView, CRecordView)
	//{{AFX_MSG_MAP(CSaleView)
	ON_BN_CLICKED(IDC_BTN_SALEBOXQUERY, OnBtnSalequery)
	ON_BN_CLICKED(IDC_BTN_SALEADD, OnBtnSaleadd)
	ON_BN_CLICKED(IDC_BTN_SALEMODIFY, OnBtnSalemodify)
	ON_BN_CLICKED(IDC_BTN_SALEDEL, OnBtnSaledel)
	ON_BN_CLICKED(IDC_BTN_SALECLEAR, OnBtnSaleclear)
	ON_EN_CHANGE(IDC_EDT_SALEQTY, OnChangeEdtSaleqty)
	ON_EN_KILLFOCUS(IDC_EDT_BARCODE, OnKillfocusEdtBarcode)
	ON_EN_KILLFOCUS(IDC_EDT_SALEITEMID, OnKillfocusEdtSaleitemid)
	ON_BN_CLICKED(IDC_BTN_SALEITEMQUERY, OnBtnSaleitemquery)
	ON_NOTIFY(HDN_ITEMCLICK, IDC_LST_SALERECORD, OnItemclickLstSalerecord)
	ON_NOTIFY(NM_CLICK, IDC_LST_SALERECORD, OnClickLstSalerecord)
	ON_BN_CLICKED(IDC_BTN_SALEIDQUERY, OnBtnSaleidquery)
	ON_BN_CLICKED(IDC_BTN_SALEINFOQUERY, OnBtnSaleinfoquery)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CSaleView diagnostics

#ifdef _DEBUG
void CSaleView::AssertValid() const
{
	CRecordView::AssertValid();
}

void CSaleView::Dump(CDumpContext& dc) const
{
	CRecordView::Dump(dc);
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CSaleView message handlers

void CSaleView::OnInitialUpdate() 
{
	
	// TODO: Add your specialized code here and/or call the base class
	CSaleDoc *pDoc=(CSaleDoc*)GetDocument();
	m_pSet = &pDoc->m_SaleSet;
	CSize s(1000,1000);
	this->SetScrollSizes(MM_TEXT,s);
	CRecordView::OnInitialUpdate();
	m_pSet->Close();
	CListCtrl *pLstBx = (CListCtrl*)GetDlgItem(IDC_LST_SALERECORD);
	pLstBx->InsertColumn(0, "销售编号");
	pLstBx->InsertColumn(1, "格子编号");
	pLstBx->InsertColumn(2, "物品编号");
	pLstBx->InsertColumn(3, "物品名称");
	pLstBx->InsertColumn(4, "售价");
	pLstBx->InsertColumn(5, "数量");
	pLstBx->InsertColumn(6, "总价");
	pLstBx->InsertColumn(7, "时间");
	pLstBx->InsertColumn(8, "销售额");
	pLstBx->SetColumnWidth(0, 100);
	pLstBx->SetColumnWidth(1, 70);
	pLstBx->SetColumnWidth(2, 70);
	pLstBx->SetColumnWidth(3, 70);	
	pLstBx->SetColumnWidth(4, 70);	
	pLstBx->SetColumnWidth(5, 70);
	pLstBx->SetColumnWidth(6, 70);
	pLstBx->SetColumnWidth(7, 150);
	pLstBx->SetColumnWidth(8, 150);
	
	ListSaleRecords("");
}

void CSaleView::OnBtnSalequery() 
{
	// TODO: Add your control notification handler code here
	CString boxid;
	GetDlgItemText(IDC_EDT_SALEBOXID, boxid);
	boxid.TrimLeft();
	boxid.TrimRight();
	if(boxid.GetLength()<=0)
	{
		AfxMessageBox("请输入格子编号！");
		return;
	}
	else
	{
	CString filter;
	filter = "  boxid = '"+boxid+"'";
	CDlgFindList finder("storage", filter, "name", "boxid", this);

	if(finder.DoModal() == IDCANCEL)
		return;
	CString barcod;
	CString itemname = finder.m_sSelectedValue, itemid;
	CRecordset rs(&CDbManger::db);
	CString sql = "select itemid from storage where boxid ='"+boxid+"' and name = '"+itemname+"'";

	rs.Open(CRecordset::forwardOnly, sql);
	if(rs.IsOpen() && !rs.IsEOF())
	{
		rs.GetFieldValue("itemid", itemid);
		barcod = boxid+"-"+itemid;
	    SetDlgItemText(IDC_EDT_BARCODE, barcod);
		OnKillfocusEdtBarcode();
	}
	}
}

void CSaleView::OnBtnSaleadd() 
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
		CString boxid, itemid, saleqty;
		GetDlgItemText(IDC_EDT_SALEBOXID, boxid);
		GetDlgItemText(IDC_EDT_SALEITEMID, itemid);
		GetDlgItemText(IDC_EDT_SALEQTY, saleqty);
		if(CheckRequired() && SaleOutItem(itemid, boxid, saleqty))
		{
		    m_pSet->AddNew();
		    UpdateData();
			m_pSet->m_saledate = CTime::GetCurrentTime();
			m_pSet->m_saleid=CDbManger::GenerateNewID("SALEID");
		    UpdateData(false);
		    m_pSet->Update();
			CString saleid;
			GetDlgItemText(IDC_EDT_SALEID, saleid);
			CDbManger::RePrepareRecordset(m_pSet, "saleid", saleid);
			UpdateData(false);
			ListSaleRecords("");
		}
	}
}

BOOL CSaleView::CheckRequired()
{
	CString saleid, boxid, itemid, totprice, totqty;
	GetDlgItemText(IDC_EDT_SALEID, saleid);
	GetDlgItemText(IDC_EDT_SALEBOXID, boxid);
	GetDlgItemText(IDC_EDT_SALEITEMID, itemid);
	GetDlgItemText(IDC_EDT_SALETOTPRICE, totprice);
	GetDlgItemText(IDC_EDT_SALEQTY, totqty);

	boxid.TrimLeft();
	boxid.TrimRight();

	itemid.TrimLeft();
	itemid.TrimRight();

	totprice.TrimLeft();
	totprice.TrimRight();

	totqty.TrimLeft();
	totqty.TrimRight();
	if(!boxid.GetLength())
	{
		AfxMessageBox("请输入格子ID!", MB_OK|MB_ICONERROR);
		return FALSE;
	}
	if(!itemid.GetLength())
	{
		AfxMessageBox("请输入物品ID!", MB_OK|MB_ICONERROR);
		return FALSE;
	}
	if(!totprice.GetLength())
	{
		AfxMessageBox("请输入销售总价格!", MB_OK|MB_ICONERROR);
		return FALSE;
	}
	if(!totqty.GetLength())
	{
		AfxMessageBox("请输入销售总数量!", MB_OK|MB_ICONERROR);
		return FALSE;
	}
	return TRUE;

}

void CSaleView::OnBtnSalemodify() 
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
			CString saleid;
			GetDlgItemText(IDC_EDT_SALEID, saleid);
			CDbManger::RePrepareRecordset(m_pSet, "saleid", saleid);
			UpdateData(false);
			ListSaleRecords("");
		}
	}	
}

void CSaleView::OnBtnSaledel() 
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
		CString boxid, itemid, bkqty;
		GetDlgItemText(IDC_EDT_SALEBOXID, boxid);
		GetDlgItemText(IDC_EDT_SALEITEMID, itemid);
		GetDlgItemText(IDC_EDT_SALEQTY, bkqty);
		BOOL putToBox = false;
		if(AfxMessageBox("物品放回格子？", MB_YESNO|MB_ICONINFORMATION) == IDYES)
		{
			putToBox = true;
		}
		if(CallBackItem(itemid, boxid, bkqty, putToBox))
		{
	    m_pSet->Delete();
		OnBtnSaleclear();
		m_pSet->Close();
		ListSaleRecords("");
		}
	}	
}

void CSaleView::OnBtnSaleclear() 
{
	// TODO: Add your control notification handler code here
	m_pSet->Close();
	SetDlgItemText(IDC_EDT_SALEID,"");
	SetDlgItemText(IDC_EDT_SALEBOXID,"");
	SetDlgItemText(IDC_EDT_SALEITEMID,"");
	SetDlgItemText(IDC_EDT_SALEQTY,"");
	//SetDlgItemText(IDC_DATETIMEPICKER_SALEDATE,CTime::GetCurrentTime());
	SetDlgItemText(IDC_EDT_SALETOTPRICE,"");
	SetDlgItemText(IDC_EDT_SALEDESCRIPTION,"");
	SetDlgItemText(IDC_EDT_SALEITEMNAME, "");
	SetDlgItemText(IDC_EDT_SALEPRICE, "");
	SetDlgItemText(IDC_EDT_SALEQTY, "");
	SetDlgItemText(IDC_EDT_BARCODE, "");
	
	//UpdateData(false);
}

void CSaleView::OnChangeEdtSaleqty() 
{
	// TODO: If this is a RICHEDIT control, the control will not
	// send this notification unless you override the CRecordView::OnInitDialog()
	// function and call CRichEditCtrl().SetEventMask()
	// with the ENM_CHANGE flag ORed into the mask.
	
	// TODO: Add your control notification handler code here
	CString price, qty;
	int iqty;
	double fprice, ftotprice;
	GetDlgItemText(IDC_EDT_SALEPRICE, price);
	GetDlgItemText(IDC_EDT_SALEQTY, qty);

	iqty = atoi(qty);
	fprice = atof(price);

	ftotprice = iqty * fprice;

	CString totprice;
	totprice.Format("%0.2lf", ftotprice);

	SetDlgItemText(IDC_EDT_SALETOTPRICE, totprice);	
}

void CSaleView::OnKillfocusEdtBarcode() 
{
	// TODO: Add your control notification handler code here
	CString boxid, itemid, barcod, str;
	GetDlgItemText(IDC_EDT_BARCODE, barcod);
	CEdit *pEdt = (CEdit*)GetDlgItem(IDC_EDT_BARCODE);
	barcod.TrimLeft();
	barcod.TrimRight();
	if(barcod.GetLength()<=0)
		return;
	int idx = barcod.Find('-');
	if(idx<0)
	{
		AfxMessageBox("条形号码格式不对：“格子编号-物品编号”");
		return;
	}
	boxid = barcod.Left(idx);
	itemid = barcod.Right(barcod.GetLength()-idx-1);
	boxid.TrimLeft();
	boxid.TrimRight();
	itemid.TrimLeft();
	itemid.TrimRight();

	//AfxMessageBox(boxid+":"+itemid);
	CRecordset rs(&CDbManger::db), *p;
	p=&rs;
	CString sql;
	sql = "select 'x' from box where boxid = '"+boxid+"'";
	rs.Open(CRecordset::forwardOnly, sql);
	/*try
	{
	    CDbManger::ExecuteSQL(sql);
	}
	catch(CDBException *e)
	{
		mst.Format("ERROR:%d", e->m_nRetCode);
		AfxMessageBox(mst);
	}*/
	if(p->IsEOF())
	{
		str.Format("条形号码错误，找不到格子：“%s”！", boxid);
		AfxMessageBox(str);
		p->Close();
		pEdt->SetFocus();
		return;
	}
	else
	{
		p->Close();
		sql = "select 'x' from item where itemid = '"+itemid+"'";
		rs.Open(CRecordset::forwardOnly, sql);
		if(p->IsEOF())
		{
			str.Format("条形号码错误，找不到物品：“%s”！", itemid);
			AfxMessageBox(str);
			p->Close();
			pEdt->SetFocus();
			return;
		}
	}
	p->Close();
	SetDlgItemText(IDC_EDT_SALEBOXID, boxid);
	SetDlgItemText(IDC_EDT_SALEITEMID, itemid);
	OnKillfocusEdtSaleitemid();
	pEdt = (CEdit*)GetDlgItem(IDC_EDT_SALEQTY);
	pEdt->SetFocus();
	pEdt->SetSel(0,100);
	
}

void CSaleView::OnKillfocusEdtSaleitemid() 
{
	// TODO: Add your control notification handler code here
	CRecordset rs(&CDbManger::db), *p=&rs;
	CString sql, itemid, str;
	GetDlgItemText(IDC_EDT_SALEITEMID, itemid);
	itemid.TrimLeft();
	itemid.TrimRight();
	if(itemid.GetLength()<=0)
		return;
	sql = "select name, price, qty from storage where itemid = '"+itemid+"'";
	rs.Open(CRecordset::forwardOnly, sql);
	if(p->IsEOF())
	{
		str.Format("找不到物品：“%s”！", itemid);
		AfxMessageBox(str);
		p->Close();
			//pEdt->SetFocus();
		return;
	}
	CString name, price, qty;
	p->GetFieldValue("name",name);
	p->GetFieldValue("price",price);
	p->GetFieldValue("qty",qty);

	name.TrimLeft();
	name.TrimRight();
	price.TrimLeft();
	price.TrimRight();

	SetDlgItemText(IDC_EDT_SALEITEMNAME, name);
	SetDlgItemText(IDC_EDT_SALEPRICE, price);
	SetDlgItemText(IDC_EDT_SALEQTY, qty);

	p->Close();

}

void CSaleView::ListSaleRecords(CString filter)
{
	CListCtrl *pLstBx = (CListCtrl*)GetDlgItem(IDC_LST_SALERECORD);

	pLstBx->DeleteAllItems();

	CRecordset rs(&CDbManger::db), *p;
    CString strCmd;
	filter.TrimLeft();
	filter.TrimRight();
	if(filter.GetLength()<=0)
	{
		filter = " YEAR(saledate) = YEAR(GETDATE()) AND MONTH(saledate) = MONTH(GETDATE()) AND DAY(saledate) = DAY(GETDATE()) ";
	}
	else
	{
		filter = filter + " and  YEAR(saledate) = YEAR(GETDATE()) AND MONTH(saledate) = MONTH(GETDATE()) AND DAY(saledate) = DAY(GETDATE()) ";
	}
	strCmd= "select saleid, boxid, itemid, itemname, price, totqty, totprice ,saledate from sale where "+filter+ " order by saledate asc";
	//::AfxMessageBox(strCmd);
	rs.Open(CRecordset::forwardOnly, strCmd);

	CString saleid, boxid, itemid, itemname,price, totqty, totprice;
	CDBVariant saledate;

	p = & rs;
	int i=0;
	double dsumprice=0.0;
	CString dte, sumprice;
	while(!rs.IsEOF())
	{
		p->GetFieldValue("saleid", saleid);
		p->GetFieldValue("boxid", boxid);
		p->GetFieldValue("itemid", itemid);
		p->GetFieldValue("itemname", itemname);
		p->GetFieldValue("price", price);
		p->GetFieldValue("totqty", totqty);
		p->GetFieldValue("totprice", totprice);
		p->GetFieldValue("saledate", saledate);
		saleid.TrimLeft();
		saleid.TrimRight();
		boxid.TrimLeft();
		boxid.TrimRight();
		itemid.TrimLeft();
		itemid.TrimRight();
		itemname.TrimLeft();
		itemname.TrimRight();
		price.TrimLeft();
		price.TrimRight();
		totqty.TrimLeft();
		totqty.TrimRight();
		totprice.TrimLeft();
		totprice.TrimRight();
		//saledate.TrimLeft();
		//saledate.TrimRight();

		CString txt;
		int rid;
		//txt.Format("%s\t%s\t%s\t%s", itemid, name,qty, price);
		//AfxMessageBox(txt);
		//txt = itemid+qty+price;
		/*pLstBx->InsertColumn(0, "销售编号");
	      pLstBx->InsertColumn(1, "格子编号");
	      pLstBx->InsertColumn(2, "物品编号");
	      pLstBx->InsertColumn(3, "物品名称");
	      pLstBx->InsertColumn(4, "数量");
	      pLstBx->InsertColumn(5, "总价");
	      pLstBx->InsertColumn(6, "时间");
	    */
		rid=pLstBx->InsertItem(0, saleid);
		pLstBx->SetItemText(rid, 1, boxid);
		pLstBx->SetItemText(rid, 2, itemid);
		pLstBx->SetItemText(rid, 3, itemname);
		pLstBx->SetItemText(rid, 4, price);
		pLstBx->SetItemText(rid, 5, totqty);
		pLstBx->SetItemText(rid, 6, totprice);
		
		dte.Format("%d时%d分 %d月%d日%d年",saledate.m_pdate->hour,saledate.m_pdate->minute,saledate.m_pdate->month, saledate.m_pdate->day,saledate.m_pdate->year);
		pLstBx->SetItemText(rid, 7, dte);

		dsumprice += atof(totprice);

		sumprice.Format("%0.2lf",dsumprice);
		pLstBx->SetItemText(rid, 8, sumprice);



		p->MoveNext();
	}
	p->Close();

}

void CSaleView::OnBtnSaleitemquery() 
{
	// TODO: Add your control notification handler code here
	CString itemname;
	GetDlgItemText(IDC_EDT_SALEITEMNAME, itemname);
	itemname.TrimLeft();
	itemname.TrimRight();
	if(itemname.GetLength()<=0)
	{
		AfxMessageBox("请输入物品名称！");
		return;
	}
	else
	{
	CString filter;
	filter = "  name = '"+itemname+"'";
	CDlgFindList finder("storage", filter, "boxid", "name", this);

	if(finder.DoModal() == IDCANCEL)
		return;
	CString barcod;
	CString boxid = finder.m_sSelectedValue, itemid;
	CRecordset rs(&CDbManger::db);
	CString sql = "select itemid from storage where boxid ='"+boxid+"' and name = '"+itemname+"'";

	rs.Open(CRecordset::forwardOnly, sql);
	if(rs.IsOpen() && !rs.IsEOF())
	{
		rs.GetFieldValue("itemid", itemid);
		barcod = boxid+"-"+itemid;
	    SetDlgItemText(IDC_EDT_BARCODE, barcod);
		rs.Close();
		OnKillfocusEdtBarcode();
	}
	}	
}


void CSaleView::OnItemclickLstSalerecord(NMHDR* pNMHDR, LRESULT* pResult) 
{
	HD_NOTIFY *phdn = (HD_NOTIFY *) pNMHDR;
	// TODO: Add your control notification handler code here


	*pResult = 0;
}

void CSaleView::OnClickLstSalerecord(NMHDR* pNMHDR, LRESULT* pResult) 
{
	// TODO: Add your control notification handler code here
	CListCtrl *pLstBx = (CListCtrl*)GetDlgItem(IDC_LST_SALERECORD);
	POSITION pos = pLstBx->GetFirstSelectedItemPosition();
	while(pos)
	{
		int idx = pLstBx->GetNextSelectedItem(pos);
		CString saleid;		
		saleid=pLstBx->GetItemText(idx,0);
		//AfxMessageBox(str);
		SetDlgItemText(IDC_EDT_SALEID,saleid);
		OnBtnSaleidquery();
	}	
	*pResult = 0;
}

void CSaleView::OnBtnSaleidquery() 
{
	// TODO: Add your control notification handler code here
	CString saleid;
	GetDlgItemText(IDC_EDT_SALEID, saleid);
	saleid.TrimLeft();
	saleid.TrimRight();
	if(saleid.GetLength()<=0)
	{
		AfxMessageBox("请输入销售编号！");
		return;
	}
	CDbManger::RePrepareRecordset(m_pSet, "saleid", saleid);
	UpdateData(false);
}

BOOL CSaleView::SaleOutItem(CString itemid, CString boxid, CString qty)
{
	CRecordset rs(&CDbManger::db);
	CString strCmd = "select qty from storage where boxid ='"+boxid+"' and itemid ='"+itemid+"'";
	rs.Open(CRecordset::forwardOnly, strCmd);
	CString boxqty;
	if(rs.IsOpen() && !rs.IsEOF())
	{
	    rs.GetFieldValue("qty", boxqty);
		rs.Close();
		if(atoi(boxqty) < atoi(qty))
		{
			AfxMessageBox("格子中物品不够出售!", MB_OK|MB_ICONERROR);
			return FALSE;
		}
		else if(atoi(boxqty) > atoi(qty))
		{
			strCmd = "update storage set qty = qty -"+qty+" where boxid ='"+boxid+"' and itemid ='"+itemid+"'";
			CDbManger::ExecuteSQL(strCmd);
		}
		else
		{
			strCmd = "delete from storage where boxid ='"+boxid+"' and itemid ='"+itemid+"'";
			CDbManger::ExecuteSQL(strCmd);
		}
		return TRUE;
	}
	else
	{
			AfxMessageBox("格子中没有该物品!", MB_OK|MB_ICONERROR);
			return FALSE;
	}
	return TRUE;
}

BOOL CSaleView::CallBackItem(CString itemid, CString boxid, CString qty, BOOL bPutToBox)
{
	if(bPutToBox)
	{
	    CRecordset rs(&CDbManger::db);
	    CString strCmd = "select qty from storage where boxid ='"+boxid+"' and itemid ='"+itemid+"'";
	    rs.Open(CRecordset::forwardOnly, strCmd);
	    if(rs.IsOpen() && !rs.IsEOF())
		{
			rs.Close();
			strCmd = "update storage set qty = qty +"+qty+ " where boxid = '" + boxid +"' and itemid ='"+itemid+"'";
			CDbManger::ExecuteSQL(strCmd);
		}
		else
		{
			strCmd = "select name, price from item where itemid ='"+itemid+"'";

			rs.Open(CRecordset::forwardOnly, strCmd);
			if(rs.IsOpen() && !rs.IsEOF())
			{
				CString itemname, itemprice;
				rs.GetFieldValue("name", itemname);
				rs.GetFieldValue("price", itemprice);
			    CString strCmd = "insert into storage (boxid, itemid, name, price, qty, description) values ('"+boxid+"', '"+ itemid+"', '"+itemname+"', "+itemprice+","+qty+", '退货')";
			    CDbManger::ExecuteSQL(strCmd);
				rs.Close();
			}
		}
	}
	else
	{
	    CRecordset rs(&CDbManger::db);
	    CString strCmd = "select 'x' from item where itemid ='"+itemid+"'";
	    rs.Open(CRecordset::forwardOnly, strCmd);
		if(rs.IsOpen() && !rs.IsEOF())
		{
			rs.Close();
			strCmd = "update item set qty = qty +" + qty +" where itemid ='"+itemid+"'";
			CDbManger::ExecuteSQL(strCmd);
			return TRUE;
		}
		else
		{
			AfxMessageBox("不存在该物品的库存信息！", MB_OK|MB_ICONERROR);
			return FALSE;
		}
	}
			return TRUE;
}

void CSaleView::OnBtnSaleinfoquery() 
{
	// TODO: Add your control notification handler code here
    CSaleDoc *pDoc=(CSaleDoc *)GetDocument();
	POSITION pos = pDoc->GetFirstViewPosition();
	CView *pV = NULL;
	while(pos)
	{
		pV = pDoc->GetNextView(pos);
		if(pV->IsKindOf(RUNTIME_CLASS(CQueryView)))
			break;
	}
	CQueryView *pQV = (CQueryView*) pV;


	CButton * pQueryAdmin = (CButton *) GetDlgItem(IDC_CHK_QUERYADMIN);
	CString filter;
	CString boxid, itemid;
	CString dterange;
	UpdateData();
	dterange.Format(" and (saledate between '%4d-%2d-%2d %2d:%2d:%2d' and '%4d-%2d-%2d %2d:%2d:%2d')",
		m_dteSaleFrom.GetYear(),
		m_dteSaleFrom.GetMonth(),
		m_dteSaleFrom.GetDay(),
		0,0,0,
		m_dteSaleTo.GetYear(),
		m_dteSaleTo.GetMonth(),
		m_dteSaleTo.GetDay()+1,
		0,0,0);
	GetDlgItemText(IDC_EDT_SALEBOXIDQUERY, boxid);
	GetDlgItemText(IDC_EDT_SALEITEMIDQUERY, itemid);
	boxid.TrimLeft();
	boxid.TrimRight();
	itemid.TrimLeft();
	itemid.TrimRight();

	if(boxid.GetLength()>0)
	{
		pQV->m_sFilter = " where s.boxid = '"+boxid+"'";
	}
	else 
		pQV->m_sFilter = " where 1 = 1 ";
	if(itemid.GetLength()>0)
		pQV->m_sFilter += " and s.itemid ='"+itemid+"'";

	pQV->m_sFilter += dterange;

	pQV->m_sFootFilter = pQV->m_sFilter;
	pQV->m_sFilter += " order by s.saledate desc ";




	pQV->m_sQuerySql = "select s.saleid 销售编号, "
		               "        s.boxid 格子编号, "
					   "        s.itemname  物品名称, "
					   "        s.price  销售价格, "
					   "        s.totqty 销售数量,"
					   "        s.totprice 总价, "
					   "        s.saledate 日期 "
					   "  from sale s ";

	TRACE("sql: %s \n where: %s\n", pQV->m_sQuerySql, pQV->m_sFilter);

	pQV->m_sFootSql = "select sum(totprice) 销售额 from sale s ";
	
	pQV->QueryRecordset();
	pDoc->UpdateAllViews(this);		
}
