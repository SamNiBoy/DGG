// HRSView.cpp : implementation of the CCUSTOMERView class
//

#include "stdafx.h"
#include "HRS.h"
#include "afxwin.h"
#include "HRSSet.h"
#include "HRSDoc.h"
#include "HRSView.h"
#include "dbmanger.h"
#include "DlgFindList.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CCUSTOMERView

IMPLEMENT_DYNCREATE(CCUSTOMERView, CRecordView)

BEGIN_MESSAGE_MAP(CCUSTOMERView, CRecordView)
	//{{AFX_MSG_MAP(CCUSTOMERView)
	ON_BN_CLICKED(IDC_BTN_MODIFY, OnBtnModify)
	ON_BN_CLICKED(IDC_BTN_ADD, OnBtnAdd)
	ON_BN_CLICKED(IDC_BTN_DEL, OnBtnDel)
	ON_BN_CLICKED(IDC_BTN_CLEAR, OnBtnClear)
	ON_BN_CLICKED(IDC_BTN_SEARCH_BY_NAME, OnBtnSearchByName)
	ON_WM_CTLCOLOR()
	ON_BN_CLICKED(IDC_BTN_UPLOAD_PIC, OnBtnUploadPic)
	ON_BN_CLICKED(IDC_BTN_CUSTOMER_QUERY, OnBtnCustomerQuery)
	//}}AFX_MSG_MAP
	// Standard printing commands
	ON_COMMAND(ID_FILE_PRINT, CRecordView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, CRecordView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, CRecordView::OnFilePrintPreview)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CCUSTOMERView construction/destruction

CCUSTOMERView::CCUSTOMERView()
	: CRecordView(CCUSTOMERView::IDD)
{
	//{{AFX_DATA_INIT(CCUSTOMERView)
	m_pSet = NULL;
	m_sSearch_by_Name = _T("");
	//}}AFX_DATA_INIT
	// TODO: add construction code here
}

CCUSTOMERView::~CCUSTOMERView()
{
}

void CCUSTOMERView::DoDataExchange(CDataExchange* pDX)
{
	CRecordView::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CCUSTOMERView)
	DDX_Control(pDX, IDC_CHK_CUSTOMER_ITEM, m_cIncludeItem);
	DDX_Control(pDX, IDC_CHK_CUSTOMER_CUSTOMER, m_cIncludeCustomer);
	DDX_Control(pDX, IDC_CHK_CUSTOMER_BOX, m_cIncludeBox);
	DDX_Control(pDX, IDC_CHK_CURCUSTOMER, m_cCurCustomer);
	DDX_Text(pDX, IDC_EDT_SEARCH_BY_NAME, m_sSearch_by_Name);
	DDX_Text(pDX, IDC_EDT_CUSTOMERID, m_pSet->m_sCustomerId);
	DDX_Text(pDX, IDC_EDT_CUSTOMERNAME, m_pSet->m_sCustomerName);
	DDX_Text(pDX, IDC_EDT_CUSTOMERSEX, m_pSet->m_sCustomerSex);
	DDX_Text(pDX, IDC_EDT_CUSTOMERAGE, m_pSet->m_iCustomerAge);
	DDX_Text(pDX, IDC_EDT_CUSTOMERLVL, m_pSet->m_iCustomerLevel);
	DDX_Text(pDX, IDC_EDT_CUSTOMERTEL, m_pSet->m_sCustomerTelphone);
	DDX_Text(pDX, IDC_EDT_CUSTOMEREMAIL, m_pSet->m_sCustomerEmail);
	DDX_Text(pDX, IDC_EDT_CUSTOMERADDRESS, m_pSet->m_sCustomerAddress);
	DDX_Text(pDX, IDC_EDT_CUSTOMERDES, m_pSet->m_sCustomerDescription);
	DDX_DateTimeCtrl(pDX, IDC_DATETIMEPICKER_JOINDATE, m_pSet->m_dCustomerJoinDate);
	//}}AFX_DATA_MAP
}

BOOL CCUSTOMERView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs
	

	return CRecordView::PreCreateWindow(cs);
	//cs.style &= ~WS_THICKFRAME;
}

void CCUSTOMERView::OnInitialUpdate()
{
	m_pSet = &GetDocument()->m_hRSSet;
	CSize s(1000,1000);
	this->SetScrollSizes(MM_TEXT,s);
	CRecordView::OnInitialUpdate();
	OnBtnClear();
	m_cCurCustomer.SetCheck(true);
	m_cIncludeCustomer.SetCheck(true);
	m_cIncludeBox.SetCheck(true);
	m_cIncludeItem.SetCheck(true);
	//UpdateData(false);
}

/////////////////////////////////////////////////////////////////////////////
// CCUSTOMERView printing

BOOL CCUSTOMERView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// default preparation
	return DoPreparePrinting(pInfo);
}

void CCUSTOMERView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add extra initialization before printing
}

void CCUSTOMERView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add cleanup after printing
}

/////////////////////////////////////////////////////////////////////////////
// CCUSTOMERView diagnostics

#ifdef _DEBUG
void CCUSTOMERView::AssertValid() const
{
	CRecordView::AssertValid();
}

void CCUSTOMERView::Dump(CDumpContext& dc) const
{
	CRecordView::Dump(dc);
}

CCUSTOMERDoc* CCUSTOMERView::GetDocument() // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CCUSTOMERDoc)));
	return (CCUSTOMERDoc*)m_pDocument;
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CCUSTOMERView database support
CRecordset* CCUSTOMERView::OnGetRecordset()
{
	return m_pSet;
}


/////////////////////////////////////////////////////////////////////////////
// CCUSTOMERView message handlers

void CCUSTOMERView::OnBtnModify() 
{
	// TODO: Add your control notification handler code here
	if(!m_pSet->IsOpen() || m_pSet->IsEOF())
	{
		AfxMessageBox("请先查询，再修改！");
		return;
	}
	if(!m_pSet->CanUpdate())
	{
		this->MessageBox("Can't update record!");
		return;
	}
	else
	{
		if(CheckRequired())
		{
		    m_pSet->Edit();
		    UpdateData();
	        m_pSet->Update();
			CString customerid;
			GetDlgItemText(IDC_EDT_CUSTOMERID, customerid);
			CDbManger::RePrepareRecordset(m_pSet, "customerid", customerid);
			UpdateData(false);
		}
	}
	
}

void CCUSTOMERView::OnBtnAdd() 
{
	// TODO: Add your control notification handler code here
	if(!m_pSet->IsOpen())
	{
		m_pSet->Open();
	}

	if(!m_pSet->CanAppend())
	{
		this->MessageBox("Can't add record!");
		return;
	}
	else
	{
		if(CheckRequired())
		{
		    m_pSet->AddNew();
		    UpdateData();
			m_pSet->m_sCustomerId=CDbManger::GenerateNewID("CUSTID");
			UpdateData(false);
		    m_pSet->Update();
			CString customerid;
			GetDlgItemText(IDC_EDT_CUSTOMERID, customerid);
			CDbManger::RePrepareRecordset(m_pSet, "customerid", customerid);
			UpdateData(false);
		}
	}
}

void CCUSTOMERView::OnBtnDel() 
{
	// TODO: Add your control notification handler code here
	if(!m_pSet->IsOpen() || m_pSet->IsEOF())
	{
		AfxMessageBox("请先查询，再删除！");
		return;
	}
	if(!m_pSet->CanUpdate())
	{
		this->MessageBox("Can't delete record!");
		return;
	}
	else
	{
		if(AfxMessageBox("确认删除该客户？",MB_YESNO|MB_ICONEXCLAMATION) == IDYES)
		{
	        m_pSet->Delete();
		    OnBtnClear();
			m_pSet->Close();
		}
	}
}

void CCUSTOMERView::OnBtnClear() 
{
	// TODO: Add your control notification handler code here
    m_pSet->Close();
	SetDlgItemText(IDC_EDT_CUSTOMERID,"");
	SetDlgItemText(IDC_EDT_CUSTOMERNAME,"");
	SetDlgItemText(IDC_EDT_CUSTOMERSEX,"");
	SetDlgItemText(IDC_EDT_CUSTOMERAGE,"");
	SetDlgItemText(IDC_EDT_CUSTOMERLVL,"");
	SetDlgItemText(IDC_EDT_CUSTOMERTEL,"");
	SetDlgItemText(IDC_EDT_CUSTOMEREMAIL,"");
	SetDlgItemText(IDC_EDT_CUSTOMERADDRESS,"");
	SetDlgItemText(IDC_EDT_CUSTOMERDES,"");
}


void CCUSTOMERView::OnBtnSearchByName() 
{
	// TODO: Add your control notification handler code here
	//UpdateData();
    CString name, filter;
	this->GetDlgItemText(IDC_EDT_SEARCH_BY_NAME, name);
	//CString sql = "select * from customer";

	if(name.GetLength()>0)
	{
		filter = " name like '%"+name+"%'";
	}
	else
	{
		filter = " 1 = 1 ";
	}

	CDlgFindList finder("customer", filter, "name", "customerid", this);

	if(finder.DoModal() == IDCANCEL)
		return;

	m_pSet->m_strFilter = " customerid = '" + finder.m_sSelectedId +"'";

	m_pSet->Close();
	m_pSet->Open();
	//TRACE("get %d rows\n", m_pSet->GetRecordCount());
	//MessageBox(m_pSet->GetSQL());
	
	
	if(!m_pSet->IsEOF())
	{
		//m_sCustomerName = m_pSet->m_sCustomerName;
		m_pSet->MoveFirst();
		UpdateData(FALSE);
	}
	if(m_pSet->IsEOF())
	{
		this->MessageBox("没有找到记录!");
	}	
}

BOOL CCUSTOMERView::IsSelected(const CObject* pDocItem) const
{
	// TODO: Add your specialized code here and/or call the base class
	
	return CRecordView::IsSelected(pDocItem);
}

void CCUSTOMERView::OnDraw(CDC* pDC) 
{
	// TODO: Add your specialized code here and/or call the base class
}

HBRUSH CCUSTOMERView::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor) 
{
	HBRUSH hbr = CRecordView::OnCtlColor(pDC, pWnd, nCtlColor);
	
	// TODO: Change any attributes of the DC here
	//pDC->SetTextColor(RGB(255,0,0));
	/*CRect r;
	pWnd->GetClientRect(&r);

	CBrush b=RGB(0,255,0),*pOld;
	pOld=pDC->SelectObject(&b);
	pDC->Rectangle(&r);
	pDC->SelectObject(pOld);*/
	
	// TODO: Return a different brush if the default is not desired
	return hbr;
}

void CCUSTOMERView::OnBtnUploadPic() 
{
	// TODO: Add your control notification handler code here
/*	TCHAR szFilters[]=_T("bmp files(*.bmp)");

	CFileDialog dlg(TRUE,_T("bmp"),_T("*.bmp"),OFN_FILEMUSTEXIST|OFN_HIDEREADONLY,szFilters);
	if(dlg.DoModal()==IDOK)
	{
		CString filename=dlg.GetPathName();
		this->MessageBox(filename);
        CFile	fileImage;
        CFileStatus	fileStatus;
//Store pic to db
        fileImage.Open(filename, CFile::modeRead);
        fileImage.GetStatus(fileStatus);

		m_pSet->Edit();

        m_pSet->m_Pic.m_dwDataLength = fileStatus.m_size;

        HGLOBAL hGlobal		= GlobalAlloc(GPTR,fileStatus.m_size);
        m_pSet->m_Pic.m_hData = GlobalLock(hGlobal);

        fileImage.ReadHuge(m_pSet->m_Pic.m_hData,fileStatus.m_size);

        m_pSet->SetFieldDirty(&m_pSet->m_Pic);
        m_pSet->SetFieldNull(&m_pSet->m_Pic,FALSE);
		if(m_pSet->CanUpdate())
		{
            m_pSet->Update();
		}
		else
			this->MessageBox("Can't update image!");

        GlobalUnlock(hGlobal);
		fileImage.Close();
*/
/*Load pic from db:
// To restore image from db table
CdbImages   dbImages(&theApp.m_DB);
CString     strFileName = pList->GetItemText(nIndex,0);
dbImages.m_strFilter.Format("BLOBName = '%s'",strFileName);
try
{
    dbImages.Open();
    if  (dbImages.IsEOF())
        AfxMessageBox("Unable to get image from db");
    else
    {
        char    tmpPath[_MAX_PATH+1];
        GetTempPath(_MAX_PATH,tmpPath);

        strFileName.Insert(0,tmpPath);
        
        CFile	outFile(strFileName,CFile::modeCreate|CFile::modeWrite);
        LPSTR	buffer = (LPSTR)GlobalLock(dbImages.m_BLOBImage.m_hData);
        outFile.WriteHuge(buffer,dbImages.m_BLOBImage.m_dwDataLength);
        GlobalUnlock(dbImages.m_BLOBImage.m_hData);
        outFile.Close();

        theApp.OpenDocumentFile(strFileName);
    }

    dbImages.Close();

}
catch(CException* pE)
{
    pE->ReportError();
    pE->Delete();
    return;
}
*/

	//Draw pic
	/*m_hbmp = (HBITMAP)::LoadImage(NULL,"E:\\dev\\pic\\son.bmp",IMAGE_BITMAP,0,0,LR_LOADFROMFILE);
	
	if(!m_hbmp)
	{
		this->MessageBox("load bmp failed!");
	}
	else
	{ 
		m_cStaff_pic.SetBitmap(m_hbmp);
		m_cStaff_pic.MoveWindow(350,100,100,100);

	}

	}*/
	
}


BOOL CCUSTOMERView::CheckRequired()
{
	CString name, sex, age;
	this->GetDlgItemText(IDC_EDT_CUSTOMERNAME, name);
	this->GetDlgItemText(IDC_EDT_CUSTOMERSEX, sex);
	this->GetDlgItemText(IDC_EDT_CUSTOMERAGE, age);

	name.TrimLeft();
	name.TrimRight();

	if(!name.GetLength())
	{
		AfxMessageBox("请输入姓名!", MB_OK|MB_ICONINFORMATION);
		return FALSE;
	}
	sex.TrimLeft();
	sex.TrimRight();
	if(!sex.GetLength() || sex.GetLength()>2)
	{
		AfxMessageBox("性别输入错误!", MB_OK|MB_ICONINFORMATION);
		return FALSE;
	}
	age.TrimLeft();
	age.TrimRight();
	if(!age.GetLength() || atoi(age)>100 || atoi(age)<1)
	{
		AfxMessageBox("年龄输入错误!", MB_OK|MB_ICONINFORMATION);
		return FALSE;
	}

	return TRUE;

}


void CCUSTOMERView::OnBtnCustomerQuery() 
{
	// TODO: Add your control notification handler code here
    CCUSTOMERDoc *pDoc=GetDocument();
	POSITION pos = pDoc->GetFirstViewPosition();
	CView *pV = NULL;
	while(pos)
	{
		pV = pDoc->GetNextView(pos);
		if(pV->IsKindOf(RUNTIME_CLASS(CQueryView)))
			break;
	}
	CQueryView *pQV = (CQueryView*) pV;


	if (BuildSql(pQV))
	{
	    TRACE("sql: %s \n where: %s\n", pQV->m_sQuerySql, pQV->m_sFilter);
		pQV->QueryRecordset();
	    pDoc->UpdateAllViews(this);
	}
	CSplitterWnd *pSp=(CSplitterWnd*)this->GetParent();
	//pSp->DoScrollBy(this, CSize(500,0));
	//pSp->SetColumnInfo(1, 500, 100);
	//pSp->RecalcLayout();
}

BOOL CCUSTOMERView::BuildSql(CQueryView *pQV)
{

	pQV->m_sQuerySql = "";
	pQV->m_sFilter = " where 1=1 ";
	CString customerfilter = " and 1=1 ";

	if(m_cCurCustomer.GetCheck())
	{
		CString cusid;
		GetDlgItemText(IDC_EDT_CUSTOMERID, cusid);
		cusid.TrimLeft();
		cusid.TrimRight();
		if(cusid.GetLength()<=0)
		{
			AfxMessageBox("请输入当前客户编号!", MB_OK|MB_ICONERROR);
			return FALSE;
		}
		else 
			customerfilter = " and c.customerid = '" + cusid+"'";
	}
	

	if(m_cIncludeBox.GetCheck() && m_cIncludeItem.GetCheck())
	{
		pQV->m_sQuerySql =  "select c.customerid 客户编号, " 
			                "       c.name 客户姓名, b.boxid 货位编号, b.rentprice 租赁价格, "
							"       i.itemid 物品编号,i.name 物品名称, i.qty 物品数量, i.price 物品价格, i.discnt 销售折扣 "
							"  from customer c "
							"  left join box b "
							"    on b.ownerid = c.customerid "
							"  left join item i "
							"    on c.customerid = i.ownerid ";

		pQV->m_sFilter = " where 1=1 "+ customerfilter;
		pQV->m_sTitle = "客户综合信息";
	}
	else if(m_cIncludeItem.GetCheck())
	{
		pQV->m_sQuerySql = "select c.customerid 客户编号, c.name 客户姓名,"
							"      i.itemid 物品编号,i.name 物品名称, i.qty 物品数量, i.price 物品价格 "
							"  from customer c "
							"  left join item i "
							"    on c.customerid = i.ownerid ";

		pQV->m_sFilter = " where 1 = 1 "+ customerfilter;
		pQV->m_sTitle = "客户物品信息";
	}
	else if(m_cIncludeBox.GetCheck())
	{
		pQV->m_sQuerySql =  "select c.name 客户姓名, b.boxid 货位编号, " 
			                "      b.rentprice 租赁价格 "
							"  from customer c "
							"  left join box b "
							"    on b.ownerid = c.customerid ";

		pQV->m_sFilter = " where 1 = 1 " + customerfilter;
		pQV->m_sTitle = "客户租赁信息";
	}
	else
	{
		pQV->m_sQuerySql = "select c.customerid 客户编号, " 
			                "      c.name 客户姓名, "
							"      c.tel 客户电话 "
							"  from customer c";

		pQV->m_sFilter = " where 1 = 1 "+ customerfilter;
		pQV->m_sTitle = "客户基本信息";
	}
        pQV->m_sFootSql = "select count(*) 客户数 from customer c ";
		pQV->m_sFootFilter = " where 1=1 " + customerfilter;	
	return TRUE;
}
