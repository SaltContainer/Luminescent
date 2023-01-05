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
                struct Tokusei
                {
                    static void handler_AddSickFailCommon(EventFactor_EventHandlerArgs_o **args, uint8_t pokeID, MethodInfo *method);
                    static void handler_Kinchoukan_MemberIn(EventFactor_EventHandlerArgs_o **args, uint8_t pokeID, MethodInfo *method);
                };
            }
        }
    }
}