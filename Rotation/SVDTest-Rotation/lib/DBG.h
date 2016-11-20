

#ifndef DD_DBG_H
#define DD_DBG_H


inline void Dbg(LPCTSTR lpFmt,... )
{
#ifdef DD_DBG
	va_list	marker;
	va_start( marker,lpFmt );
	char text[1000]={0,};
	
	vsprintf( text,lpFmt,marker);
	va_end( marker );

	CString buf(text);

	OutputDebugString (buf);
#endif
}



inline CString DDFORMAT(LPCTSTR lpFmt,... )
{
	va_list	marker;
	va_start( marker,lpFmt );
	char text[1000]={0,};
	
	vsprintf( text,lpFmt,marker);
	va_end( marker );

	CString buf(text);

	return buf;

}


#endif