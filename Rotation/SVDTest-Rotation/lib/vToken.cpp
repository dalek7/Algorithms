#include "stdafx.h"
#include "vToken.h"



vToken::vToken()
{
	m_in.Empty();
	nMaxArg	= 0;
	RemoveAll();
}

vToken::~vToken()
{
	RemoveAll();
}

void vToken::RemoveAll()
{
#ifdef VTFIX
	for (int i=0;i<MAX_ARG;i++)
	if ( !m_arg[i].IsEmpty() )
		m_arg[i].Empty();	
	nMaxArg	= 0;
#else
	for (int i=0;i<m_arg.GetSize();i++)
		m_arg[i].Close();
	m_arg.RemoveAll();	
#endif
	nMaxArg	= 0;
	m_in.Empty();
}

vToken::vToken( char *s )
{
	RemoveAll();
	m_in	= vString(s);
}

vToken::vToken( vString s )
{
	RemoveAll();
	m_in	= s;
	//m_in.Format("%s",s.GetBuffer());
}

void vToken::Set(vString st)
{ 
	if (!st.IsEmpty())
		//m_in.Format("%s",st.GetBuffer()); 
		m_in	= st;
	else
		m_in.Empty();
#ifdef VTFIX
	for ( int i=0;i<MAX_ARG;i++)
		m_arg[i].Empty();	
#else
	for (int i=0;i<m_arg.GetSize();i++)
		m_arg[i].Close();
	m_arg.RemoveAll();			
#endif
}

void vToken::Add( vString st)
{
#ifdef VTFIX
	m_arg[nMaxArg]	= st;				
#else
	m_arg.Add( st);	
#endif
	nMaxArg++;
}

void vToken::SetSeparator( char *sep ,BOOL bEmpty)
{
#ifndef VTFIX
	for (int i=0;i<m_arg.GetSize();i++)
		m_arg[i].Close();
	m_arg.RemoveAll();	
#endif
	nMaxArg = 0;

	// separate tokens.
	char *p	= (char*)m_in.GetBuffer();
	if (p==NULL)	return;

	char *ret;
	int max = strlen(p);
	int ni	= 0;

	while(*p!=0 )
	{	
		ret	= strtok(p,sep);
		
		if ( bEmpty==FALSE && ret==NULL )	break;
		else 
		if ( bEmpty )	
		{
			if ( *(p+1)==sep[0] )	Add(vString(""));	// Ad-hoc for counting line feed.
		}

		if (ret)
		Add(vString(ret));
				
		ni+=strlen(p);
		p+=strlen(p);
		
		p++;
		ni++;

		if ( ni>=max )	break;
	}
}


void vToken::SetSeparator( char *sep ,char *pOP,BOOL bEmpty)
{
#ifndef VTFIX
	for (int i=0;i<m_arg.GetSize();i++)
		m_arg[i].Close();
	m_arg.RemoveAll();	
#endif
	nMaxArg = 0;

	// separate tokens.
	char *p	= (char*)m_in.GetBuffer();
	char *ret;
	int max = strlen(p);
	int ni	= 0;

	// copy
	char *pcopy	= new char[max+1];
	strcpy(pcopy,p);
	pcopy[max]	= 0;

	// synth
	char newsep[100];
	strcpy(newsep,sep);
	strcat(newsep,pOP);

	/*
	// find former part. ex) when " (1+2)", ( cannot be neglected!.
	ret	= strtok(p,newsep);
	if ( strlen(ret)!=strlen(p))
	{
		ret	= strtok(p,sep);
		for ( int i=0;i<strlen(ret);i++)
		for ( int j=0;j<strlen(pOP);j++)
			if ( ret[i]==pOP[j]	)	Add(pOP[j]);
	}
	strcpy(p,pcopy);	
	*/

	// general separating routine
	while(*p!=0 )
	{	
		ret	= strtok(p,newsep);
		if ( ret==NULL)
		{			
			for ( int i=0;i<strlen(p);i++)
			for ( int j=0;j<strlen(pOP);j++)
				if ( p[i]==pOP[j]	)	
					Add(vString(pOP[j]));
			break;
		}
		
		char *p2 = p;
		while( strlen(ret)!=strlen(p2))
		{
			for ( int j=0;j<strlen(pOP);j++)
			if ( *p2==pOP[j]	)	
				Add(vString(pOP[j]));
			p2++;
		}
		strcpy(p,&pcopy[ni]);	
		
		ret	= strtok(p,newsep);
		Add(vString(ret));

		int n	= ni+strlen(p);
		for ( int i=0;i<strlen(pOP);i++)
		if ( pcopy[n]==pOP[i] )	
		{
			Add(vString(pOP[i]));
			break;
		}
		
		ni+=strlen(p);
		p+=strlen(p);
		
		p++;
		ni++;

		if ( ni>=max )	break;
	}

	delete pcopy;

	if ( bEmpty)
	for (int i=0;i<GetSize();i++)
	{
		CString tmp = m_arg[i];

		BOOL bSep = FALSE;
		int j;
		for ( j=0;j<strlen(pOP);j++)
		if ( tmp==pOP[j])
		{
			bSep = TRUE;
			break;
		}

		if ( bSep)
		{
			CString tmp2;
			if ( i+1<GetSize())	tmp2 = m_arg[i+1];

			if ( tmp2.IsEmpty())	
			{
				Add("");
				return;
			}
			else
			{
				for ( j=0;j<strlen(pOP);j++)
				if ( tmp2==pOP[j])
				{
					InsertAt("",i+1);
					i++;
					break;
				}	
			}
		}
	}
}

void vToken::SetSeparatorString( char *sep ,char bStrBracket)
{
#ifndef VTFIX
	for (int i=0;i<m_arg.GetSize();i++)
		m_arg[i].Close();
	m_arg.RemoveAll();	
#endif
	nMaxArg = 0;

	// add string bracket.
	char *pSep	= new char [strlen(sep)+1+1];
	strcpy(pSep,sep);
	pSep[strlen(pSep)] = bStrBracket;

	// separate tokens.
	char *p	= (char*)m_in.GetBuffer();
	if (p==NULL)	return;

	char *ret;
	int max = strlen(p);
	int ni	= 0;

	// copy
	char *pcopy	= new char[max+1];
	strcpy(pcopy,p);
	pcopy[max]	= 0;

	while(*p!=0 )
	{	
		ret	= strtok(p,pSep);

		if ( *p==bStrBracket)
		{
                        memmove(p,&pcopy[ni],max-ni);
                        int i;
                        for (i=ni+1;i<max;i++)
			if ( pcopy[i]==bStrBracket)
			{
				break;
			}
			
                        char *ptemp = new char[i-ni+2];
			memmove(ptemp,p,i-ni+1);
			ptemp[i-ni+1] = 0;
			Add(vString(ptemp));
                        delete ptemp;

			p+=i-ni+1;
			ni+=i-ni+1;
			continue;
		}

		if ( ret==NULL )	break;		

		Add(vString(ret));
				
		ni+=strlen(p);
		p+=strlen(p);
		
		p++;
		ni++;

		if ( ni>=max )	break;
	}

	if ( pSep)	delete pSep;
	if (pcopy)	delete pcopy;
}


void vToken::FindP(char *sep)
{
#ifndef VTFIX
	for (int i=0;i<m_arg.GetSize();i++)
		m_arg[i].Close();
	m_arg.RemoveAll();	
#endif
	nMaxArg	= 0;

	char *p	= (char*)m_in.GetBuffer();
	char *ret = p;
	int max = strlen(p);
	int ns	= 0;
	int nt	= 0;

	while(*p!=0 )
	{	
		// find first '('
		while( *p!=0 && *p!=sep[0] )	p++,ns++;
		if ( ns>=max )	return;
		ret	= p+1;

		// find second ')'
		nt	= ns;
		while( *p!=0 && *p!=sep[1])		p++,nt++;
		*p	= 0;

		Add(vString(ret));
		ns	= nt+1;
		nt	= ns;
		p++;
	}
}

// "<babo>" --> don't find <> in string.
void vToken::FindNP(char *sep,char strbracket)
{
#ifndef VTFIX
	for (int i=0;i<m_arg.GetSize();i++)
        m_arg[i].Close();
	m_arg.RemoveAll();	
#endif
	nMaxArg	= 0;

	char *p	= (char*)m_in.GetBuffer();
	char *ret = p;
	int max=0;
	if (p)	max= strlen(p);
	else	return;

	int ni	= 0;
	int ne	= 0;

	BOOL bString = FALSE;

	while(*p!=0 )
	{	
		// find first '('
		//while( *p!=0 && *p!=sep[0] )
		while( *p!=0  )
		{
			if ( bString==FALSE)
			if (*p==sep[0])	break;
			if ( *p==strbracket)	bString =!bString;
			p++,ni++;
		}
		if ( ni>=max )	
		{
			if ( *ret!=0)	Add(vString(ret));
			return;
		}
		
		// non p
		if ( ni>0 && ne+1!=ni)	
		{
			*p	= 0;
			if ( *ret!=0)
			{
				Add(vString(ret));
				p++;
				ret	= p;
			}
		}
		else	ret	= p+1;

		// find second ')'
		ni++;
		//while( *p!=0 && *p!=sep[1])		p++,ni++;
		while( *p!=0  )
		{
			if ( bString==FALSE)
			if (*p==sep[1])	break;
			if ( *p==strbracket)	bString =!bString;
			p++,ni++;
		}
		*p	= 0;
		ne	= ni;

		Add( vString(sep)+vString(ret));
		ni++;
		p++;
		ret	= p;
	}
}

vString vToken::RetArg(int n)
{
#ifndef VTFIX
	if ( m_arg.GetSize()==0)	return vString("");
#endif
	return m_arg[n];
}

float vToken::RetArgf( int n )
{
#ifndef VTFIX
	if ( m_arg.GetSize()==0)	return 0;
#endif

	vString buf = m_arg[n];
	buf.MakeLower();
	if ( buf.Find( "rad")>=0 )
	{
		vToken rad(buf);
		rad.SetSeparator("()");
		float radian = rad.RetArgf(1);
	
		return radian*3.1415926/180;
	}
	return (float)atof( m_arg[n] );
}

int vToken::RetArgi( int n )
{
#ifndef VTFIX
	if ( m_arg.GetSize()==0)	return 0;
#endif
	return atoi( m_arg[n] );
}

float vToken::f(int n)	{	return RetArgf(n); }
int   vToken::i(int n)	{	return RetArgi(n); }

#include <ctype.h>
BOOL vToken::IsChar( int n)
{
  if (isalpha(m_arg[n][0])>0) return TRUE;
  return FALSE;
}

BOOL vToken::IsDigit( int n)
{
	if ( m_arg[n][0]=='-' || m_arg[n][0]=='.' )
	if ( m_arg[n].GetLength()>1)
	if ( m_arg[n][1]>='0' && m_arg[n][1]<='9' )	return TRUE;

	if ( m_arg[n][0]>='0' && m_arg[n][0]<='9' )
	return TRUE;
	return FALSE;
}

BOOL vToken::IsIn( int n,vString s )
{
	if ( m_arg[n].FindOneOf( s )<0 )	return FALSE;
	return TRUE;
}

void vToken::Compress( char *p )
{
	vString buf;

	for ( int i=0;i<m_in.GetLength();i++)
	{
	  BOOL b= FALSE;
	  for ( int j=0;j<strlen(p);j++)
	    if (p[j]==m_in[i]) { b= TRUE; break;}

	  if ( b==FALSE ) buf = buf+vString(m_in[i]);
	}
	m_in	= buf;
}

vString vToken::operator [](int i)
{
#ifndef VTFIX
	if ( m_arg.GetSize()==0)	return vString("");
#endif
	return m_arg[i];
}

vString vToken::GetAt(int i)
{
#ifndef VTFIX
	if ( m_arg.GetSize()==0)	return vString("");
#endif
	return m_arg[i];
}


vString vToken::Get(int i)	{ return vToken::RetArg(i); }
float	vToken::Getf(int i)	{ return vToken::RetArgf(i); }
int		vToken::Geti(int i)	{ return vToken::RetArgi(i); }

void vToken::Load(char *psz)
{
  vToken::Load(vString(psz));
}
void vToken::Load(vString st)
{
#ifndef VTFIX
	for (int i=0;i<m_arg.GetSize();i++)
		m_arg[i].Close();
	m_arg.RemoveAll();		
#else
	for (int i=0;i<MAX_ARG;i++)
	if ( !m_arg[i].IsEmpty() )
		m_arg[i].Close();
#endif

	FILE *fp	= fopen(st,"rb");
	if ( fp==NULL )	return;
	fseek(fp,0,SEEK_END);
	LONG dw	= ftell(fp);
	fseek(fp,0,SEEK_SET);
	fread(m_in.GetBuffer(dw),dw,1,fp);
	fclose(fp);
}

vString vToken::All( int sToken )
{
	vString tmp;
	for ( int i=sToken;i<GetSize();i++)
		tmp	+=RetArg(i);
	return tmp;
}

vString vToken::All( int sToken ,int tToken)
{
	vString tmp;
	for ( int i=sToken;i<tToken;i++)
		tmp	+=RetArg(i);
	return tmp;
}

void vToken::RemoveAt(int n)
{
#ifndef VTFIX	
	m_arg.RemoveAt(n);
#else
	for (int i=n;i<GetSize()-1;i++)
		m_arg[i]	= m_arg[i+1];
	m_arg[GetSize()-1].Empty();
#endif
	nMaxArg--;
	if ( nMaxArg<0)	nMaxArg	= 0;
}

void vToken::InsertAt(char *psz,int n)
{
#ifndef VTFIX
	vString tmp=psz;
	m_arg.InsertAt(n,tmp);
#else
	for (int i=GetSize();i>n;i--)
		m_arg[i]	= m_arg[i-1];
	m_arg[n]	= psz;
#endif
	nMaxArg++;
}

// Insertion Sort based method.	11/21/06
void vToken::Sort(BOOL bAscending )
{
	for (int i=1;i<GetSize();i++)
	{
		vString st = m_arg[i];
		for (int j=0;j<i;j++)
		{
			vString tmp	= m_arg[j];

			if ( bAscending )
			{
                                if ( strcmp(st,tmp)<=0)
				{
					for (int k=i;k>j;k--)
						m_arg[k]	= m_arg[k-1];

					m_arg[j]	=st;
					break;
				}
			}
			else	// descending.
			{
                                if ( strcmp(st,tmp)>=0)
				{
					for (int k=i;k>j;k--)
						m_arg[k]	= m_arg[k-1];

					m_arg[j]	=st;
					break;
				}
			}
		}
	}
}

vString vToken::Combine(int sToken,int tToken,char ch)
{
	char buf[2]={0,};
	buf[0]	= ch;
	return Combine(sToken,tToken,buf);
}

vString vToken::Combine(int sToken,int tToken,char *psz)
{
	vString ret;
	vString intm;
	intm	= psz;

	if ( sToken==tToken)	
	{
		if ( !m_arg[sToken].IsEmpty())
		ret	= m_arg[sToken];
		return ret;
	}

	for (int i=sToken;i<=tToken;i++)
	{
		if (i==sToken)	ret	= m_arg[i];
		else			ret	= ret+intm+m_arg[i];
	}
	return ret;
}

vString vToken::Combine(int sToken,char ch)
{
	return Combine(sToken,GetSize()-1,ch);
}

vString vToken::Combine(char ch)
{
	return Combine(0,GetSize()-1,ch);
}

vString vToken::Combine(char *psz)
{
	return Combine(0,GetSize()-1,psz);
}

int vToken::Search(char *psz)
{
	for (int i=0;i<GetSize();i++)
	{
		vString v = Get(i);
                if ( strcmp(v,psz)==0)	return i;
	}
	return -1;
}

vString vToken::Format(LPCTSTR lpFmt,... )
{
        va_list	marker;
	va_start( marker,lpFmt );
	char text[1000]={0,};
	
	vsprintf( text,lpFmt,marker);
	va_end( marker );

	vString ret(text);
	return ret;
}

vString vToken::FormatA(LPCTSTR lpFmt,... )
{
	va_list	marker;
	va_start( marker,lpFmt );
	char text[1000]={0,};
	
	vsprintf( text,lpFmt,marker);
	va_end( marker );

	vToken tk(lpFmt);
	tk.FindNP("[]");

	vToken tr(text);
	tr.FindP("[]");

	vString ret("");
	for (int i=0,j=0;i<tk.GetSize();i++)
	{
		vString buf	= tk[i];
		if ( buf[0]=='[')
		{
			int n	= tk[i].GetLength()-4;
			int n2	= tr[j].GetLength();

			vString tmp;
			if ( n<n2)
				tmp.Format("[%s]",(char*)tr[j].Left(n) );
			else if ( n>n2)
			{
				tmp.Format("[%s]",(char*)tr[j]);
				for (int k=0;k<n-n2;k++)
					tmp	= tmp+" ";
			}
			else	tmp	= tr[j];
			j++;

			ret	= ret+tmp;
		}
		else	ret	= ret+tk[i];
	}

	return ret;
}
