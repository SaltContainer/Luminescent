#include "Dpr/Battle/Logic/Calc.hpp"
#include "Dpr/Battle/Logic/Common.hpp"
#include "Dpr/Battle/Logic/EventFactor.hpp"
#include "Dpr/Battle/Logic/EventID.hpp"
#include "Dpr/Battle/Logic/EventVar.hpp"
#include "Dpr/Battle/Logic/Handler.hpp"
#include "Dpr/Battle/Logic/Handler/Pos.hpp"
#include "Dpr/Battle/Logic/PosEffectManager.hpp"
#include "Pml/WazaData/WazaRankEffect.hpp"
#include "Pml/WazaData/WazaSick.hpp"

#include "il2cpp-api.h"
#include "il2cpp.hpp"
#include "System/Array.hpp"
#include "util.hpp"

using namespace Dpr::Battle::Logic;
using namespace Dpr::Battle::Logic::Handler;
using namespace Pml::WazaData;

// Template MethodInfo
extern MethodInfo * handler_pos_BatonTouch;

// WorkIdx
constexpr uint8_t WORKIDX_SKIP_SPFAIL_CHECK = 0;
constexpr uint8_t WORKIDX_FIRST_TURN_FLAG = 1;
constexpr uint8_t WORKIDX_TURN = 2;
constexpr uint8_t A = 3;
constexpr uint8_t B = 4;
constexpr uint8_t C = 5;
constexpr uint8_t WORKIDX_USER_POKEID = 6;

// BtlPosEffect
constexpr int32_t NIGHTMARE_POS = 5;

// Remember to update when adding handlers
constexpr uint32_t NEW_POS_EFFECT_COUNT = 0;

// HanderTables
static System::Array<EventFactor_EventHandlerTable_o *> * sHandlerTableNightmarePos;

// --- EventHandler delegates ---
void HandlerNightmarePosTurncheckDone(EventFactor_EventHandlerArgs_o **args, uint8_t pokePos, MethodInfo *method) {
    uint8_t pokeID = Common::GetWorkValue(args, WORKIDX_USER_POKEID, nullptr);
    BTL_POKEPARAM_o * bpp = Common::GetPokeParam(args, pokeID, nullptr);
    if (bpp->CheckNemuri(BTL_POKEPARAM_NemuriCheckMode::NEMURI_CHECK_ONLY_SICK, nullptr) &&
    bpp->CheckSick(WazaSick::WAZASICK_AKUMU, nullptr)) {
        HandlerDamage(args, pokeID, pokeID,
                      Calc::QuotMaxHP(bpp, 4, true, nullptr),
                      false, false);
        return;
    }
    HandlerCureSick(args, pokeID);
    Pos::common_removePosEffect(args, pokePos, nullptr);
}

EventFactor_EventHandlerTable_o * CreatePosEventHandler(uint16_t eventID, Il2CppMethodPointer methodPointer) {
    return CreateEventHandler(eventID, handler_pos_BatonTouch, methodPointer);
}

// --- HandlerGetFunc delegates ---
System::Array<EventFactor_EventHandlerTable_o *> * ADD_NightmarePos(MethodInfo *method) {
    if (sHandlerTableNightmarePos == nullptr) {
        sHandlerTableNightmarePos = (System::Array<EventFactor_EventHandlerTable_o *> *) system_array_new(EventFactor_EventHandlerTable_Array_TypeInfo, 1);
        sHandlerTableNightmarePos->m_Items[0] = CreatePosEventHandler(EventID::TURNCHECK_DONE, (Il2CppMethodPointer) &HandlerNightmarePosTurncheckDone);
    }
    return sHandlerTableNightmarePos;
}

//Adds an additional entry to GET_FUNC_TABLE
void SetPosFunctionTable(System::Array<Pos_GET_FUNC_TABLE_ELEM_o> * getFuncTable, uint32_t * idx, int32_t effect, Il2CppMethodPointer methodPointer) {
    MethodInfo * method = copyMethodInfo(Method_ADD_BatonTouch, methodPointer);
    Pos_GET_FUNC_TABLE_ELEM_o * elem = &getFuncTable->m_Items[*idx];
    Pos_HandlerGetFunc_o * func = (Pos_HandlerGetFunc_o *) il2cpp_object_new(Pos_HandlerGetFunc_TypeInfo);
    func->ctor((intptr_t)methodPointer, method);
    elem->fields.eff = effect;
    elem->fields.func = func;
    *idx += 1;
}

//Entry point. Replaces system_array_new.
void * Pos_system_array_new(void * typeInfo, uint32_t len) {
    System::Array<Pos_GET_FUNC_TABLE_ELEM_o> * getFuncTable = (System::Array<Pos_GET_FUNC_TABLE_ELEM_o> *) system_array_new(typeInfo, len + NEW_POS_EFFECT_COUNT);
    uint32_t idx = len;

    //SetPosFunctionTable(getFuncTable, &idx, RAGE_POS, (Il2CppMethodPointer) &ADD_RagePos);

    return getFuncTable;
}

void Dpr_Battle_Logic_PosEffectManager_CreateEffectStatusArray(PosEffectManager_o *__this, MethodInfo *method) {
    system_load_typeinfo((void *)0x6f54);
    system_load_typeinfo((void *)0x6f56);
    PosEffectStatus_array_array *table = __this->fields.m_posEffects;
    for (int posIdx = 0; posIdx < 6; ++posIdx) {
        PosEffectStatus_array *array = table->m_Items[posIdx];
        for (int effectIdx = 0; effectIdx < 15; ++effectIdx) {
            auto posEffectStatus = (PosEffectStatus_o *)il2cpp_object_new(PosEffectStatus_TypeInfo);
            auto data = (PosEffectStatus_Data_o *)il2cpp_object_new(PosEffectStatus_Data_TypeInfo);
            PosEffectStatus_Fields *posEffectStatusFields = &posEffectStatus->fields;
            posEffectStatusFields->m_data = data;
            _system_array_init((void *)posEffectStatusFields);
            posEffectStatusFields->m_data->fields.pos = posIdx;
            posEffectStatusFields->m_data->fields.posEffect = effectIdx;
            array->m_Items[effectIdx] = posEffectStatus;
            _system_array_init(array->m_Items);
        }
    }
}