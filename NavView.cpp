// NavView.cpp : implementation file
//

#include "stdafx.h"
#include "HRS.h"
#include "NavView.h"
#include "hrsdoc.h"
#include "hrsview.h"
#include "boxview.h"
#include "itemview.h"
#include "userview.h"
#include "saleview.h"
#include "childfrm.h"
#include "staticbox.h"
#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CNavView

IMPLEMENT_DYNCREATE(CNavView, CFormView)

CNavView::CNavView()
: CFormView(CNavView::IDD),m_cCustomer(CUSTOMER),m_cBox(BOX),m_cItem(ITEM),m_cSale(SALE),m_cUser(USER),m_cMoney(MONEY)
{
	//{{AFX_DATA_INIT(CNavView)
	//}}AFX_DATA_INIT
	m_iIconWidth = 100;
	m_iIconHeight = 100;
	m_iViewWidth = 1000;
	m_iViewHeight = 1000;
}

CNavView::~CNavView()
{
}

void CNavView::DoDataExchange(CDataExchange* pDX)
{
	CFormView::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CNavView)
	DDX_Control(pDX, IDC_STATIC_USER, m_cUser);
	DDX_Control(pDX, IDC_STATIC_SALE, m_cSale);
	DDX_Control(pDX, IDC_STATIC_MONEY, m_cMoney);
	DDX_Control(pDX, IDC_STATIC_ITEM, m_cItem);
	DDX_Control(pDX, IDC_STATIC_BOX, m_cBox);
	DDX_Control(pDX, IDC_STATIC_CUSTOMER, m_cCustomer);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CNavView, CFormView)
	//{{AFX_MSG_MAP(CNavView)
	ON_WM_SIZE()
	ON_WM_CTLCOLOR()
	ON_WM_PAINT()
	ON_WM_VSCROLL()
	ON_WM_MOUSEMOVE()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CNavView diagnostics

#ifdef _DEBUG
void CNavView::AssertValid() const
{
	CFormView::AssertValid();
}

void CNavView::Dump(CDumpContext& dc) const
{
	CFormView::Dump(dc);
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CNavView message handlers

void CNavView::OnInitialUpdate() 
{
	//CSize s(m_iViewWidth,m_iViewHeight);
	CSize s(10,10);
	this->SetScrollSizes(MM_TEXT,s);
    m_cCustomer.SubclassDlgItem(IDC_STATIC_CUSTOMER, this);
	m_cBox.SubclassDlgItem(IDC_STATIC_BOX, this);
	m_cItem.SubclassDlgItem(IDC_STATIC_ITEM, this);
	m_cSale.SubclassDlgItem(IDC_STATIC_SALE, this);
	m_cUser.SubclassDlgItem(IDC_STATIC_USER, this);
	m_cMoney.SubclassDlgItem(IDC_STATIC_MONEY, this);

	int rnum=2, cnum=3;

	int rgap = m_iViewHeight/(rnum), cgap = m_iViewWidth/(cnum);
		//CStaticBox m_cCustomer;
	CRect cus(0,0,cgap,rgap);
	cus.DeflateRect(5,5);
	//Deflect(10, 10, 10, 10);
    CRect box(cgap, 0, 2* cgap,rgap);
	box.InflateRect(-5,-5);
	CRect item(cgap*2,0,cgap*3,rgap);
	item.InflateRect(-5,-5);
	CRect sale(0,rgap,cgap,rgap*2);
	sale.InflateRect(-5,-5);
	CRect user(cgap,rgap,cgap*2,rgap*2);
	user.InflateRect(-5,-5);
	CRect money(cgap*2,rgap,cgap*3,rgap*2);
	money.InflateRect(-5,-5);
	

	m_cCustomer.MoveWindow(cus);
	m_cBox.MoveWindow(box);
	m_cItem.MoveWindow(item);
	m_cSale.MoveWindow(sale);
	m_cUser.MoveWindow(user);
	m_cMoney.MoveWindow(money);
	//ModifyStyle(WS_HSCROLL|WS_VSCROLL, 0, SWP_NOREDRAW|SWP_FRAMECHANGED);
	//sb.Detach();
}

BOOL CNavView::Create(LPCTSTR lpszClassName, LPCTSTR lpszWindowName, DWORD dwStyle, const RECT& rect, CWnd* pParentWnd, UINT nID, CCreateContext* pContext) 
{
	// TODO: Add your specialized code here and/or call the base class
	
	return CFormView::Create(lpszClassName, lpszWindowName, dwStyle, rect, pParentWnd, nID, pContext);
}

void CNavView::OnSize(UINT nType, int cx, int cy) 
{
	CFormView::OnSize(nType, cx, cy);
	

	// TODO: Add your message handler code here

	if (m_cCustomer.m_hWnd)
	{
	m_cCustomer.ShowWindow(SW_HIDE);
	m_cBox.ShowWindow(SW_HIDE);
	m_cItem.ShowWindow(SW_HIDE);
	m_cSale.ShowWindow(SW_HIDE);
	m_cUser.ShowWindow(SW_HIDE);
	m_cMoney.ShowWindow(SW_HIDE);
	}
}
CBrush navbsh = RGB(255,0,255);
HBRUSH CNavView::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor) 
{
	HBRUSH hbr = CFormView::OnCtlColor(pDC, pWnd, nCtlColor);
	
	// TODO: Change any attributes of the DC here
	
	// TODO: Return a different brush if the default is not desired

	return navbsh;
}

void CNavView::OnPaint() 
{
	CPaintDC dc(this); // device context for painting

	CRect rc;
	GetClientRect(&rc);

	m_iViewHeight = rc.bottom - rc.top;
	m_iViewWidth = rc.right - rc.left;

	
	// TODO: Add your message handler code here
/*	int rnum=8, cnum=8;

	int rgap = m_iViewHeight/(rnum), cgap = m_iViewWidth/(cnum);

	CPen pen;
	pen.CreatePen(PS_SOLID,1,RGB(255,0,255));
	dc.SelectObject(&pen);

	CFont ft;
	ft.CreatePointFont(420,_T("Impact"));
	dc.SelectObject(&ft);
	dc.SetBkMode(TRANSPARENT);
	dc.SetTextColor(RGB(0,0,0));
	CRect tr(cgap*2,rgap*1,cgap*3,rgap*2);
	dc.DrawText("¸ñ",&tr,DT_SINGLELINE|DT_CENTER|DT_VCENTER);
	tr.SetRect(cgap*3,rgap*1,cgap*4,rgap*2);
	dc.DrawText("×Ó",&tr,DT_SINGLELINE|DT_CENTER|DT_VCENTER);
	tr.SetRect(cgap*4,rgap*1,cgap*5,rgap*2);
	dc.DrawText("ÆÌ",&tr,DT_SINGLELINE|DT_CENTER|DT_VCENTER); */
	//AfxMessageBox("ffff");

	//m_iViewWidth = dc.GetDeviceCaps(HORZRES);
	//m_iViewHeight = dc.GetDeviceCaps(VERTRES);
	
	if (m_cCustomer.m_hWnd)
	    CenterBoxs(m_iViewWidth,  m_iViewHeight);

	
	/*
	//draw row
	for(int i=0;i<rnum;i++)
	{
		CPoint frm(0,rgap*i), to(m_iViewWidth,rgap*i);
		dc.LPtoDP(&frm);
		dc.LPtoDP(&to);
	    dc.MoveTo(frm);
	    dc.LineTo(to);		
	}
	//draw col
	for( i=0;i<cnum;i++)
	{
		CPoint frm(cgap*i,0), to(cgap*i, m_iViewHeight);
		dc.LPtoDP(&frm);
		dc.LPtoDP(&to);
	    dc.MoveTo(frm);
	    dc.LineTo(to);			
	} */
	/*for(i=0;i<rnum;i++)
		for(int j=0;j<cnum;j++)
		{
			CBrush br = RGB(((i*3+j)*100)%255,((i*2+j)*100)%255,((i*1+j)*100)%255);
			dc.SelectObject(&br);
			dc.Rectangle(cgap*i,rgap*j,cgap*(i+1),rgap*(j+1));
		}*/




	//dc.Rectangle(&rc);
	
	//CFormView::OnPaint();
	TRACE("out out");
}



void CNavView::OnVScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar) 
{
	// TODO: Add your message handler code here and/or call default
	
	CFormView::OnVScroll(nSBCode, nPos, pScrollBar);
	Invalidate();
}

BOOL CNavView::PreCreateWindow(CREATESTRUCT& cs) 
{
	// TODO: Add your specialized code here and/or call the base class
	//cs.style =cs.style & ~WS_VSCROLL;
	return CFormView::PreCreateWindow(cs);
}

void CNavView::OnMouseMove(UINT nFlags, CPoint point) 
{
	// TODO: Add your message handler code here and/or call default
   /* m_cCustomer.SetOutBitmap();
	m_cBox.SetOutBitmap();
	m_cItem.SetOutBitmap();
	m_cSale.SetOutBitmap();
	m_cUser.SetOutBitmap();
	m_cMoney.SetOutBitmap();

	CFormView::OnMouseMove(nFlags, point);*/
}

void CNavView::CenterBoxs(int w, int h)
{


	m_iViewHeight = h;
	m_iViewWidth = w;

	int rnum=2, cnum=3;

	int rgap = m_iViewHeight/(rnum) -10, cgap = m_iViewWidth/(cnum);
		//CStaticBox m_cCustomer;
	CRect cus(0,0,cgap,rgap);
	//cus.DeflateRect(5,5);
	//Deflect(10, 10, 10, 10);
    CRect box(cgap, 0, 2* cgap,rgap);
	//box.DeflateRect(5,5);
	CRect item(cgap*2,0,cgap*3,rgap);
	//item.DeflateRect(5,5);
	CRect sale(0,rgap,cgap,rgap*2);
	//sale.DeflateRect(5,5);
	CRect user(cgap,rgap,cgap*2,rgap*2);
	//user.DeflateRect(5,5);
	CRect money(cgap*2,rgap,cgap*3,rgap*2);
	//money.DeflateRect(5,5);
	
	m_cCustomer.MoveWindow(cus);
	m_cBox.MoveWindow(box);
	m_cItem.MoveWindow(item);
	m_cSale.MoveWindow(sale);
	m_cUser.MoveWindow(user);
	m_cMoney.MoveWindow(money);
	m_cCustomer.ShowWindow(SW_SHOW);
	m_cBox.ShowWindow(SW_SHOW);
	m_cItem.ShowWindow(SW_SHOW);
	m_cSale.ShowWindow(SW_SHOW);
	m_cUser.ShowWindow(SW_SHOW);
	m_cMoney.ShowWindow(SW_SHOW);
}

void CNavView::OnDraw(CDC* pDC) 
{
	// TODO: Add your specialized code here and/or call the base class

	::AfxMessageBox("Haha");
	m_iViewWidth = pDC->GetDeviceCaps(HORZRES);
	m_iViewHeight = pDC->GetDeviceCaps(VERTRES);
	
	CenterBoxs(m_iViewWidth,  m_iViewHeight);
}
