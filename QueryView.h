#if !defined(AFX_QUERYVIEW_H__A1DC1AC1_0E1D_44F1_B8C1_50D0FA8E8D7F__INCLUDED_)
#define AFX_QUERYVIEW_H__A1DC1AC1_0E1D_44F1_B8C1_50D0FA8E8D7F__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// QueryView.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CQueryView view

class CQueryView : public CScrollView
{
protected:
	CQueryView();
	DECLARE_DYNCREATE(CQueryView)

// Attributes
public:
	CString m_sQuerySql;
	CString m_sFilter;
	CRecordsetWrap m_wrs;
	int m_nRecordCnt;

	int m_cxHeader, m_cyHeader, m_cxCell,m_cyCell;
	int m_nTopMargin;
	int m_nTopLineGap;
	int m_nLeftMargin;
	int m_nRightMargin;
	int m_nBottomMargin;
	int m_nBottomLineGap;

// Operations
public:
	void DrawFooter(CDC *pDC);
	void DrawBody(CDC *pDC);
	void DrawTitle(CDC *pDC);
	void DrawPrinter(CDC *pDC);
	void DrawScreen(CDC *pDC);
	int m_nPageHeigh;
	void QueryFootRecordSet();
	CRecordsetWrap m_wfootRs;
	CString m_sFootFilter;
	CString m_sFootSql;
	CFont m_ftRecord;
	CFont m_ftFooter;
	CFont m_ftFooterNote;
	CFont m_ftHeader;
	CFont m_ftHeaderNote;
	CFont m_ftTitle;
	CSize m_viewSize;
	void SetPrintPara(CPrintInfo *pInfo);
	void Init();
	CString m_sTitle;
	void QueryRecordset();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CQueryView)
	public:
	virtual void OnPrepareDC(CDC* pDC, CPrintInfo* pInfo = NULL);
	protected:
	virtual void OnDraw(CDC* pDC);      // overridden to draw this view
	virtual void OnInitialUpdate();     // first time after construct
	virtual BOOL OnPreparePrinting(CPrintInfo* pInfo);
	virtual void OnBeginPrinting(CDC* pDC, CPrintInfo* pInfo);
	//}}AFX_VIRTUAL

// Implementation
protected:
	virtual ~CQueryView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

	// Generated message map functions
	//{{AFX_MSG(CQueryView)
	afx_msg void OnIdPreviewPrint();
	afx_msg void OnContextMenu(CWnd* pWnd, CPoint point);
	afx_msg void OnUpdateMenuPrint(CCmdUI* pCmdUI);
	afx_msg void OnFilePrintDirect();
	afx_msg void OnFilePrintPreview();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_QUERYVIEW_H__A1DC1AC1_0E1D_44F1_B8C1_50D0FA8E8D7F__INCLUDED_)
