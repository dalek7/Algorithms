
// SVDTestView.cpp : implementation of the CSVDTestView class
//

#include "stdafx.h"
#include "SVDTest.h"

#include "SVDTestDoc.h"
#include "SVDTestView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CSVDTestView

IMPLEMENT_DYNCREATE(CSVDTestView, CView)

BEGIN_MESSAGE_MAP(CSVDTestView, CView)
	// Standard printing commands
	ON_COMMAND(ID_FILE_PRINT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, &CSVDTestView::OnFilePrintPreview)
	ON_WM_RBUTTONDOWN()
END_MESSAGE_MAP()

// CSVDTestView construction/destruction

CSVDTestView::CSVDTestView()
{
	// TODO: add construction code here

}

CSVDTestView::~CSVDTestView()
{
}

BOOL CSVDTestView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs

	return CView::PreCreateWindow(cs);
}

// CSVDTestView drawing

void CSVDTestView::OnDraw(CDC* /*pDC*/)
{
	CSVDTestDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	// TODO: add draw code for native data here
}


// CSVDTestView printing


void CSVDTestView::OnFilePrintPreview()
{
	AFXPrintPreview(this);
}

BOOL CSVDTestView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// default preparation
	return DoPreparePrinting(pInfo);
}

void CSVDTestView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add extra initialization before printing
}

void CSVDTestView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add cleanup after printing
}

void CSVDTestView::OnRButtonUp(UINT nFlags, CPoint point)
{
	ClientToScreen(&point);
	OnContextMenu(this, point);
}

void CSVDTestView::OnContextMenu(CWnd* pWnd, CPoint point)
{
	theApp.GetContextMenuManager()->ShowPopupMenu(IDR_POPUP_EDIT, point.x, point.y, this, TRUE);
}


// CSVDTestView diagnostics

#ifdef _DEBUG
void CSVDTestView::AssertValid() const
{
	CView::AssertValid();
}

void CSVDTestView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CSVDTestDoc* CSVDTestView::GetDocument() const // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CSVDTestDoc)));
	return (CSVDTestDoc*)m_pDocument;
}
#endif //_DEBUG


// CSVDTestView message handlers

void CSVDTestView::OnRButtonDown(UINT nFlags, CPoint point)
{
	// TODO: Add your message handler code here and/or call default

	Dbg("aA");

	m_dr.LoadData("../data/_A.txt","../data/_B.txt","../data/_R.txt","../data/_t.txt");
	m_dr.Calc();


	CView::OnRButtonDown(nFlags, point);
}
