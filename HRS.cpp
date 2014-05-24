// HRS.cpp : Defines the class behaviors for the application.
//

#include "stdafx.h"
#include "HRS.h"

#include "MainFrm.h"
#include "ChildFrm.h"
#include "HRSSet.h"
#include "HRSDoc.h"
#include "HRSView.h"

#include "boxdoc.h"
#include "boxView.h"

#include "itemdoc.h"
#include "itemView.h"

#include "saledoc.h"
#include "saleView.h"

#include "userdoc.h"
#include "userView.h"

#include "moneyDoc.h"
#include "moneyView.h"
#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CHRSApp

BEGIN_MESSAGE_MAP(CHRSApp, CWinApp)
	//{{AFX_MSG_MAP(CHRSApp)
	ON_COMMAND(ID_APP_ABOUT, OnAppAbout)
	//}}AFX_MSG_MAP
	// Standard file based document commands
	ON_COMMAND(ID_FILE_NEW, CWinApp::OnFileNew)
	ON_COMMAND(ID_FILE_OPEN, CWinApp::OnFileOpen)
	// Standard print setup command
	ON_COMMAND(ID_FILE_PRINT_SETUP, CWinApp::OnFilePrintSetup)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CHRSApp construction

CHRSApp::CHRSApp()
{
	// TODO: add construction code here,
	// Place all significant initialization in InitInstance
}

/////////////////////////////////////////////////////////////////////////////
// The one and only CHRSApp object

CHRSApp theApp;

/////////////////////////////////////////////////////////////////////////////
// CHRSApp initialization

BOOL CHRSApp::InitInstance()
{
	// Standard initialization
	// If you are not using these features and wish to reduce the size
	//  of your final executable, youbb should remove from the following
	//  the specific initialization routines you do not need.
    //m_BTHand = AfxGetApp()->LoadCursor(IDC_CURSOR_HAND);

#ifdef _AFXDLL
	Enable3dControls();			// Call this when using MFC in a shared DLL
#else
	Enable3dControlsStatic();	// Call this when linking to MFC statically
#endif

	// Change the registry key under which our settings are stored.
	// TODO: You should modify this string to be something appropriate
	// such as the name of your company or organization.
	SetRegistryKey(_T("Local AppWizard-Generated Applications"));

	LoadStdProfileSettings();  // Load standard INI file options (including MRU)

	// Register the application's document templates.  Document templates
	//  serve as the connection between documents, frame windows and views.

	CMultiDocTemplate* pDocTemplate;
	pDocTemplate = new CMultiDocTemplate(
		IDR_CUSTOMERTYPE,
		RUNTIME_CLASS(CCUSTOMERDoc),
		RUNTIME_CLASS(CChildFrame), // custom MDI child frame
		RUNTIME_CLASS(CCUSTOMERView));
	AddDocTemplate(pDocTemplate);

	pDocTemplate = new CMultiDocTemplate(
		IDR_BOXTYPE,
		RUNTIME_CLASS(CBoxDoc),
		RUNTIME_CLASS(CChildFrame), // custom MDI child frame
		RUNTIME_CLASS(CBoxView));
	AddDocTemplate(pDocTemplate);

			pDocTemplate = new CMultiDocTemplate(
		IDR_SALETYPE,
		RUNTIME_CLASS(CSaleDoc),
		RUNTIME_CLASS(CChildFrame), // custom MDI child frame
		RUNTIME_CLASS(CSaleView));
	AddDocTemplate(pDocTemplate);

		pDocTemplate = new CMultiDocTemplate(
		IDR_ITEMTYPE,
		RUNTIME_CLASS(CItemDoc),
		RUNTIME_CLASS(CChildFrame), // custom MDI child frame
		RUNTIME_CLASS(CItemView));
	AddDocTemplate(pDocTemplate);


		pDocTemplate = new CMultiDocTemplate(
		IDR_USERTYPE,
		RUNTIME_CLASS(CUserDoc),
		RUNTIME_CLASS(CChildFrame), // custom MDI child frame
		RUNTIME_CLASS(CUserView));
	AddDocTemplate(pDocTemplate);

			pDocTemplate = new CMultiDocTemplate(
		IDR_COSTTYPE,
		RUNTIME_CLASS(CMoneyDoc),
		RUNTIME_CLASS(CChildFrame), // custom MDI child frame
		RUNTIME_CLASS(CMoneyView));
	AddDocTemplate(pDocTemplate);

	// create main MDI Frame window
	CMainFrame* pMainFrame = new CMainFrame;
	if (!pMainFrame->LoadFrame(IDR_MAINFRAME))
		return FALSE;
	m_pMainWnd = pMainFrame;

	// Parse command line for standard shell commands, DDE, file open
	CCommandLineInfo cmdInfo;
	cmdInfo.m_nShellCommand = CCommandLineInfo::FileNothing;
	ParseCommandLine(cmdInfo);

	// Dispatch commands specified on the command line
	if (!ProcessShellCommand(cmdInfo))
		return FALSE;

	// The main window has been initialized, so show and update it.
	m_nCmdShow = SW_MAXIMIZE;
	pMainFrame->ShowWindow(m_nCmdShow);
	pMainFrame->UpdateWindow();

	CDbManger::OpenConnection();

	pMainFrame->OnCmdMsg(ID_MENU_LOGIN,0,0,0);

	return TRUE;
}


/////////////////////////////////////////////////////////////////////////////
// CAboutDlg dialog used for App About

class CAboutDlg : public CDialog
{
public:
	CAboutDlg();

// Dialog Data
	//{{AFX_DATA(CAboutDlg)
	enum { IDD = IDD_ABOUTBOX };
	CString	m_sAbout;
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CAboutDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	//{{AFX_MSG(CAboutDlg)
	virtual BOOL OnInitDialog();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialog(CAboutDlg::IDD)
{
	//{{AFX_DATA_INIT(CAboutDlg)
	m_sAbout = _T("");
	//}}AFX_DATA_INIT
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CAboutDlg)
	DDX_Text(pDX, IDC_EDIT_ABOUT, m_sAbout);
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialog)
	//{{AFX_MSG_MAP(CAboutDlg)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

// App command to run the dialog
void CHRSApp::OnAppAbout()
{
	CAboutDlg aboutDlg;
	aboutDlg.DoModal();
}

/////////////////////////////////////////////////////////////////////////////
// CHRSApp message handlers


int CHRSApp::ExitInstance() 
{
	// TODO: Add your specialized code here and/or call the base class
	CDbManger::CloseDBConnection();
	return CWinApp::ExitInstance();
}

BOOL CAboutDlg::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	// TODO: Add extra initialization here
	m_sAbout ="支持请联系：samniboy@gmail.com\r\n大格格 1.0 版\r\n版权所有 (C) 2010";
	UpdateData(false);
	//GetDlgItemText(IDC_EDIT_ABOUT,txt);
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

