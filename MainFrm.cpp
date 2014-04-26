// MainFrm.cpp : implementation of the CMainFrame class
//

#include "stdafx.h"
#include "HRS.h"

#include "MainFrm.h"
#include "logindlg.h"
#include "navview.h"
#include "queryview.h"
#include "hrsdoc.h"
#include "hrsview.h"
#include "boxview.h"
#include "itemview.h"
#include "userview.h"
#include "saleview.h"
#include "childfrm.h"
#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CMainFrame

IMPLEMENT_DYNAMIC(CMainFrame, CMDIFrameWnd)

BEGIN_MESSAGE_MAP(CMainFrame, CMDIFrameWnd)
	//{{AFX_MSG_MAP(CMainFrame)
	ON_WM_CREATE()
	ON_COMMAND(ID_MENU_LOGIN, OnMenuLogin)
	ON_WM_SIZE()
	ON_WM_PAINT()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

static UINT indicators[] =
{
	ID_SEPARATOR,           // status line indicator
	ID_INDICATOR_USER,
	ID_INDICATOR_ISADMIN,
	ID_INDICATOR_DATE,
};

/////////////////////////////////////////////////////////////////////////////
// CMainFrame construction/destruction

CMainFrame::CMainFrame()
{
	// TODO: add member initialization code here
	m_bLogin_flg=FALSE;
	m_pwChildFrm = NULL;
	m_pNavClient = new CNavView;

}

CMainFrame::~CMainFrame()
{
}

int CMainFrame::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CMDIFrameWnd::OnCreate(lpCreateStruct) == -1)
		return -1;
	
	/*if (!m_wndToolBar.CreateEx(this, TBSTYLE_FLAT, WS_CHILD | WS_VISIBLE | CBRS_TOP
		| CBRS_GRIPPER | CBRS_TOOLTIPS | CBRS_FLYBY | CBRS_SIZE_DYNAMIC) ||
		!m_wndToolBar.LoadToolBar(IDR_MAINFRAME))
	{
		TRACE0("Failed to create toolbar\n");
		return -1;      // fail to create
	}*/

	if (!m_wndStatusBar.Create(this) ||
		!m_wndStatusBar.SetIndicators(indicators,
		  sizeof(indicators)/sizeof(UINT)))
	{
		TRACE0("Failed to create status bar\n");
		return -1;      // fail to create
	}
	m_wndStatusBar.SetPaneInfo(0,ID_SEPARATOR,SBPS_POPOUT|SBPS_STRETCH,200);
	m_wndStatusBar.SetPaneInfo(1,ID_INDICATOR_USER,SBPS_POPOUT,150);
	m_wndStatusBar.SetPaneInfo(2,ID_INDICATOR_ISADMIN,SBPS_POPOUT,150);
	m_wndStatusBar.SetPaneInfo(3,ID_INDICATOR_DATE,SBPS_POPOUT,150);

	CTime lt = CTime::GetCurrentTime();
	CString txt ;
	txt.Format("日期: %d年%d月%d日",lt.GetYear(),lt.GetMonth(),lt.GetDay());
	m_wndStatusBar.SetPaneText(3,txt);


	// TODO: Delete these three lines if you don't want the toolbar to
	//  be dockable
//	m_wndToolBar.EnableDocking(CBRS_ALIGN_ANY);
	EnableDocking(CBRS_ALIGN_ANY);
//	DockControlBar(&m_wndToolBar);

	return 0;
}

BOOL CMainFrame::PreCreateWindow(CREATESTRUCT& cs)
{
	if( !CMDIFrameWnd::PreCreateWindow(cs) )
		return FALSE;
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs

	return TRUE;
}

/////////////////////////////////////////////////////////////////////////////
// CMainFrame diagnostics

#ifdef _DEBUG
void CMainFrame::AssertValid() const
{
	CMDIFrameWnd::AssertValid();
}

void CMainFrame::Dump(CDumpContext& dc) const
{
	CMDIFrameWnd::Dump(dc);
}

#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CMainFrame message handlers


void CMainFrame::OnMenuLogin() 
{
	// TODO: Add your command handler code here
	CLoginDlg dlg;
	while(dlg.DoModal() == IDOK && dlg.m_bSuccess == FALSE);	
}


BOOL CMainFrame::OnCreateClient(LPCREATESTRUCT lpcs, CCreateContext* pContext) 
{
	// TODO: Add your specialized code here and/or call the base class

	CMDIFrameWnd::OnCreateClient(lpcs, pContext);
	CWnd *pClient = CWnd::FromHandle(m_hWndMDIClient);
	//CButton *btn = new CButton;
	//btn->Create("Click Me",WS_CHILD,CRect(0,0,100,100), pClient, IDC_BTN_NAV_CUSTOMER);
	//btn->ShowWindow(SW_SHOW);
	//CNavView *pV = new CNavView;
	//::ShowWindow(m_hWndMDIClient, SW_HIDE);
	//pV->SubclassWindow(m_hWndMDIClient);
	CRect rc;
	GetClientRect(&rc);
	m_pNavClient->Create(NULL,NULL,WS_CHILD|WS_CLIPCHILDREN,rc,pClient,AFX_WS_DEFAULT_VIEW,pContext);
	
	m_pNavClient->ShowWindow(SW_HIDE);
	//m_hWndMDIClient = m_pNavClient->m_hWnd;
	//m_pNavClient->SubclassWindow(m_hWndMDIClient);

	return TRUE;
}

BOOL CMainFrame::Create(LPCTSTR lpszClassName, LPCTSTR lpszWindowName, DWORD dwStyle, const RECT& rect, CWnd* pParentWnd, UINT nID, CCreateContext* pContext) 
{
	// TODO: Add your specialized code here and/or call the base class
	
	return CWnd::Create(lpszClassName, lpszWindowName, dwStyle, rect, pParentWnd, nID, pContext);
}


void CMainFrame::OnSize(UINT nType, int cx, int cy) 
{
	CMDIFrameWnd::OnSize(nType, cx, cy);
	CRect rc;
	GetClientRect(&rc);
	m_pNavClient->MoveWindow(&rc,true);
	//m_pNavClient->SendMessage(WM_PAINT);
	
	// TODO: Add your message handler code here
}

void CMainFrame::OnPaint() 
{
	CPaintDC dc(this); // device context for painting

	// TODO: Add your message handler code here

	// Do not call CMDIFrameWnd::OnPaint() for painting messages
}
