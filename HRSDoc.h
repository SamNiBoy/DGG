// HRSDoc.h : interface of the CCUSTOMERDoc class
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_HRSDOC_H__75B20930_C845_43E0_A637_74B32FD2B269__INCLUDED_)
#define AFX_HRSDOC_H__75B20930_C845_43E0_A637_74B32FD2B269__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
#include "HRSSet.h"


class CCUSTOMERDoc : public CDocument
{
protected: // create from serialization only
	CCUSTOMERDoc();
	DECLARE_DYNCREATE(CCUSTOMERDoc)

// Attributes
public:
	CCUSTOMERSet m_hRSSet;

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CCUSTOMERDoc)
	public:
	virtual BOOL OnNewDocument();
	virtual void Serialize(CArchive& ar);
	//}}AFX_VIRTUAL

// Implementation
public:

	virtual ~CCUSTOMERDoc();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	//{{AFX_MSG(CCUSTOMERDoc)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_HRSDOC_H__75B20930_C845_43E0_A637_74B32FD2B269__INCLUDED_)
