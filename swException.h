// ============================================================================
//  swException
// ============================================================================
#pragma once


class swException
{
public: 
	swException( wstring what )
	{
		m_errorMsg = what;
	}

	swException( const swException& rhs ) : m_errorMsg(rhs.m_errorMsg)
	{
	}

	virtual ~swException()
	{
	}

	swException& operator=( const swException& rhs )
	{
		m_errorMsg = rhs.m_errorMsg; 
		return *this; 
	}

	const wchar_t* What() const
	{
		return m_errorMsg.c_str();
	}

private:
	wstring m_errorMsg;
};

//// ============================================================================
//// guards
//// ============================================================================
//#define guard	try {
//#define unguard } catch( swException& e ) { wxLogError( wxString::Format(wxT("%s"), e.What().c_str() )); }\
//				  catch( exception& e ) { wxLogError( wxString::Format(wxT("%hs"), e.what())); }


// ============================================================================
//  EOF
// ============================================================================