/******************************************************************************
 ** WOGRA Solutions Modul Information
 ** Modulename: basetools.h
 ** Started Implementation: 19.8.02
 ** Description:
 ** 
 ** Interface defintion file
 **
 ** This file is provided AS IS with NO WARRANTY OF ANY KIND, INCLUDING THE
 ** WARRANTY OF DESIGN, MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE. 
 **(C) copyright by WOGRA Solutions All rights reserved
 *****************************************************************************/ 

#ifndef BASETOOLS_H
#define BASETOOLS_H

// System and QT Includes
#include <QMap>
#include <QColor>

// own Includes


// forwards


#ifdef BASETOOLS_EXPORTS
  #define BASETOOLS_API Q_DECL_EXPORT
#else
  #define BASETOOLS_API Q_DECL_IMPORT
#endif

// defines
#define MAP(f,c) for (auto x : c) { if (x) x->f;}

#define WMS_DIALOG_STANDARD_FLAGS Qt::CustomizeWindowHint | Qt::WindowSystemMenuHint | Qt::WindowCloseButtonHint | Qt::WindowTitleHint
#define WMS_DIALOG_MAXIMIZE_FLAGS Qt::CustomizeWindowHint | Qt::WindowSystemMenuHint | Qt::WindowCloseButtonHint | Qt::WindowTitleHint | Qt::WindowMaximizeButtonHint

#define WMS_BASE_QT_STANDARD_DIALOG QDialog(p_pqwParent, WMS_DIALOG_STANDARD_FLAGS)
#define WMS_BASE_QT_MAXIMIZE_DIALOG QDialog(p_pqwParent, WMS_DIALOG_MAXIMIZE_FLAGS)



// enumerations
enum EwmsLvSorting
{
   eWmsLvSortingNone,
   eWmsLvSortingNumber,
   eWmsLvSortingDate,
   eWmsLvSortingString
};

enum EwmsLvObjectInUseHandling
{
   eWmsLvNone,
   eWmsLvWarning,
   eWmsLvForbid
};

// Typedefs
typedef QMap<int, QString> TIntStringMap;
typedef QMap<int, QColor>  TIntColorMap;

#endif //
