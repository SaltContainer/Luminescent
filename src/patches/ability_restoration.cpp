/*
#include "Dpr/Battle/Logic/Common.hpp"
#include "Dpr/Battle/Logic/EventFactor.hpp"
#include "Dpr/Battle/Logic/EventID.hpp"
#include "Dpr/Battle/Logic/EventVar.hpp"
#include "Dpr/Battle/Logic/Handler.hpp"

#include "il2cpp-api.h"
#include "il2cpp.hpp"
#include "System/Array.hpp"
#include "util.hpp"
#include "logger.hpp"

using namespace Dpr::Battle::Logic;
using namespace Dpr::Battle::Logic::Handler;

// 4c79da0
extern MethodInfo * Method_handler_TetunoKobusi;

const uint32_t NUM_NEW_ABILITIES = 1;
const uint32_t BLADEMASTER_ID = 268;

static System::Array<EventFactor_EventHandlerTable_o *> * sBlademasterEventHandlerTable = nullptr;

const uint32_t NUM_BLADEMASTER_MOVES = 12;
const int32_t BLADEMASTER_MOVES[NUM_BLADEMASTER_MOVES] = {
    533, // Sacred Sword
    427, // Psycho Cut
    15, // Cut
    163, // Slash
    348, // Leaf Blade
    400, // Night Slash
    206, // False Swipe
    404, // X-Scissor
    669, // Solar Blade
    210, // Fury Cutter
    534, // Razor Shell
    421, // Shadow claw
};

bool isBlademasterMove(int32_t wazaID)
{
    for (uint32_t i = 0; i < NUM_BLADEMASTER_MOVES; i++)
    {
        if (BLADEMASTER_MOVES[i] == wazaID)
        {
            return true;
        }
    }

    return false;
}

void handler_Blademaster_WazaPow(EventFactor_EventHandlerArgs_o **args, uint8_t pokeID, MethodInfo *method)
{
    int32_t evPokeID = Common::GetEventVar(args, EventVar::POKEID_ATK, (MethodInfo *) nullptr);

    if (evPokeID != pokeID)
    {
        return;
    }

    int32_t wazaID = Common::GetEventVar(args, EventVar::WAZAID, (MethodInfo *) nullptr);

    if (isBlademasterMove(wazaID))
    {
        // 1.2 * pow(2, 12) = 0x1333
        // So we're boosting by 1.2 here
        Common::MulEventVar(args, EventVar::POWER, 0x1333, (MethodInfo *) nullptr);
        
    }
}


void handler_Blademaster_CritCheck(EventFactor_EventHandlerArgs_o **args, uint8_t pokeID, MethodInfo *method)
{
    int32_t evPokeID = Common::GetEventVar(args, EventVar::POKEID_ATK, (MethodInfo *) nullptr);

    if (evPokeID != pokeID)
    {
        return;
    }

    int32_t wazaID = Common::GetEventVar(args, EventVar::WAZAID, (MethodInfo *) nullptr);

    if (isBlademasterMove(wazaID))
    {
        int32_t critRank = Common::GetEventVar(args, EventVar::CRITICAL_RANK, (MethodInfo *) nullptr);
        Common::RewriteEventVar(args, EventVar::CRITICAL_RANK, (critRank + 1) & 0xff, (MethodInfo *) nullptr);
    }
}

EventFactor_EventHandlerTable_o * CreateAbilityEventHandler(uint16_t eventID, Il2CppMethodPointer methodPointer) {
    return CreateEventHandler(eventID, Method_handler_TetunoKobusi, methodPointer);
}

System::Array<EventFactor_EventHandlerTable_o *> * ADD_Blademaster(MethodInfo *method)
{
    if (sBlademasterEventHandlerTable == nullptr) {
        sBlademasterEventHandlerTable = (System::Array<EventFactor_EventHandlerTable_o *> *) system_array_new(EventFactor_EventHandlerTable_Array_TypeInfo, 2);
        sBlademasterEventHandlerTable->m_Items[0] = CreateAbilityEventHandler(EventID::WAZA_POWER, (Il2CppMethodPointer) &handler_Blademaster_WazaPow);
        sBlademasterEventHandlerTable->m_Items[1] = CreateAbilityEventHandler(EventID::CRITICAL_CHECK, (Il2CppMethodPointer) &handler_Blademaster_CritCheck);
    }

    return sBlademasterEventHandlerTable;
}

void SetAbilityFunctionTable(System::Array<Tokusei_GET_FUNC_TABLE_ELEM_o> * getFuncTable, uint32_t * idx, int32_t tokusei, Il2CppMethodPointer methodPointer)
{
    socket_log_fmt("Method_ADD_Karagenki: %08X\n", Method_ADD_Karagenki);
    socket_log_fmt("Method_ADD_TetunoKobusi: %08X\n", Method_ADD_TetunoKobusi);
    MethodInfo * method = copyMethodInfo(Method_ADD_TetunoKobusi, methodPointer);
    Tokusei_GET_FUNC_TABLE_ELEM_o * elem = &getFuncTable->m_Items[*idx];
    socket_log_fmt("Got GET_FUNC_TABLE_ELEM at %i\n", *idx);
    Tokusei_HandlerGetFunc_o * func = (Tokusei_HandlerGetFunc_o *) il2cpp_object_new(Tokusei_HandlerGetFunc_TypeInfo);
    socket_log_fmt("entry.method: %08X\n", methodPointer);
    func->ctor((intptr_t) methodPointer, method);
    elem->fields.tokusei = tokusei;
    elem->fields.func = func;
    *idx += 1;
}

void * Tokusei_system_array_new(void * typeInfo, uint32_t len)
{
    System::Array<Tokusei_GET_FUNC_TABLE_ELEM_o> * getFuncTable = (System::Array<Tokusei_GET_FUNC_TABLE_ELEM_o> *) system_array_new(typeInfo, len + NUM_NEW_ABILITIES);
    uint32_t idx = len;

    socket_log_fmt("Return idx: %08X\n", idx);
    SetAbilityFunctionTable(getFuncTable, &idx, BLADEMASTER_ID, (Il2CppMethodPointer) &ADD_Blademaster);

    return getFuncTable;
}
*/