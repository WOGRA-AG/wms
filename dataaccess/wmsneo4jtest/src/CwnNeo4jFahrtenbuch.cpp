#include "CwnNeo4jFahrtenbuch.h"

#include "CwnCommandCreateUser.h"
#include "CdmSessionManager.h"
#include "CdmScheme.h"

#include "CdmClass.h"
#include "CdmMember.h"
#include "CdmClassGroup.h"
#include "CdmClassManager.h"

#include "CdmValue.h"
#include "CdmValueInt.h"
#include "CdmValueDate.h"
#include "CdmValueUser.h"
#include "CdmValueString.h"
#include "CdmValueLong.h"
#include "CdmValueDouble.h"
#include "CdmValueLong.h"
#include "CdmValueObjectRef.h"

#include "CdmContainerManager.h"
#include "CdmObject.h"
#include "CdmObjectContainer.h"
#include "CdmDataProvider.h"



CwnNeo4jFahrtenBuch::CwnNeo4jFahrtenBuch(QObject *parent) : QObject(parent)
{

}

CdmClass * CwnNeo4jFahrtenBuch::GetClassByName(CdmDataProvider *pCdmManager, QString qstrKeyname)
{
    CdmClass* Fahrtenbuch = pCdmManager->GetClassManager()->FindClassByKeyname(qstrKeyname);

    if (!Fahrtenbuch)
    {
         Fahrtenbuch = pCdmManager->GetClassManager()->CreateClass(qstrKeyname);
    }

    return Fahrtenbuch;
}

void CwnNeo4jFahrtenBuch::initTestCase()
{

    CwnCommandCreateUser create(NULL,"");
    create.setActive(true);
    create.setAdmin(true);
    create.setEmail("admin9@wogra.com");
    create.setFirstname("admin");
    create.setLastname("admin");
    create.setLogin("admin");
    create.setPass("admin");
    create.Run();


    CdmSessionManager* pFactory = CdmSessionManager::CreateSessionManager(eDmSettingsModeClient);

    if (SUCCESSFULL(pFactory->Login("admin","admin")))
    {
         m_pCdmManager = CdmSessionManager::GetDataProvider();
         m_pCumManager = m_pCdmManager->GetUserManager();
    }

//    m_pCdmManager->CreateScheme("SchemaNeo4jFahrtenBuch");
//    m_pCdmManager->LoadScheme("SchemaNeo4jFahrtenBuch");

//    //WATCH OUT NULL POINTER TODO
//    CdmClass* Fahrtenbuch = GetClassByName(m_pCdmManager, "Fahrtenbuch");
//    //WATCH OUT NULL POINTER TODO
//    CdmClass* Fahrzeug = GetClassByName(m_pCdmManager, "Fahrzeug");
//    Fahrzeug->Commit();

//    CdmMember* pMember1 = Fahrtenbuch->CreateMember("Fahrttyp",eDmValueEnum,false,15);
//    if(pMember1==0)
//        pMember1=const_cast<CdmMember*>(Fahrtenbuch->FindMember("Fahrttyp"));

//    pMember1->SetCreatorId(CdmSessionManager::GetManager()->GetUserId());
//    pMember1->SetModifierId(CdmSessionManager::GetManager()->GetUserId());

//    pMember1->SetValidationCode("Art1,Art2,Art3");

//    CdmMember* pMember2 = Fahrtenbuch->CreateMember("Fahrzeug",eDmValueObjectRef,false,15);
//    if(pMember2==0)
//        pMember2=const_cast<CdmMember*>(Fahrtenbuch->FindMember("Fahrzeug"));

//    pMember2->SetClassReference("Fahrzeug");
//    pMember2->SetCreatorId(CdmSessionManager::GetManager()->GetUserId());
//    pMember2->SetModifierId(CdmSessionManager::GetManager()->GetUserId());

//    CdmMember* pMember3 = Fahrtenbuch->CreateMember("Kilometer",eDmValueInt,false,15);
//    if(pMember3==0)
//        pMember3=const_cast<CdmMember*>(Fahrtenbuch->FindMember("Kilometer"));

//    pMember3->SetCreatorId(CdmSessionManager::GetManager()->GetUserId());
//    pMember3->SetModifierId(CdmSessionManager::GetManager()->GetUserId());

//    CdmMember* pMember4 = Fahrtenbuch->CreateMember("Kilometerstand_Abfahrt",eDmValueInt,false,15);
//    if(pMember4==0)
//        pMember4=const_cast<CdmMember*>(Fahrtenbuch->FindMember("Kilometerstand_Abfahrt"));

//    pMember4->SetCreatorId(CdmSessionManager::GetManager()->GetUserId());
//    pMember4->SetModifierId(CdmSessionManager::GetManager()->GetUserId());

//    CdmMember* pMember5 = Fahrtenbuch->CreateMember("Kilometerstand_Ankunft",eDmValueInt,false,15);
//    if(pMember5==0)
//        pMember5=const_cast<CdmMember*>(Fahrtenbuch->FindMember("Kilometerstand_Ankunft"));

//    pMember5->SetCreatorId(CdmSessionManager::GetManager()->GetUserId());
//    pMember5->SetModifierId(CdmSessionManager::GetManager()->GetUserId());

//    CdmMember* pMember6 = Fahrtenbuch->CreateMember("Zielort",eDmValueString,false,15);
//    if(pMember6==0)
//        pMember6=const_cast<CdmMember*>(Fahrtenbuch->FindMember("Zielort"));

//    pMember6->SetCreatorId(CdmSessionManager::GetManager()->GetUserId());
//    pMember6->SetModifierId(CdmSessionManager::GetManager()->GetUserId());

//    Fahrtenbuch->Commit();



//    CdmClassGroup* g=Fahrzeug->FindGroupByName("Fahrzeuginfo");
//    if(g==NULL)
//    {
//        Fahrzeug->CreateGroup("Fahrzeuginfo",1,1,NULL);
//        g = Fahrzeug->FindGroupByName("Fahrzeuginfo");
//    }

//    CdmMember* pMember7 = Fahrzeug->CreateMember("Anschaffungsart",eDmValueEnum,false,15);
//    if(pMember7==0)
//        pMember7=const_cast<CdmMember*>(Fahrzeug->FindMember("Anschaffungsart"));

//    pMember7->SetCreatorId(CdmSessionManager::GetManager()->GetUserId());
//    pMember7->SetModifierId(CdmSessionManager::GetManager()->GetUserId());

//    pMember7->SetValidationCode("Gekauft,Geleast,Gestohlen");

//    CdmMember* pMember8 = Fahrzeug->CreateMember("Anschaffungsdatum",eDmValueDate,false,15);
//    if(pMember8==0)
//        pMember8=const_cast<CdmMember*>(Fahrzeug->FindMember("Anschaffungsdatum"));

//    pMember8->SetCreatorId(CdmSessionManager::GetManager()->GetUserId());
//    pMember8->SetModifierId(CdmSessionManager::GetManager()->GetUserId());

//    CdmMember* pMember9 = Fahrzeug->CreateMember("Fabrikat",eDmValueString,false,15);
//    if(pMember9==0)
//        pMember9=const_cast<CdmMember*>(Fahrzeug->FindMember("Fabrikat"));

//    pMember9->SetCreatorId(CdmSessionManager::GetManager()->GetUserId());
//    pMember9->SetModifierId(CdmSessionManager::GetManager()->GetUserId());

//    CdmMember* pMember10 = Fahrzeug->CreateMember("Halter",eDmValueUser,false,15);
//    if(pMember10==0)
//        pMember10=const_cast<CdmMember*>(Fahrzeug->FindMember("Halter"));

//    pMember10->SetCreatorId(CdmSessionManager::GetManager()->GetUserId());
//    pMember10->SetModifierId(CdmSessionManager::GetManager()->GetUserId());

//    CdmMember* pMember11 = Fahrzeug->CreateMember("Hersteller",eDmValueString,false,15);
//    if(pMember11==0)
//        pMember11=const_cast<CdmMember*>(Fahrzeug->FindMember("Hersteller"));

//    pMember11->SetCreatorId(CdmSessionManager::GetManager()->GetUserId());
//    pMember11->SetModifierId(CdmSessionManager::GetManager()->GetUserId());

//    CdmMember* pMember12 = Fahrzeug->CreateMember("Kennzeichen",eDmValueString,false,15);
//    if(pMember12==0)
//        pMember12=const_cast<CdmMember*>(Fahrzeug->FindMember("Kennzeichen"));

//    pMember12->SetCreatorId(CdmSessionManager::GetManager()->GetUserId());
//    pMember12->SetModifierId(CdmSessionManager::GetManager()->GetUserId());

//    pMember7->SetGroup(g);
//    pMember8->SetGroup(g);
//    pMember9->SetGroup(g);
//    pMember10->SetGroup(g);
//    pMember11->SetGroup(g);
//    pMember12->SetGroup(g);

//    CdmClassGroup* g2=Fahrzeug->FindGroupByName("Kosten");
//    if(g2==NULL){
//       Fahrzeug->CreateGroup("Kosten",1,2,NULL);
//       g2=Fahrzeug->FindGroupByName("Kosten");
//    }

//    CdmMember* pMember13 = Fahrzeug->CreateMember("Anschaffungskosten",eDmValueInt,false,15);
//    if(pMember13==0)
//        pMember13=const_cast<CdmMember*>(Fahrzeug->FindMember("Anschaffungskosten"));

//    pMember13->SetCreatorId(CdmSessionManager::GetManager()->GetUserId());
//    pMember13->SetModifierId(CdmSessionManager::GetManager()->GetUserId());

//    CdmMember* pMember14 = Fahrzeug->CreateMember("BruttoAnschaffungspreis",eDmValueDouble,false,15);
//    if(pMember14==0)
//        pMember14=const_cast<CdmMember*>(Fahrzeug->FindMember("BruttoAnschaffungspreis"));

//    pMember14->SetCreatorId(CdmSessionManager::GetManager()->GetUserId());
//    pMember14->SetModifierId(CdmSessionManager::GetManager()->GetUserId());

//    CdmMember* pMember15 = Fahrzeug->CreateMember("Versicherungskosten_Jahr",eDmValueInt,false,15);
//    if(pMember15==0)
//        pMember15=const_cast<CdmMember*>(Fahrzeug->FindMember("Versicherungskosten_Jahr"));

//    pMember15->SetCreatorId(CdmSessionManager::GetManager()->GetUserId());
//    pMember15->SetModifierId(CdmSessionManager::GetManager()->GetUserId());

//    CdmMember* pMember16 = Fahrzeug->CreateMember("Laufende_Fix_Kosten_Monat",eDmValueInt,false,15);
//    if(pMember16==0)
//        pMember16=const_cast<CdmMember*>(Fahrzeug->FindMember("Laufende_Fix_Kosten_Monat"));

//    pMember16->SetCreatorId(CdmSessionManager::GetManager()->GetUserId());
//    pMember16->SetModifierId(CdmSessionManager::GetManager()->GetUserId());

//    pMember13->SetGroup(g2);
//    pMember14->SetGroup(g2);
//    pMember15->SetGroup(g2);
//    pMember16->SetGroup(g2);

//    Fahrzeug->Commit();

//    //WATCH OUT NULL POINTER TODO
//    CdmClass* Fahrzeugkosten = GetClassByName(m_pCdmManager, "Fahrzeugkosten");

//    CdmMember* pMember17 = Fahrzeugkosten->CreateMember("Art",eDmValueEnum,false,15);
//    if(pMember17==0)
//        pMember17=const_cast<CdmMember*>(Fahrzeugkosten->FindMember("Art"));

//    pMember17->SetCreatorId(CdmSessionManager::GetManager()->GetUserId());
//    pMember17->SetModifierId(CdmSessionManager::GetManager()->GetUserId());

//    pMember17->SetValidationCode("Beschaffungskosten,Benzin,Reperatur");

//    CdmMember* pMember18 = Fahrzeugkosten->CreateMember("Betrag",eDmValueDouble,false,15);
//    if(pMember18==0)
//        pMember18=const_cast<CdmMember*>(Fahrzeugkosten->FindMember("Betrag"));

//    pMember18->SetCreatorId(CdmSessionManager::GetManager()->GetUserId());
//    pMember18->SetModifierId(CdmSessionManager::GetManager()->GetUserId());

//    CdmMember* pMember19 = Fahrzeugkosten->CreateMember("Datum",eDmValueDate,false,15);
//    if(pMember19==0)
//        pMember19=const_cast<CdmMember*>(Fahrzeugkosten->FindMember("Datum"));

//    pMember19->SetCreatorId(CdmSessionManager::GetManager()->GetUserId());
//    pMember19->SetModifierId(CdmSessionManager::GetManager()->GetUserId());

//    CdmMember* pMember20 = Fahrzeugkosten->CreateMember("Fahrzeug",eDmValueObjectRef,false,15);
//    if(pMember20==0)
//    pMember20=const_cast<CdmMember*>(Fahrzeugkosten->FindMember("Fahrzeug"));

//    pMember20->SetCreatorId(CdmSessionManager::GetManager()->GetUserId());
//    pMember20->SetClassReference("Fahrzeug");
//    pMember20->SetModifierId(CdmSessionManager::GetManager()->GetUserId());


//    CdmMember* pMember21 = Fahrzeugkosten->CreateMember("Kommentar",eDmValueString,false,1000);
//    if(pMember21==0)
//        pMember21=const_cast<CdmMember*>(Fahrzeugkosten->FindMember("Kommentar"));

//    pMember21->SetCreatorId(CdmSessionManager::GetManager()->GetUserId());
//    pMember21->SetModifierId(CdmSessionManager::GetManager()->GetUserId());

//    Fahrzeugkosten->Commit();


//    QString qstrContainerKeyname = "Buchungen";
//    CdmObjectContainer* pContainer = m_pCdmManager->GetContainerManager()->FindContainerByKeyname(qstrContainerKeyname);

//    if(pContainer==NULL && Fahrtenbuch!=NULL)
//    {
//        m_pCdmManager->GetContainerManager()->CreateContainer(Fahrtenbuch->GetId(),qstrContainerKeyname);
//    }

//    qstrContainerKeyname = "Fahrzeuge";
//    pContainer = m_pCdmManager->GetContainerManager()->FindContainerByKeyname(qstrContainerKeyname);

//    if(pContainer==NULL && Fahrzeug!=NULL)
//    {
//        m_pCdmManager->GetContainerManager()->CreateContainer(Fahrzeug->GetId(),qstrContainerKeyname);
//    }

//    qstrContainerKeyname = "kosten";
//    pContainer = m_pCdmManager->GetContainerManager()->FindContainerByKeyname(qstrContainerKeyname);

//    if(pContainer==NULL && Fahrzeugkosten!=NULL)
//    {
//        m_pCdmManager->GetContainerManager()->CreateContainer(Fahrzeugkosten->GetId(),qstrContainerKeyname);
//    }

//    pContainer = m_pCdmManager->GetContainerManager()->FindContainerByKeyname("Fahrzeuge");

//    CdmObject* maluszek=pContainer->FindObjectByKeynameLocal("Maluszek");
//    CdmObject* ferrari=pContainer->FindObjectByKeynameLocal("Ferrari");

//    if(!maluszek)
//    {
//        maluszek = pContainer->CreateNewObject("Maluszek");
//    }

//    if(!ferrari)
//    {
//        ferrari = pContainer->CreateNewObject("Ferrari");
//    }

//    CdmValue* anschaffungsart_m = maluszek->GetValue("Anschaffungsart");

//    if (anschaffungsart_m && anschaffungsart_m->GetValueType() == eDmValueEnum)
//    {
//        ((CdmValueInt*)anschaffungsart_m)->SetValue(1);
//    }

//    CdmValue* anschaffungsdatum_m = maluszek->GetValue("Anschaffungsdatum");

//    if (anschaffungsdatum_m && anschaffungsdatum_m->GetValueType() == eDmValueDate)
//    {
//        ((CdmValueDate*)anschaffungsdatum_m)->SetValue(QDate::currentDate());
//    }

//    CdmValue* fabrikat_m = maluszek->GetValue("Fabrikat");

//    if (fabrikat_m && fabrikat_m->GetValueType() == eDmValueString)
//    {
//        ((CdmValueString*)fabrikat_m)->SetValue("Klasse 1");
//    }

//    CdmValue* halter_m = maluszek->GetValue("Halter");

//    if (halter_m && halter_m->GetValueType() == eDmValueUser)
//    {
//        ((CdmValueUser*)halter_m)->SetValue(CdmSessionManager::GetManager()->GetUserId());
//    }

//    CdmValue* hersteller_m = maluszek->GetValue("Hersteller");

//    if (hersteller_m && hersteller_m->GetValueType() == eDmValueString)
//    {
//        ((CdmValueString*)hersteller_m)->SetValue("Fiat");
//    }

//    CdmValue* kennzeichen_m = maluszek->GetValue("Kennzeichen");

//    if (kennzeichen_m && kennzeichen_m->GetValueType() == eDmValueString)
//    {
//        ((CdmValueString*)kennzeichen_m)->SetValue("A-MK 1234");
//    }

//    CdmValue* anschaffungskosten_m = maluszek->GetValue("Anschaffungskosten");

//    if (anschaffungskosten_m && anschaffungskosten_m->GetValueType() == eDmValueInt)
//    {
//        ((CdmValueInt*) anschaffungskosten_m)->SetValue(2000);
//    }

//    CdmValue* bruttoanschaffungspreis_m = maluszek->GetValue("BruttoAnschaffungspreis");

//    if (bruttoanschaffungspreis_m && bruttoanschaffungspreis_m->GetValueType() == eDmValueDouble)
//    {
//        ((CdmValueDouble*) bruttoanschaffungspreis_m)->SetValue(400050.50);
//    }

//    CdmValue* versicherungskosten_jahr_m = maluszek->GetValue("Versicherungskosten_Jahr");

//    if (versicherungskosten_jahr_m && versicherungskosten_jahr_m->GetValueType() == eDmValueInt)
//    {
//        ((CdmValueInt*) versicherungskosten_jahr_m)->SetValue(500);
//    }

//    CdmValue* laufende_fix_kosten_monat_m = maluszek->GetValue("Laufende_Fix_Kosten_Monat");

//    if (laufende_fix_kosten_monat_m && laufende_fix_kosten_monat_m->GetValueType() == eDmValueInt)
//    {
//        ((CdmValueInt*) laufende_fix_kosten_monat_m)->SetValue(100);
//    }


//    CdmValue* anschaffungsart_f = ferrari->GetValue("Anschaffungsart");

//    if (anschaffungsart_f && anschaffungsart_f->GetValueType() == eDmValueEnum)
//    {
//        ((CdmValueInt*)anschaffungsart_f)->SetValue(2);
//    }

//    CdmValue* anschaffungsdatum_f = ferrari->GetValue("Anschaffungsdatum");

//    if (anschaffungsdatum_f && anschaffungsdatum_f->GetValueType() == eDmValueDate)
//    {
//        ((CdmValueDate*)anschaffungsdatum_f)->SetValue(QDate::currentDate());
//    }

//    CdmValue* fabrikat_f = ferrari->GetValue("Fabrikat");

//    if (fabrikat_f && fabrikat_f->GetValueType() == eDmValueString)
//    {
//        ((CdmValueString*)fabrikat_f)->SetValue("Diablo");
//    }

//    CdmValue* halter_f = ferrari->GetValue("Halter");

//    if (halter_f && halter_f->GetValueType() == eDmValueUser)
//    {
//        ((CdmValueUser*)halter_f)->SetValue(CdmSessionManager::GetManager()->GetUserId());
//    }

//    CdmValue* hersteller_f = ferrari->GetValue("Hersteller");

//    if (hersteller_f && hersteller_f->GetValueType() == eDmValueString)
//    {
//        ((CdmValueString*)hersteller_f)->SetValue("Ferrari");
//    }

//    CdmValue* kennzeichen_f = ferrari->GetValue("Kennzeichen");

//    if (kennzeichen_f && kennzeichen_f->GetValueType() == eDmValueString)
//    {
//        ((CdmValueString*)kennzeichen_f)->SetValue("A-$$ 1337");
//    }

//    CdmValue* anschaffungskosten_f = ferrari->GetValue("Anschaffungskosten");

//    if (anschaffungskosten_f && anschaffungskosten_f->GetValueType() == eDmValueInt)
//    {
//        ((CdmValueInt*) anschaffungskosten_f)->SetValue(200000);
//    }

//    CdmValue* bruttoanschaffungspreis_f = ferrari->GetValue("BruttoAnschaffungspreis");

//    if (bruttoanschaffungspreis_f && bruttoanschaffungspreis_f->GetValueType() == eDmValueDouble)
//    {
//        ((CdmValueDouble*) bruttoanschaffungspreis_f)->SetValue(300000.89);
//    }

//    CdmValue* versicherungskosten_jahr_f = ferrari->GetValue("Versicherungskosten_Jahr");

//    if (versicherungskosten_jahr_f && versicherungskosten_jahr_f->GetValueType() == eDmValueInt)
//    {
//        ((CdmValueInt*) versicherungskosten_jahr_f)->SetValue(3000);
//    }

//    CdmValue* laufende_fix_kosten_monat_f = ferrari->GetValue("Laufende_Fix_Kosten_Monat");

//    if (laufende_fix_kosten_monat_f && laufende_fix_kosten_monat_f->GetValueType() == eDmValueInt)
//    {
//        ((CdmValueInt*) laufende_fix_kosten_monat_f)->SetValue(1500);
//    }

//    pContainer->Commit();

//    pContainer = m_pCdmManager->GetContainerManager()->FindContainerByKeyname("Buchungen");

//    CdmObject* augsburgmuenchen=pContainer->FindObjectByKeynameLocal("AugsburgMuenchen");
//    CdmObject* muenchenaugsburg=pContainer->FindObjectByKeynameLocal("MuenchenAugsburg");

//    if(!augsburgmuenchen)
//    {
//        augsburgmuenchen = pContainer->CreateNewObject("AugsburgMuenchen");
//    }

//    if(!muenchenaugsburg)
//    {
//        muenchenaugsburg = pContainer->CreateNewObject("MuenchenAugsburg");
//    }

//    CdmValue* fahrttyp_am = augsburgmuenchen->GetValue("Fahrttyp");

//    if (fahrttyp_am && fahrttyp_am->GetValueType() == eDmValueEnum)
//    {
//        ((CdmValueInt*)fahrttyp_am)->SetValue(1);
//    }

//    CdmValue* fahrzeug_am = augsburgmuenchen->GetValue("Fahrzeug");

//    if (fahrzeug_am && fahrzeug_am->GetValueType() == eDmValueObjectRef)
//    {
//        ((CdmValueObjectRef*)fahrzeug_am)->SetValue(maluszek);
//    }

//    CdmValue* kilometer_am = augsburgmuenchen->GetValue("Kilometer");

//    if (kilometer_am && kilometer_am->GetValueType() == eDmValueInt)
//    {
//        ((CdmValueInt*)kilometer_am)->SetValue(60);
//    }

//    CdmValue* kilometerab_am = augsburgmuenchen->GetValue("Kilometerstand_Abfahrt");

//    if (kilometerab_am && kilometerab_am->GetValueType() == eDmValueInt)
//    {
//        ((CdmValueInt*)kilometerab_am)->SetValue(300000);
//    }

//    CdmValue* kilometeran_am = augsburgmuenchen->GetValue("Kilometerstand_Ankunft");

//    if (kilometeran_am && kilometeran_am->GetValueType() == eDmValueInt)
//    {
//        ((CdmValueInt*)kilometeran_am)->SetValue(300060);
//    }

//    CdmValue* zielort_am = augsburgmuenchen->GetValue("Zielort");

//    if (zielort_am && zielort_am->GetValueType() == eDmValueString)
//    {
//        ((CdmValueString*)zielort_am)->SetValue("München");
//    }

//    CdmValue* fahrttyp_ma = muenchenaugsburg->GetValue("Fahrttyp");

//    if (fahrttyp_ma && fahrttyp_ma->GetValueType() == eDmValueEnum)
//    {
//        ((CdmValueInt*)fahrttyp_ma)->SetValue(1);
//    }

//    CdmValue* fahrzeug_ma = muenchenaugsburg->GetValue("Fahrzeug");

//    if (fahrzeug_ma && fahrzeug_ma->GetValueType() == eDmValueObjectRef)
//    {
//        ((CdmValueObjectRef*)fahrzeug_ma)->SetValue(ferrari);
//    }

//    CdmValue* kilometer_ma = muenchenaugsburg->GetValue("Kilometer");

//    if (kilometer_ma && kilometer_ma->GetValueType() == eDmValueInt)
//    {
//        ((CdmValueInt*)kilometer_ma)->SetValue(60);
//    }

//    CdmValue* kilometerab_ma = muenchenaugsburg->GetValue("Kilometerstand_Abfahrt");

//    if (kilometerab_ma && kilometerab_ma->GetValueType() == eDmValueInt)
//    {
//        ((CdmValueInt*)kilometerab_ma)->SetValue(300060);
//    }

//    CdmValue* kilometeran_ma = muenchenaugsburg->GetValue("Kilometerstand_Ankunft");

//    if (kilometeran_ma && kilometeran_ma->GetValueType() == eDmValueInt)
//    {
//        ((CdmValueInt*)kilometeran_ma)->SetValue(300120);
//    }

//    CdmValue* zielort_ma = muenchenaugsburg->GetValue("Zielort");

//    if (zielort_ma && zielort_ma->GetValueType() == eDmValueString)
//    {
//        ((CdmValueString*)zielort_ma)->SetValue("Augsburg");
//    }

//    pContainer->Commit();

//    pContainer = m_pCdmManager->GetContainerManager()->FindContainerByKeyname("kosten");

//    CdmObject* maluszekkosten=pContainer->FindObjectByKeynameLocal("Maluszek_kosten");
//    CdmObject* ferrarikosten=pContainer->FindObjectByKeynameLocal("Ferrari_kosten");

//    if(!maluszekkosten)
//    {
//        maluszekkosten = pContainer->CreateNewObject("Maluszek_kosten");
//    }

//    if(!ferrarikosten)
//    {
//        ferrarikosten = pContainer->CreateNewObject("Ferrari_kosten");
//    }

//    CdmValue* art_km = maluszekkosten->GetValue("Art");

//    if (art_km && art_km->GetValueType() == eDmValueEnum)
//    {
//        ((CdmValueInt*)art_km)->SetValue(0);
//    }

//    CdmValue* fahrzeug_km = maluszekkosten->GetValue("Fahrzeug");

//    if (fahrzeug_km && fahrzeug_km->GetValueType() == eDmValueObjectRef)
//    {
//        ((CdmValueObjectRef*)fahrzeug_km)->SetValue(maluszek);
//    }

//    CdmValue* datum_km = maluszekkosten->GetValue("Datum");

//    if (datum_km && datum_km->GetValueType() == eDmValueDate)
//    {
//        ((CdmValueDate*)datum_km)->SetValue(QDate::currentDate());
//    }

//    CdmValue* betrag_km = maluszekkosten->GetValue("Betrag");

//    if (betrag_km && betrag_km->GetValueType() == eDmValueDouble)
//    {
//        ((CdmValueDouble*) betrag_km)->SetValue(2000.89);
//    }

//    CdmValue* kommentar_km = maluszekkosten->GetValue("Kommentar");

//    if (kommentar_km && kommentar_km->GetValueType() == eDmValueString)
//    {
//        ((CdmValueString*)kommentar_km)->SetValue("Polnische Ingenieurskunst trifft deutsche Autobahn.");
//    }

//    CdmValue* art_kf = ferrarikosten->GetValue("Art");

//    if (art_kf && art_kf->GetValueType() == eDmValueEnum)
//    {
//        ((CdmValueInt*)art_kf)->SetValue(0);
//    }

//    CdmValue* fahrzeug_kf = ferrarikosten->GetValue("Fahrzeug");

//    if (fahrzeug_kf && fahrzeug_kf->GetValueType() == eDmValueObjectRef)
//    {
//        ((CdmValueObjectRef*)fahrzeug_kf)->SetValue(ferrari);
//    }

//    CdmValue* datum_kf = ferrarikosten->GetValue("Datum");

//    if (datum_kf && datum_kf->GetValueType() == eDmValueDate)
//    {
//        ((CdmValueDate*)datum_kf)->SetValue(QDate::currentDate());
//    }

//    CdmValue* betrag_kf = ferrarikosten->GetValue("Betrag");

//    if (betrag_kf && betrag_kf->GetValueType() == eDmValueDouble)
//    {
//        ((CdmValueDouble*) betrag_kf)->SetValue(300000.90);
//    }

//    CdmValue* kommentar_kf = ferrarikosten->GetValue("Kommentar");

//    if (kommentar_kf && kommentar_kf->GetValueType() == eDmValueString)
//    {
//        ((CdmValueString*)kommentar_kf)->SetValue("Der Ferrari Das Auto für Jedermann.");
//    }

//    pContainer->Commit();

}

void CwnNeo4jFahrtenBuch::cleanupTestCase()
{
    CdmDataProvider* pCdmManager = CdmSessionManager::GetDataProvider();
    if (CHKPTR(pCdmManager))
    {
        CdmSessionManager::Logout();
    }
}
