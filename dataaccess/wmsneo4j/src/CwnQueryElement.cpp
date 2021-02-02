#include "CwnQueryElement.h"
#include "CwnDataStructureHelper.h"

#include "CdmLogging.h"

#include <QMap>
#include <QDebug>
#include <CdmQuery.h>

CwnQueryElement::CwnQueryElement(CwnDataAccess *p_pCwnDataAccess, CdmQueryElement *p_pCdmQueryElement)
    : m_rpCwnDataAccess(p_pCwnDataAccess),
      m_rpCdmQueryElement(p_pCdmQueryElement)
{
    if(CHKPTR(m_rpCdmQueryElement) && CHKPTR(m_rpCwnDataAccess))
    {
       QLinkedList<CdmQueryElement*> qvlQueryElements;
       m_rpCdmQueryElement->GetChildList(qvlQueryElements);
       CreateChildren(qvlQueryElements);
    }
}

CwnQueryElement::~CwnQueryElement()
{
      m_qvlChildren.clear();
      m_rpCdmQueryElement = nullptr;
}

void CwnQueryElement::CreateChildren(QLinkedList<CdmQueryElement*>& p_qvlChildren)
{
   QLinkedList<CdmQueryElement*>::iterator qvlIt    = p_qvlChildren.begin();
   QLinkedList<CdmQueryElement*>::iterator qvlItEnd = p_qvlChildren.end();

   for (; qvlIt != qvlItEnd; ++qvlIt)
   {
      CdmQueryElement* pCdmQueryElement = (*qvlIt);

      if(CHKPTR(pCdmQueryElement))
      {
         CwnQueryElement* pCwnQueryElement = new CwnQueryElement(m_rpCwnDataAccess, pCdmQueryElement);
         m_qvlChildren.append(pCwnQueryElement);   
      }
   }
}

void CwnQueryElement::GenerateVariablesForLaterUse(QString& qstrQuery)
{
    if (m_qvlChildren.count() > 0)
    {
        QLinkedList<CwnQueryElement*>::iterator qvlIt = m_qvlChildren.begin();
        QLinkedList<CwnQueryElement*>::iterator qvlItEnd = m_qvlChildren.end();

        for (; qvlIt != qvlItEnd; ++qvlIt)
        {
            CwnQueryElement* pCwnQueryElement = (*qvlIt);

            if(CHKPTR(pCwnQueryElement))
            {
                pCwnQueryElement->GenerateVariablesForLaterUse(qstrQuery);
            }
        }
    }
    else
    {
        QString label = getLabel(m_rpCdmQueryElement->GetValueType());

        qstrQuery += QString("MATCH (o)-[:Object_value]->(v"+QString::number(CwnQueryVariables::s_value)+":WMS_VALUE"+label+")<-[:member_to_value]-(m"+QString::number(CwnQueryVariables::s_value)+":WMS_CLASS_MEMBER) ");
        QString fullKeyname;
        QStringList subStringKeyname;

        switch(m_rpCdmQueryElement->GetValueType())
        {
        case eDmValueObjectRef:
            fullKeyname=m_rpCdmQueryElement->GetCompareKeyname();
            if(fullKeyname.contains("."))
            {
                CdmQuery* pSubQuery = m_rpCdmQueryElement->GetSubQuery();

                if (CHKPTR(pSubQuery))
                {
                     pElement = pSubQuery->GetQueryElement();
                }
                label = getLabel(pElement->GetValueType());

                subStringKeyname = fullKeyname.split(".");
                if(CwnQueryVariables::referenceObjects.contains(subStringKeyname[0]))
                {
                    qstrQuery += QString(", (v%1)-[:objectRefValue]->(or%2)-[:Object_value]->(rv%3:WMS_VALUE"+label+")<-[:member_to_value]-(rm%4:WMS_CLASS_MEMBER) ")
                    .arg(CwnQueryVariables::s_value)
                    .arg(CwnQueryVariables::referenceObjects.value(subStringKeyname[0]))
                    .arg(CwnQueryVariables::rv_value++)
                    .arg(CwnQueryVariables::rm_value++);
                }
                else
                {
                    qstrQuery += QString(", (v%1)-[:objectRefValue]->(or%2:WMS_DM_OBJECT)-[:Object_value]->(rv%3:WMS_VALUE"+label+")<-[:member_to_value]-(rm%4:WMS_CLASS_MEMBER) ")
                    .arg(CwnQueryVariables::s_value)
                    .arg(CwnQueryVariables::vc_ro_value)
                    .arg(CwnQueryVariables::rv_value++)
                    .arg(CwnQueryVariables::rm_value++);
                    CwnQueryVariables::referenceObjects.insert(subStringKeyname[0],CwnQueryVariables::vc_ro_value++);
                }

                switch(pElement->GetValueType())
                {
                case eDmValueContainerRef:
                    qstrQuery += QString(",(rv"+QString::number(CwnQueryVariables::rv_value-1)+")-[:objectListRefValue]->(olr"+QString::number(CwnQueryVariables::olr_value)+":WMS_DM_OBJECTLIST) ");
                    CwnQueryVariables::olr_value++;
                    break;
                case eDmValueUser:
                    qstrQuery += QString(",(rv"+QString::number(CwnQueryVariables::rv_value-1)+")-[:userValue]->(u"+QString::number(CwnQueryVariables::u_value)+":User) ");
                    CwnQueryVariables::u_value++;
                    break;
                case eDmValueUserGroup:
                    qstrQuery += QString(",(rv"+QString::number(CwnQueryVariables::rv_value-1)+")-[:userGroupValue]->(ug"+QString::number(CwnQueryVariables::ug_value)+":Group) ");
                    CwnQueryVariables::ug_value++;
                    break;
                case eDmValueEnum:
                    qstrQuery += QString(",(rv"+QString::number(CwnQueryVariables::rv_value-1)+")-[:enumValue]->(e"+QString::number(CwnQueryVariables::e_value)+":Enum) ");
                    CwnQueryVariables::e_value++;
                    break;
                default:
                    break;
                }
            }
            else
            {
                qstrQuery += QString(",(v"+QString::number(CwnQueryVariables::s_value)+")-[:objectRefValue]->(or"+QString::number(CwnQueryVariables::or_value)+":WMS_DM_OBJECT) ");
            }
            CwnQueryVariables::or_value++;
            break;
        case eDmValueContainerRef:
            qstrQuery += QString(",(v"+QString::number(CwnQueryVariables::s_value)+")-[:objectListRefValue]->(olr"+QString::number(CwnQueryVariables::olr_value)+":WMS_DM_OBJECTLIST) ");
            CwnQueryVariables::olr_value++;
            break;
        case eDmValueUser:
            qstrQuery += QString(",(v"+QString::number(CwnQueryVariables::s_value)+")-[:userValue]->(u"+QString::number(CwnQueryVariables::u_value)+":User) ");
            CwnQueryVariables::u_value++;
            break;
        case eDmValueUserGroup:
            qstrQuery += QString(",(v"+QString::number(CwnQueryVariables::s_value)+")-[:userGroupValue]->(ug"+QString::number(CwnQueryVariables::ug_value)+":Group) ");
            CwnQueryVariables::ug_value++;
            break;
        case eDmValueEnum:
            qstrQuery += QString(",(v"+QString::number(CwnQueryVariables::s_value)+")-[:enumValue]->(e"+QString::number(CwnQueryVariables::e_value)+":Enum) ");
            CwnQueryVariables::e_value++;
            break;
        default:
            break;
        }
        CwnQueryVariables::s_value++;
     }
}

QString CwnQueryElement::GenerateQuery()
{
    QString qstrQuery = GenerateStatement();
    return qstrQuery;
}

QString CwnQueryElement::GenerateStatement()
{
    QString qstrQuery;
    switch(m_rpCdmQueryElement->GetQueryElementType())
    {
    case eDmQueryElementTypeAnd:
       qstrQuery += GenerateAndQuery();
       break;
    case eDmQueryElementTypeOr:
       qstrQuery += GenerateOrQuery();
       break;
    case eDmQueryElementTypeCompare:
       qstrQuery += GenerateValueQuery();
       break;
    default:
       ERR("Default in switch called, this enum does not exist here!!");
       break;
    }
    return qstrQuery;
}

QString CwnQueryElement::GenerateAndQuery()
{
    bool bLast = false;
    QString qstrQuery;

    if (m_qvlChildren.count() > 0)
    {
        QLinkedList<CwnQueryElement*>::iterator qvlIt = m_qvlChildren.begin();
        QLinkedList<CwnQueryElement*>::iterator qvlItEnd = m_qvlChildren.end();

        qstrQuery += " ( ";

        for (; qvlIt != qvlItEnd; ++qvlIt)
        {
            if(qvlIt == qvlItEnd-1)
                bLast=true;

            CwnQueryElement* pCwnQueryElement = (*qvlIt);

            if(CHKPTR(pCwnQueryElement))
            {
                QString qstrPartialQuery = pCwnQueryElement->GenerateStatement();

                if (!qstrPartialQuery.isEmpty())
                {
                    if(bLast)
                        qstrQuery += QString(qstrPartialQuery)+" ) ";
                    else
                        qstrQuery += QString(qstrPartialQuery)+ " AND ";
                }
            }
        }
    }
    return qstrQuery;
}

QString CwnQueryElement::GenerateOrQuery()
{
    QString qstrQuery;

    if (m_qvlChildren.count() > 0)
    {
        bool bLast = false;
        QLinkedList<CwnQueryElement*>::iterator qvlIt = m_qvlChildren.begin();
        QLinkedList<CwnQueryElement*>::iterator qvlItEnd = m_qvlChildren.end();

        qstrQuery += " ( ";

        for (; qvlIt != qvlItEnd; ++qvlIt)
        {
            if(qvlIt == qvlItEnd-1)
                bLast=true;

            CwnQueryElement* pCwnQueryElement = (*qvlIt);

            if(CHKPTR(pCwnQueryElement))
            {
                QString qstrPartialQuery = pCwnQueryElement->GenerateStatement();

                if (!qstrPartialQuery.isEmpty())
                {
                    if(bLast)
                        qstrQuery += QString(qstrPartialQuery)+" ) ";
                    else
                        qstrQuery += QString(qstrPartialQuery)+ " OR ";
                }
            }
        }
    }
    return qstrQuery;
}

QString CwnQueryElement::GenerateValueQuery()
{
    QString qstrQuery;
    CdmQuery* pCdmQuery = m_rpCdmQueryElement->GetQuery();
    QString fullKeyname=m_rpCdmQueryElement->GetCompareKeyname();

    QString variableType;
    QString variableNumber;
    QString qstrCompareKeyname;
    QString qstrValueDataField;
    QString qstrCompareSign;
    QString qstrCompareValue;
    QString joinVariable;

    if(fullKeyname.contains("."))
    {
        con_reference=true;

        CdmQuery* pSubQuery = m_rpCdmQueryElement->GetSubQuery();

        if (CHKPTR(pSubQuery))
        {
             pElement = pSubQuery->GetQueryElement();
        }

        QStringList subStringKeyname = fullKeyname.split(".");
        joinVariable = "m"+QString::number(CwnQueryVariables::s_value)+".Keyname='"+subStringKeyname[0]+"' AND";
        variableType = "r";
        variableNumber = QString::number(CwnQueryVariables::rm_value);
        qstrCompareKeyname = subStringKeyname[1];
        qstrValueDataField = GetVariableAndPropertyName();
        qstrCompareSign = GetCompareSign();
        qstrCompareValue = GetCompareValueAsString();
        CwnQueryVariables::rm_value++;
        CwnQueryVariables::rv_value++;
    }
    else
    {
        con_reference=false;
        variableType = "";
        variableNumber = QString::number(CwnQueryVariables::s_value);
        qstrCompareKeyname = CwnDataStructureHelper::GetFirstMember(CwnHelper::MaskStringForChanges(m_rpCdmQueryElement->GetCompareKeyname()));
        qstrValueDataField = GetVariableAndPropertyName();
        qstrCompareSign = GetCompareSign();
        qstrCompareValue = GetCompareValueAsString();

    }

    if(pCdmQuery)
    {
        if (!qstrCompareValue.isEmpty() && qstrCompareValue != "()")
        {
                if(m_rpCdmQueryElement->GetCompareType()==eDmQueryCompareTypeNotEqual && m_rpCdmQueryElement->GetValue()==eDmValueString)
                {
                    qstrQuery += QString("("+joinVariable+" "+variableType+"m"+variableNumber+".Keyname=\'%1\' AND NOT(%2%3%4) ")
                                    .arg(qstrCompareKeyname)
                                    .arg(qstrValueDataField)
                                    .arg(qstrCompareSign)
                                    .arg(qstrCompareValue);
                }
                else
                {
                    qstrQuery += QString("("+joinVariable+" "+variableType+"m"+variableNumber+".Keyname=\'%1\' AND %2%3%4) ")
                                    .arg(qstrCompareKeyname)
                                    .arg(qstrValueDataField)
                                    .arg(qstrCompareSign)
                                    .arg(qstrCompareValue);
                }

        }
        CwnQueryVariables::s_value++;
    }
    else
    {
        ERR("Comparevalue is Empty!");
        qstrQuery = "";
    }
    return qstrQuery;
}

QString CwnQueryElement::GetCompareValueAsString()
{
    if (!CHKPTR(m_rpCdmQueryElement))
    {
        return "m_rpCdmQuerElement no Value";
    }

   EdmValueType eDmValueType;
   QVariant qVariant;
   QString qstrValue;

   if(con_reference)
   {
       eDmValueType = pElement->GetValueType();
       qVariant = pElement->GetValue();

   }
   else
   {
       eDmValueType = m_rpCdmQueryElement->GetValueType();
       qVariant = m_rpCdmQueryElement->GetValue();
   }

   if (!qVariant.isValid() )
   {
       return "";
   }

    switch(eDmValueType)
    {
    case eDmValueObjectRef:
    case eDmValueContainerRef:
    case eDmValueUser:
    case eDmValueUserGroup:
    case eDmValueEnum:
    case eDmValueCounter:
    case eDmValueInt:
    case eDmValueLong:
       qstrValue = "toInt("+QString::number(qVariant.toInt())+")";
       break;
    case eDmValueBool:
       qstrValue = "\'"+CwnHelper::ConvertBoolToString(qVariant.toBool())+"\'";
       break;
    case eDmValueFloat:
    case eDmValueDouble:
       qstrValue = "toFloat("+QString::number(qVariant.toFloat())+")";
       break;
    case eDmValueString:
       if(qVariant.toString().contains("%"))
       {
          qstrValue = "\'(?i)" + qVariant.toString().toLower() + "\'";
          qstrValue.replace(QString("%"),QString(".*"));
       }
       else
       {
          qstrValue = "\'(?i)" + CwnHelper::MakeValueSave(qVariant.toString().toLower()) + "\'";
       }
        break;
    case eDmValueDate:
       qstrValue = "toInt("+QString::number(qVariant.toDate().toJulianDay())+")";
       break;
    case eDmValueDateTime:
       qstrValue = "toInt("+QString::number(qVariant.toDateTime().toTime_t())+")";
       break;
    case eDmValueTime:
       qstrValue = "toInt("+QString::number(QTime(0,0).secsTo(qVariant.toTime()))+")";
       break;
    // for this values queries are not possible neo4j saves CharDocs in base64
    case eDmValueCharacterDocument:
    case eDmValueBinaryDocument:
    case eDmValueListInt:
    case eDmValueListDouble:
    case eDmValueListString:
    case eDmValueDictStringInt:
    case eDmValueDictStringString:
    case eDmValueDictStringDouble:
    case eDmValueDictIntInt:
    case eDmValueDictIntString:
    case eDmValueDictIntDouble:
    default:
       ERR("Invalid Type for Comparision choosen ID: " + QString::number(eDmValueType));
       qstrValue = "Invalid Value";
       break;
    }

    return qstrValue;
}

QString CwnQueryElement::GetCompareSign()
{
    QString qstrRet;

    EdmQueryCompareType eDmQueryCompareType;
    bool isCompareTypeString = false;
    if(con_reference)
    {
        eDmQueryCompareType = pElement->GetCompareType();
        isCompareTypeString = (pElement->GetValueType()!=eDmValueString)?true:false;
    }
    else
    {
        eDmQueryCompareType = m_rpCdmQueryElement->GetCompareType();
        isCompareTypeString = (m_rpCdmQueryElement->GetValueType()!=eDmValueString)?true:false;

    }

    switch(eDmQueryCompareType)
    {
       case eDmQueryCompareTypeEqual:
            if(isCompareTypeString)
            {
                qstrRet = "=";
            }
            else
            {
                qstrRet = "=~";
            }
            break;
       case eDmQueryCompareTypeNotEqual:
            if(isCompareTypeString)
            {
                qstrRet = "<>";
            }
            else
            {
                qstrRet = "=~";
            }
            break;
       case eDmQueryCompareTypeSmaller:
          qstrRet = "<";
          break;
       case eDmQueryCompareTypeSmallerEqual:
          qstrRet = "<=";
          break;
       case eDmQueryCompareTypeLarger:
          qstrRet = ">";
          break;
       case eDmQueryCompareTypeLargerEqual:
          qstrRet = ">=";
          break;
       case eDmQueryCompareTypeLike:
          qstrRet = "=~";
          break;
       case eDmQueryCompareTypeIn:
          qstrRet = "IN";
          break;
       default:
          ERR("Unknown compare sign!!!");
          qstrRet = "?";
          break;
    };
    return qstrRet;

}

QString CwnQueryElement::GetVariableAndPropertyName()
{
    QString qstrRet;

    if (CHKPTR(m_rpCdmQueryElement))
    {
        EdmValueType eDmValueType;

        if(con_reference)
        {
            eDmValueType = pElement->GetValueType();
        }
        else
        {
            eDmValueType = m_rpCdmQueryElement->GetValueType();
        }

        switch(eDmValueType)
        {
        case eDmValueObjectRef:
            qstrRet = "id(or"+QString::number(CwnQueryVariables::or_value)+")";
            CwnQueryVariables::or_value++;
            break;
        case eDmValueContainerRef:
            qstrRet = "id(olr"+QString::number(CwnQueryVariables::olr_value)+")";
            CwnQueryVariables::olr_value++;
            break;
        case eDmValueUser:
            qstrRet = "id(u"+QString::number(CwnQueryVariables::u_value)+")";
            CwnQueryVariables::u_value++;
            break;
        case eDmValueUserGroup:
            qstrRet = "id(ug"+QString::number(CwnQueryVariables::ug_value)+")";
            CwnQueryVariables::ug_value++;
            break;
        case eDmValueEnum:
            qstrRet = "id(e"+QString::number(CwnQueryVariables::e_value)+")";
            CwnQueryVariables::e_value++;
            break;
        default:
            if(con_reference)
            {
                qstrRet = "rv"+QString::number(CwnQueryVariables::rv_value)+".val";
            }
            else
            {
                qstrRet = "v"+QString::number(CwnQueryVariables::s_value)+".val";
            }
            break;
        }
    }

    return qstrRet;

}

QString CwnQueryElement::getLabel(EdmValueType type)
{
    switch(type)
    {
    case eDmValueObjectRef:
        return ":OBJECTREF";
    case eDmValueContainerRef:
        return ":OBJECTLISTREF";
    case eDmValueUser:
        return ":USER";
    case eDmValueUserGroup:
        return ":USERGROUP";
    case eDmValueEnum:
        return ":ENUM";
    case eDmValueInt:
        return ":INTEGER";
    case eDmValueLong:
        return ":LONG";
    case eDmValueBool:
        return ":BOOLEAN";
    case eDmValueFloat:
        return ":FLOAT";
    case eDmValueDouble:
        return ":DOUBLE";
    case eDmValueString:
        return ":STRING";
    case eDmValueCharacterDocument:
        return ":CHARDOC";
    case eDmValueDate:
        return ":DATE";
    case eDmValueDateTime:
        return ":DATETIME";
    case eDmValueTime:
        return ":TIME";
    default:
        return "";
    }
}
