#ifndef WMSDEFINES_H
#define WMSDEFINES_H

#include "wmsServerDefines.h"

#define WMS_LIB_VERSION "3.0.1"
#define WMS_LIB_VERSION_MAJOR "3"
#define WMS_LIB_VERSION_MINOR "0"
#define WMS_LIB_VERSION_BUGFIX "1"


#define WMS_OBJECT "Object"
#define WMS_OBJECTID "ObjectId"
#define WMS_CLASS "Class"
#define WMS_CLASSID "ClassId"
#define WMS_CONTAINER "Container"
#define WMS_CONTAINERID "ContainerId"
#define WMS_FILENAME "Filename"
#define WMS_FILETYPE "Filetype"
#define WMS_VALUE "Value"
#define WMS_ABSTRACT "Abstract"
#define WMS_INUSE "InUse"
#define WMS_BASECLASSCOUNTER "BaseClassCounter"
#define WMS_VERSION "Version"
#define WMS_ANNOTATION "EAnnotation"
#define WMS_COMMENT "Comment"
#define WMS_PACKAGE "Package"
#define WMS_STRUCTURALFEATURE "EStructuralFeatures"
#define WMS_BASECLASSES "Baseclasses"
#define WMS_MEMBERSEQUENCE "MemberSequence"
#define WMS_METHODS "Methods"
#define DATASOURCE "datasource"
#define WMS_GROUPS "Groups"
#define WMS_VALIDATIONS "Validations"
#define WMS_CAPTIONMEMBER "CaptionMember"
#define WMS_POS "Pos"
#define WMS_KEYNAME "Keyname"
#define WMS_FULLQUALIFIEDNAME "FullQualifiedName"
#define WMS_CAPTION "Caption"
#define WMS_URI "Uri"
#define WMS_VALUETYPE "ValueType"
#define WMS_NAME "Name"
#define WMS_POSITION "Position"
#define WMS_ID "Id"
#define WMS_CHILDREN "Children"
#define WMS_RIGHTS "Rights"
#define WMS_TRANSLATIONS "Translations"
#define WMS_ECLASS "EClass"
#define WMS_CODE "Code"
#define WMS_TYPE "Type"
#define WMS_ACCESS "Access"
#define WMS_ACCESS_PRIVATE "Private"
#define WMS_ACCESS_PROTECTED "Protected"
#define WMS_ACCESS_PUBLIC "Public"
#define WMS_UNIQUE "Unique"
#define WMS_ICON "Icon"
#define WMS_PARAMETERS "Parameters"
#define WMS_REFERENCE "Reference"
#define WMS_VALIDATIONTYPE "ValidationType"
#define WMS_ERRORMESSAGE "ErrorMessage"
#define WMS_CLASSMANAGER "Class Manager"
#define WMS_LANGUAGES "Languages"
#define WMS_CONTAINERMANAGER "Container Manager"
#define WMS_USERMANAGER "User Manager"
#define WMS_USER "User"
#define WMS_USERGROUP "Usergroup"
#define WMS_SCHEME "Scheme"
#define WMS_URI_PACKAGE "package"
#define WMS_URI_SCHEME "scheme"
#define WMS_URI_DATABASE "database"
#define WMS_URI_CLASS "class"
#define WMS_URI_MEMBER "member"
#define WMS_URI_METHOD "method"
#define WMS_URI_CONTAINER "container"
#define WMS_URI_CONTAINER_MANAGER "containermanager"
#define WMS_URI_CLASS_MANAGER "classmanager"
#define WMS_URI_OBJECT "object"
#define WMS_URI_VALUE "value"
#define WMS_URI_USER "user"
#define WMS_URI_USERGROUP "usergroup"
#define WMS_URI_DATAPROVIDER "dataprovider"
#define WMS_DATAPROVIDER "Data Provider"
#define WMS_URI_UNKNOWN "unknown"
#define WMS_URI_START "http://wms.db"
#define WMS_URI_START_WITHOUT_HTPP "wms.db"
#define WMS_URI_START_HTTPS "https://wms.db"
#define WMS_HTTP "http://"
#define WMS_HTTPS "https://"
#define WMS_CURRENT_SCHEME "wms.currentScheme"
#define WMS_URI_START_SCHEME_INDEPENDENT "http://wms.currentScheme"
#define WMS_URI_START_SCHEME_INDEPENDENT_HTTPS "https://wms.currentScheme"
#define WMS_TECHNICAL "Technical"
#define WMS_TECHNICAL_SERVER "Technical_Server"
#define WMS_WORKFLOW "Workflow"
#define WMS_PERMANENT "Permanent"
#define WMS_MAP "Map"
#define WMS_LISTENTRIES "ListEntries"
#define WMS_ENTRY "Entry"
#define WMS_COUNT "Count"
#define WMS_KEY "key"
#define WMS_DATA "Data"
#define WMS_LIST "list"
#define WMS_SYSTEMVALUE "SystemValue"
#define WMS_SYSTEMPACKAGE "SystemPackage"
#define WMS_OWNER "Owner"
#define WMS_DEFAULT "Default"
#define WMS_COUNTERSTART "CounterStart"
#define WMS_VALIDATION "Validation"
#define WMS_PERSISTENT "Persistent"
#define WMS_MUST "Must"
#define WMS_TREE "Tree"
#define WMS_PREFIX "Prefix"
#define WMS_SUFFIX "Suffix"
#define WMS_DECIMALCOUNTINPUT "DecimalCountInput"
#define WMS_DECIMALCOUNTOUTPUT "DecimalCountOutput"
#define WMS_TRANSLATION "Translation"
#define WMS_CATEGORY "Category"
#define WMS_REFERENCEURI "ReferenceUri"
#define WMS_MEMBER "Member"
#define WMS_MEMBERID "MemberId"
#define WMS_MEMBERURI "MemberUri"
#define WMS_SIZE "Size"
#define WMS_VALUETYPENAME "ValueTypeName"
#define WMS_REFERENCEKEYNAME "Reference_Keyname"
#define WMS_CHANGEINFO "ChangeInfo"
#define WMS_MODIFIED "Modified"
#define WMS_NEW "New"
#define WMS_DELETED "Deleted"
#define WMS_MODIFIERID "ModifierId"
#define WMS_CREATORID "CreatorId"
#define WMS_LASTCHANGE "LastChange"
#define WMS_VALID "Valid"
#define WMS_DATABASEID "DatabaseId"
#define WMS_PARENTID "ParentId"
#define WMS_VALUES "Values"
#define WMS_CLASSURI "ClassUri"
#define WMS_CONTAINERURI "ContainerUri"
#define WMS_PARENTURI "ParentUri"
#define WMS_PARENTKEYNAME "ParentKeyname"
#define WMS_OBJECTS "Objects"
#define WMS_ACCESSORRIGHTS "AccessorRights"
#define WMS_ACCESSORID "AccessorId"
#define WMS_RIGHT "RIGHT"
#define WMS_CONTAINERS "Container"
#define WMS_OBJECTURI "ObjectUri"
#define WMS_STATIC "Static"
#define WMS_IMMUTABLE "Immutable"
#define WMS_SINGLETON "Singleton"
#define WMS_RETURNTYPE "Returntype"

#define WMS_EMF_TYPE_BOOL "EBoolean"
#define WMS_EMF_TYPE_INT "EInt"
#define WMS_EMF_TYPE_LONG "ELong"
#define WMS_EMF_TYPE_FLOAT "EFloat"
#define WMS_EMF_TYPE_DOUBLE "EDouble"
#define WMS_EMF_TYPE_STRING "EString"
#define WMS_EMF_TYPE_DATE "EDate"
#define WMS_EMF_TYPE_TIME "ETime"
#define WMS_EMF_TYPE_DATETIME "EDateTime"
#define WMS_EMF_TYPE_OBJECTREF "EObject"
#define WMS_EMF_TYPE_CONTAINER "ObjectList" // TODO: Rename !!! on both sides Java and WMS
#define WMS_EMF_TYPE_COUNTER "ECounter"
#define WMS_EMF_TYPE_BINARYDOCUMENT "EByteArray"
#define WMS_EMF_TYPE_CHARACTERDOCUMENT "EText"
#define WMS_EMF_TYPE_LISTDOUBLES "EEList<EFloat>"
#define WMS_EMF_TYPE_LISTINTS "EEList<EInt>"
#define WMS_EMF_TYPE_LISTOBJECTS "EEList<EObject>"
#define WMS_EMF_TYPE_LISTSTRINGS "EEList<EString>"
#define WMS_EMF_TYPE_DICTINTINT "EMap<EInt,EInt>"
#define WMS_EMF_TYPE_DICTINTDOUBLE "EMap<EInt,EFloat>"
#define WMS_EMF_TYPE_DICTINTSTRING "EMap<EInt,EString>"
#define WMS_EMF_TYPE_DICTSTRINGDOUBLE "EMap<EString,EFloat>"
#define WMS_EMF_TYPE_DICTSTRINGINT "EMap<EString,EInt>"
#define WMS_EMF_TYPE_DICTSTRINGSTRING "EMap<EString,EString>"
#define WMS_EMF_TYPE_USERGROUP "EUsergroup"
#define WMS_EMF_TYPE_USER "EUser"
#define WMS_EMF_TYPE_ENUM "Eenum"
#define WMS_EMF_TYPE_FORMULA "EFormula"

#define CLIENT_CONFIG_NAME "Client"
#define SERVER_CONFIG_NAME "Server"
#define DATA_ACCESS_CONFIG "dataAccessConfig"
#define DATA_ACCESS_CONFIG_SECTION "DataAccessConfigurations"
#define DATA_ACCESS_PLUGIN_NAME "dataAccessPluginName"
#define DATA_ACCESS_PLUGIN_FILE "dataAccessPluginFile"

#define WMS_URL_SERVER_HOST "urlserverhost"
#define WMS_URL_SERVER_PORT "urlserverport"
#define WMS_URL_SERVER_PATH "urlserverpath"
#define LDAP_USER_GROUP "Ldap_User_Group"
#define LDAP_ADMIN_GROUP "Ldap_Admin_Group"
#define LDAP_PASSWORD "Ldap_Passwd"
#define LDAP_ADMIN "Ldap_Admin"
#define LDAP_BASE_DN "Ldap_BaseDN"
#define LDAP_PORT "Ldap_Port"
#define LDAP_HOST "Ldap_Host"
#define LDAP_CONFIG "Ldap_Config"
#define LDAP_ACTIVE "Ldap_Active"
#define WMS_LOGIN "WmsLogin"
#define STORE_WMS_LOGIN "StoreWmsLogin"
#define BINARY_DIRECTORY "BinaryDirectory"
#define PASSWORD "Password"
#define DATAACCESS_PLUGIN_PATH "/dataaccess"
#define DATA_ACCESS_PLUGIN "DataAccessPlugin"
#define SERVER "Server"
#define SECOND_SERVER "second_Server"
#define PORT "Port"
#define SECOND_PORT "second_Port"
#define DRIVER "Driver"
#define SECOND_DRIVER "second_Driver"
#define DATABASE "Database"
#define SECOND_DATABASE "second_Database"
#define USER "User"
#define SECOND_USER "second_User"
#define PASSWORD "Password"
#define SECOND_PASSWORD "second_Password"
#define CONNECT_OPTIONS "ConnectOptions"
#define SECOND_CONNECT_OPTIONS "second_ConnectOptions"
#define POSITION "position"
#define LABEL "label"
#define TYPE "type"
#define SECOND_TYPE "second_type"
#define SELECTION "selection"
#define OPTION "option"
#define ENCRYPTED "encrypted"
#define VALUE "value"
#define NAME "name"
#define FILENAME "Filename"
#define ZIP "Zip"
#define SSL "Ssl"
#define SSL_CA_FILE "SslCaFile"
#define SSL_CLIENT_FILE "SslClientFile"
#define RFC "Rfc"
#define PROXY_SERVER "ProxyServer"
#define PROXY_PORT "ProxyPort"
#define PROXY_USER "ProxyUser"
#define PROXY_PASSWORD "ProxyPassword"
#define REGISTRATION_ALLOWED "Registration_Allowed"
#define COMPANY_REGISTRATION_ALLOWED "Company_Registration_Allowed"
#define MAX_MEMBER_COUNT 20
#define SCHEME_BASED_USERMANAGEMENT "SchemeBasedUserManagement"
#define SCHEME_BASED_USERMANAGEMENT_VALUE false
#define WMS_HREF "href"
#define WMS_SELF "self"
#define WMS_REL "rel"
#define WMS_DETAIL "details"
#define WMS_LINKS "_links"
#define WMS_LOG "_log"
#define WMS_EXECUTE "execute"
#define WMS_URI_CREATE "create"
#define WMS_CREATE "create object"
#define WMS_GRAPH "graph"
#define WMS_SIMPLE_REST_DATA "data"
#define WMS_FOLLOW_NON_OWNER_OBJECTLIST "followNonOwnerObjectlist"
#define WMS_FOLLOW_NON_OWNER_OBJECT "followNonOwnerObject"
#define WMS_EXCLUDED_KEYNAMES "excludedKeynames"
#define WMS_MAX_DEPTH "maxDepth"
#define WMS_MAX_OBJECTS "maxObjects"
#define WMS_PROCESSED_OBJECTS "wmsProcessedObjects"
#define WMS_URI_DELETE_ALL_OBJECTS "deleteAllObjects"
#define WMS_DELETE_ALL_OBJECTS "delete all objects"
#define WMS_WQL "WQL Query"
#define WMS_URI_WQL "wql"
#define WWW_AUTHENTICATE "WWW-Authenticate"
#define BASIC_REALM "Basic realm=\"Please insert username and password\""
#define WMS_FIND_BY_ID "find by id"
#define WMS_FIND_BY_KEYNAME "find by keyname"
#define WMS_GET_LIST_BY_CLASS_ID "getListByClassId"
#define WMS_GET_LIST_BY_CLASS_KEYNAME "getListByClassKeyname"
#define WMS_RESULT "result"
#define WMS_SUCCESS "success"
#define WMS_TRUE "true"
#define WMS_FALSE "false"
#define WMS_ERROR "error"
#define WMS_INFO "info"
#define WMS_VALUES "Values"
#define WMS_VALUE_DETAILS "ValueDetails"
#define WMS_MESSAGE "Message"
#define WMS_SET "set"
#define WMS_URI_SET "set"
#define WMS_CONTENT "content"
#define WMS_ADD "add"
#define WMS_INSERT "insert"
#define WMS_REMOVE "remove"
#define WMS_URI_FIND_USER "findUser"
#define WMS_FIND_USER "find User"
#define WMS_URI_FIND_USERGROUP "findUsergroups"
#define WMS_FIND_USERGROUP "find Usergroups"
#define WMS_URI_GET_SCHEMELIST "getSchemeList"
#define WMS_GET_SCHEMELIST "Scheme List"
#define WMS_CLASS_KEYNAME "classkeyname"


#define WMS_USER_FIRST_NAME "FirstName"
#define WMS_USER_LAST_NAME "LastName"
#define WMS_USER_LOGIN "Login"
#define WMS_USER_PASSWORD "Password"
#define WMS_USER_EMAIL "Email"
#define WMS_USER_ENCRYPTED "Encrypted"
#define WMS_USER_SCHEME_INDEPENDENT "SchemeIndependent"
#define WMS_USER_ADMIN "Admin"
#define WMS_USER_ID "Id"
#define WMS_USER_ACTIVE "Active"

#endif // // WMSDEFINES_H
