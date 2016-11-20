#include "stdafx.h"
#include "vString.h"

/*
#ifdef _DEBUG
#define new DEBUG_NEW
#endif
*/
#ifndef ABS
#define ABS(a) a>0 ? a:-a
#endif

vString::vString()
{
	InternalInit();	
}

vString::vString( const vString& v)
{
	if ( !v.bTemp)
	{
		InternalInit();	
		Close();

		int n=0;
		if ( v.data )	n	= strlen(v.data);

		Init(n);
		memmove( data,v.data,nLen );
		data[nLen] =0;
		NoTemp();
	}
	else
	{
		data	= v.data;
		nLen	= v.nLen;
		NoTemp();
	}
	//if ( v.bTemp )	v.TempClose(); 
}

vString::vString( char ch)
{
	InternalInit();	
	Close();
	Init(1);
	data[0]	= ch;
	data[1] = 0;
	NoTemp();
}

#ifdef __AFXWIN_H__
vString::vString( CString& st)
{
	InternalInit();	
	Close();
	Init( st.GetLength());
	memmove( data,st.GetBuffer(0),st.GetLength() );
	data[ st.GetLength() ] =0;
	NoTemp();	
}
#endif

vString::vString(const char *p)
{
	InternalInit();	
	if ( p==NULL )	return;
	if ( *p==0 )	return;
	Close();
	Init( strlen(p) );
	memmove( data,p ,nLen );
	data[nLen] = 0;
	NoTemp();
}

vString::~vString()
{
	if ( bTemp )	return;
	Close();
}

// buffering functions.
void vString::InternalInit()
{
	data	= NULL;
	nLen	= 0;
	bTemp	= FALSE;
}


void vString::Init(int n)
{
	nLen	= n;
	if ( data )	delete data;
	data	= new char [nLen+1];
	memset( data,0,(n+1)*sizeof(char) );
}

void vString::Close()
{
	if ( data )	delete data;
	data	= NULL;
	nLen	= 0;
}


// operator 
void vString::operator =( vString &v)
{
	Close();
	Init( v.GetLength() );
	memmove( data,v.data,nLen );
	if ( nLen>0)
	data[nLen] = 0;

	NoTemp();
	if( v.bTemp )	v.TempClose();
}

void vString::operator =( char *p )
{
	Close();
	if (p==NULL) return;
	Init( strlen(p) );
	memmove( data,p,nLen );
	data[nLen] = 0;

	NoTemp();
}

vString vString::operator +( vString &v)
{
	vString ret;
	ret.Init( nLen +v.GetLength() );

	memmove( ret.data,data,nLen*sizeof(char));
	memmove( &ret.data[nLen], v.data,v.nLen*sizeof(char));
	ret.data[nLen+v.nLen] = 0;

	if ( v.bTemp )	v.TempClose();
	
	NoTemp();
	ret.Temp();
	return ret;

}

vString vString::operator +( char *p )
{
	vString ret;
	ret.Init( nLen +strlen(p) );

	memmove( ret.data,data,nLen*sizeof(char));
	memmove( &ret.data[nLen],p,strlen(p)*sizeof(char));
	ret.data[nLen+strlen(p)] = 0;
	
	NoTemp();
	ret.Temp();
	return ret;

}

#ifdef __AFXWIN_H__
vString vString::operator +(CString st)
{
	return operator+((char*)st.operator LPCTSTR());
}
#endif

vString vString::operator +(char ch)
{
	vString ret;
	ret.Init( nLen +1 );

	memmove( ret.data,data,nLen*sizeof(char));
	memmove( &ret.data[nLen], &ch , sizeof(char));
	ret.data[nLen+1] = 0;

	NoTemp();
	ret.Temp();
	return ret;
}

char *vString::operator +( int n )
{
	return &data[n];
}

void vString::operator +=( vString &v)
{
	char *pBuf = new char [nLen+v.GetLength()+1];
	memmove( pBuf,data,sizeof(char)*nLen );
	memmove( &pBuf[nLen],v.data,sizeof(char)*v.nLen );
	pBuf[nLen+v.nLen] = 0;

	int nNewLen = nLen+v.nLen;
	Close();
	data	= pBuf;
	nLen	= nNewLen;

	if ( v.bTemp )	v.TempClose();
	NoTemp();
}

void vString::operator+=(char *psz)
{
  this->operator+=(vString(psz));
}

void vString::operator +=(char ch)
{
	char *pBuf = new char [nLen+1+1];
	memmove( pBuf,data,sizeof(char)*nLen );
	memmove( &pBuf[nLen],&ch,sizeof(char) );
	pBuf[nLen+1] = 0;

	Close();
	nLen	+=1;
	data	= pBuf;

	NoTemp();
}

void vString::Cut( int n)
{
	int an	= ABS(n);
	int tmp = nLen	= nLen-an;

	char *pBuf = new char [nLen+1];
	memset( pBuf,0,nLen+1);	

	if ( n>0 )	memmove( pBuf,data,sizeof(char)*nLen );
	else 
	if ( n<0)	memmove( pBuf,&data[an],sizeof(char)*nLen );

	Close();
	nLen		= tmp;
	pBuf[nLen]	= 0;
	data		= pBuf;
	NoTemp();
}

// sub functions.
int vString::GetLength()
{
	if ( data )	
	{
	  nLen = strlen(data);
	  return nLen;
	}
	return 0;
}	

BOOL vString::IsEmpty()
{
	return nLen==0 ? TRUE: FALSE;
}

void vString::Empty()
{
	Close();
	NoTemp();
}

char& vString::operator [](int n)
{
	if ( nLen<=n )	
	{
		char *pBuf	= new char [n+2];
		memset( pBuf,' ',n+1);
		memmove( pBuf,data,sizeof(char)*nLen );
		pBuf[n+1]	= 0;
		Close();
		nLen		= n+1;
		data		= pBuf;
	}
	
	NoTemp();
	return data[n];
}

#ifdef LPCTSTR
vString::operator LPCTSTR()
{
	return data;
}
#endif

vString::operator char*(){	return data;}

BOOL operator ==( const vString &s1, const vString &s2)
{
  return strcmp( s1.Buf(),s2.Buf() )==0;
}
BOOL operator ==( const vString &s1,const char* s2)
{
	return strcmp( s1.Buf(),s2 )==0;
}
BOOL operator ==( const char* s1, const vString &s2)
{
	return strcmp( s1,s2.Buf() )==0;
}

BOOL operator !=( const vString &s1, const vString &s2)
{
	return strcmp( s1.Buf(),s2.Buf() )!=0;
}
BOOL operator !=( const vString &s1, const char* s2)
{
	return strcmp( s1.Buf(),s2 )!=0;
}
BOOL operator !=( const char* s1, const vString &s2)
{
	return strcmp( s1,s2.Buf() )!=0;
}

BOOL operator <( const vString &s1, const vString &s2)
{
	return strcmp( s1.Buf(),s2.Buf() )<0;
}
BOOL operator <( const vString &s1, const char* s2)
{
	return strcmp( s1.Buf(),s2 )<0;
}
BOOL operator <( const char* s1, const vString &s2)
{
	return strcmp( s1,s2.Buf() )<0;
}
BOOL operator >( const vString &s1, const vString &s2)
{
	return strcmp( s1.Buf(),s2.Buf() )>0;
}
BOOL operator >( const vString &s1, const char* s2)
{
	return strcmp( s1.Buf(),s2 )>0;
}
BOOL operator >(const char* s1, const vString &s2)
{
	return strcmp( s1,s2.Buf() )>0;
}
BOOL operator <=( const vString &s1, const vString &s2)
{
	return strcmp( s1.Buf(),s2.Buf() )<=0;
}
BOOL operator <=( const vString &s1, const char* s2)
{
	return strcmp( s1.Buf(),s2 )<=0;
}
BOOL operator <=( const char* s1, const vString &s2)
{
	return strcmp( s1,s2.Buf() )<=0;
}

BOOL operator >=( const vString &s1, const vString &s2)
{
	return strcmp( s1.Buf(),s2.Buf() )>=0;
}
BOOL operator >=( const vString &s1, const char* s2)
{
	return strcmp( s1.Buf(),s2 )>=0;
}
BOOL operator >=( const char* s1, const vString &s2)
{
	return strcmp( s1,s2.Buf() )>=0;
}

vString vString::Token( char *pSep ,int n)
{
	vString ret;
	vString copy(data);
	char *p	= copy;
	char *pret;
	int max = strlen(p);
	int ni	= 0;
	int nArg= 0;

	while(*p!=0 )
	{	
		pret	= strtok(p,pSep);		
		if ( pret==NULL )	break;

		if ( n==nArg )	
		{
			ret = pret;
			break;
		}
		nArg++;
		
		ni	+=strlen(p);
		p	+=strlen(p);
		
		p++;
		ni++;

		if ( ni>=max )	break;
	}

	ret.Temp();
	return ret;
}

vString vString::Mid( int nFirst,int nCount )
{
	vString ret;
	ret.Init(nCount);
	
	memmove( ret.data,&data[nFirst],nCount*sizeof(char));
	ret.data[nCount] = 0;

	NoTemp();
	ret.Temp();
	return ret;
}

vString vString::Left( int n ,BOOL b)
{
	vString ret;
	ret.Init( n );
	
	memmove( ret.data,data,n*sizeof(char));
	ret.data[n] = 0;

	NoTemp();
	ret.Temp();
	
	if ( b )	Cut(-n);

	return ret;
}

vString vString::Right( int n ,BOOL b)
{
	vString ret="";
	if (n==0)	return ret;
	ret.Init( n );
	
	memmove( ret.data,&data[nLen-n],n*sizeof(char));
	ret.data[n] = 0;

	NoTemp();
	ret.Temp();
	
	if ( b )	Cut(n);

	return ret;
}

int vString::FindOneOf(char *lpszSub)
{
	LPTSTR lpsz = strstr( data , lpszSub);
	return (lpsz == NULL) ? -1 : (int)(lpsz - data);
}

int vString::Find( char *lpszSub, int nStart) 
{
	if (nStart > nLen)	return -1;

	// find first matching substring
#ifdef __AFXWIN_H__
	LPTSTR lpsz = _tcsstr( data + nStart, lpszSub);
#else
	LPTSTR lpsz = strstr( data + nStart, lpszSub);
#endif

	// return -1 for not found, distance from beginning otherwise
	return (lpsz == NULL) ? -1 : (int)(lpsz - data);
}

int vString::Find(char ch, int nStart) 
{
	if (nStart >= nLen)	return -1;

	// find first single character
#ifdef __AFXWIN_H__
	LPTSTR lpsz = _tcschr( data + nStart, (_TUCHAR)ch);
#else
	char *p = &ch;
	LPTSTR lpsz = strstr( data + nStart, p);
#endif
	// return -1 if not found and index otherwise
	return (lpsz == NULL) ? -1 : (int)(lpsz - data);
}

vString vString::GetPath()
{
	vString ret(data);

	int n=0;
	for ( int i=0;i<nLen;i++)
		if ( data[i]=='/' || data[i]=='\\')	n=i;
	
	if ( n )	ret.Cut( nLen-n );

	NoTemp();
	ret.Temp();
	return ret;
}	

vString vString::GetFileName()
{
	vString ret;
	if ( IsEmpty() ) return ret;
	ret = data;

	int n=0;
	for ( int i=0;i<nLen;i++)
		if ( data[i]=='/' || data[i]=='\\')	n=i;
	
	n++;
	ret.Cut( -n );

	NoTemp();
	ret.Temp();
	return ret;
}	

vString vString::GetExt()
{
	vString ret(data);

	int n=-1;
	for ( int i=0;i<nLen;i++)
		if ( data[i]=='.' )	n=i;
	
	n++;
	ret.Cut( -n );

	NoTemp();
	ret.Temp();
	return ret;
}	

vString vString::Format(LPCTSTR lpFmt,... )
{
	va_list	marker;
	va_start( marker,lpFmt );
	char text[1000]={0,};
	
	vsprintf( text,lpFmt,marker);
	va_end( marker );

	Close();
	Init( strlen(text) );
	memmove( data,text ,nLen*sizeof(char));
	data[nLen] = 0;

	NoTemp();
	
	vString ret(data);
	return ret;
}

float vString::AtoF()
{
	return atof(data);
}

int vString::AtoI()
{
	return atoi(data);
}

BOOL vString::Open( char *fn )
{
	if ( fn==NULL )	return FALSE;
	FILE *fp	= fopen(fn,"rb");
	if ( fp==NULL )	return FALSE;

	// get file size
	fseek( fp,0,SEEK_END);
	long len	= ftell(fp);
	fseek( fp,0,SEEK_SET );

	// load file
	Close();
	Init( len );
	fread( data,len,1,fp );
	data[len] = 0;
	NoTemp();
	
	fclose(fp);
	return TRUE;
}

BOOL vString::Save( char *fn )
{
	FILE *fp	= fopen(fn,"wb");
	if ( fp==NULL )	return FALSE;

	fwrite( data,GetLength(),1,fp );
	fclose(fp);
	return TRUE;
}

#ifdef __AFXWIN_H__
BOOL vString::Open( CString st )
{
	return vString::Open( (char*)st.operator LPCTSTR() );
}
#endif

BOOL vString::Open( vString st )
{
	return vString::Open( (char*)st.operator char *() );
}


vString vString::FindLine( int nLine)
{
	vString line;
	int n = 0;

	do
	{
		line	= Token( "\r\n",n);
		if ( nLine==n) return line;
		n++;
	} while( !line.IsEmpty() );
	
	return line;
}

vString vString::FindLine2( int nOffset )
{
	vString line;
	int n	= 0;
	int nLen= 0;
	do
	{
		line	= Token( "\r\n\0",n);
		nLen+= line.GetLength();
		if ( data[nLen]==13)	nLen++;
		if ( data[nLen]==10)	nLen++;
		
		if ( nOffset<nLen )	return line;
		n++;
	} while( !line.IsEmpty() );
	
	return line;
}

vString vString::FindText( char *pfind, char *psep ,int nStart)
{
	vString line;
	vString ret;
	line.Empty();

	while(1)
	{
		int offset	= Find(pfind,nStart );
		if ( offset<0 )	return line;

		line	= FindLine2(offset);
		ret		= line.Token( psep,0 );
		ret.Filter( "\n\r\t>");

		vString tmp(pfind);

		if ( ret==tmp )	
		{
			ret	= line.Token(psep,1);
			return ret;
		}
		else	nStart	+=line.GetLength();
	}

	
	return line;
}

void vString::Filter( char *pSep )
{
	char *pBuf	= new char [GetLength()+1];
	pBuf[0]	= 0;

	vString copy(data);
	char *p	= copy;
	char *pret;
	int max = strlen(p);
	int ni	= 0;

	while(*p!=0 )
	{	
		pret	= strtok(p,pSep);		
		if ( pret==NULL )	break;
		strcat( pBuf,pret );

		ni	+=strlen(p);
		p	+=strlen(p);
		
		p++;
		ni++;

		if ( ni>=max )	break;
	}

	Close();
	Init( nLen =strlen(pBuf) );
	memmove( data,pBuf,nLen);
	data[nLen] = 0;

	delete pBuf;

	NoTemp();
}

vString vString::Hex(BYTE *p,int n)
{
	vString ret;
	
	for (int i=0;i<n;i++)
	{
		vString tmp;
		tmp.Format( "%x",p[i]);
		if ( tmp.GetLength()<2)	tmp	= vString("0")+ tmp;
		ret	= ret+tmp;
	}
	return ret;
}

#include <ctype.h>
void vString::MakeLower()
{
  char *str= data;
  while(*str!=0)
  {
    *str= tolower(*str);
    str++;
  }
}

void vString::MakeUpper()
{
  char *str= data;
  while(*str!=0)
  {
    *str= toupper(*str);
    str++;
  }
}

char* vString::GetBuffer(int n)
{
	int nOld	= GetLength();
	if ( n>nOld )
	{
		char *pcopy	= new char[nOld];
		memmove( pcopy,data,nOld);
		Init(n);
		memmove( data,pcopy,nOld);
		delete pcopy;
	}
	return data;
}

vString vString::FindTag(char* lpszSub,int &nStart)
{
	vString ret("");

	int s	= Find(lpszSub,nStart );
	if ( s<0)	return ret;
	int t	= Find(">",s);
	if ( t<0)	return ret;
	
	ret	= Mid(s,t-s+1);
	nStart	= t;
	return ret;
}

#include <ctype.h>
BOOL vString::IsChar()
{
	return isalpha(data[0]);
}

BOOL vString::IsDigit()
{
	if ( data[0]=='-' || data[0]=='.')
	if ( GetLength()>1)
	if ( data[1]>='0' && data[1]<='9')	return TRUE;

	if ( data[0]>='0' && data[0]<='9' )
	return TRUE;
	return FALSE;
}
