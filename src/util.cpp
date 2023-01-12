#include "util.hpp"
#include "il2cpp-api.h"
#include "PlayerWork.hpp"
#include "Dpr/Battle/Logic/BTL_POKEPARAM.hpp"
#include "Dpr/Battle/Logic/Common.hpp"
#include "Dpr/Battle/Logic/DamageCause.hpp"
#include "Dpr/Battle/Logic/EventFactor.hpp"
#include "Dpr/Battle/Logic/RankEffectCause.hpp"
#include "Dpr/Battle/Logic/SickCause.hpp"
#include "Pml/WazaData/WazaSick.hpp"

using namespace Dpr::Battle::Logic;
using namespace Pml::WazaData;

void system_load_typeinfo(void * typeInfo)
{
  _system_load_typeinfo(typeInfo);
}

void * system_array_new(void * typeInfo, uint32_t len)
{
  void * array = _system_array_new(typeInfo, len);
  _system_array_init(array);
  return array;
}


MethodInfo * copyMethodInfo(MethodInfo * src, Il2CppMethodPointer methodPointer)
{
  auto * dst = (MethodInfo *) malloc(sizeof(MethodInfo));
  memcpy(dst, src, sizeof(MethodInfo));

  if (methodPointer != nullptr)
  {
    dst->methodPointer = methodPointer;
  }

  return dst;
}


uint32_t GetBadgeCount()
{
  bool bVar1 = PlayerWork::GetSytemFlag(0x81, (MethodInfo *)nullptr);
  bool bVar2 = PlayerWork::GetSytemFlag(0x7c, (MethodInfo *)nullptr);
  bool bVar3 = PlayerWork::GetSytemFlag(0x7d, (MethodInfo *)nullptr);
  bool bVar4 = PlayerWork::GetSytemFlag(0x80, (MethodInfo *)nullptr);
  bool bVar5 = PlayerWork::GetSytemFlag(0x7f, (MethodInfo *)nullptr);
  bool bVar6 = PlayerWork::GetSytemFlag(0x7e, (MethodInfo *)nullptr);
  bool bVar7 = PlayerWork::GetSytemFlag(0x83, (MethodInfo *)nullptr);
  bool bVar8 = PlayerWork::GetSytemFlag(0x82, (MethodInfo *)nullptr);
  return (bVar2 & 1) + (bVar1 & 1) + (bVar3 & 1) + (bVar4 & 1) + (bVar5 & 1) + (bVar6 & 1) +
         (bVar7 & 1) + (bVar8 & 1);
}

Dpr::Battle::Logic::EventFactor_EventHandlerTable_o * CreateEventHandler(uint16_t eventID, MethodInfo * src, Il2CppMethodPointer methodPointer)
{
    MethodInfo * method = copyMethodInfo(src, methodPointer);
    auto * evtHandlerTable = (Dpr::Battle::Logic::EventFactor_EventHandlerTable_o *) il2cpp_object_new(Dpr::Battle::Logic::EventFactor_EventHandlerTable_TypeInfo);
    auto * evtHandler = (Dpr::Battle::Logic::EventFactor_EventHandler_o *) il2cpp_object_new(Dpr::Battle::Logic::EventFactor_EventHandler_TypeInfo);
    evtHandler->ctor((intptr_t) methodPointer, method);
    evtHandlerTable->fields.eventID = eventID;
    evtHandlerTable->fields.eventHandler = evtHandler;

    return evtHandlerTable;
}
uint8_t HighestMultiple(uint8_t max, uint8_t factor) {
    uint8_t factor2 = max / factor;
    return factor * factor2;
}
void HandlerAddPosEffect(EventFactor_EventHandlerArgs_o **args, uint8_t pokeID) {
    system_load_typeinfo((void *)0xa909);
    auto *desc = (Section_FromEvent_PosEffect_Add_Description_o *)
            il2cpp_object_new(Section_FromEvent_PosEffect_Add_Description_TypeInfo);
    desc->ctor(nullptr);
    desc->fields.userPokeID = pokeID;
    desc->fields.pos = Common::PokeIDtoPokePos(args, &pokeID, nullptr);
    desc->fields.effect = 5;
    Common::AddPosEffect(args, &desc, nullptr);
}
void HandlerAddSick(EventFactor_EventHandlerArgs_o **args, uint8_t pokeID, uint8_t targetPokeID, int32_t sickID,
                    int64_t sickCont) {
    system_load_typeinfo((void *)0xa9aa);
    auto *addSickDesc = (Section_AddSick_Description_o *)
            il2cpp_object_new(Section_AddSick_Description_TypeInfo);
    addSickDesc->ctor(nullptr);
    addSickDesc->fields.pokeID = pokeID;
    addSickDesc->fields.targetPokeID = targetPokeID;
    addSickDesc->fields.sickID = sickID;
    addSickDesc->fields.sickCont.fields.raw = sickCont;
    addSickDesc->fields.sickCause = SickCause::OTHER;
    addSickDesc->fields.isDisplayTokuseiWindow = false;
    addSickDesc->fields.isFailResultDisplay = false;
    Common::AddSick(args, &addSickDesc, nullptr);
}
void HandlerCureSick(EventFactor_EventHandlerArgs_o **args, uint8_t targetPokeID) {
    system_load_typeinfo((void *)0x893f);
    auto desc = (Section_CureSick_Description_o *)
            il2cpp_object_new(Section_CureSick_Description_TypeInfo);
    desc->ctor(nullptr);
    desc->fields.pokeID = targetPokeID;
    desc->fields.sick = WazaSick::WAZASICK_AKUMU;
    desc->fields.targetPokeID->m_Items[0] = targetPokeID;
    desc->fields.targetPokeCount = 1;
    desc->fields.isDisplayTokuseiWindow = false;
    desc->fields.isStandardMessageDisable = true;
    Common::CureSick(args,&desc,nullptr);
}
void HandlerDamage(EventFactor_EventHandlerArgs_o **args, uint8_t causePokeID, uint8_t targetPokeID, uint16_t damage,
                   bool disableDeadProcess, bool displayAbility) {
    system_load_typeinfo((void *)0x8a36);
    auto *desc = (Section_FromEvent_Damage_Description_o *)
            il2cpp_object_new(Section_FromEvent_Damage_Description_TypeInfo);
    desc->ctor(nullptr);
    desc->fields.pokeID = causePokeID;
    desc->fields.targetPokeID = targetPokeID;
    desc->fields.damage = damage;
    desc->fields.damageCause = DamageCause::OTHER;
    desc->fields.damageCausePokeID = causePokeID;
    desc->fields.disableDeadProcess = disableDeadProcess;
    desc->fields.isDisplayTokuseiWindow = displayAbility;
    Common::Damage(args,&desc, nullptr);
}
void HandlerFormChange(EventFactor_EventHandlerArgs_o **args, uint8_t pokeID, uint8_t nextForm, bool persistOnSwitch,
                       bool displayAbility, bool animationEnabled) {
    system_load_typeinfo((void *)0x88fe);
    BTL_POKEPARAM_o * bpp = Common::GetPokeParam(args,pokeID, nullptr);
    if (bpp->fields.m_formNo == nextForm) return;
    auto * desc = (Section_FromEvent_FormChange_Description_o *)
            il2cpp_object_new(Section_FromEvent_FormChange_Description_TypeInfo);
    desc->ctor(nullptr);
    desc->fields.pokeID = pokeID;
    desc->fields.formNo = nextForm;
    desc->fields.isDontResetFormByOut = persistOnSwitch;
    desc->fields.isDisplayTokuseiWindow = displayAbility;
    desc->fields.isDisplayChangeEffect = animationEnabled;
    //desc->fields.successMessage->Setup(BtlStrType::BTL_STRTYPE_SET, 304, nullptr);
    //desc->fields.successMessage->AddArg(pokeID, nullptr);
    Common::FormChange(args, &desc, nullptr);
}
void HandlerMessage(EventFactor_EventHandlerArgs_o **args, uint8_t pokeID, bool displayAbility) {
    system_load_typeinfo((void *)0x58d8);
    auto *desc = (Section_FromEvent_Message::Description_o *)
            il2cpp_object_new(Section_FromEvent_Message::Description_TypeInfo);
    desc->ctor(nullptr);
    desc->fields.pokeID = pokeID;
    desc->fields.isDisplayTokuseiWindow = displayAbility;
    Common::Message(args, &desc, nullptr);
}
void HandlerRankEffect(EventFactor_EventHandlerArgs_o **args, uint8_t causePokeID, uint8_t targetPokeID,
                       int32_t rankType, int8_t rankVolume, bool displayAbility, bool ignoreSubstitute,
                       bool messageOnFail) {
    system_load_typeinfo((void *)0x89b2);
    auto *rankEffectDesc = (Section_FromEvent_RankEffect_Description_o *)
            il2cpp_object_new(Section_FromEvent_RankEffect_Description_TypeInfo);
    rankEffectDesc->ctor(nullptr);
    rankEffectDesc->fields.pokeID = causePokeID;
    rankEffectDesc->fields.targetPokeCount = 1;
    rankEffectDesc->fields.targetPokeID->m_Items[0] = targetPokeID;
    rankEffectDesc->fields.rankType = rankType;
    rankEffectDesc->fields.rankVolume = rankVolume;
    rankEffectDesc->fields.cause = RankEffectCause::OTHER;
    rankEffectDesc->fields.isDisplayTokuseiWindow = displayAbility;
    rankEffectDesc->fields.isMigawariThrew = ignoreSubstitute;
    rankEffectDesc->fields.isSpFailMessageDisplay = messageOnFail;
    Common::RankEffect(args,&rankEffectDesc, nullptr);
}
void HandlerRankReset(EventFactor_EventHandlerArgs_o **args, uint8_t pokeID) {
    system_load_typeinfo((void *)0xa911);
    auto *desc = (Section_FromEvent_RankReset_Description_o *)
            il2cpp_object_new(Section_FromEvent_RankReset_Description_TypeInfo);
    desc->ctor(nullptr);
    desc->fields.pokeCount = 1;
    desc->fields.pokeID->m_Items[0] = pokeID;
    Common::RankReset(args,&desc, nullptr);
}