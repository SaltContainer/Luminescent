#pragma once

#include "il2cpp.hpp"
#include "PokeAction.hpp"

namespace Dpr
{
    namespace Battle
    {
        namespace Logic
        {
            struct EventLauncher_c;

            struct EventLauncher_Fields {
                struct Dpr_Battle_Logic_MainModule_o* m_pMainModule;
                struct Dpr_Battle_Logic_EventSystem_o* m_pEventSystem;
                struct Dpr_Battle_Logic_BattleEnv_o* m_pBattleEnv;
            };

            struct EventLauncher_o {
                EventLauncher_c *klass;
                void *monitor;
                EventLauncher_Fields fields;

                void Event_ActProcCanceled(PokeAction_o *action, MethodInfo *method);
                void Event_ActProcEnd(BTL_POKEPARAM_o *bpp, int32_t actionCmd, MethodInfo *method);
                void Event_ActProcStart(PokeAction_o *action, MethodInfo *method);
            };
        }
    }
}