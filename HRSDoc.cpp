// HRSDoc.cpp : implementation of the CCUSTOMERDoc class
//

#include "stdafx.h"
#include "HRS.h"

#include "HRSSet.h"
#include "HRSDoc.h"
#include "logindlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CCUSTOMERDoc

IMPLEMENT_DYNCREATE(CCUSTOMERDoc, CDocument)

BEGIN_MESSAGE_MAP(CCUSTOMERDoc, CDocument)
	//{{AFX_MSG_MAP(CCUSTOMERDoc)
		// NOTE - the ClassWizard will add and remove mapping macros here.
		//    DO NOT EDIT what you see in these blocks of generated code!
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CCUSTOMERDoc construction/destruction

CCUSTOMERDoc::CCUSTOMERDoc()
{
	// TODO: add one-time construction code here

}

CCUSTOMERDoc::~CCUSTOMERDoc()
{
}

BOOL CCUSTOMERDoc::OnNewDocument()
{

/*	if(!((CHRSApp*)::AfxGetApp())->m_bLogin_flg)
	{
		CLoginDlg dlg;
		dlg.DoModal();
		if(!dlg.m_bSuccess)
		{
			return FALSE;
		}
	}
*/
	if (!CDocument::OnNewDocument())
		return FALSE;

	// TODO: add reinitialization code here
	// (SDI documents will reuse this document)
	

	return TRUE;
}



/////////////////////////////////////////////////////////////////////////////
// CCUSTOMERDoc serialization

void CCUSTOMERDoc::Serialize(CArchive& ar)
{
	if (ar.IsStoring())
	{
		// TODO: add storing code here
	}
	else
	{
		// TODO: add loading code here
	}
}

/////////////////////////////////////////////////////////////////////////////
// CCUSTOMERDoc diagnostics

#ifdef _DEBUG
void CCUSTOMERDoc::AssertValid() const
{
	CDocument::AssertValid();
}

void CCUSTOMERDoc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CCUSTOMERDoc commands
