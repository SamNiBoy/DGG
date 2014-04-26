// BoxView.cpp : implementation file
//

#include "stdafx.h"
#include "HRS.h"
#include "BoxView.h"
#include "DlgFindList.h"
#include "dlgboxlayout.h"
#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CBoxView

IMPLEMENT_DYNCREATE(CBoxView, CRecordView)

CBoxView::CBoxView()
	: CRecordView(CBoxView::IDD)
{
	//{{AFX_DATA_INIT(CBoxView)
	m_sRentName = _T("");
	m_dRentPrice = 0.0;
	m_iRentSeqnum = 0;
	m_dTotPrice = 0.0;
	m_sRentDescription = _T("");
	m_bRentPayed = FALSE;
	//}}AFX_DATA_INIT
	m_dteRentFrom = CTime::GetCurrentTime();
	m_dteRentTo = CTime::GetCurrentTime();
}

CBoxView::~CBoxView()
{
}

void CBoxView::DoDataExchange(CDataExchange* pDX)
{
	CRecordView::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CBoxView)
	DDX_Control(pDX, IDC_CHK_BOX_RENTEXP, m_cIncludeRentExp);
	DDX_Control(pDX, IDC_CHK_BOX_RENT, m_cIncludeRent);
	DDX_Control(pDX, IDC_CHK_BOX_ITEM, m_cIncludeItem);
	DDX_Control(pDX, IDC_CHK_BOX_CUSTOMER, m_cIncludeCustomer);
	DDX_Control(pDX, IDC_CHK_CURBOX, m_cCurBox);
	DDX_Text(pDX, IDC_EDT_BOXRENTNAME, m_sRentName);
	DDX_Text(pDX, IDC_EDT_BOXRENTPRICE, m_dRentPrice);
	DDX_Text(pDX, IDC_EDT_BOXRENTSEQNUM, m_iRentSeqnum);
	DDX_Text(pDX, IDC_EDT_BOXRENTTOTPRICE, m_dTotPrice);
	DDX_Text(pDX, IDC_EDT_BOXRENTDESCRIPTION, m_sRentDescription);
	DDX_DateTimeCtrl(pDX, IDC_DTEPK_RENTFROM, m_dteRentFrom);
	DDX_DateTimeCtrl(pDX, IDC_DTEPK_RENTTO, m_dteRentTo);
	DDX_Check(pDX, IDC_CHK_RENTPAYED, m_bRentPayed);
	DDX_Text(pDX, IDC_EDT_BOXID, m_pSet->m_boxid);
	DDX_Text(pDX, IDC_EDT_BOXOWNERID, m_pSet->m_ownerid);
	DDX_Text(pDX, IDC_EDT_BOXPRICE, m_pSet->m_rentprice);
	DDX_Text(pDX, IDC_EDT_BOXDESCRIPTION, m_pSet->m_description);
	//}}AFX_DATA_MAP
}

#ifdef _DEBUG
CBoxDoc* CBoxView::GetDocument()
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CBoxDoc)));
	return (CBoxDoc*)m_pDocument;
}
#endif

CRecordset* CBoxView::OnGetRecordset()
{
	return m_pSet;
}

BEGIN_MESSAGE_MAP(CBoxView, CRecordView)
	//{{AFX_MSG_MAP(CBoxView)
	ON_BN_CLICKED(IDC_BTN_BOXQUERY, OnBtnBoxquery)
	ON_BN_CLICKED(IDC_BTN_BOXADD, OnBtnBoxadd)
	ON_BN_CLICKED(IDC_BTN_BOXMODIFY, OnBtnBoxmodify)
	ON_BN_CLICKED(IDC_BTN_BOXDEL, OnBtnBoxdel)
	ON_BN_CLICKED(IDC_BTN_BOXCLEAR, OnBtnBoxclear)
	ON_BN_CLICKED(IDC_BTN_BOXLAYOUT, OnBtnBoxlayout)
	ON_BN_CLICKED(IDC_BTN_BOX_QUERY, OnBtnBoxQuery)
	ON_EN_KILLFOCUS(IDC_EDT_BOXOWNERID, OnKillfocusEdtBoxownerid)
	ON_NOTIFY(DTN_CLOSEUP, IDC_DTEPK_RENTFROM, OnCloseupDtepkRentfrom)
	ON_NOTIFY(DTN_CLOSEUP, IDC_DTEPK_RENTTO, OnCloseupDtepkRentto)
	ON_BN_CLICKED(IDC_BTN_BOXRENTADD, OnBtnBoxrentadd)
	ON_BN_CLICKED(IDC_BTN_BOXRENTMODIFY, OnBtnBoxrentmodify)
	ON_BN_CLICKED(IDC_BTN_BOXRENTDEL, OnBtnBoxrentdel)
	ON_BN_CLICKED(IDC_BTN_BOXRENTOVER, OnBtnBoxrentover)
	ON_BN_CLICKED(IDC_CHK_BOX_RENT, OnChkBoxRent)
	ON_BN_CLICKED(IDC_BTN_BOXRENTQUERY, OnBtnBoxrentquery)
	ON_BN_CLICKED(IDC_CHK_BOX_RENTEXP, OnChkBoxRentexp)
	ON_BN_CLICKED(IDC_CHK_BOX_CUSTOMER, OnChkBoxCustomer)
	ON_BN_CLICKED(IDC_CHK_BOX_ITEM, OnChkBoxItem)
	ON_BN_CLICKED(IDC_BTN_BOXOWNERQUERY, OnBtnBoxownerquery)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CBoxView diagnostics

#ifdef _DEBUG
void CBoxView::AssertValid() const
{
	CRecordView::AssertValid();
}

void CBoxView::Dump(CDumpContext& dc) const
{
	CRecordView::Dump(dc);
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CBoxView message handlers

void CBoxView::OnInitialUpdate() 
{
	
	// TODO: Add your specialized code here and/or call the base class
	m_pSet = &GetDocument()->m_BoxSet;

	CSize s(1000,1000);
	this->SetScrollSizes(MM_TEXT,s);
	CRecordView::OnInitialUpdate();
	m_pSet->Close();
	m_cCurBox.SetCheck(false);
	m_cIncludeCustomer.SetCheck(true);
	m_cIncludeRent.SetCheck(false);
	m_cIncludeItem.SetCheck(true);

	CRecordset rs(&CDbManger::db);
	CString sql = "select count(*) cnt from rent where payed = 0 and dteto <= getdate() ";
	rs.Open(CRecordset::forwardOnly, sql);
	if(rs.IsOpen() && !rs.IsEOF())
	{
		CString cnt="0";
		rs.GetFieldValue("cnt", cnt);
		if(atoi(cnt)>0)
		{
			CString txt;
			txt.Format("你有%s笔租赁到期，请查询到期租赁并处理！", cnt);
			AfxMessageBox(txt,MB_OK|MB_ICONEXCLAMATION);
		}
		rs.Close();
	}

}

void CBoxView::OnBtnBoxquery() 
{
	// TODO: Add your control notification handler code here
	CString boxid, filter;
	GetDlgItemText(IDC_EDT_BOXID, boxid);
	boxid.TrimLeft();
	boxid.TrimRight();
	if(boxid.GetLength()>0)
	{
		filter = " boxid like '%"+boxid+"%'";
	}
	else
	{
		filter = " 1 = 1 ";
	}

	CDlgFindList finder("box", filter, "boxid", "boxid", this);

	if(finder.DoModal() == IDCANCEL)
		return;

	m_pSet->m_strFilter = " boxid = '" + finder.m_sSelectedId +"'";

	m_pSet->Close();
	m_pSet->Open();
	if(!m_pSet->IsEOF())
	{
		m_pSet->MoveFirst();
		UpdateData(FALSE);
		OnKillfocusEdtBoxownerid();
	}
	if(m_pSet->IsEOF())
	{
		this->MessageBox("没有找到记录!");
	}
}

void CBoxView::OnBtnBoxadd() 
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
			m_pSet->m_boxid=CDbManger::GenerateNewID("BOXID");
		    UpdateData(false);
		    m_pSet->Update();
			CString boxid;
			GetDlgItemText(IDC_EDT_BOXID, boxid);
			CDbManger::RePrepareRecordset(m_pSet,"boxid", boxid);
			UpdateData(false);
	/*CODBCFieldInfo fi;
	for(int i=0;i<m_pSet->GetODBCFieldCount();i++)
	{
		m_pSet->GetODBCFieldInfo(i, fi);
		AfxMessageBox(fi.m_strName);
	}*/
		}
	}
}

BOOL CBoxView::CheckRequired()
{
	CString price;
	GetDlgItemText(IDC_EDT_BOXPRICE, price);
	price.TrimLeft();
	price.TrimRight();
	if(atof(price)<=0)
	{
		AfxMessageBox("租赁价格必需大于0!", MB_OK|MB_ICONERROR);
		return FALSE;
	}
	CString custid;
	GetDlgItemText(IDC_EDT_BOXOWNERID, custid);
	custid.TrimLeft();
	custid.TrimRight();
	CRecordset rs(&CDbManger::db);
	CString sql = "select 'x' from rent where renterid !='"+custid+"' and boxid ='"+m_pSet->m_boxid+"' and payed = 0";
    rs.Open(CRecordset::forwardOnly, sql);
	if(rs.IsOpen() && !rs.IsEOF())
	{
		AfxMessageBox("该格子存在未结算租赁，不能修改格主！");
		rs.Close();
		return false;
	}

	return TRUE;

}

void CBoxView::OnBtnBoxmodify() 
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
			CDbManger::db.BeginTrans();
		    m_pSet->Edit();
		    UpdateData();
	        m_pSet->Update();
			CDbManger::db.CommitTrans();
			CString boxid;
			GetDlgItemText(IDC_EDT_BOXID, boxid);
			CDbManger::RePrepareRecordset(m_pSet,"boxid", boxid);
			UpdateData(false);
		}
	}	
}

void CBoxView::OnBtnBoxdel() 
{
	// TODO: Add your control notification handler code here
	if(!m_pSet->IsOpen() || m_pSet->IsEOF())
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
		CRecordset rs(&CDbManger::db), *p;
		p = &rs;
		CString sql;
		sql.Format("select 'x' from storage where boxid = '%s'", m_pSet->m_boxid);
		rs.Open(CRecordset::forwardOnly, sql);
		if(!p->IsEOF())
		{
			p->Close();
			if(AfxMessageBox("格子中存放物品，是否自动清空？", MB_YESNO|MB_ICONINFORMATION) == IDYES)
			{
				sql.Format("delete from storage where boxid = '%s'", m_pSet->m_boxid);
				CDbManger::db.ExecuteSQL(sql);
			}
			else
			{
				AfxMessageBox("请清空物品后再删除格子！");
				return;
			}
		}
		else
			p->Close();
		sql.Format("select 'x' from rent where boxid = '%s' and payed = 0 ", m_pSet->m_boxid);
		rs.Open(CRecordset::forwardOnly, sql);
		if(!p->IsEOF())
		{
			p->Close();
			if(AfxMessageBox("格子存在未结算租赁，是否删除未结算租赁关系？", MB_YESNO|MB_ICONINFORMATION) == IDYES)
			{
				sql.Format("delete from rent where boxid = '%s' and payed = 0 ", m_pSet->m_boxid);
				CDbManger::db.ExecuteSQL(sql);
			}
			else
			{
				AfxMessageBox("请结算租赁后再删除！");
				return;
			}
		}
		else
			p->Close();		
	    m_pSet->Delete();
		OnBtnBoxclear();
		m_pSet->Close();
	}	
}

void CBoxView::OnBtnBoxclear() 
{
	// TODO: Add your control notification handler code here
ClearBoxInfo();
ClearRentInfo();
}

void CBoxView::OnBtnBoxlayout() 
{
	// TODO: Add your control notification handler code here
	CString boxid;
	GetDlgItemText(IDC_EDT_BOXID, boxid);
	boxid.TrimLeft();
	boxid.TrimRight();

	if(!boxid.GetLength())
	{
		AfxMessageBox("请输入格子编号再摆放！");
		return;
	}
	CDlgBoxLayout dlg(boxid);
	dlg.DoModal();
}

void CBoxView::OnBtnBoxQuery() 
{
	// TODO: Add your control notification handler code here
	// TODO: Add your control notification handler code here
    CBoxDoc *pDoc=GetDocument();
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

BOOL CBoxView::BuildSql(CQueryView * pQV)
{

	pQV->m_sQuerySql = "";
	pQV->m_sFootSql = "";
	pQV->m_sFootFilter="";
	pQV->m_sFilter = " where 1=1 ";
	CString boxfilter = " and 1=1 ";

	if(m_cCurBox.GetCheck())
	{
		CString boxid;
		GetDlgItemText(IDC_EDT_BOXID, boxid);
		boxid.TrimLeft();
		boxid.TrimRight();
		if(boxid.GetLength()<=0)
		{
			AfxMessageBox("请输入当前格子编号!", MB_OK|MB_ICONERROR);
			return FALSE;
		}
		else 
			boxfilter = " and b.boxid = '" + boxid+"'";
	}

	if(m_cIncludeRent.GetCheck())
	{
		pQV->m_sQuerySql =  "select r.boxid 格子编号, " 
			                "       r.rentname 格主姓名, r.seqnum 租赁序号, r.price 租赁价格, "
							"       r.totprice 租赁总价, r.payed 结算标志, "
							"       r.dtefrm 起始日期, "
							"       r.dteto 终止日期 "
							"  from rent r "
							"  left join box b "
							"    on b.ownerid = r.renterid ";

		pQV->m_sFilter = " where 1=1 "+ boxfilter + " order by r.rentname, r.boxid, r.seqnum asc ";
		pQV->m_sTitle = "格子租赁信息";
		pQV->m_sFootSql = "select "
			              "       sum(case payed when 1 then 1 else 0 end) 已结笔数, "
						  "       sum(case payed when 1 then r.totprice else 0 end) 已结算总额, "
						  "       sum(case payed when 1 then 0 else 1 end) 未结笔数, "
						  "       sum(case payed when 0 then r.totprice else 0 end) 未结算总额 "
						  "  from rent r ";
		pQV->m_sFootFilter = " where 1=1 "+ boxfilter;
	}
	else if(m_cIncludeRentExp.GetCheck())
	{
		pQV->m_sQuerySql =  "select r.boxid 格子编号, " 
			                "       r.rentname 格主姓名, r.seqnum 租赁序号, r.price 租赁价格, "
							"       r.totprice 租赁总价, r.payed 结算标志, "
							"       r.dtefrm 起始日期, "
							"       r.dteto 终止日期 "
							"  from rent r "
							"  left join box b "
							"    on b.ownerid = r.renterid "
							"   and b.boxid = r.boxid ";

		pQV->m_sFilter = " where payed =0  and dteto <= getdate() "+ boxfilter + " order by r.rentname, r.boxid, r.seqnum asc ";
		pQV->m_sTitle = "到期租赁信息";
		pQV->m_sFootSql = "select "
						  "       sum(case payed when 1 then 0 else 1 end) 未结笔数, "
						  "       sum(case payed when 0 then r.totprice else 0 end) 未结算总额 "
						  "  from rent r ";
		pQV->m_sFootFilter = " where payed =0  and dteto <= getdate() "+ boxfilter;
	}
	else if(m_cIncludeCustomer.GetCheck() && m_cIncludeItem.GetCheck())
	{
		pQV->m_sQuerySql =  "select b.boxid 格子编号, " 
			                "       c.name 格主姓名, b.rentprice 租赁价格, "
							"       s.itemid 物品编号,s.name 物品名称, s.qty 物品数量, s.price 物品价格 "
							"  from box b "
							"  left join customer c "
							"    on b.ownerid = c.customerid "
							"  left join storage s "
							"    on b.boxid = s.boxid ";

		pQV->m_sFilter = " where 1=1 "+ boxfilter;
		pQV->m_sTitle = "格子综合信息";
		pQV->m_sFootSql = "select "
			              " count(*) 格子总数"
						  "  from box b ";
		pQV->m_sFootFilter = " where 1 = 1 "+ boxfilter;

	}
	else if(m_cIncludeItem.GetCheck())
	{
		pQV->m_sQuerySql = "select b.boxid 格子编号, "
							"      s.itemid 物品编号,s.name 物品名称, s.qty 物品数量, s.price 物品价格 "
							"  from box b "
							"  left join storage s "
							"    on b.boxid = s.boxid ";

		pQV->m_sFilter = " where 1 = 1 "+ boxfilter;
		pQV->m_sTitle = "格子中物品信息";
		pQV->m_sFootSql = "select "
			              " count(*) 格子总数"
						  "  from box b ";
		pQV->m_sFootFilter = " where 1 = 1 "+ boxfilter;

	}
	else if(m_cIncludeCustomer.GetCheck())
	{
		pQV->m_sQuerySql =  "select b.boxid 格子编号, " 
			                "      c.name 格主姓名, b.rentprice 租赁价格 "
							"  from box b "
							"  left join customer c "
							"    on b.ownerid = c.customerid ";

		pQV->m_sFilter = " where 1 = 1 " + boxfilter;
		pQV->m_sTitle = "格子租赁信息";
		pQV->m_sFootSql = "select "
			              " count(*) 格子总数"
						  "  from box b ";
		pQV->m_sFootFilter = " where 1 = 1 "+ boxfilter;

	}
	else
	{
		pQV->m_sQuerySql = "select b.boxid 格子编号, " 
			                "      b.rentprice 租赁价格 "
							"  from box b";

		pQV->m_sFilter = " where 1 = 1 "+ boxfilter;
		pQV->m_sTitle = "格子基本信息";
		pQV->m_sFootSql = "select "
			              " count(*) 格子总数"
						  "  from box b ";
		pQV->m_sFootFilter = " where 1 = 1 "+ boxfilter;

	}
	
	return TRUE;

}

BOOL CBoxView::PreCreateWindow(CREATESTRUCT& cs) 
{
	// TODO: Add your specialized code here and/or call the base class
	
	return CRecordView::PreCreateWindow(cs);
}

void CBoxView::OnKillfocusEdtBoxownerid() 
{
	// TODO: Add your control notification handler code here
	CString renterid;
	GetDlgItemText(IDC_EDT_BOXOWNERID, renterid);
	renterid.TrimLeft();
	renterid.TrimRight();

	if(GetRentInformation(m_pSet->m_boxid, renterid, ""))
		return;
	CRecordset rs(&CDbManger::db);
	CString sql;
	sql = "select name from customer where customerid = '"+renterid+"'";
	rs.Open(CRecordset::forwardOnly, sql);
	if(rs.IsOpen() && !rs.IsEOF())
	{
		CString rentername;
		rs.GetFieldValue("name", rentername);
		rentername.TrimLeft();
		rentername.TrimRight();
		m_sRentName=rentername;
		//SetDlgItemText(IDC_EDT_BOXRENTNAME, );
	}
	else
	{
		AfxMessageBox("不存在该格主！");
		return;
	} 
	CString rentprice;
	
	GetDlgItemText(IDC_EDT_BOXPRICE, rentprice);
	m_dRentPrice = atoi(rentprice);
	//SetDlgItemText(IDC_EDT_BOXRENTPRICE, rentprice);
	m_dteRentFrom = CTime::GetCurrentTime();
	int detYear = (m_dteRentFrom.GetMonth()+3)/12;
	int Month = (m_dteRentFrom.GetMonth()+3)%12;
    m_dteRentTo = CTime(m_dteRentFrom.GetYear()+detYear,Month,m_dteRentFrom.GetDay(),m_dteRentFrom.GetHour(),m_dteRentFrom.GetMinute(),m_dteRentFrom.GetSecond());
	m_iRentSeqnum = 0;
	m_dTotPrice = m_dRentPrice * 3;
	
	//m_pSet->SetFieldDirty("ownerid");
	UpdateData(false);
	SetDlgItemText(IDC_EDT_BOXOWNERID,renterid);
}

void CBoxView::OnCloseupDtepkRentfrom(NMHDR* pNMHDR, LRESULT* pResult) 
{
	// TODO: Add your control notification handler code here
	//AfxMessageBox("aaa");
    CalCulateRentTotPrice(false);
	*pResult = 0;
}

void CBoxView::OnCloseupDtepkRentto(NMHDR* pNMHDR, LRESULT* pResult) 
{
	// TODO: Add your control notification handler code here
    CalCulateRentTotPrice(false);
	*pResult = 0;
}

BOOL CBoxView::CalCulateRentTotPrice(BOOL bCheckFlg)
{
	UpdateData();
	int YearDiff = m_dteRentTo.GetYear()-m_dteRentFrom.GetYear();
	int MonthDiff = m_dteRentTo.GetMonth()-m_dteRentFrom.GetMonth();
	int months = YearDiff*12 + MonthDiff;
	if(months > 0 && !bCheckFlg)
	{
		m_dTotPrice = months * m_dRentPrice;
		UpdateData(false);	
		return TRUE;
	}
	else if(months <= 0 && bCheckFlg)
	{
		AfxMessageBox("租用日期至少一个月!", MB_OK|MB_ICONERROR);
	    return FALSE;
	}
	return TRUE;
}

void CBoxView::OnBtnBoxrentadd() 
{
	// TODO: Add your control notification handler code here
	if(!CheckRentRequired())
		return;
	CString chksql;
	CRecordset rs(&CDbManger::db);

	chksql = "select 'x' from rent where payed = 0 and boxid ='"+m_pSet->m_boxid+"'";
	rs.Open(CRecordset::forwardOnly, chksql);

	if(rs.IsOpen() && !rs.IsEOF())
	{
		AfxMessageBox("该格子存在末结算租赁，不能添加新的租赁！");
		return;
	}
	OnBtnBoxmodify();
	if(!CalCulateRentTotPrice(true))
	{
		return;
	}
	CString sseqnum;
	int iseqnum;
	GetDlgItemText(IDC_EDT_BOXRENTSEQNUM, sseqnum);
	iseqnum = atoi(sseqnum) + 1;
	sseqnum.Format("%d", iseqnum);
	SetDlgItemText(IDC_EDT_BOXRENTSEQNUM, sseqnum);
	CButton *pPayed = (CButton*)GetDlgItem(IDC_CHK_RENTPAYED);
	pPayed->SetCheck(false);
	UpdateData();
	CString sql;
	//CTime::FormatGmt("YYYYMMDDHHMISS");
	sql.Format("insert into rent (boxid, renterid, seqnum, payed, rentname, \
		                          price, totprice, dtefrm, dteto, description) \
		        values ('%s', '%s', %d, %d, '%s', %.2f, %.2f, '%4d/%2d/%2d %2d:%2d:%2d', '%4d/%2d/%2d %2d:%2d:%2d', '%s')", \
				m_pSet->m_boxid, \
				m_pSet->m_ownerid, \
				m_iRentSeqnum, \
				m_bRentPayed, \
				m_sRentName, \
				m_dRentPrice,\
				m_dTotPrice, \
				m_dteRentFrom.GetYear(), \
				m_dteRentFrom.GetMonth(), \
				m_dteRentFrom.GetDay(), \
				m_dteRentFrom.GetHour(), \
				m_dteRentFrom.GetMinute(), \
				m_dteRentFrom.GetSecond(), \
				m_dteRentTo.GetYear(), \
				m_dteRentTo.GetMonth(), \
				m_dteRentTo.GetDay(), \
				m_dteRentTo.GetHour(), \
				m_dteRentTo.GetMinute(), \
				m_dteRentTo.GetSecond(), \
				m_sRentDescription);

	CDbManger::ExecuteSQL(sql);
}

BOOL CBoxView::GetRentInformation(CString boxid, CString renterid, CString seqnum)
{
	CRecordset rs(&CDbManger::db);
	CString seqclause;
	if(seqnum.GetLength()>0)
	{
	    seqclause = " and seqnum = "+seqnum;
	}
	else
		seqclause = " and 1 = 1 ";
	renterid.TrimLeft();
	renterid.TrimRight();
	CString sql = "select rentname, \
		                  price, \
						  totprice, \
						  seqnum, \
						  payed, \
						  dtefrm, \
						  dteto, \
						  description\
				    from rent \
					where boxid = '"+m_pSet->m_boxid+"' \
				   	  and renterid = '"+renterid+"'" + seqclause +\
					" order by seqnum desc";
     rs.Open(CRecordset::forwardOnly, sql);
	 if(rs.IsOpen() && ! rs.IsEOF())
	 {
		 CString name, price, totprice, seqnum, payed, description;
		 CDBVariant dvfrm, dvto;
		 rs.GetFieldValue("rentname", name);
		 rs.GetFieldValue("price", price);
		 rs.GetFieldValue("totprice", totprice);
		 rs.GetFieldValue("seqnum", seqnum);
		 rs.GetFieldValue("payed", payed);
		 rs.GetFieldValue("dtefrm", dvfrm);
		 rs.GetFieldValue("dteto", dvto);
		 rs.GetFieldValue("description", description);
		 m_sRentName = name;
		 m_dRentPrice = atof(price);
		 m_dTotPrice = atof(totprice);
		 m_iRentSeqnum = atoi(seqnum);
		 m_bRentPayed = atoi(payed);
		 m_dteRentFrom = CTime(dvfrm.m_pdate->year,\
			 dvfrm.m_pdate->month,\
			 dvfrm.m_pdate->day,\
			 dvfrm.m_pdate->hour,\
			 dvfrm.m_pdate->minute,\
			 dvfrm.m_pdate->second);
		 m_dteRentTo = CTime(dvto.m_pdate->year,\
			 dvto.m_pdate->month,\
			 dvto.m_pdate->day,\
			 dvto.m_pdate->hour,\
			 dvto.m_pdate->minute,\
			 dvto.m_pdate->second);
		 //m_pSet->m_ownerid = renterid;
		 //m_pSet->SetFieldDirty("ownerid");
		 UpdateData(false);
		 SetDlgItemText(IDC_EDT_BOXOWNERID,renterid);
		 return TRUE;
	 }
	 return FALSE;
}

void CBoxView::OnBtnBoxrentmodify() 
{
	// TODO: Add your control notification handler code here
	if(!CheckRentRequired())
		return;
	if(m_bRentPayed)
	{
		AfxMessageBox("不能修改已结算租赁！");
		return;
	}
	if(!CalCulateRentTotPrice(true))
	{
		return;
	}
	UpdateData();
	CString sql;
	//CTime::FormatGmt("YYYYMMDDHHMISS");
	sql.Format("update rent set \
                       payed = %d, \
					   rentname = '%s', \
		               price = %.2f , \
					   totprice = %.2f, \
					   dtefrm = '%4d/%2d/%2d %2d:%2d:%2d', \
					   dteto = '%4d/%2d/%2d %2d:%2d:%2d' , \
					   description = '%s' \
			     where boxid ='%s' \
				   and renterid = '%s' \
				   and seqnum = %d ", \
				m_bRentPayed, \
				m_sRentName, \
				m_dRentPrice,\
				m_dTotPrice, \
				m_dteRentFrom.GetYear(), \
				m_dteRentFrom.GetMonth(), \
				m_dteRentFrom.GetDay(), \
				m_dteRentFrom.GetHour(), \
				m_dteRentFrom.GetMinute(), \
				m_dteRentFrom.GetSecond(), \
				m_dteRentTo.GetYear(), \
				m_dteRentTo.GetMonth(), \
				m_dteRentTo.GetDay(), \
				m_dteRentTo.GetHour(), \
				m_dteRentTo.GetMinute(), \
				m_dteRentTo.GetSecond(), \
				m_sRentDescription,\
				m_pSet->m_boxid,\
				m_pSet->m_ownerid,\
				m_iRentSeqnum);

	CDbManger::ExecuteSQL(sql);	
}

void CBoxView::OnBtnBoxrentdel() 
{
	// TODO: Add your control notification handler code here
	if(m_bRentPayed)
	{
		if(AfxMessageBox("租赁已结算，确实删除？", MB_YESNO|MB_ICONINFORMATION)==IDNO)
		    return;
	}
	else
	{
		if(AfxMessageBox("租赁还未结算，确实删除？", MB_YESNO|MB_ICONINFORMATION)==IDNO)
		    return;
	}
	CRecordset rs(&CDbManger::db);
	CString seqnum;
	UpdateData();
	seqnum.Format("%d", m_iRentSeqnum);
	CString sql;
	sql.Format("select 'x' from rent where boxid ='%s' and renterid = '%s' and seqnum = %d",\
		m_pSet->m_boxid, \
		m_pSet->m_ownerid, \
		m_iRentSeqnum);
    rs.Open(CRecordset::forwardOnly, sql);
	if(!rs.IsOpen() || rs.IsEOF())
	{
		AfxMessageBox("该租赁关系还未建立！");
		return;
	}
	rs.Close();
	sql.Format("delete from rent where boxid ='%s' and renterid = '%s' and seqnum = %d",\
		m_pSet->m_boxid, \
		m_pSet->m_ownerid, \
		m_iRentSeqnum);

	CDbManger::ExecuteSQL(sql);
	ClearRentInfo();
}

void CBoxView::OnBtnBoxrentover() 
{
	// TODO: Add your control notification handler code here
	CRecordset rs(&CDbManger::db);
	CString sql;
	UpdateData(false);
	sql.Format("select payed from rent where boxid = '%s' "
		       "   and renterid = '%s' "
			   "   and seqnum = %d ",
			   m_pSet->m_boxid,
			   m_pSet->m_ownerid,
			   m_iRentSeqnum);

	rs.Open(CRecordset::forwardOnly, sql);
	if(!rs.IsOpen() || rs.IsEOF())
	{
		AfxMessageBox("该租赁关系还未建立！");
		return;
	}
	else if (rs.IsOpen())
	{
		CString payed;
		rs.GetFieldValue("payed", payed);
		if(atoi(payed) > 0)
		{
			AfxMessageBox("该租赁已经结算，不能再结算！");
			return;
		}
		rs.Close();
	}

	if(AfxMessageBox("确认结算并结束该笔租赁吗！", MB_YESNO|MB_ICONINFORMATION) == IDNO)
		return;
	
	CalCulateRentTotPrice(false);
	CString txt;
	txt.Format("应该支付金额：%.2f", m_dTotPrice);
	AfxMessageBox(txt);
	m_bRentPayed = true;

	UpdateData(false);
	sql.Format("update rent set \
                       payed = %d, \
					   totprice = %.2f \
			     where boxid ='%s' \
				   and renterid = '%s' \
				   and seqnum = %d ", \
				m_bRentPayed, \
				m_dTotPrice,\
				m_pSet->m_boxid,\
				m_pSet->m_ownerid,\
				m_iRentSeqnum);

	CDbManger::ExecuteSQL(sql);	
	GetDocument()->UpdateAllViews(this);
}

void CBoxView::OnChkBoxRent() 
{
	// TODO: Add your control notification handler code here
	m_cIncludeItem.SetCheck(false);
	m_cIncludeCustomer.SetCheck(false);
	m_cIncludeRentExp.SetCheck(false);
	m_cCurBox.SetCheck(false);
	UpdateData(false);
}

void CBoxView::OnBtnBoxrentquery() 
{
	// TODO: Add your control notification handler code here
	CString filter;
	filter = " boxid = '" + m_pSet->m_boxid + "' and renterid = '"+m_pSet->m_ownerid+"'";
	CDlgFindList finder("rent", filter, "seqnum", "boxid", this);

	if(finder.DoModal() == IDCANCEL)
		return;
    this->GetRentInformation(m_pSet->m_boxid, m_pSet->m_ownerid, finder.m_sSelectedValue);
	//m_pSet->m_strFilter = " boxid = '" + finder.m_sSelectedId +"'";	
}

void CBoxView::OnChkBoxRentexp() 
{
	// TODO: Add your control notification handler code here
	m_cIncludeItem.SetCheck(false);
	m_cIncludeRent.SetCheck(false);
	m_cIncludeCustomer.SetCheck(false);
	m_cCurBox.SetCheck(false);
	UpdateData(false);
}

void CBoxView::OnChkBoxCustomer() 
{
	// TODO: Add your control notification handler code here
	m_cIncludeRent.SetCheck(false);
	m_cIncludeRentExp.SetCheck(false);
	UpdateData(false);	
}

void CBoxView::OnChkBoxItem() 
{
	// TODO: Add your control notification handler code here
	m_cIncludeRent.SetCheck(false);
	m_cIncludeRentExp.SetCheck(false);
	UpdateData(false);	
}

BOOL CBoxView::CheckRentRequired()
{
	CString renter;
	GetDlgItemText(IDC_EDT_BOXRENTNAME, renter);
	renter.TrimLeft();
	renter.TrimRight();
	CString price;
	GetDlgItemText(IDC_EDT_BOXRENTPRICE, price);
	price.TrimLeft();
	price.TrimRight();
	if(!m_pSet->IsOpen() || m_pSet->m_boxid.GetLength()<=0)
	{
        AfxMessageBox("请先查询格子信息！");
		return FALSE;		
	}
	if(renter.GetLength()<=0)
	{
		AfxMessageBox("格主姓名必输！");
		return FALSE;
	}
	if(atof(price)<=0)
	{
		AfxMessageBox("租凭价格必需大于0！");
		return FALSE;
	}
	CString custid;
	GetDlgItemText(IDC_EDT_BOXOWNERID, custid);
	custid.TrimLeft();
	custid.TrimRight();
	CRecordset rs(&CDbManger::db);
	CString sql = "select 'x' from rent where renterid !='"+custid+"' and boxid ='"+m_pSet->m_boxid+"' and payed = 0";
    rs.Open(CRecordset::forwardOnly, sql);
	if(rs.IsOpen() && !rs.IsEOF())
	{
		AfxMessageBox("该格子存在未结算租赁，不能修改格主！");
		rs.Close();
		return false;
	}
	return TRUE;
}

void CBoxView::OnBtnBoxownerquery() 
{
	// TODO: Add your control notification handler code here
	CString filter;
	filter = "  1 = 1 ";
	CDlgFindList finder("customer", filter, "name", "customerid", this);

	if(finder.DoModal() == IDCANCEL)
		return;
	SetDlgItemText(IDC_EDT_BOXOWNERID, finder.m_sSelectedId);
	OnKillfocusEdtBoxownerid();
}

void CBoxView::ClearRentInfo()
{
	SetDlgItemText(IDC_EDT_BOXRENTNAME,"");
	SetDlgItemText(IDC_EDT_BOXRENTPRICE,"0.0");
	SetDlgItemText(IDC_EDT_BOXRENTTOTPRICE,"0.0");
	SetDlgItemText(IDC_EDT_BOXRENTSEQNUM,"0");
	SetDlgItemText(IDC_EDT_BOXRENTDESCRIPTION,"");
}

void CBoxView::ClearBoxInfo()
{
	m_pSet->Close();
	SetDlgItemText(IDC_EDT_BOXID,"");
	SetDlgItemText(IDC_EDT_BOXOWNERID,"");
	SetDlgItemText(IDC_EDT_BOXPRICE,"");
	SetDlgItemText(IDC_EDT_BOXDESCRIPTION,"");
}
