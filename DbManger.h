// DbManger.h: interface for the CDbManger class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_DBMANGER_H__9DF32C67_1B30_4796_9FF5_5ECC79CA4B51__INCLUDED_)
#define AFX_DBMANGER_H__9DF32C67_1B30_4796_9FF5_5ECC79CA4B51__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef _DBMANGER
#define _DBMANGER



typedef struct valuenode
{
	CString value;
	struct valuenode *pNext;
	struct valuenode *pNextBother;
}VALUENODE;

typedef struct titlenode
{
	CString colname;
	struct valuenode *pFstValue;
	struct titlenode *pNextBother;
}TITLENODE;

class CRecordsetWrap
{
public:
	int m_nNumOfRecords;
	int m_nNumOfCols;
	TITLENODE **pColsHeader;
	TITLENODE *pTablePointer;
public:
	void GetValue(int i, int j, CString &value);
	BOOL GetColHeader(int idx, CString &colname);
	int GetRecordCount();
	int GetColumnCount();
	void Close();
	void WrapRecordset(CRecordset &rs);
	CRecordsetWrap():m_nNumOfRecords(0),m_nNumOfCols(0),pColsHeader(NULL),pTablePointer(NULL)
	{
	}
	BOOL IsOpen(){return pTablePointer != NULL;}
	void ExecuteSql(CString &sql);
	~CRecordsetWrap()
	{
		if(IsOpen())
			Close();
	}
};

class CDbManger
{
public:

static CDatabase db;

private:
	CDbManger();
public:
	static BOOL RePrepareRecordset(CRecordset *m_pSet, CString idcol, CString idvalue);
	static CString GenerateNewID(CString IDName);
	static BOOL ExecuteSQL(CString &sql);
	static BOOL CloseDBConnection();
	static BOOL OpenConnection();
	static CDatabase & GetDbConnection();
	~CDbManger();
};

#endif

#endif // !defined(AFX_DBMANGER_H__9DF32C67_1B30_4796_9FF5_5ECC79CA4B51__INCLUDED_)
