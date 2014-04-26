// QueryView.cpp : implementation file
//

#include "stdafx.h"
#include "hrs.h"
#include "QueryView.h"
#include "childfrm.h"
#include "mainfrm.h"
#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CQueryView

IMPLEMENT_DYNCREATE(CQueryView, CScrollView)

CQueryView::CQueryView()
{
Init();	
}


CQueryView::~CQueryView()
{
}


BEGIN_MESSAGE_MAP(CQueryView, CScrollView)
	//{{AFX_MSG_MAP(CQueryView)
	ON_COMMAND(AFX_ID_PREVIEW_PRINT, OnIdPreviewPrint)
	ON_WM_CONTEXTMENU()
	ON_UPDATE_COMMAND_UI(ID_FILE_PRINT_DIRECT, OnUpdateMenuPrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, OnFilePrintDirect)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, OnFilePrintPreview)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CQueryView drawing

void CQueryView::OnInitialUpdate()
{
	CScrollView::OnInitialUpdate();

	CSize sizeTotal;
	// TODO: calculate the total size of this view
	sizeTotal.cx = sizeTotal.cy = 100;
	//AfxMessageBox("aaa");
	SetScrollSizes(MM_TEXT, sizeTotal);
}

void CQueryView::OnDraw(CDC* pDC)
{
	if(pDC->IsPrinting())
	{
		DrawPrinter(pDC);
	}
	else
	{
		DrawScreen(pDC);
	}
}

/////////////////////////////////////////////////////////////////////////////
// CQueryView diagnostics

#ifdef _DEBUG
void CQueryView::AssertValid() const
{
	CScrollView::AssertValid();
}

void CQueryView::Dump(CDumpContext& dc) const
{
	CScrollView::Dump(dc);
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CQueryView message handlers

void CQueryView::QueryRecordset()
{
	CString sql = m_sQuerySql + m_sFilter;
	TRACE("sql is: %s\n", sql);
	if(sql.GetLength()<=0)
		return;
	m_wrs.ExecuteSql(sql);
	QueryFootRecordSet();
}

void CQueryView::Init()
{
	m_nRecordCnt = 0;
	m_cxHeader = 80;
	m_cyHeader = 30;
	m_cyCell = 30;
	m_cxCell = 80;
	m_sQuerySql = "";
	m_sFilter = "";
	m_sFootSql = "";
	m_sFootFilter = "";
    m_nTopMargin = 100;
	m_nTopLineGap = 20;
	m_nLeftMargin = 50;
	m_nRightMargin = 50;
	m_nBottomMargin = 100;
	m_nBottomLineGap = 20;
	m_sTitle = "信息查询";
	m_nPageHeigh = 0;
	m_viewSize = CSize(100,100);

	m_ftTitle.CreatePointFont(200, "黑体");
	m_ftHeader.CreatePointFont(100, "黑体");
	m_ftHeaderNote.CreatePointFont(80, "黑体");
	m_ftRecord.CreatePointFont(80, "黑体");
	m_ftFooter.CreatePointFont(50, "黑体");
	m_ftFooterNote.CreatePointFont(50, "黑体");
}

void CQueryView::OnIdPreviewPrint() 
{
	// TODO: Add your command handler code here
	//CPreviewView pv;
	//CScrollView::OnPrint();
}

void CQueryView::OnContextMenu(CWnd* pWnd, CPoint point) 
{
	// TODO: Add your message handler code here
	//AfxMessageBox("right clicked");
	CMenu menu, *subMenu;
	menu.LoadMenu(IDR_MENU_PRINT);
	subMenu = menu.GetSubMenu(0);
	subMenu->TrackPopupMenu(TPM_LEFTALIGN|TPM_RIGHTBUTTON, point.x, point.y, this);
	
}

void CQueryView::OnUpdateMenuPrint(CCmdUI* pCmdUI) 
{
	// TODO: Add your command update UI handler code here
	
}

void CQueryView::OnFilePrintDirect() 
{
	// TODO: Add your command handler code here
	OnFilePrint();
	//AfxGetApp()->m_hMainSendMessage(WM_COMMAND, ID_FILE_PRINT_SETUP);
}

BOOL CQueryView::OnPreparePrinting(CPrintInfo* pInfo) 
{
	// TODO: call DoPreparePrinting to invoke the Print dialog box
	//AfxGetApp()
	
	//pInfo->m_pPD->UpdateData(false);
	if(pInfo->m_pPD->DoModal() != IDOK)
		return FALSE;
	SetPrintPara(pInfo);
	//pInfo->m_pPD->UpdateData(true);
	return DoPreparePrinting(pInfo);
	// CScrollView::OnPreparePrinting(pInfo);
}

void CQueryView::SetPrintPara(CPrintInfo *pInfo)
{
	//CFont *pOldFnt;
	//int nTitleHeigh, nHeaderHeigh, nFooterHeigh, nRecordHeigh;
	CDC pdc;
	pdc.Attach(pInfo->m_pPD->m_pd.hDC);
	pdc.SetMapMode(MM_LOENGLISH);
	/*TEXTMETRIC tmHeader, tmFooter, tmTitle, tmRecord;

	pOldFnt = pdc.SelectObject(&m_ftTitle);
	pdc.GetTextMetrics(&tmTitle);
	nTitleHeigh = tmTitle.tmHeight + tmTitle.tmExternalLeading;

	pdc.SelectObject(&m_ftHeader);
	pdc.GetTextMetrics(&tmHeader);
	nHeaderHeigh = tmHeader.tmHeight + tmHeader.tmExternalLeading;

	pdc.SelectObject(&m_ftFooter);
	pdc.GetTextMetrics(&tmFooter);
	nFooterHeigh = tmFooter.tmHeight + tmFooter.tmExternalLeading;

	pdc.SelectObject(&m_ftRecord);
	pdc.GetTextMetrics(&tmRecord);
	nRecordHeigh = tmRecord.tmHeight + tmRecord.tmExternalLeading;

	pdc.SelectObject(pOldFnt);

	int totHeight = nTitleHeigh + nHeaderHeigh + nRecordHeigh * m_nRecordCnt + nFooterHeigh;*/
	int cxPrint, cyPrint;
	cxPrint = pdc.GetDeviceCaps(HORZRES);
	cyPrint = pdc.GetDeviceCaps(VERTRES);

	/*int cxlog, cylog;
	cxlog = pdc.GetDeviceCaps(LOGPIXELSX);
	cylog = pdc.GetDeviceCaps(LOGPIXELSY);

	int InchPagey = cyPrint/cylog;
	int InchPagex = cxPrint/cxlog;*/

	CSize pageSize=CSize(cxPrint, cyPrint);
	pdc.DPtoLP(&pageSize);

	m_nPageHeigh = pageSize.cy;
	int pages = m_viewSize.cy/m_nPageHeigh;
	
	pInfo->m_nCurPage = 1;
	pInfo->m_pPD->m_pd.nFromPage = 1;
	pInfo->m_pPD->m_pd.nToPage = pages;
	pInfo->m_pPD->m_pd.nMinPage = 1;
	pInfo->m_pPD->m_pd.nMaxPage = pages;
	pdc.Detach();
}

void CQueryView::OnBeginPrinting(CDC* pDC, CPrintInfo* pInfo) 
{
	// TODO: Add your specialized code here and/or call the base class
	
	CScrollView::OnBeginPrinting(pDC, pInfo);
}

void CQueryView::QueryFootRecordSet()
{
	CString sql;
	if(m_sFootSql.GetLength()<=0)
		return;

	sql = m_sFootSql + m_sFootFilter;
	TRACE("sql is: %s\n", sql);
	if(sql.GetLength()<=0)
		return;
	m_wfootRs.ExecuteSql(sql);
}


void CQueryView::OnPrepareDC(CDC* pDC, CPrintInfo* pInfo) 
{
	// TODO: Add your specialized code here and/or call the base class

	pDC->SetMapMode(MM_LOENGLISH);
	pDC->SetViewportOrg(0, 0);
	if(pDC->IsPrinting())
	{
		int y = (pInfo->m_nCurPage-1)*m_nPageHeigh;
		CPoint p = CPoint(0, y);
		pDC->LPtoDP(&p);
		pDC->SetViewportOrg(0, p.y);

		pInfo->m_rectDraw.SetRect(0, 0,
					pDC->GetDeviceCaps(HORZRES),
					pDC->GetDeviceCaps(VERTRES));
				pDC->DPtoLP(&pInfo->m_rectDraw);
				pInfo->m_rectDraw.bottom += m_nBottomMargin;
		return;
	}
	CScrollView::OnPrepareDC(pDC, pInfo);
}

void CQueryView::DrawScreen(CDC *pDC)
{
	CDocument* pDoc = GetDocument();

	pDC->SetMapMode(MM_LOENGLISH);
	if(m_wrs.IsOpen())
	{
	    m_viewSize = CSize(m_nLeftMargin+m_nRightMargin + m_wrs.GetColumnCount()*m_cxCell, m_nTopMargin + m_nTopLineGap + m_nBottomMargin+m_wrs.GetRecordCount()*m_cyCell+m_cyHeader+m_nBottomLineGap);
		//pDC->SetWindowExt(m_viewSize.cx, -m_viewSize.cy);
	    SetScrollSizes(MM_LOENGLISH, m_viewSize);
		DrawTitle(pDC);
		DrawBody(pDC);
		DrawFooter(pDC);
	}
}
/*	
-------------------------------
   |
   |
   |m_nTopMargin
   |
---------------------------
   | m_nTopLineGap
----------------------
   |
   |m_cyHeader
------------------
   |
   |
   |Records
   .
   .
   .
-------------------
   | m_nBottomLineGap
-------------------
   |
   |
   |m_nBottomMargin
------------------------------------

	
	  int scrollpos;
	scrollpos=this->GetScrollPos(SB_VERT);
	CString tt;
	CRecordset *p = NULL;
	CRect clientrc;
	GetClientRect(&clientrc);

	if(m_wrs.IsOpen())
	{
		long i;
		m_viewSize.cx = (nColNum+1)*m_cxHeader+m_nLeftMargin +m_nRightMargin;
		m_viewSize.cy = (m_wrs.GetRecordCount())*m_cyCell+m_cyHeader+m_nTopMargin+m_nBottomMargin;
		CSize page = CSize(0,10 * m_cyCell);
		CSize line = CSize(0, 1 * m_cyCell);
		this->SetScrollSizes(MM_TEXT,m_viewSize, page, line);

		CRect ttr(m_nLeftMargin, m_nTopLineGap- 80, (nColNum+1)*m_cxHeader+m_nLeftMargin, m_nTopLineGap-30);
		pDC->SelectObject(&m_ftTitle);
		pDC->SetTextColor(RGB(0,0,0));
		pDC->DrawText(m_sTitle, &ttr, DT_SINGLELINE|DT_CENTER|DT_VCENTER);

		CRect dtr(m_nLeftMargin, m_nTopLineGap- 30, m_nLeftMargin + 150, m_nTopLineGap);
		CFont datefont;
		datefont.CreatePointFont(100, "黑体");
		
		pDC->SelectObject(&datefont);
		pDC->SetTextColor(RGB(0,0,0));
		CTime ct = CTime::GetCurrentTime();
		CString tstr;
		tstr.Format("日期: %d年%d月%d日", ct.GetYear(), ct.GetMonth(), ct.GetDay());
		pDC->DrawText(tstr, &dtr, DT_SINGLELINE|DT_CENTER|DT_VCENTER);

		CRect usr((nColNum+1)*m_cxHeader+m_nLeftMargin - 200, m_nTopLineGap- 30, (nColNum+1)*m_cxHeader+m_nLeftMargin, m_nTopLineGap);
		CFont userfont;
		userfont.CreatePointFont(100, "黑体");
		
		pDC->SelectObject(&userfont);
		pDC->SetTextColor(RGB(0,0,0));
		CMainFrame *pM = (CMainFrame*)AfxGetApp()->GetMainWnd();
		tstr.Format("操作员: %s", pM->m_cLoginUser.m_sUserName);
		pDC->DrawText(tstr, &usr, DT_SINGLELINE|DT_CENTER|DT_VCENTER);
		

		CPoint frm(m_nLeftMargin, m_nTopLineGap);
		CPoint to(m_viewSize.cx - m_nRightMargin,m_nTopLineGap);
		pDC->MoveTo(frm);
		pDC->LineTo(to);

	    frm = CPoint(m_nLeftMargin, m_nTopMargin);
	    to = CPoint(m_viewSize.cx - m_nRightMargin,m_nTopMargin);
		pDC->MoveTo(frm);
		pDC->LineTo(to);

	    frm = CPoint(m_nLeftMargin, m_nTopMargin+m_cyHeader);
		to  = CPoint(m_viewSize.cx - m_nRightMargin,m_nTopMargin+m_cyHeader);

		pDC->MoveTo(frm);
		pDC->LineTo(to);
		CBrush brush;
		brush.CreateStockObject(LTGRAY_BRUSH);
		pDC->SelectObject(&brush);
		CODBCFieldInfo cfi;
		pDC->SetBkMode(TRANSPARENT);
		CString colname;

		pDC->SelectObject(&m_ftHeader);
		pDC->SetTextColor(RGB(0,0,0));
		
		for(i = 0;i<=nColNum; i++)
		{
			pDC->MoveTo(m_nLeftMargin+m_cxHeader*i, m_nTopMargin);
			pDC->LineTo(m_nLeftMargin+m_cxHeader*i, m_viewSize.cy - m_nBottomMargin);
			CRect rc(m_nLeftMargin+m_cxHeader*i+1, m_nTopMargin+1, m_nLeftMargin+m_cxHeader*i+m_cxHeader, m_nTopMargin+m_cyHeader);
			pDC->FillRect(rc,&brush);
			//pDC->Draw3dRect(&rc, RGB(255, 255, 255), RGB(128,128,128));
			if(i==0)
			{
				colname = "行号";
			}
			else
			{
			    p->GetODBCFieldInfo(i-1, cfi);
				colname = cfi.m_strName;
			}
			pDC->DrawText(colname, &rc, DT_SINGLELINE|DT_CENTER|DT_VCENTER);
			
		}
		pDC->MoveTo(m_nLeftMargin+m_cxHeader*(nColNum+1), m_nTopMargin);
		pDC->LineTo(m_nLeftMargin+m_cxHeader*(nColNum+1), m_viewSize.cy - m_nBottomMargin);

		
		CPoint lefttop(m_nLeftMargin, m_nTopMargin + m_cyHeader), bottomright;
		CPoint lt = lefttop;


		pDC->SelectObject(&m_ftRecord);
		pDC->SetTextColor(RGB(0,0,255));

		i = ((scrollpos - lt.y) / m_cyCell)>0 ? ((scrollpos - lt.y) / m_cyCell): 0 ;
		nRecordCnt = i+clientrc.Height() / m_cyCell + 1;
		TRACE("i = %d, cnt = %d\n", i, nRecordCnt);
		for(int k=0; k<i; k++)
			p->MoveNext();

		for(;i<nRecordCnt && !p->IsEOF(); i++)
		{
			lefttop.y = lt.y + m_cyCell*(i+1);
			bottomright = lefttop;
			bottomright.x = m_viewSize.cx - m_nRightMargin;
			
			pDC->MoveTo(lefttop);
			pDC->LineTo(bottomright);
			CRect tr;
			CDBVariant fdv;
			CString fv;
			for(int j=0;j<=nColNum; j++)
			{
				tr.SetRect(m_nLeftMargin+m_cxCell * j, lefttop.y - m_cyCell, m_nLeftMargin+m_cxCell*(j+1), lefttop.y);
				if(j == 0)
				{
					fv.Format("%ld", i+1);
				}
				else
				{
				    //p->GetFieldValue(j-1,fdv);
					CODBCFieldInfo ff;
					p->GetODBCFieldInfo(j-1, ff);
					switch(ff.m_nSQLType)
					{
					case 11:
						p->GetFieldValue(j-1,fdv);
						fv.Format("%d年%d月%d日", fdv.m_pdate->year, fdv.m_pdate->month, fdv.m_pdate->day);
						break;
					default:
						p->GetFieldValue(j-1,fv);
						break;
					}
				}
				pDC->DrawText(fv, &tr, DT_SINGLELINE|DT_CENTER|DT_VCENTER);
			}
			p->MoveNext();
		}
		p->Close();			
	}*/
void CQueryView::DrawPrinter(CDC *pDC)
{
	CDocument* pDoc = GetDocument();

	/*int cxPrint, cyPrint;
	cxPrint = pDC->GetDeviceCaps(HORZRES);
	cyPrint = pDC->GetDeviceCaps(VERTRES);

	int cxlog, cylog;
	cxlog = pDC->GetDeviceCaps(LOGPIXELSX);
	cylog = pDC->GetDeviceCaps(LOGPIXELSY);

	pDC->SetMapMode(MM_ANISOTROPIC);
	pDC->SetWindowExt(m_viewSize);
	pDC->SetViewportExt(cxPrint, cyPrint);*/

	pDC->SetMapMode(MM_LOENGLISH);
	if(m_wrs.IsOpen())
	{
		DrawTitle(pDC);
		DrawBody(pDC);
		DrawFooter(pDC);
	}
}
/*  CDocument* pDoc = GetDocument();
	this->QueryRecordset();
	CString tt;

	CRecordset *p = NULL;//&m_rs;

	int nColNum;

	if(p->IsOpen())
	{
	    nColNum = p->GetODBCFieldCount();
		long nRecordCnt = m_nRecordCnt, i;
		m_viewSize.cx = (nColNum+1)*m_cxHeader+m_nLeftMargin +m_nRightMargin;
		m_viewSize.cy = (nRecordCnt)*m_cyCell+m_cyHeader+m_nTopMargin+m_nBottomMargin;
		CSize page = CSize(0,10 * m_cyCell);
		CSize line = CSize(0, 1 * m_cyCell);
		this->SetScrollSizes(MM_TEXT,m_viewSize, page, line);

		if(m_bIsFstPage)
		{
		    CRect ttr(m_nLeftMargin, m_nTopLineGap- 80, (nColNum+1)*m_cxHeader+m_nLeftMargin, m_nTopLineGap-30);
		    pDC->SelectObject(&m_ftTitle);
		    pDC->SetTextColor(RGB(0,0,0));
		    pDC->DrawText(m_sTitle, &ttr, DT_SINGLELINE|DT_CENTER|DT_VCENTER);

		    CRect dtr(m_nLeftMargin, m_nTopLineGap- 30, m_nLeftMargin + 150, m_nTopLineGap);
	    	CFont datefont;
    		datefont.CreatePointFont(100, "黑体");
		
    		pDC->SelectObject(&datefont);
	    	pDC->SetTextColor(RGB(0,0,0));
	    	CTime ct = CTime::GetCurrentTime();
	    	CString tstr;
    		tstr.Format("日期: %d年%d月%d日", ct.GetYear(), ct.GetMonth(), ct.GetDay());
	    	pDC->DrawText(tstr, &dtr, DT_SINGLELINE|DT_CENTER|DT_VCENTER);

	    	CRect usr((nColNum+1)*m_cxHeader+m_nLeftMargin - 200, m_nTopLineGap- 30, (nColNum+1)*m_cxHeader+m_nLeftMargin, m_nTopLineGap);
	    	CFont userfont;
	    	userfont.CreatePointFont(100, "黑体");
		
	    	pDC->SelectObject(&userfont);
    		pDC->SetTextColor(RGB(0,0,0));
    		CMainFrame *pM = (CMainFrame*)AfxGetApp()->GetMainWnd();
    		tstr.Format("操作员: %s", pM->m_cLoginUser.m_sUserName);
	    	pDC->DrawText(tstr, &usr, DT_SINGLELINE|DT_CENTER|DT_VCENTER);
		}

		CPoint frm(m_nLeftMargin, m_nTopLineGap);
		CPoint to(m_viewSize.cx - m_nRightMargin,m_nTopLineGap);
		pDC->MoveTo(frm);
		pDC->LineTo(to);

	    frm = CPoint(m_nLeftMargin, m_nTopMargin);
	    to = CPoint(m_viewSize.cx - m_nRightMargin,m_nTopMargin);
		pDC->MoveTo(frm);
		pDC->LineTo(to);

	    frm = CPoint(m_nLeftMargin, m_nTopMargin+m_cyHeader);
		to  = CPoint(m_viewSize.cx - m_nRightMargin,m_nTopMargin+m_cyHeader);

		pDC->MoveTo(frm);
		pDC->LineTo(to);
		CBrush brush;
		brush.CreateStockObject(LTGRAY_BRUSH);
		pDC->SelectObject(&brush);
		CODBCFieldInfo cfi;
		pDC->SetBkMode(TRANSPARENT);
		CString colname;

		pDC->SelectObject(&m_ftHeader);
		pDC->SetTextColor(RGB(0,0,0));
		
		for(i = 0;i<=nColNum; i++)
		{
			pDC->MoveTo(m_nLeftMargin+m_cxHeader*i, m_nTopMargin);
			pDC->LineTo(m_nLeftMargin+m_cxHeader*i, m_viewSize.cy - m_nBottomMargin);
			CRect rc(m_nLeftMargin+m_cxHeader*i+1, m_nTopMargin+1, m_nLeftMargin+m_cxHeader*i+m_cxHeader, m_nTopMargin+m_cyHeader);
			pDC->FillRect(rc,&brush);
			//pDC->Draw3dRect(&rc, RGB(255, 255, 255), RGB(128,128,128));
			if(i==0)
			{
				colname = "行号";
			}
			else
			{
				ASSERT(p->IsOpen());
			    p->GetODBCFieldInfo(i-1, cfi);
				colname = cfi.m_strName;
			}
			pDC->DrawText(colname, &rc, DT_SINGLELINE|DT_CENTER|DT_VCENTER);
			
		}
		pDC->MoveTo(m_nLeftMargin+m_cxHeader*(nColNum+1), m_nTopMargin);
		pDC->LineTo(m_nLeftMargin+m_cxHeader*(nColNum+1), m_viewSize.cy - m_nBottomMargin);

		
		CPoint lefttop(m_nLeftMargin, m_nTopMargin + m_cyHeader), bottomright;
		CPoint lt = lefttop;


		pDC->SelectObject(&m_ftRecord);
		pDC->SetTextColor(RGB(0,0,255));


		i = (m_nCurPgeLastRecord - m_nRecordsPerPage) >= 0 ? (m_nCurPgeLastRecord - m_nRecordsPerPage) : 0;
		if(i==0)
			nRecordCnt = m_nCurPgeLastRecord;
		else
		    nRecordCnt = i + m_nRecordsPerPage;

		ASSERT(nRecordCnt<m_nRecordCnt);

		for(int k=0; k<i; k++)
		{
			ASSERT(!p->IsEOF());
			p->MoveNext();
		}
		TRACE("from %d, to %d, tot %d, perpage %d", i, nRecordCnt, m_nRecordCnt, m_nRecordsPerPage);

		for(;i<nRecordCnt && !p->IsEOF(); i++)
		{
			lefttop.y = lt.y + m_cyCell*(i+1);
			bottomright = lefttop;
			bottomright.x = m_viewSize.cx - m_nRightMargin;
			
			pDC->MoveTo(lefttop);
			pDC->LineTo(bottomright);
			CRect tr;
			CDBVariant fdv;
			CString fv;
			for(int j=0;j<=nColNum; j++)
			{
				tr.SetRect(m_nLeftMargin+m_cxCell * j, lefttop.y - m_cyCell, m_nLeftMargin+m_cxCell*(j+1), lefttop.y);
				if(j == 0)
				{
					fv.Format("%ld", i+1);
				}
				else
				{
				    //p->GetFieldValue(j-1,fdv);
					CODBCFieldInfo ff;
					p->GetODBCFieldInfo(j-1, ff);
					switch(ff.m_nSQLType)
					{
					case 11:
						p->GetFieldValue(j-1,fdv);
						fv.Format("%d年%d月%d日", fdv.m_pdate->year, fdv.m_pdate->month, fdv.m_pdate->day);
						break;
					default:
						p->GetFieldValue(j-1,fv);
						break;
					}
				}
				pDC->DrawText(fv, &tr, DT_SINGLELINE|DT_CENTER|DT_VCENTER);
			}
			p->MoveNext();
		}

		p->Close();			
	}

	this->QueryFootRecordSet();
	if(m_footRs.IsOpen())
	{
		p = &m_footRs;
		int nfootColNum = p->GetODBCFieldCount();
		CString colname, colvalue, txt;
		CSize size;
		CODBCFieldInfo cfi;
		pDC->MoveTo(m_nLeftMargin, m_nRecordCnt*m_cyCell+m_cyHeader+m_nTopMargin+m_nBottomLineGap);
		pDC->LineTo(m_nLeftMargin+m_cxHeader*(nColNum+1), m_nRecordCnt*m_cyCell+m_cyHeader+m_nTopMargin+m_nBottomLineGap);
		
		for(int i = 0;i<nfootColNum; i++)
		{
			pDC->SelectObject(m_ftFooter);
			int det = (m_cxHeader*(nColNum+1))/nfootColNum;
			int left = m_nLeftMargin+(nfootColNum-i-1)*det;
			int top = m_nRecordCnt*m_cyCell+m_cyHeader+m_nTopMargin+m_nBottomLineGap;
			int right = m_nLeftMargin+m_cxHeader*nColNum;
			int bottom = (m_nRecordCnt+1)*m_cyCell+m_cyHeader+m_nTopMargin+m_nBottomLineGap;
			CRect rc(left,top,left+det,bottom);
			p->GetODBCFieldInfo(i, cfi);
			colname = cfi.m_strName;
			p->GetFieldValue(colname, colvalue);
			txt = colname+": "+colvalue;
			pDC->DrawText(txt, &rc, DT_SINGLELINE|DT_LEFT|DT_VCENTER);
		}
	}*/
void CQueryView::DrawTitle(CDC *pDC)
{
	if(!pDC->IsPrinting() && m_wrs.IsOpen())
	{
		pDC->SelectObject(&m_ftTitle);
		pDC->SetTextColor(RGB(0,0,0));
		CRect tr = CRect(m_nLeftMargin, -(m_nTopMargin - m_cyHeader), m_viewSize.cx-m_nRightMargin, -m_nTopMargin);
		pDC->DrawText(m_sTitle, &tr, DT_SINGLELINE|DT_CENTER|DT_VCENTER);

		CRect dtr(m_nLeftMargin, -m_nTopMargin, m_nLeftMargin + 2*m_cxCell, -(m_nTopMargin + m_nTopLineGap));
		
		pDC->SelectObject(&m_ftHeaderNote);
		pDC->SetTextColor(RGB(0,0,0));
		CTime ct = CTime::GetCurrentTime();
		CString tstr;
		tstr.Format("日期: %d年%d月%d日", ct.GetYear(), ct.GetMonth(), ct.GetDay());
		pDC->DrawText(tstr, &dtr, DT_SINGLELINE|DT_LEFT|DT_VCENTER);

		CRect usr((m_wrs.GetColumnCount()+1)*m_cxHeader+m_nLeftMargin - m_cxCell, -m_nTopMargin, (m_wrs.GetColumnCount()+1)*m_cxHeader+m_nLeftMargin, -(m_nTopMargin+m_nTopLineGap));
		
		pDC->SelectObject(&m_ftHeaderNote);
		pDC->SetTextColor(RGB(0,0,0));
		CMainFrame *pM = (CMainFrame*)AfxGetApp()->GetMainWnd();
		tstr.Format("操作员: %s", pM->m_cLoginUser.m_sUserName);
		pDC->DrawText(tstr, &usr, DT_SINGLELINE|DT_RIGHT|DT_VCENTER);
		pDC->MoveTo(m_nLeftMargin, -(m_nTopMargin + m_nTopLineGap));
		pDC->LineTo((m_wrs.GetColumnCount()+1)*m_cxCell+m_nLeftMargin, -(m_nTopMargin + m_nTopLineGap));
	}
	else if(pDC->IsPrinting() && m_wrs.IsOpen())
	{
		pDC->SelectObject(&m_ftTitle);
		pDC->SetTextColor(RGB(0,0,0));
		CRect tr = CRect(m_nLeftMargin, -(m_nTopMargin - m_cyHeader), m_viewSize.cx-m_nRightMargin, -m_nTopMargin);
		//pDC->Rectangle(&tr);
		pDC->DrawText(m_sTitle, &tr, DT_SINGLELINE|DT_CENTER|DT_VCENTER);

		CRect dtr(m_nLeftMargin, -m_nTopMargin, m_nLeftMargin + 2*m_cxCell, -(m_nTopMargin + m_nTopLineGap));

		
		pDC->SelectObject(&m_ftHeaderNote);
		pDC->SetTextColor(RGB(0,0,0));
		CTime ct = CTime::GetCurrentTime();
		CString tstr;
		tstr.Format("日期: %d年%d月%d日", ct.GetYear(), ct.GetMonth(), ct.GetDay());
		pDC->DrawText(tstr, &dtr, DT_SINGLELINE|DT_LEFT|DT_VCENTER);

		CRect usr((m_wrs.GetColumnCount()+1)*m_cxHeader+m_nLeftMargin - 2*m_cxCell, -m_nTopMargin, (m_wrs.GetColumnCount()+1)*m_cxHeader+m_nLeftMargin, -(m_nTopMargin+m_nTopLineGap));

		
		pDC->SelectObject(&m_ftHeaderNote);
		pDC->SetTextColor(RGB(0,0,0));
		CMainFrame *pM = (CMainFrame*)AfxGetApp()->GetMainWnd();
		tstr.Format("操作员: %s", pM->m_cLoginUser.m_sUserName);
		pDC->DrawText(tstr, &usr, DT_SINGLELINE|DT_RIGHT|DT_VCENTER);
		pDC->MoveTo(m_nLeftMargin, -(m_nTopMargin + m_nTopLineGap));
		pDC->LineTo((m_wrs.GetColumnCount()+1)*m_cxCell+m_nLeftMargin, -(m_nTopMargin + m_nTopLineGap));
	}

}
/*-------------------------------
   |
   |
   |m_nTopMargin
   |
---------------------------
   | m_nTopLineGap
----------------------
   |
   |m_cyHeader
------------------
   |
   |
   |Records
   .
   .
   .
-------------------
   | m_nBottomLineGap
-------------------
   |
   |
   |m_nBottomMargin
------------------------------------*/
void CQueryView::DrawBody(CDC *pDC)
{
	if(!pDC->IsPrinting() && m_wrs.IsOpen())
	{
		//Draw column title.
		CBrush brush;
		CODBCFieldInfo cfi;
		CString colname;
		CPoint lt = CPoint(m_nLeftMargin, -(m_nTopMargin + m_nTopLineGap)), pt;

		brush.CreateStockObject(LTGRAY_BRUSH);
		pDC->SelectObject(&brush);
		pDC->SetBkMode(TRANSPARENT);


		pDC->SelectObject(&m_ftHeader);
		pDC->SetTextColor(RGB(0,0,0));
		
		pt = lt;
		for(int i = 0;i<=m_wrs.GetColumnCount(); i++)
		{
			pDC->MoveTo(pt);
			pDC->LineTo(pt.x, -(-pt.y + m_cyHeader + m_wrs.GetRecordCount()*m_cyCell));
			CRect rc(pt.x+1, -(-pt.y+1), pt.x + m_cxHeader, -(-pt.y + m_cyHeader));
			pDC->FillRect(rc,&brush);
			//pDC->Draw3dRect(&rc, RGB(255, 255, 255), RGB(128,128,128));
			if(i==0)
			{
				colname = "行号";
			}
			else
			{
			    m_wrs.GetColHeader(i-1, colname);
			}
			pDC->DrawText(colname, &rc, DT_SINGLELINE|DT_CENTER|DT_VCENTER);
			pt.Offset(m_cxHeader,0);
		}
        pDC->MoveTo(lt.x + (m_wrs.GetColumnCount()+1)*m_cxHeader, lt.y);
		pDC->LineTo(lt.x + (m_wrs.GetColumnCount()+1)*m_cxHeader, -(-lt.y + m_cyHeader + m_wrs.GetRecordCount()*m_cyCell));

		pt = lt;
		pDC->MoveTo(pt);
		pDC->LineTo(pt.x + (m_wrs.GetColumnCount()+1)*m_cxHeader, pt.y);
		pt.Offset(0, -m_cyHeader);
		pDC->MoveTo(pt);
		pDC->LineTo(pt.x + (m_wrs.GetColumnCount()+1)*m_cxHeader, pt.y);

		//Draw records.
		lt.Offset(0, -m_cyHeader);
		CRect valRt(lt.x, lt.y, lt.x + m_cxCell, -(-lt.y + m_cyCell));
		CString value;
		int cnt = 0;
		pDC->SelectObject(&m_ftRecord);
		pDC->SetTextColor(RGB(0,0,255));

		for( i=0;i<m_wrs.GetRecordCount();i++)
		{
			cnt++;
			for(int j=0;j<=m_wrs.GetColumnCount();j++)
			{
				if(j == 0)
				{
					value.Format("%d", cnt);
				}
				else
				{
				    m_wrs.GetValue(i,j-1,value);
				}
				pDC->DrawText(value, &valRt, DT_SINGLELINE|DT_CENTER|DT_VCENTER);
				valRt.OffsetRect(m_cxCell, 0);
			}
			valRt.OffsetRect(-m_cxCell*(m_wrs.GetColumnCount() + 1), -m_cyCell);
			pDC->MoveTo(valRt.left, valRt.top);
			pDC->LineTo(valRt.left + m_cxCell*(m_wrs.GetColumnCount() + 1), valRt.top);
		}
	}
	else if(pDC->IsPrinting() && m_wrs.IsOpen())
	{
		//Draw column title.
		CBrush brush;
		CODBCFieldInfo cfi;
		CString colname;
		CPoint lt = CPoint(m_nLeftMargin, -(m_nTopMargin + m_nTopLineGap)), pt;

		brush.CreateStockObject(LTGRAY_BRUSH);
		pDC->SelectObject(&brush);
		pDC->SetBkMode(TRANSPARENT);


		pDC->SelectObject(&m_ftHeader);
		pDC->SetTextColor(RGB(0,0,0));
		
		pt = lt;
		for(int i = 0;i<=m_wrs.GetColumnCount(); i++)
		{
			pDC->MoveTo(pt);
			pDC->LineTo(pt.x, -(-pt.y + m_cyHeader));
			CRect rc(pt.x+1, -(-pt.y+1), pt.x + m_cxHeader, -(-pt.y + m_cyHeader));
			pDC->FillRect(rc,&brush);
			//pDC->Draw3dRect(&rc, RGB(255, 255, 255), RGB(128,128,128));
			if(i==0)
			{
				colname = "行号";
			}
			else
			{
			    m_wrs.GetColHeader(i-1, colname);
			}
			pDC->DrawText(colname, &rc, DT_SINGLELINE|DT_CENTER|DT_VCENTER);
			pt.Offset(m_cxHeader,0);
		}
        pDC->MoveTo(lt.x + (m_wrs.GetColumnCount()+1)*m_cxHeader, lt.y);
		pDC->LineTo(lt.x + (m_wrs.GetColumnCount()+1)*m_cxHeader, -(-lt.y + m_cyHeader));

		pt = lt;
		pDC->MoveTo(pt);
		pDC->LineTo(pt.x + (m_wrs.GetColumnCount()+1)*m_cxHeader, pt.y);
		pt.Offset(0, -m_cyHeader);
		pDC->MoveTo(pt);
		pDC->LineTo(pt.x + (m_wrs.GetColumnCount()+1)*m_cxHeader, pt.y);

		//Draw records.
		lt.Offset(0, -m_cyHeader);
		CRect valRt(lt.x, lt.y, lt.x + m_cxCell, -(-lt.y + m_cyCell));
		CString value;
		int cnt = 0;
		pDC->SelectObject(&m_ftRecord);
		pDC->SetTextColor(RGB(0,0,255));

		for( i=0;i<m_wrs.GetRecordCount();i++)
		{
			cnt++;
			for(int j=0;j<=m_wrs.GetColumnCount();j++)
			{
				if(j == 0)
				{
					value.Format("%d", cnt);
				}
				else
				{
				    m_wrs.GetValue(i,j-1,value);
				}
				pDC->DrawText(value, &valRt, DT_SINGLELINE|DT_CENTER|DT_VCENTER);
				pDC->MoveTo(valRt.left, valRt.top);
				pDC->LineTo(valRt.left, valRt.top+(-m_cyCell));
				valRt.OffsetRect(m_cxCell, 0);
			}
			pDC->MoveTo(valRt.left, valRt.top);
			pDC->LineTo(valRt.left, valRt.top+(-m_cyCell));

			valRt.OffsetRect(-m_cxCell*(m_wrs.GetColumnCount() + 1), -m_cyCell);
			pDC->MoveTo(valRt.left, valRt.top);
			pDC->LineTo(valRt.left + m_cxCell*(m_wrs.GetColumnCount() + 1), valRt.top);
		}
	}
}

void CQueryView::DrawFooter(CDC *pDC)
{
    if(!pDC->IsPrinting() && m_wrs.IsOpen())
	{
		CPoint lt = CPoint(m_nLeftMargin, -(m_nTopMargin + m_nTopLineGap +m_cyHeader +m_cyCell *m_wrs.GetRecordCount() + m_nBottomLineGap));
		pDC->MoveTo(lt);
		lt.Offset((m_wrs.GetColumnCount()+1)*m_cxCell, 0);
		pDC->LineTo(lt);
		int top = -(m_nTopMargin + m_nTopLineGap +m_cyHeader +m_cyCell *m_wrs.GetRecordCount() + m_nBottomLineGap);

		CRect valRt(m_nLeftMargin, top, m_cxCell * 2, top-m_cyCell);
		CString value;
		for(int j=0;j<m_wfootRs.GetColumnCount();j++)
		{
			m_wfootRs.GetColHeader(j, value);
			pDC->DrawText(value, &valRt, DT_SINGLELINE|DT_LEFT|DT_VCENTER);
			valRt.OffsetRect(m_cxCell, 0);
		    m_wfootRs.GetValue(0,j,value);
		    pDC->DrawText(value, &valRt, DT_SINGLELINE|DT_LEFT|DT_VCENTER);
			valRt.OffsetRect(m_cxCell, 0);
		}
	}
	else if(pDC->IsPrinting() && m_wrs.IsOpen())
	{
		CPoint lt = CPoint(m_nLeftMargin, -(m_nTopMargin + m_nTopLineGap +m_cyHeader +m_cyCell *m_wrs.GetRecordCount() + m_nBottomLineGap));
		pDC->MoveTo(lt);
		lt.Offset((m_wrs.GetColumnCount()+1)*m_cxCell, 0);
		pDC->LineTo(lt);
		int top = -(m_nTopMargin + m_nTopLineGap +m_cyHeader +m_cyCell *m_wrs.GetRecordCount() + m_nBottomLineGap);

		CRect valRt(m_nLeftMargin, top, m_cxCell * 2, top-m_cyCell);
		CString value;
		for(int j=0;j<m_wfootRs.GetColumnCount();j++)
		{
			m_wfootRs.GetColHeader(j, value);
			pDC->DrawText(value, &valRt, DT_SINGLELINE|DT_LEFT|DT_VCENTER);
			valRt.OffsetRect(m_cxCell, 0);
		    m_wfootRs.GetValue(0,j,value);
		    pDC->DrawText(value, &valRt, DT_SINGLELINE|DT_LEFT|DT_VCENTER);
			valRt.OffsetRect(m_cxCell, 0);
		}
	}
}

void CQueryView::OnFilePrintPreview() 
{
	// TODO: Add your command handler code here
	CView::OnFilePrintPreview();
}
