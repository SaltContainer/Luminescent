#include "Dpr/Battle/Logic/ActionDesc.hpp"
#include "Dpr/Battle/Logic/BtlEscapeMode.hpp"
#include "Dpr/Battle/Logic/Calc.hpp"
#include "Dpr/Battle/Logic/Common.hpp"
#include "Dpr/Battle/Logic/ContFlag.hpp"
#include "Dpr/Battle/Logic/EventFactor.hpp"
#include "Dpr/Battle/Logic/EventID.hpp"
#include "Dpr/Battle/Logic/EventVar.hpp"
#include "Dpr/Battle/Logic/ExPokePos.hpp"
#include "Dpr/Battle/Logic/Handler.hpp"
#include "Dpr/Battle/Logic/Handler/Waza.hpp"
#include "Dpr/Battle/Logic/InterruptCode.hpp"
#include "Dpr/Battle/Logic/PokeID.hpp"
#include "Dpr/Battle/Logic/PokeActionCategory.hpp"
#include "Dpr/Battle/Logic/Section_FromEvent_Message.hpp"
#include "Dpr/Battle/Logic/Section_InterruptAction.hpp"
#include "Dpr/Battle/Logic/Section_ProcessActionCore.hpp"
#include "Dpr/Battle/Logic/SICKCONT.hpp"
#include "Dpr/Battle/Logic/WAZADATA.hpp"
#include "Dpr/Battle/Logic/WazaFailCause.hpp"
#include "Pml/WazaData/WazaFlag.hpp"
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
extern MethodInfo * Handler_Karagenki_WazaPowMethodInfo;

// WorkIdx
constexpr uint8_t A = 0;
constexpr uint8_t B = 1;
constexpr uint8_t C = 2;
constexpr uint8_t D = 3;
constexpr uint8_t E = 4;
constexpr uint8_t F = 5;
constexpr uint8_t PERSIST = 6;

// MoveIDs
constexpr int32_t NULL_WAZA = 0;
constexpr int32_t JUMP_KICK = 26;
constexpr int32_t SONIC_BOOM = 49;
constexpr int32_t DRAGON_RAGE = 82;
constexpr int32_t RAGE = 99;
constexpr int32_t BIDE = 117;
constexpr int32_t MIRROR_MOVE = 119;
constexpr int32_t PSYWAVE = 149;
constexpr int32_t SPIDER_WEB = 169;
constexpr int32_t NIGHTMARE = 171;
constexpr int32_t RETURN = 216;
constexpr int32_t FRUSTRATION = 218;
constexpr int32_t MAGNITUDE = 222;
constexpr int32_t PURSUIT = 228;
constexpr int32_t U_TURN = 369;
constexpr int32_t VOLT_SWITCH = 521;
constexpr int32_t PARTING_SHOT = 575;
constexpr int32_t GLITZY_GLOW = 736;
constexpr int32_t BADDY_BAD = 737;
constexpr int32_t FREEZY_FROST = 739;
constexpr int32_t VEEVEE_VOLLEY = 741;

// Side Effects
constexpr int32_t EFFECT_REFLECT = 141;
constexpr int32_t EFFECT_LIGHT_SCREEN = 145;

// HanderTables
static System::Array<EventFactor_EventHandlerTable_o *> * sHandlerTableJumpKick;
static System::Array<EventFactor_EventHandlerTable_o *> * sHandlerTableSonicBoom;
static System::Array<EventFactor_EventHandlerTable_o *> * sHandlerTableDragonRage;
static System::Array<EventFactor_EventHandlerTable_o *> * sHandlerTableRage;
static System::Array<EventFactor_EventHandlerTable_o *> * sHandlerTableBide;
static System::Array<EventFactor_EventHandlerTable_o *> * sHandlerTableMirrorMove;
static System::Array<EventFactor_EventHandlerTable_o *> * sHandlerTablePsywave;
static System::Array<EventFactor_EventHandlerTable_o *> * sHandlerTableNightmare;
static System::Array<EventFactor_EventHandlerTable_o *> * sHandlerTableReturn;
static System::Array<EventFactor_EventHandlerTable_o *> * sHandlerTableFrustration;
static System::Array<EventFactor_EventHandlerTable_o *> * sHandlerTableMagnitude;
static System::Array<EventFactor_EventHandlerTable_o *> * sHandlerTablePursuit;
static System::Array<EventFactor_EventHandlerTable_o *> * sHandlerTableGlitzyGlow;
static System::Array<EventFactor_EventHandlerTable_o *> * sHandlerTableBaddyBad;
static System::Array<EventFactor_EventHandlerTable_o *> * sHandlerTableFreezyFrost;
static System::Array<EventFactor_EventHandlerTable_o *> * sHandlerTableVeeveeVolley;

void PursuitInterrupt(Section_ProcessActionCore_o *section, PokeAction_o *action, uint8_t targetPokeID) {
    if (((Section_o *)section)->CheckEncoreWazaChange(action, nullptr) != NULL_WAZA) return;
    action->fields.actionDesc->fields.isOiutiInterruptAction = true;
    action->fields.actionParam_Fight->fields.targetPos =
            ((Section_o *)section)->GetPokePos(targetPokeID, nullptr);
    section->fields.super.m_pSectionContainer->fields.m_section_InterruptAction->processAction(action,
                                                                                               nullptr);
}
void PursuitProcess(Section_ProcessActionCore_o *section, PokeActionContainer_o *pokeActionContainer,
                    PokeAction_o *thisAction) {
    bool isPursuitTarget = thisAction->fields.actionCategory == PokeActionCategory::PokeChange;
    bool isFight = thisAction->fields.actionCategory == PokeActionCategory::Fight;
    if (!isPursuitTarget && isFight) {
        int32_t wazaID = thisAction->fields.actionParam_Fight->fields.waza;
        isPursuitTarget = wazaID == U_TURN || wazaID == VOLT_SWITCH || wazaID == PARTING_SHOT;
    }
    if (!isPursuitTarget) return;
    uint8_t thisPokeID = thisAction->fields.bpp->GetID(nullptr);
    for (int i = 0; i < pokeActionContainer->fields.m_count; i++) {
        PokeAction_o *action = pokeActionContainer->fields.m_actions->m_Items[i];
        if (action->fields.fDone ||
        action->fields.actionCategory != PokeActionCategory::Fight) continue;
        PokeActionParam_Fight_o *papf = action->fields.actionParam_Fight;
        if (papf->fields.waza != PURSUIT) continue;
        uint8_t pokeID = action->fields.bpp->GetID(nullptr);
        if (!isFight && section->fields.super.m_pMainModule->IsFriendPokeID(thisPokeID, pokeID,
                                                                            nullptr)) continue;
        if (isFight && papf->fields.aimTargetID != thisPokeID) continue;
        PursuitInterrupt(section, action, thisPokeID);
    }
}
void Dpr_Battle_Logic_Section_ProcessActionCore_Execute(Section_ProcessActionCore_o *spac,
                                                        Section_ProcessActionCore_Result_o *pResult,
                                                        Section_ProcessActionCore_Description_o **description,
                                                        MethodInfo *method) {
    PokeAction_o *pa = (*description)->fields.pokeAction;
    if (pa->fields.fDone) return;
    pa->fields.fDone = true;
    PursuitProcess(spac, spac->fields.super.m_pPokemonActionContainer, pa);
    int32_t pac = pa->fields.actionCategory;
    if (pac == PokeActionCategory::Cheer) {
        spac->action_Cheer(pa, nullptr);
        return;
    }
    BTL_POKEPARAM_o *bpp = pa->fields.bpp;
    if (bpp == nullptr || bpp->IsDead(nullptr)) return;
    uint8_t pokeID = bpp->GetID(nullptr);
    if (!spac->fields.super.m_pBattleEnv->fields.m_posPoke->IsExist(pokeID, nullptr)) return;
    ServerCommandPutter_o *scp = spac->fields.super.m_pServerCmdPutter;
    EventLauncher_o *el = spac->fields.super.m_pEventLauncher;
    if (bpp->CheckSick(WazaSick::WAZASICK_FREEFALL, nullptr) &&
    (pac != PokeActionCategory::Escape ||
    spac->fields.super.m_pMainModule->GetEscapeMode(nullptr) !=  BtlEscapeMode::BTL_ESCAPE_MODE_CONFIRM)) {
        if (bpp->COUNTER_Get(BTL_POKEPARAM_Counter::COUNTER_MAMORU, nullptr) != '\0')
            scp->SetBppCounter(bpp,BTL_POKEPARAM_Counter::COUNTER_MAMORU, 0, nullptr);
        el->Event_ActProcCanceled(pa, nullptr);
        return;
    }
    spac->reinforceRaidBoss(pa, nullptr);
    ActionDesc_o *ad = pa->fields.actionDesc;
    if (ad->fields.isOdorikoReaction ||
    ad->fields.isSaihaiReaction) {
        InsertActionInfo_o *iaf = (ad->fields).insertInfo;
        scp->InsertWazaInfo(pokeID, iaf->fields.isTokuseiWindowDisplay, &iaf->fields.prevActionMessage, nullptr);
    }
    el->Event_ActProcStart(pa, nullptr);
    bpp->TURNFLAG_Set(BTL_POKEPARAM_TurnFlag::TURNFLG_ACTION_START, nullptr);
    spac->action(pa, nullptr);
    if (pac < 3) {
        bpp->TURNFLAG_Set(BTL_POKEPARAM_TurnFlag::TURNFLG_ACTION_DONE, nullptr);
        scp->SetContFlag(bpp,ContFlag::CONTFLG_ACTION_DONE, nullptr);
    }
    if (spac->fields.super.m_pSharedData->fields.m_interruptAccessor->IsRequested(InterruptCode::QUIT_ESCAPE,
                                                                                    nullptr)) return;
    el->Event_ActProcEnd(bpp, pac, nullptr);
}

// --- EventHandler delegates ---
// Sonic Boom
void HandlerSonicBoomWazaDmgProc1(EventFactor_EventHandlerArgs_o **args, uint8_t pokeID, MethodInfo *method) {
    if (Common::GetEventVar(args, EventVar::POKEID_ATK, nullptr) != pokeID) return;
    Common::RewriteEventVar(args, EventVar::FIX_DAMAGE_FLAG, true, nullptr);
    Common::RewriteEventVar(args, EventVar::FIX_DAMAGE, 20, nullptr);
}
// Dragon Rage
void HandlerDragonRageWazaDmgProc1(EventFactor_EventHandlerArgs_o **args, uint8_t pokeID, MethodInfo *method) {
    if (Common::GetEventVar(args, EventVar::POKEID_ATK, nullptr) != pokeID) return;
    Common::RewriteEventVar(args, EventVar::FIX_DAMAGE_FLAG, true, nullptr);
    Common::RewriteEventVar(args, EventVar::FIX_DAMAGE, 40, nullptr);
}
// Rage
void HandlerRageWazaCallDecide(EventFactor_EventHandlerArgs_o **args, uint8_t pokeID, MethodInfo *method) {
    if (!Common::GetWorkValue(args, PERSIST, nullptr)) return;
    if (Common::GetEventVar(args, EventVar::POKEID_ATK, nullptr) != pokeID) return;
    Common::SetWorkValue(args, PERSIST, false, nullptr);
}
void HandlerRageWazaExecuteEffective(EventFactor_EventHandlerArgs_o **args, uint8_t pokeID, MethodInfo *method) {
    if (Common::GetEventVar(args, EventVar::POKEID, nullptr) != pokeID) return;
    if (Common::GetEventVar(args, EventVar::WAZAID, nullptr) != RAGE) return;
    Common::SetWorkValue(args, PERSIST, true, nullptr);
}
void HandlerRageWazaDmgReaction(EventFactor_EventHandlerArgs_o **args, uint8_t pokeID, MethodInfo *method) {
    if (!Common::GetWorkValue(args, PERSIST, nullptr)) return;
    if (Common::CheckShowDown(args, nullptr)) return;
    if (Common::GetEventVar(args, EventVar::POKEID_DEF, nullptr) != pokeID) return;
    if (Common::GetEventVar(args, EventVar::MIGAWARI_FLAG, nullptr)) return;
    HandlerRankEffect(args, pokeID, pokeID, WazaRankEffect::ATTACK, 1,
                      false, false, true);
}
void HandlerRageMemberOutFixed(EventFactor_EventHandlerArgs_o **args, uint8_t pokeID, MethodInfo *method) {
    if (!Common::GetWorkValue(args, PERSIST, nullptr)) return;
    if (Common::GetEventVar(args, EventVar::POKEID, nullptr) != pokeID) return;
    Common::SetWorkValue(args, PERSIST, false, nullptr);
}
// Bide
void HandlerBideCheckDelayWaza(EventFactor_EventHandlerArgs_o **args, uint8_t pokeID, MethodInfo *method) {
    if (Common::GetEventVar(args, EventVar::POKEID_ATK, nullptr) != pokeID) return;
    if (Common::GetWorkValue(args, A, nullptr) >= 2) return;
    Common::RewriteEventVar(args, EventVar::GEN_FLAG, true, nullptr);
    Common::RewriteEventVar(args, EventVar::SUCCESS_FLAG, true, nullptr);
}
void HandlerBideWazaExecuteCheck3rd(EventFactor_EventHandlerArgs_o **args, uint8_t pokeID, MethodInfo *method) {
    if (Common::GetEventVar(args, EventVar::POKEID, nullptr) != pokeID) return;
    if (Common::GetWorkValue(args, A, nullptr) < 2) return;
    if (Common::GetWorkValue(args, B, nullptr) > 0) return;
    Common::RewriteEventVar(args,EventVar::FAIL_CAUSE,WazaFailCause::OTHER,(MethodInfo *)0x0);
}
void HandlerBideWazaCallDecide(EventFactor_EventHandlerArgs_o **args, uint8_t pokeID, MethodInfo *method) {
    if (Common::GetEventVar(args, EventVar::POKEID_ATK, nullptr) != pokeID) return;
    BTL_POKEPARAM_o * bpp = Common::GetPokeParam(args, pokeID, nullptr);
    if (bpp->CheckSick(WazaSick::WAZASICK_WAZALOCK, nullptr)) return;
    if (bpp->CheckNemuri(BTL_POKEPARAM_NemuriCheckMode::NEMURI_CHECK_ONLY_SICK, nullptr)) return;
    if (Common::GetWorkValue(args, 6, nullptr)) return;
    HandlerAddSick(args, pokeID, pokeID, WazaSick::WAZASICK_WAZALOCK,
                   SICKCONT::MakeTurnParam(pokeID,
                                           3,
                                           Common::GetSubID(args, nullptr),
                                           nullptr).fields.raw);
    Common::SetWorkValue(args, PERSIST, true, nullptr);//Active flag
    Common::SetWorkValue(args, A, 0, nullptr);//Turn counter
    Common::SetWorkValue(args, B, 0, nullptr);//Damage taken
    Common::SetWorkValue(args, C, PokeID::INVALID, nullptr);//Target
}
void HandlerBideDecideTarget(EventFactor_EventHandlerArgs_o **args, uint8_t pokeID, MethodInfo *method) {
    if (Common::GetEventVar(args, EventVar::POKEID_ATK, nullptr) != pokeID) return;
    Common::RewriteEventVar(args, EventVar::POKEID_DEF,
                            Common::GetWorkValue(args, C, nullptr),
                            nullptr);
}
void HandlerBideWazaDmgProc1(EventFactor_EventHandlerArgs_o **args, uint8_t pokeID, MethodInfo *method) {
    if (Common::GetEventVar(args, EventVar::POKEID_ATK, nullptr) != pokeID) return;
    Common::RewriteEventVar(args, EventVar::FIX_DAMAGE_FLAG, true, nullptr);
    Common::RewriteEventVar(args, EventVar::FIX_DAMAGE,
                            Common::GetWorkValue(args, B, nullptr) * 2,
                            nullptr);
    Waza::common_Korogaru_Unlock(args, pokeID, nullptr);
}
void HandlerBideWazaDmgReaction(EventFactor_EventHandlerArgs_o **args, uint8_t pokeID, MethodInfo *method) {
    if (Common::GetEventVar(args, EventVar::POKEID_DEF, nullptr) != pokeID) return;
    if (!Common::GetWorkValue(args, PERSIST, nullptr)) return;
    Common::SetWorkValue(args, B,
                         Common::GetWorkValue(args, B, nullptr) +
                         Common::GetEventVar(args, EventVar::DAMAGE, nullptr),
                         nullptr);
    Common::SetWorkValue(args, C,
                         Common::GetEventVar(args, EventVar::POKEID_ATK, nullptr),
                         nullptr);
}
void HandlerBideTurncheckEnd(EventFactor_EventHandlerArgs_o **args, uint8_t pokeID, MethodInfo *method) {
    if (Common::GetEventVar(args, EventVar::POKEID, nullptr) != pokeID) return;
    if (!Common::GetWorkValue(args, PERSIST, nullptr)) return;
    int32_t turnCounter = Common::GetWorkValue(args, A, nullptr) + 1;
    Common::SetWorkValue(args, A, turnCounter, nullptr);
    if (turnCounter < 3 && !Common::GetPokeParam(args, pokeID, nullptr)->
            CheckNemuri(BTL_POKEPARAM_NemuriCheckMode::NEMURI_CHECK_ONLY_SICK, nullptr)) return;
    Common::SetWorkValue(args, A, 0, nullptr);
    Common::SetWorkValue(args, B, 0, nullptr);
    Waza::common_Korogaru_Unlock(args, pokeID, nullptr);
}
// Mirror Move
void HandlerMirrorMoveReqwazaParam(EventFactor_EventHandlerArgs_o **args, uint8_t pokeID, MethodInfo *method) {
    if (Common::GetEventVar(args, EventVar::POKEID, nullptr) != pokeID) return;
    uint8_t targetPokePos = Common::GetEventVar(args, EventVar::POKEPOS_ORG, nullptr);
    uint8_t targetPokeID = Common::GetFrontPokeID(args,&targetPokePos,nullptr);
    if (targetPokeID == PokeID::INVALID) return;
    int32_t targetWazaID = Common::GetPokeParam(args, targetPokeID, nullptr)->fields.m_prevActWazaID;
    if (targetWazaID == NULL_WAZA) return;
    if (!WAZADATA::GetFlag(targetWazaID, WazaFlag::OUMU, nullptr)) return;
    Common::RewriteEventVar(args, EventVar::WAZAID, targetWazaID, nullptr);
    Common::RewriteEventVar(args, EventVar::POKEPOS, targetPokePos, nullptr);
}
// Psywave
void HandlerPsywaveWazaDmgProc1(EventFactor_EventHandlerArgs_o **args, uint8_t pokeID, MethodInfo *method) {
    if (Common::GetEventVar(args, EventVar::POKEID_ATK, nullptr) != pokeID) return;
    Common::RewriteEventVar(args, EventVar::FIX_DAMAGE_FLAG, true, nullptr);
    Common::RewriteEventVar(args, EventVar::FIX_DAMAGE,
                            Calc::RandRange(50, 150, nullptr) *
                            Common::GetPokeParam(args, pokeID, nullptr)->
                            GetValue(BTL_POKEPARAM_ValueID::BPP_LEVEL, nullptr) / 100,
                            nullptr);
}
// Nightmare
void HandlerNightmareAddsickCheckfail(EventFactor_EventHandlerArgs_o **args, uint8_t pokeID, MethodInfo *method) {
    if (Common::GetEventVar(args, EventVar::POKEID_ATK, nullptr) != pokeID) return;
    if (Common::GetEventVar(args, EventVar::SICKID, nullptr) != WazaSick::WAZASICK_AKUMU) return;
    BTL_POKEPARAM_o * bpp = Common::GetPokeParam(args,
                                                 Common::GetEventVar(args,
                                                                     EventVar::POKEID_DEF,
                                                                     nullptr),
                                                 nullptr);
    if (bpp->CheckNemuri(BTL_POKEPARAM_NemuriCheckMode::NEMURI_CHECK_ONLY_SICK, nullptr) &&
            !bpp->CheckSick(WazaSick::WAZASICK_AKUMU, nullptr)) return;
    Common::RewriteEventVar(args, EventVar::FAIL_FLAG, true, nullptr);
}
// Return
void HandlerReturnWazaPower(EventFactor_EventHandlerArgs_o **args, uint8_t pokeID, MethodInfo *method) {
    if (Common::GetEventVar(args, EventVar::POKEID_ATK, nullptr) != pokeID) return;
    Common::RewriteEventVar(args, EventVar::WAZA_POWER,
                            Common::GetPokeParam(args, pokeID, nullptr)->GetFriendship(nullptr) *
                            2 / 5,
                            nullptr);
}
// Frustration
void HandlerFrustrationWazaPower(EventFactor_EventHandlerArgs_o **args, uint8_t pokeID, MethodInfo *method) {
    if (Common::GetEventVar(args, EventVar::POKEID_ATK, nullptr) != pokeID) return;
    Common::RewriteEventVar(args, EventVar::WAZA_POWER,
                            (255 - Common::GetPokeParam(args, pokeID, nullptr)->
                            GetFriendship(nullptr)) * 2 / 5,
                            nullptr);
}
// Magnitude
void HandlerMagnitudeWazaPower(EventFactor_EventHandlerArgs_o **args, uint8_t pokeID, MethodInfo *method) {
    if (Common::GetEventVar(args, EventVar::POKEID_ATK, nullptr) != pokeID) return;
    uint32_t r = Calc::GetRand(20, nullptr);
    int32_t power = 0;
    if (r < 1) power = 10;
    else if (r < 3) power = 30;
    else if (r < 7) power = 50;
    else if (r < 13) power = 70;
    else if (r < 17) power = 90;
    else if (r < 19) power = 110;
    else if (r < 20) power = 150;
    Common::RewriteEventVar(args, EventVar::WAZA_POWER, power, nullptr);
}
void HandlerPursuitGetWazaPri(EventFactor_EventHandlerArgs_o **args, uint8_t pokeID, MethodInfo *method) {
    if (Common::GetEventVar(args, EventVar::POKEID_ATK, nullptr) != pokeID) return;
    HandlerMessage(args, pokeID, true);
}
//Baddy Bad
void HandlerBaddyBadWallEffect(EventFactor_EventHandlerArgs_o **args, uint8_t pokeID, MethodInfo *method) {
    if (Common::GetEventVar(args, EventVar::POKEID_ATK, nullptr) != pokeID) return;

    BTL_SICKCONT_o sickCont = SICKCONT::MakeTurnParam(pokeID, 5, 0, nullptr);
    int32_t side = Common::PokeIDtoSide(args, (uint8_t *) &pokeID, method);

    bool retVal = Handler::Waza_o::common_SideEffectCore(args, pokeID, side, 0, &sickCont, 1, EFFECT_REFLECT, side, true, nullptr);

    if (retVal)
    {
        Common::RewriteEventVar(args, EventVar::SUCCESS_FLAG, 1, nullptr);
    }
}
//Freezy Frost
void HandlerFreezyFrostHazeEffect(EventFactor_EventHandlerArgs_o **args, uint8_t pokeID, MethodInfo *method) {
    if (Common::GetEventVar(args, EventVar::POKEID_ATK, nullptr) != pokeID) return;

    //uint8_t uVar1 = Common::GetExistFrontPokePos(args, pokeID, nullptr);
    //ExPokePos_o* local_28 = (ExPokePos_o *) il2cpp_object_new(ExPokePos_TypeInfo);
    //local_28->ctor(9, uVar1, nullptr);

    //Section_FromEvent_RankReset_Description_o *local_38 = (Section_FromEvent_RankReset_Description_o *) il2cpp_object_new(Section_FromEvent_RankReset_Description_TypeInfo);
    //local_38->ctor(nullptr);

    //(local_38->fields).pokeCount = Common::ExpandExistPokeID(args,&local_28,(local_38->fields).pokeID,(MethodInfo *)0x0);
    //Common::RankReset(args, &local_38, nullptr);
    //Section_FromEvent_Message::Description_o * local_40 = (Section_FromEvent_Message::Description_o *) il2cpp_object_new(Section_FromEvent_Message::Description_TypeInfo);
    //local_40->ctor(nullptr);

    //(local_40->fields).message->Setup(1, 0x74, nullptr);
    //Common::Message(args, &local_40, nullptr);
    Common::RewriteEventVar(args, EventVar::SUCCESS_FLAG, 1, nullptr);
}
//Glitzy Glow
void HandlerGlitzyGlowWallEffect(EventFactor_EventHandlerArgs_o **args, uint8_t pokeID, MethodInfo *method) {
    if (Common::GetEventVar(args, EventVar::POKEID_ATK, nullptr) != pokeID) return;

    BTL_SICKCONT_o sickCont = SICKCONT::MakeTurnParam(pokeID, 5, 0, nullptr);
    int32_t side = Common::PokeIDtoSide(args, (uint8_t *) &pokeID, method);

    bool retVal = Handler::Waza_o::common_SideEffectCore(args, pokeID, side, 0, &sickCont, 1, EFFECT_LIGHT_SCREEN, side, true, nullptr);

    if (retVal)
    {
        Common::RewriteEventVar(args, EventVar::SUCCESS_FLAG, 1, nullptr);
    }
}
//Veevee Volley
void HandlerVeeveeVolleyWazaPower(EventFactor_EventHandlerArgs_o **args, uint8_t pokeID, MethodInfo *method) {
    if (Common::GetEventVar(args, EventVar::POKEID_ATK, nullptr) != pokeID) return;
    int32_t power = Common::GetPokeParam(args, pokeID, nullptr)->GetFriendship(nullptr) * 2 / 5;
    if (power < 1) power = 1;
    Common::RewriteEventVar(args, EventVar::WAZA_POWER, power, nullptr);
}

EventFactor_EventHandlerTable_o * CreateMoveEventHandler(uint16_t eventID, Il2CppMethodPointer methodPointer) {
    return CreateEventHandler(eventID, Handler_Karagenki_WazaPowMethodInfo, methodPointer);
}

// --- HandlerGetFunc delegates ---
System::Array<EventFactor_EventHandlerTable_o *> * ADD_JumpKick(MethodInfo *method) {
    if (sHandlerTableJumpKick == nullptr) {
        sHandlerTableJumpKick = (System::Array<EventFactor_EventHandlerTable_o *> *) system_array_new(EventFactor_EventHandlerTable_Array_TypeInfo, 1);
        sHandlerTableJumpKick->m_Items[0] = CreateMoveEventHandler(EventID::WAZA_EXECUTE_NO_EFFECT, (Il2CppMethodPointer) &Waza::handler_Tobigeri_NoEffect);
    }
    return sHandlerTableJumpKick;
}
System::Array<EventFactor_EventHandlerTable_o *> * ADD_SonicBoom(MethodInfo *method) {
    if (sHandlerTableSonicBoom == nullptr) {
        sHandlerTableSonicBoom = (System::Array<EventFactor_EventHandlerTable_o *> *) system_array_new(EventFactor_EventHandlerTable_Array_TypeInfo, 1);
        sHandlerTableSonicBoom->m_Items[0] = CreateMoveEventHandler(EventID::WAZA_DMG_PROC1, (Il2CppMethodPointer) &HandlerSonicBoomWazaDmgProc1);
    }
    return sHandlerTableSonicBoom;
}
System::Array<EventFactor_EventHandlerTable_o *> * ADD_DragonRage(MethodInfo *method) {
    if (sHandlerTableDragonRage == nullptr) {
        sHandlerTableDragonRage = (System::Array<EventFactor_EventHandlerTable_o *> *) system_array_new(EventFactor_EventHandlerTable_Array_TypeInfo, 1);
        sHandlerTableDragonRage->m_Items[0] = CreateMoveEventHandler(EventID::WAZA_DMG_PROC1, (Il2CppMethodPointer) &HandlerDragonRageWazaDmgProc1);
    }
    return sHandlerTableDragonRage;
}
System::Array<EventFactor_EventHandlerTable_o *> * ADD_Rage(MethodInfo *method) {
    if (sHandlerTableRage == nullptr) {
        sHandlerTableRage = (System::Array<EventFactor_EventHandlerTable_o *> *) system_array_new(EventFactor_EventHandlerTable_Array_TypeInfo, 4);
        sHandlerTableRage->m_Items[0] = CreateMoveEventHandler(EventID::WAZA_CALL_DECIDE, (Il2CppMethodPointer) &HandlerRageWazaCallDecide);
        sHandlerTableRage->m_Items[1] = CreateMoveEventHandler(EventID::WAZA_EXECUTE_EFFECTIVE, (Il2CppMethodPointer) &HandlerRageWazaExecuteEffective);
        sHandlerTableRage->m_Items[2] = CreateMoveEventHandler(EventID::WAZA_DMG_REACTION, (Il2CppMethodPointer) &HandlerRageWazaDmgReaction);
        sHandlerTableRage->m_Items[3] = CreateMoveEventHandler(EventID::MEMBER_OUT_FIXED, (Il2CppMethodPointer) &HandlerRageMemberOutFixed);
    }
    return sHandlerTableRage;
}
System::Array<EventFactor_EventHandlerTable_o *> * ADD_Bide(MethodInfo *method) {
    if (sHandlerTableBide == nullptr) {
        sHandlerTableBide = (System::Array<EventFactor_EventHandlerTable_o *> *) system_array_new(EventFactor_EventHandlerTable_Array_TypeInfo, 7);
        sHandlerTableBide->m_Items[0] = CreateMoveEventHandler(EventID::CHECK_DELAY_WAZA, (Il2CppMethodPointer) &HandlerBideCheckDelayWaza);
        sHandlerTableBide->m_Items[1] = CreateMoveEventHandler(EventID::WAZA_EXECUTE_CHECK_3RD, (Il2CppMethodPointer) &HandlerBideWazaExecuteCheck3rd);
        sHandlerTableBide->m_Items[2] = CreateMoveEventHandler(EventID::WAZA_CALL_DECIDE, (Il2CppMethodPointer) &HandlerBideWazaCallDecide);
        sHandlerTableBide->m_Items[3] = CreateMoveEventHandler(EventID::DECIDE_TARGET, (Il2CppMethodPointer) &HandlerBideDecideTarget);
        sHandlerTableBide->m_Items[4] = CreateMoveEventHandler(EventID::WAZA_DMG_PROC1, (Il2CppMethodPointer) &HandlerBideWazaDmgProc1);
        sHandlerTableBide->m_Items[5] = CreateMoveEventHandler(EventID::WAZA_DMG_REACTION, (Il2CppMethodPointer) &HandlerBideWazaDmgReaction);
        sHandlerTableBide->m_Items[6] = CreateMoveEventHandler(EventID::TURNCHECK_END, (Il2CppMethodPointer) &HandlerBideTurncheckEnd);
    }
    return sHandlerTableBide;
}
System::Array<EventFactor_EventHandlerTable_o *> * ADD_MirrorMove(MethodInfo *method) {
    if (sHandlerTableMirrorMove == nullptr) {
        sHandlerTableMirrorMove = (System::Array<EventFactor_EventHandlerTable_o *> *) system_array_new(EventFactor_EventHandlerTable_Array_TypeInfo, 1);
        sHandlerTableMirrorMove->m_Items[0] = CreateMoveEventHandler(EventID::REQWAZA_PARAM, (Il2CppMethodPointer) &HandlerMirrorMoveReqwazaParam);
    }
    return sHandlerTableMirrorMove;
}
System::Array<EventFactor_EventHandlerTable_o *> * ADD_Psywave(MethodInfo *method) {
    if (sHandlerTablePsywave == nullptr) {
        sHandlerTablePsywave = (System::Array<EventFactor_EventHandlerTable_o *> *) system_array_new(EventFactor_EventHandlerTable_Array_TypeInfo, 1);
        sHandlerTablePsywave->m_Items[0] = CreateMoveEventHandler(EventID::WAZA_DMG_PROC1, (Il2CppMethodPointer) &HandlerPsywaveWazaDmgProc1);
    }
    return sHandlerTablePsywave;
}
System::Array<EventFactor_EventHandlerTable_o *> * ADD_Nightmare(MethodInfo *method) {
    if (sHandlerTableNightmare == nullptr) {
        sHandlerTableNightmare = (System::Array<EventFactor_EventHandlerTable_o *> *) system_array_new(EventFactor_EventHandlerTable_Array_TypeInfo, 1);
        sHandlerTableNightmare->m_Items[0] = CreateMoveEventHandler(EventID::ADDSICK_CHECKFAIL, (Il2CppMethodPointer) &HandlerNightmareAddsickCheckfail);
    }
    return sHandlerTableNightmare;
}
System::Array<EventFactor_EventHandlerTable_o *> * ADD_Return(MethodInfo *method) {
    if (sHandlerTableReturn == nullptr) {
        sHandlerTableReturn = (System::Array<EventFactor_EventHandlerTable_o *> *) system_array_new(EventFactor_EventHandlerTable_Array_TypeInfo, 1);
        sHandlerTableReturn->m_Items[0] = CreateMoveEventHandler(EventID::WAZA_POWER, (Il2CppMethodPointer) &HandlerReturnWazaPower);
    }
    return sHandlerTableReturn;
}
System::Array<EventFactor_EventHandlerTable_o *> * ADD_Frustration(MethodInfo *method) {
    if (sHandlerTableFrustration == nullptr) {
        sHandlerTableFrustration = (System::Array<EventFactor_EventHandlerTable_o *> *) system_array_new(EventFactor_EventHandlerTable_Array_TypeInfo, 1);
        sHandlerTableFrustration->m_Items[0] = CreateMoveEventHandler(EventID::WAZA_POWER, (Il2CppMethodPointer) &HandlerFrustrationWazaPower);
    }
    return sHandlerTableFrustration;
}
System::Array<EventFactor_EventHandlerTable_o *> * ADD_Magnitude(MethodInfo *method) {
    if (sHandlerTableMagnitude == nullptr) {
        sHandlerTableMagnitude = (System::Array<EventFactor_EventHandlerTable_o *> *) system_array_new(EventFactor_EventHandlerTable_Array_TypeInfo, 3);
        sHandlerTableMagnitude->m_Items[0] = CreateMoveEventHandler(EventID::WAZA_POWER, (Il2CppMethodPointer) &HandlerMagnitudeWazaPower);
        sHandlerTableMagnitude->m_Items[1] = CreateMoveEventHandler(EventID::WAZA_DMG_PROC3, (Il2CppMethodPointer) &Waza::handler_Jisin_damage);
        sHandlerTableMagnitude->m_Items[2] = CreateMoveEventHandler(EventID::CHECK_POKE_HIDE, (Il2CppMethodPointer) &Waza::handler_Jisin_checkHide);
    }
    return sHandlerTableMagnitude;
}
System::Array<EventFactor_EventHandlerTable_o *> * ADD_Pursuit(MethodInfo *method) {
    if (sHandlerTablePursuit == nullptr) {
        sHandlerTablePursuit = (System::Array<EventFactor_EventHandlerTable_o *> *) system_array_new(EventFactor_EventHandlerTable_Array_TypeInfo, 1);
        sHandlerTablePursuit->m_Items[0] = CreateMoveEventHandler(EventID::GET_WAZA_PRI, (Il2CppMethodPointer) &HandlerPursuitGetWazaPri);
    }
    return sHandlerTablePursuit;
}
System::Array<EventFactor_EventHandlerTable_o *> * ADD_GlitzyGlow(MethodInfo *method) {
    if (sHandlerTableGlitzyGlow == nullptr) {
        sHandlerTableGlitzyGlow = (System::Array<EventFactor_EventHandlerTable_o *> *) system_array_new(EventFactor_EventHandlerTable_Array_TypeInfo, 1);
        sHandlerTableGlitzyGlow->m_Items[0] = CreateMoveEventHandler(EventID::ADD_SICK, (Il2CppMethodPointer) &HandlerGlitzyGlowWallEffect);
    }
    return sHandlerTableGlitzyGlow;
}
System::Array<EventFactor_EventHandlerTable_o *> * ADD_BaddyBad(MethodInfo *method) {
    if (sHandlerTableBaddyBad == nullptr) {
        sHandlerTableBaddyBad = (System::Array<EventFactor_EventHandlerTable_o *> *) system_array_new(EventFactor_EventHandlerTable_Array_TypeInfo, 1);
        sHandlerTableBaddyBad->m_Items[0] = CreateMoveEventHandler(EventID::ADD_SICK, (Il2CppMethodPointer) &HandlerBaddyBadWallEffect);
    }
    return sHandlerTableBaddyBad;
}
System::Array<EventFactor_EventHandlerTable_o *> * ADD_FreezyFrost(MethodInfo *method) {
    if (sHandlerTableFreezyFrost == nullptr) {
        sHandlerTableFreezyFrost = (System::Array<EventFactor_EventHandlerTable_o *> *) system_array_new(EventFactor_EventHandlerTable_Array_TypeInfo, 1);
        sHandlerTableFreezyFrost->m_Items[0] = CreateMoveEventHandler(EventID::ADD_SICK, (Il2CppMethodPointer) &HandlerFreezyFrostHazeEffect);
    }
    return sHandlerTableFreezyFrost;
}
System::Array<EventFactor_EventHandlerTable_o *> * ADD_VeeveeVolley(MethodInfo *method) {
    if (sHandlerTableVeeveeVolley == nullptr) {
        sHandlerTableVeeveeVolley = (System::Array<EventFactor_EventHandlerTable_o *> *) system_array_new(EventFactor_EventHandlerTable_Array_TypeInfo, 1);
        sHandlerTableVeeveeVolley->m_Items[0] = CreateMoveEventHandler(EventID::WAZA_POWER, (Il2CppMethodPointer) &HandlerVeeveeVolleyWazaPower);
    }
    return sHandlerTableVeeveeVolley;
}

//Adds an additional entry to GET_FUNC_TABLE
void SetMoveFunctionTable(System::Array<Waza_GET_FUNC_TABLE_ELEM_o> * getFuncTable, uint32_t * idx, int32_t wazaNo, Il2CppMethodPointer methodPointer) {
    MethodInfo * method = copyMethodInfo(Method_ADD_Karagenki, methodPointer);
    Waza_GET_FUNC_TABLE_ELEM_o * elem = &getFuncTable->m_Items[*idx];
    Waza_HandlerGetFunc_o * func = (Waza_HandlerGetFunc_o *) il2cpp_object_new(Waza_HandlerGetFunc_TypeInfo);
    func->ctor((intptr_t)methodPointer, method);
    elem->fields.waza = wazaNo;
    elem->fields.func = func;
    *idx += 1;
}

// Remember to update when adding handlers
constexpr uint32_t NEW_MOVES_COUNT = 14;

//Entry point. Replaces system_array_new.
void * Waza_system_array_new(void * typeInfo, uint32_t len) {
    System::Array<Waza_GET_FUNC_TABLE_ELEM_o> * getFuncTable = (System::Array<Waza_GET_FUNC_TABLE_ELEM_o> *) system_array_new(typeInfo, len + NEW_MOVES_COUNT);
    uint32_t idx = len;

    //0
    SetMoveFunctionTable(getFuncTable, &idx, JUMP_KICK, (Il2CppMethodPointer) &ADD_JumpKick);
    SetMoveFunctionTable(getFuncTable, &idx, SONIC_BOOM, (Il2CppMethodPointer) &ADD_SonicBoom);
    SetMoveFunctionTable(getFuncTable, &idx, DRAGON_RAGE, (Il2CppMethodPointer) &ADD_DragonRage);
    SetMoveFunctionTable(getFuncTable, &idx, RAGE, (Il2CppMethodPointer) &ADD_Rage);
    SetMoveFunctionTable(getFuncTable, &idx, BIDE, (Il2CppMethodPointer) &ADD_Bide);
    SetMoveFunctionTable(getFuncTable, &idx, MIRROR_MOVE, (Il2CppMethodPointer) &ADD_MirrorMove);
    SetMoveFunctionTable(getFuncTable, &idx, PSYWAVE, (Il2CppMethodPointer) &ADD_Psywave);
    SetMoveFunctionTable(getFuncTable, &idx, SPIDER_WEB, (Il2CppMethodPointer) &Waza::ADD_KumoNoSu);
    SetMoveFunctionTable(getFuncTable, &idx, NIGHTMARE, (Il2CppMethodPointer) &ADD_Nightmare);
    SetMoveFunctionTable(getFuncTable, &idx, RETURN, (Il2CppMethodPointer) &ADD_Return);
    //10
    SetMoveFunctionTable(getFuncTable, &idx, FRUSTRATION, (Il2CppMethodPointer) &ADD_Frustration);
    SetMoveFunctionTable(getFuncTable, &idx, MAGNITUDE, (Il2CppMethodPointer) &ADD_Magnitude);
    SetMoveFunctionTable(getFuncTable, &idx, PURSUIT, (Il2CppMethodPointer) &ADD_Pursuit);
    //SetMoveFunctionTable(getFuncTable, &idx, GLITZY_GLOW, (Il2CppMethodPointer) &ADD_GlitzyGlow);
    //SetMoveFunctionTable(getFuncTable, &idx, BADDY_BAD, (Il2CppMethodPointer) &ADD_BaddyBad);
    //SetMoveFunctionTable(getFuncTable, &idx, FREEZY_FROST, (Il2CppMethodPointer) &ADD_FreezyFrost);
    SetMoveFunctionTable(getFuncTable, &idx, VEEVEE_VOLLEY, (Il2CppMethodPointer) &ADD_VeeveeVolley);

    return getFuncTable;
}
