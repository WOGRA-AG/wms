CREATE TABLE WMS_CLASS
    (
        Abstract  Number(1) , Caption VARCHAR ( 50 ) , CaptionMember Number , ClassId Number , "COMMENT" VARCHAR ( 1000 ) , CreatorId Number , DatabaseId INT
        , Keyname VARCHAR ( 50 ) , LastChange TIMESTAMP , ModifierId Number , PositionSequence VARCHAR ( 4000 ) , TempSessionId Number , PRIMARY KEY ( ClassId )
    ) ;
	
CREATE TABLE WMS_CLASS_MEMBER
    (
        "ACCESS"            Number , Caption VARCHAR ( 50 ) , ClassId Number , "COMMENT" VARCHAR ( 4000 ) , CounterStart Number , CreatorId Number , DataType Number , DefaultValue VARCHAR (
        1000 ) , Explicit Number(1) , Keyname VARCHAR ( 50 ) , MemberId Number  , ModifierId Number , Must Number(1) , ObjectRefClassId Number , Owner Number(1)
        , "SIZE"            Number , System Number(1) , PRIMARY KEY ( MemberId )
    ) ;
	
CREATE TABLE WMS_CLASS_BASECLASS
    (
        BaseClassId Number , ClassId Number , PRIMARY KEY ( BaseClassId , ClassId )
    ) ;
	
CREATE TABLE WMS_DM_OBJECTLIST
    (
        Caption      VARCHAR ( 50 ) , ClassId Number , "COMMENT" VARCHAR ( 1000 ) , CreatorId Number , Keyname VARCHAR ( 50 ) , LastChange TIMESTAMP , ModifierId Number ,
        ObjectListId Number  , TempSessionId Number , PRIMARY KEY ( ObjectListId )
    ) ;
	
CREATE TABLE WMS_DM_OBJECT
    (
        "CACHE" clob , Caption VARCHAR ( 50 ) , CreatorId Number , Keyname VARCHAR ( 50 ) , LastChange TIMESTAMP , ModifierId Number , ObjectId Number 
        , ObjectListId           Number , TempSessionId Number , PRIMARY KEY ( ObjectId )
    ) ;
	
CREATE TABLE WMS_DM_LOCKEDOBJECT
    (
        ObjectId Number , SessionId Number , PRIMARY KEY ( ObjectId , SessionId )
    ) ;
	
CREATE TABLE WMS_DM_ACCESSORRIGHT
    (
        AccessRight Number , AccessorId Number , ObjectListId Number , PRIMARY KEY ( AccessorId , ObjectListId )
    ) ;
	
CREATE TABLE WMS_VALUE
    (
        BaseType Number , CreatorId Number , LastChange TIMESTAMP , MemberId Number , ModifierId Number , ObjectId Number , ValueId Number  , PRIMARY KEY ( ValueId
        )
    ) ;
	
CREATE TABLE WMS_VALUE_BINARYDOCUMENT
    (
        BinaryDocumentId Number , Filename VARCHAR ( 32 ) , Type VARCHAR ( 3 ) , Val blob , PRIMARY KEY ( BinaryDocumentId )
    ) ;
	
CREATE TABLE WMS_VALUE_BOOL
    (
        BoolId Number , Val Number(1) , PRIMARY KEY ( BoolId )
    ) ;
	
CREATE TABLE WMS_VALUE_CHARACTERDOCUMENT
    (
        CharacterDocumentId Number , Val CLOB , PRIMARY KEY ( CharacterDocumentId )
    ) ;
	
CREATE TABLE WMS_VALUE_COUNTER
    (
        CounterId Number , TIMESTAMP Number , Val Number , PRIMARY KEY ( CounterId )
    ) ;
	
CREATE TABLE WMS_VALUE_DATE
    (
        DateId Number , Val DATE , PRIMARY KEY ( DateId )
    ) ;
	
CREATE TABLE WMS_VALUE_DATETIME
    (
        DateTimeId Number , Val TIMESTAMP , PRIMARY KEY ( DateTimeId )
    ) ;
	
CREATE TABLE WMS_DATABASE
    (
        DatabaseId Number  , DatabaseName VARCHAR ( 50 ) NOT NULL  , Version Number , PRIMARY KEY ( DatabaseId ),
		CONSTRAINT WMS_DATABASE_unique UNIQUE (DatabaseName)
    ) ;

CREATE TABLE WMS_VALUE_DOUBLE
    (
        DoubleId Number , Val Number , PRIMARY KEY ( DoubleId )
    ) ;
	
CREATE TABLE WMS_VALUE_FLOAT
    (
        FloatId Number , Val Number , PRIMARY KEY ( FloatId )
    ) ;
	
CREATE TABLE WMS_VALUE_INT
    (
        IntId Number , Val Number , PRIMARY KEY ( IntId )
    ) ;
	
CREATE TABLE WMS_VALUE_LONG
    (
        LongId Number , Val Number , PRIMARY KEY ( LongId )
    ) ;
	
CREATE TABLE WMS_VALUE_OBJECTLISTREFERENCE
    (
        ClassId Number , ObjectListId Number , ObjectListReferenceId Number , PRIMARY KEY ( ObjectListReferenceId )
    ) ;
	
CREATE TABLE WMS_VALUE_OBJECTREFERENCE
    (
        ClassId Number , ObjectId Number , ObjectListid Number , ObjectReferenceId Number , PRIMARY KEY ( ObjectReferenceId )
    ) ;
	
CREATE TABLE WMS_VALUE_STRING
    (
        StringId Number , Val VARCHAR ( 1000 ) , PRIMARY KEY ( StringId )
    ) ;
	
CREATE TABLE WMS_VALUE_TIME
    (
        TimeId Number , Val Date , PRIMARY KEY ( TimeId )
    ) ;
	
CREATE TABLE WMS_UM_ACCESSOR
    (
        AccessorId Number  , AccessorType Number , NewAccessor Number(1) , PRIMARY KEY ( AccessorId )
    ) ;
	
CREATE TABLE WMS_UM_USER
    (
        Active Number(1) , Admin Number(1) , Email VARCHAR ( 70 ) , UserId Number , firstname VARCHAR ( 50 ) , lastname VARCHAR ( 50 ) , login VARCHAR ( 50 )  ,
        pass   VARCHAR ( 50 ) NOT NULL , PRIMARY KEY ( UserId ),
		CONSTRAINT WMS_UM_USER_unique UNIQUE (login)
    ) ;
	
CREATE TABLE WMS_UM_GROUP
    (
        GroupId Number , Name VARCHAR ( 50 )  , PRIMARY KEY ( GroupId ),
		CONSTRAINT WMS_UM_GROUP_unique UNIQUE (Name)
    ) ;
	
CREATE TABLE WMS_UM_GROUPMEMBER
    (
        GroupId Number , UserId Number , PRIMARY KEY ( GroupId , UserId )
    ) ;
	
CREATE TABLE WMS_UM_SESSION
    (
        Application VARCHAR ( 100 ) , LoginDate TIMESTAMP , LogoutDate TIMESTAMP , SessionId Number  , State Number(1) , UserId Number , PRIMARY KEY (
        SessionId )
    ) ;
	
CREATE TABLE WMS_UM_LICENSEKEY
    (
        Application VARCHAR ( 100 ) NOT NULL , Licensee VARCHAR ( 100 ) , Licensekey VARCHAR ( 100 ) , PRIMARY KEY ( Application , Licensee )
    ) ;
	
CREATE TABLE WMS_VERSION
    (
        Current_Version Number NOT NULL , PRIMARY KEY ( Current_Version )
    ) ;
	
CREATE TABLE WMS_CLASS_MEMBER_RIGHTS
    (
        MemberId Number NOT NULL , UserBaseId Number NOT NULL , RightId Number NULL , PRIMARY KEY ( MemberId , UserBaseId )
    ) ;
	
CREATE TABLE WMS_CLASS_MEMBER_TRANSLATION
    (
        MemberId Number NOT NULL , LanguageId Number NOT NULL , Caption VARCHAR ( 200 ) NOT NULL , PRIMARY KEY ( MemberId , LanguageId )
    ) ;
	
CREATE TABLE WMS_LANGUAGE
    (
        LanguageId Number NOT NULL  , DatabaseId Number NOT NULL , Name VARCHAR ( 200 ) NOT NULL , PRIMARY KEY ( LanguageId )
    ) ;
	
CREATE TABLE WMS_CLASS_GROUP
    (
        CLASSID Number NOT NULL , ID Number NOT NULL  , NAME VARCHAR ( 2000 ) NOT NULL , PRIMARY KEY ( ID )
    ) ;
	
CREATE TABLE WMS_CLASS_GROUP_RIGHTS
    (
        GroupId Number NOT NULL , UserBaseId Number NOT NULL , RightId Number NULL , PRIMARY KEY ( GroupId , UserBaseId )
    ) ;
	
CREATE TABLE WMS_CLASS_GROUP_TRANSLATION
    (
        GroupId Number NOT NULL , LanguageId Number NOT NULL , Caption VARCHAR ( 2000 ) NOT NULL , PRIMARY KEY ( GroupId , LanguageId )
    ) ;
	
CREATE TABLE WMS_CLASS_METHOD_RIGHTS
    (
        MethodId Number NOT NULL  , UserBaseId Number NOT NULL , RightId Number NULL , PRIMARY KEY ( MethodId , UserBaseId )
    ) ;
	
CREATE TABLE WMS_CLASS_VALIDATION
    (
        ClassId Number NOT NULL , Id Number NOT NULL  , Code clob NULL , PRIMARY KEY ( Id )
    ) ;
	
CREATE TABLE WMS_CLASS_METHOD
    (
        Id Number NOT NULL  , ClassId Number NOT NULL , Name VARCHAR ( 200 ) NOT NULL , MethodType Number NULL , Code clob NULL , PRIMARY
        KEY ( id )
    ) ;
	
CREATE TABLE WMS_DATABASE_RIGHTS
    (
        DatabaseId Number NOT NULL , UserBaseId Number NOT NULL , RightId Number NULL , PRIMARY KEY ( DatabaseId , UserBaseId )
    ) ;
	 
CREATE TABLE WMS_JOURNAL
    (
        EntryId    Number NOT NULL  , UserId Number NOT NULL , SessionId Number NOT NULL , DateTime TIMESTAMP NOT NULL , CHANGEMODE Number NOT NULL ,
        DatabaseId Number NOT NULL , ObjectListId Number , ObjectId Number NULL , Member VARCHAR ( 2000 ) NULL , JSON_Changes clob NULL , PRIMARY KEY (
        EntryId )
    ) ;
	
-- create trigger/sequences for tables --	
-- create trigger/sequences for tables --	
create sequence WMS_CLASS_seq
start with 1
increment by 1
nomaxvalue; 	

create trigger WMS_CLASS_trigger
before insert on WMS_CLASS
for each row
begin
select WMS_CLASS_seq.nextval into :new.ClassId from dual; end;
/ 
	
create sequence WMS_CLASS_MEMBER_seq
start with 1
increment by 1
nomaxvalue; 	

create trigger WMS_CLASS_MEMBER_trigger
before insert on WMS_CLASS_MEMBER
for each row
begin
select WMS_CLASS_MEMBER_seq.nextval into :new.MemberId from dual; end;	
/ 

create sequence WMS_DM_OBJECTLIST_seq
start with 1
increment by 1
nomaxvalue; 	

create trigger WMS_DM_OBJECTLIST_trigger
before insert on WMS_DM_OBJECTLIST
for each row
begin
select WMS_DM_OBJECTLIST_seq.nextval into :new.ObjectListId from dual; end;
/ 

create sequence WMS_DM_OBJECT_seq
start with 1
increment by 1
nomaxvalue; 	

create trigger WMS_DM_OBJECT_trigger
before insert on WMS_DM_OBJECT
for each row
begin
select WMS_DM_OBJECT_seq.nextval into :new.ObjectId from dual; end;
/ 

create sequence WMS_VALUE_seq
start with 1
increment by 1
nomaxvalue; 	

create trigger WMS_VALUE_trigger
before insert on WMS_VALUE
for each row
begin
select WMS_VALUE_seq.nextval into :new.ValueId from dual; end;
/ 

create sequence WMS_DATABASE_seq
start with 1
increment by 1
nomaxvalue; 	

create trigger WMS_DATABASE_trigger
before insert on WMS_DATABASE
for each row
begin
select WMS_DATABASE_seq.nextval into :new.DatabaseId from dual; end;
/ 

create sequence WMS_UM_ACCESSOR_seq
start with 1
increment by 1
nomaxvalue; 	

create trigger WMS_UM_ACCESSOR_trigger
before insert on WMS_UM_ACCESSOR
for each row
begin
select WMS_UM_ACCESSOR_seq.nextval into :new.AccessorId from dual; end;
/ 

create sequence WMS_UM_SESSION_seq
start with 1
increment by 1
nomaxvalue; 	

create trigger WMS_UM_SESSION_trigger
before insert on WMS_UM_SESSION
for each row
begin
select WMS_UM_SESSION_seq.nextval into :new.SessionId from dual; end;
/ 

create sequence WMS_LANGUAGE_seq
start with 1
increment by 1
nomaxvalue; 	

create trigger WMS_LANGUAGE_trigger
before insert on WMS_LANGUAGE
for each row
begin
select WMS_LANGUAGE_seq.nextval into :new.LanguageId from dual; end;
/ 

create sequence WMS_CLASS_GROUP_seq
start with 1
increment by 1
nomaxvalue; 	

create trigger WMS_CLASS_GROUP_trigger
before insert on WMS_CLASS_GROUP
for each row
begin
select WMS_CLASS_GROUP_seq.nextval into :new.ID from dual; end;
/ 

create sequence WMS_CLASS_METHOD_RIGHTS_seq
start with 1
increment by 1
nomaxvalue; 	

create trigger WMS_CLASS_METHOD_RIGHTS_trg
before insert on WMS_CLASS_METHOD_RIGHTS
for each row
begin
select WMS_CLASS_METHOD_RIGHTS_seq.nextval into :new.MethodId from dual; end;
/ 

create sequence WMS_CLASS_VALIDATION_seq
start with 1
increment by 1
nomaxvalue; 	

create trigger WMS_CLASS_VALIDATION_trigger
before insert on WMS_CLASS_VALIDATION
for each row
begin
select WMS_CLASS_VALIDATION_seq.nextval into :new.Id from dual; end;
/ 

create sequence WMS_CLASS_METHOD_seq
start with 1
increment by 1
nomaxvalue; 	

create trigger WMS_CLASS_METHOD_trigger
before insert on WMS_CLASS_METHOD
for each row
begin
select WMS_CLASS_METHOD_seq.nextval into :new.Id from dual; end;
/ 

create sequence WMS_JOURNAL_seq
start with 1
increment by 1
nomaxvalue; 	

create trigger WMS_JOURNAL_trigger
before insert on WMS_JOURNAL
for each row
begin
select WMS_JOURNAL_seq.nextval into :new.EntryId from dual; end;
/ 



	
ALTER TABLE WMS_VALUE ADD FOREIGN KEY ( ObjectId ) REFERENCES WMS_DM_OBJECT ( ObjectId ) ON
DELETE CASCADE;
ALTER TABLE WMS_VALUE_BINARYDOCUMENT ADD FOREIGN KEY ( BinaryDocumentId ) REFERENCES WMS_VALUE ( ValueId ) ON
DELETE CASCADE;
ALTER TABLE WMS_VALUE_BOOL ADD FOREIGN KEY ( BoolId ) REFERENCES WMS_VALUE ( ValueId ) ON
DELETE CASCADE;
ALTER TABLE WMS_VALUE_CHARACTERDOCUMENT ADD FOREIGN KEY ( CharacterDocumentId ) REFERENCES WMS_VALUE ( ValueId ) ON
DELETE CASCADE;
ALTER TABLE WMS_VALUE_DATE ADD FOREIGN KEY ( DateId ) REFERENCES WMS_VALUE ( ValueId ) ON
DELETE CASCADE;
ALTER TABLE WMS_VALUE_DATETIME ADD FOREIGN KEY ( DateTimeId ) REFERENCES WMS_VALUE ( ValueId ) ON
DELETE CASCADE;
ALTER TABLE WMS_VALUE_STRING ADD FOREIGN KEY ( StringId ) REFERENCES WMS_VALUE ( ValueId ) ON
DELETE CASCADE;
ALTER TABLE WMS_VALUE_DOUBLE ADD FOREIGN KEY ( DoubleId ) REFERENCES WMS_VALUE ( ValueId ) ON
DELETE CASCADE;
ALTER TABLE WMS_VALUE_FLOAT ADD FOREIGN KEY ( FloatId ) REFERENCES WMS_VALUE ( ValueId ) ON
DELETE CASCADE;
ALTER TABLE WMS_VALUE_INT ADD FOREIGN KEY ( IntId ) REFERENCES WMS_VALUE ( ValueId ) ON
DELETE CASCADE;
ALTER TABLE WMS_VALUE_LONG ADD FOREIGN KEY ( LongId ) REFERENCES WMS_VALUE ( ValueId ) ON
DELETE CASCADE;
ALTER TABLE WMS_VALUE_OBJECTLISTREFERENCE ADD FOREIGN KEY ( ObjectListReferenceId ) REFERENCES WMS_VALUE ( ValueId ) ON
DELETE CASCADE;
ALTER TABLE WMS_VALUE_OBJECTREFERENCE ADD FOREIGN KEY ( ObjectReferenceId ) REFERENCES WMS_VALUE ( ValueId ) ON
DELETE CASCADE;
ALTER TABLE WMS_VALUE_COUNTER ADD FOREIGN KEY ( CounterId ) REFERENCES WMS_VALUE ( ValueId ) ON
DELETE CASCADE;
ALTER TABLE WMS_DM_ACCESSORRIGHT ADD FOREIGN KEY ( ObjectListId ) REFERENCES WMS_DM_OBJECTLIST ( ObjectListId ) ON
DELETE CASCADE;
ALTER TABLE WMS_DM_OBJECTLIST ADD FOREIGN KEY ( ClassId ) REFERENCES WMS_CLASS ( ClassId ) ON
DELETE CASCADE;
ALTER TABLE WMS_DM_OBJECT ADD FOREIGN KEY ( ObjectListId ) REFERENCES WMS_DM_OBJECTLIST ( ObjectListId ) ON
DELETE CASCADE;
ALTER TABLE WMS_DM_LOCKEDOBJECT ADD FOREIGN KEY ( ObjectId ) REFERENCES WMS_DM_OBJECT ( ObjectId ) ON
DELETE CASCADE;
ALTER TABLE WMS_DM_LOCKEDOBJECT ADD FOREIGN KEY ( SessionId ) REFERENCES WMS_UM_SESSION ( SessionId ) ON
DELETE CASCADE;
ALTER TABLE WMS_CLASS_MEMBER ADD FOREIGN KEY ( ClassId ) REFERENCES WMS_CLASS ( ClassId ) ON
DELETE CASCADE;
ALTER TABLE WMS_CLASS_BASECLASS ADD FOREIGN KEY ( ClassId ) REFERENCES WMS_CLASS ( ClassId ) ON
DELETE CASCADE;
ALTER TABLE WMS_CLASS_BASECLASS ADD FOREIGN KEY ( BaseClassId ) REFERENCES WMS_CLASS ( ClassId ) ON
DELETE CASCADE;
ALTER TABLE WMS_UM_GROUPMEMBER ADD FOREIGN KEY ( GroupId ) REFERENCES WMS_UM_GROUP ( GroupId ) ON
DELETE CASCADE;
ALTER TABLE WMS_UM_GROUPMEMBER ADD FOREIGN KEY ( UserId ) REFERENCES WMS_UM_USER ( UserId ) ON
DELETE CASCADE;
ALTER TABLE WMS_UM_GROUP ADD FOREIGN KEY ( GroupId ) REFERENCES WMS_UM_ACCESSOR ( AccessorId ) ON
DELETE CASCADE;
ALTER TABLE WMS_UM_USER ADD FOREIGN KEY ( UserId ) REFERENCES WMS_UM_ACCESSOR ( AccessorId ) ON
DELETE CASCADE;
ALTER TABLE WMS_UM_SESSION ADD FOREIGN KEY ( UserId ) REFERENCES WMS_UM_ACCESSOR ( AccessorId ) ON
DELETE CASCADE;
ALTER TABLE WMS_DM_ACCESSORRIGHT ADD FOREIGN KEY ( AccessorId ) REFERENCES WMS_UM_ACCESSOR ( AccessorId ) ON
DELETE CASCADE;




CREATE INDEX IDX_CLASS_KEYNAME ON WMS_CLASS
    (
        KEYNAME
    ) ;
	
CREATE INDEX IDX_CLASS_DBID ON WMS_CLASS
    (
        DATABASEID
    ) ;
	
CREATE INDEX IDX_BASECLASS_ID ON WMS_CLASS_BASECLASS
    (
        BASECLASSID
    ) ;
	
CREATE INDEX IDX_BASECLASS_CLASSID ON WMS_CLASS_BASECLASS
    (
        CLASSID
    ) ;
	
CREATE INDEX IDX_MEMBER_CLASSID ON WMS_CLASS_MEMBER
    (
        CLASSID
    ) ;
	
	
CREATE INDEX IDX_ACCRIGHT_IDRIGHT ON WMS_DM_ACCESSORRIGHT
    (
        ACCESSORID , ACCESSRIGHT
    ) ;
	
CREATE INDEX IDX_LOCKEDOBJ_OBJID ON WMS_DM_LOCKEDOBJECT
    (
        OBJECTID
    ) ;
	
CREATE INDEX IDX_OBJ_OBJLISTID ON WMS_DM_OBJECT
    (
        OBJECTLISTID
    ) ;
		
CREATE INDEX IDX_OBJLIST_KEYNAME ON WMS_DM_OBJECTLIST
    (
        KEYNAME
    ) ;
	
	
CREATE INDEX IDX_VALUE_OBJID ON WMS_VALUE
    (
        OBJECTID
    ) ;
	
	
	
INSERT
INTO WMS_UM_ACCESSOR
    (
        accessortype , newaccessor
    )
    VALUES
    (
        1 , 0
    ) ;
INSERT
INTO WMS_UM_USER
    (
        userid , firstname , lastname , login , pass , admin , active
    )
    VALUES
    (
        1 , 'admin' , 'admin' , 'admin' , 'admin' , 1 , 1
    ) ;
INSERT
INTO WMS_VERSION
    (
        Current_Version
    )
    VALUES
    (
        4
    ) ;
	
	
ALTER TABLE WMS_CLASS_MEMBER ADD  GroupId  Number NULL;
ALTER TABLE WMS_CLASS ADD  Version         Number NULL;
ALTER TABLE WMS_CLASS_VALIDATION ADD  Name VARCHAR(200) NULL;
ALTER TABLE WMS_CLASS_VALIDATION ADD  Message clob NULL;
ALTER TABLE WMS_CLASS_VALIDATION ADD  ValidationType Number NULL;
ALTER TABLE WMS_CLASS_VALIDATION ADD  Version        Number NULL;
ALTER TABLE WMS_CLASS_MEMBER ADD  Version            Number NULL;
ALTER TABLE WMS_CLASS_MEMBER ADD  Validation clob NULL;
ALTER TABLE WMS_CLASS_MEMBER ADD  Non_Persistent Number NULL;
ALTER TABLE WMS_CLASS_MEMBER ADD  Is_Tree        Number NULL;
ALTER TABLE WMS_JOURNAL ADD  DisplayValue clob NULL;
ALTER TABLE WMS_DM_OBJECTLIST ADD  Version   Number NULL;
ALTER TABLE WMS_CLASS_GROUP ADD  Version     Number NULL;
ALTER TABLE WMS_CLASS_GROUP ADD  Position    Number NULL;
ALTER TABLE WMS_CLASS_GROUP ADD  Parent      Number NULL;
ALTER TABLE WMS_CLASS_METHOD ADD  Version    Number NULL;
ALTER TABLE WMS_CLASS_METHOD ADD  AccessMode Number NULL;
ALTER TABLE WMS_CLASS_METHOD ADD  "PARAMETERS" clob NULL;
ALTER TABLE WMS_CLASS_METHOD ADD  "COMMENT" clob NULL;
ALTER TABLE WMS_CLASS_METHOD ADD  Static              Number NULL;
ALTER TABLE WMS_CLASS_METHOD ADD  "CAPTION"              varchar(200) NULL;
ALTER TABLE WMS_CLASS_METHOD ADD  Icon              CLOB NULL;
ALTER TABLE WMS_UM_USER ADD  Encrypted                Number NULL;
ALTER TABLE WMS_DM_OBJECT ADD  Parent                 Number NULL;
ALTER TABLE WMS_DM_OBJECTLIST ADD  Tree               Number NULL;
ALTER TABLE WMS_CLASS_MEMBER_TRANSLATION ADD  "COMMENT" VARCHAR(4000) NULL;



CREATE VIEW V_VALUE_BINARYDOCUMENT AS
SELECT v.valueid , v.objectid , o.objectlistid , v.memberid , cm.keyname , bd.val , bd.filename , bd.type
FROM WMS_VALUE v
INNER JOIN WMS_VALUE_BINARYDOCUMENT bd ON v.valueId   = bd.binarydocumentId
INNER JOIN WMS_DM_OBJECT  o          ON o.objectid  = v.objectid
INNER JOIN WMS_CLASS_MEMBER  cm      ON cm.memberid = v.memberid;


CREATE VIEW V_VALUE_STRING AS
SELECT v.valueid , v.objectid , o.objectlistid , v.memberid , cm.keyname , str.val
FROM WMS_VALUE v
INNER JOIN WMS_VALUE_STRING str   ON v.valueId   = str.stringId
INNER JOIN WMS_DM_OBJECT  o     ON o.objectid  = v.objectid
INNER JOIN WMS_CLASS_MEMBER  cm ON cm.memberid = v.memberid;

CREATE VIEW V_VALUE_BOOL AS
SELECT v.valueid , v.objectid , o.objectlistid , v.memberid , cm.keyname , b.val
FROM WMS_VALUE v
INNER JOIN WMS_VALUE_BOOL b       ON v.valueId   = b.boolId
INNER JOIN WMS_DM_OBJECT  o     ON o.objectid  = v.objectid
INNER JOIN WMS_CLASS_MEMBER  cm ON cm.memberid = v.memberid;

CREATE VIEW V_VALUE_CHARACTERDOCUMENT AS
SELECT v.valueid , v.objectid , o.objectlistid , v.memberid , cm.keyname , ch.val
FROM WMS_VALUE v
INNER JOIN WMS_VALUE_CHARACTERDOCUMENT ch ON v.valueId   = ch.CharacterDocumentId
INNER JOIN WMS_DM_OBJECT  o             ON o.objectid  = v.objectid
INNER JOIN WMS_CLASS_MEMBER  cm         ON cm.memberid = v.memberid;

CREATE VIEW V_VALUE_COUNTER AS
SELECT v.valueid , v.objectid , o.objectlistid , v.memberid , cm.keyname , c.val
FROM WMS_VALUE v
INNER JOIN WMS_VALUE_COUNTER c    ON v.valueId   = c.CounterId
INNER JOIN WMS_DM_OBJECT  o     ON o.objectid  = v.objectid
INNER JOIN WMS_CLASS_MEMBER  cm ON cm.memberid = v.memberid;

CREATE VIEW V_VALUE_DATE AS
SELECT v.valueid , v.objectid , o.objectlistid , v.memberid , cm.keyname , d.val
FROM WMS_VALUE v
INNER JOIN WMS_VALUE_DATE d       ON v.valueId   = d.DateId
INNER JOIN WMS_DM_OBJECT  o     ON o.objectid  = v.objectid
INNER JOIN WMS_CLASS_MEMBER  cm ON cm.memberid = v.memberid;

CREATE VIEW V_VALUE_DATETIME AS
SELECT v.valueid , v.objectid , o.objectlistid , v.memberid , cm.keyname , dt.val
FROM WMS_VALUE v
INNER JOIN WMS_VALUE_DATETIME dt  ON v.valueId   = dt.DateTimeId
INNER JOIN WMS_DM_OBJECT  o     ON o.objectid  = v.objectid
INNER JOIN WMS_CLASS_MEMBER  cm ON cm.memberid = v.memberid;

CREATE VIEW V_VALUE_FLOAT AS
SELECT v.valueid , v.objectid , o.objectlistid , v.memberid , cm.keyname , f.val
FROM WMS_VALUE v
INNER JOIN WMS_VALUE_FLOAT f      ON v.valueId   = f.FloatId
INNER JOIN WMS_DM_OBJECT  o     ON o.objectid  = v.objectid
INNER JOIN WMS_CLASS_MEMBER  cm ON cm.memberid = v.memberid;

CREATE VIEW V_VALUE_INT AS
SELECT v.valueid , v.objectid , o.objectlistid , v.memberid , cm.keyname , i.val
FROM WMS_VALUE v
INNER JOIN WMS_VALUE_INT i        ON v.valueId   = i.IntId
INNER JOIN WMS_DM_OBJECT  o     ON o.objectid  = v.objectid
INNER JOIN WMS_CLASS_MEMBER  cm ON cm.memberid = v.memberid;

CREATE VIEW V_VALUE_LONG AS
SELECT v.valueid , v.objectid , o.objectlistid , v.memberid , cm.keyname , l.val
FROM WMS_VALUE v
INNER JOIN WMS_VALUE_LONG l       ON v.valueId   = l.LongId
INNER JOIN WMS_DM_OBJECT  o     ON o.objectid  = v.objectid
INNER JOIN WMS_CLASS_MEMBER  cm ON cm.memberid = v.memberid;

CREATE VIEW V_VALUE_OBJECTLISTREFERENCE AS
SELECT v.valueid , v.objectid , o.objectlistid , v.memberid , cm.keyname , ol.ObjectListId AS val , ol.classid , cm.owner
FROM WMS_VALUE v
INNER JOIN WMS_VALUE_OBJECTLISTREFERENCE ol ON v.valueId   = ol.ObjectListReferenceId
INNER JOIN WMS_DM_OBJECT  o               ON o.objectid  = v.objectid
INNER JOIN WMS_CLASS_MEMBER  cm           ON cm.memberid = v.memberid;

CREATE VIEW V_VALUE_OBJECTREFERENCE AS
SELECT v.valueid , v.objectid , o.objectlistid , v.memberid , cm.keyname , oref.ObjectId AS val , oref.classid , oref.objectlistid AS orefobjectlist , cm.owner
FROM WMS_VALUE v
INNER JOIN WMS_VALUE_OBJECTREFERENCE oref ON v.valueId   = oref.ObjectReferenceId
INNER JOIN WMS_DM_OBJECT  o             ON o.objectid  = v.objectid
INNER JOIN WMS_CLASS_MEMBER  cm         ON cm.memberid = v.memberid;

CREATE VIEW V_VALUE_TIME AS
SELECT v.valueid , v.objectid , o.objectlistid , v.memberid , cm.keyname , t.val
FROM WMS_VALUE v
INNER JOIN WMS_VALUE_TIME t       ON v.valueId   = t.TimeId
INNER JOIN WMS_DM_OBJECT  o     ON o.objectid  = v.objectid
INNER JOIN WMS_CLASS_MEMBER  cm ON cm.memberid = v.memberid;
