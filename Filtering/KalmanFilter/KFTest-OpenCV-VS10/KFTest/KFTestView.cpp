
// KFTestView.cpp : implementation of the CKFTestView class
//

#include "stdafx.h"
// SHARED_HANDLERS can be defined in an ATL project implementing preview, thumbnail
// and search filter handlers and allows sharing of document code with that project.
#ifndef SHARED_HANDLERS
#include "KFTest.h"
#endif

#include "KFTestDoc.h"
#include "KFTestView.h"
CKFTestView *pv;

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CKFTestView

IMPLEMENT_DYNCREATE(CKFTestView, CFormView)

BEGIN_MESSAGE_MAP(CKFTestView, CFormView)
	ON_WM_CONTEXTMENU()
	ON_WM_RBUTTONUP()
	ON_BN_CLICKED(IDC_BUTTON1, &CKFTestView::OnBnClickedButton1)
END_MESSAGE_MAP()

// CKFTestView construction/destruction

CKFTestView::CKFTestView()
	: CFormView(CKFTestView::IDD)
{
	// TODO: add construction code here

}

CKFTestView::~CKFTestView()
{
}

void CKFTestView::DoDataExchange(CDataExchange* pDX)
{
	CFormView::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_CHECK1, m_chk_run);
	DDX_Control(pDX, IDC_SLIDER1, m_sld_vel);
	DDX_Control(pDX, IDC_STATIC1, m_info1);
}

BOOL CKFTestView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs

	return CFormView::PreCreateWindow(cs);
}

void CKFTestView::OnInitialUpdate()
{
	CFormView::OnInitialUpdate();
	GetParentFrame()->RecalcLayout();
	ResizeParentToFit();


	pv = this;

	m_wnd1.Create(this);
	pWnd1 = &m_wnd1;

//	RedirectIOToConsole();

	m_sld_vel.SetRange(0,99);

	printf("Ready..\n");

}

void CKFTestView::OnRButtonUp(UINT /* nFlags */, CPoint point)
{
	ClientToScreen(&point);
	OnContextMenu(this, point);
}

void CKFTestView::OnContextMenu(CWnd* /* pWnd */, CPoint point)
{
#ifndef SHARED_HANDLERS
	theApp.GetContextMenuManager()->ShowPopupMenu(IDR_POPUP_EDIT, point.x, point.y, this, TRUE);
#endif
}


// CKFTestView diagnostics

#ifdef _DEBUG
void CKFTestView::AssertValid() const
{
	CFormView::AssertValid();
}

void CKFTestView::Dump(CDumpContext& dc) const
{
	CFormView::Dump(dc);
}

CKFTestDoc* CKFTestView::GetDocument() const // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CKFTestDoc)));
	return (CKFTestDoc*)m_pDocument;
}
#endif //_DEBUG


// CKFTestView message handlers


void CKFTestView::OnBnClickedButton1()
{
	//pWnd1->Init();
	pWnd1->InitKF();
}
