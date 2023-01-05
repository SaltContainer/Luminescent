#pragma once

#include "il2cpp.hpp"
#include "Dpr/Battle/Logic/EventFactor.hpp"

namespace Dpr
{
    namespace Battle
    {
        namespace Logic
        {
            namespace Handler
            {
                struct Waza
                {
                    static void SleepGuardSideEffects(EventFactor_EventHandlerArgs_o **args, uint8_t pokeID, bool wakeFlag, MethodInfo *method);
                    static void common_feint_proc(EventFactor_EventHandlerArgs_o **args, uint8_t pokeID, uint16_t strID, MethodInfo *method);
                };
            }
        }
    }
}