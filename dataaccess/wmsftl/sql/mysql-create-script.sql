create table WMS_CLASS (Abstract boolean , Caption varchar(255) , CaptionMember int , ClassId int auto_increment , Comment varchar(1000) , CreatorId int , SchemeId int , Keyname varchar(255) , LastChange timestamp , ModifierId int , PositionSequence varchar(5000) , TempSessionId int , primary key (ClassId));

create table WMS_CLASS_MEMBER (Access int , Caption varchar(255) , ClassId int , Comment varchar(4000) , CounterStart int , CreatorId int , DataType int , DefaultValue varchar(1000) , Explicit boolean , Keyname varchar(255) , MemberId int auto_increment , ModifierId int , Must boolean , ObjectRefClassId int , Owner boolean , Size int , System boolean , primary key (MemberId));

create table WMS_CLASS_BASECLASS (BaseClassId int , ClassId int , primary key (BaseClassId, ClassId));

create table WMS_DM_CONTAINER (Caption varchar(255) , ClassId int , Comment varchar(1000) , CreatorId int , Keyname varchar(255) , LastChange timestamp , ModifierId int , ContainerId int auto_increment , TempSessionId int , primary key (ContainerId));

create table WMS_DM_ACCESSORRIGHT (AccessRight int , AccessorId int , ContainerId int , primary key (AccessorId, ContainerId));

create table WMS_SCHEME (SchemeId int auto_increment , SchemeName varchar(255) NOT NULL UNIQUE , Version int , primary key (SchemeId));

create table WMS_DM_CONTAINER_REFERENCE (ContainerId int , Ref_Container_ID int, Ref_Object_ID int, owner boolean, primary key (ContainerId));

create table WMS_DM_OBJECT_REFERENCE (ObjectId int, ContainerId int , Ref_Object_ID int, Ref_Container_ID int, owner boolean, primary key (ObjectId, ContainerId));

create table WMS_UM_ACCESSOR (AccessorId int auto_increment , AccessorType int , NewAccessor boolean , primary key (AccessorId));

create table WMS_UM_USER (Active boolean , Admin boolean , Email varchar(70) , UserId int , firstname varchar(255) , lastname varchar(255) , login varchar(255) UNIQUE , pass varchar(255) NOT NULL , primary key (UserId));

create table WMS_UM_GROUP (GroupId int , Name varchar(255) UNIQUE , primary key (GroupId));

create table WMS_UM_GROUPMEMBER (GroupId int , UserId int , primary key (GroupId, UserId));

create table WMS_UM_SESSION (Application varchar(100) , LoginDate timestamp , SessionId int auto_increment, LogoutDate timestamp, State boolean , UserId int, BaseAuth varchar(255) , primary key (SessionId));


create table WMS_VERSION (Current_Version int NOT NULL , primary key (Current_Version));

CREATE  TABLE WMS_CLASS_MEMBER_RIGHTS (
  MemberId INT NOT NULL ,
  UserBaseId INT NOT NULL ,
  RightId INT NULL ,
  PRIMARY KEY (MemberId, UserBaseId) );
  
  CREATE  TABLE WMS_CLASS_MEMBER_TRANSLATION (
  MemberId INT NOT NULL ,
  Language VARCHAR(200) NOT NULL ,
  Caption VARCHAR(200) NOT NULL ,
  PRIMARY KEY (MemberId, Language) );
  
  CREATE  TABLE WMS_LANGUAGE (
  LanguageId INT NOT NULL auto_increment,
  SchemeId INT NOT NULL,
  Name VARCHAR(200) NOT NULL,
  PRIMARY KEY (LanguageId) );
  
  
  CREATE  TABLE WMS_CLASS_GROUP (
  CLASSID INT NOT NULL ,
  ID INT NOT NULL auto_increment,
  NAME VARCHAR(2000) NOT NULL ,
  PRIMARY KEY (ID) );
  
  CREATE  TABLE WMS_CLASS_GROUP_RIGHTS (
  GroupId INT NOT NULL ,
  UserBaseId INT NOT NULL ,
  RightId INT NULL ,
  PRIMARY KEY (GroupId, UserBaseId) );
  
    CREATE  TABLE WMS_CLASS_GROUP_TRANSLATION (
  GroupId INT NOT NULL ,
  Language VARCHAR(200) NOT NULL ,
  Caption VARCHAR(200) NOT NULL ,
  PRIMARY KEY (GroupId, Language) );
  
  CREATE  TABLE WMS_CLASS_METHOD_RIGHTS (
  MethodId INT NOT NULL auto_increment,
  UserBaseId INT NOT NULL ,
  RightId INT NULL ,
  PRIMARY KEY (MethodId, UserBaseId) );
  
  CREATE  TABLE WMS_CLASS_VALIDATION (
  ClassId INT NOT NULL ,
  Id INT NOT NULL auto_increment,
  Code LONGTEXT NULL ,
  PRIMARY KEY (Id));

  CREATE  TABLE WMS_CLASS_METHOD (
  Id INT NOT NULL auto_increment,
  ClassId INT NOT NULL ,
  Name VARCHAR(200) NOT NULL ,
  MethodType INT NULL ,
  Code LONGTEXT NULL ,
  PRIMARY KEY (id));
  
  CREATE  TABLE WMS_SCHEME_RIGHTS (
  SchemeId INT NOT NULL ,
  UserBaseId INT NOT NULL ,
  RightId INT NULL ,
  PRIMARY KEY (SchemeId, UserBaseId) );
  
  CREATE  TABLE WMS_JOURNAL (
  EntryId INT NOT NULL auto_increment,
  UserId INT NOT NULL ,
  SessionId INT NOT NULL ,
  DateTime TIMESTAMP NOT NULL ,
  CHANGEMODE INT NOT NULL ,
  SchemeId INT NOT NULL ,
  ContainerId INT  ,
  ObjectId INT NULL ,
  Member VARCHAR(2000) NULL ,
  JSON_Changes LONGTEXT NULL ,
  
  PRIMARY KEY (EntryId) );

create table WMS_CLASS_LOCKEDMETHOD (MethodId int , SessionId int , primary key (MethodId, SessionId));

alter table WMS_DM_ACCESSORRIGHT add foreign key (ContainerId) references WMS_DM_CONTAINER(ContainerId) on delete cascade;

alter table WMS_DM_CONTAINER add foreign key (ClassId) references WMS_CLASS(ClassId) on delete cascade;

alter table WMS_CLASS_MEMBER add foreign key (ClassId) references WMS_CLASS(ClassId) on delete cascade;

alter table WMS_CLASS_BASECLASS add foreign key (ClassId) references WMS_CLASS(ClassId) on delete cascade;

alter table WMS_CLASS_BASECLASS add foreign key (BaseClassId) references WMS_CLASS(ClassId) on delete cascade;

alter table WMS_UM_GROUPMEMBER add foreign key (GroupId) references WMS_UM_GROUP(GroupId) on delete cascade;

alter table WMS_UM_GROUPMEMBER add foreign key (UserId) references WMS_UM_USER(UserId) on delete cascade;

alter table WMS_UM_GROUP add foreign key (GroupId) references WMS_UM_ACCESSOR(AccessorId) on delete cascade;

alter table WMS_UM_USER add foreign key (UserId) references WMS_UM_ACCESSOR(AccessorId) on delete cascade;

alter table WMS_UM_SESSION add foreign key (UserId) references WMS_UM_ACCESSOR(AccessorId) on delete cascade;

alter table WMS_DM_ACCESSORRIGHT add foreign key (AccessorId) references WMS_UM_ACCESSOR(AccessorId) on delete cascade;


insert into WMS_UM_ACCESSOR (accessortype, newaccessor) values (1, false);

insert into WMS_UM_USER (userid, firstname, lastname, login, pass, admin, active) values(1, 'admin', 'admin', 'admin', 'admin', true, true);

insert into WMS_VERSION (Current_Version) values (1);

  
 ALTER TABLE WMS_CLASS_MEMBER ADD COLUMN GroupId INT NULL;  
 
 ALTER TABLE WMS_CLASS ADD COLUMN Version INT NULL;

 ALTER TABLE WMS_CLASS_VALIDATION ADD COLUMN Name VARCHAR(200) NULL;    

 ALTER TABLE WMS_CLASS_VALIDATION ADD COLUMN Message LONGTEXT NULL;    

 ALTER TABLE WMS_CLASS_VALIDATION ADD COLUMN ValidationType SMALLINT NULL;  

 ALTER TABLE WMS_CLASS_VALIDATION ADD COLUMN Version SMALLINT NULL;  

 ALTER TABLE WMS_CLASS_MEMBER ADD COLUMN Version INT NULL;

 ALTER TABLE WMS_CLASS_MEMBER ADD COLUMN Validation LONGTEXT NULL;

 ALTER TABLE WMS_CLASS_MEMBER ADD COLUMN Non_Persistent SMALLINT NULL;

 ALTER TABLE WMS_CLASS_MEMBER ADD COLUMN Is_Tree SMALLINT NULL;

 ALTER TABLE WMS_JOURNAL ADD COLUMN DisplayValue LONGTEXT NULL;

 ALTER TABLE WMS_DM_CONTAINER ADD COLUMN Version INT NULL;

 ALTER TABLE WMS_CLASS_GROUP ADD COLUMN Version INT NULL;

 ALTER TABLE WMS_CLASS_GROUP ADD COLUMN Position INT NULL;

 ALTER TABLE WMS_CLASS_GROUP ADD COLUMN Parent INT NULL;

 ALTER TABLE WMS_CLASS_METHOD ADD COLUMN Version INT NULL;

 ALTER TABLE WMS_CLASS_METHOD ADD COLUMN AccessMode INT NULL;

 ALTER TABLE WMS_CLASS_METHOD ADD COLUMN Parameters LONGTEXT NULL;

 ALTER TABLE WMS_CLASS_METHOD ADD COLUMN Comment LONGTEXT NULL;

 ALTER TABLE WMS_CLASS_METHOD ADD COLUMN Static SMALLINT NULL;

 ALTER TABLE WMS_UM_USER ADD COLUMN Encrypted SMALLINT NULL;

 ALTER TABLE WMS_DM_CONTAINER ADD COLUMN Tree SMALLINT NULL;

 ALTER TABLE WMS_CLASS_MEMBER_TRANSLATION ADD COLUMN Comment VARCHAR(4000) NULL;

 ALTER TABLE WMS_CLASS_METHOD ADD COLUMN Caption VARCHAR(200) NULL; 

 ALTER TABLE WMS_CLASS_METHOD ADD COLUMN Icon LONGTEXT NULL  AFTER Caption;

 ALTER TABLE WMS_DM_CONTAINER CHANGE COLUMN Keyname Keyname VARCHAR(255);

 ALTER TABLE WMS_DM_CONTAINER CHANGE COLUMN Caption Caption VARCHAR(255);

 ALTER TABLE WMS_DM_CONTAINER ADD COLUMN Config longtext NULL; 

CREATE TABLE WMS_CLASS_PACKAGE (
  URI VARCHAR(200) NOT NULL,
  System_Package SMALLINT(1) NULL,
  SchemeId  INT(11) NOT NULL,
  PRIMARY KEY (URI, SchemeId));
  
ALTER TABLE WMS_CLASS ADD COLUMN PACKAGE_URI VARCHAR(200) NULL DEFAULT NULL;

ALTER TABLE WMS_CLASS ADD COLUMN config LONGTEXT NULL;

ALTER TABLE WMS_CLASS_MEMBER ADD COLUMN config LONGTEXT NULL; 
  
ALTER TABLE WMS_UM_SESSION add column Last_Request timestamp;

ALTER TABLE WMS_UM_USER add column IdentityKey varchar(255);

CREATE  OR REPLACE VIEW v_active_sessions AS
SELECT sessionid, u.UserId, u.firstname, u.lastname, u.login, LoginDate, Last_Request, Application FROM WMS_UM_SESSION s inner join WMS_UM_USER u on u.UserId = s.UserId where State = 1 order by sessionid desc;

create index IDX_CLASS_KEYNAME on WMS_CLASS(KEYNAME);

create index IDX_CLASS_DBID on WMS_CLASS(SchemeId);

create index IDX_CLASS_ID on WMS_CLASS(CLASSID);

create index IDX_BASECLASS_ID on WMS_CLASS_BASECLASS(BASECLASSID);

create index IDX_BASECLASS_CLASSID on WMS_CLASS_BASECLASS(CLASSID);

create index IDX_MEMBER_CLASSID on WMS_CLASS_MEMBER(CLASSID);

create index IDX_MEMBER_MEMBERID on WMS_CLASS_MEMBER(MEMBERID);

create index IDX_DATABASE_DBID on WMS_SCHEME(SchemeId);

create index IDX_DATABASE_DBNAME on WMS_SCHEME(SchemeName);

create index IDX_ACCRIGHT_IDRIGHT on WMS_DM_ACCESSORRIGHT(ACCESSORID, ACCESSRIGHT);

create index IDX_OBJLIST_OBJLISTID on WMS_DM_CONTAINER(ContainerId);

create index IDX_OBJLIST_KEYNAME on WMS_DM_CONTAINER(KEYNAME);

create index IDX_ACCESSOR_ID on WMS_UM_ACCESSOR(ACCESSORID);

CREATE TABLE wms_um_accesor_scheme (
accessorId INT(11) NOT NULL,
SchemeUri VARCHAR(255) NOT NULL,
PRIMARY KEY (accessorId, SchemeUri));

ALTER TABLE wms_um_user
ADD COLUMN SchemeIndependent TINYINT(1) NULL DEFAULT 0;

UPDATE wms_version SET Current_Version='1'