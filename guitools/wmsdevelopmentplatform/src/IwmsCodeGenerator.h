/******************************************************************************
 ** WOGRA technologies Gmbh & Co KG Modul Information
 ** Modulename: IwmsCodeGenerator.h
 ** Started Implementation: 2011/11/21
 ** Description:
 ** 
 ** The Interface for code generation
 **
 ** This file is provided AS IS with NO WARRANTY OF ANY KIND, INCLUDING THE
 ** WARRANTY OF DESIGN, MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE. 
 **(C) copyright by WOGRA technologies GmbH & Co KG All rights reserved
 *****************************************************************************/ 

#ifndef IWMSCODEGENERATOR_H
#define IWMSCODEGENERATOR_H

#ifdef WURZELBLA
#define slots
#endif //

// System and QT Includes


// Own Includes


// Forwards


// TypeDefs


/* 
 * The interface for code generation
 */
class IwmsCodeGenerator
{
public: virtual void GenerateCode() = 0;
public: virtual void SaveFiles() = 0;
};

#endif // IWMSCODEGENERATOR_H
