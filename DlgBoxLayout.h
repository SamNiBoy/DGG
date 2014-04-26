#if !defined(AFX_DLGBOXLAYOUT_H__98592760_8009_4318_9175_58115AF15C04__INCLUDED_)
#define AFX_DLGBOXLAYOUT_H__98592760_8009_4318_9175_58115AF15C04__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// DlgBoxLayout.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CDlgBoxLayout dialog

class CDlgBoxLayout : public CDialog
{
public:
// Construction
public:
	void SetBoxItems();
	BOOL CheckRequired();
	CDlgBoxLayout(CString &boxid, CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CDlgBoxLayout)
	enum { IDD = IDD_ITEMLAYOUT_FORM };
	CListBox	m_cLstBox;
	CString	m_boxid;
	CString	m_itemid;
	CString	m_itemname;
	int		m_qty;
	double	m_price;
	double	m_totprice;
	int		m_boxitemqty;
	double	m_boxtotprice;
	CString	m_ownerid;
	double	m_discnt;
	CString	m_description;
	CTime	m_expdte;
	CTime	m_mandte;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDlgBoxLayout)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CDlgBoxLayout)
	afx_msg void OnBtnLayoutItemquery();
	afx_msg void OnChangeEdtLayoutItemqty();
	afx_msg void OnBtnLayoutPuttobox();
	virtual BOOL OnInitDialog();
	afx_msg void OnBtnLayoutItemclear();
	afx_msg void OnBtnLayoutClearbox();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DLGBOXLAYOUT_H__98592760_8009_4318_9175_58115AF15C04__INCLUDED_)
