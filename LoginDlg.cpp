// LoginDlg.cpp : implementation file
//

#include "stdafx.h"
#include "HRS.h"
#include "LoginDlg.h"
#include "mainfrm.h"
#include "dbmanger.h"
#include "userdoc.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CLoginDlg dialog

CLoginDlg::CLoginDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CLoginDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CLoginDlg)
	m_sLoginName = _T("");
	m_sLoginPassword = _T("");
	//}}AFX_DATA_INIT
	m_bSuccess = FALSE;
}


void CLoginDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CLoginDlg)
	DDX_Text(pDX, IDC_EDT_LOGIN_NAME, m_sLoginName);
	DDX_Text(pDX, IDC_EDT_LOGIN_PASSWORD, m_sLoginPassword);
	DDV_MaxChars(pDX, m_sLoginPassword, 6);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CLoginDlg, CDialog)
	//{{AFX_MSG_MAP(CLoginDlg)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CLoginDlg message handlers

void CLoginDlg::OnOK() 
{
	// TODO: Add extra validation here

	if(CDbManger::db.IsOpen())
			{
				CRecordset rs (&CDbManger::db);

				UpdateData();
				CString pwd;
				pwd=CUserDoc::EncodePassword(m_sLoginPassword);
				//AfxMessageBox("pwd is" +pwd);
				CString strCmd = "select isadmin,name from shopowner where userid = '"+m_sLoginName+"' and password = '" +pwd+"'";

				//::AfxMessageBox(strCmd);

				rs.Open(CRecordset::forwardOnly, strCmd);
                CHRSApp * p = (CHRSApp*)::AfxGetApp();
				CMainFrame *pm = (CMainFrame*)p->GetMainWnd();
				if(!rs.IsEOF())
				{
					CString isadmin;
					rs.GetFieldValue("isadmin", isadmin);
					isadmin.TrimLeft();
					isadmin.TrimRight();
					if(isadmin == "1")
					{
						pm->m_cLoginUser.m_bAdmin_flg = true;
						
					}
					else
					{
						pm->m_cLoginUser.m_bAdmin_flg = false;
					}

					pm->m_bLogin_flg = TRUE;
					m_bSuccess = TRUE;
					this->ShowWindow(FALSE);
					::AfxMessageBox("登录成功，欢迎使用系统！");
					
					pm->m_pNavClient->ShowWindow(SW_SHOW);
					CString txt,name;
					rs.GetFieldValue("name", name);
					name.TrimLeft();
					name.TrimRight();
					pm->m_cLoginUser.m_sUserName = name;
					txt.Format("用户: %s",name);
					pm->m_wndStatusBar.SetPaneText(1,txt, TRUE);
					txt.Format("管理员: %s", pm->m_cLoginUser.m_bAdmin_flg? "是":"否");
                    pm->m_wndStatusBar.SetPaneText(2,txt, TRUE);
					rs.Close();
				}
				else
				{
					this->ShowWindow(FALSE);
					::AfxMessageBox("登录失败，请确认用户名密码正确！");
					pm->m_bLogin_flg = FALSE;
					m_bSuccess = FALSE;
				}
				
			}
	
	CDialog::OnOK();
}

BOOL CLoginDlg::OnInitDialog()
{
	CDialog::OnInitDialog();
	
	// TODO: Add extra initialization here
	HICON h=::AfxGetApp()->LoadIcon(IDI_ICN_OK);
	((CBitmapButton*)GetDlgItem(IDOK))->SetIcon(h);
	h=::AfxGetApp()->LoadIcon(IDI_ICN_CANCEL);
	((CBitmapButton*)GetDlgItem(IDCANCEL))->SetIcon(h);
	
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CLoginDlg::OnCancel() 
{
	// TODO: Add extra cleanup here
	//AfxGetApp()->PostThreadMessage(WM_QUIT,0,0);
	CDialog::OnCancel();
}
