#ifndef __vString__
#define __vString__

#include <stdio.h>
#include <string.h>
#include <stdarg.h>
#include <stdlib.h>

class vString
{
public:
		vString();
		vString( const vString&);
		vString( const char *);
		vString( char);

#ifdef __AFXWIN_H__
		vString( CString &);
#endif
		~vString();

public:
		// create and destroy
		void		Close();
		void		Init(int);
		
		// operation.
		vString		operator+(vString&);
		vString		operator+(char );
		vString     operator+(char*);	      
#ifdef __AFXWIN_H__
		vString		operator+(CString );
		void		operator=(CString);
#endif
		void		operator+=(char*);
		void		operator+=(vString &);
		void		operator+=(char);
		
		char*		operator+(int);

		void		operator=(vString&);
		void		operator=(char*);
		
		char&		operator[](int n);
#ifdef LPCTSTR
		operator	LPCTSTR();
#endif
		operator        char*();
		
		// sub functions.
		int			GetLength();
		BOOL		IsEmpty();
		void		Empty();
		char*		Buf()	const	{ return data;}
		char*		GetBuffer()	{ return data;}
		char*		GetBuffer(int);
		void		MakeLower();
		void		MakeUpper();
		
		// string divider
		void		Cut(int n);		// if n>0, remove right  and if n<0, remove left
		vString		Mid( int nFirst, int nCount );
		vString		Left (int	,BOOL b=FALSE);
		vString		Right(int	,BOOL b=FALSE);

		// find
		int			Find( char*,int nStart=0);
		int			Find( char,int nStart=0);
		int			FindOneOf(char*);
		vString		Token( char *,int n=0);
		vString		FindTag(char*,int &nStart);

		// file and extension
		vString		GetPath();
		vString		GetFileName();
		vString		GetExt();

		// format.
		vString		Format( LPCTSTR,... );
		int			AtoI();
		float		AtoF();
		vString		Hex(BYTE *,int);

		// file operation
		BOOL		Open( char *);
#ifdef __AFXWIN_H__	
		BOOL		Open( CString );
#endif
		BOOL		Open( vString );

		BOOL		Save(char *);


		// text a=b
		vString		FindLine( int nLine );
		vString		FindLine2( int nOffset );
		vString		FindText( char *,char *,int nStart = 0);

		// filter
		void		Filter( char *);
		BOOL		IsDigit();
		BOOL		IsChar();
		
		
private:
		void		InternalInit();
		void		TempClose()		{ Close(); bTemp=FALSE; }
		void		Temp()			{ bTemp= TRUE; }
		void		NoTemp()		{ bTemp= FALSE;}
		

		BOOL		bTemp;
		char		*data;
		int			nLen;
};

BOOL		operator==( const vString&, const vString &);
BOOL		operator==( const vString&, const char* );
BOOL		operator==( const char* , const vString& );
BOOL		operator!=( const vString&, const vString &);
BOOL		operator!=( const vString&, const char* );
BOOL		operator!=( const char* , const vString& );
BOOL		operator<( const vString&, const vString &);
BOOL		operator<( const vString&, const char* );
BOOL		operator<( const char* , const vString& );
BOOL		operator<=( const vString&, const vString &);
BOOL		operator<=( const vString&, LPCTSTR );
BOOL		operator<=( const char* , const vString& );
BOOL		operator>( const vString&, const vString &);
BOOL		operator>( const vString&, const char* );
BOOL		operator>( const char* , const vString& );
BOOL		operator>=( const vString&, const vString &);
BOOL		operator>=( const vString&, const char* );
BOOL		operator>=( const char* , vString& );
#endif

