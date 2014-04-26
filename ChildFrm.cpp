// ChildFrm.cpp : implementation of the CChildFrame class
//

#include "stdafx.h"
#include "HRS.h"

#include "ChildFrm.h"
#include "hrsview.h"
#include "boxview.h"
#include "itemview.h"
#include "saleview.h"
#include "userview.h"
#include "moneyview.h"

#include "queryview.h"
#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CChildFrame

IMPLEMENT_DYNCREATE(CChildFrame, CMDIChildWnd)

BEGIN_MESSAGE_MAP(CChildFrame, CMDIChildWnd)
	//{{AFX_MSG_MAP(CChildFrame)
	ON_WM_SIZE()
	ON_WM_CREATE()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CChildFrame construction/destruction

CChildFrame::CChildFrame()
{
	// TODO: add member initialization code here
	
}

CChildFrame::~CChildFrame()
{
}

BOOL CChildFrame::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs

		//cs.style = WS_CHILD | WS_VISIBLE| WS_EX_CLIENTEDGE | WS_OVERLAPPED | WS_CAPTION | WS_SYSMENU
		//| FWS_ADDTOTITLE | WS_MINIMIZEBOX | WS_MAXIMIZEBOX;

	if( !CMDIChildWnd::PreCreateWindow(cs) )
		return FALSE;

	return TRUE;
}

void CChildFrame::ActivateFrame(int nCmdShow)
{
	// TODO: Modify this function to change how the frame is activated.

	nCmdShow = SW_SHOWMAXIMIZED;
	
	CMDIChildWnd::ActivateFrame(nCmdShow);
	
}

BOXTYPE CChildFrame::bt = CUSTOMER;
/////////////////////////////////////////////////////////////////////////////
// CChildFrame diagnostics

#ifdef _DEBUG
void CChildFrame::AssertValid() const
{
	CMDIChildWnd::AssertValid();
}

void CChildFrame::Dump(CDumpContext& dc) const
{
	CMDIChildWnd::Dump(dc);
}

#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CChildFrame message handlers

void CChildFrame::RecalcLayout(BOOL bNotify) 
{
	// TODO: Add your specialized code here and/or call the base class
	
	CMDIChildWnd::RecalcLayout(bNotify);
}

void CChildFrame::OnSize(UINT nType, int cx, int cy) 
{
	CMDIChildWnd::OnSize(nType, cx, cy);
	
	// TODO: Add your message handler code here
	::BringWindowToTop(this->m_hWnd);
}

BOOL CChildFrame::OnCreateClient(LPCREATESTRUCT lpcs, CCreateContext* pContext) 
{
	// TODO: Add your specialized code here and/or call the base class
	//CSplitterWnd sp;
	//CMDIChildWnd::OnCreateClient(lpcs, pContext);
	//AfxMessageBox("create child client");
	switch(CChildFrame::bt)
	{
	case CUSTOMER:
		m_wSplitter.CreateStatic(this, 1, 2);//SIZE(10,10), pContext);
	    m_wSplitter.CreateView(0,0,RUNTIME_CLASS(CCUSTOMERView),CSize(500,1000), pContext);
	    m_wSplitter.CreateView(0,1,RUNTIME_CLASS(CQueryView),CSize(500,1000), pContext);	
		return TRUE;
	case BOX:
		m_wSplitter.CreateStatic(this, 1, 2);//SIZE(10,10), pContext);
	    m_wSplitter.CreateView(0,0,RUNTIME_CLASS(CBoxView),CSize(500,1000), pContext);
	    m_wSplitter.CreateView(0,1,RUNTIME_CLASS(CQueryView),CSize(500,1000), pContext);	
		return TRUE;
	case ITEM:
		m_wSplitter.CreateStatic(this, 1, 2);//SIZE(10,10), pContext);
	    m_wSplitter.CreateView(0,0,RUNTIME_CLASS(CItemView),CSize(500,1000), pContext);
	    m_wSplitter.CreateView(0,1,RUNTIME_CLASS(CQueryView),CSize(500,1000), pContext);	
		return TRUE;
	case SALE:
		m_wSplitter.CreateStatic(this, 1, 2);//SIZE(10,10), pContext);
	    m_wSplitter.CreateView(0,0,RUNTIME_CLASS(CSaleView),CSize(500,1000), pContext);
	    m_wSplitter.CreateView(0,1,RUNTIME_CLASS(CQueryView),CSize(500,1000), pContext);	
		return TRUE;
	case USER:
		m_wSplitter.CreateStatic(this, 1, 2);//SIZE(10,10), pContext);
	    m_wSplitter.CreateView(0,0,RUNTIME_CLASS(CUserView),CSize(500,1000), pContext);
	    m_wSplitter.CreateView(0,1,RUNTIME_CLASS(CQueryView),CSize(500,1000), pContext);	
		return TRUE;
	case MONEY:
		m_wSplitter.CreateStatic(this, 1, 2);//SIZE(10,10), pContext);
	    m_wSplitter.CreateView(0,0,RUNTIME_CLASS(CMoneyView),CSize(500,1000), pContext);
	    m_wSplitter.CreateView(0,1,RUNTIME_CLASS(CQueryView),CSize(500,1000), pContext);	
		return TRUE;	
		break;
	default:
		return CMDIChildWnd::OnCreateClient(lpcs, pContext);
	}
	return CMDIChildWnd::OnCreateClient(lpcs, pContext);
}

int CChildFrame::OnCreate(LPCREATESTRUCT lpCreateStruct) 
{
	if (CMDIChildWnd::OnCreate(lpCreateStruct) == -1)
		return -1;
	
	// TODO: Add your specialized creation code here

	return 0;
}
