
// SVDTestDoc.h : interface of the CSVDTestDoc class
//


#pragma once


class CSVDTestDoc : public CDocument
{
protected: // create from serialization only
	CSVDTestDoc();
	DECLARE_DYNCREATE(CSVDTestDoc)

// Attributes
public:

// Operations
public:

// Overrides
public:
	virtual BOOL OnNewDocument();
	virtual void Serialize(CArchive& ar);

// Implementation
public:
	virtual ~CSVDTestDoc();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	DECLARE_MESSAGE_MAP()
};


