create table WMS_CLASS (
Abstract boolean , 
Caption varchar(255) , 
CaptionMember int , 
ClassId int auto_increment , 
Comment varchar(1000) , 
CreatorId int , 
DatabaseId int , 
Keyname varchar(255) , 
LastChange timestamp , 
ModifierId int , 
PositionSequence varchar(5000) , 
TempSessionId int , 
primary key (ClassId));

create table WMS_CLASS_MEMBER (
Access int , 
Caption varchar(255) , 
ClassId int , 
Comment varchar(4000) , 
CounterStart int , 
CreatorId int , 
DataType int , 
DefaultValue varchar(1000) , 
Explicit boolean , 
Keyname varchar(255) , 
MemberId int auto_increment , 
ModifierId int , 
Must boolean , 
ObjectRefClassId int , 
Owner boolean , 
Size int , 
System boolean , 
primary key (MemberId));

create table WMS_CLASS_BASECLASS (
BaseClassId int , 
ClassId int , 
primary key (BaseClassId, ClassId));

create table WMS_DM_OBJECTLIST (
Caption varchar(255) , 
ClassId int , 
Comment varchar(1000) , 
CreatorId int , 
Keyname varchar(255) , 
LastChange timestamp , 
ModifierId int , 
ObjectListId int auto_increment , 
TempSessionId int , 
primary key (ObjectListId));

create table WMS_DM_OBJECT (
Cache longtext , 
Caption varchar(255) , 
CreatorId int , 
Keyname varchar(255) , 
LastChange timestamp , 
ModifierId int , 
ObjectId int auto_increment , 
ObjectListId int , 
TempSessionId int , 
primary key (ObjectId));

create table WMS_DM_LOCKEDOBJECT (ObjectId int , SessionId int , primary key (ObjectId, SessionId));

create table WMS_DM_ACCESSORRIGHT (AccessRight int , AccessorId int , ObjectListId int , primary key (AccessorId, ObjectListId));

create table WMS_VALUE (BaseType int , CreatorId int , LastChange timestamp , MemberId int , ModifierId int , ObjectId int , ValueId int auto_increment , primary key (ValueId));

create table WMS_VALUE_BINARYDOCUMENT (BinaryDocumentId int , Filename varchar(512) , Type varchar(256) , Val longblob , primary key (BinaryDocumentId));

create table WMS_VALUE_BOOL (BoolId int , Val boolean , primary key (BoolId));

create table WMS_VALUE_CHARACTERDOCUMENT (CharacterDocumentId int , Val longtext , primary key (CharacterDocumentId)) ENGINE=MyISAM;

create table WMS_VALUE_COUNTER (CounterId int , TimeStamp int , Val int , primary key (CounterId));

create table WMS_VALUE_DATE (DateId int , Val date , primary key (DateId));

create table WMS_VALUE_DATETIME (DateTimeId int , Val timestamp , primary key (DateTimeId));

create table WMS_DATABASE (DatabaseId int auto_increment , DatabaseName varchar(255) NOT NULL UNIQUE , Version int , primary key (DatabaseId));

create table WMS_VALUE_DOUBLE (DoubleId int , Val double , primary key (DoubleId));

create table WMS_VALUE_FLOAT (FloatId int , Val decimal(18,7) , primary key (FloatId));

create table WMS_VALUE_INT (IntId int , Val int , primary key (IntId));

create table WMS_VALUE_LONG (LongId int , Val bigint , primary key (LongId));

create table WMS_VALUE_OBJECTLISTREFERENCE (ClassId int , ObjectListId int , ObjectListReferenceId int , primary key (ObjectListReferenceId));

create table WMS_VALUE_OBJECTREFERENCE (ClassId int , ObjectId int , ObjectListid int , ObjectReferenceId int , primary key (ObjectReferenceId));

create table WMS_VALUE_STRING (StringId int , Val varchar(1000) , primary key (StringId)) ENGINE=MyISAM;

create table WMS_VALUE_TIME (TimeId int , Val time , primary key (TimeId));

create table WMS_UM_ACCESSOR (AccessorId int auto_increment , AccessorType int , NewAccessor boolean , primary key (AccessorId));

create table WMS_UM_USER (Active boolean , Admin boolean , SchemeIndependent boolean, Email varchar(70) , UserId int , firstname varchar(255) , lastname varchar(255) , login varchar(255) UNIQUE , pass varchar(255) NOT NULL , primary key (UserId));

create table WMS_UM_GROUP (GroupId int , Name varchar(255) UNIQUE , primary key (GroupId));

create table WMS_UM_GROUPMEMBER (GroupId int , UserId int , primary key (GroupId, UserId));

create table WMS_UM_SESSION (Application varchar(100) , LoginDate timestamp , SessionId int auto_increment, LogoutDate timestamp, State boolean , UserId int, BaseAuth varchar(255) , primary key (SessionId));

create table WMS_UM_LICENSEKEY (Application varchar(100) NOT NULL , Licensee varchar(100) , Licensekey varchar(100) , primary key (Application, Licensee));

create table WMS_VERSION (Current_Version int NOT NULL , primary key (Current_Version));

CREATE  TABLE `WMS_CLASS_MEMBER_RIGHTS` (
  `MemberId` INT NOT NULL ,
  `UserBaseId` INT NOT NULL ,
  `RightId` INT NULL ,
  PRIMARY KEY (`MemberId`, `UserBaseId`) );
  
  CREATE  TABLE `WMS_CLASS_MEMBER_TRANSLATION` (
  `MemberId` INT NOT NULL ,
  `Language` VARCHAR(200) NOT NULL ,
  `Caption` VARCHAR(200) NOT NULL ,
  PRIMARY KEY (`MemberId`, `Language`) );
  
  CREATE  TABLE `WMS_LANGUAGE` (
  `LanguageId` INT NOT NULL auto_increment,
  `DatabaseId` INT NOT NULL,
  `Name` VARCHAR(200) NOT NULL,
  PRIMARY KEY (`LanguageId`) );
  
  
  CREATE  TABLE `WMS_CLASS_GROUP` (
  `CLASSID` INT NOT NULL ,
  `ID` INT NOT NULL auto_increment,
  `NAME` VARCHAR(2000) NOT NULL ,
  PRIMARY KEY (`ID`) );
  
  CREATE  TABLE `WMS_CLASS_GROUP_RIGHTS` (
  `GroupId` INT NOT NULL ,
  `UserBaseId` INT NOT NULL ,
  `RightId` INT NULL ,
  PRIMARY KEY (`GroupId`, `UserBaseId`) );
  
    CREATE  TABLE `WMS_CLASS_GROUP_TRANSLATION` (
  `GroupId` INT NOT NULL ,
  `Language` VARCHAR(200) NOT NULL ,
  `Caption` VARCHAR(200) NOT NULL ,
  PRIMARY KEY (`GroupId`, `Language`) );
  
  CREATE  TABLE `WMS_CLASS_METHOD_RIGHTS` (
  `MethodId` INT NOT NULL auto_increment,
  `UserBaseId` INT NOT NULL ,
  `RightId` INT NULL ,
  PRIMARY KEY (`MethodId`, `UserBaseId`) );
  
  CREATE  TABLE `WMS_CLASS_VALIDATION` (
  `ClassId` INT NOT NULL ,
  `Id` INT NOT NULL auto_increment,
  `Code` LONGTEXT NULL ,
  PRIMARY KEY (`Id`));

  
  CREATE  TABLE `WMS_CLASS_METHOD` (
  `Id` INT NOT NULL auto_increment,
  `ClassId` INT NOT NULL ,
  `Name` VARCHAR(200) NOT NULL ,
  `MethodType` INT NULL ,
  `Code` LONGTEXT NULL ,
  PRIMARY KEY (`id`));
  
  CREATE  TABLE `WMS_DATABASE_RIGHTS` (
  `DatabaseId` INT NOT NULL ,
  `UserBaseId` INT NOT NULL ,
  `RightId` INT NULL ,
  PRIMARY KEY (`DatabaseId`, `UserBaseId`) );
  

  CREATE  TABLE `WMS_JOURNAL` (
  `EntryId` INT NOT NULL auto_increment,
  `UserId` INT NOT NULL ,
  `SessionId` INT NOT NULL ,
  `DateTime` TIMESTAMP NOT NULL ,
  `CHANGEMODE` INT NOT NULL ,
  `DatabaseId` INT NOT NULL ,
  `ObjectListId` INT  ,
  `ObjectId` INT NULL ,
  `Member` VARCHAR(2000) NULL ,
  `JSON_Changes` LONGTEXT NULL ,
  
  PRIMARY KEY (`EntryId`) );

create table WMS_CLASS_LOCKEDMETHOD (MethodId int , SessionId int , primary key (MethodId, SessionId));

alter table WMS_VALUE add foreign key (ObjectId) references WMS_DM_OBJECT(ObjectId) on delete cascade;

alter table WMS_VALUE_BINARYDOCUMENT add foreign key (BinaryDocumentId) references WMS_VALUE(ValueId) on delete cascade;

alter table WMS_VALUE_BOOL add foreign key (BoolId) references WMS_VALUE(ValueId) on delete cascade;

alter table WMS_VALUE_CHARACTERDOCUMENT add foreign key (CharacterDocumentId) references WMS_VALUE(ValueId) on delete cascade;

alter table WMS_VALUE_DATE add foreign key (DateId) references WMS_VALUE(ValueId) on delete cascade;

alter table WMS_VALUE_DATETIME add foreign key (DateTimeId) references WMS_VALUE(ValueId) on delete cascade;

alter table WMS_VALUE_STRING add foreign key (StringId) references WMS_VALUE(ValueId) on delete cascade;

alter table WMS_VALUE_DOUBLE add foreign key (DoubleId) references WMS_VALUE(ValueId) on delete cascade;

alter table WMS_VALUE_FLOAT add foreign key (FloatId) references WMS_VALUE(ValueId) on delete cascade;

alter table WMS_VALUE_INT add foreign key (IntId) references WMS_VALUE(ValueId) on delete cascade;

alter table WMS_VALUE_LONG add foreign key (LongId) references WMS_VALUE(ValueId) on delete cascade;

alter table WMS_VALUE_OBJECTLISTREFERENCE add foreign key (ObjectListReferenceId) references WMS_VALUE(ValueId) on delete cascade;

alter table WMS_VALUE_OBJECTREFERENCE add foreign key (ObjectReferenceId) references WMS_VALUE(ValueId) on delete cascade;

alter table WMS_VALUE_COUNTER add foreign key (CounterId) references WMS_VALUE(ValueId) on delete cascade;

alter table WMS_DM_ACCESSORRIGHT add foreign key (ObjectListId) references WMS_DM_OBJECTLIST(ObjectListId) on delete cascade;

alter table WMS_DM_OBJECTLIST add foreign key (ClassId) references WMS_CLASS(ClassId) on delete cascade;

alter table WMS_DM_OBJECT add foreign key (ObjectListId) references WMS_DM_OBJECTLIST(ObjectListId) on delete cascade;

alter table WMS_DM_LOCKEDOBJECT add foreign key (ObjectId) references WMS_DM_OBJECT(ObjectId) on delete cascade;

alter table WMS_DM_LOCKEDOBJECT add foreign key (SessionId) references WMS_UM_SESSION(SessionId) on delete cascade;

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

insert into WMS_VERSION (Current_Version) values (4);

  
 ALTER TABLE `WMS_CLASS_MEMBER` ADD COLUMN `GroupId` INT NULL;  
 
 ALTER TABLE `WMS_CLASS` ADD COLUMN `Version` INT NULL;
 
 ALTER TABLE `WMS_VALUE` ADD COLUMN `ContainerId` INT NULL;

 ALTER TABLE `WMS_CLASS_VALIDATION` ADD COLUMN `Name` VARCHAR(200) NULL;    

 ALTER TABLE `WMS_CLASS_VALIDATION` ADD COLUMN `Message` LONGTEXT NULL;    

 ALTER TABLE `WMS_CLASS_VALIDATION` ADD COLUMN `ValidationType` SMALLINT NULL;  

 ALTER TABLE `WMS_CLASS_VALIDATION` ADD COLUMN `Version` SMALLINT NULL;  

 ALTER TABLE `WMS_CLASS_MEMBER` ADD COLUMN `Version` INT NULL;

 ALTER TABLE `WMS_CLASS_MEMBER` ADD COLUMN `Validation` LONGTEXT NULL;

 ALTER TABLE `WMS_CLASS_MEMBER` ADD COLUMN `Non_Persistent` SMALLINT NULL;

 ALTER TABLE `WMS_CLASS_MEMBER` ADD COLUMN `Is_Tree` SMALLINT NULL;

 ALTER TABLE `WMS_JOURNAL` ADD COLUMN `DisplayValue` LONGTEXT NULL;

 ALTER TABLE `WMS_DM_OBJECTLIST` ADD COLUMN `Version` INT NULL;

 ALTER TABLE `WMS_CLASS_GROUP` ADD COLUMN `Version` INT NULL;

 ALTER TABLE `WMS_CLASS_GROUP` ADD COLUMN `Position` INT NULL;

 ALTER TABLE `WMS_CLASS_GROUP` ADD COLUMN `Parent` INT NULL;

 ALTER TABLE `WMS_CLASS_METHOD` ADD COLUMN `Version` INT NULL;

 ALTER TABLE `WMS_CLASS_METHOD` ADD COLUMN `AccessMode` INT NULL;

 ALTER TABLE `WMS_CLASS_METHOD` ADD COLUMN `Parameters` LONGTEXT NULL;

 ALTER TABLE `WMS_CLASS_METHOD` ADD COLUMN `Comment` LONGTEXT NULL;

 ALTER TABLE `WMS_CLASS_METHOD` ADD COLUMN `Static` SMALLINT NULL;

 ALTER TABLE `WMS_UM_USER` ADD COLUMN `Encrypted` SMALLINT NULL;

 ALTER TABLE `WMS_DM_OBJECT` ADD COLUMN `Parent` INT NULL;

 ALTER TABLE `WMS_DM_OBJECTLIST` ADD COLUMN `Tree` SMALLINT NULL;

 ALTER TABLE `WMS_CLASS_MEMBER_TRANSLATION` ADD COLUMN `Comment` VARCHAR(4000) NULL;

 ALTER TABLE `WMS_CLASS_METHOD` ADD COLUMN `Caption` VARCHAR(200) NULL; 

 ALTER TABLE `WMS_CLASS_METHOD` ADD COLUMN `Icon` LONGTEXT NULL  AFTER `Caption`;

 ALTER TABLE WMS_DM_OBJECTLIST CHANGE COLUMN `Keyname` `Keyname` VARCHAR(255);

 ALTER TABLE WMS_DM_OBJECT CHANGE COLUMN `Keyname` `Keyname` VARCHAR(255);

 ALTER TABLE WMS_DM_OBJECTLIST CHANGE COLUMN `Caption` `Caption` VARCHAR(255);

 ALTER TABLE WMS_DM_OBJECT CHANGE COLUMN `Caption` `Caption` VARCHAR(255);

 ALTER TABLE WMS_VALUE_BINARYDOCUMENT CHANGE COLUMN `Filename` `Filename` VARCHAR(255);
 
 ALTER TABLE `WMS_DM_OBJECT` ADD COLUMN `Config` longtext NULL; 
 
 ALTER TABLE `WMS_DM_OBJECTLIST` ADD COLUMN `Config` longtext NULL; 

CREATE TABLE `WMS_CLASS_PACKAGE` (
  `URI` VARCHAR(200) NOT NULL,
  `System_Package` SMALLINT(1) NULL,
  `SchemeId`  INT(11) NOT NULL,
  PRIMARY KEY (`URI`, `SchemeId`));
  
ALTER TABLE WMS_CLASS ADD COLUMN `PACKAGE_URI` VARCHAR(200) NULL DEFAULT NULL;

ALTER TABLE WMS_CLASS ADD COLUMN `config` LONGTEXT NULL;

ALTER TABLE WMS_CLASS_MEMBER ADD COLUMN `config` LONGTEXT NULL; 
  
ALTER TABLE WMS_UM_SESSION add column `Last_Request` timestamp;

ALTER TABLE WMS_UM_USER add column `IdentityKey` varchar(255);

create or replace view V_VALUE_BINARYDOCUMENT as
select v.valueid, v.objectid, v.ContainerId as objectlistid, v.memberid, cm.keyname, bd.val, bd.filename, bd.type, cm.classid as memberclassid
from 
WMS_VALUE v 
inner join WMS_VALUE_BINARYDOCUMENT bd on v.valueId = bd.binarydocumentId 
inner join WMS_CLASS_MEMBER as cm on cm.memberid = v.memberid;

create or replace view V_VALUE_STRING as
select v.valueid, v.objectid, v.ContainerId as objectlistid, v.memberid, cm.keyname, str.val, cm.classid as memberclassid
from 
WMS_VALUE v 
inner join WMS_VALUE_STRING str on v.valueId = str.stringId 
inner join WMS_CLASS_MEMBER as cm on cm.memberid = v.memberid;

create or replace view V_VALUE_BOOL as
select v.valueid, v.objectid, v.ContainerId as objectlistid, v.memberid, cm.keyname, b.val, cm.classid as memberclassid
from 
WMS_VALUE v 
inner join WMS_VALUE_BOOL b on v.valueId = b.boolId 
inner join WMS_CLASS_MEMBER as cm on cm.memberid = v.memberid;

create or replace view V_VALUE_CHARACTERDOCUMENT as
select v.valueid, v.objectid, v.ContainerId as objectlistid, v.memberid, cm.keyname, ch.val, cm.classid as memberclassid
from 
WMS_VALUE v 
inner join WMS_VALUE_CHARACTERDOCUMENT ch on v.valueId = ch.CharacterDocumentId 
inner join WMS_CLASS_MEMBER as cm on cm.memberid = v.memberid;

create or replace view V_VALUE_COUNTER as
select v.valueid, v.objectid, v.ContainerId as objectlistid, v.memberid, cm.keyname, c.val, cm.classid as memberclassid
from 
WMS_VALUE v 
inner join WMS_VALUE_COUNTER c on v.valueId = c.CounterId 
inner join WMS_CLASS_MEMBER as cm on cm.memberid = v.memberid;

create or replace view V_VALUE_DATE as
select v.valueid, v.objectid, v.ContainerId as objectlistid, v.memberid, cm.keyname, d.val, cm.classid as memberclassid
from 
WMS_VALUE v 
inner join WMS_VALUE_DATE d on v.valueId = d.DateId 
inner join WMS_CLASS_MEMBER as cm on cm.memberid = v.memberid;

create or replace view V_VALUE_DATETIME as
select v.valueid, v.objectid, v.ContainerId as objectlistid, v.memberid, cm.keyname, dt.val, cm.classid as memberclassid
from 
WMS_VALUE v 
inner join WMS_VALUE_DATETIME dt on v.valueId = dt.DateTimeId 
inner join WMS_CLASS_MEMBER as cm on cm.memberid = v.memberid;

create or replace view V_VALUE_FLOAT as
select v.valueid, v.objectid, v.ContainerId as objectlistid, v.memberid, cm.keyname, f.val, cm.classid as memberclassid
from 
WMS_VALUE v 
inner join WMS_VALUE_FLOAT f on v.valueId = f.FloatId 
inner join WMS_CLASS_MEMBER as cm on cm.memberid = v.memberid;

create or replace view V_VALUE_INT as
select v.valueid, v.objectid, v.ContainerId as objectlistid, v.memberid, cm.keyname, i.val, cm.classid as memberclassid
from 
WMS_VALUE v 
inner join WMS_VALUE_INT i on v.valueId = i.IntId 
inner join WMS_CLASS_MEMBER as cm on cm.memberid = v.memberid;

create or replace view V_VALUE_LONG as
select v.valueid, v.objectid, v.ContainerId as objectlistid, v.memberid, cm.keyname, l.val, cm.classid as memberclassid
from 
WMS_VALUE v 
inner join WMS_VALUE_LONG l on v.valueId = l.LongId 
inner join WMS_CLASS_MEMBER as cm on cm.memberid = v.memberid;

create or replace view V_VALUE_OBJECTLISTREFERENCE as
select v.valueid, v.objectid, v.ContainerId as objectlistid, v.memberid, cm.keyname, ol.ObjectListId as val, ol.classid, cm.owner, cm.classid as memberclassid
from 
WMS_VALUE v 
inner join WMS_VALUE_OBJECTLISTREFERENCE ol on v.valueId = ol.ObjectListReferenceId 
inner join WMS_CLASS_MEMBER as cm on cm.memberid = v.memberid;

create or replace view V_VALUE_OBJECTREFERENCE as
select v.valueid, v.objectid, v.ContainerId as objectlistid, v.memberid, cm.keyname, oref.ObjectId as val, oref.classid, oref.objectlistid as orefobjectlist, cm.owner, cm.classid as memberclassid
from 
WMS_VALUE v 
inner join WMS_VALUE_OBJECTREFERENCE oref on v.valueId = oref.ObjectReferenceId 
inner join WMS_CLASS_MEMBER as cm on cm.memberid = v.memberid;

create or replace view V_VALUE_TIME  as
select v.valueid, v.objectid, v.ContainerId as objectlistid, v.memberid, cm.keyname, t.val, cm.classid as memberclassid
from 
WMS_VALUE v 
inner join WMS_VALUE_TIME t on v.valueId = t.TimeId 
inner join WMS_CLASS_MEMBER as cm on cm.memberid = v.memberid;

create or replace view V_VALUE_DOUBLE as
select v.valueid, v.objectid, v.ContainerId as objectlistid, v.memberid, cm.keyname, f.val, cm.classid as memberclassid
from 
WMS_VALUE v 
inner join WMS_VALUE_DOUBLE f on v.valueId = f.DoubleId 
inner join WMS_CLASS_MEMBER as cm on cm.memberid = v.memberid;

CREATE  OR REPLACE VIEW `v_active_sessions` AS

SELECT sessionid, u.UserId, u.firstname, u.lastname, u.login, LoginDate, Last_Request, Application FROM WMS_UM_SESSION s inner join WMS_UM_USER u on u.UserId = s.UserId where State = 1 order by sessionid desc;

ALTER TABLE WMS_VALUE_BOOL ADD INDEX `IDX_BOOL_VAL` (`Val` ASC);

ALTER TABLE WMS_VALUE_CHARACTERDOCUMENT ADD FULLTEXT INDEX `IDX_CHARDOC_VAL` (`Val` ASC);

ALTER TABLE WMS_VALUE_INT ADD INDEX `IDX_INT_VAL` (`Val` ASC);

ALTER TABLE WMS_VALUE_BINARYDOCUMENT ADD INDEX `IDX_BINDOC_Filename` (`Filename` ASC);

ALTER TABLE WMS_VALUE_COUNTER ADD INDEX `IDX_COUNTER_VAL` (`Val` ASC);

ALTER TABLE WMS_VALUE_DATE ADD INDEX `IDX_DATE_VAL` (`Val` ASC);

ALTER TABLE WMS_VALUE_DATETIME ADD INDEX `IDX_DATETIME_VAL` (`Val` ASC);

ALTER TABLE WMS_VALUE_DOUBLE ADD INDEX `IDX_DOUBLE_VAL` (`Val` ASC);

ALTER TABLE WMS_VALUE_FLOAT ADD INDEX `IDX_FLOAT_VAL` (`Val` ASC);

ALTER TABLE WMS_VALUE_LONG ADD INDEX `IDX_LONG_VAL` (`Val` ASC);

ALTER TABLE WMS_VALUE_OBJECTLISTREFERENCE ADD INDEX `IDX_OBJLIST_VAL` (`OBJECTLISTID` ASC);

ALTER TABLE WMS_VALUE_OBJECTREFERENCE ADD INDEX `IDX_OBJREF_VAL` (`ObjectId` ASC, `ObjectListid` ASC);

ALTER TABLE WMS_VALUE_STRING ADD FULLTEXT INDEX `IDX_STRING_VAL` (`Val` ASC);

ALTER TABLE WMS_VALUE_TIME ADD INDEX `IDX_TIME_VAL` (`Val` ASC);

ALTER TABLE WMS_DM_OBJECT ADD INDEX `IDX_TMP_SESS_IDD` (`TEMPSESSIONID` ASC);

ALTER TABLE WMS_VALUE ADD INDEX `IDX_VALUE_MEMBER` (`MEMBERID` ASC);

ALTER TABLE WMS_VALUE_OBJECTREFERENCE ADD INDEX `IDX_OBJ_VAL` (`OBJECTID` ASC);

ALTER TABLE WMS_CLASS_MEMBER ADD INDEX `IDX_MEMBER_KEYNAME` (`KEYNAME` ASC);

create index IDX_CLASS_KEYNAME on WMS_CLASS(KEYNAME);

create index IDX_CLASS_DBID on WMS_CLASS(DATABASEID);

create index IDX_CLASS_ID on WMS_CLASS(CLASSID);

create index IDX_BASECLASS_ID on WMS_CLASS_BASECLASS(BASECLASSID);

create index IDX_BASECLASS_CLASSID on WMS_CLASS_BASECLASS(CLASSID);

create index IDX_MEMBER_CLASSID on WMS_CLASS_MEMBER(CLASSID);

create index IDX_MEMBER_MEMBERID on WMS_CLASS_MEMBER(MEMBERID);

create index IDX_DATABASE_DBID on WMS_DATABASE(DATABASEID);

create index IDX_DATABASE_DBNAME on WMS_DATABASE(DATABASENAME);

create index IDX_ACCRIGHT_IDRIGHT on WMS_DM_ACCESSORRIGHT(ACCESSORID, ACCESSRIGHT);

create index IDX_LOCKEDOBJ_OBJID on WMS_DM_LOCKEDOBJECT(OBJECTID);

create index IDX_OBJ_OBJID on WMS_DM_OBJECT(OBJECTID);

create index IDX_OBJ_OBJLISTID on WMS_DM_OBJECT(OBJECTLISTID);

create index IDX_OBJLIST_OBJLISTID on WMS_DM_OBJECTLIST(OBJECTLISTID);

create index IDX_OBJLIST_KEYNAME on WMS_DM_OBJECTLIST(KEYNAME);

create index IDX_ACCESSOR_ID on WMS_UM_ACCESSOR(ACCESSORID);

create index IDX_VALUE_ID on WMS_VALUE(VALUEID);

create index IDX_VALUE_OBJID on WMS_VALUE(OBJECTID);

create index IDX_BINDOC_ID on WMS_VALUE_BINARYDOCUMENT(BINARYDOCUMENTID);

create index IDX_BOOL_ID on WMS_VALUE_BOOL(BOOLID);

create index IDX_CHARDOC_ID on WMS_VALUE_CHARACTERDOCUMENT(CHARACTERDOCUMENTID);

create index IDX_COUNTER_ID on WMS_VALUE_COUNTER(COUNTERID);

create index IDX_DATE_ID on WMS_VALUE_DATE(DATEID);

create index IDX_DATETIME_ID on WMS_VALUE_DATETIME(DATETIMEID);

create index IDX_DOUBLE_ID on WMS_VALUE_DOUBLE(DOUBLEID);

create index IDX_FLOAT_ID on WMS_VALUE_FLOAT(FLOATID);

create index IDX_INT_ID on WMS_VALUE_INT(INTID);

create index IDX_LONG_ID on WMS_VALUE_LONG(LONGID);

create index IDX_OBJLISTREF_ID on WMS_VALUE_OBJECTLISTREFERENCE(OBJECTLISTREFERENCEID);

create index IDX_OBJREF_ID on WMS_VALUE_OBJECTREFERENCE(OBJECTREFERENCEID);

create index IDX_STRING_ID on WMS_VALUE_STRING(STRINGID);

create index IDX_TIME_ID on WMS_VALUE_TIME(TIMEID);

CREATE TABLE WMS_UM_ACCESOR_SCHEME (
accessorId INT(11) NOT NULL,
SchemeUri VARCHAR(255) NOT NULL,
PRIMARY KEY (accessorId, SchemeUri));


alter table WMS_VALUE add column containerid int(11)
update WMS_VALUE v inner join WMS_DM_OBJECT o on o.objectid = v.objectid set v.containerId = o.objectlistid where v.containerid is null
UPDATE WMS_VERSION SET Current_Version=7 where Current_Version>0;

