
// SVDTestDoc.cpp : implementation of the CSVDTestDoc class
//

#include "stdafx.h"
#include "SVDTest.h"

#include "SVDTestDoc.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CSVDTestDoc

IMPLEMENT_DYNCREATE(CSVDTestDoc, CDocument)

BEGIN_MESSAGE_MAP(CSVDTestDoc, CDocument)
END_MESSAGE_MAP()


// CSVDTestDoc construction/destruction

CSVDTestDoc::CSVDTestDoc()
{
	// TODO: add one-time construction code here

}

CSVDTestDoc::~CSVDTestDoc()
{
}

BOOL CSVDTestDoc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;

	// TODO: add reinitialization code here
	// (SDI documents will reuse this document)

	return TRUE;
}




// CSVDTestDoc serialization

void CSVDTestDoc::Serialize(CArchive& ar)
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


// CSVDTestDoc diagnostics

#ifdef _DEBUG
void CSVDTestDoc::AssertValid() const
{
	CDocument::AssertValid();
}

void CSVDTestDoc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif //_DEBUG


// CSVDTestDoc commands
