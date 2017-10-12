/*****************************************************************************
 *
 * Atmel Corporation
 *
 * File              : XMLParser.hpp
 * Compiler          : Dev-C++ 4.9.8.0 - http://bloodshed.net/dev/
 * Revision          : $Revision: 3419 $
 * Date              : $Date: 2008-02-22 09:56:34 +0100 (fr, 22 feb 2008) $
 * Updated by        : $Author: khole $
 *
 * Support mail      : avr@atmel.com
 *
 * Target platform   : Win32
 *
 * AppNote           : AVR911 - AVR Open-source Programmer
 *
 * Description       : A simple XML DOM-like parser. It builds a complete tree from
 *                     the XML file. IT supports <section/> tags, but not tag attributes.
 *
 * 
 ****************************************************************************/
#ifndef XMLPARSER_HPP
#define XMLPARSER_HPP

#include "ErrorMsg.hpp"
#include "Utility.hpp"
#include <iostream>
#include <fstream>
#include <list>

class XMLAbstractNode; // Preliminary definitions.
class XMLTree;
class XMLNode;


/* Main XML file class. Contains search methods and entire XML tree */
class XMLFile
{
	protected:
		XMLTree * root; // The root node, either a subtree or an ordinary node.

		void XMLFile::removeStartXML( std::string & txt ); // Remove the start xml tag.
		void removeComments( std::string & txt ); // Remove comment tags.
		void removeAttributes( std::string & txt ); // Remove attributes from tags.
		void readFile( const std::string & _filename ); // Read XML file.
		void parseFragment( std::string & fragment, XMLTree * parent );

	public:
		/* Constructors */
		XMLFile( const std::string & _filename );

		/* Destructor */
		~XMLFile();

		/* Methods */
		bool exists( const std::string & path ); // Checks if node exists.
		const std::string & getValue( const std::string & path ); // Get node value.

		void print();
};

#endif

