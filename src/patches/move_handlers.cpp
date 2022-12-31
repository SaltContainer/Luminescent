#include "Dpr/Battle/Logic/BtlStrType.hpp"
#include "Dpr/Battle/Logic/Calc.hpp"
#include "Dpr/Battle/Logic/Common.hpp"
#include "Dpr/Battle/Logic/EventFactor.hpp"
#include "Dpr/Battle/Logic/EventID.hpp"
#include "Dpr/Battle/Logic/EventVar.hpp"
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

// Remember to update when adding handlers
constexpr uint32_t NEW_MOVES_COUNT = 3;

// MoveIDs
constexpr int32_t JUMP_KICK_ID = 26;
constexpr int32_t RETURN_ID = 216;
constexpr int32_t FRUSTRATION_ID = 218;

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

    int32_t pokeIDVar = Common::GetEventVar(args, EventVar::POKEID, nullptr);
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
    desc->fields.successMessage->Setup(BtlStrType::BTL_STRTYPE_SET, 1224, nullptr);
    desc->fields.successMessage->AddArg(pokeIDVar, nullptr);
    Common::Damage(args,&desc, nullptr);
}
void HandlerReturn(EventFactor_EventHandlerArgs_o **args, uint8_t pokeID, MethodInfo *method) {
    int32_t evPokeID = Common::GetEventVar(args, EventVar::POKEID_ATK, (MethodInfo *) nullptr);
    if (evPokeID != pokeID)
        return;

    BTL_POKEPARAM_o * bpp = Common::GetPokeParam(args, pokeID, (MethodInfo *) nullptr);
    uint8_t friendship = bpp->GetFriendship((MethodInfo *) nullptr);
    int32_t waza_power = friendship / 2.5;
    Common::RewriteEventVar(args, EventVar::WAZA_POWER, waza_power, (MethodInfo *) nullptr);
}
void HandlerFrustration(EventFactor_EventHandlerArgs_o **args, uint8_t pokeID, MethodInfo *method) {
    int32_t evPokeID = Common::GetEventVar(args, EventVar::POKEID_ATK, (MethodInfo *) nullptr);
    if (evPokeID != pokeID)
        return;

    BTL_POKEPARAM_o * bpp = Common::GetPokeParam(args, pokeID, (MethodInfo *) nullptr);
    uint8_t friendship = bpp->GetFriendship((MethodInfo *) nullptr);
    int32_t waza_power = (255 - friendship) / 2.5;
    Common::RewriteEventVar(args, EventVar::WAZA_POWER, waza_power, (MethodInfo *) nullptr);
}

EventFactor_EventHandlerTable_o * CreateMoveEventHandler(uint16_t eventID, Il2CppMethodPointer methodPointer) {
    return CreateEventHandler(eventID, Handler_Karagenki_WazaPowMethodInfo, methodPointer);
}

//HandlerGetFunc delegates
System::Array<EventFactor_EventHandlerTable_o *> * ADD_JumpKick(MethodInfo *method) {
    if (sHandlerTableJumpKick == nullptr) {
        sHandlerTableJumpKick = (System::Array<EventFactor_EventHandlerTable_o *> *)
                system_array_new(EventFactor_EventHandlerTable_Array_TypeInfo, 1);
        sHandlerTableJumpKick->m_Items[0] =
                CreateMoveEventHandler(EVENT_ID_WAZA_EXECUTE_NO_EFFECT, (Il2CppMethodPointer) &HandlerJumpKick);
    }
    return sHandlerTableJumpKick;
}
System::Array<EventFactor_EventHandlerTable_o *> * ADD_Return(MethodInfo *method) {
    if (sHandlerTableReturn == nullptr) {
        sHandlerTableReturn = (System::Array<EventFactor_EventHandlerTable_o *> *)
                system_array_new(EventFactor_EventHandlerTable_Array_TypeInfo, 1);
        sHandlerTableReturn->m_Items[0] =
                CreateMoveEventHandler(EVENT_ID_WAZA_POWER, (Il2CppMethodPointer) &HandlerReturn);
    }
    return sHandlerTableReturn;
}
System::Array<EventFactor_EventHandlerTable_o *> * ADD_Frustration(MethodInfo *method) {
    if (sHandlerTableFrustration == nullptr) {
        sHandlerTableFrustration = (System::Array<EventFactor_EventHandlerTable_o *> *)
                system_array_new(EventFactor_EventHandlerTable_Array_TypeInfo, 1);
        sHandlerTableFrustration->m_Items[0] =
                CreateMoveEventHandler(EVENT_ID_WAZA_POWER, (Il2CppMethodPointer) &HandlerFrustration);
    }
    return sHandlerTableFrustration;
}

//Adds an additional entry to GET_FUNC_TABLE
void SetMoveFunctionTable(System::Array<Waza_GET_FUNC_TABLE_ELEM_o> * getFuncTable, uint32_t * idx, int32_t wazaNo,
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
void * Waza_system_array_new(void * typeInfo, uint32_t len) {
    System::Array<Waza_GET_FUNC_TABLE_ELEM_o> * getFuncTable =
            (System::Array<Waza_GET_FUNC_TABLE_ELEM_o> *) system_array_new(typeInfo, len + NEW_MOVES_COUNT);
    uint32_t idx = len;

    SetMoveFunctionTable(getFuncTable, &idx, JUMP_KICK_ID, (Il2CppMethodPointer) &ADD_JumpKick);
    SetMoveFunctionTable(getFuncTable, &idx, RETURN_ID, (Il2CppMethodPointer) &ADD_Return);
    SetMoveFunctionTable(getFuncTable, &idx, FRUSTRATION_ID, (Il2CppMethodPointer) &ADD_Frustration);

    return getFuncTable;
}