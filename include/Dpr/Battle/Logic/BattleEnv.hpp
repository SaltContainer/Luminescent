#pragma once 

#include "il2cpp.hpp"
#include "PosPoke.hpp"

namespace Dpr
{
    namespace Battle
    {
        namespace Logic
        {
            struct BattleEnv_c;
            
            struct BattleEnv_Fields {
                struct POKECON_o* m_pokecon;
                struct FieldStatus_o* m_fieldStatus;
                struct SideEffectManager_o* m_sideEffectManager;
                struct PosEffectManager_o* m_posEffectManager;
                struct EventFactorContainer_o* m_eventFactorContainer;
                struct PosPoke_o* m_posPoke;
                struct DeadRec_o* m_deadRec;
                struct WazaRec_o* m_wazaRec;
                struct AffCounter_o* m_affCounter;
                struct ActionRecorder_o* m_actionRecorder;
                struct ActionSerialNoManager_o* m_actionSerialNoManager;
                struct TimeLimit_o* m_timeLimit;
                struct GRightsManager_o* m_gRightsManager;
                struct GGauge_array* m_gGauge;
                struct RaidBattleStatus_o* m_raidBattleStatus;
                struct BattleFlags_o* m_flags;
                struct BattleCounter_o* m_counter;
                struct EscapeInfo_o* m_escapeInfo;
                struct WazaParam_o* m_lastExecutedWaza;
                struct TamaHiroiData_o* m_tamaHiroiData;
            };
            
            struct BattleEnv_o {
                BattleEnv_c *klass;
                void *monitor;
                BattleEnv_Fields fields;
            };
        }
    }
}