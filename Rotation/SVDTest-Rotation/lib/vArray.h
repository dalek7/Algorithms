#ifndef __VARRAY__
#define __VARRAY__
 
/*
	vLibrary Plan 
	 : vArray
	 : vString
	 : vMat
	 : CPTRList

    Compatible vlibrary series(vArray compatible to CArray).
	 :   WIN32 for Windows, otherwise for Linux.		  

	Written by J.Yang in 2005		  
	emailto: egregory@kaist.ac.kr 
*/

template<class TYPE,class ARG_TYPE>
class vArray 
{
public:
		vArray();
		~vArray();
public:
		int		GetSize()	{ return m_nSize;}
		int		Add( ARG_TYPE ,BOOL bOverwrite=FALSE);
		int		Overwrite( ARG_TYPE);
		int		AddNew(ARG_TYPE);
		TYPE	operator[](int nIndex) const;
		TYPE&	operator[](int nIndex);
		TYPE	GetAt(int nIndex);// const;
		TYPE	Last() const;
		TYPE	First()	const;
		TYPE&	ElementAt(int nIndex);
		void	RemoveAt(int nIndex, int nCount = 1);
		void	InsertAt(int nIndex, ARG_TYPE newElement, int nCount = 1);

		void	InsertAt(int nIndex, vArray* pArr);
		void	RemoveAll();

protected:
		void	SetErr(char*);
		void	ClearErr();
		void	DisplayErr();
		
protected:
		TYPE*	m_pData;
		int		m_nSize;
		char	stErr[100];
		BOOL	bError;
};


template<class TYPE> 
void Construct(TYPE *p,int n)
{	
	/*
	memset((void*)p, 0, n * sizeof(TYPE));

	// then call the constructor(s)
	for (; n--; p++)
		::new((void*)p) TYPE;
		*/
}

template<class TYPE> 
void Destruct(TYPE *p,int n)
{	
	/*
	memset((void*)p, 0, n * sizeof(TYPE));

	// then call the constructor(s)
	for (; n--; p++)
		::new((void*)p) TYPE;
	*/
}

/*
#ifdef CString
template<> 
void Construct<CString>(CString *p,int n)
{
	for (; n--; ++p)
	memcpy(p,&afxEmptyString, sizeof(*p));
}
#endif
*/

#ifndef vString
#include "vString.h"
template<> 
void inline Construct<vString>(vString *p,int n)
{
	for (; n--; ++p)
	      *p	= vString();
}

template<>
void inline Destruct<vString>(vString *p,int n)
{
	for (; n--; ++p)
		p->~vString();
}

#endif

template<class TYPE,class ARG_TYPE>
vArray<TYPE,ARG_TYPE>::vArray()
{
	m_pData = NULL;
	m_nSize = 0;
	bError	= FALSE;
}

template<class TYPE,class ARG_TYPE>
vArray<TYPE,ARG_TYPE>::~vArray()
{
	RemoveAll();
}

template<class TYPE,class ARG_TYPE>
int vArray<TYPE,ARG_TYPE>::Add(ARG_TYPE arg, BOOL bOverwrite)
{
	int nCurrent = m_nSize;
	if ( m_pData==NULL )
	{
		m_pData = (TYPE*) new BYTE[ sizeof(TYPE) ];
		memset( m_pData,0,sizeof(TYPE));
		Construct<TYPE>(m_pData,1);
		m_pData[m_nSize] = arg;
		m_nSize++;
	}
	else
	{
		TYPE *pNew = (TYPE*)new BYTE[sizeof(TYPE)*(m_nSize+1)];
		memset( pNew,0,sizeof(TYPE)*(m_nSize+1));
		memmove( pNew, m_pData,sizeof(TYPE)*m_nSize);
		delete [](BYTE*)m_pData;
		Construct<TYPE>(&pNew[m_nSize],1);
		pNew[m_nSize]	= arg;
		m_pData = pNew;
		m_nSize++;
	}
	
	return nCurrent;
}

template<class TYPE,class ARG_TYPE>
int vArray<TYPE,ARG_TYPE>::Overwrite(ARG_TYPE arg)
{
	int nCurrent = m_nSize;
	if ( m_pData==NULL )
	{
		Add(arg);
	}
	else
	{
		for (int i=0;i<m_nSize;i++)
		if ( m_pData[i]==arg)
			return i;

		TYPE *pNew = (TYPE*)new BYTE[sizeof(TYPE)*(m_nSize+1)];
		memset( pNew,0,sizeof(TYPE)*(m_nSize+1));
		memmove( pNew, m_pData,sizeof(TYPE)*m_nSize);
		delete [](BYTE*)m_pData;
		Construct<TYPE>(&pNew[m_nSize],1);
		pNew[m_nSize]	= arg;
		m_pData = pNew;
		m_nSize++;
	}
	
	return nCurrent;
}

template<class TYPE,class ARG_TYPE>
int vArray<TYPE,ARG_TYPE>::AddNew(ARG_TYPE arg)
{
	for (int i=0;i<GetSize();i++)
		if ( m_pData[i]==arg)	return m_nSize;

	int nCurrent = m_nSize;
	if ( m_pData==NULL )
	{
		m_pData = (TYPE*) new BYTE[ sizeof(TYPE) ];
		memset( m_pData,0,sizeof(TYPE));
		Construct<TYPE>(m_pData,1);
		m_pData[m_nSize] = arg;
		m_nSize++;
	}
	else
	{
		int a = sizeof(TYPE);
		TYPE *pNew = (TYPE*)new BYTE[sizeof(TYPE)*(m_nSize+1)];
		memset( pNew,0,sizeof(TYPE)*(m_nSize+1));
		memmove( pNew, m_pData,sizeof(TYPE)*m_nSize);
		delete [](BYTE*)m_pData;
		Construct<TYPE>(&pNew[m_nSize],1);
		pNew[m_nSize]	= arg;
		m_pData = pNew;
		m_nSize++;
	}
	
	return nCurrent;
}

template<class TYPE,class ARG_TYPE>
TYPE vArray<TYPE,ARG_TYPE>::GetAt(int nIndex) //const
{
	if ( nIndex>=0 && nIndex<m_nSize)	;
	else SetErr("Array size is mismatched!");
	
	return m_pData[nIndex];
}

template<class TYPE,class ARG_TYPE>
TYPE vArray<TYPE,ARG_TYPE>::Last() const
{
	return m_pData[m_nSize-1];
}

template<class TYPE,class ARG_TYPE>
TYPE vArray<TYPE,ARG_TYPE>::First() const
{
	return m_pData[0];
}

template<class TYPE,class ARG_TYPE>
TYPE& vArray<TYPE,ARG_TYPE>::ElementAt(int nIndex)
{
	if ( nIndex>=0 && nIndex<m_nSize)	;
	else SetErr("Array size is mismatched!");
	
	return m_pData[nIndex];
}

template<class TYPE,class ARG_TYPE>
void vArray<TYPE,ARG_TYPE>::SetErr(char *p)
{
	strcpy( stErr,p);
	bError	= TRUE;

	DisplayErr();
}

template<class TYPE,class ARG_TYPE>
void vArray<TYPE,ARG_TYPE>::DisplayErr()
{
#ifdef WIN32
#ifdef ASSERT
	ASSERT(FALSE);
#endif
#else
	printf( "%s",stErr);
#endif
	ClearErr();
}

template<class TYPE,class ARG_TYPE>
void vArray<TYPE,ARG_TYPE>::ClearErr()
{
	stErr[0]	= 0;
	bError	= FALSE;
}

template<class TYPE,class ARG_TYPE>
TYPE vArray<TYPE,ARG_TYPE>::operator[](int nIndex) const
{
	return GetAt(nIndex);
}

template<class TYPE,class ARG_TYPE>
TYPE& vArray<TYPE,ARG_TYPE>::operator[](int nIndex){return ElementAt(nIndex);}

template<class TYPE, class ARG_TYPE>
void vArray<TYPE, ARG_TYPE>::RemoveAt(int nIndex, int nCount)
{
	
	if ( nIndex<0 || nIndex>=m_nSize )	SetErr("Array size is mismatched.");
	if ( nCount<0 )						SetErr("Array count should be nonzero value.");

	TYPE *pNew = (TYPE*)new BYTE[sizeof(TYPE)*(m_nSize-nCount)];
	memset( pNew,0,sizeof(TYPE)*(m_nSize-nCount));
	memmove( pNew,m_pData,sizeof(TYPE)*nIndex);
	Destruct<TYPE>( &m_pData[nIndex],nCount);
	memmove( &pNew[nIndex],&m_pData[nIndex+nCount],sizeof(TYPE)*(m_nSize-nCount-nIndex) );
	delete[] (BYTE*)m_pData;
	m_pData = pNew;
	m_nSize	-=nCount;
}

template<class TYPE, class ARG_TYPE>
void vArray<TYPE, ARG_TYPE>::InsertAt(int nIndex, ARG_TYPE arg, int nCount )
{
	if ( nIndex<0 || nIndex>m_nSize )	SetErr("Array size is mismatched.");
	if ( nCount<0 )						SetErr("Array count should be nonzero value.");

	TYPE *pNew = (TYPE*)new BYTE[sizeof(TYPE)*(m_nSize+nCount)];
	memset( pNew,0,sizeof(TYPE)*(m_nSize+nCount));
	memmove( pNew,m_pData,sizeof(TYPE)*nIndex);
	//Construct<TYPE>(&pNew[m_nSize],nCount);
	memmove( &pNew[nIndex+nCount],&m_pData[nIndex],sizeof(TYPE)*(m_nSize-nIndex) );

	for ( int i=0;i<nCount;i++)
	{
		Construct<TYPE>(&pNew[nIndex+i],1);
		pNew[nIndex+i]	= arg;
	}
		//memmove( &pNew[nIndex+i],&arg,sizeof(TYPE));
	delete [](BYTE*)m_pData;
	m_pData = pNew;
	m_nSize	+=nCount;
}

template<class TYPE, class ARG_TYPE>
void vArray<TYPE, ARG_TYPE>::InsertAt(int nIndex,vArray *pArr )
{
	if ( nIndex<0 || nIndex>m_nSize )	SetErr("Array size is mismatched.");
	
	int nCount	= pArr->GetSize();
	if ( nCount<0 )				SetErr("Array count should be nonzero value.");

	// just remove a range
	TYPE *pNew = (TYPE*)new TYPE[sizeof(TYPE)*(m_nSize+nCount)];
	memmove( pNew,m_pData,sizeof(TYPE)*nIndex);

	for ( int i=0;i<pArr->GetSize();i++)
		memmove( &pNew[nIndex+i],*pArr[i],sizeof(TYPE));
	
	memmove( &pNew[nIndex+nCount],&m_pData[nIndex],sizeof(TYPE)*(m_nSize-nIndex) );
	delete[] (BYTE*)m_pData;
	m_pData = pNew;
	m_nSize	+=nCount;
}

template<class TYPE,class ARG_TYPE>
void vArray<TYPE,ARG_TYPE>::RemoveAll()
{
	Destruct( m_pData,m_nSize);
	m_nSize	= 0;
	if ( m_pData )	delete[](BYTE*)m_pData;
	m_pData = NULL;
}

#endif
