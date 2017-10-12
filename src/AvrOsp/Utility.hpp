/*****************************************************************************
 *
 * Atmel Corporation
 *
 * File              : Utility.hpp
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
#ifndef UTILITY_HPP
#define UTILITY_HPP

#ifndef NOREGISTRY
#define WIN32_LEAN_AND_MEAN
#include <windows.h>
#endif

#include <Rpc.h>
#include <locale>
#include <codecvt>
#include <vector>
#include <string>
#include "ErrorMsg.hpp"

class Utility
{
	protected:
		bool noLog;
		bool noProgress;

	public:
		/* Constructor */
		Utility();

		/* Destructor */
		~Utility();

		/* Methods */
		void muteLog() { noLog = true; }
		void muteProgress() { noProgress = true; }

		void log( const std::string & txt );
		void progress( const std::string & txt );

		long convertHex( const std::string & txt );
		std::string convertLong( long num, long radix = 10 );

		void parsePath( std::vector<std::string> & list );
		bool fileExists( std::string filename );
		void saveString( std::string txt, std::string filename );

		std::string getLastError();

		void handleMallocFailure(unsigned long size);

		std::string guidToString(GUID uuid);

		std::string convertToString(std::wstring value);

#ifndef NOREGISTRY	
		std::string getRegistryValue( const std::string & path, const std::string & value );
#endif
};

extern Utility Util;

#endif

