// DlgBoxLayout.cpp : implementation file
//

#include "stdafx.h"
#include "hrs.h"
#include "DlgBoxLayout.h"
#include "Dbmanger.h"
#include "DlgFindList.h"
#include <math.h>

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDlgBoxLayout dialog


CDlgBoxLayout::CDlgBoxLayout(CString &boxid, CWnd* pParent /*=NULL*/)
	: m_boxid(boxid), CDialog(CDlgBoxLayout::IDD, pParent)
{
	//{{AFX_DATA_INIT(CDlgBoxLayout)
	m_itemid = _T("");
	m_itemname = _T("");
	m_qty = 0;
	m_price = 0.0;
	m_totprice = 0.0;
	m_boxitemqty = 0;
	m_boxtotprice = 0.0;
	m_ownerid = _T("");
	m_discnt = 0.0;
	m_description = _T("");
	m_expdte = 0;
	m_mandte = 0;
	//}}AFX_DATA_INIT
}


void CDlgBoxLayout::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDlgBoxLayout)
	DDX_Control(pDX, IDC_LST_LAYOUT_BOXITEM, m_cLstBox);
	DDX_Text(pDX, IDC_EDT_LAYOUT_BOXID, m_boxid);
	DDX_Text(pDX, IDC_EDT_LAYOUT_ITEMID, m_itemid);
	DDX_Text(pDX, IDC_EDT_LAYOUT_ITEMNAME, m_itemname);
	DDX_Text(pDX, IDC_EDT_LAYOUT_ITEMQTY, m_qty);
	DDX_Text(pDX, IDC_EDT_LAYOUT_ITEMPRICE, m_price);
	DDX_Text(pDX, IDC_EDT_LAYOUT_ITEMTOTPRICE, m_totprice);
	DDX_Text(pDX, IDC_EDT_LAYOUT_BOXITEMQTY, m_boxitemqty);
	DDX_Text(pDX, IDC_EDT_LAYOUT_BOXTOTPRICE, m_boxtotprice);
	DDX_Text(pDX, IDC_EDT_LAYOUT_ITEMOWNERID, m_ownerid);
	DDX_Text(pDX, IDC_EDT_LAYOUT_ITEMDISCNT, m_discnt);
	DDX_Text(pDX, IDC_EDT_LAYOUT_ITEMDESCRIPTION, m_description);
	DDX_DateTimeCtrl(pDX, IDC_DATETIMEPICKER_LAYOUT_EXPDTE, m_expdte);
	DDX_DateTimeCtrl(pDX, IDC_DATETIMEPICKER_LAYOUT_MANDTE, m_mandte);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CDlgBoxLayout, CDialog)
	//{{AFX_MSG_MAP(CDlgBoxLayout)
	ON_BN_CLICKED(IDC_BTN_LAYOUT_ITEMQUERY, OnBtnLayoutItemquery)
	ON_EN_CHANGE(IDC_EDT_LAYOUT_ITEMQTY, OnChangeEdtLayoutItemqty)
	ON_BN_CLICKED(IDC_BTN_LAYOUT_PUTTOBOX, OnBtnLayoutPuttobox)
	ON_BN_CLICKED(IDC_BTN_LAYOUT_ITEMCLEAR, OnBtnLayoutItemclear)
	ON_BN_CLICKED(IDC_BTN_LAYOUT_CLEARBOX, OnBtnLayoutClearbox)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDlgBoxLayout message handlers

void CDlgBoxLayout::OnBtnLayoutItemquery() 
{
	// TODO: Add your control notification handler code here
	UpdateData();
	CString itemid, filter;
	GetDlgItemText(IDC_EDT_LAYOUT_ITEMID, itemid);
	itemid.TrimLeft();
	itemid.TrimRight();

	if(itemid.GetLength()>0)
	{
		filter = " itemid like '%"+itemid+"%'";
	}
	else
	{
		filter = " 1 = 1 ";
	}

	CDlgFindList finder("item", filter, "name", "itemid", this);

	if(finder.DoModal() == IDCANCEL)
		return;

	filter.Format(" itemid = '%s'", finder.m_sSelectedId);


	CRecordset rs(&CDbManger::db);
	CString strCmd = "select itemid, ownerid, name, qty, price,discnt,description from item where " + filter;
	rs.Open(CRecordset::forwardOnly, strCmd);
	if(!rs.IsEOF())
	{
		CString itemid, ownerid, name, qty, price, discnt, description;
		CRecordset *p=&rs;
		p->GetFieldValue("itemid", itemid);
		p->GetFieldValue("ownerid", ownerid);
		p->GetFieldValue("name", name);
		p->GetFieldValue("qty", qty);
		p->GetFieldValue("price", price);
		p->GetFieldValue("discnt", discnt);
		p->GetFieldValue("description", description);
		SetDlgItemText(IDC_EDT_LAYOUT_ITEMID, itemid);
		SetDlgItemText(IDC_EDT_LAYOUT_ITEMOWNERID, ownerid);
		SetDlgItemText(IDC_EDT_LAYOUT_ITEMNAME, name);
		SetDlgItemText(IDC_EDT_LAYOUT_ITEMQTY, qty);
		SetDlgItemText(IDC_EDT_LAYOUT_ITEMPRICE, price);
		SetDlgItemText(IDC_EDT_LAYOUT_ITEMDISCNT, discnt);
		SetDlgItemText(IDC_EDT_LAYOUT_ITEMDESCRIPTION, description);

	int iqty;
	double fprice, fdiscnt, ftotprice;
	iqty = atoi(qty);
	fprice = atof(price);
	fdiscnt = atof(discnt);

	ftotprice = iqty * fprice * fdiscnt;

	CString totprice;
	totprice.Format("%0.2lf", ftotprice);
    SetDlgItemText(IDC_EDT_LAYOUT_ITEMTOTPRICE, totprice);
		p->Close();
	}
	else
	{
		AfxMessageBox("不存在该物品编号！");
		return;
	}
}

void CDlgBoxLayout::OnChangeEdtLayoutItemqty() 
{
	// TODO: If this is a RICHEDIT control, the control will not
	// send this notification unless you override the CDialog::OnInitDialog()
	// function and call CRichEditCtrl().SetEventMask()
	// with the ENM_CHANGE flag ORed into the mask.
	
	// TODO: Add your control notification handler code here
	CString qty, price, discnt;
	int iqty;
	double fprice, fdiscnt, ftotprice;
	GetDlgItemText(IDC_EDT_LAYOUT_ITEMQTY, qty);
	GetDlgItemText(IDC_EDT_LAYOUT_ITEMPRICE, price);
	GetDlgItemText(IDC_EDT_LAYOUT_ITEMDISCNT, discnt);
	iqty = atoi(qty);
	fprice = atof(price);
	fdiscnt = atof(discnt);

	ftotprice = iqty * fprice * fdiscnt;

	CString totprice;
	totprice.Format("%0.2lf", ftotprice);
    SetDlgItemText(IDC_EDT_LAYOUT_ITEMTOTPRICE, totprice);	
}

void CDlgBoxLayout::OnBtnLayoutPuttobox() 
{
	// TODO: Add your control notification handler code here
	if(CheckRequired())
	{
		CRecordset rs(&CDbManger::db);
        CString strCmd = "select qty, price from storage where boxid = '"+m_boxid+"' and itemid ='" + m_itemid+"'";
		CString updCmd = "";
		//::AfxMessageBox(strCmd);
		rs.Open(CRecordset::forwardOnly, strCmd);
		if(!rs.IsEOF())
		{
			CRecordset *p=&rs;
			CString qty, price;
			p->GetFieldValue("qty", qty);
			p->GetFieldValue("price", price);

			p->Close();
			double dprice = atof(price);
			if(fabs(dprice-m_price)>0.01)
			{
				if(AfxMessageBox("设定价格与格子中物品价格不一致，继续？", MB_YESNO|MB_ICONINFORMATION) == IDNO)
					return;
			}

			if(m_qty == 0)
			{
				if(AfxMessageBox("您输入的数量为0，确认删除物品吗？", MB_YESNO|MB_ICONINFORMATION) == IDYES)
				{
					strCmd = "delete from storage where boxid = '"+m_boxid+"' and itemid ='" + m_itemid+"'";
					updCmd = "update item set qty = qty +"+qty+ " where itemid ='"+ m_itemid +"'";
				}
				else
					return;
			}
			else
			{
				CString mqty, mprice;
			    mqty.Format("%d", m_qty);
			    mprice.Format("%0.2f", m_price);

				if(m_qty > atoi(qty))
				{
					int det = m_qty - atoi(qty);
					CString moreqty;
					moreqty.Format("%d", det);

				    strCmd = "select 'x' from item where qty < "+moreqty+" and itemid ='"+m_itemid+"'";

				    rs.Open(CRecordset::forwardOnly, strCmd);

				    if(rs.IsOpen() && !rs.IsEOF())
					{
					    AfxMessageBox("物品数量不足！");
					    rs.Close();
					    return;
					}
				}
			    strCmd = "update storage set qty = "+mqty+", price = "+mprice+ " where boxid = '"+m_boxid+"' and itemid ='" + m_itemid+"'";
				if(m_qty > atoi(qty))
				{
					CString putqty;
					putqty.Format("%d",m_qty - atoi(qty));
					updCmd = "update item set qty = qty -"+putqty+ " where itemid ='"+ m_itemid +"'";
				}
				else if(m_qty < atoi(qty))
				{
					CString putbkqty;
					putbkqty.Format("%d",atoi(qty) - m_qty);
					updCmd = "update item set qty = qty + "+putbkqty+ " where itemid ='"+ m_itemid +"'";
				}

			}
			CDbManger::db.ExecuteSQL(strCmd);	
			SetBoxItems();
			CDbManger::ExecuteSQL(updCmd);
		}
		else
		{
			if(rs.IsOpen())
				rs.Close();
			if(m_qty == 0)
			{
				AfxMessageBox("您输入的数量为0，不能添加物品！", MB_OK|MB_ICONINFORMATION);
				return;
			}
			CString mqty, mprice;
			mqty.Format("%d", m_qty);
			mprice.Format("%0.2f", m_price);

			CString testsql;
			testsql.Format("select 'x' from item where qty < %s and itemid ='%s'", mqty, m_itemid);

			rs.Open(CRecordset::forwardOnly, testsql);

			if(rs.IsOpen() && !rs.IsEOF())
			{
			    AfxMessageBox("数量不足，不能放入这么多物品！");
			    rs.Close();
			    return;
			}
			
			CString strCmd = "insert into storage (boxid, itemid, name, price, qty, description) values ('"+m_boxid+"', '"+ m_itemid+"', '"+m_itemname+"', "+mprice+","+mqty+", '"+m_description+"')";
			CString updCmd = "";

			CString putqty;
			putqty.Format("%d",m_qty);
			updCmd = "update item set qty = qty -"+putqty+ " where itemid ='"+ m_itemid +"'";
			
			CDbManger::ExecuteSQL(strCmd);
			CDbManger::ExecuteSQL(updCmd);

			/*CListBox *pLstBx = (CListBox*)GetDlgItem(IDC_LST_LAYOUT_BOXITEM);

			CString txt = m_itemid + "    " + m_itemname + "    " + qty + "    " + price;

			pLstBx->AddString(txt);*/
			SetBoxItems();
		}
	}
}

BOOL CDlgBoxLayout::CheckRequired()
{
/*
	DDX_Control(pDX, IDC_LST_LAYOUT_BOXITEM, m_cLstBox);
	DDX_Text(pDX, IDC_EDT_LAYOUT_BOXID, m_boxid);
	DDX_Text(pDX, IDC_EDT_LAYOUT_ITEMID, m_itemid);
	DDX_Text(pDX, IDC_EDT_LAYOUT_ITEMNAME, m_itemname);
	DDX_Text(pDX, IDC_EDT_LAYOUT_ITEMQTY, m_qty);
	DDV_MinMaxInt(pDX, m_qty, 0, 10000);
	DDX_Text(pDX, IDC_EDT_LAYOUT_ITEMPRICE, m_price);
	DDX_Text(pDX, IDC_EDT_LAYOUT_ITEMTOTPRICE, m_totprice);
	DDX_Text(pDX, IDC_EDT_LAYOUT_BOXITEMQTY, m_boxitemqty);
	DDX_Text(pDX, IDC_EDT_LAYOUT_BOXTOTPRICE, m_boxtotprice);
	DDX_Text(pDX, IDC_EDT_LAYOUT_ITEMOWNERID, m_ownerid);
	DDX_Text(pDX, IDC_EDT_LAYOUT_ITEMDISCNT, m_discnt);
	DDX_Text(pDX, IDC_EDT_LAYOUT_ITEMDESCRIPTION, m_description);
	DDX_DateTimeCtrl(pDX, IDC_DATETIMEPICKER_LAYOUT_EXPDTE, m_expdte);
	DDX_DateTimeCtrl(pDX, IDC_DATETIMEPICKER_LAYOUT_MANDTE, m_mandte);
	*/
	CString itemid, itemprice, itemqty, itemname, itemdescription;
    GetDlgItemText(IDC_EDT_LAYOUT_ITEMID, itemid);
	GetDlgItemText(IDC_EDT_LAYOUT_ITEMPRICE, itemprice);
	GetDlgItemText(IDC_EDT_LAYOUT_ITEMQTY, itemqty);
	GetDlgItemText(IDC_EDT_LAYOUT_ITEMNAME, itemname);
	GetDlgItemText(IDC_EDT_LAYOUT_ITEMDESCRIPTION, itemdescription);

	m_boxid.TrimLeft();
	m_boxid.TrimRight();

	itemid.TrimLeft();
	itemid.TrimRight();

	itemprice.TrimLeft();
	itemprice.TrimRight();

	itemqty.TrimLeft();
	itemqty.TrimRight();

	m_itemname.TrimLeft();
	m_itemname.TrimRight();

	itemdescription.TrimLeft();
	itemdescription.TrimRight();

	if(!itemid.GetLength())
	{
		AfxMessageBox("请输入物品编号！");
		return FALSE;
	}
	if(!itemprice.GetLength())
	{
		AfxMessageBox("请输入物品价格！");
		return FALSE;
	}
	if(!itemqty.GetLength())
	{
		AfxMessageBox("请输入物品数量！");
		return FALSE;
	}
	if(!itemname.GetLength())
	{
		AfxMessageBox("请输入物品名称！");
		return FALSE;
	}

	m_itemid = itemid;
	m_price = atof(itemprice);
	m_qty = atoi(itemqty);
	m_itemname = itemname;

	return TRUE;
}

BOOL CDlgBoxLayout::OnInitDialog() 
{
	CDialog::OnInitDialog();
    CListCtrl *pLstBx = (CListCtrl*)GetDlgItem(IDC_LST_LAYOUT_BOXITEM);
	pLstBx->InsertColumn(0, "物品编号");
	pLstBx->InsertColumn(1, "物品名称");
	pLstBx->InsertColumn(2, "数量");
	pLstBx->InsertColumn(3, "价格");
	pLstBx->InsertColumn(4, "总价");
	pLstBx->SetColumnWidth(0, 80);
	pLstBx->SetColumnWidth(1, 80);
	pLstBx->SetColumnWidth(2, 50);
	pLstBx->SetColumnWidth(3, 50);	
	pLstBx->SetColumnWidth(4, 50);	
	// TODO: Add extra initialization here
	SetBoxItems();
	OnBtnLayoutItemclear();
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CDlgBoxLayout::SetBoxItems()
{
	CListCtrl *pLstBx = (CListCtrl*)GetDlgItem(IDC_LST_LAYOUT_BOXITEM);

	pLstBx->DeleteAllItems();

	CRecordset rs(&CDbManger::db), *p;
    CString strCmd = "select itemid, name, qty, price, qty*price totprice from storage where boxid = '"+m_boxid+"' order by itemid";
	//::AfxMessageBox(strCmd);
	rs.Open(CRecordset::forwardOnly, strCmd);

	CString itemid, name, qty, price, totprice;

	p = & rs;
	int i=0;
	while(!rs.IsEOF())
	{
		p->GetFieldValue("itemid", itemid);
		p->GetFieldValue("name", name);
		p->GetFieldValue("qty", qty);
		p->GetFieldValue("price", price);
		p->GetFieldValue("totprice", totprice);

		itemid.TrimLeft();
		itemid.TrimRight();
		name.TrimLeft();
		name.TrimRight();

		CString txt;
		int rid;
		//txt.Format("%s\t%s\t%s\t%s", itemid, name,qty, price);
		//AfxMessageBox(txt);
		//txt = itemid+qty+price;
		
		rid=pLstBx->InsertItem(0, itemid);
		pLstBx->SetItemText(rid, 1, name);
		pLstBx->SetItemText(rid, 2, qty);
		pLstBx->SetItemText(rid, 3, price);
		pLstBx->SetItemText(rid, 4, totprice);
		p->MoveNext();
	}
	p->Close();


	//Get statistic information

	strCmd = "select count(itemid) kinds, sum(price*qty) value from storage where boxid = '"+m_boxid+"'  group by boxid";
	rs.Open(CRecordset::forwardOnly, strCmd);
	if(!rs.IsEOF())
	{
		CString kinds, value;
		p->GetFieldValue("kinds", kinds);
		p->GetFieldValue("value", value);
		
		SetDlgItemText(IDC_EDT_LAYOUT_BOXITEMQTY, kinds);
		SetDlgItemText(IDC_EDT_LAYOUT_BOXTOTPRICE, value);
	}
	else
	{
		SetDlgItemText(IDC_EDT_LAYOUT_BOXITEMQTY, "0");
		SetDlgItemText(IDC_EDT_LAYOUT_BOXTOTPRICE, "0.0");
	}
	p->Close();

}

void CDlgBoxLayout::OnBtnLayoutItemclear() 
{
	// TODO: Add your control notification handler code here
	SetDlgItemText(IDC_EDT_LAYOUT_ITEMID,"");
	SetDlgItemText(IDC_EDT_LAYOUT_ITEMOWNERID,"");
	SetDlgItemText(IDC_EDT_LAYOUT_ITEMNAME,"");
	SetDlgItemText(IDC_EDT_LAYOUT_ITEMPRICE,"0.00");
	SetDlgItemText(IDC_EDT_LAYOUT_ITEMQTY,"0");
	SetDlgItemText(IDC_EDT_LAYOUT_ITEMDISCNT,"0");
	SetDlgItemText(IDC_EDT_LAYOUT_ITEMTOTPRICE,"0");
	SetDlgItemText(IDC_DATETIMEPICKER_LAYOUT_MANDTE,"");
	SetDlgItemText(IDC_DATETIMEPICKER_LAYOUT_EXPDTE,"");
	SetDlgItemText(IDC_EDT_LAYOUT_ITEMDESCRIPTION,"");
}

void CDlgBoxLayout::OnBtnLayoutClearbox() 
{
	// TODO: Add your control notification handler code here
	CString sql;
	CString qty;

	GetDlgItemText(IDC_EDT_LAYOUT_BOXITEMQTY, qty);
	if(atoi(qty)<=0)
	{
		AfxMessageBox("格子中没有任何物品!", MB_OK|MB_ICONINFORMATION);
		return;
	}

	if(AfxMessageBox("确认清空格子中所有物品？", MB_YESNO|MB_ICONEXCLAMATION) == IDYES)
	{

		long rtcod=AfxMessageBox("放回库存？", MB_YESNOCANCEL|MB_ICONEXCLAMATION);
		if(rtcod == IDYES)
		{
			CRecordset rs(&CDbManger::db);
			sql = "select itemid, qty from storage where boxid ='"+m_boxid+"'";
			rs.Open(CRecordset::forwardOnly, sql);
			CString itemid, boxqty;
			CMapStringToString si;
			while(rs.IsOpen() && !rs.IsEOF())
			{
				rs.GetFieldValue("itemid", itemid);
				rs.GetFieldValue("qty", boxqty);
				itemid.TrimLeft();
				itemid.TrimRight();
				boxqty.TrimLeft();
				boxqty.TrimRight();
				si.SetAt(itemid, boxqty);
				rs.MoveNext();
			}
			if(rs.IsOpen())
				rs.Close();
			POSITION pos = si.GetStartPosition();
			while(pos)
			{
				CDbManger::db.BeginTrans();
				si.GetNextAssoc(pos, itemid, boxqty);
			    sql = "update item set qty = qty +"+boxqty+" where itemid ='"+itemid+"'";
			    CDbManger::ExecuteSQL(sql);
				CDbManger::db.CommitTrans();
			}
		}
		else if(rtcod == IDNO)
		{
			if(AfxMessageBox("系统将会丢失被清空物品的记录，继续？", MB_YESNO|MB_ICONEXCLAMATION)==IDNO)
			{
				return;
			}
		}
		else
			return;

		sql.Format("delete from storage where boxid = '%s'", m_boxid);
		CDbManger::ExecuteSQL(sql);
		SetBoxItems();
	}
}
