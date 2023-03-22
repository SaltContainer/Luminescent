#pragma once

#include "il2cpp.hpp"
#include "BTL_POKEPARAM.hpp"
#include "StrParam.hpp"

namespace Dpr
{
    namespace Battle
    {
        namespace Logic
        {
            struct ServerCommandPutter_c;

            struct ServerCommandPutter_Fields {
                struct Dpr_Battle_Logic_MainModule_o* m_pMainModule;
                struct Dpr_Battle_Logic_BattleEnv_o* m_pBattleEnv;
                struct Dpr_Battle_Logic_ServerCommandQueue_o* m_pQueue;
                struct Dpr_Battle_Logic_ServerCommandExecutor_o* m_pExecutor;
            };

            struct ServerCommandPutter_o
            {
                ServerCommandPutter_c *klass;
                void *monitor;
                ServerCommandPutter_Fields fields;

                void IncBattleCount(uint8_t counterID, MethodInfo *method);
                void InsertWazaInfo(uint8_t pokeID, bool isTokuseiWindowDisplay, StrParam_o **message, MethodInfo *method);
                void SetBppCounter(BTL_POKEPARAM_o *poke, int32_t counterID, uint8_t value, MethodInfo *method);
                void SetContFlag(BTL_POKEPARAM_o *poke, int32_t flag, MethodInfo *method);
            };
        }
    }
}