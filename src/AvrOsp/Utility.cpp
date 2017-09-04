/*****************************************************************************
 *
 * Atmel Corporation
 *
 * File              : Utility.cpp
 * Compiler          : Dev-C++ 4.9.8.0 - http://bloodshed.net/dev/
 * Revision          : $Revision: 1163 $
 * Date              : $Date: 2006-08-02 15:38:16 +0200 (on, 02 aug 2006) $
 * Updated by        : $Author: ohlia $
 *
 * Support mail      : avr@atmel.com
 *
 * Target platform   : Win32
 *
 * AppNote           : AVR911 - AVR Open-source Programmer
 *
 * Description       : A class holding misc. utility methods used in AVROSP.
 *
 *
 ****************************************************************************/
#include "Utility.hpp"

#include <windows.h>

#include <sstream>
#include <iostream>
#include <fstream>
#include <stdlib.h>

/* Global object */
Utility Util;


/* Constructor */
Utility::Utility() :
	noLog( false ),
	noProgress( false )
{
	/* No code here */
}


/* Destructor */
Utility::~Utility()
{
	/* No code here */
}



void Utility::log( const string & txt )
{
	if( !noLog )
		cout << txt;
}


void Utility::progress( const string & txt )
{
	if( !noProgress )
		cout << txt;
}


long Utility::convertHex( const string & txt )
{
	long result = 0;
	long digit;
	long i;

	if( txt.size() == 0 )
		throw new ErrorMsg( "Cannot convert zero-length hex-string to number!" );

	if( txt.size() > 8 )
		throw new ErrorMsg( "Hex conversion overflow! Too many hex digits in string." );


	for( i = 0; i < txt.size(); i++ )
	{
		/* Convert hex digit */
		if( txt[i] >= '0' && txt[i] <= '9' )
			digit = txt[i] - '0';
		else if( txt[i] >= 'a' && txt[i] <= 'f' )
			digit = txt[i] - 'a' + 10;
		else if( txt[i] >= 'A' && txt[i] <= 'F' )
			digit = txt[i] - 'A' + 10;
		else
			throw new ErrorMsg( "Invalid hex digit found!" );

		/* Add digit as least significant 4 bits of result */
		result = (result << 4) | digit;
	}

	return result;
}


string Utility::convertLong( long num, long radix )
{
	char buf[18];
	string res;

	itoa( num, buf, radix );
	res = buf;
	return res;
}


void Utility::parsePath( vector<string> & list )
{
	/* Get environment variable and parse if it exists */
	char * pathptr = getenv( "PATH" );
	if( pathptr != NULL && pathptr[0] != 0 ) {
		string path = pathptr;
		int pos;

		while( (pos = path.find_first_of( ";" )) < path.length() ) {
			list.push_back( path.substr( 0, pos ) );
			path.erase( 0, pos+1 );
		}

		list.push_back( path ); // Last directory.
	}
}


bool Utility::fileExists( string filename )
{
	/* Attempt to open file */
	ifstream f;
	f.open( filename.c_str(), ios::in );
	if( !f ) {
		return false;
	} else {
		f.close();
		return true;
	}
}


void Utility::saveString( string txt, string filename )
{
	ofstream f;

	f.open( filename.c_str(), ios::out );
	if( !f )
		throw new ErrorMsg( "Error opening HEX file for output!" );

	f << txt;

	f.close();
}

string Utility::getLastError()
{
	DWORD errorMessageID = ::GetLastError();

	if (errorMessageID == 0)
		return string();

	LPSTR messageBuffer = nullptr;
	size_t size = FormatMessageA(FORMAT_MESSAGE_ALLOCATE_BUFFER | FORMAT_MESSAGE_FROM_SYSTEM | FORMAT_MESSAGE_IGNORE_INSERTS,
		NULL, errorMessageID, MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT), (LPSTR)&messageBuffer, 0, NULL);

	string message(messageBuffer, size);

	LocalFree(messageBuffer);

	return message.replace(message.end() - 3, message.end(), "");
}


void Utility::handleMallocFailure(unsigned long size)
{
	stringstream msg;
	msg << "Unable to allocate [" << size << "] bytes";

	throw new ErrorMsg(msg.str());
}

string Utility::guidToString(GUID uuid)
{
	string guid;
	RPC_CSTR szUuid = NULL;
	if (::UuidToStringA(&uuid, &szUuid) == RPC_S_OK)
	{
		guid = (char*)szUuid;
		::RpcStringFreeA(&szUuid);
	}

	return guid;
}

string Utility::convertToString(wstring value)
{
	using convert_type = std::codecvt_utf8<wchar_t>;
	std::wstring_convert<convert_type, wchar_t> converter;
	return converter.to_bytes(value);
}

#ifndef NOREGISTRY
string Utility::getRegistryValue( const string & path, const string & value )
{
	/* Code modified from MSDN */
	const long BUFSIZE=1000;
	string result;
	HKEY hKey;
	char szAVRPath[BUFSIZE];
	DWORD dwBufLen=BUFSIZE;
	LONG lRet;

	/* Open key */
	lRet = RegOpenKeyEx( HKEY_LOCAL_MACHINE, path.c_str(), 0, KEY_QUERY_VALUE, &hKey );
	if( lRet != ERROR_SUCCESS )
		throw new ErrorMsg( "Error when opening registry key: (" + path + ")!" );

	/* Get value */
	lRet = RegQueryValueEx( hKey, value.c_str(), NULL, NULL, (LPBYTE) szAVRPath, &dwBufLen);
	if( (lRet != ERROR_SUCCESS) || (dwBufLen > BUFSIZE) )
		throw new ErrorMsg( "Error when reading key value: (" + value + ")!" );

	/* Clean up and return result */
	RegCloseKey( hKey );
	result = szAVRPath;
	return result;
}
#endif

/* end of file */

