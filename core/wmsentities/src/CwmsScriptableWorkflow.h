/******************************************************************************
 ** WOGRA technologies Gmbh & Co KG Modul Information
 ** Modulename: CwmsScriptableWorkflow.h
 ** Started Implementation: 2012/12/30
 ** Description:
 ** 
 ** implements the scriptinterface for workflows
 **
 ** This file is provided AS IS with NO WARRANTY OF ANY KIND, INCLUDING THE
 ** WARRANTY OF DESIGN, MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE. 
 **(C) copyright by WOGRA technologies GmbH & Co KG All rights reserved
 *****************************************************************************/ 

#ifndef CWMSSCRIPTABLEWORKFLOW_H
#define CWMSSCRIPTABLEWORKFLOW_H

#ifdef WURZELBLA
#define slots
#endif //

// System and QT Includes
#include <QScriptable>
#include <QObject>

// Own Includes
#include "CwmsScriptableBase.h"
#include "basetools.h"

// Forwards
class CdmObject;

// TypeDefs


/* 
 * This class implements the scriptinterface for workflows
 */
class BASETOOLS_API CwmsScriptableWorkflow : public CwmsScriptableBase
{
   Q_OBJECT

   public:
   /** +-=---------------------------------------------------------So 30. Dez 12:39:00 2012-------*
    * @method  CwmsScriptableWorkflow::CwmsScriptableWorkflow // public                           *
    * @return                                                //                                   *
    * @comment                                                                                    *
    *----------------last changed: -----------------------------So 30. Dez 12:39:00 2012----------*/
    CwmsScriptableWorkflow( );

   public:
   /** +-=---------------------------------------------------------So 30. Dez 12:39:06 2012-------*
    * @method  CwmsScriptableWorkflow::~CwmsScriptableWorkflow // public, virtual                 *
    * @return  void                                          //                                   *
    * @comment The Destructor of Class CwmsScriptableWorkflow                                     *
    *----------------last changed: -----------------------------So 30. Dez 12:39:06 2012----------*/
    virtual ~CwmsScriptableWorkflow( );

    public slots:
         /** +-=---------------------------------------------------------So 30. Dez 12:39:30 2012-------*
    * @method  CwmsScriptableWorkflow::StartWorkflow         // public, slots                     *
    * @return  void                                          //                                   *
    * @param   CdmObject* p_pCdmObject                       //                                   *
    * @comment                                                                                    *
    *----------------last changed: -----------------------------So 30. Dez 12:39:30 2012----------*/
void StartWorkflow( CdmObject* p_pCdmObject);

    public slots:
         /** +-=---------------------------------------------------------So 30. Dez 12:39:53 2012-------*
    * @method  CwmsScriptableWorkflow::UpdateWorkflow        // public, slots                     *
    * @return  void                                          //                                   *
    * @param   CdmObject* p_pCdmObject                       //                                   *
    * @comment                                                                                    *
    *----------------last changed: -----------------------------So 30. Dez 12:39:53 2012----------*/
void UpdateWorkflow( CdmObject* p_pCdmObject);
};

#endif // CWMSSCRIPTABLEWORKFLOW_H
