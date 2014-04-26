// MoneyView.cpp : implementation file
//

#include "stdafx.h"
#include "hrs.h"
#include "moneyView.h"
#include "DlgFindList.h"
#include "moneyDoc.h"
#include "MainFrm.h"
#include "queryview.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CMoneyView

IMPLEMENT_DYNCREATE(CMoneyView, CRecordView)

CMoneyView::CMoneyView()
	: CRecordView(CMoneyView::IDD)
{
	//{{AFX_DATA_INIT(CMoneyView)
	m_pSet = NULL;
	//}}AFX_DATA_INIT
	m_CostBegDte = CTime::GetCurrentTime();
	m_CostEndDte = CTime::GetCurrentTime();

}

CMoneyView::~CMoneyView()
{
	if (m_pSet)
		delete m_pSet;
}

void CMoneyView::DoDataExchange(CDataExchange* pDX)
{
	CRecordView::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CMoneyView)
	DDX_Control(pDX, IDC_CMB_MONEY_QUERYCLASS, m_cmbQueryClass);
	DDX_Control(pDX, IDC_CMB_MONEY_CLASS, m_cmbClass);
	DDX_Text(pDX, IDC_EDT_MONEY_QTY, m_pSet->m_qty);
	DDX_Text(pDX, IDC_EDT_MONEY_COSTER, m_pSet->m_coster);
	DDX_Text(pDX, IDC_EDT_MONEY_DESC, m_pSet->m_description);
    DDX_Text(pDX, IDC_EDT_MONEY_COSTID, m_pSet->m_costid);
	DDX_DateTimeCtrl(pDX, IDC_DTEPK_MONEY_COSTDATE, m_pSet->m_date);
	DDX_DateTimeCtrl(pDX, IDC_DTEPK_MONEY_COSTBEGDATE, m_CostBegDte);
	DDX_DateTimeCtrl(pDX, IDC_DTEPK_MONEY_COSTENDDATE, m_CostEndDte);
	//}}AFX_DATA_MAP
	if(pDX->m_bSaveAndValidate)
	{
		int idx = m_cmbClass.GetCurSel();
		if(idx>=0)
		    m_cmbClass.GetLBText(idx, m_pSet->m_class);
		//AfxMessageBox("after");
	}
	else
	{
		CString tt = m_pSet->m_class, txt;
		int cnt = m_cmbClass.GetCount();
		for (int i=0 ; i< cnt && tt.GetLength() > 0; i++)
		{
			m_cmbClass.GetLBText(i, txt);
			if(tt == txt)
				m_cmbClass.SetCurSel(i);
		}
	}
}


BEGIN_MESSAGE_MAP(CMoneyView, CRecordView)
	//{{AFX_MSG_MAP(CMoneyView)
	ON_BN_CLICKED(IDC_BTN_MONEYQUERY, OnBtnMoneyquery)
	ON_BN_CLICKED(IDC_BTN_MONEYCLEAR, OnBtnMoneyclear)
	ON_BN_CLICKED(IDC_BTN_MONEYADD, OnBtnMoneyadd)
	ON_BN_CLICKED(IDC_BTN_MONEYMODIFY, OnBtnMoneymodify)
	ON_BN_CLICKED(IDC_BTN_MONEYDEL, OnBtnMoneydel)
	ON_BN_CLICKED(IDC_BTN_MONEY_INFOQUERY, OnBtnMoneyInfoquery)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CMoneyView diagnostics

#ifdef _DEBUG
void CMoneyView::AssertValid() const
{
	CRecordView::AssertValid();
}

void CMoneyView::Dump(CDumpContext& dc) const
{
	CRecordView::Dump(dc);
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CMoneyView message handlers

CRecordset* CMoneyView::OnGetRecordset()
{
	if (m_pSet != NULL)
		return m_pSet;

	m_pSet = new CMoneySet(NULL);
	m_pSet->Open();

	return m_pSet;
}

CMoneySet* CMoneyView::GetRecordset()
{
	CMoneySet* pData = (CMoneySet*) OnGetRecordset();
	ASSERT(pData == NULL || pData->IsKindOf(RUNTIME_CLASS(CMoneySet)));
	return pData;
}

void CMoneyView::OnInitialUpdate()
{
	CSize s(1000,1000);
	this->SetScrollSizes(MM_TEXT,s);

	CRecordView::OnInitialUpdate();
	m_pSet->m_date = CTime::GetCurrentTime();
	CMainFrame *pMain = (CMainFrame*) AfxGetApp()->GetMainWnd();
	m_pSet->m_coster = pMain->m_cLoginUser.m_sUserName;
	
	UpdateData(false);
}

void CMoneyView::OnBtnMoneyquery() 
{
	// TODO: Add your control notification handler code here
	CString costid,filter;
	GetDlgItemText(IDC_EDT_MONEY_COSTID, costid);
	costid.TrimLeft();
	costid.TrimRight();
	if(costid.GetLength()>0)
	{
		filter = " costid like '%"+costid+"%'";
	}
	else
	{
		filter = " 1 = 1 ";
	}

	CDlgFindList finder("cost", filter, "costid", "costid", this);

	if(finder.DoModal() == IDCANCEL)
		return;

	m_pSet->m_strFilter = " costid = '" + finder.m_sSelectedId +"'";

	m_pSet->Close();
	m_pSet->Open();
	UpdateData(false);
}

void CMoneyView::OnBtnMoneyclear() 
{
	// TODO: Add your control notification handler code here
	if(m_pSet->IsOpen())
	    m_pSet->Close();
	SetDlgItemText(IDC_EDT_MONEY_COSTID,"");
	m_cmbClass.SetCurSel(0);
	SetDlgItemText(IDC_EDT_MONEY_QTY,"0");
	SetDlgItemText(IDC_EDT_MONEY_DESC,"");
}

void CMoneyView::OnBtnMoneyadd() 
{
	// TODO: Add your control notification handler code here
	CString Moneyid;

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
			m_pSet->m_costid=CDbManger::GenerateNewID("COSTID");
			UpdateData(false);
		    m_pSet->Update();
			CString Costid;
			GetDlgItemText(IDC_EDT_MONEY_COSTID, Costid);
			CDbManger::RePrepareRecordset(m_pSet, "costid", Costid);
			UpdateData(false);
		}
	}
}

BOOL CMoneyView::CheckRequired()
{
	/*CString Moneyid, name, password, sex, age;
	GetDlgItemText(IDC_EDT_MoneyID, Moneyid);
	GetDlgItemText(IDC_EDT_MoneyNAME, name);
	GetDlgItemText(IDC_EDT_MoneyPWD, password);
	GetDlgItemText(IDC_EDT_MoneySEX, sex);
	GetDlgItemText(IDC_EDT_MoneyAGE, age);

	Moneyid.TrimLeft();
	Moneyid.TrimRight();

	name.TrimLeft();
	name.TrimRight();

	password.TrimLeft();
	password.TrimRight();

	sex.TrimLeft();
	sex.TrimRight();
	age.TrimLeft();
	age.TrimRight();
	if(!Moneyid.GetLength())
	{
		AfxMessageBox("请输入用户ID!", MB_OK|MB_ICONERROR);
		return FALSE;
	}
	if(!name.GetLength())
	{
		AfxMessageBox("请输入用户姓名!", MB_OK|MB_ICONERROR);
		return FALSE;
	}
	if(!password.GetLength())
	{
		AfxMessageBox("请输入用户密码!", MB_OK|MB_ICONERROR);
		return FALSE;
	}
	if(!sex.GetLength())
	{
		AfxMessageBox("请输入性别!", MB_OK|MB_ICONERROR);
		return FALSE;
	}
	if(!age.GetLength())
	{
		AfxMessageBox("请输入年龄!", MB_OK|MB_ICONERROR);
		return FALSE;
	}*/
	return TRUE;
}

void CMoneyView::OnBtnMoneymodify() 
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
			CString costid;
			GetDlgItemText(IDC_EDT_MONEY_COSTID, costid);
			CDbManger::RePrepareRecordset(m_pSet, "costid", costid);
			UpdateData(false);
		}
	}
}

void CMoneyView::OnBtnMoneydel() 
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
		OnBtnMoneyclear();
		m_pSet->Close();
	}
}

void CMoneyView::OnBtnMoneyInfoquery() 
{
	// TODO: Add your control notification handler code here
    CMoneyDoc *pDoc=(CMoneyDoc*)GetDocument();
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

BOOL CMoneyView::BuildSql(CQueryView * pQV)
{
	pQV->m_sQuerySql = "";
	pQV->m_sFilter = " where 1=1 ";
	//UpdateData();

    int idx = m_cmbQueryClass.GetCurSel();
	CString costcls;
	if(idx>=0)
	    m_cmbQueryClass.GetLBText(idx, costcls);
	else
	{
		idx = 0;
	}

	UpdateData();
	CString dterange;
	dterange.Format(" and (date between '%4d-%2d-%2d %2d:%2d:%2d' and '%4d-%2d-%2d %2d:%2d:%2d')",
		m_CostBegDte.GetYear(),
		m_CostBegDte.GetMonth(),
		m_CostBegDte.GetDay(),
		0,0,0,
		m_CostEndDte.GetYear(),
		m_CostEndDte.GetMonth(),
		m_CostEndDte.GetDay()+1,
		0,0,0);

	CString clsclause;
	if(idx == 0)
		clsclause = " 1 = 1 ";
	else
		clsclause = " c.class = '"+costcls+"' ";


		pQV->m_sQuerySql =  "select c.costid 支出编号, " 
			                "       c.class 类别, "
			                "       c.coster 经办人, "
							"       c.qty 支出金额, "
							"       c.date 日期, "
							"       c.description 备注 "
							"  from cost c ";

		pQV->m_sFilter = " where " +clsclause+dterange+" order by c.date desc ";
		pQV->m_sTitle = "支出信息";
		pQV->m_sFootSql = "select sum(c.qty) 总额 from cost c ";
		pQV->m_sFootFilter = " where " +clsclause+dterange;
	return TRUE;
}
