#include "Dpr/Battle/Logic/Calc.hpp"
#include "Dpr/Battle/Logic/Common.hpp"
#include "Dpr/Battle/Logic/EventFactor.hpp"
#include "Dpr/Battle/Logic/Handler.hpp"
#include "Dpr/Battle/Logic/Section_FromEvent_Damage.hpp"

#include "il2cpp-api.h"
#include "il2cpp.hpp"
#include "System/Array.hpp"
#include "util.hpp"

using namespace Dpr::Battle::Logic;
using namespace Dpr::Battle::Logic::Handler;

// Template MethodInfo
extern MethodInfo * Handler_Karagenki_WazaPowMethodInfo;

// Remember to update when adding moves
constexpr uint32_t NEW_MOVES_COUNT = 3;

//EventVar.Label
constexpr uint16_t EVENT_VAR_POKEID = 2;
constexpr uint16_t EVENT_VAR_POKEID_ATK = 3;
constexpr uint16_t EVENT_VAR_POKEPOS = 13;
constexpr uint16_t EVENT_VAR_WAZAID = 18;
constexpr uint16_t EVENT_VAR_CHECK_HIDE = 24; // Used Fly/Dig before
constexpr uint16_t EVENT_VAR_WAZA_POWER = 51;
constexpr uint16_t EVENT_VAR_WAZA_POWER_RATIO = 52;
constexpr uint16_t EVENT_VAR_WORK_ADRS = 68;
constexpr uint16_t EVENT_VAR_AVOID_FLAG = 73;
constexpr uint16_t EVENT_VAR_GEN_FLAG = 89;
constexpr uint16_t EVENT_VAR_DISABLE_BURN_FLAG = 90;

//WazaNo
constexpr int32_t WAZA_NO_JUMP_KICK = 26;
constexpr int32_t WAZA_NO_RETURN = 216;
constexpr int32_t WAZA_NO_FRUSTRATION = 218;

//HanderTables
static System::Array<EventFactor_EventHandlerTable_o *> * sHandlerTableJumpKick;
static System::Array<EventFactor_EventHandlerTable_o *> * sHandlerTableReturn;
static System::Array<EventFactor_EventHandlerTable_o *> * sHandlerTableFrustration;

//EventID
constexpr int16_t EVENT_ID_REQWAZA_MSG = 26;
constexpr int16_t EVENT_ID_WAZA_EXECUTE_NO_EFFECT = 40;
constexpr int16_t EVENT_ID_WAZA_POWER = 70;

//EventHandler delegates
void HandlerJumpKick(EventFactor_EventHandlerArgs_o **args, uint8_t pokeID, MethodInfo *method) {
    system_load_typeinfo((void *)0xaa66);

    int32_t pokeIDVar = Common::GetEventVar(args, EVENT_VAR_POKEID, nullptr);
    if (pokeIDVar != pokeID)
        return;

    BTL_POKEPARAM_o *bpp = Common::GetPokeParam(args, pokeID, nullptr);
    uint32_t damage = Calc::QuotMaxHP(bpp, 2, true, nullptr);
    Section_FromEvent_Damage_Description_o *desc = (Section_FromEvent_Damage_Description_o *)
            il2cpp_object_new(Section_FromEvent_Damage_Description_TypeInfo);
    desc->ctor(nullptr);
    desc->fields.pokeID = pokeID;
    desc->fields.targetPokeID = pokeID;
    desc->fields.damage = (uint16_t)damage;
    desc->fields.damageCause = 19;
    desc->fields.damageCausePokeID = pokeID;
    desc->fields.successMessage->Setup(2, 1224, nullptr);
    desc->fields.successMessage->AddArg(pokeIDVar, nullptr);
    Common::Damage(args,&desc, nullptr);
}
void HandlerReturn(EventFactor_EventHandlerArgs_o **args, uint8_t pokeID, MethodInfo *method) {
    int32_t evPokeID = Common::GetEventVar(args, EVENT_VAR_POKEID_ATK, (MethodInfo *) nullptr);
    if (evPokeID != pokeID)
        return;

    BTL_POKEPARAM_o * bpp = Common::GetPokeParam(args, pokeID, (MethodInfo *) nullptr);
    uint8_t friendship = bpp->GetFriendship((MethodInfo *) nullptr);
    int32_t waza_power = friendship / 2.5;
    Common::RewriteEventVar(args, EVENT_VAR_WAZA_POWER, waza_power, (MethodInfo *) nullptr);
}
void HandlerFrustration(EventFactor_EventHandlerArgs_o **args, uint8_t pokeID, MethodInfo *method) {
    int32_t evPokeID = Common::GetEventVar(args, EVENT_VAR_POKEID_ATK, (MethodInfo *) nullptr);
    if (evPokeID != pokeID)
        return;

    BTL_POKEPARAM_o * bpp = Common::GetPokeParam(args, pokeID, (MethodInfo *) nullptr);
    uint8_t friendship = bpp->GetFriendship((MethodInfo *) nullptr);
    int32_t waza_power = (255 - friendship) / 2.5;
    Common::RewriteEventVar(args, EVENT_VAR_WAZA_POWER, waza_power, (MethodInfo *) nullptr);
}

//Creates an EventHandler from an Il2CppMethodPointer
EventFactor_EventHandlerTable_o * CreateEventHandler(uint16_t eventID, Il2CppMethodPointer methodPointer) {
    MethodInfo * method = copyMethodInfo(Handler_Karagenki_WazaPowMethodInfo, methodPointer);
    EventFactor_EventHandlerTable_o * evtHandlerTable = (EventFactor_EventHandlerTable_o *)
            il2cpp_object_new(EventFactor_EventHandlerTable_TypeInfo);
    EventFactor_EventHandler_o * evtHandler = (EventFactor_EventHandler_o *)
            il2cpp_object_new(EventFactor_EventHandler_TypeInfo);
    evtHandler->ctor(0, method);
    evtHandlerTable->fields.eventID = eventID;
    evtHandlerTable->fields.eventHandler = evtHandler;

    return evtHandlerTable;
}

//HandlerGetFunc delegates
System::Array<EventFactor_EventHandlerTable_o *> * ADD_JumpKick(MethodInfo *method) {
    if (sHandlerTableJumpKick == nullptr) {
        sHandlerTableJumpKick = (System::Array<EventFactor_EventHandlerTable_o *> *)
                system_array_new(EventFactor_EventHandlerTable_Array_TypeInfo, 1);
        sHandlerTableJumpKick->m_Items[0] =
                CreateEventHandler(EVENT_ID_WAZA_EXECUTE_NO_EFFECT, (Il2CppMethodPointer) &HandlerJumpKick);
    }
    return sHandlerTableJumpKick;
}
System::Array<EventFactor_EventHandlerTable_o *> * ADD_Return(MethodInfo *method) {
    if (sHandlerTableReturn == nullptr) {
        sHandlerTableReturn = (System::Array<EventFactor_EventHandlerTable_o *> *)
                system_array_new(EventFactor_EventHandlerTable_Array_TypeInfo, 1);
        sHandlerTableReturn->m_Items[0] =
                CreateEventHandler(EVENT_ID_WAZA_POWER, (Il2CppMethodPointer) &HandlerReturn);
    }
    return sHandlerTableReturn;
}
System::Array<EventFactor_EventHandlerTable_o *> * ADD_Frustration(MethodInfo *method) {
    if (sHandlerTableFrustration == nullptr) {
        sHandlerTableFrustration = (System::Array<EventFactor_EventHandlerTable_o *> *)
                system_array_new(EventFactor_EventHandlerTable_Array_TypeInfo, 1);
        sHandlerTableFrustration->m_Items[0] =
                CreateEventHandler(EVENT_ID_WAZA_POWER, (Il2CppMethodPointer) &HandlerFrustration);
    }
    return sHandlerTableFrustration;
}

//Adds an additional entry to GET_FUNC_TABLE
void AddGET_FUNC_TABLE_ELEM(System::Array<Waza_GET_FUNC_TABLE_ELEM_o> * getFuncTable, uint32_t * idx, int32_t wazaNo,
                            Il2CppMethodPointer methodPointer) {
    MethodInfo * method = copyMethodInfo(Method_ADD_Karagenki, methodPointer);
    Waza_GET_FUNC_TABLE_ELEM_o * elem = &getFuncTable->m_Items[*idx];
    Waza_HandlerGetFunc_o * func = (Waza_HandlerGetFunc_o *) il2cpp_object_new(Waza_HandlerGetFunc_TypeInfo);
    func->ctor(0, method);
    elem->fields.waza = wazaNo;
    elem->fields.func = func;
    *idx += 1;
}

//Entry point. Replaces system_array_new.
void * CreateGET_FUNC_TABLE(void * typeInfo, uint32_t len) {
    System::Array<Waza_GET_FUNC_TABLE_ELEM_o> * getFuncTable =
            (System::Array<Waza_GET_FUNC_TABLE_ELEM_o> *) system_array_new(typeInfo, len + NEW_MOVES_COUNT);
    uint32_t idx = len;

    AddGET_FUNC_TABLE_ELEM(getFuncTable, &idx, WAZA_NO_JUMP_KICK, (Il2CppMethodPointer) &ADD_JumpKick);
    AddGET_FUNC_TABLE_ELEM(getFuncTable, &idx, WAZA_NO_RETURN, (Il2CppMethodPointer) &ADD_Return);
    AddGET_FUNC_TABLE_ELEM(getFuncTable, &idx, WAZA_NO_FRUSTRATION, (Il2CppMethodPointer) &ADD_Frustration);

    return getFuncTable;
}