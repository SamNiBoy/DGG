#if !defined(AFX_STATICBOX_H__47DA471D_AF63_4800_BF2D_1B5DA125630B__INCLUDED_)
#define AFX_STATICBOX_H__47DA471D_AF63_4800_BF2D_1B5DA125630B__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// StaticBox.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CStaticBox window
typedef enum{
		CUSTOMER,
		BOX,
		ITEM,
		SALE,
		USER,
		MONEY
	}BOXTYPE;
class CStaticBox : public CStatic
{

// Construction
public:
	CStaticBox();
	CStaticBox(BOXTYPE bt);

// Attributes
public:
   BOXTYPE bt;
   bool m_bIsMouseInBox;
// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CStaticBox)
	public:
	virtual BOOL Create(LPCTSTR lpszClassName, LPCTSTR lpszWindowName, DWORD dwStyle, const RECT& rect, CWnd* pParentWnd, UINT nID, CCreateContext* pContext = NULL);
	//}}AFX_VIRTUAL

// Implementation
public:
	void SetOutBitmap();
	void SetInBitmap();
	virtual ~CStaticBox();

	// Generated message map functions
protected:
	//{{AFX_MSG(CStaticBox)
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	afx_msg void OnClicked();
	afx_msg void OnCaptureChanged(CWnd *pWnd);
	afx_msg BOOL OnSetCursor(CWnd* pWnd, UINT nHitTest, UINT message);
	afx_msg void OnNcMouseMove(UINT nHitTest, CPoint point);
	afx_msg void OnKillFocus(CWnd* pNewWnd);
	//}}AFX_MSG
	void OnStaticCustomer();
	void OnStaticBox();
	void OnStaticItem();
	void OnStaticSale();
	void OnStaticUser();
	void OnStaticMoney();
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_STATICBOX_H__47DA471D_AF63_4800_BF2D_1B5DA125630B__INCLUDED_)
