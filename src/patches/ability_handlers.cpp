#include "Dpr/Battle/Logic/BtlStrType.hpp"
#include "Dpr/Battle/Logic/BtlWeather.hpp"
#include "Dpr/Battle/Logic/Calc.hpp"
#include "Dpr/Battle/Logic/Common.hpp"
#include "Dpr/Battle/Logic/DamageCause.hpp"
#include "Dpr/Battle/Logic/EventFactor.hpp"
#include "Dpr/Battle/Logic/EventID.hpp"
#include "Dpr/Battle/Logic/EventVar.hpp"
#include "Dpr/Battle/Logic/Handler.hpp"
#include "Dpr/Battle/Logic/Handler/Tokusei.hpp"
#include "Dpr/Battle/Logic/RankEffectCause.hpp"
#include "Dpr/Battle/Logic/Section_AddSick.hpp"
#include "Dpr/Battle/Logic/Section_FromEvent_Damage.hpp"
#include "Dpr/Battle/Logic/Section_FromEvent_FormChange.hpp"
#include "Dpr/Battle/Logic/Section_FromEvent_RankEffect.hpp"
#include "Dpr/Battle/Logic/SickCause.hpp"
#include "Dpr/Battle/Logic/WAZADATA.hpp"
#include "Pml/Personal/ParamID.hpp"
#include "Pml/Personal/PersonalTableExtensions.hpp"
#include "Pml/Personal/PersonalSystem.hpp"
#include "Pml/PokePara/Accessor.h"
#include "Pml/PokePara/CoreParam.h"
#include "Pml/PokePara/Sick.hpp"
#include "Pml/WazaData/WazaDamageType.hpp"
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

// AbilityIDs
constexpr uint32_t FORECAST_ID = 59;
constexpr uint32_t MULTITYPE_ID = 121;
constexpr uint32_t FLOWER_GIFT_ID = 122;
constexpr uint32_t ZEN_MODE_ID = 161;
constexpr uint32_t STANCE_CHANGE_ID = 176;
constexpr uint32_t SHIELDS_DOWN_ID = 197;
constexpr uint32_t SCHOOLING_ID = 208;
constexpr uint32_t DISGUISE_ID = 209;
constexpr uint32_t BATTLE_BOND_ID = 210;
constexpr uint32_t POWER_CONSTRUCT_ID = 211;
constexpr uint32_t RKS_SYSTEM_ID = 225;
constexpr uint32_t GULP_MISSILE_ID = 241;
constexpr uint32_t ICE_FACE_ID = 248;
constexpr uint32_t HUNGER_SWITCH_ID = 258;

// MoveIDs
constexpr uint32_t SURF_ID = 57;
constexpr uint32_t DIVE_ID = 291;
constexpr uint32_t KINGS_SHIELD_ID = 588;
constexpr uint32_t WATER_SHURIKEN_ID = 594;

// ItemIDs
constexpr uint32_t FLAME_PLATE_ID = 298;
constexpr uint32_t SPLASH_PLATE_ID = 299;
constexpr uint32_t ZAP_PLATE_ID = 300;
constexpr uint32_t MEADOW_PLATE_ID = 301;
constexpr uint32_t ICICLE_PLATE_ID = 302;
constexpr uint32_t FIST_PLATE_ID = 303;
constexpr uint32_t TOXIC_PLATE_ID = 304;
constexpr uint32_t EARTH_PLATE_ID = 305;
constexpr uint32_t SKY_PLATE_ID = 306;
constexpr uint32_t MIND_PLATE_ID = 307;
constexpr uint32_t INSECT_PLATE_ID = 308;
constexpr uint32_t STONE_PLATE_ID = 309;
constexpr uint32_t SPOOKY_PLATE_ID = 310;
constexpr uint32_t DRACO_PLATE_ID = 311;
constexpr uint32_t DREAD_PLATE_ID = 312;
constexpr uint32_t IRON_PLATE_ID = 313;
constexpr uint32_t PIXIE_PLATE_ID = 644;
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

// Remember to update when adding handlers
const uint32_t NEW_ABILITIES_COUNT = 10;

// HandlerTables
static System::Array<EventFactor_EventHandlerTable_o *> * sHandlerTableZenMode;
static System::Array<EventFactor_EventHandlerTable_o *> * sHandlerTableStanceChange;
static System::Array<EventFactor_EventHandlerTable_o *> * sHandlerTableShieldsDown;
static System::Array<EventFactor_EventHandlerTable_o *> * sHandlerTableSchooling;
static System::Array<EventFactor_EventHandlerTable_o *> * sHandlerTableDisguise;
static System::Array<EventFactor_EventHandlerTable_o *> * sHandlerTableBattleBond;
static System::Array<EventFactor_EventHandlerTable_o *> * sHandlerTablePowerConstruct;
static System::Array<EventFactor_EventHandlerTable_o *> * sHandlerTableGulpMissile;
static System::Array<EventFactor_EventHandlerTable_o *> * sHandlerTableIceFace;
static System::Array<EventFactor_EventHandlerTable_o *> * sHandlerTableHungerSwitch;


// --- EventHandler delegates ---
uint8_t HighestMultiple(uint8_t max, uint8_t factor) {
    uint8_t factor2 = max / factor;
    return factor * factor2;
}
void HandlerFormChange(EventFactor_EventHandlerArgs_o **args, uint8_t pokeID, uint8_t nextForm, bool persistOnSwitch,
                       bool displayAbility, bool animationEnabled) {
    system_load_typeinfo((void *)0x88fe);
    BTL_POKEPARAM_o * bpp = Common::GetPokeParam(args,pokeID, nullptr);
    if (bpp->fields.m_formNo == nextForm) return;
    Section_FromEvent_FormChange_Description_o * desc = (Section_FromEvent_FormChange_Description_o *)
            il2cpp_object_new(Section_FromEvent_FormChange_Description_TypeInfo);
    desc->ctor(nullptr);
    desc->fields.pokeID = pokeID;
    desc->fields.formNo = nextForm;
    desc->fields.isDontResetFormByOut = persistOnSwitch;
    desc->fields.isDisplayTokuseiWindow = displayAbility;
    desc->fields.isDisplayChangeEffect = animationEnabled;
    desc->fields.successMessage->Setup(BtlStrType::BTL_STRTYPE_SET, 304, nullptr);
    desc->fields.successMessage->AddArg(pokeID, nullptr);
    Common::FormChange(args, &desc, nullptr);
}
uint8_t MultitypeType(uint32_t itemNo) {
    switch (itemNo) {
        case FIST_PLATE_ID:
        case FIGHTINIUM_Z:
            return 1;
        case SKY_PLATE_ID:
        case FLYINIUM_Z:
            return 2;
        case TOXIC_PLATE_ID:
        case POISONIUM_Z:
            return 3;
        case EARTH_PLATE_ID:
        case GROUNDIUM_Z:
            return 4;
        case STONE_PLATE_ID:
        case ROCKIUM_Z:
            return 5;
        case INSECT_PLATE_ID:
        case BUGINIUM_Z:
            return 6;
        case SPOOKY_PLATE_ID:
        case GHOSTIUM_Z:
            return 7;
        case IRON_PLATE_ID:
        case STEELIUM_Z:
            return 8;
        case FLAME_PLATE_ID:
        case FIRIUM_Z:
            return 9;
        case SPLASH_PLATE_ID:
        case WATERIUM_Z:
            return 10;
        case MEADOW_PLATE_ID:
        case GRASSIUM_Z:
            return 11;
        case ZAP_PLATE_ID:
        case ELECTRIUM_Z:
            return 12;
        case MIND_PLATE_ID:
        case PSYCHIUM_Z:
            return 13;
        case ICICLE_PLATE_ID:
        case ICIUM_Z:
            return 14;
        case DRACO_PLATE_ID:
        case DRAGONIUM_Z:
            return 15;
        case DREAD_PLATE_ID:
        case DARKINIUM_Z:
            return 16;
        case PIXIE_PLATE_ID:
        case FAIRIUM_Z:
            return 17;
        default:
            return 0;
    }
}
uint8_t RKSSystemType(uint32_t itemNo) {
    switch (itemNo) {
        case FIGHTING_MEMORY:
            return 1;
        case FLYING_MEMORY:
            return 2;
        case POISON_MEMORY:
            return 3;
        case GROUND_MEMORY:
            return 4;
        case ROCK_MEMORY:
            return 5;
        case BUG_MEMORY:
            return 6;
        case GHOST_MEMORY:
            return 7;
        case STEEL_MEMORY:
            return 8;
        case FIRE_MEMORY:
            return 9;
        case WATER_MEMORY:
            return 10;
        case GRASS_MEMORY:
            return 11;
        case ELECTRIC_MEMORY:
            return 12;
        case PSYCHIC_MEMORY:
            return 13;
        case ICE_MEMORY:
            return 14;
        case DRAGON_MEMORY:
            return 15;
        case DARK_MEMORY:
            return 16;
        case FAIRY_MEMORY:
            return 17;
        default:
            return 0;
    }
}
uint8_t GetType(CoreParam *cp, int32_t paramID) {
    Accessor *a = cp->fields.m_accessor;
    int32_t tokuseiNo = a->GetTokuseiNo(nullptr);
    uint32_t itemNo = a->GetItemNo(nullptr);
    if (tokuseiNo == MULTITYPE_ID)
        return MultitypeType(itemNo);
    if (tokuseiNo == RKS_SYSTEM_ID)
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
    if (Common::GetWorkValue(args, 0, nullptr) == 0) return;
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
    if (nextForm >= PersonalSystem::GetPersonalData(bpp->GetMonsNo(nullptr), 0,
                                                    nullptr)->fields.form_max) return;
    HandlerFormChange(args, pokeID, nextForm, false, true, true);
    Common::SetWorkValue(args, 0, 1, nullptr);
}
void HandlerForecastTokuseiDisable(EventFactor_EventHandlerArgs_o **args, uint8_t pokeID, MethodInfo *method) {
    if (Common::GetEventVar(args, EventVar::POKEID, nullptr) != pokeID) return;
    //if (bpp->HENSIN_Check(nullptr)) return;
    HandlerFormChange(args, pokeID, HandlerForecastGetFormID0(args, pokeID), false,
                      false, true);
}
void HandlerForecastNotifyAirlock(EventFactor_EventHandlerArgs_o **args, uint8_t pokeID, MethodInfo *method) {
    if (Common::GetWorkValue(args, 0, nullptr) == 0) return;
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
    if (Common::GetWorkValue(args, 0, nullptr) == 0) return;
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
    if (nextForm >= PersonalSystem::GetPersonalData(bpp->GetMonsNo(nullptr), 0,
                                                    nullptr)->fields.form_max) return;
    HandlerFormChange(args, pokeID, nextForm, false, true, true);
    Common::SetWorkValue(args, 0, 1, nullptr);
}
void HandlerFlowerGiftTokuseiDisable(EventFactor_EventHandlerArgs_o **args, uint8_t pokeID, MethodInfo *method) {
    if (Common::GetWorkValue(args, 0, nullptr) == 0) return;
    if (Common::GetEventVar(args, EventVar::POKEID, nullptr) != pokeID) return;
    //if (bpp->HENSIN_Check(nullptr)) return;
    HandlerFormChange(args, pokeID, HandlerFlowerGiftGetFormID0(args, pokeID), false,
                      false, true);
}
void HandlerFlowerGiftNotifyAirlock(EventFactor_EventHandlerArgs_o **args, uint8_t pokeID, MethodInfo *method) {
    if (Common::GetWorkValue(args, 0, nullptr) == 0) return;
    //if (bpp->HENSIN_Check(nullptr)) return;
    HandlerFormChange(args, pokeID, HandlerFlowerGiftGetFormID0(args, pokeID), false,
                      false, true);
}
void HandlerFlowerGiftChangeTokuseiBefore(EventFactor_EventHandlerArgs_o **args, uint8_t pokeID, MethodInfo *method) {
    if (Common::GetWorkValue(args, 0, nullptr) == 0) return;
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
    if (nextForm >= PersonalSystem::GetPersonalData(bpp->GetMonsNo(nullptr), 0,
                                                    nullptr)->fields.form_max) return;
    HandlerFormChange(args, pokeID, nextForm, false, true, true);
    Common::SetWorkValue(args, 0, 1, nullptr);
}
void HandlerZenModeTurncheckDone(EventFactor_EventHandlerArgs_o **args, uint8_t pokeID, MethodInfo *method) {
    if (Common::GetWorkValue(args, 0, nullptr) == 0) return;
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
    int32_t damageType = WAZADATA::GetDamageType(wazaID, nullptr);
    if (wazaID != KINGS_SHIELD_ID && damageType == WazaDamageType::NONE) return;
    uint8_t nextForm = HighestMultiple(bpp->fields.m_formNo, 2);
    if (damageType > 0)
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
    if (bpp->fields.m_formNo > 13) return;
    uint8_t nextForm = HandlerShieldsDownGetFormID(bpp);
    if (nextForm >= PersonalSystem::GetPersonalData(bpp->GetMonsNo(nullptr), 0,
                                                    nullptr)->fields.form_max) return;
    HandlerFormChange(args, pokeID, nextForm, false, true, true);
    Common::SetWorkValue(args, 1, 1, nullptr);
}
void HandlerShieldsDownAddSickCheckFail(EventFactor_EventHandlerArgs_o **args, uint8_t pokeID, MethodInfo *method) {
    if (Common::GetEventVar(args, EventVar::POKEID_DEF, nullptr) != pokeID) return;
    if (!HandlerShieldsDownGetAddSickFail(Common::GetPokeParam(args,pokeID, nullptr))) return;
    int32_t sickID = Common::GetEventVar(args, EventVar::SICKID, nullptr);
    if (sickID != 14 && sickID > 5) return;
    Common::SetWorkValue(args, 0, Common::RewriteEventVar(args, EventVar::FAIL_FLAG, 1,
                                                          nullptr), nullptr);
}
void HandlerShieldsDownTurncheckDone(EventFactor_EventHandlerArgs_o **args, uint8_t pokeID, MethodInfo *method) {
    if (Common::GetWorkValue(args, 1, nullptr) == 0) return;
    BTL_POKEPARAM_o * bpp = Common::GetPokeParam(args,pokeID, nullptr);
    //if (bpp->HENSIN_Check(nullptr)) return;
    if (bpp->fields.m_formNo > 13) return;
    uint8_t nextForm = HandlerShieldsDownGetFormID(bpp);
    if (nextForm >= PersonalSystem::GetPersonalData(bpp->GetMonsNo(nullptr), 0,
                                                    nullptr)->fields.form_max) return;
    HandlerFormChange(args, pokeID, nextForm, false, true, true);
}
// Schooling
uint8_t HandlerSchoolingGetFormID(BTL_POKEPARAM_o *bpp) {
    return HighestMultiple(bpp->fields.m_formNo, 2) +
           ((uint32_t)bpp->GetValue(BTL_POKEPARAM_ValueID::BPP_HP, nullptr) >
            Calc::QuotMaxHP_Zero(bpp, 4, false, nullptr) && bpp->GetValue(17, nullptr) >= 20);
}
void HandlerSchoolingMemberInComp(EventFactor_EventHandlerArgs_o **args, uint8_t pokeID, MethodInfo *method) {
    BTL_POKEPARAM_o * bpp = Common::GetPokeParam(args,pokeID, nullptr);
    //if (bpp->HENSIN_Check(nullptr)) return;
    uint8_t nextForm = HandlerSchoolingGetFormID(bpp);
    if (nextForm >= PersonalSystem::GetPersonalData(bpp->GetMonsNo(nullptr), 0,
                                                    nullptr)->fields.form_max) return;
    HandlerFormChange(args, pokeID, nextForm, false, true, true);
    Common::SetWorkValue(args, 0, 1, nullptr);
}
void HandlerSchoolingTurncheckDone(EventFactor_EventHandlerArgs_o **args, uint8_t pokeID, MethodInfo *method) {
    if (Common::GetWorkValue(args, 0, nullptr) == 0) return;
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
    Common::RewriteEventVar(args, EventVar::ZERO_DAMAGE_FLAG, 1, nullptr);
    Common::SetWorkValue(args, 0, 1, nullptr);
}
void HandlerDisguiseWazaDmgReaction(EventFactor_EventHandlerArgs_o **args, uint8_t pokeID, MethodInfo *method) {
    system_load_typeinfo((void *)0x8a36);
    if (Common::GetEventVar(args, EventVar::POKEID_DEF, nullptr) != pokeID) return;
    if (Common::GetEventVar(args, EventVar::MIGAWARI_FLAG, nullptr)) return;
    uint8_t formNo = Common::GetPokeParam(args,pokeID, nullptr)->fields.m_formNo;
    if (formNo != HandlerDisguiseGetFormID(formNo, 0)) return;
    if (Common::GetWorkValue(args, 0, nullptr) == 0) return;
    uint8_t nextForm = HandlerDisguiseGetFormID(formNo, 1);
    BTL_POKEPARAM_o * bpp = Common::GetPokeParam(args,pokeID, nullptr);
    if (nextForm < PersonalSystem::GetPersonalData(bpp->GetMonsNo(nullptr), 0,
                                                    nullptr)->fields.form_max)
        HandlerFormChange(args, pokeID, nextForm, true, false, true);
    Common::SetWorkValue(args, 0, 0, nullptr);
    Section_FromEvent_Damage_Description_o *desc = (Section_FromEvent_Damage_Description_o *)
            il2cpp_object_new(Section_FromEvent_Damage_Description_TypeInfo);
    desc->ctor(nullptr);
    desc->fields.pokeID = pokeID;
    desc->fields.targetPokeID = pokeID;
    desc->fields.damage = (uint16_t)Calc::QuotMaxHP(bpp, 8, true, nullptr);
    desc->fields.damageCause = DamageCause::OTHER;
    desc->fields.damageCausePokeID = pokeID;
    desc->fields.isDisplayTokuseiWindow = true;
    Common::Damage(args,&desc, nullptr);
}
// Battle Bond
uint8_t HandlerBattleBondGetFormID(uint8_t formNo, uint8_t targetFormNo) {
    return HighestMultiple(formNo, 3) + targetFormNo;
}
void HandlerBattleBondWazaHitCount(EventFactor_EventHandlerArgs_o **args, uint8_t pokeID, MethodInfo *method) {
    if (Common::GetEventVar(args, EventVar::POKEID_ATK, nullptr) != pokeID) return;
    if (Common::GetEventVar(args, EventVar::WAZAID, nullptr) != WATER_SHURIKEN_ID) return;
    uint8_t formNo = Common::GetPokeParam(args,pokeID, nullptr)->fields.m_formNo;
    if (formNo != HandlerBattleBondGetFormID(formNo, 2)) return;
    Common::RewriteEventVar(args, EventVar::HITCOUNT, 3, nullptr);
}
void HandlerBattleBondWazaPower(EventFactor_EventHandlerArgs_o **args, uint8_t pokeID, MethodInfo *method) {
    if (Common::GetEventVar(args, EventVar::POKEID_ATK, nullptr) != pokeID) return;
    if (Common::GetEventVar(args, EventVar::WAZAID, nullptr) != WATER_SHURIKEN_ID) return;
    uint8_t formNo = Common::GetPokeParam(args,pokeID, nullptr)->fields.m_formNo;
    if (formNo != HandlerBattleBondGetFormID(formNo, 2)) return;
    Common::RewriteEventVar(args, EventVar::WAZA_POWER, Common::GetEventVar(args, EventVar::WAZA_POWER,
                                                                            nullptr) + 5, nullptr);
}
void HandlerBattleBondDamageprocEndHitReal(EventFactor_EventHandlerArgs_o **args, uint8_t pokeID, MethodInfo *method) {
    if (Common::CheckShowDown(args, nullptr)) return;
    if (Common::GetKillCount(args, pokeID, nullptr) != 1) return;
    uint8_t formNo = Common::GetPokeParam(args,pokeID, nullptr)->fields.m_formNo;
    if (formNo == HandlerBattleBondGetFormID(formNo, 2)) return;
    uint8_t nextForm = HandlerBattleBondGetFormID(formNo, 2);
    BTL_POKEPARAM_o * bpp = Common::GetPokeParam(args,pokeID, nullptr);
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
    if (wazaID != SURF_ID && wazaID != DIVE_ID) return;
    BTL_POKEPARAM_o * bpp = Common::GetPokeParam(args, pokeID, nullptr);
    uint8_t formNo = bpp->fields.m_formNo;
    if (formNo != HandlerGulpMissileGetFormID(formNo, 0)) return;
    uint8_t nextForm = HandlerGulpMissileGetFormID(formNo,1 +
    ((uint32_t)bpp->GetValue(BTL_POKEPARAM_ValueID::BPP_HP, nullptr) <=
    Calc::QuotMaxHP_Zero(bpp, 2, false, nullptr)));
    if (nextForm >= PersonalSystem::GetPersonalData(bpp->GetMonsNo(nullptr), 0,
                                                    nullptr)->fields.form_max) return;
    HandlerFormChange(args, pokeID, nextForm, false, true, wazaID != DIVE_ID);
}
void HandlerGulpMissileWazaDmgReaction(EventFactor_EventHandlerArgs_o **args, uint8_t pokeID, MethodInfo *method) {
    system_load_typeinfo((void *)0x8a36);
    system_load_typeinfo((void *)0x89a6);
    system_load_typeinfo((void *)0x8919);
    system_load_typeinfo((void *)0x8a39);
    if (Common::GetEventVar(args, EventVar::POKEID_DEF, nullptr) != pokeID) return;
    if (Common::GetEventVar(args, EventVar::MIGAWARI_FLAG, nullptr)) return;
    BTL_POKEPARAM_o * bpp = Common::GetPokeParam(args, pokeID, nullptr);
    uint8_t formNo = bpp->fields.m_formNo;
    if (formNo == HandlerGulpMissileGetFormID(formNo, 0)) return;
    int32_t pokeIDAtk = Common::GetEventVar(args, EventVar::POKEID_ATK, nullptr);
    BTL_POKEPARAM_o * bppAtk = Common::GetPokeParam(args, pokeIDAtk, nullptr);
    if (!bppAtk->IsDead(nullptr)) {
        Section_FromEvent_Damage_Description_o *damageDesc = (Section_FromEvent_Damage_Description_o *)
                il2cpp_object_new(Section_FromEvent_Damage_Description_TypeInfo);
        damageDesc->ctor(nullptr);
        damageDesc->fields.pokeID = pokeID;
        damageDesc->fields.targetPokeID = pokeIDAtk;
        damageDesc->fields.damage = (uint16_t)Calc::QuotMaxHP(bppAtk, 4, true, nullptr);
        damageDesc->fields.damageCause = DamageCause::OTHER;
        damageDesc->fields.damageCausePokeID = pokeID;
        damageDesc->fields.disableDeadProcess = true;
        damageDesc->fields.isDisplayTokuseiWindow = true;
        Common::Damage(args,&damageDesc, nullptr);
        if (formNo == HandlerGulpMissileGetFormID(formNo, 1)) {
            Section_FromEvent_RankEffect_Description_o *rankEffectDesc = (Section_FromEvent_RankEffect_Description_o *)
                    il2cpp_object_new(Section_FromEvent_RankEffect_Description_TypeInfo);
            rankEffectDesc->ctor(nullptr);
            rankEffectDesc->fields.rankType = WazaRankEffect::DEFENCE;
            rankEffectDesc->fields.rankVolume = -1;
            rankEffectDesc->fields.cause = RankEffectCause::OTHER;
            rankEffectDesc->fields.pokeID = pokeID;
            rankEffectDesc->fields.targetPokeCount = 1;
            rankEffectDesc->fields.targetPokeID->m_Items[0] = (uint8_t)pokeIDAtk;
            rankEffectDesc->fields.isDisplayTokuseiWindow = false;
            rankEffectDesc->fields.isMigawariThrew = false;
            rankEffectDesc->fields.isSpFailMessageDisplay = true;
            Common::RankEffect(args,&rankEffectDesc,(MethodInfo *)0x0);
        }
        else {
            Section_AddSick_Description_o *addSickDesc = (Section_AddSick_Description_o *)
                    il2cpp_object_new(Section_AddSick_Description_TypeInfo);
            addSickDesc->ctor(nullptr);
            addSickDesc->fields.pokeID = pokeID;
            addSickDesc->fields.isDisplayTokuseiWindow = false;
            addSickDesc->fields.sickID = WazaSick::WAZASICK_MAHI;
            addSickDesc->fields.sickCont.fields.raw = Calc::MakeDefaultPokeSickCont(Sick::MAHI,
                                                                                    pokeID,
                                                                                    false,
                                                                                    nullptr).fields.raw;
            addSickDesc->fields.sickCause = SickCause::OTHER;
            addSickDesc->fields.isFailResultDisplay = false;
            addSickDesc->fields.targetPokeID = (uint8_t)pokeIDAtk;
            Common::AddSick(args, &addSickDesc, nullptr);
        }
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
    Common::RewriteEventVar(args, EventVar::ZERO_DAMAGE_FLAG, 1, nullptr);
    Common::SetWorkValue(args, 0, 1, nullptr);
}
void HandlerIceFaceWazaDmgReaction(EventFactor_EventHandlerArgs_o **args, uint8_t pokeID, MethodInfo *method) {
    if (Common::GetEventVar(args, EventVar::POKEID_DEF, nullptr) != pokeID) return;
    if (Common::GetWorkValue(args, 0, nullptr) == 0) return;
    Common::SetWorkValue(args, 0, 0, nullptr);
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

    SetAbilityFunctionTable(getFuncTable, &idx, ZEN_MODE_ID, (Il2CppMethodPointer) &ADD_ZenMode);
    SetAbilityFunctionTable(getFuncTable, &idx, STANCE_CHANGE_ID, (Il2CppMethodPointer) &ADD_StanceChange);
    SetAbilityFunctionTable(getFuncTable, &idx, SHIELDS_DOWN_ID, (Il2CppMethodPointer) &ADD_ShieldsDown);
    SetAbilityFunctionTable(getFuncTable, &idx, SCHOOLING_ID, (Il2CppMethodPointer) &ADD_Schooling);
    SetAbilityFunctionTable(getFuncTable, &idx, DISGUISE_ID, (Il2CppMethodPointer) &ADD_Disguise);
    SetAbilityFunctionTable(getFuncTable, &idx, BATTLE_BOND_ID, (Il2CppMethodPointer) &ADD_BattleBond);
    SetAbilityFunctionTable(getFuncTable, &idx, POWER_CONSTRUCT_ID, (Il2CppMethodPointer) &ADD_PowerConstruct);
    SetAbilityFunctionTable(getFuncTable, &idx, GULP_MISSILE_ID, (Il2CppMethodPointer) &ADD_GulpMissile);
    SetAbilityFunctionTable(getFuncTable, &idx, ICE_FACE_ID, (Il2CppMethodPointer) &ADD_IceFace);
    SetAbilityFunctionTable(getFuncTable, &idx, HUNGER_SWITCH_ID, (Il2CppMethodPointer) &ADD_HungerSwitch);

    return getFuncTable;
}