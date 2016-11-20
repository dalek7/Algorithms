#ifndef __INTELLIGENT_TOKEN__
#define __INTELLIGENT_TOKEN__

#include "vString.h"
#include "vArray.h"

#ifdef _DEBUG
#ifndef VTVAR
#define VTFIX
#endif
#else
#define VTVAR
#endif

// VTVAR variable array
// VTFIX fixed array for debugging

/////////////////////////////////////////////////////////////////////////////////
//
//		Token Separation for Parsing.
//
//		Programming by J.Yang, UT at Austin, in 2002
//
//		
/////////////////////////////////////////////////////////////////////////////////

//		FindNP is added for July 2004 at KAIST
//		vToken is added for Sep. 2005 at KAIST
//		(vToken is an alias of CToken from Windows platform)

//! vToken for token separation.
class vToken
{
public:
		vToken();	
		~vToken();
		vToken(char*);
		vToken(vString);
public:
		void	SetSeparator(char *,BOOL bEmpty=FALSE);
		void	SetSeparator(char *,char *pOP,BOOL bEmpty=FALSE);	// for 1.7 *3+ --> 1.7,*,3,+
		void	SetSeparatorString(char *,char bStrBracket='"');

		void	Set(vString s);	
		void	Compress( char *);
		void	FindP(char*);	// find parenthesis
		void	FindNP(char*,char strbracket=0);	// find parenthesis and not parenthesis
		void	SimpleCalc(char p=0);
		vString	All(int sToken,int tToken);		// setseparator(,pOP) when pop shoul be existed.
		vString All(int sToken);
		vString Combine(int sToken,int tToken,char );	
		vString Combine(int sToken,char );	
		vString Combine(char );	
		vString Combine(int sToken,int tToken,char* );	
		vString Combine(int sToken,char* );	
		vString Combine(char *);
		void	RemoveAll();
		int		Search(char*);
		vString		Format( LPCTSTR,... );
		vString		FormatA( LPCTSTR,... );	// "[%d    ]",1 --> "[1     ]"


		BOOL	IsChar(int);
		BOOL	IsDigit(int);
		BOOL	IsIn(int,vString);
		vString RetArg(int);	// string
		float   RetArgf(int);	// double
		int		RetArgi(int);	// integer;

		vString	Get(int);
		float	Getf(int);
		int		Geti(int);


		int		RetArgMax()	{ return nMaxArg; }		
		int		GetSize()	{ return nMaxArg; }		
		void	RemoveAt(int);
		void	InsertAt(char*,int n=0);

		vString operator[](int);	// same with RetArg
		vString GetAt(int);	
		float	f(int);				// same with RetArgf
		int		i(int);				// same with RetArgi
		void	Add(vString);
		void	Load(vString);		
		void    Load(char*);
		void	Sort(BOOL bAscending=TRUE);

public:
		vString m_in;

protected:

#ifdef VTFIX
#define MAX_ARG 500
		vString	m_arg[MAX_ARG];						
#else	
		vArray<vString,vString> m_arg;

#endif
		int		nMaxArg;

		
};




#endif
