PRECOMPILED_HEADER = precompile.h

HEADERS += \
    $$PWD/precompile.h \
    ../src/CftlClassAccess.h \
    ../src/CftlDataAccess.h \
    ../src/CftlDataStructureHelper.h \
    ../src/CftlDbAccess.h \
    ../src/CftlHelper.h \
    ../src/CftlJournal.h \
    ../src/CftlLoginManager.h \
    ../src/CftlObjectAccess.h \
    ../src/CftlUserManager.h \
    ../src/CftlDataAccessPlugin.h \
    ../src/CftlDataAccessConfigurator.h \
    $$PWD/../src/CftlCommandCreatePackage.h \
    $$PWD/../src/CftlCommandUpdatePackage.h \
    $$PWD/../src/CftlCommandDeletePackage.h \
    $$PWD/../src/CftlCommandLoadPackages.h \
    $$PWD/../src/CftlCommandExistClass.h \
    $$PWD/../src/CftlCommandGetClass.h \
    $$PWD/../src/CftlCommandGetNewClassId.h \
    $$PWD/../src/CftlCommandDeleteClass.h \
    $$PWD/../src/CftlCommandLockMethod.h \
    $$PWD/../src/CftlCommandUnlockMethod.h \
    $$PWD/../src/CftlCommandLoadClassManager.h \
    $$PWD/../src/CftlCommandUpdateClass.h \
    $$PWD/../src/CftlCommandLogin.h \
    $$PWD/../src/CftlCommandLicenceCheck.h \
    $$PWD/../src/CftlCommandGetNewSession.h \
    $$PWD/../src/CftlCommandFindSession.h \
    $$PWD/../src/CftlCommandLogout.h \
    $$PWD/../src/CftlCommandCreateUser.h \
    $$PWD/../src/CftlCommandDeleteUser.h \
    $$PWD/../src/CftlCommandFindUser.h \
    $$PWD/../src/CftlAbstractCommand.h \
    $$PWD/../src/CftlCommandUpdateUser.h \
    $$PWD/../src/CftlCommandGetUserList.h \
    $$PWD/../src/CftlCommandExistUser.h \
    $$PWD/../src/CftlCommandRenameUserGroup.h \
    $$PWD/../src/CftlCommandCreateUserGroup.h \
    $$PWD/../src/CftlCommandDeleteUserGroup.h \
    $$PWD/../src/CftlCommandAddUserToUserGroup.h \
    $$PWD/../src/CftlCommandRemoveUserFromUserGroup.h \
    $$PWD/../src/CftlCommandGetUserGroupList.h \
    $$PWD/../src/CftlCommandGetGroupsOfUser.h \
    $$PWD/../src/CftlCommandFindUserGroup.h \
    $$PWD/../src/CftlCommandGetGroupUserList.h \
    $$PWD/../src/CftlCommandCreateScheme.h \
    $$PWD/../src/CftlCommandCleanupDB.h \
    $$PWD/../src/CftlCommandDeleteScheme.h \
    $$PWD/../src/CftlCommandExistScheme.h \
    $$PWD/../src/CftlCommandFindScheme.h \
    $$PWD/../src/CftlCommandGetSchemeList.h \
    $$PWD/../src/CftlCommandUpdateScheme.h \
    $$PWD/../src/CftlCommandDeleteSchemeLanguage.h \
    $$PWD/../src/CftlCommandAddSchemeLanguage.h \
    $$PWD/../src/CftlCommandDeleteContainer.h \
    $$PWD/../src/CftlCommandCheckObjectLocked.h \
    $$PWD/../src/CftlCommandDeleteObject.h \
    $$PWD/../src/CftlCommandExistContainer.h \
    $$PWD/../src/CftlCommandGetNewObjectId.h \
    $$PWD/../src/CftlCommandGetNewContainerId.h \
    $$PWD/../src/CftlCommandGetContainerList.h \
    $$PWD/../src/CftlCommandLoadObjects.h \
    $$PWD/../src/CftlCommandLoadSingleObject.h \
    $$PWD/../src/CftlCommandLoadContainer.h \
    $$PWD/../src/CftlCommandLockObject.h \
    $$PWD/../src/CftlCommandUnlockObject.h \
    $$PWD/../src/CftlCommandUpdateObject.h \
    $$PWD/../src/CftlCommandUpdateBinaryDocument.h \
    $$PWD/../src/CftlCommandRefreshObject.h \
    $$PWD/../src/CftlCommandRefreshComtainer.h \
    $$PWD/../src/CftlCommandGetCounterValue.h \
    $$PWD/../src/CftlCommandReadBinaryDocument.h \
    $$PWD/../src/CftlCommandUpdateContainer.h \
    $$PWD/../src/CftlCommandCheckObjectUsed.h \
    $$PWD/../src/CftlCommandCountObjectsOnDb.h \
    $$PWD/../src/CftlCommandGetObjectReferences.h \
    $$PWD/../src/CftlCommandUpdateSession.h \
    $$PWD/../src/CftlCommandCheckSessionTimeout.h \
    $$PWD/../src/CftlCommandGetOwner.h \
    ../src/CftlCommandFindGroups.h \
    $$PWD/../src/CftlInterface.h \
    $$PWD/../src/CftlDialect.h \
    $$PWD/../src/CftlContainerTableBase.h \
    $$PWD/../src/CftlContainerTableCreate.h \
    $$PWD/../src/CftlContainerTableDrop.h \
    $$PWD/../src/CftlContainerTableAlter.h \
    $$PWD/../src/CftlContainerTableSelect.h \
    $$PWD/../src/CftlContainerTableInsert.h \
    $$PWD/../src/CftlContainerTableUpdate.h \
    $$PWD/../src/CftlObjectReader.h \
    $$PWD/../src/CftlCommandQuery.h \
    $$PWD/../src/CftlCommandQueryElement.h \
    $$PWD/../src/CftlCommandQueryEnhanced.h \
    $$PWD/../src/CftlAbstractTransactionalCommand.h \
    $$PWD/../src/CftlJoinData.h


contains(DEFINES, WMS_LDAP) {
HEADERS += $$PWD/../src/CftlCommandLdapLogin.h
}


SOURCES += ../src/CftlClassAccess.cpp \
    ../src/CftlDataAccess.cpp \
    ../src/CftlDataStructureHelper.cpp \
    ../src/CftlDbAccess.cpp \
    ../src/CftlHelper.cpp \
    ../src/CftlJournal.cpp \
    ../src/CftlLoginManager.cpp \
    ../src/CftlObjectAccess.cpp \
    ../src/CftlUserManager.cpp \
    ../src/CftlDataAccessPlugin.cpp \
    ../src/CftlDataAccessConfigurator.cpp \
    $$PWD/../src/CftlCommandCreatePackage.cpp \
    $$PWD/../src/CftlCommandUpdatePackage.cpp \
    $$PWD/../src/CftlCommandDeletePackage.cpp \
    $$PWD/../src/CftlCommandLoadPackages.cpp \
    $$PWD/../src/CftlCommandExistClass.cpp \
    $$PWD/../src/CftlCommandGetClass.cpp \
    $$PWD/../src/CftlCommandGetNewClassId.cpp \
    $$PWD/../src/CftlCommandDeleteClass.cpp \
    $$PWD/../src/CftlCommandLockMethod.cpp \
    $$PWD/../src/CftlCommandUnlockMethod.cpp \
    $$PWD/../src/CftlCommandLoadClassManager.cpp \
    $$PWD/../src/CftlCommandUpdateClass.cpp \
    $$PWD/../src/CftlCommandLogin.cpp \
    $$PWD/../src/CftlCommandLicenceCheck.cpp \
    $$PWD/../src/CftlCommandGetNewSession.cpp \
    $$PWD/../src/CftlCommandFindSession.cpp \
    $$PWD/../src/CftlCommandLogout.cpp \
    $$PWD/../src/CftlCommandCreateUser.cpp \
    $$PWD/../src/CftlCommandDeleteUser.cpp \
    $$PWD/../src/CftlCommandFindUser.cpp \
    $$PWD/../src/CftlAbstractCommand.cpp \
    $$PWD/../src/CftlCommandUpdateUser.cpp \
    $$PWD/../src/CftlCommandGetUserList.cpp \
    $$PWD/../src/CftlCommandExistUser.cpp \
    $$PWD/../src/CftlCommandRenameUserGroup.cpp \
    $$PWD/../src/CftlCommandCreateUserGroup.cpp \
    $$PWD/../src/CftlCommandDeleteUserGroup.cpp \
    $$PWD/../src/CftlCommandAddUserToUserGroup.cpp \
    $$PWD/../src/CftlCommandRemoveUserFromUserGroup.cpp \
    $$PWD/../src/CftlCommandGetUserGroupList.cpp \
    $$PWD/../src/CftlCommandGetGroupsOfUser.cpp \
    $$PWD/../src/CftlCommandFindUserGroup.cpp \
    $$PWD/../src/CftlCommandGetGroupUserList.cpp \
    $$PWD/../src/CftlCommandCreateScheme.cpp \
    $$PWD/../src/CftlCommandCleanupDB.cpp \
    $$PWD/../src/CftlCommandDeleteScheme.cpp \
    $$PWD/../src/CftlCommandExistScheme.cpp \
    $$PWD/../src/CftlCommandFindScheme.cpp \
    $$PWD/../src/CftlCommandGetSchemeList.cpp \
    $$PWD/../src/CftlCommandUpdateScheme.cpp \
    $$PWD/../src/CftlCommandDeleteSchemeLanguage.cpp \
    $$PWD/../src/CftlCommandAddSchemeLanguage.cpp \
    $$PWD/../src/CftlCommandDeleteContainer.cpp \
    $$PWD/../src/CftlCommandCheckObjectLocked.cpp \
    $$PWD/../src/CftlCommandDeleteObject.cpp \
    $$PWD/../src/CftlCommandExistContainer.cpp \
    $$PWD/../src/CftlCommandGetNewObjectId.cpp \
    $$PWD/../src/CftlCommandGetNewContainerId.cpp \
    $$PWD/../src/CftlCommandGetContainerList.cpp \
    $$PWD/../src/CftlCommandLoadObjects.cpp \
    $$PWD/../src/CftlCommandLoadSingleObject.cpp \
    $$PWD/../src/CftlCommandLoadContainer.cpp \
    $$PWD/../src/CftlCommandLockObject.cpp \
    $$PWD/../src/CftlCommandUnlockObject.cpp \
    $$PWD/../src/CftlCommandUpdateObject.cpp \
    $$PWD/../src/CftlCommandUpdateBinaryDocument.cpp \
    $$PWD/../src/CftlCommandRefreshObject.cpp \
    $$PWD/../src/CftlCommandRefreshComtainer.cpp \
    $$PWD/../src/CftlCommandGetCounterValue.cpp \
    $$PWD/../src/CftlCommandReadBinaryDocument.cpp \
    $$PWD/../src/CftlCommandUpdateContainer.cpp \
    $$PWD/../src/CftlCommandCheckObjectUsed.cpp \
    $$PWD/../src/CftlCommandCountObjectsOnDb.cpp \
    $$PWD/../src/CftlCommandGetObjectReferences.cpp \
    $$PWD/../src/CftlCommandUpdateSession.cpp \
    $$PWD/../src/CftlCommandCheckSessionTimeout.cpp \
    $$PWD/../src/CftlCommandGetOwner.cpp \
    ../src/CftlCommandFindGroups.cpp \
    $$PWD/../src/CftlInterface.cpp \
    $$PWD/../src/CftlDialect.cpp \
    $$PWD/../src/CftlContainerTableBase.cpp \
    $$PWD/../src/CftlContainerTableCreate.cpp \
    $$PWD/../src/CftlContainerTableDrop.cpp \
    $$PWD/../src/CftlContainerTableAlter.cpp \
    $$PWD/../src/CftlContainerTableSelect.cpp \
    $$PWD/../src/CftlContainerTableInsert.cpp \
    $$PWD/../src/CftlContainerTableUpdate.cpp \
    $$PWD/../src/CftlObjectReader.cpp \
    $$PWD/../src/CftlCommandQuery.cpp \
    $$PWD/../src/CftlCommandQueryElement.cpp \
    $$PWD/../src/CftlCommandQueryEnhanced.cpp \
    $$PWD/../src/CftlAbstractTransactionalCommand.cpp \
    $$PWD/../src/CftlJoinData.cpp


contains(DEFINES, WMS_LDAP) {
  SOURCES += $$PWD/../src/CftlCommandLdapLogin.cpp
}

RESOURCES += \
    ../src/wmsftl.qrc

lupdate_only {
    SOURCES = ../src/*.qml \
              ../src/*.js
}
