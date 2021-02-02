create table WMS_CLASS (Abstract boolean , Caption varchar(50) , CaptionMember int , ClassId SERIAL , Comment varchar(1000) , CreatorId int , DatabaseId int , Keyname varchar(50) , LastChange timestamp , ModifierId int , PositionSequence varchar(5000) , TempSessionId int , primary key (ClassId));

create table WMS_CLASS_MEMBER (Access int , Caption varchar(50) , ClassId int , Comment varchar(4000) , CounterStart int , CreatorId int , DataType int , DefaultValue varchar(1000) , Explicit boolean , Keyname varchar(50) , MemberId SERIAL , ModifierId int , Must boolean , ObjectRefClassId int , Owner boolean , Size int , System boolean , primary key (MemberId));

create table WMS_CLASS_BASECLASS (BaseClassId int , ClassId int , primary key (BaseClassId, ClassId));

create table WMS_DM_OBJECTLIST (Caption varchar(50) , ClassId int , Comment varchar(1000) , CreatorId int , Keyname varchar(50) , LastChange timestamp , ModifierId int , ObjectListId SERIAL , TempSessionId int , primary key (ObjectListId));

create table WMS_DM_OBJECT (Cache text , Caption varchar(50) , CreatorId int , Keyname varchar(50) , LastChange timestamp , ModifierId int , ObjectId SERIAL , ObjectListId int , TempSessionId int , primary key (ObjectId));

create table WMS_DM_LOCKEDOBJECT (ObjectId int , SessionId int , primary key (ObjectId, SessionId));

create table WMS_DM_ACCESSORRIGHT (AccessRight int , AccessorId int , ObjectListId int , primary key (AccessorId, ObjectListId));

create table WMS_VALUE (BaseType int , CreatorId int , LastChange timestamp , MemberId int , ModifierId int , ObjectId int , ValueId SERIAL , primary key (ValueId));

create table WMS_VALUE_BINARYDOCUMENT (BinaryDocumentId int , Filename varchar(32) , Type varchar(3) , Val bytea , primary key (BinaryDocumentId));

create table WMS_VALUE_BOOL (BoolId int , Val boolean , primary key (BoolId));

create table WMS_VALUE_CHARACTERDOCUMENT (CharacterDocumentId int , Val text , primary key (CharacterDocumentId));

create table WMS_VALUE_COUNTER (CounterId int , TimeStamp int , Val int , primary key (CounterId));

create table WMS_VALUE_DATE (DateId int , Val date , primary key (DateId));

create table WMS_VALUE_DATETIME (DateTimeId int , Val timestamp , primary key (DateTimeId));

create table WMS_DATABASE (DatabaseId SERIAL, DatabaseName varchar(50) NOT NULL UNIQUE , Version int , primary key (DatabaseId));

create table WMS_VALUE_DOUBLE (DoubleId int , Val float8 , primary key (DoubleId));

create table WMS_VALUE_FLOAT (FloatId int , Val float4 , primary key (FloatId));

create table WMS_VALUE_INT (IntId int , Val int , primary key (IntId));

create table WMS_VALUE_LONG (LongId int , Val bigint , primary key (LongId));

create table WMS_VALUE_OBJECTLISTREFERENCE (ClassId int , ObjectListId int , ObjectListReferenceId int , primary key (ObjectListReferenceId));

create table WMS_VALUE_OBJECTREFERENCE (ClassId int , ObjectId int , ObjectListid int , ObjectReferenceId int , primary key (ObjectReferenceId));

create table WMS_VALUE_STRING (StringId int , Val varchar(1000) , primary key (StringId));

create table WMS_VALUE_TIME (TimeId int , Val time , primary key (TimeId));

create table WMS_UM_ACCESSOR (AccessorId SERIAL , AccessorType int , NewAccessor boolean , primary key (AccessorId));

create table WMS_UM_USER (Active boolean , Admin boolean , Email varchar(70) , UserId int , firstname varchar(50) , lastname varchar(50) , login varchar(50) UNIQUE , pass varchar(50) NOT NULL , primary key (UserId));

create table WMS_UM_GROUP (GroupId int , Name varchar(50) UNIQUE , primary key (GroupId));

create table WMS_UM_GROUPMEMBER (GroupId int , UserId int , primary key (GroupId, UserId));

create table WMS_UM_SESSION (Application varchar(100) , LoginDate timestamp , LogoutDate timestamp , SessionId SERIAL , State boolean , UserId int , primary key (SessionId));

create table WMS_UM_LICENSEKEY (Application varchar(100) NOT NULL , Licensee varchar(100) , Licensekey varchar(100) , primary key (Application, Licensee));

create table WMS_VERSION (Current_Version int NOT NULL , primary key (Current_Version));

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

delete from WMS_VERSION;

insert into WMS_VERSION (Current_Version) values (4);

insert into WMS_UM_ACCESSOR (accessorId, accessortype, newaccessor) values (1, 1, true);

insert into WMS_UM_USER (userid, firstname, lastname, login, pass, admin, active) values(1, 'admin', 'admin', 'admin', 'admin', true, true);

