#pragma once

#include <string>
#include <stlsoft/shims/access/string.hpp>
#include <stlsoft/string/case_functions.hpp>

class CWildcard  
{
public:

	enum Match
	{
		matchNone,			///< For internal use.
		matchValid,			///< A valid match.
		matchEnd,			///< Premature end of the pattern string.
		matchAbort,			///< Premature end of the text string.
		matchRange,			///< Match failure on the \c [..] construct.
		matchLiteral,		///< Match failure on a literal match
		matchPattern		///< A bad pattern.
	};

	enum Pattern 
	{
		patternEmpty = -4,	///< The \c [..] construct is empty
		patternClose,		///< There is no end bracket in the \c [..] construct.
		patternRange,		///< Malformed range in the \c [..] construct.
		patternEsc,			///< There is a literal escape at the end of the pattern.
		patternValid,		///< A valid pattern.
	};


	/**
	Matches \a lpszText against the pattern.
	A match means the entire \a lpszText is used in matching.
	Set the pattern with the #SetPattern method or in the constructor.

	\param lpszText
	The string to match against the pattern.

	\param iRetCode
	If not \c NULL, receives one of the #Match values indicating a return code.

	\return
	\c true, if \a lpszText matches the pattern.

	\see
	SetPattern
	*/
	bool IsMatch(LPCTSTR lpszText, int* iRetCode = NULL);

	/**
	Returns the value indicating whether \a lpszPattern has any special wildcard characters.

	\param lpszPattern
	The pattern to test.

	\return
	\c true, if the pattern has wildcard characters; \c false otherwise.

	*/
	static bool IsPattern(LPCTSTR lpszPattern);

	/**
	Tests \a lpszPattern for validity.

	\param lpszPattern
	The pattern to test.

	\param iErrorType
	If not \c NULL, receives one of the #Pattern values indicating a return code.

	\return
	\c true, if \a lpszPattern is a well formed regular expression according
	to the CWildcard class syntax (see #SetPattern); \c false otherwise.
	*/
	static bool IsPatternValid(LPCTSTR lpszPattern, int* iErrorType = NULL);

	/**
	Matches \a lpszText against \a lpszPattern.

	A match means the entire \a lpszText is used in matching.

	\param lpszPattern
	The pattern to match.

	\param lpszText
	The string to match against the pattern.

	\return 
	One of the #Match values.

	\see
	SetPattern
	*/
	static int Match(LPCTSTR lpszPattern, LPCTSTR lpszText);

	/**	
	Initializes a new instance of the CWildcard class.
	*/
	CWildcard(){}

	/**
	Initializes a new instance of the CWildcard class.

	\param lpszPattern
	The pattern to use in matching.

	\param bCaseSensitive
	The case-sensitivity of matching.

	\see
	<a href="kb">0610242025|wildcards</a>
	*/
	CWildcard(LPCTSTR lpszPattern, bool bCaseSensitive)
	{
		SetPattern(lpszPattern, bCaseSensitive);
	}

	virtual ~CWildcard(){}

	/**
	Sets the current pattern

	\param lpszPattern
	The pattern used in matching.

	\param bCaseSensitive
	The case-sensitivity of matching.

	\see
	<a href="kb">0610242025|wildcards</a>
	*/
	void SetPattern(LPCTSTR lpszPattern, bool bCaseSensitive)
	{
		m_szPattern = lpszPattern;
		m_bCaseSensitive=bCaseSensitive;
		if (!bCaseSensitive)
			stlsoft::make_lower(m_szPattern);
	}
	operator LPCTSTR()
	{
		return stlsoft::c_str_data(m_szPattern);
	}

private:
	typedef std::basic_string<TCHAR> tstring;

private:
	bool m_bCaseSensitive;		
	static int MatchAfterStar(LPCTSTR p , LPCTSTR t);
	tstring m_szPattern;
};