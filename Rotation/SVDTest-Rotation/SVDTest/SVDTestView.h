
// SVDTestView.h : interface of the CSVDTestView class
//


#pragma once

#include "DecomposeRotation.h"
class CSVDTestView : public CView
{
protected: // create from serialization only
	CSVDTestView();
	DECLARE_DYNCREATE(CSVDTestView)

// Attributes
public:
	CSVDTestDoc* GetDocument() const;

// Operations
public:

	DecomposeRotation m_dr;
// Overrides
public:
	virtual void OnDraw(CDC* pDC);  // overridden to draw this view
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
protected:
	virtual BOOL OnPreparePrinting(CPrintInfo* pInfo);
	virtual void OnBeginPrinting(CDC* pDC, CPrintInfo* pInfo);
	virtual void OnEndPrinting(CDC* pDC, CPrintInfo* pInfo);

// Implementation
public:
	virtual ~CSVDTestView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	afx_msg void OnFilePrintPreview();
	afx_msg void OnRButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnContextMenu(CWnd* pWnd, CPoint point);
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnRButtonDown(UINT nFlags, CPoint point);
};

#ifndef _DEBUG  // debug version in SVDTestView.cpp
inline CSVDTestDoc* CSVDTestView::GetDocument() const
   { return reinterpret_cast<CSVDTestDoc*>(m_pDocument); }
#endif

