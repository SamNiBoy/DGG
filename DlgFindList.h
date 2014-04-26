#if !defined(AFX_DLGFINDLIST_H__8BAA23A5_B438_49B3_8B55_943D68584379__INCLUDED_)
#define AFX_DLGFINDLIST_H__8BAA23A5_B438_49B3_8B55_943D68584379__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// DlgFindList.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CDlgFindList dialog

class CDlgFindList : public CDialog
{
private:
	CString m_sTableName;
	CString m_sFilter;
	CString m_sDspCol;
	CString m_sIdCol;

	CStringArray m_sList;

public:
	CString m_sSelectedId;
	CString m_sSelectedValue;
// Construction
public:
	CDlgFindList(CString  tn, CString filter, CString dspcol,CString idcol, CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CDlgFindList)
	enum { IDD = IDD_DLG_FIND };
		// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDlgFindList)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CDlgFindList)
	virtual BOOL OnInitDialog();
	virtual void OnOK();
	afx_msg void OnDblclkLstContent();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DLGFINDLIST_H__8BAA23A5_B438_49B3_8B55_943D68584379__INCLUDED_)
