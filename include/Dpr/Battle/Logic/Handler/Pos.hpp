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
                struct Pos
                {
                    static void common_removePosEffect(EventFactor_EventHandlerArgs_o **args, uint8_t myPos, MethodInfo *method);
                };
            }
        }
    }
}