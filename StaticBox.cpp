// StaticBox.cpp : implementation file
//

#include "stdafx.h"
#include "hrs.h"
#include "StaticBox.h"
#include "hrsdoc.h"
#include "hrsview.h"
#include "boxview.h"
#include "itemview.h"
#include "userview.h"
#include "saleview.h"
#include "childfrm.h"
#include "navview.h"
#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CStaticBox

CStaticBox::CStaticBox()
{
	m_bIsMouseInBox = false;
}

CStaticBox::CStaticBox(BOXTYPE btt):bt(btt)
{
}

CStaticBox::~CStaticBox()
{
}


BEGIN_MESSAGE_MAP(CStaticBox, CStatic)
	//{{AFX_MSG_MAP(CStaticBox)
	ON_WM_MOUSEMOVE()
	ON_CONTROL_REFLECT(BN_CLICKED, OnClicked)
	ON_WM_CAPTURECHANGED()
	ON_WM_SETCURSOR()
	ON_WM_NCMOUSEMOVE()
	ON_WM_KILLFOCUS()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CStaticBox message handlers

void CStaticBox::OnMouseMove(UINT nFlags, CPoint point) 
{
	// TODO: Add your message handler code here and/or call default
	//AfxMessageBox("moved mouse!");
	//this->SetCursor((HCURSOR));
    //::SetCursor(((CHRSApp*)AfxGetApp())->m_BTHand);

	SetInBitmap();

	CStatic::OnMouseMove(nFlags, point);
}

void CStaticBox::OnClicked() 
{
	// TODO: Add your control notification handler code here
	SetOutBitmap();
	switch(bt)
	{
	case CUSTOMER:
		OnStaticCustomer();
		break;
	case BOX:
		OnStaticBox();
		break;
	case ITEM:
		OnStaticItem();
		break;
	case SALE:
		OnStaticSale();
		break;
	case USER:
		OnStaticUser();
		break;
	case MONEY:
		OnStaticMoney();
		break;
	}
}
BOOL CStaticBox::Create(LPCTSTR lpszClassName, LPCTSTR lpszWindowName, DWORD dwStyle, const RECT& rect, CWnd* pParentWnd, UINT nID, CCreateContext* pContext) 
{
	// TODO: Add your specialized code here and/or call the base class
	
	return CWnd::Create(lpszClassName, lpszWindowName, dwStyle, rect, pParentWnd, nID, pContext);
}


void CStaticBox::OnStaticCustomer() 
{
	// TODO: Add your control notification handler code here
	//MessageBox("aaa");
	// TODO: Add your control notification handler code here
	CChildFrame::bt = CUSTOMER;
	CHRSApp *pApp=(CHRSApp *)::AfxGetApp();
	POSITION pos = pApp->m_pDocManager->GetFirstDocTemplatePosition();
	CDocTemplate *pt;
	while(pos)
	{
		pt=pApp->m_pDocManager->GetNextDocTemplate(pos);
		CString docstr;
		pt->GetDocString(docstr,CDocTemplate::fileNewName);
		//this->MessageBox(docstr);
		if(docstr == "¿Í»§")
		{
			POSITION pos =	pt->GetFirstDocPosition();
			CCUSTOMERDoc *pDoc = NULL;
			if(pos)
				pDoc=(CCUSTOMERDoc*)pt->GetNextDoc(pos);

			if(pDoc)
			{
				CCUSTOMERView *pView = NULL;
				CChildFrame *pActiveChild=NULL;
				pos = pDoc->GetFirstViewPosition();
				pView = (CCUSTOMERView*)pDoc->GetNextView(pos);
				if(pView)
				{
					pActiveChild= (CChildFrame*)pView->GetParent();

					//pActiveChild->SendMessage(WM_);
					//::BringWindowToTop(pActiveChild->m_hWnd);
					//pActiveChild->ShowWindow(SW_SHOW);
					//::BringWindowToTop(pActiveChild->m_hWnd);

					//CChildFrame cf;
					//pActiveChild->ActivateFrame(SW_HIDE);
					
					pActiveChild->ActivateFrame(SW_SHOW);
					////this->OnOK();
					return;
				}
			}				
			pt->OpenDocumentFile(NULL);
			
			break;
		}
	}
	////this->OnOK();
}

void CStaticBox::OnStaticBox() 
{
	// TODO: Add your control notification handler code here
	// TODO: Add your control notification handler code here
	CChildFrame::bt=BOX;
	CHRSApp *pApp=(CHRSApp *)::AfxGetApp();
	POSITION pos = pApp->m_pDocManager->GetFirstDocTemplatePosition();
	CDocTemplate *pt;
	while(pos)
	{
		pt=pApp->m_pDocManager->GetNextDocTemplate(pos);
		CString docstr;
		pt->GetDocString(docstr,CDocTemplate::fileNewName);
		//this->MessageBox(docstr);
		if(docstr == "BOX")
		{
			POSITION pos =	pt->GetFirstDocPosition();
			CCUSTOMERDoc *pDoc = NULL;
			if(pos)
				pDoc=(CCUSTOMERDoc*)pt->GetNextDoc(pos);

			if(pDoc)
			{
				CBoxView *pView = NULL;
				CChildFrame *pActiveChild=NULL;
				pos = pDoc->GetFirstViewPosition();
				pView = (CBoxView*)pDoc->GetNextView(pos);
				if(pView)
				{
					pActiveChild= (CChildFrame*)pView->GetParent();
					pActiveChild->ActivateFrame(SW_SHOW);
					//this->OnOK();
					return;
				}
			}
			pt->OpenDocumentFile(NULL);
			break;
		}
	}
	//this->OnOK();		
}

void CStaticBox::OnStaticItem() 
{
	// TODO: Add your control notification handler code here
	// TODO: Add your control notification handler code here
	CChildFrame::bt=ITEM;
	CHRSApp *pApp=(CHRSApp *)::AfxGetApp();
	POSITION pos = pApp->m_pDocManager->GetFirstDocTemplatePosition();
	CDocTemplate *pt;
	while(pos)
	{
		pt=pApp->m_pDocManager->GetNextDocTemplate(pos);
		CString docstr;
		pt->GetDocString(docstr,CDocTemplate::fileNewName);
		//this->MessageBox(docstr);
		if(docstr == "ITEM")
		{
			POSITION pos =	pt->GetFirstDocPosition();
			CCUSTOMERDoc *pDoc = NULL;
			if(pos)
				pDoc=(CCUSTOMERDoc*)pt->GetNextDoc(pos);

			if(pDoc)
			{
				CItemView *pView = NULL;
				CChildFrame *pActiveChild=NULL;
				pos = pDoc->GetFirstViewPosition();
				pView = (CItemView*)pDoc->GetNextView(pos);
				if(pView)
				{
					pActiveChild= (CChildFrame*)pView->GetParent();
					pActiveChild->ActivateFrame(SW_SHOW);
					//this->OnOK();
					return;
				}
			}
			pt->OpenDocumentFile(NULL);
			break;
		}
	}
	//this->OnOK();	bb	
}

void CStaticBox::OnStaticSale() 
{
	// TODO: Add your control notification handler code here
	// TODO: Add your control notification handler code here
	CChildFrame::bt=SALE;
	CHRSApp *pApp=(CHRSApp *)::AfxGetApp();
	POSITION pos = pApp->m_pDocManager->GetFirstDocTemplatePosition();
	CDocTemplate *pt;
	while(pos)
	{
		pt=pApp->m_pDocManager->GetNextDocTemplate(pos);
		CString docstr;
		pt->GetDocString(docstr,CDocTemplate::fileNewName);
		//this->MessageBox(docstr);
		if(docstr == "SALE")
		{
			POSITION pos =	pt->GetFirstDocPosition();
			CCUSTOMERDoc *pDoc = NULL;
			if(pos)
				pDoc=(CCUSTOMERDoc*)pt->GetNextDoc(pos);

			if(pDoc)
			{
				CSaleView *pView = NULL;
				CChildFrame *pActiveChild=NULL;
				pos = pDoc->GetFirstViewPosition();
				pView = (CSaleView*)pDoc->GetNextView(pos);
				if(pView)
				{
					pActiveChild= (CChildFrame*)pView->GetParent();
					pActiveChild->ActivateFrame(SW_SHOW);
					//this->OnOK();
					return;
				}
			}
			pt->OpenDocumentFile(NULL);
			break;
		}
	}
	//this->OnOK();		
}

void CStaticBox::OnStaticUser() 
{
	// TODO: Add your control notification handler code here
	// TODO: Add your control notification handler code here
	CChildFrame::bt=USER;
	CHRSApp *pApp=(CHRSApp *)::AfxGetApp();
	POSITION pos = pApp->m_pDocManager->GetFirstDocTemplatePosition();
	CDocTemplate *pt;
	while(pos)
	{
		pt=pApp->m_pDocManager->GetNextDocTemplate(pos);
		CString docstr;
		pt->GetDocString(docstr,CDocTemplate::fileNewName);
		//this->MessageBox(docstr);
		if(docstr == "USER")
		{
			POSITION pos =	pt->GetFirstDocPosition();
			CCUSTOMERDoc *pDoc = NULL;
			if(pos)
				pDoc=(CCUSTOMERDoc*)pt->GetNextDoc(pos);

			if(pDoc)
			{
				CUserView *pView = NULL;
				CChildFrame *pActiveChild=NULL;
				pos = pDoc->GetFirstViewPosition();
				pView = (CUserView*)pDoc->GetNextView(pos);
				if(pView)
				{
					pActiveChild= (CChildFrame*)pView->GetParent();
					pActiveChild->ActivateFrame(SW_SHOW);
					//this->OnOK();
					return;
				}
			}
			pt->OpenDocumentFile(NULL);
			break;
		}
	}
	//this->OnOK();		
}

void CStaticBox::OnStaticMoney() 
{
	// TODO: Add your control notification handler code here
	// TODO: Add your control notification handler code here
	CChildFrame::bt=MONEY;
	CHRSApp *pApp=(CHRSApp *)::AfxGetApp();
	POSITION pos = pApp->m_pDocManager->GetFirstDocTemplatePosition();
	CDocTemplate *pt;
	while(pos)
	{
		pt=pApp->m_pDocManager->GetNextDocTemplate(pos);
		CString docstr;
		pt->GetDocString(docstr,CDocTemplate::fileNewName);
		//this->MessageBox(docstr);
		if(docstr == "COST")
		{
			POSITION pos =	pt->GetFirstDocPosition();
			CCUSTOMERDoc *pDoc = NULL;
			if(pos)
				pDoc=(CCUSTOMERDoc*)pt->GetNextDoc(pos);

			if(pDoc)
			{
				CUserView *pView = NULL;
				CChildFrame *pActiveChild=NULL;
				pos = pDoc->GetFirstViewPosition();
				pView = (CUserView*)pDoc->GetNextView(pos);
				if(pView)
				{
					pActiveChild= (CChildFrame*)pView->GetParent();
					pActiveChild->ActivateFrame(SW_SHOW);
					//this->OnOK();
					return;
				}
			}
			pt->OpenDocumentFile(NULL);
			break;
		}
	}
	//this->OnOK();		
}

void CStaticBox::OnCaptureChanged(CWnd *pWnd) 
{
	// TODO: Add your message handler code here
	//AfxMessageBox("losing capture");
	CStatic::OnCaptureChanged(pWnd);
}

BOOL CStaticBox::OnSetCursor(CWnd* pWnd, UINT nHitTest, UINT message) 
{
	// TODO: Add your message handler code here and/or call default
	
	return CStatic::OnSetCursor(pWnd, nHitTest, message);
}

void CStaticBox::OnNcMouseMove(UINT nHitTest, CPoint point) 
{
	// TODO: Add your message handler code here and/or call default
	//AfxMessageBox("non client move");
	CStatic::OnNcMouseMove(nHitTest, point);
}

void CStaticBox::OnKillFocus(CWnd* pNewWnd) 
{
	//CStatic::OnKillFocus(pNewWnd);
	//AfxMessageBox("lose focus");
	// TODO: Add your message handler code here
	
}

void CStaticBox::SetInBitmap()
{
	/*if(m_bIsMouseInBox ||1)
		return;
	CBitmap b;
	switch(bt)
	{
	case CUSTOMER:
	    b.LoadBitmap(IDB_CUSTOMER_IN);
		break;
	case BOX:
		b.LoadBitmap(IDB_BOX_IN);
		break;
	case ITEM:
		b.LoadBitmap(IDB_ITEM_IN);
		break;
	case USER:
		b.LoadBitmap(IDB_USER_IN);
		break;
	case SALE:
		b.LoadBitmap(IDB_SALE_IN);
		break;
	case MONEY:
		b.LoadBitmap(IDB_MONEY_IN);
		break;
	}

	SetBitmap((HBITMAP)b);
	b.Detach();
	m_bIsMouseInBox = true;*/
}

void CStaticBox::SetOutBitmap()
{
	/*if(!m_bIsMouseInBox ||1)
		return;
	CBitmap b;
	switch(bt)
	{
	case CUSTOMER:
	    b.LoadBitmap(IDB_CUSTOMER);
		break;
	case BOX:
		b.LoadBitmap(IDB_BOX);
		break;
	case ITEM:
		b.LoadBitmap(IDB_ITEM);
		break;
	case USER:
		b.LoadBitmap(IDB_USER);
		break;
	case SALE:
		b.LoadBitmap(IDB_SALE);
		break;
	case MONEY:
		b.LoadBitmap(IDB_MONEY);
		break;
	}
	SetBitmap((HBITMAP)b);
	b.Detach();
	m_bIsMouseInBox = false;*/
}
