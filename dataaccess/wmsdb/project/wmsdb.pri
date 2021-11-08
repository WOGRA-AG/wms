PRECOMPILED_HEADER = precompile.h

HEADERS += \
    $$PWD/../src/CdbQueryEnhancedDefault.h \
    $$PWD/../src/CdbQueryEnhancedDoubleRequest.h \
    $$PWD/precompile.h \
    ../src/CdbClassAccess.h \
    ../src/CdbDataAccess.h \
    ../src/CdbDataStructureHelper.h \
    ../src/CdbDbAccess.h \
    ../src/CdbJournal.h \
    ../src/CdbLoginManager.h \
    ../src/CdbObjectAccess.h \
    ../src/CdbQuery.h \
    ../src/CdbQueryElement.h \
    ../src/CdbUserManager.h \
    ../src/CdbDataAccessPlugin.h \
    ../src/CdbDataAccessConfigurator.h \
    $$PWD/../src/CdbCommandCreatePackage.h \
    $$PWD/../src/CdbCommandUpdatePackage.h \
    $$PWD/../src/CdbCommandDeletePackage.h \
    $$PWD/../src/CdbCommandLoadPackages.h \
    $$PWD/../src/CdbCommandExistClass.h \
    $$PWD/../src/CdbCommandGetClass.h \
    $$PWD/../src/CdbCommandGetNewClassId.h \
    $$PWD/../src/CdbCommandDeleteClass.h \
    $$PWD/../src/CdbCommandLockMethod.h \
    $$PWD/../src/CdbCommandUnlockMethod.h \
    $$PWD/../src/CdbCommandLoadClassManager.h \
    $$PWD/../src/CdbCommandUpdateClass.h \
    $$PWD/../src/CdbCommandLogin.h \
    $$PWD/../src/CdbCommandLicenceCheck.h \
    $$PWD/../src/CdbCommandGetNewSession.h \
    $$PWD/../src/CdbCommandFindSession.h \
    $$PWD/../src/CdbCommandLogout.h \
    $$PWD/../src/CdbCommandCreateUser.h \
    $$PWD/../src/CdbCommandDeleteUser.h \
    $$PWD/../src/CdbCommandFindUser.h \
    $$PWD/../src/CdbAbstractCommand.h \
    $$PWD/../src/CdbCommandUpdateUser.h \
    $$PWD/../src/CdbCommandGetUserList.h \
    $$PWD/../src/CdbCommandExistUser.h \
    $$PWD/../src/CdbCommandRenameUserGroup.h \
    $$PWD/../src/CdbCommandCreateUserGroup.h \
    $$PWD/../src/CdbCommandDeleteUserGroup.h \
    $$PWD/../src/CdbCommandAddUserToUserGroup.h \
    $$PWD/../src/CdbCommandRemoveUserFromUserGroup.h \
    $$PWD/../src/CdbCommandGetUserGroupList.h \
    $$PWD/../src/CdbCommandGetGroupsOfUser.h \
    $$PWD/../src/CdbCommandFindUserGroup.h \
    $$PWD/../src/CdbCommandGetGroupUserList.h \
    $$PWD/../src/CdbCommandCreateScheme.h \
    $$PWD/../src/CdbCommandCleanupDB.h \
    $$PWD/../src/CdbCommandDeleteScheme.h \
    $$PWD/../src/CdbCommandExistScheme.h \
    $$PWD/../src/CdbCommandFindScheme.h \
    $$PWD/../src/CdbCommandGetSchemeList.h \
    $$PWD/../src/CdbCommandUpdateScheme.h \
    $$PWD/../src/CdbCommandDeleteSchemeLanguage.h \
    $$PWD/../src/CdbCommandAddSchemeLanguage.h \
    $$PWD/../src/CdbCommandDeleteContainer.h \
    $$PWD/../src/CdbCommandCheckObjectLocked.h \
    $$PWD/../src/CdbCommandDeleteObject.h \
    $$PWD/../src/CdbCommandExistContainer.h \
    $$PWD/../src/CdbCommandGetNewObjectId.h \
    $$PWD/../src/CdbCommandGetNewContainerId.h \
    $$PWD/../src/CdbCommandGetContainerList.h \
    $$PWD/../src/CdbCommandLoadObjects.h \
    $$PWD/../src/CdbCommandLoadSingleObject.h \
    $$PWD/../src/CdbCommandLoadContainer.h \
    $$PWD/../src/CdbCommandLockObject.h \
    $$PWD/../src/CdbCommandUnlockObject.h \
    $$PWD/../src/CdbCommandUpdateObject.h \
    $$PWD/../src/CdbCommandUpdateBinaryDocument.h \
    $$PWD/../src/CdbCommandRefreshObject.h \
    $$PWD/../src/CdbCommandRefreshComtainer.h \
    $$PWD/../src/CdbCommandGetCounterValue.h \
    $$PWD/../src/CdbCommandReadBinaryDocument.h \
    $$PWD/../src/CdbCommandUpdateContainer.h \
    $$PWD/../src/CdbCommandCheckObjectUsed.h \
    $$PWD/../src/CdbCommandCountObjectsOnDb.h \
    $$PWD/../src/CdbCommandGetObjectReferences.h \
    $$PWD/../src/CdbCommandUpdateSession.h \
    $$PWD/../src/CdbCommandCheckSessionTimeout.h\
    $$PWD/../src/CdbCommandGetOwner.h \
    $$PWD/../src/CdbInterface.h \
    $$PWD/../src/CdbCommandFindUserGroupById.h \
    $$PWD/../src/CdbCommandFindUserGroupByName.h \
    $$PWD/../src/CdbCommandFindGroups.h \
    $$PWD/../src/CdbAbstractCommandTransactional.h


contains(DEFINES, WMS_LDAP) {

HEADERS += $$PWD/../src/CdbCommandLdapLogin.h
}

SOURCES += ../src/CdbClassAccess.cpp \
    $$PWD/../src/CdbQueryEnhancedDefault.cpp \
    $$PWD/../src/CdbQueryEnhancedDoubleRequest.cpp \
    ../src/CdbDataAccess.cpp \
    ../src/CdbDataStructureHelper.cpp \
    ../src/CdbDbAccess.cpp \
    ../src/CdbJournal.cpp \
    ../src/CdbLoginManager.cpp \
    ../src/CdbObjectAccess.cpp \
    ../src/CdbQuery.cpp \
    ../src/CdbQueryElement.cpp \
    ../src/CdbUserManager.cpp \
    ../src/CdbDataAccessPlugin.cpp \
    ../src/CdbDataAccessConfigurator.cpp \
    $$PWD/../src/CdbCommandCreatePackage.cpp \
    $$PWD/../src/CdbCommandUpdatePackage.cpp \
    $$PWD/../src/CdbCommandDeletePackage.cpp \
    $$PWD/../src/CdbCommandLoadPackages.cpp \
    $$PWD/../src/CdbCommandExistClass.cpp \
    $$PWD/../src/CdbCommandGetClass.cpp \
    $$PWD/../src/CdbCommandGetNewClassId.cpp \
    $$PWD/../src/CdbCommandDeleteClass.cpp \
    $$PWD/../src/CdbCommandLockMethod.cpp \
    $$PWD/../src/CdbCommandUnlockMethod.cpp \
    $$PWD/../src/CdbCommandLoadClassManager.cpp \
    $$PWD/../src/CdbCommandUpdateClass.cpp \
    $$PWD/../src/CdbCommandLogin.cpp \
    $$PWD/../src/CdbCommandLicenceCheck.cpp \
    $$PWD/../src/CdbCommandGetNewSession.cpp \
    $$PWD/../src/CdbCommandFindSession.cpp \
    $$PWD/../src/CdbCommandLogout.cpp \
    $$PWD/../src/CdbCommandCreateUser.cpp \
    $$PWD/../src/CdbCommandDeleteUser.cpp \
    $$PWD/../src/CdbCommandFindUser.cpp \
    $$PWD/../src/CdbAbstractCommand.cpp \
    $$PWD/../src/CdbCommandUpdateUser.cpp \
    $$PWD/../src/CdbCommandGetUserList.cpp \
    $$PWD/../src/CdbCommandExistUser.cpp \
    $$PWD/../src/CdbCommandRenameUserGroup.cpp \
    $$PWD/../src/CdbCommandCreateUserGroup.cpp \
    $$PWD/../src/CdbCommandDeleteUserGroup.cpp \
    $$PWD/../src/CdbCommandAddUserToUserGroup.cpp \
    $$PWD/../src/CdbCommandRemoveUserFromUserGroup.cpp \
    $$PWD/../src/CdbCommandGetUserGroupList.cpp \
    $$PWD/../src/CdbCommandGetGroupsOfUser.cpp \
    $$PWD/../src/CdbCommandGetGroupUserList.cpp \
    $$PWD/../src/CdbCommandCreateScheme.cpp \
    $$PWD/../src/CdbCommandCleanupDB.cpp \
    $$PWD/../src/CdbCommandDeleteScheme.cpp \
    $$PWD/../src/CdbCommandExistScheme.cpp \
    $$PWD/../src/CdbCommandFindScheme.cpp \
    $$PWD/../src/CdbCommandGetSchemeList.cpp \
    $$PWD/../src/CdbCommandUpdateScheme.cpp \
    $$PWD/../src/CdbCommandDeleteSchemeLanguage.cpp \
    $$PWD/../src/CdbCommandAddSchemeLanguage.cpp \
    $$PWD/../src/CdbCommandDeleteContainer.cpp \
    $$PWD/../src/CdbCommandCheckObjectLocked.cpp \
    $$PWD/../src/CdbCommandDeleteObject.cpp \
    $$PWD/../src/CdbCommandExistContainer.cpp \
    $$PWD/../src/CdbCommandGetNewObjectId.cpp \
    $$PWD/../src/CdbCommandGetNewContainerId.cpp \
    $$PWD/../src/CdbCommandGetContainerList.cpp \
    $$PWD/../src/CdbCommandLoadObjects.cpp \
    $$PWD/../src/CdbCommandLoadSingleObject.cpp \
    $$PWD/../src/CdbCommandLoadContainer.cpp \
    $$PWD/../src/CdbCommandLockObject.cpp \
    $$PWD/../src/CdbCommandUnlockObject.cpp \
    $$PWD/../src/CdbCommandUpdateObject.cpp \
    $$PWD/../src/CdbCommandUpdateBinaryDocument.cpp \
    $$PWD/../src/CdbCommandRefreshObject.cpp \
    $$PWD/../src/CdbCommandRefreshComtainer.cpp \
    $$PWD/../src/CdbCommandGetCounterValue.cpp \
    $$PWD/../src/CdbCommandReadBinaryDocument.cpp \
    $$PWD/../src/CdbCommandUpdateContainer.cpp \
    $$PWD/../src/CdbCommandCheckObjectUsed.cpp \
    $$PWD/../src/CdbCommandCountObjectsOnDb.cpp \
    $$PWD/../src/CdbCommandGetObjectReferences.cpp \
    $$PWD/../src/CdbCommandUpdateSession.cpp \
    $$PWD/../src/CdbCommandCheckSessionTimeout.cpp \
    $$PWD/../src/CdbCommandGetOwner.cpp \
    $$PWD/../src/CdbInterface.cpp \
    $$PWD/../src/CdbCommandFindUserGroup.cpp \
    $$PWD/../src/CdbCommandFindUserGroupById.cpp \
    $$PWD/../src/CdbCommandFindUserGroupByName.cpp \
    $$PWD/../src/CdbCommandFindGroups.cpp \
    $$PWD/../src/CdbAbstractCommandTransactional.cpp


contains(DEFINES, WMS_LDAP) {
  SOURCES += $$PWD/../src/CdbCommandLdapLogin.cpp
}

RESOURCES += \
    ../src/wmsdb.qrc

lupdate_only {
    SOURCES = ../src/*.qml \
              ../src/*.js
}
