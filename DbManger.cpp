// DbManger.cpp: implementation of the CDbManger class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "HRS.h"
#include "DbManger.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CDatabase CDbManger::db;

CDbManger::CDbManger()
{

}

CDbManger::~CDbManger()
{

}



CDatabase & CDbManger::GetDbConnection()
{
	if(!db.IsOpen())
	{
		OpenConnection();
	}

	return db;
}

BOOL CDbManger::OpenConnection()
{
	if(db.IsOpen())
	{
		return TRUE;
	}
	else
	{
		db.OpenEx(_T( "DSN=DGG;" ), CDatabase::useCursorLib | CDatabase::noOdbcDialog);
	}

	if(db.IsOpen())
	{
		return TRUE;
	}
	else
	{
		return FALSE;
	}
}

BOOL CDbManger::CloseDBConnection()
{
	if(db.IsOpen())
	{
		db.Close();
	}
	if(db.IsOpen())
	{
		return FALSE;
	}
	else
	{
		return TRUE;
	}
}

BOOL CDbManger::ExecuteSQL(CString &sql)
{
	if(CDbManger::db.IsOpen())
	{
		CDbManger::db.ExecuteSQL(sql);
	}
	else
	{
		if(OpenConnection())
		{
			CDbManger::db.ExecuteSQL(sql);
			return TRUE;
		}
		else
		{
			AfxMessageBox("不能打开数据库连接!",MB_OK|MB_ICONERROR);
			return FALSE;
		}
	}
	return TRUE;
}

CString CDbManger::GenerateNewID(CString IDName)
{
	CString IDtext ="" ;
			if(!db.IsOpen())
			{
				OpenConnection();
			}

			if(db.IsOpen())
			{
			
				CRecordset rs (&db), *prs = NULL;

				CString strCmd = "select prefix, curval, totlen from seq where id = '"+IDName+"' ";

				//::AfxMessageBox(strCmd);

				rs.Open(CRecordset::forwardOnly, strCmd);
				if(!rs.IsEOF())
				{
					CString prefix, curval, totlen;
					int val, tl;
					prs=&rs;
					prs->GetFieldValue("prefix", prefix);
					prs->GetFieldValue("curval", curval);
					prs->GetFieldValue("totlen", totlen);

					prefix.TrimLeft();
					prefix.TrimRight();

					val = atoi(curval) + 1;
					tl  = atoi(totlen);

					curval.Format("%d", val);
					for(int i=0;i<tl-curval.GetLength()-prefix.GetLength();i++)
					{
						curval = "0"+ curval;
					}

					IDtext = prefix + curval;

					db.ExecuteSQL("update seq set curval = "+curval+" where id = '"+IDName+"' ");

					rs.Close();

					//MessageBox("prefix is"+prefix);
					//MessageBox("curval is"+curval);
				}
				else
				{
					::AfxMessageBox("生成序号:"+IDName+" 失败！");
				}
			}
			return IDtext;
}

BOOL CDbManger::RePrepareRecordset(CRecordset *m_pSet, CString idcol, CString idvalue)
{
	if(m_pSet->IsOpen())
	{
		m_pSet->Close();
	}
	idvalue.TrimLeft();
	idvalue.TrimRight();
	if(idvalue.GetLength()<=0)
	{
		AfxMessageBox("请先查询，再修改！");
		return FALSE;
	}
	m_pSet->m_strFilter.Format(" %s = '%s'",idcol, idvalue);
	m_pSet->Open();
	//UpdateData(false);
	return TRUE;
}

void CRecordsetWrap::ExecuteSql(CString &sql)
{
	CRecordset rs(&CDbManger::db);
	if(IsOpen())
		Close();
	rs.Open(CRecordset::forwardOnly, sql);
	WrapRecordset(rs);
	rs.Close();
}

void CRecordsetWrap::WrapRecordset(CRecordset &rs)
{
	CODBCFieldInfo cfi;
	CString colname;
	TITLENODE *pColn = NULL,*pPreBother = NULL;

	m_nNumOfCols = rs.GetODBCFieldCount();

	pColsHeader = new TITLENODE*[m_nNumOfCols];

	// Construct Cols.
	for(int i=0;i<m_nNumOfCols;i++)
	{
	    rs.GetODBCFieldInfo(i, cfi);
		pColn = new TITLENODE;
		pColn->colname = cfi.m_strName;
		pColn->pFstValue = NULL;
		pColn->pNextBother = NULL;
		if(pPreBother)
		   pPreBother->pNextBother = pColn;
		pPreBother = pColn;
		pColsHeader[i] = pColn;
	}

	pTablePointer = pColsHeader[0];
	m_nNumOfRecords = 0;

	VALUENODE ***pPreLst = new VALUENODE**[m_nNumOfCols];
	for(i = 0;i<m_nNumOfCols; i++)
	{
		pPreLst[i] = &pColsHeader[i]->pFstValue;
	}

	while(!rs.IsEOF())
	{
		VALUENODE *pPre = NULL;
		for(i=0;i<m_nNumOfCols;i++)
		{
			CODBCFieldInfo ff;
			CDBVariant fdv;
			CString fv;
			rs.GetODBCFieldInfo(i, ff);
			switch(ff.m_nSQLType)
			{
			case 11:
				rs.GetFieldValue(i,fdv);
				fv.Format("%d年%d月%d日", fdv.m_pdate->year, fdv.m_pdate->month, fdv.m_pdate->day);
				break;
			default:
				rs.GetFieldValue(i,fv);
				break;
			}
			fv.TrimLeft();
			fv.TrimRight();
			VALUENODE *pVal = new VALUENODE;
			pVal->pNext = NULL;
			pVal->pNextBother = NULL;
			pVal->value = fv;
			*pPreLst[i] = pVal;
			pPreLst[i] = &pVal->pNext;
			if(pPre)
				pPre->pNextBother = pVal;
			pPre = pVal;
		}
		rs.MoveNext();
		m_nNumOfRecords++;
	}
	free(pPreLst);

	TITLENODE *pCur = pTablePointer;

	TRACE("total Colums: %d, Total Records: %d\n ", m_nNumOfCols, m_nNumOfRecords);
	while(pCur)
	{
		TRACE("ColNam: %s\t",pCur->colname);
		pCur = pCur->pNextBother;
	}
	TRACE("\n");
	VALUENODE *pVCur = pTablePointer->pFstValue;
	while(pVCur)
	{
		VALUENODE *pVNxt = pVCur;
		while(pVNxt)
		{
			TRACE("%s\t",pVNxt->value);
			pVNxt = pVNxt->pNextBother;
		}
		TRACE("\n");
		pVCur = pVCur->pNext;
	}
	TRACE("Finished Out table!");
}

void CRecordsetWrap::Close()
{
	VALUENODE *pVCur = pTablePointer ? pTablePointer->pFstValue : NULL;
	VALUENODE *pVNxt = NULL;
	for(int i=0;i<m_nNumOfCols;i++)
	{
		pVCur = pColsHeader[i]->pFstValue;
		while(pVCur)
		{
			pVNxt = pVCur->pNext;
			free(pVCur);
			pVCur = pVNxt;
		}
		free(pColsHeader[i]);
	}
	pTablePointer = NULL;
}

int CRecordsetWrap::GetColumnCount()
{

	return m_nNumOfCols;

}

int CRecordsetWrap::GetRecordCount()
{

	return m_nNumOfRecords;
}

BOOL CRecordsetWrap::GetColHeader(int idx, CString &colname)
{
	ASSERT(idx>=0 && idx <m_nNumOfCols);
	colname = pColsHeader[idx]->colname;
	return TRUE;
}

void CRecordsetWrap::GetValue(int i, int j, CString &value)
{
	ASSERT(i>=0 && i<m_nNumOfRecords && j>=0 && j< m_nNumOfCols);
	VALUENODE *pVal = pColsHeader[j]->pFstValue;
	int skpcnt = 0;
	while (skpcnt < i)
	{
		pVal = pVal->pNext;
		skpcnt++;
	}
	value = pVal->value;
}
