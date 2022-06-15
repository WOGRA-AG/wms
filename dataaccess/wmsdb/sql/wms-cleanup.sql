delete from WMS_DM_OBJECT where objectid in (select str.objectid from (select s.objectid from WMS_DM_OBJECT s left join WMS_DM_OBJECTLIST v on v.ObjectListId = s.objectlistid where v.ObjectListId is null) str);
delete from WMS_VALUE where valueid in (select t.valueid from (select valueid from WMS_VALUE v left join WMS_DM_OBJECT o on o.ObjectId = v.ObjectId where o.ObjectId is null) t);
delete from WMS_VALUE_STRING where stringid in (select str.stringid from (select s.StringId from WMS_VALUE_STRING s left join WMS_VALUE v on v.ValueId = s.StringId where v.valueid is null) str);
delete from WMS_VALUE_DOUBLE where doubleid in (select str.doubleid from (select s.doubleId from WMS_VALUE_DOUBLE s left join WMS_VALUE v on v.ValueId = s.DoubleId where v.valueid is null) str);
delete from WMS_VALUE_INT where intid in (select str.intid from (select s.intId from WMS_VALUE_INT s left join WMS_VALUE v on v.ValueId = s.intId where v.valueid is null) str);
delete from WMS_VALUE_LONG where longid in (select str.longid from (select s.longId from WMS_VALUE_LONG s left join WMS_VALUE v on v.ValueId = s.longId where v.valueid is null) str);
delete from WMS_VALUE_FLOAT where floatid in (select str.floatid from (select s.floatId from WMS_VALUE_FLOAT s left join WMS_VALUE v on v.ValueId = s.floatId where v.valueid is null) str);
delete from WMS_VALUE_COUNTER where counterid in (select str.counterid from (select s.counterId from WMS_VALUE_COUNTER s left join WMS_VALUE v on v.ValueId = s.counterId where v.valueid is null) str);
delete from WMS_VALUE_DATE where dateid in (select str.dateid from (select s.dateId from WMS_VALUE_DATE s left join WMS_VALUE v on v.ValueId = s.dateId where v.valueid is null) str);
delete from WMS_VALUE_TIME where timeid in (select str.timeid from (select s.timeId from WMS_VALUE_TIME s left join WMS_VALUE v on v.ValueId = s.timeId where v.valueid is null) str);
delete from WMS_VALUE_DATETIME where datetimeid in (select str.datetimeid from (select s.datetimeId from WMS_VALUE_DATETIME s left join WMS_VALUE v on v.ValueId = s.datetimeId where v.valueid is null) str);
delete from WMS_VALUE_BOOL where boolid in (select str.boolid from (select s.boolId from WMS_VALUE_BOOL s left join WMS_VALUE v on v.ValueId = s.boolId where v.valueid is null) str);
delete from WMS_VALUE_BINARYDOCUMENT where binarydocumentid in (select str.binarydocumentid from (select s.binarydocumentid from WMS_VALUE_BINARYDOCUMENT s left join WMS_VALUE v on v.ValueId = s.binarydocumentid where v.valueid is null) str);
delete from WMS_VALUE_CHARACTERDOCUMENT where characterdocumentid in (select str.characterdocumentid from (select s.characterdocumentid from WMS_VALUE_CHARACTERDOCUMENT s left join WMS_VALUE v on v.ValueId = s.characterdocumentid where v.valueid is null) str);
delete from WMS_VALUE_OBJECTREFERENCE where objectreferenceid in (select str.objectreferenceid from (select s.objectreferenceid from WMS_VALUE_OBJECTREFERENCE s left join WMS_VALUE v on v.ValueId = s.objectreferenceid where v.valueid is null) str);
delete from WMS_VALUE_OBJECTLISTREFERENCE where objectlistreferenceid in (select str.objectlistreferenceid from (select s.objectlistreferenceid from WMS_VALUE_OBJECTLISTREFERENCE s left join WMS_VALUE v on v.ValueId = s.objectlistreferenceid where v.valueid is null) str);