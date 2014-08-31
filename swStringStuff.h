// ============================================================================
//  swStringStuff
// ============================================================================
#pragma once


string toNarrowString( const wchar_t* pStr );
wstring toWideString( const char* pStr );


// ============================================================================
//  string_make
// ============================================================================
class string_make : public ostringstream 
{
public:
	operator string() const { return str(); };
	template<typename AA>
	string_make &operator << (const AA &str) 
	{
		*static_cast<ostringstream *>(this) << str;
		return *this;
	}
};

class wstring_make : public wostringstream 
{
public:
	operator wstring() const { return str(); };
	template<typename AA>
	wstring_make &operator << (const AA &str) 
	{
		*static_cast<wostringstream *>(this) << str;
		return *this;
	}
};

// ============================================================================
//  std::string trim
// ============================================================================
template<typename StringType>
inline StringType trim(const StringType& s, const StringType& chars) 
{
	if( s.length() != 0 )
	{
		StringType::size_type beg = s.find_first_not_of(chars);
		if( beg != StringType::npos )
		{
			StringType::size_type end = s.find_last_not_of(chars);
			return StringType(s, beg, end-beg+1);
		}
	}
	return StringType();
}

// ============================================================================
//  std::string startsWith
// ============================================================================
template<typename StringType>
inline bool startsWith(const StringType& s, const StringType& chars) 
{
	return chars.find(s.c_str(), 0, chars.size()) != StringType::npos;
}

// ============================================================================
//  LazyString
// ============================================================================
struct LazyString
{
	vector<char>::iterator Begin;
	vector<char>::iterator End;
	bool bEmpty;

	LazyString() : bEmpty(true) {}
	LazyString(vector<char>::iterator Begin, vector<char>::iterator End) : Begin(Begin), End(End), bEmpty(false) {}

	const char* ptr()
	{
		return &(*Begin);
	}

	const char* c_str()
	{
		return bEmpty ? "" : string(Begin,End).c_str();
	}

	string str()
	{
		return bEmpty ? "" : string(Begin,End);
	}

	bool empty() const
	{
		return bEmpty;
	}
};


// ============================================================================
//  EOF
// ============================================================================