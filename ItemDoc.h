// BoxDoc.h: interface for the CItemDoc class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_ITEMDOC_H__8EAED7A5_F47F_4430_B0B4_C18498BFE9F5__INCLUDED_)
#define AFX_ITEMDOC_H__8EAED7A5_F47F_4430_B0B4_C18498BFE9F5__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
#include"itemset.h"

class CItemDoc : public CDocument
{
protected:
	DECLARE_DYNCREATE(CItemDoc)
public:
	CItemSet m_ItemSet;
public:
	CItemDoc();
	virtual ~CItemDoc();

protected:

	DECLARE_MESSAGE_MAP()
};

#endif // !defined(AFX_BOXDOC_H__8EAED7A5_F47F_4430_B0B4_C18498BFE9F5__INCLUDED_)
