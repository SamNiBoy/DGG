// UserView.cpp : implementation file
//

#include "stdafx.h"
#include "hrs.h"
#include "UserView.h"
#include "DlgFindList.h"
#include "UserDoc.h"
#include "MainFrm.h"
#include "queryview.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CUserView

IMPLEMENT_DYNCREATE(CUserView, CRecordView)

CUserView::CUserView()
	: CRecordView(CUserView::IDD)
{
	//{{AFX_DATA_INIT(CUserView)
	m_pSet = NULL;
	//}}AFX_DATA_INIT
}

CUserView::~CUserView()
{
	if (m_pSet)
		delete m_pSet;
}

void CUserView::DoDataExchange(CDataExchange* pDX)
{
	CRecordView::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CUserView)
	DDX_Text(pDX, IDC_EDT_USERID, m_pSet->m_userid);
	DDX_Text(pDX, IDC_EDT_USERNAME, m_pSet->m_name);
	DDX_Text(pDX, IDC_EDT_USERPWD, m_pSet->m_password);
	DDV_MaxChars(pDX, m_pSet->m_password, 6);
	DDX_Text(pDX, IDC_EDT_USERSEX, m_pSet->m_sex);
	DDX_Text(pDX, IDC_EDT_USERAGE, m_pSet->m_age);
	DDX_Text(pDX, IDC_EDT_USERTEL, m_pSet->m_tel);
	DDX_Text(pDX, IDC_EDT_USEREMAIL, m_pSet->m_email);
	DDX_Text(pDX, IDC_EDT_USERADDRESS, m_pSet->m_address);
	//}}AFX_DATA_MAP
	CButton *pChkBx=(CButton*)GetDlgItem(IDC_CHK_ISADMIN);
	if(pDX->m_bSaveAndValidate)
	{
		m_pSet->m_isadmin = pChkBx->GetCheck();
		CString pwd;
		GetDlgItemText(IDC_EDT_USERPWD, pwd);
		pwd.TrimRight();
		pwd.TrimLeft();
		m_pSet->m_password = ((CUserDoc*)GetDocument())->EncodePassword(pwd);
	}
	else
	{
		pChkBx->SetCheck(m_pSet->m_isadmin);
		SetDlgItemText(IDC_EDT_USERPWD, ((CUserDoc*)GetDocument())->DecodePassword(m_pSet->m_password));
	}
}


BEGIN_MESSAGE_MAP(CUserView, CRecordView)
	//{{AFX_MSG_MAP(CUserView)
	ON_BN_CLICKED(IDC_BTN_USERQUERY, OnBtnUserquery)
	ON_BN_CLICKED(IDC_BTN_USERCLEAR, OnBtnUserclear)
	ON_BN_CLICKED(IDC_BTN_USERADD, OnBtnUseradd)
	ON_BN_CLICKED(IDC_BTN_USERMODIFY, OnBtnUsermodify)
	ON_BN_CLICKED(IDC_BTN_USERDEL, OnBtnUserdel)
	ON_BN_CLICKED(IDC_BTN_QUERYUSER, OnBtnQueryuser)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CUserView diagnostics

#ifdef _DEBUG
void CUserView::AssertValid() const
{
	CRecordView::AssertValid();
}

void CUserView::Dump(CDumpContext& dc) const
{
	CRecordView::Dump(dc);
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CUserView message handlers

CRecordset* CUserView::OnGetRecordset()
{
	if (m_pSet != NULL)
		return m_pSet;

	m_pSet = new CUserSet(NULL);
	m_pSet->Open();

	return m_pSet;
}

CUserSet* CUserView::GetRecordset()
{
	CUserSet* pData = (CUserSet*) OnGetRecordset();
	ASSERT(pData == NULL || pData->IsKindOf(RUNTIME_CLASS(CUserSet)));
	return pData;
}

void CUserView::OnInitialUpdate()
{
	BeginWaitCursor();
	GetRecordset();
	CSize s(1000,1000);
	this->SetScrollSizes(MM_TEXT,s);
	CRecordView::OnInitialUpdate();
	CHRSApp *pApp=(CHRSApp*)::AfxGetApp();
	CMainFrame *pMF = (CMainFrame*)pApp->GetMainWnd();
	if(!pMF->m_cLoginUser.m_bAdmin_flg)
	{
		CButton *pBtn = (CButton*)GetDlgItem(IDC_BTN_USERADD);
		pBtn->EnableWindow(false);
		pBtn = (CButton*)GetDlgItem(IDC_BTN_USERMODIFY);
		pBtn->EnableWindow(false);
		pBtn = (CButton*)GetDlgItem(IDC_BTN_USERDEL);
		pBtn->EnableWindow(false);
	}
	EndWaitCursor();
}

void CUserView::OnBtnUserquery() 
{
	// TODO: Add your control notification handler code here
	CString userid,filter;
	GetDlgItemText(IDC_EDT_USERID, userid);
	userid.TrimLeft();
	userid.TrimRight();
	if(userid.GetLength()>0)
	{
		filter = " userid like '%"+userid+"%'";
	}
	else
	{
		filter = " 1 = 1 ";
	}

	CDlgFindList finder("shopowner", filter, "name", "userid", this);

	if(finder.DoModal() == IDCANCEL)
		return;

	m_pSet->m_strFilter = " userid = '" + finder.m_sSelectedId +"'";

	m_pSet->Close();
	m_pSet->Open();
	UpdateData(false);
}

void CUserView::OnBtnUserclear() 
{
	// TODO: Add your control notification handler code here
	if(m_pSet->IsOpen())
	    m_pSet->Close();
	SetDlgItemText(IDC_EDT_USERID,"");
	SetDlgItemText(IDC_EDT_USERNAME,"");
	SetDlgItemText(IDC_EDT_USERPWD,"");
	SetDlgItemText(IDC_EDT_USERSEX,"");
	SetDlgItemText(IDC_EDT_USERAGE,"");
	SetDlgItemText(IDC_EDT_USERTEL,"");
	SetDlgItemText(IDC_EDT_USEREMAIL, "");
	SetDlgItemText(IDC_EDT_USERADDRESS, "");
	CButton *pChkBx=(CButton*)GetDlgItem(IDC_CHK_ISADMIN);
	pChkBx->SetCheck(false);
}

void CUserView::OnBtnUseradd() 
{
	// TODO: Add your control notification handler code here
	CString userid;
	CRecordset rs(&CDbManger::db), *p=&rs;

	GetDlgItemText(IDC_EDT_USERID, userid);
	userid.TrimLeft();
	userid.TrimRight();

	CString strCmd;
	strCmd = "select 'x' from shopowner where userid = '"+userid+"'";
	rs.Open(CRecordset::forwardOnly, strCmd);

	if(!p->IsEOF())
	{
		AfxMessageBox("该用户已经存在，不能添加！");
		p->Close();
		CEdit *pEdtUsrId= (CEdit*)GetDlgItem(IDC_EDT_USERID);
		pEdtUsrId->SetFocus();
		pEdtUsrId->SetSel(50);
		return;
	}
	p->Close();

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
		    m_pSet->Update();
			CString userid;
			GetDlgItemText(IDC_EDT_USERID, userid);
			CDbManger::RePrepareRecordset(m_pSet, "userid", userid);
			UpdateData(false);
		}
	}
}

BOOL CUserView::CheckRequired()
{
	CString userid, name, password, sex, age;
	GetDlgItemText(IDC_EDT_USERID, userid);
	GetDlgItemText(IDC_EDT_USERNAME, name);
	GetDlgItemText(IDC_EDT_USERPWD, password);
	GetDlgItemText(IDC_EDT_USERSEX, sex);
	GetDlgItemText(IDC_EDT_USERAGE, age);

	userid.TrimLeft();
	userid.TrimRight();

	name.TrimLeft();
	name.TrimRight();

	password.TrimLeft();
	password.TrimRight();

	sex.TrimLeft();
	sex.TrimRight();
	age.TrimLeft();
	age.TrimRight();
	if(!userid.GetLength())
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
	}
	return TRUE;
}

void CUserView::OnBtnUsermodify() 
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
	        CRecordset rs(&CDbManger::db), *p=&rs;
	        CString sql = "select userid from shopowner where isadmin = 1";

	        rs.Open(CRecordset::forwardOnly, sql);

        	if(!p->IsEOF())
			{
	        	CString leftuserid;
     	    	p->GetFieldValue("userid", leftuserid);
	    	    leftuserid.TrimLeft();
	    	    leftuserid.TrimRight();
				CButton *pChkAdm = (CButton*)GetDlgItem(IDC_CHK_ISADMIN);
	    	    if(p->GetRecordCount() == 1 && leftuserid == m_pSet->m_userid && !pChkAdm->GetCheck())
				{
	    		    AfxMessageBox("修改失败，至少有一个管理员帐户！");
				    p->Close();
		    	    return;
				}
			    p->Close();
			}
		    else
			    p->Close();
		    m_pSet->Edit();
		    UpdateData();
	        m_pSet->Update();
			CString userid;
			GetDlgItemText(IDC_EDT_USERID, userid);
			CDbManger::RePrepareRecordset(m_pSet, "userid", userid);
			UpdateData(false);
		}
	}	
}

void CUserView::OnBtnUserdel() 
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
	    CRecordset rs(&CDbManger::db), *p=&rs;
	    CString sql = "select userid from shopowner where isadmin = 1";

	    rs.Open(CRecordset::forwardOnly, sql);

    	if(!p->IsEOF())
		{
	    	CString leftuserid;
	    	p->GetFieldValue("userid", leftuserid);
	    	leftuserid.TrimLeft();
	    	leftuserid.TrimRight();
	    	if(p->GetRecordCount() == 1 && leftuserid == m_pSet->m_userid)
			{
	    		AfxMessageBox("删除失败，至少有一个管理员帐户！");
				p->Close();
		    	return;
			}
			p->Close();
		}
		else
			p->Close();

	    m_pSet->Delete();
		OnBtnUserclear();
		m_pSet->Close();
	}	
}

void CUserView::OnBtnQueryuser() 
{
	// TODO: Add your control notification handler code here
    CUserDoc *pDoc=(CUserDoc *)GetDocument();
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
	if(pQueryAdmin->GetCheck())
	{
		pQV->m_sFilter = " where u.isadmin = 1 ";
	}
	else 
		pQV->m_sFilter = " where 1 = 1 order by isadmin desc ";



	pQV->m_sQuerySql = "select u.userid 登录号码, "
		               "        u.name 用户姓名, "
					   "        u.sex  用户性别, "
					   "        u.age  用户年龄, "
					   "        case u.isadmin when 1 then '是' else '否' end 管理员, "
					   "        u.tel 电话, "
					   "        u.email 邮件 "
					   "  from shopowner u ";

	TRACE("sql: %s \n where: %s\n", pQV->m_sQuerySql, pQV->m_sFilter);
	pQV->QueryRecordset();
	pDoc->UpdateAllViews(this);		
}
