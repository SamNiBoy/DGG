// SaleDoc.h: interface for the CSaleDoc class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_SaleDOC_H__8EAED7A5_F47F_4430_B0B4_C18498BFE9F5__INCLUDED_)
#define AFX_SaleDOC_H__8EAED7A5_F47F_4430_B0B4_C18498BFE9F5__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
#include"Saleset.h"

class CSaleDoc : public CDocument
{
protected:
	DECLARE_DYNCREATE(CSaleDoc)
public:
	CSaleSet m_SaleSet;
public:
	CSaleDoc();
	virtual ~CSaleDoc();

protected:

	DECLARE_MESSAGE_MAP()
};

#endif // !defined(AFX_SaleDOC_H__8EAED7A5_F47F_4430_B0B4_C18498BFE9F5__INCLUDED_)
