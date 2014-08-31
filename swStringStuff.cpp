// ============================================================================
//  swStringStuff.cpp
// ============================================================================

#include "stdafx.h"

// Modify the following defines if you have to target a platform prior to the ones specified below.
// Refer to MSDN for the latest info on corresponding values for different platforms.
#ifndef WINVER				// Allow use of features specific to Windows XP or later.
#define WINVER 0x0501		// Change this to the appropriate value to target other versions of Windows.
#endif

#ifndef _WIN32_WINNT		// Allow use of features specific to Windows XP or later.                   
#define _WIN32_WINNT 0x0501	// Change this to the appropriate value to target other versions of Windows.
#endif						

#ifndef _WIN32_WINDOWS		// Allow use of features specific to Windows 98 or later.
#define _WIN32_WINDOWS 0x0410 // Change this to the appropriate value to target Windows Me or later.
#endif

#ifndef _WIN32_IE			// Allow use of features specific to IE 6.0 or later.
#define _WIN32_IE 0x0600	// Change this to the appropriate value to target other versions of IE.
#endif

#define WIN32_LEAN_AND_MEAN		// Exclude rarely-used stuff from Windows headers

#include "swStringStuff.h"
#include "windows.h"


string toNarrowString( const wchar_t* pStr )
{
	// figure out how many narrow characters we are going to get 

	int len = static_cast<int>(wcslen(pStr));
	int nChars = WideCharToMultiByte( CP_UTF8 , 0 , pStr , len , NULL , 0 , NULL , NULL ) ; 

	if ( len == -1 )
		-- nChars ; 
	if ( nChars == 0 )
		return "" ;

	// convert the wide string to a narrow string

	// nb: slightly naughty to write directly into the string like this

	string buf ;
	buf.resize( nChars ) ;
	WideCharToMultiByte( CP_UTF8 , 0 , pStr , len , const_cast<char*>(buf.c_str()) , nChars , NULL , NULL ) ; 

	return buf ; 
}

wstring toWideString( const char* pStr )
{
	// figure out how many wide characters we are going to get 

	int len = static_cast<int>(strlen(pStr));
	int nChars = MultiByteToWideChar( CP_ACP , 0 , pStr , len , NULL , 0 ) ; 
	if ( len == -1 )
		-- nChars ; 
	if ( nChars == 0 )
		return L"" ;

	// convert the narrow string to a wide string 

	// nb: slightly naughty to write directly into the string like this

	wstring buf ;
	buf.resize( nChars ) ; 
	MultiByteToWideChar( CP_ACP , 0 , pStr , len , const_cast<wchar_t*>(buf.c_str()) , nChars ) ; 

	return buf ;
}

// ============================================================================
//  EOF
// ============================================================================