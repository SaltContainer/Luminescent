#pragma once

#include "il2cpp.hpp"
#include "Pml/PokePara/CoreParam.h"
#include "System/Array.hpp"

namespace Dpr
{
    namespace Battle
    {
        namespace Logic
        {
            struct BTL_POKEPARAM_CORE_PARAM_o;
            struct BTL_POKEPARAM_BASE_PARAM_o;
            struct BTL_POKEPARAM_VARIABLE_PARAM_o;
            struct BTL_POKEPARAM_DORYOKU_PARAM_o;
            struct BTL_POKEPARAM_WAZA_SET_array;
            struct BTL_POKEPARAM_WAZADMG_REC_array_array;
            struct FieldStatus_o;

            struct BTL_POKEPARAM_Fields {
                BTL_POKEPARAM_CORE_PARAM_o* m_coreParam;
                BTL_POKEPARAM_BASE_PARAM_o* m_baseParam;
                BTL_POKEPARAM_VARIABLE_PARAM_o* m_varyParam;
                BTL_POKEPARAM_DORYOKU_PARAM_o* m_doryokuParam;
                BTL_POKEPARAM_WAZA_SET_array* m_waza;
                uint16_t m_tokusei;
                uint16_t m_weight;
                uint8_t m_wazaCnt;
                uint8_t m_formNo;
                uint8_t m_friendship;
                uint8_t m_criticalRank;
                uint8_t m_usedWazaCount;
                uint8_t m_prevWazaType;
                uint8_t m_spActPriority;
                uint16_t m_turnCount;
                uint16_t m_appearedTurn;
                uint16_t m_wazaContCounter;
                uint8_t m_prevTargetPos;
                int32_t m_prevActWazaID;
                int32_t m_prevSelectWazaID;
                int32_t m_prevDamagedWaza;
                System::Array<uint8_t> * m_turnFlag;
                System::Array<uint8_t> * m_contFlag;
                System::Array<uint8_t> * m_permFlag;
                System::Array<uint8_t> * m_counter;
                System::Array<uint32_t> * m_permCounter;
                BTL_POKEPARAM_WAZADMG_REC_array_array* m_wazaDamageRec;
                System::Array<uint8_t> * m_dmgrecCount;
                uint8_t m_dmgrecTurnPtr;
                uint8_t m_dmgrecPtr;
                uint16_t m_migawariHP;
                int32_t m_combiWazaID;
                uint8_t m_combiPokeID;
                FieldStatus_o* m_fldSim;
            };

            struct BTL_POKEPARAM_c;

            struct BTL_POKEPARAM_o
            {
                bool CONFRONT_REC_IsMatch(uint8_t pokeID, MethodInfo *method);
                uint16_t GetItem(MethodInfo *method);
                uint8_t GetFriendship(MethodInfo *method);
                uint16_t GetMonsNo(MethodInfo *method);
                uint32_t GetPokeSick(MethodInfo *method);
                Pml::PokePara::CoreParam * GetSrcDataConst(MethodInfo *method);
                int32_t GetValue(int32_t valueID,MethodInfo *method);
                bool HENSIN_Check(MethodInfo *method);
                bool IsDead(MethodInfo *method);


                BTL_POKEPARAM_c *klass;
                void *monitor;
                BTL_POKEPARAM_Fields fields;
            };
            enum BTL_POKEPARAM_ValueID {
                BPP_VALUE_NULL,
                BPP_ATTACK_RANK,
                BPP_DEFENCE_RANK,
                BPP_SP_ATTACK_RANK,
                BPP_SP_DEFENCE_RANK,
                BPP_AGILITY_RANK,
                BPP_HIT_RATIO,
                BPP_AVOID_RATIO,
                BPP_ATTACK,
                BPP_DEFENCE,
                BPP_SP_ATTACK,
                BPP_SP_DEFENCE,
                BPP_AGILITY,
                BPP_HP,
                BPP_HP_BEFORE_G,
                BPP_MAX_HP,
                BPP_MAX_HP_BEFORE_G,
                BPP_LEVEL,
                BPP_TOKUSEI,
                BPP_TOKUSEI_EFFECTIVE,
                BPP_SEX,
                BPP_SEIKAKU,
                BPP_PERSONAL_RAND,
                BPP_EXP,
                BPP_MONS_POW,
                BPP_MONS_AGILITY,
                BPP_RANKVALUE_START = 1,
                BPP_RANKVALUE_END = 7,
                BPP_RANKVALUE_RANGE = 7
            };
        }
    }
}