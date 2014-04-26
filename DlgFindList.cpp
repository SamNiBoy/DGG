// DlgFindList.cpp : implementation file
//

#include "stdafx.h"
#include "hrs.h"
#include "DlgFindList.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDlgFindList dialog


CDlgFindList::CDlgFindList(CString  tn, CString filter, CString dspcol,CString idcol,  CWnd* pParent /*=NULL*/)
: m_sTableName(tn), m_sFilter(filter), m_sDspCol(dspcol), m_sIdCol(idcol), CDialog(CDlgFindList::IDD, pParent)
{
	m_sSelectedId = "";
	m_sSelectedValue = "";
	//{{AFX_DATA_INIT(CDlgFindList)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}


void CDlgFindList::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDlgFindList)
		// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CDlgFindList, CDialog)
	//{{AFX_MSG_MAP(CDlgFindList)
	ON_LBN_DBLCLK(IDC_LST_CONTENT, OnDblclkLstContent)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDlgFindList message handlers

BOOL CDlgFindList::OnInitDialog() 
{
	CDialog::OnInitDialog();
	CRecordset rs(&CDbManger::db), *p;
	p = &rs;
	CString sql = "select " + m_sIdCol+" as idcol, "+m_sDspCol+ " as dspcol from " + m_sTableName + " where "+ m_sFilter;

	rs.Open(CRecordset::forwardOnly, sql);
	CString id, dsp;
	CListBox *pLst = (CListBox*)GetDlgItem(IDC_LST_CONTENT);
	int idx = 0;
	while(!p->IsEOF())
	{
		p->GetFieldValue("idcol", id);
		p->GetFieldValue("dspcol", dsp);
		id.TrimLeft();
		id.TrimRight();
		dsp.TrimLeft();
		dsp.TrimRight();
		m_sList.Add(id);
		pLst->AddString(dsp);
		//pLst->SetItemData(idx,idx);
		idx++;
		p->MoveNext();
	}

	p->Close();
	pLst->SetCurSel(0);

	// TODO: Add extra initialization here
	
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CDlgFindList::OnOK() 
{
	// TODO: Add extra validation here
	CListBox *pLst = (CListBox*)GetDlgItem(IDC_LST_CONTENT);
	int idx;
	idx = pLst->GetCurSel();
	if (idx < 0)
	{
		CDialog::OnCancel();
		return;
	}
	pLst->GetText(idx, m_sSelectedValue);
	m_sSelectedValue.TrimLeft();
	m_sSelectedValue.TrimRight();

	m_sSelectedId = m_sList[idx];
	m_sSelectedId.TrimLeft();
	m_sSelectedId.TrimRight();
	CDialog::OnOK();
}

void CDlgFindList::OnDblclkLstContent() 
{
	// TODO: Add your control notification handler code here
	OnOK();
}
