#pragma once

#include "il2cpp.hpp"
#include "BTL_SICKCONT.hpp"

namespace Dpr
{
    namespace Battle
    {
        namespace Logic
        {
            struct SICKCONT {
                static BTL_SICKCONT_o MakeTurnParam(uint8_t causePokeID, uint8_t turns, uint16_t param, MethodInfo *method);
            };
        }
    }
}