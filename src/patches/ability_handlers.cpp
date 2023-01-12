#include "Dpr/Battle/Logic/BtlSpecialPri.hpp"
#include "Dpr/Battle/Logic/BtlWeather.hpp"
#include "Dpr/Battle/Logic/Calc.hpp"
#include "Dpr/Battle/Logic/Common.hpp"
#include "Dpr/Battle/Logic/DamageCause.hpp"
#include "Dpr/Battle/Logic/DmgAffRec.hpp"
#include "Dpr/Battle/Logic/EventFactor.hpp"
#include "Dpr/Battle/Logic/EventID.hpp"
#include "Dpr/Battle/Logic/EventVar.hpp"
#include "Dpr/Battle/Logic/Handler.hpp"
#include "Dpr/Battle/Logic/Handler/Tokusei.hpp"
#include "Dpr/Battle/Logic/PokeSet.hpp"
#include "Dpr/Battle/Logic/Section.hpp"
#include "Dpr/Battle/Logic/Section_CheckNotEffect_Guard.hpp"
#include "Dpr/Battle/Logic/Section_FromEvent_Damage.hpp"
#include "Dpr/Battle/Logic/WAZADATA.hpp"
#include "Dpr/Battle/Logic/WazaParam.hpp"
#include "Pml/Personal/ParamID.hpp"
#include "Pml/Personal/PersonalTableExtensions.hpp"
#include "Pml/Personal/PersonalSystem.hpp"
#include "Pml/PokePara/Accessor.h"
#include "Pml/PokePara/CoreParam.h"
#include "Pml/PokePara/Sick.hpp"
#include "Pml/WazaData/WazaDamageType.hpp"
#include "Pml/WazaData/WazaFlag.hpp"
#include "Pml/WazaData/WazaRankEffect.hpp"
#include "Pml/WazaData/WazaSick.hpp"

#include "il2cpp-api.h"
#include "il2cpp.hpp"
#include "System/Array.hpp"
#include "util.hpp"

using namespace Dpr::Battle::Logic;
using namespace Dpr::Battle::Logic::Handler;
using namespace Pml::Personal;
using namespace Pml::PokePara;
using namespace Pml::WazaData;

// Template MethodInfo
extern MethodInfo * Method_handler_TetunoKobusi;

// WorkIdx
constexpr uint8_t A = 0;
constexpr uint8_t B = 1;
constexpr uint8_t C = 2;
constexpr uint8_t D = 3;
constexpr uint8_t PERSIST = 4;

// AbilityIDs
constexpr uint32_t FORECAST = 59;
constexpr uint32_t MULTITYPE = 121;
constexpr uint32_t FLOWER_GIFT = 122;
constexpr uint32_t ZEN_MODE = 161;
constexpr uint32_t STANCE_CHANGE = 176;
constexpr uint32_t SHIELDS_DOWN = 197;
constexpr uint32_t SCHOOLING = 208;
constexpr uint32_t DISGUISE = 209;
constexpr uint32_t BATTLE_BOND = 210;
constexpr uint32_t POWER_CONSTRUCT = 211;
constexpr uint32_t RKS_SYSTEM = 225;
constexpr uint32_t GULP_MISSILE = 241;
constexpr uint32_t ICE_FACE = 248;
constexpr uint32_t HUNGER_SWITCH = 258;
constexpr uint32_t QUICK_DRAW = 259;
constexpr uint32_t UNSEEN_FIST = 260;
constexpr uint32_t CURIOUS_MEDICINE = 261;
constexpr uint32_t TRANSISTOR = 262;
constexpr uint32_t DRAGONS_MAW = 263;
constexpr uint32_t CHILLING_NEIGH = 264;
constexpr uint32_t GRIM_NEIGH = 265;
constexpr uint32_t AS_ONE0 = 266;
constexpr uint32_t AS_ONE1 = 267;

// MoveIDs
constexpr uint32_t SURF = 57;
constexpr uint32_t DIVE = 291;
constexpr uint32_t KINGS_SHIELD = 588;
constexpr uint32_t WATER_SHURIKEN = 594;

// ItemIDs
constexpr uint32_t FLAME_PLATE = 298;
constexpr uint32_t SPLASH_PLATE = 299;
constexpr uint32_t ZAP_PLATE = 300;
constexpr uint32_t MEADOW_PLATE = 301;
constexpr uint32_t ICICLE_PLATE = 302;
constexpr uint32_t FIST_PLATE = 303;
constexpr uint32_t TOXIC_PLATE = 304;
constexpr uint32_t EARTH_PLATE = 305;
constexpr uint32_t SKY_PLATE = 306;
constexpr uint32_t MIND_PLATE = 307;
constexpr uint32_t INSECT_PLATE = 308;
constexpr uint32_t STONE_PLATE = 309;
constexpr uint32_t SPOOKY_PLATE = 310;
constexpr uint32_t DRACO_PLATE = 311;
constexpr uint32_t DREAD_PLATE = 312;
constexpr uint32_t IRON_PLATE = 313;
constexpr uint32_t PIXIE_PLATE = 644;
constexpr uint32_t FIRIUM_Z = 777;
constexpr uint32_t WATERIUM_Z = 778;
constexpr uint32_t ELECTRIUM_Z = 779;
constexpr uint32_t GRASSIUM_Z = 780;
constexpr uint32_t ICIUM_Z = 781;
constexpr uint32_t FIGHTINIUM_Z = 782;
constexpr uint32_t POISONIUM_Z = 783;
constexpr uint32_t GROUNDIUM_Z = 784;
constexpr uint32_t FLYINIUM_Z = 785;
constexpr uint32_t PSYCHIUM_Z = 786;
constexpr uint32_t BUGINIUM_Z = 787;
constexpr uint32_t ROCKIUM_Z = 788;
constexpr uint32_t GHOSTIUM_Z = 789;
constexpr uint32_t DRAGONIUM_Z = 790;
constexpr uint32_t DARKINIUM_Z = 791;
constexpr uint32_t STEELIUM_Z = 792;
constexpr uint32_t FAIRIUM_Z = 793;
constexpr uint32_t FIGHTING_MEMORY = 904;
constexpr uint32_t FLYING_MEMORY = 905;
constexpr uint32_t POISON_MEMORY = 906;
constexpr uint32_t GROUND_MEMORY = 907;
constexpr uint32_t ROCK_MEMORY = 908;
constexpr uint32_t BUG_MEMORY = 909;
constexpr uint32_t GHOST_MEMORY = 910;
constexpr uint32_t STEEL_MEMORY = 911;
constexpr uint32_t FIRE_MEMORY = 912;
constexpr uint32_t WATER_MEMORY = 913;
constexpr uint32_t GRASS_MEMORY = 914;
constexpr uint32_t ELECTRIC_MEMORY = 915;
constexpr uint32_t PSYCHIC_MEMORY = 916;
constexpr uint32_t ICE_MEMORY = 917;
constexpr uint32_t DRAGON_MEMORY = 918;
constexpr uint32_t DARK_MEMORY = 919;
constexpr uint32_t FAIRY_MEMORY = 920;

// TypeIDs
constexpr uint32_t NORMAL = 0;
constexpr uint32_t FIGHTING = 1;
constexpr uint32_t FLYING = 2;
constexpr uint32_t POISON = 3;
constexpr uint32_t GROUND = 4;
constexpr uint32_t ROCK = 5;
constexpr uint32_t BUG = 6;
constexpr uint32_t GHOST = 7;
constexpr uint32_t STEEL = 8;
constexpr uint32_t FIRE = 9;
constexpr uint32_t WATER = 10;
constexpr uint32_t GRASS = 11;
constexpr uint32_t ELECTRIC = 12;
constexpr uint32_t PSYCHIC = 13;
constexpr uint32_t ICE = 14;
constexpr uint32_t DRAGON = 15;
constexpr uint32_t DARK = 16;
constexpr uint32_t FAIRY = 17;

// Remember to update when adding handlers
const uint32_t NEW_ABILITIES_COUNT = 18;

// HandlerTables
static System::Array<EventFactor_EventHandlerTable_o *> * sHandlerTableZenMode;//0
static System::Array<EventFactor_EventHandlerTable_o *> * sHandlerTableStanceChange;
static System::Array<EventFactor_EventHandlerTable_o *> * sHandlerTableShieldsDown;
static System::Array<EventFactor_EventHandlerTable_o *> * sHandlerTableSchooling;
static System::Array<EventFactor_EventHandlerTable_o *> * sHandlerTableDisguise;
static System::Array<EventFactor_EventHandlerTable_o *> * sHandlerTableBattleBond;
static System::Array<EventFactor_EventHandlerTable_o *> * sHandlerTablePowerConstruct;
static System::Array<EventFactor_EventHandlerTable_o *> * sHandlerTableGulpMissile;
static System::Array<EventFactor_EventHandlerTable_o *> * sHandlerTableIceFace;
static System::Array<EventFactor_EventHandlerTable_o *> * sHandlerTableHungerSwitch;
static System::Array<EventFactor_EventHandlerTable_o *> * sHandlerTableQuickDraw;//10
static System::Array<EventFactor_EventHandlerTable_o *> * sHandlerTableCuriousMedicine;
static System::Array<EventFactor_EventHandlerTable_o *> * sHandlerTableTransistor;
static System::Array<EventFactor_EventHandlerTable_o *> * sHandlerTableDragonsMaw;
static System::Array<EventFactor_EventHandlerTable_o *> * sHandlerTableChillingNeigh;
static System::Array<EventFactor_EventHandlerTable_o *> * sHandlerTableGrimNeigh;
static System::Array<EventFactor_EventHandlerTable_o *> * sHandlerTableAsOne0;
static System::Array<EventFactor_EventHandlerTable_o *> * sHandlerTableAsOne1;

// --- EventHandler delegates ---
uint8_t MultitypeType(uint32_t itemNo) {
    switch (itemNo) {
        case FIST_PLATE:
        case FIGHTINIUM_Z:
            return FIGHTING;
        case SKY_PLATE:
        case FLYINIUM_Z:
            return FLYING;
        case TOXIC_PLATE:
        case POISONIUM_Z:
            return POISON;
        case EARTH_PLATE:
        case GROUNDIUM_Z:
            return GROUND;
        case STONE_PLATE:
        case ROCKIUM_Z:
            return ROCK;
        case INSECT_PLATE:
        case BUGINIUM_Z:
            return BUG;
        case SPOOKY_PLATE:
        case GHOSTIUM_Z:
            return GHOST;
        case IRON_PLATE:
        case STEELIUM_Z:
            return STEEL;
        case FLAME_PLATE:
        case FIRIUM_Z:
            return FIRE;
        case SPLASH_PLATE:
        case WATERIUM_Z:
            return WATER;
        case MEADOW_PLATE:
        case GRASSIUM_Z:
            return GRASS;
        case ZAP_PLATE:
        case ELECTRIUM_Z:
            return ELECTRIC;
        case MIND_PLATE:
        case PSYCHIUM_Z:
            return PSYCHIC;
        case ICICLE_PLATE:
        case ICIUM_Z:
            return ICE;
        case DRACO_PLATE:
        case DRAGONIUM_Z:
            return DRAGON;
        case DREAD_PLATE:
        case DARKINIUM_Z:
            return DARK;
        case PIXIE_PLATE:
        case FAIRIUM_Z:
            return FAIRY;
        default:
            return NORMAL;
    }
}
uint8_t RKSSystemType(uint32_t itemNo) {
    switch (itemNo) {
        case FIGHTING_MEMORY:
            return FIGHTING;
        case FLYING_MEMORY:
            return FLYING;
        case POISON_MEMORY:
            return POISON;
        case GROUND_MEMORY:
            return GROUND;
        case ROCK_MEMORY:
            return ROCK;
        case BUG_MEMORY:
            return BUG;
        case GHOST_MEMORY:
            return GHOST;
        case STEEL_MEMORY:
            return STEEL;
        case FIRE_MEMORY:
            return FIRE;
        case WATER_MEMORY:
            return WATER;
        case GRASS_MEMORY:
            return GRASS;
        case ELECTRIC_MEMORY:
            return ELECTRIC;
        case PSYCHIC_MEMORY:
            return PSYCHIC;
        case ICE_MEMORY:
            return ICE;
        case DRAGON_MEMORY:
            return DRAGON;
        case DARK_MEMORY:
            return DARK;
        case FAIRY_MEMORY:
            return FAIRY;
        default:
            return NORMAL;
    }
}
uint8_t GetType(CoreParam *cp, int32_t paramID) {
    Accessor *a = cp->fields.m_accessor;
    int32_t tokuseiNo = a->GetTokuseiNo(nullptr);
    uint32_t itemNo = a->GetItemNo(nullptr);
    if (tokuseiNo == MULTITYPE)
        return MultitypeType(itemNo);
    if (tokuseiNo == RKS_SYSTEM)
        return RKSSystemType(itemNo);
    return PersonalTableExtensions::GetParam(
            PersonalSystem::GetPersonalData(a->GetMonsNo(nullptr),
                                            a->GetFormNo(nullptr),
                                            nullptr),
            paramID,
            nullptr);
}
uint8_t Pml_PokePara_CoreParam_GetType1(CoreParam *cp, MethodInfo *method) {
    return GetType(cp, ParamID::TYPE1);
}
uint8_t Pml_PokePara_CoreParam_GetType2(CoreParam *cp, MethodInfo *method) {
    return GetType(cp, ParamID::TYPE2);
}
void Dpr_Battle_Logic_Section_CheckNotEffect_Guard_check_Mamoru(Section_CheckNotEffect_Guard_o *__this,
                                                                BTL_POKEPARAM_o *attacker, WazaParam_o *wazaParam,
                                                                DmgAffRec_o *affinityRecorder, PokeSet_o *targets,
                                                                MethodInfo *method) {
    int32_t wazaID = wazaParam->fields.wazaID;
    bool affectedByProtect = WAZADATA::GetFlag(wazaID, WazaFlag::MAMORU, nullptr) &&
            !(WAZADATA::GetFlag(wazaID, WazaFlag::TOUCH, nullptr) &&
            attacker->IsMatchTokusei(UNSEEN_FIST, nullptr));
    if (!affectedByProtect) return;
    targets->SeekStart(nullptr);
    BTL_POKEPARAM_o *defender = targets->SeekNext(nullptr);
    while (defender != nullptr) {
        bool protectTurnFlag = defender->TURNFLAG_Get(BTL_POKEPARAM_TurnFlag::TURNFLG_MAMORU,
                                                      nullptr);
        if ((!protectTurnFlag &&
        !__this->isNoEffectByMamoru_Others(attacker, defender, wazaParam, affinityRecorder, method)) ||
        (protectTurnFlag &&
        defender->TURNFLAG_Get(BTL_POKEPARAM_TurnFlag::TURNFLG_MAMORU_ONLY_DAMAGE_WAZA, nullptr) &&
        !WAZADATA::IsDamage(wazaID, nullptr))) {
            defender = targets->SeekNext(nullptr);
            continue;
        }
        bool messageDisplay = wazaParam->canInvalidMessageDisplay(targets->fields.m_count, nullptr);
        targets->Remove(defender, nullptr);
        if (!((Section_o *)__this)->GetActionSharedData(nullptr)->fields.isWazaFailMessageDisplayed &&
        messageDisplay) {
            __this->onMamoruSuccess(attacker, defender, wazaParam, nullptr);
        }
        ((Section_o *)__this)->GetActionSharedData(nullptr)->fields.isWazaFailMessageDisplayed = false;
        defender = targets->SeekNext(nullptr);
    }
}
// Forecast
uint8_t HandlerForecastGetFormID(EventFactor_EventHandlerArgs_o **args, uint8_t pokeID) {
    uint8_t formID = HighestMultiple(Common::GetPokeParam(args, pokeID, nullptr)->fields.m_formNo, 4);
    switch (Common::GetLocalWeather(args, pokeID, nullptr)) {
        case BtlWeather::BTL_WEATHER_SHINE:
        case BtlWeather::BTL_WEATHER_DAY:
            return formID + 1;
        case BtlWeather::BTL_WEATHER_RAIN:
        case BtlWeather::BTL_WEATHER_STORM:
            return formID + 2;
        case BtlWeather::BTL_WEATHER_SNOW:
            return formID + 3;
        default:
            return formID;
    }
}
uint8_t HandlerForecastGetFormID0(EventFactor_EventHandlerArgs_o **args, uint8_t pokeID) {
    return HighestMultiple(Common::GetPokeParam(args, pokeID, nullptr)->fields.m_formNo, 4);
}
void HandlerForecastAtkprocEnd(EventFactor_EventHandlerArgs_o **args, uint8_t pokeID, MethodInfo *method) {
    if (!Common::GetWorkValue(args, A, nullptr)) return;
    BTL_POKEPARAM_o * bpp = Common::GetPokeParam(args,pokeID, nullptr);
    //if (bpp->HENSIN_Check(nullptr)) return;
    uint8_t nextForm = HandlerForecastGetFormID(args, pokeID);
    if (nextForm >= PersonalSystem::GetPersonalData(bpp->GetMonsNo(nullptr), 0,
                                                    nullptr)->fields.form_max) return;
    HandlerFormChange(args, pokeID, nextForm, false, true, true);
}
void HandlerForecastMemberInComp(EventFactor_EventHandlerArgs_o **args, uint8_t pokeID, MethodInfo *method) {
    BTL_POKEPARAM_o * bpp = Common::GetPokeParam(args,pokeID, nullptr);
    //if (bpp->HENSIN_Check(nullptr)) return;
    uint8_t nextForm = HandlerForecastGetFormID(args, pokeID);
    Common::SetWorkValue(args, A, true, nullptr);
    if (nextForm >= PersonalSystem::GetPersonalData(bpp->GetMonsNo(nullptr), 0,
                                                    nullptr)->fields.form_max) return;
    HandlerFormChange(args, pokeID, nextForm, false, true, true);
}
void HandlerForecastTokuseiDisable(EventFactor_EventHandlerArgs_o **args, uint8_t pokeID, MethodInfo *method) {
    if (Common::GetEventVar(args, EventVar::POKEID, nullptr) != pokeID) return;
    //if (bpp->HENSIN_Check(nullptr)) return;
    HandlerFormChange(args, pokeID, HandlerForecastGetFormID0(args, pokeID), false,
                      false, true);
}
void HandlerForecastNotifyAirlock(EventFactor_EventHandlerArgs_o **args, uint8_t pokeID, MethodInfo *method) {
    if (!Common::GetWorkValue(args, A, nullptr)) return;
    //if (bpp->HENSIN_Check(nullptr)) return;
    HandlerFormChange(args, pokeID, HandlerForecastGetFormID0(args, pokeID), false,
                      false, true);
}
void HandlerForecastChangeTokuseiBefore(EventFactor_EventHandlerArgs_o **args, uint8_t pokeID, MethodInfo *method) {
    if (Common::GetEventVar(args, EventVar::POKEID, nullptr) != pokeID) return;
    if (Common::GetEventVar(args, EventVar::TOKUSEI_NEXT, nullptr) ==
    Common::GetSubID(args, nullptr)) return;
    //if (bpp->HENSIN_Check(nullptr)) return;
    HandlerFormChange(args, pokeID, HandlerForecastGetFormID0(args, pokeID), false,
                      false, true);
}
void HandlerForecastChangeTokuseiAfter(EventFactor_EventHandlerArgs_o **args, uint8_t pokeID, MethodInfo *method) {
    if (Common::GetEventVar(args, EventVar::POKEID, nullptr) != pokeID) return;
    HandlerForecastMemberInComp(args, pokeID, method);
}
// Flower Gift
uint8_t HandlerFlowerGiftGetFormID(EventFactor_EventHandlerArgs_o **args, uint8_t pokeID) {
    uint8_t weather = Common::GetLocalWeather(args, pokeID, nullptr);
    return HighestMultiple(Common::GetPokeParam(args, pokeID, nullptr)->fields.m_formNo, 2) +
    (weather == BtlWeather::BTL_WEATHER_SHINE || weather == BtlWeather::BTL_WEATHER_DAY);
}
uint8_t HandlerFlowerGiftGetFormID0(EventFactor_EventHandlerArgs_o **args, uint8_t pokeID) {
    return HighestMultiple(Common::GetPokeParam(args, pokeID, nullptr)->fields.m_formNo, 2);
}
void HandlerFlowerGiftAtkprocEnd(EventFactor_EventHandlerArgs_o **args, uint8_t pokeID, MethodInfo *method) {
    if (!Common::GetWorkValue(args, A, nullptr)) return;
    BTL_POKEPARAM_o * bpp = Common::GetPokeParam(args,pokeID, nullptr);
    //if (bpp->HENSIN_Check(nullptr)) return;
    uint8_t nextForm = HandlerFlowerGiftGetFormID(args, pokeID);
    if (nextForm >= PersonalSystem::GetPersonalData(bpp->GetMonsNo(nullptr), 0,
                                                    nullptr)->fields.form_max) return;
    HandlerFormChange(args, pokeID, nextForm, false, true, true);
}
void HandlerFlowerGiftMemberInComp(EventFactor_EventHandlerArgs_o **args, uint8_t pokeID, MethodInfo *method) {
    BTL_POKEPARAM_o * bpp = Common::GetPokeParam(args,pokeID, nullptr);
    //if (bpp->HENSIN_Check(nullptr)) return;
    uint8_t nextForm = HandlerFlowerGiftGetFormID(args, pokeID);
    Common::SetWorkValue(args, A, true, nullptr);
    if (nextForm >= PersonalSystem::GetPersonalData(bpp->GetMonsNo(nullptr), 0,
                                                    nullptr)->fields.form_max) return;
    HandlerFormChange(args, pokeID, nextForm, false, true, true);
}
void HandlerFlowerGiftTokuseiDisable(EventFactor_EventHandlerArgs_o **args, uint8_t pokeID, MethodInfo *method) {
    if (!Common::GetWorkValue(args, A, nullptr)) return;
    if (Common::GetEventVar(args, EventVar::POKEID, nullptr) != pokeID) return;
    //if (bpp->HENSIN_Check(nullptr)) return;
    HandlerFormChange(args, pokeID, HandlerFlowerGiftGetFormID0(args, pokeID), false,
                      false, true);
}
void HandlerFlowerGiftNotifyAirlock(EventFactor_EventHandlerArgs_o **args, uint8_t pokeID, MethodInfo *method) {
    if (!Common::GetWorkValue(args, A, nullptr)) return;
    //if (bpp->HENSIN_Check(nullptr)) return;
    HandlerFormChange(args, pokeID, HandlerFlowerGiftGetFormID0(args, pokeID), false,
                      false, true);
}
void HandlerFlowerGiftChangeTokuseiBefore(EventFactor_EventHandlerArgs_o **args, uint8_t pokeID, MethodInfo *method) {
    if (!Common::GetWorkValue(args, A, nullptr)) return;
    //if (bpp->HENSIN_Check(nullptr)) return;
    if (Common::GetEventVar(args, EventVar::POKEID, nullptr) != pokeID) return;
    if (Common::GetEventVar(args, EventVar::TOKUSEI_NEXT, nullptr) ==
        Common::GetSubID(args, nullptr)) return;
    HandlerFormChange(args, pokeID, HandlerFlowerGiftGetFormID0(args, pokeID), false,
                      false, true);
}
void HandlerFlowerGiftChangeTokuseiAfter(EventFactor_EventHandlerArgs_o **args, uint8_t pokeID, MethodInfo *method) {
    if (Common::GetEventVar(args, EventVar::POKEID, nullptr) != pokeID) return;
    HandlerForecastMemberInComp(args, pokeID, method);
}
// Zen Mode
uint8_t HandlerZenModeGetFormID(BTL_POKEPARAM_o *bpp) {
    return HighestMultiple(bpp->fields.m_formNo, 2) +
    ((uint32_t)bpp->GetValue(BTL_POKEPARAM_ValueID::BPP_HP, nullptr) <=
    Calc::QuotMaxHP_Zero(bpp, 2, false, nullptr));
}
void HandlerZenModeMemberInComp(EventFactor_EventHandlerArgs_o **args, uint8_t pokeID, MethodInfo *method) {
    BTL_POKEPARAM_o * bpp = Common::GetPokeParam(args,pokeID, nullptr);
    //if (bpp->HENSIN_Check(nullptr)) return;
    uint8_t nextForm = HandlerZenModeGetFormID(bpp);
    Common::SetWorkValue(args, A, true, nullptr);
    if (nextForm >= PersonalSystem::GetPersonalData(bpp->GetMonsNo(nullptr), 0,
                                                    nullptr)->fields.form_max) return;
    HandlerFormChange(args, pokeID, nextForm, false, true, true);
}
void HandlerZenModeTurncheckDone(EventFactor_EventHandlerArgs_o **args, uint8_t pokeID, MethodInfo *method) {
    if (!Common::GetWorkValue(args, A, nullptr)) return;
    BTL_POKEPARAM_o * bpp = Common::GetPokeParam(args,pokeID, nullptr);
    //if (bpp->HENSIN_Check(nullptr)) return;
    uint8_t nextForm = HandlerZenModeGetFormID(bpp);
    if (nextForm >= PersonalSystem::GetPersonalData(bpp->GetMonsNo(nullptr), 0,
                                                    nullptr)->fields.form_max) return;
    HandlerFormChange(args, pokeID, nextForm, false, true, true);
}
// Stance Change
void HandlerStanceChangeWazaCallDecide(EventFactor_EventHandlerArgs_o **args, uint8_t pokeID, MethodInfo *method) {
    if (Common::GetEventVar(args, EventVar::POKEID_ATK, nullptr) != pokeID) return;
    BTL_POKEPARAM_o * bpp = Common::GetPokeParam(args,pokeID, nullptr);
    //if (bpp->HENSIN_Check(nullptr)) return;
    int32_t wazaID = Common::GetEventVar(args, EventVar::WAZAID, nullptr);
    bool isDamage = WAZADATA::IsDamage(wazaID, nullptr);
    if (wazaID != KINGS_SHIELD && !isDamage) return;
    uint8_t nextForm = HighestMultiple(bpp->fields.m_formNo, 2);
    if (isDamage)
        nextForm += 1;
    if (nextForm >= PersonalSystem::GetPersonalData(bpp->GetMonsNo(nullptr), 0,
                                                    nullptr)->fields.form_max) return;
    HandlerFormChange(args, pokeID, nextForm, false, true, true);
}
// Shields Down
bool HandlerShieldsDownGetAddSickFail(BTL_POKEPARAM_o *bpp) {
    return bpp->fields.m_formNo % 14 < 7;
}
uint8_t HandlerShieldsDownGetFormID(BTL_POKEPARAM_o *bpp) {
    uint8_t nextForm = bpp->fields.m_formNo % 7;
    return HighestMultiple(bpp->fields.m_formNo, 14) + nextForm + 7 * ((uint32_t)bpp->GetValue(BTL_POKEPARAM_ValueID::BPP_HP, nullptr) <=
           Calc::QuotMaxHP_Zero(bpp, 2, false, nullptr));
}
void HandlerShieldsDownCheckInemuri(EventFactor_EventHandlerArgs_o **args, uint8_t pokeID, MethodInfo *method) {
    if (Common::GetEventVar(args, EventVar::POKEID, nullptr) != pokeID) return;
    if (!HandlerShieldsDownGetAddSickFail(Common::GetPokeParam(args,pokeID, nullptr))) return;
    Common::RewriteEventVar(args, EventVar::FAIL_FLAG, 1, nullptr);
}
void HandlerShieldsDownMemberInComp(EventFactor_EventHandlerArgs_o **args, uint8_t pokeID, MethodInfo *method) {
    BTL_POKEPARAM_o * bpp = Common::GetPokeParam(args,pokeID, nullptr);
    //if (bpp->HENSIN_Check(nullptr)) return;
    uint8_t nextForm = HandlerShieldsDownGetFormID(bpp);
    Common::SetWorkValue(args, B, true, nullptr);
    if (nextForm >= PersonalSystem::GetPersonalData(bpp->GetMonsNo(nullptr), 0,
                                                    nullptr)->fields.form_max) return;
    HandlerFormChange(args, pokeID, nextForm, false, true, true);
}
void HandlerShieldsDownAddSickCheckFail(EventFactor_EventHandlerArgs_o **args, uint8_t pokeID, MethodInfo *method) {
    if (Common::GetEventVar(args, EventVar::POKEID_DEF, nullptr) != pokeID) return;
    if (!HandlerShieldsDownGetAddSickFail(Common::GetPokeParam(args,pokeID, nullptr))) return;
    int32_t sickID = Common::GetEventVar(args, EventVar::SICKID, nullptr);
    if (sickID != WazaSick::WAZASICK_AKUBI && sickID > 5) return;
    Common::SetWorkValue(args, A, Common::RewriteEventVar(args, EventVar::FAIL_FLAG, true,
                                                          nullptr), nullptr);
}
void HandlerShieldsDownTurncheckDone(EventFactor_EventHandlerArgs_o **args, uint8_t pokeID, MethodInfo *method) {
    if (!Common::GetWorkValue(args, B, nullptr)) return;
    BTL_POKEPARAM_o * bpp = Common::GetPokeParam(args,pokeID, nullptr);
    //if (bpp->HENSIN_Check(nullptr)) return;
    uint8_t nextForm = HandlerShieldsDownGetFormID(bpp);
    if (nextForm >= PersonalSystem::GetPersonalData(bpp->GetMonsNo(nullptr), 0,
                                                    nullptr)->fields.form_max) return;
    HandlerFormChange(args, pokeID, nextForm, false, true, true);
}
// Schooling
uint8_t HandlerSchoolingGetFormID(BTL_POKEPARAM_o *bpp) {
    return HighestMultiple(bpp->fields.m_formNo, 2) +
           ((uint32_t)bpp->GetValue(BTL_POKEPARAM_ValueID::BPP_HP, nullptr) >
            Calc::QuotMaxHP_Zero(bpp, 4, false, nullptr) &&
            bpp->GetValue(BTL_POKEPARAM_ValueID::BPP_LEVEL, nullptr) >= 20);
}
void HandlerSchoolingMemberInComp(EventFactor_EventHandlerArgs_o **args, uint8_t pokeID, MethodInfo *method) {
    BTL_POKEPARAM_o * bpp = Common::GetPokeParam(args,pokeID, nullptr);
    //if (bpp->HENSIN_Check(nullptr)) return;
    uint8_t nextForm = HandlerSchoolingGetFormID(bpp);
    Common::SetWorkValue(args, A, true, nullptr);
    if (nextForm >= PersonalSystem::GetPersonalData(bpp->GetMonsNo(nullptr), 0,
                                                    nullptr)->fields.form_max) return;
    HandlerFormChange(args, pokeID, nextForm, false, true, true);
}
void HandlerSchoolingTurncheckDone(EventFactor_EventHandlerArgs_o **args, uint8_t pokeID, MethodInfo *method) {
    if (!Common::GetWorkValue(args, A, nullptr)) return;
    BTL_POKEPARAM_o * bpp = Common::GetPokeParam(args,pokeID, nullptr);
    //if (bpp->HENSIN_Check(nullptr)) return;
    uint8_t nextForm = HandlerSchoolingGetFormID(bpp);
    if (nextForm >= PersonalSystem::GetPersonalData(bpp->GetMonsNo(nullptr), 0,
                                                    nullptr)->fields.form_max) return;
    HandlerFormChange(args, pokeID, nextForm, false, true, true);
}
// Disguise
uint8_t HandlerDisguiseGetFormID(uint8_t formNo, uint8_t targetFormNo) {
    return HighestMultiple(formNo, 2) + targetFormNo;
}
void HandlerDisguiseWazaDmgProc2(EventFactor_EventHandlerArgs_o **args, uint8_t pokeID, MethodInfo *method) {
    if (Common::GetEventVar(args, EventVar::POKEID_DEF, nullptr) != pokeID) return;
    if (Common::GetEventVar(args, EventVar::MIGAWARI_FLAG, nullptr)) return;
    //if (bpp->HENSIN_Check(nullptr)) return;
    uint8_t formNo = Common::GetPokeParam(args,pokeID, nullptr)->fields.m_formNo;
    if (formNo != HandlerDisguiseGetFormID(formNo, 0)) return;
    Common::RewriteEventVar(args, EventVar::ZERO_DAMAGE_FLAG, true, nullptr);
    Common::SetWorkValue(args, A, true, nullptr);
}
void HandlerDisguiseWazaDmgReaction(EventFactor_EventHandlerArgs_o **args, uint8_t pokeID, MethodInfo *method) {
    if (Common::GetEventVar(args, EventVar::POKEID_DEF, nullptr) != pokeID) return;
    if (Common::GetEventVar(args, EventVar::MIGAWARI_FLAG, nullptr)) return;
    uint8_t formNo = Common::GetPokeParam(args,pokeID, nullptr)->fields.m_formNo;
    if (formNo != HandlerDisguiseGetFormID(formNo, 0)) return;
    if (!Common::GetWorkValue(args, A, nullptr)) return;
    uint8_t nextForm = HandlerDisguiseGetFormID(formNo, 1);
    BTL_POKEPARAM_o * bpp = Common::GetPokeParam(args,pokeID, nullptr);
    if (nextForm < PersonalSystem::GetPersonalData(bpp->GetMonsNo(nullptr), 0,
                                                    nullptr)->fields.form_max)
        HandlerFormChange(args, pokeID, nextForm, true, false, true);
    Common::SetWorkValue(args, A, false, nullptr);
    HandlerDamage(args, pokeID, pokeID,
                  Calc::QuotMaxHP(bpp, 8, true, nullptr),
                  false, true);
}
// Battle Bond
uint8_t HandlerBattleBondGetFormID(uint8_t formNo, uint8_t targetFormNo) {
    return HighestMultiple(formNo, 3) + targetFormNo;
}
void HandlerBattleBondWazaHitCount(EventFactor_EventHandlerArgs_o **args, uint8_t pokeID, MethodInfo *method) {
    if (Common::GetEventVar(args, EventVar::POKEID_ATK, nullptr) != pokeID) return;
    if (Common::GetEventVar(args, EventVar::WAZAID, nullptr) != WATER_SHURIKEN) return;
    uint8_t formNo = Common::GetPokeParam(args,pokeID, nullptr)->fields.m_formNo;
    if (formNo != HandlerBattleBondGetFormID(formNo, 2)) return;
    Common::RewriteEventVar(args, EventVar::HITCOUNT, 3, nullptr);
}
void HandlerBattleBondWazaPower(EventFactor_EventHandlerArgs_o **args, uint8_t pokeID, MethodInfo *method) {
    if (Common::GetEventVar(args, EventVar::POKEID_ATK, nullptr) != pokeID) return;
    if (Common::GetEventVar(args, EventVar::WAZAID, nullptr) != WATER_SHURIKEN) return;
    uint8_t formNo = Common::GetPokeParam(args,pokeID, nullptr)->fields.m_formNo;
    if (formNo != HandlerBattleBondGetFormID(formNo, 2)) return;
    Common::RewriteEventVar(args, EventVar::WAZA_POWER, Common::GetEventVar(args, EventVar::WAZA_POWER,
                                                                            nullptr) + 5, nullptr);
}
void HandlerBattleBondDamageprocEndHitReal(EventFactor_EventHandlerArgs_o **args, uint8_t pokeID, MethodInfo *method) {
    if (Common::GetWorkValue(args, PERSIST, nullptr)) return;
    if (Common::CheckShowDown(args, nullptr)) return;
    if (Common::GetKillCount(args, pokeID, nullptr) == 0) return;
    uint8_t formNo = Common::GetPokeParam(args,pokeID, nullptr)->fields.m_formNo;
    if (formNo == HandlerBattleBondGetFormID(formNo, 2)) return;
    uint8_t nextForm = HandlerBattleBondGetFormID(formNo, 2);
    BTL_POKEPARAM_o * bpp = Common::GetPokeParam(args,pokeID, nullptr);
    Common::SetWorkValue(args, PERSIST, true, nullptr);
    if (nextForm >= PersonalSystem::GetPersonalData(bpp->GetMonsNo(nullptr), 0,
                                                    nullptr)->fields.form_max) return;
    HandlerFormChange(args, pokeID, nextForm, true, true, true);
}
// Power Construct
uint8_t HandlerPowerConstructGetFormID(uint8_t formNo, uint8_t targetFormNo) {
    return HighestMultiple(formNo, 5) + targetFormNo;
}
void HandlerPowerConstructMemberInComp(EventFactor_EventHandlerArgs_o **args, uint8_t pokeID, MethodInfo *method) {
    BTL_POKEPARAM_o * bpp = Common::GetPokeParam(args,pokeID, nullptr);
    //if (bpp->HENSIN_Check(nullptr)) return;
    if ((uint32_t)bpp->GetValue(BTL_POKEPARAM_ValueID::BPP_HP, nullptr) >
        Calc::QuotMaxHP_Zero(bpp, 2, false, nullptr)) return;
    uint8_t nextForm = HandlerPowerConstructGetFormID(bpp->fields.m_formNo, 4);
    if (nextForm >= PersonalSystem::GetPersonalData(bpp->GetMonsNo(nullptr), 0,
                                                    nullptr)->fields.form_max) return;
    HandlerFormChange(args, pokeID, nextForm, true, true, true);
}
void HandlerPowerConstructTurncheckDone(EventFactor_EventHandlerArgs_o **args, uint8_t pokeID, MethodInfo *method) {
    BTL_POKEPARAM_o * bpp = Common::GetPokeParam(args, pokeID, nullptr);
    //if (bpp->HENSIN_Check(nullptr)) return;
    if ((uint32_t)bpp->GetValue(BTL_POKEPARAM_ValueID::BPP_HP, nullptr) >
        Calc::QuotMaxHP_Zero(bpp, 2, false, nullptr)) return;
    uint8_t nextForm = HandlerPowerConstructGetFormID(bpp->fields.m_formNo, 4);
    if (nextForm >= PersonalSystem::GetPersonalData(bpp->GetMonsNo(nullptr), 0,
                                                    nullptr)->fields.form_max) return;
    HandlerFormChange(args, pokeID, nextForm, true, true, true);
}
// Gulp Missile
uint8_t HandlerGulpMissileGetFormID(uint8_t formNo, uint8_t targetFormNo) {
    return HighestMultiple(formNo, 3) + targetFormNo;
}
void HandlerGulpMissileWazaseqEnd(EventFactor_EventHandlerArgs_o **args, uint8_t pokeID, MethodInfo *method) {
    if (Common::GetEventVar(args, EventVar::POKEID_ATK, nullptr) != pokeID) return;
    int32_t wazaID = Common::GetEventVar(args, EventVar::WAZAID, nullptr);
    if (wazaID != SURF && wazaID != DIVE) return;
    BTL_POKEPARAM_o * bpp = Common::GetPokeParam(args, pokeID, nullptr);
    uint8_t formNo = bpp->fields.m_formNo;
    if (formNo != HandlerGulpMissileGetFormID(formNo, 0)) return;
    uint8_t nextForm = HandlerGulpMissileGetFormID(formNo,1 +
    ((uint32_t)bpp->GetValue(BTL_POKEPARAM_ValueID::BPP_HP, nullptr) <=
    Calc::QuotMaxHP_Zero(bpp, 2, false, nullptr)));
    if (nextForm >= PersonalSystem::GetPersonalData(bpp->GetMonsNo(nullptr), 0,
                                                    nullptr)->fields.form_max) return;
    HandlerFormChange(args, pokeID, nextForm, false, true, wazaID != DIVE);
}
void HandlerGulpMissileWazaDmgReaction(EventFactor_EventHandlerArgs_o **args, uint8_t pokeID, MethodInfo *method) {
    if (Common::GetEventVar(args, EventVar::POKEID_DEF, nullptr) != pokeID) return;
    if (Common::GetEventVar(args, EventVar::MIGAWARI_FLAG, nullptr)) return;
    BTL_POKEPARAM_o * bpp = Common::GetPokeParam(args, pokeID, nullptr);
    uint8_t formNo = bpp->fields.m_formNo;
    if (formNo == HandlerGulpMissileGetFormID(formNo, 0)) return;
    int32_t pokeIDAtk = Common::GetEventVar(args, EventVar::POKEID_ATK, nullptr);
    BTL_POKEPARAM_o * bppAtk = Common::GetPokeParam(args, pokeIDAtk, nullptr);
    if (!bppAtk->IsDead(nullptr)) {
        HandlerDamage(args, pokeID, pokeIDAtk,
                      Calc::QuotMaxHP(bppAtk, 4, true, nullptr),
                      true, true);
        if (formNo == HandlerGulpMissileGetFormID(formNo, 1))
            HandlerRankEffect(args, pokeID, pokeIDAtk, WazaRankEffect::DEFENCE,
                              -1, false, false, true);
        else
            HandlerAddSick(args, pokeID, pokeIDAtk, WazaSick::WAZASICK_MAHI,
                           Calc::MakeDefaultPokeSickCont(Sick::MAHI,
                                                         pokeID,
                                                         false,
                                                         nullptr).fields.raw);
    }
    HandlerFormChange(args, pokeID, HandlerGulpMissileGetFormID(formNo, 0), false,
                      false, true);
}
// Ice Face
uint8_t HandlerIceFaceGetFormID(uint8_t formNo, uint8_t targetFormNo) {
    return HighestMultiple(formNo, 2) + targetFormNo;
}
void HandlerIceFaceWazaDmgProc2(EventFactor_EventHandlerArgs_o **args, uint8_t pokeID, MethodInfo *method) {
    if (Common::GetEventVar(args, EventVar::POKEID_DEF, nullptr) != pokeID) return;
    if (Common::GetEventVar(args, EventVar::MIGAWARI_FLAG, nullptr)) return;
    if (Common::GetEventVar(args, EventVar::DAMAGE_TYPE, nullptr) != WazaDamageType::PHYSIC) return;
    //if (bpp->HENSIN_Check(nullptr)) return;
    uint8_t formNo = Common::GetPokeParam(args,pokeID, nullptr)->fields.m_formNo;
    if (formNo != HandlerIceFaceGetFormID(formNo, 0)) return;
    Common::RewriteEventVar(args, EventVar::ZERO_DAMAGE_FLAG, true, nullptr);
    Common::SetWorkValue(args, A, true, nullptr);
}
void HandlerIceFaceWazaDmgReaction(EventFactor_EventHandlerArgs_o **args, uint8_t pokeID, MethodInfo *method) {
    if (Common::GetEventVar(args, EventVar::POKEID_DEF, nullptr) != pokeID) return;
    if (!Common::GetWorkValue(args, A, nullptr)) return;
    Common::SetWorkValue(args, A, false, nullptr);
    if (Common::GetEventVar(args, EventVar::MIGAWARI_FLAG, nullptr)) return;
    BTL_POKEPARAM_o * bpp = Common::GetPokeParam(args,pokeID, nullptr);
    uint8_t formNo = bpp->fields.m_formNo;
    if (formNo != HandlerIceFaceGetFormID(formNo, 0)) return;
    uint8_t nextForm = HandlerIceFaceGetFormID(formNo, 1);
    if (nextForm >= PersonalSystem::GetPersonalData(bpp->GetMonsNo(nullptr), 0,
                                                   nullptr)->fields.form_max) return;
    HandlerFormChange(args, pokeID, nextForm, true, true, true);
}
void HandlerIceFaceMemberInComp(EventFactor_EventHandlerArgs_o **args, uint8_t pokeID, MethodInfo *method) {
    BTL_POKEPARAM_o * bpp = Common::GetPokeParam(args,pokeID, nullptr);
    //if (bpp->HENSIN_Check(nullptr)) return;
    uint8_t formNo = bpp->fields.m_formNo;
    if (formNo != HandlerIceFaceGetFormID(formNo, 1)) return;
    if (Common::GetLocalWeather(args, pokeID, nullptr) != BtlWeather::BTL_WEATHER_SNOW) return;
    HandlerFormChange(args, pokeID, HandlerIceFaceGetFormID(formNo, 0), true,
                      true, true);
}
void HandlerIceFaceWeatherChangeAfter(EventFactor_EventHandlerArgs_o **args, uint8_t pokeID, MethodInfo *method) {
    BTL_POKEPARAM_o * bpp = Common::GetPokeParam(args,pokeID, nullptr);
    //if (bpp->HENSIN_Check(nullptr)) return;
    uint8_t formNo = bpp->fields.m_formNo;
    if (formNo != HandlerIceFaceGetFormID(formNo, 1)) return;
    if (Common::GetLocalWeather(args, pokeID, nullptr) != BtlWeather::BTL_WEATHER_SNOW) return;
    HandlerFormChange(args, pokeID, HandlerIceFaceGetFormID(formNo, 0), true,
                      true, true);
}
// Hunger Switch
uint8_t HandlerHungerSwitchGetFormID(uint8_t formNo, uint8_t targetFormNo) {
    return HighestMultiple(formNo, 2) + targetFormNo;
}
void HandlerHungerSwitchTurncheckDone(EventFactor_EventHandlerArgs_o **args, uint8_t pokeID, MethodInfo *method) {
    if (Common::GetEventVar(args, EventVar::POKEID, nullptr) != pokeID) return;
    BTL_POKEPARAM_o * bpp = Common::GetPokeParam(args,pokeID, nullptr);
    //if (bpp->HENSIN_Check(nullptr)) return;
    uint8_t formNo = bpp->fields.m_formNo;
    uint8_t form0 = HandlerHungerSwitchGetFormID(formNo, 0);
    uint8_t nextForm = (formNo == form0) ? HandlerHungerSwitchGetFormID(formNo, 1) : form0;
    if (nextForm >= PersonalSystem::GetPersonalData(bpp->GetMonsNo(nullptr), 0,
                                                    nullptr)->fields.form_max) return;
    HandlerFormChange(args, pokeID, nextForm, false, true, true);
}
// Quick Draw
void HandlerQuickDrawCheckSpPriority(EventFactor_EventHandlerArgs_o **args, uint8_t pokeID, MethodInfo *method) {
    if (Common::GetEventVar(args, EventVar::SP_PRIORITY, nullptr) != BtlSpecialPri::BTL_SPPRI_DEFAULT) return;
    if (Common::GetEventVar(args, EventVar::POKEID, nullptr) != pokeID) return;
    PokeAction_o *pokeAction = Common::SearchByPokeID(args, pokeID, true, true, nullptr);
    if (pokeAction == nullptr) return;
    if (!WAZADATA::IsDamage(PokeAction::GetWazaID(pokeAction, nullptr),nullptr)) return;
    if ((*args)->fields.pPokeActionContainer->IsAllActDoneByPokeID(pokeID, nullptr)) return;
    if (!Common::GetWorkValue(args, A, nullptr)) {
        Common::SetWorkValue(args, A, true, nullptr);
        Common::SetWorkValue(args, B, Calc::IsOccurPer(30, nullptr), nullptr);
    }
    if (!Common::GetWorkValue(args, B, nullptr)) return;
    if (!Common::RewriteEventVar(args, EventVar::SP_PRIORITY, BtlSpecialPri::BTL_SPPRI_HIGH, nullptr)) return;
    if (Common::GetWorkValue(args, C, nullptr)) return;
    Common::SetWorkValue(args, C, true, nullptr);
    HandlerMessage(args, pokeID, true);
}
void HandlerQuickDrawTurncheckDone(EventFactor_EventHandlerArgs_o **args, uint8_t pokeID, MethodInfo *method) {
    if (Common::GetEventVar(args, EventVar::POKEID, nullptr) != pokeID) return;
    Common::SetWorkValue(args, A, false, nullptr);
    Common::SetWorkValue(args, B, false, nullptr);
    Common::SetWorkValue(args, C, false, nullptr);
}
// Curious Medicine
void HandlerCuriousMedicineMemberInEvo(EventFactor_EventHandlerArgs_o **args, uint8_t pokeID, MethodInfo *method) {
    uint8_t targetPokeID = Common::GetEventVar(args, EventVar::POKEID, nullptr);
    if (targetPokeID == pokeID) return;
    if (!Common::IsFriendPokeID(args, pokeID, targetPokeID, nullptr)) return;
    if (!Common::GetWorkValue(args, A, nullptr)) {
        Common::SetWorkValue(args, A, true, nullptr);
        HandlerMessage(args, pokeID, true);
    }
    HandlerRankReset(args, targetPokeID);
}
// Transistor
void HandlerTransistorAttackerPower(EventFactor_EventHandlerArgs_o **args, uint8_t pokeID, MethodInfo *method) {
    if (Common::GetEventVar(args, EventVar::POKEID_ATK, nullptr) != pokeID) return;
    if (Common::GetEventVar(args, EventVar::WAZA_TYPE, nullptr) != ELECTRIC) return;
    Common::MulEventVar(args, EventVar::RATIO, 0x1800, nullptr);
}
// Dragon's Maw
void HandlerDragonsMawAttackerPower(EventFactor_EventHandlerArgs_o **args, uint8_t pokeID, MethodInfo *method) {
    if (Common::GetEventVar(args, EventVar::POKEID_ATK, nullptr) != pokeID) return;
    if (Common::GetEventVar(args, EventVar::WAZA_TYPE, nullptr) != DRAGON) return;
    Common::MulEventVar(args, EventVar::RATIO, 0x1800, nullptr);
}
// Chilling Neigh
void HandlerChillingNeighDamageprocEndHitReal(EventFactor_EventHandlerArgs_o **args, uint8_t pokeID,
                                              MethodInfo *method) {
    if (Common::CheckShowDown(args, nullptr)) return;
    uint32_t killCount = Common::GetKillCount(args, pokeID, nullptr);
    if (killCount == 0) return;
    HandlerRankEffect(args, pokeID, pokeID, WazaRankEffect::ATTACK,
                      killCount, true, true, false);
}
// Grim Neigh
void HandlerGrimNeighDamageprocEndHitReal(EventFactor_EventHandlerArgs_o **args, uint8_t pokeID,
                                              MethodInfo *method) {
    if (Common::CheckShowDown(args, nullptr)) return;
    uint32_t killCount = Common::GetKillCount(args, pokeID, nullptr);
    if (killCount == 0) return;
    HandlerRankEffect(args, pokeID, pokeID, WazaRankEffect::SP_ATTACK,
                      killCount, true, true, false);
}

EventFactor_EventHandlerTable_o * CreateAbilityEventHandler(uint16_t eventID, Il2CppMethodPointer methodPointer) {
    return CreateEventHandler(eventID, Method_handler_TetunoKobusi, methodPointer);
}

// --- HandlerGetFunc delegates ---
System::Array<EventFactor_EventHandlerTable_o *> * ADD_ZenMode(MethodInfo *method)
{
    if (sHandlerTableZenMode == nullptr) {
        sHandlerTableZenMode = (System::Array<EventFactor_EventHandlerTable_o *> *) system_array_new(EventFactor_EventHandlerTable_Array_TypeInfo, 2);
        sHandlerTableZenMode->m_Items[0] = CreateAbilityEventHandler(EventID::MEMBER_IN_COMP, (Il2CppMethodPointer) &HandlerZenModeMemberInComp);
        sHandlerTableZenMode->m_Items[1] = CreateAbilityEventHandler(EventID::TURNCHECK_DONE, (Il2CppMethodPointer) &HandlerZenModeTurncheckDone);
    }
    return sHandlerTableZenMode;
}
System::Array<EventFactor_EventHandlerTable_o *> * ADD_StanceChange(MethodInfo *method)
{
    if (sHandlerTableStanceChange == nullptr) {
        sHandlerTableStanceChange = (System::Array<EventFactor_EventHandlerTable_o *> *) system_array_new(EventFactor_EventHandlerTable_Array_TypeInfo, 1);
        sHandlerTableStanceChange->m_Items[0] = CreateAbilityEventHandler(EventID::WAZA_CALL_DECIDE, (Il2CppMethodPointer) &HandlerStanceChangeWazaCallDecide);
    }
    return sHandlerTableStanceChange;
}
System::Array<EventFactor_EventHandlerTable_o *> * ADD_ShieldsDown(MethodInfo *method)
{
    if (sHandlerTableShieldsDown == nullptr) {
        sHandlerTableShieldsDown = (System::Array<EventFactor_EventHandlerTable_o *> *) system_array_new(EventFactor_EventHandlerTable_Array_TypeInfo, 5);
        sHandlerTableShieldsDown->m_Items[0] = CreateAbilityEventHandler(EventID::CHECK_INEMURI, (Il2CppMethodPointer) &HandlerShieldsDownCheckInemuri);
        sHandlerTableShieldsDown->m_Items[1] = CreateAbilityEventHandler(EventID::MEMBER_IN_COMP, (Il2CppMethodPointer) &HandlerShieldsDownMemberInComp);
        sHandlerTableShieldsDown->m_Items[2] = CreateAbilityEventHandler(EventID::ADDSICK_CHECKFAIL, (Il2CppMethodPointer) &HandlerShieldsDownAddSickCheckFail);
        sHandlerTableShieldsDown->m_Items[3] = CreateAbilityEventHandler(EventID::ADDSICK_FAILED, (Il2CppMethodPointer) &Tokusei::handler_AddSickFailCommon);
        sHandlerTableShieldsDown->m_Items[4] = CreateAbilityEventHandler(EventID::TURNCHECK_DONE, (Il2CppMethodPointer) &HandlerShieldsDownTurncheckDone);
    }
    return sHandlerTableShieldsDown;
}
System::Array<EventFactor_EventHandlerTable_o *> * ADD_Schooling(MethodInfo *method)
{
    if (sHandlerTableSchooling == nullptr) {
        sHandlerTableSchooling = (System::Array<EventFactor_EventHandlerTable_o *> *) system_array_new(EventFactor_EventHandlerTable_Array_TypeInfo, 2);
        sHandlerTableSchooling->m_Items[0] = CreateAbilityEventHandler(EventID::MEMBER_IN_COMP, (Il2CppMethodPointer) &HandlerSchoolingMemberInComp);
        sHandlerTableSchooling->m_Items[1] = CreateAbilityEventHandler(EventID::TURNCHECK_DONE, (Il2CppMethodPointer) &HandlerSchoolingTurncheckDone);
    }
    return sHandlerTableSchooling;
}
System::Array<EventFactor_EventHandlerTable_o *> * ADD_Disguise(MethodInfo *method)
{
    if (sHandlerTableDisguise == nullptr) {
        sHandlerTableDisguise = (System::Array<EventFactor_EventHandlerTable_o *> *) system_array_new(EventFactor_EventHandlerTable_Array_TypeInfo, 2);
        sHandlerTableDisguise->m_Items[0] = CreateAbilityEventHandler(EventID::WAZA_DMG_PROC2, (Il2CppMethodPointer) &HandlerDisguiseWazaDmgProc2);
        sHandlerTableDisguise->m_Items[1] = CreateAbilityEventHandler(EventID::WAZA_DMG_REACTION, (Il2CppMethodPointer) &HandlerDisguiseWazaDmgReaction);
    }
    return sHandlerTableDisguise;
}
System::Array<EventFactor_EventHandlerTable_o *> * ADD_BattleBond(MethodInfo *method)
{
    if (sHandlerTableBattleBond == nullptr) {
        sHandlerTableBattleBond = (System::Array<EventFactor_EventHandlerTable_o *> *) system_array_new(EventFactor_EventHandlerTable_Array_TypeInfo, 3);
        sHandlerTableBattleBond->m_Items[0] = CreateAbilityEventHandler(EventID::WAZA_HIT_COUNT, (Il2CppMethodPointer) &HandlerBattleBondWazaHitCount);
        sHandlerTableBattleBond->m_Items[1] = CreateAbilityEventHandler(EventID::WAZA_POWER, (Il2CppMethodPointer) &HandlerBattleBondWazaPower);
        sHandlerTableBattleBond->m_Items[2] = CreateAbilityEventHandler(EventID::DAMAGEPROC_END_HIT_REAL, (Il2CppMethodPointer) &HandlerBattleBondDamageprocEndHitReal);
    }
    return sHandlerTableBattleBond;
}
System::Array<EventFactor_EventHandlerTable_o *> * ADD_PowerConstruct(MethodInfo *method)
{
    if (sHandlerTablePowerConstruct == nullptr) {
        sHandlerTablePowerConstruct = (System::Array<EventFactor_EventHandlerTable_o *> *) system_array_new(EventFactor_EventHandlerTable_Array_TypeInfo, 2);
        sHandlerTablePowerConstruct->m_Items[0] = CreateAbilityEventHandler(EventID::MEMBER_IN_COMP, (Il2CppMethodPointer) &HandlerPowerConstructMemberInComp);
        sHandlerTablePowerConstruct->m_Items[1] = CreateAbilityEventHandler(EventID::TURNCHECK_DONE, (Il2CppMethodPointer) &HandlerPowerConstructTurncheckDone);
    }
    return sHandlerTablePowerConstruct;
}
System::Array<EventFactor_EventHandlerTable_o *> * ADD_GulpMissile(MethodInfo *method)
{
    if (sHandlerTableGulpMissile == nullptr) {
        sHandlerTableGulpMissile = (System::Array<EventFactor_EventHandlerTable_o *> *) system_array_new(EventFactor_EventHandlerTable_Array_TypeInfo, 2);
        sHandlerTableGulpMissile->m_Items[0] = CreateAbilityEventHandler(EventID::WAZASEQ_END, (Il2CppMethodPointer) &HandlerGulpMissileWazaseqEnd);
        sHandlerTableGulpMissile->m_Items[1] = CreateAbilityEventHandler(EventID::WAZA_DMG_REACTION, (Il2CppMethodPointer) &HandlerGulpMissileWazaDmgReaction);
    }
    return sHandlerTableGulpMissile;
}
System::Array<EventFactor_EventHandlerTable_o *> * ADD_IceFace(MethodInfo *method)
{
    if (sHandlerTableIceFace == nullptr) {
        sHandlerTableIceFace = (System::Array<EventFactor_EventHandlerTable_o *> *) system_array_new(EventFactor_EventHandlerTable_Array_TypeInfo, 4);
        sHandlerTableIceFace->m_Items[0] = CreateAbilityEventHandler(EventID::WAZA_DMG_PROC2, (Il2CppMethodPointer) &HandlerIceFaceWazaDmgProc2);
        sHandlerTableIceFace->m_Items[1] = CreateAbilityEventHandler(EventID::WAZA_DMG_REACTION, (Il2CppMethodPointer) &HandlerIceFaceWazaDmgReaction);
        sHandlerTableIceFace->m_Items[2] = CreateAbilityEventHandler(EventID::MEMBER_IN_COMP, (Il2CppMethodPointer) &HandlerIceFaceMemberInComp);
        sHandlerTableIceFace->m_Items[3] = CreateAbilityEventHandler(EventID::WEATHER_CHANGE_AFTER, (Il2CppMethodPointer) &HandlerIceFaceWeatherChangeAfter);
    }
    return sHandlerTableIceFace;
}
System::Array<EventFactor_EventHandlerTable_o *> * ADD_HungerSwitch(MethodInfo *method)
{
    if (sHandlerTableHungerSwitch == nullptr) {
        sHandlerTableHungerSwitch = (System::Array<EventFactor_EventHandlerTable_o *> *) system_array_new(EventFactor_EventHandlerTable_Array_TypeInfo, 1);
        sHandlerTableHungerSwitch->m_Items[0] = CreateAbilityEventHandler(EventID::TURNCHECK_DONE, (Il2CppMethodPointer) &HandlerHungerSwitchTurncheckDone);
    }
    return sHandlerTableHungerSwitch;
}
System::Array<EventFactor_EventHandlerTable_o *> * ADD_QuickDraw(MethodInfo *method)
{
    if (sHandlerTableQuickDraw == nullptr) {
        sHandlerTableQuickDraw = (System::Array<EventFactor_EventHandlerTable_o *> *) system_array_new(EventFactor_EventHandlerTable_Array_TypeInfo, 2);
        sHandlerTableQuickDraw->m_Items[0] = CreateAbilityEventHandler(EventID::CHECK_SP_PRIORITY, (Il2CppMethodPointer) &HandlerQuickDrawCheckSpPriority);
        sHandlerTableQuickDraw->m_Items[1] = CreateAbilityEventHandler(EventID::TURNCHECK_DONE, (Il2CppMethodPointer) &HandlerQuickDrawTurncheckDone);
    }
    return sHandlerTableQuickDraw;
}
System::Array<EventFactor_EventHandlerTable_o *> * ADD_CuriousMedicine(MethodInfo *method)
{
    if (sHandlerTableCuriousMedicine == nullptr) {
        sHandlerTableCuriousMedicine = (System::Array<EventFactor_EventHandlerTable_o *> *) system_array_new(EventFactor_EventHandlerTable_Array_TypeInfo, 1);
        sHandlerTableCuriousMedicine->m_Items[0] = CreateAbilityEventHandler(EventID::MEMBER_IN_EVO, (Il2CppMethodPointer) &HandlerCuriousMedicineMemberInEvo);
    }
    return sHandlerTableCuriousMedicine;
}
System::Array<EventFactor_EventHandlerTable_o *> * ADD_Transistor(MethodInfo *method)
{
    if (sHandlerTableTransistor == nullptr) {
        sHandlerTableTransistor = (System::Array<EventFactor_EventHandlerTable_o *> *) system_array_new(EventFactor_EventHandlerTable_Array_TypeInfo, 1);
        sHandlerTableTransistor->m_Items[0] = CreateAbilityEventHandler(EventID::ATTACKER_POWER, (Il2CppMethodPointer) &HandlerTransistorAttackerPower);
    }
    return sHandlerTableTransistor;
}
System::Array<EventFactor_EventHandlerTable_o *> * ADD_DragonsMaw(MethodInfo *method)
{
    if (sHandlerTableDragonsMaw == nullptr) {
        sHandlerTableDragonsMaw = (System::Array<EventFactor_EventHandlerTable_o *> *) system_array_new(EventFactor_EventHandlerTable_Array_TypeInfo, 1);
        sHandlerTableDragonsMaw->m_Items[0] = CreateAbilityEventHandler(EventID::ATTACKER_POWER, (Il2CppMethodPointer) &HandlerDragonsMawAttackerPower);
    }
    return sHandlerTableDragonsMaw;
}
System::Array<EventFactor_EventHandlerTable_o *> * ADD_ChillingNeigh(MethodInfo *method)
{
    if (sHandlerTableChillingNeigh == nullptr) {
        sHandlerTableChillingNeigh = (System::Array<EventFactor_EventHandlerTable_o *> *) system_array_new(EventFactor_EventHandlerTable_Array_TypeInfo, 1);
        sHandlerTableChillingNeigh->m_Items[0] = CreateAbilityEventHandler(EventID::DAMAGEPROC_END_HIT_REAL, (Il2CppMethodPointer) &HandlerChillingNeighDamageprocEndHitReal);
    }
    return sHandlerTableChillingNeigh;
}
System::Array<EventFactor_EventHandlerTable_o *> * ADD_GrimNeigh(MethodInfo *method)
{
    if (sHandlerTableGrimNeigh == nullptr) {
        sHandlerTableGrimNeigh = (System::Array<EventFactor_EventHandlerTable_o *> *) system_array_new(EventFactor_EventHandlerTable_Array_TypeInfo, 1);
        sHandlerTableGrimNeigh->m_Items[0] = CreateAbilityEventHandler(EventID::DAMAGEPROC_END_HIT_REAL, (Il2CppMethodPointer) &HandlerGrimNeighDamageprocEndHitReal);
    }
    return sHandlerTableGrimNeigh;
}
System::Array<EventFactor_EventHandlerTable_o *> * ADD_AsOne0(MethodInfo *method)
{
    if (sHandlerTableAsOne0 == nullptr) {
        sHandlerTableAsOne0 = (System::Array<EventFactor_EventHandlerTable_o *> *) system_array_new(EventFactor_EventHandlerTable_Array_TypeInfo, 3);
        sHandlerTableAsOne0->m_Items[0] = CreateAbilityEventHandler(EventID::MEMBER_IN_PREV2, (Il2CppMethodPointer) &Tokusei::handler_Kinchoukan_MemberIn);
        sHandlerTableAsOne0->m_Items[1] = CreateAbilityEventHandler(EventID::DAMAGEPROC_END_HIT_REAL, (Il2CppMethodPointer) &HandlerChillingNeighDamageprocEndHitReal);
        sHandlerTableAsOne0->m_Items[2] = CreateAbilityEventHandler(EventID::CHANGE_TOKUSEI_AFTER, (Il2CppMethodPointer) &Tokusei::handler_Kinchoukan_MemberIn);
    }
    return sHandlerTableAsOne0;
}
System::Array<EventFactor_EventHandlerTable_o *> * ADD_AsOne1(MethodInfo *method)
{
    if (sHandlerTableAsOne1 == nullptr) {
        sHandlerTableAsOne1 = (System::Array<EventFactor_EventHandlerTable_o *> *) system_array_new(EventFactor_EventHandlerTable_Array_TypeInfo, 3);
        sHandlerTableAsOne1->m_Items[0] = CreateAbilityEventHandler(EventID::MEMBER_IN_PREV2, (Il2CppMethodPointer) &Tokusei::handler_Kinchoukan_MemberIn);
        sHandlerTableAsOne1->m_Items[1] = CreateAbilityEventHandler(EventID::DAMAGEPROC_END_HIT_REAL, (Il2CppMethodPointer) &HandlerGrimNeighDamageprocEndHitReal);
        sHandlerTableAsOne1->m_Items[2] = CreateAbilityEventHandler(EventID::CHANGE_TOKUSEI_AFTER, (Il2CppMethodPointer) &Tokusei::handler_Kinchoukan_MemberIn);
    }
    return sHandlerTableAsOne1;
}

//Adds an additional entry to GET_FUNC_TABLE
void SetAbilityFunctionTable(System::Array<Tokusei_GET_FUNC_TABLE_ELEM_o> * getFuncTable, uint32_t * idx, int32_t tokusei, Il2CppMethodPointer methodPointer)
{
    MethodInfo * method = copyMethodInfo(Method_ADD_TetunoKobusi, methodPointer);
    Tokusei_GET_FUNC_TABLE_ELEM_o * elem = &getFuncTable->m_Items[*idx];
    Tokusei_HandlerGetFunc_o * func = (Tokusei_HandlerGetFunc_o *) il2cpp_object_new(Tokusei_HandlerGetFunc_TypeInfo);
    func->ctor((intptr_t) methodPointer, method);
    elem->fields.tokusei = tokusei;
    elem->fields.func = func;
    *idx += 1;
}

//Entry point. Replaces system_array_new.
void * Tokusei_system_array_new(void * typeInfo, uint32_t len)
{
    System::Array<Tokusei_GET_FUNC_TABLE_ELEM_o> * getFuncTable = (System::Array<Tokusei_GET_FUNC_TABLE_ELEM_o> *) system_array_new(typeInfo, len + NEW_ABILITIES_COUNT);
    uint32_t idx = len;

    SetAbilityFunctionTable(getFuncTable, &idx, ZEN_MODE, (Il2CppMethodPointer) &ADD_ZenMode);
    SetAbilityFunctionTable(getFuncTable, &idx, STANCE_CHANGE, (Il2CppMethodPointer) &ADD_StanceChange);
    SetAbilityFunctionTable(getFuncTable, &idx, SHIELDS_DOWN, (Il2CppMethodPointer) &ADD_ShieldsDown);
    SetAbilityFunctionTable(getFuncTable, &idx, SCHOOLING, (Il2CppMethodPointer) &ADD_Schooling);
    SetAbilityFunctionTable(getFuncTable, &idx, DISGUISE, (Il2CppMethodPointer) &ADD_Disguise);
    SetAbilityFunctionTable(getFuncTable, &idx, BATTLE_BOND, (Il2CppMethodPointer) &ADD_BattleBond);
    SetAbilityFunctionTable(getFuncTable, &idx, POWER_CONSTRUCT, (Il2CppMethodPointer) &ADD_PowerConstruct);
    SetAbilityFunctionTable(getFuncTable, &idx, GULP_MISSILE, (Il2CppMethodPointer) &ADD_GulpMissile);
    SetAbilityFunctionTable(getFuncTable, &idx, ICE_FACE, (Il2CppMethodPointer) &ADD_IceFace);
    SetAbilityFunctionTable(getFuncTable, &idx, HUNGER_SWITCH, (Il2CppMethodPointer) &ADD_HungerSwitch);
    SetAbilityFunctionTable(getFuncTable, &idx, QUICK_DRAW, (Il2CppMethodPointer) &ADD_QuickDraw);
    SetAbilityFunctionTable(getFuncTable, &idx, CURIOUS_MEDICINE, (Il2CppMethodPointer) &ADD_CuriousMedicine);
    SetAbilityFunctionTable(getFuncTable, &idx, TRANSISTOR, (Il2CppMethodPointer) &ADD_Transistor);
    SetAbilityFunctionTable(getFuncTable, &idx, DRAGONS_MAW, (Il2CppMethodPointer) &ADD_DragonsMaw);
    SetAbilityFunctionTable(getFuncTable, &idx, CHILLING_NEIGH, (Il2CppMethodPointer) &ADD_ChillingNeigh);
    SetAbilityFunctionTable(getFuncTable, &idx, GRIM_NEIGH, (Il2CppMethodPointer) &ADD_GrimNeigh);
    SetAbilityFunctionTable(getFuncTable, &idx, AS_ONE0, (Il2CppMethodPointer) &ADD_AsOne0);
    SetAbilityFunctionTable(getFuncTable, &idx, AS_ONE1, (Il2CppMethodPointer) &ADD_AsOne1);

    return getFuncTable;
}