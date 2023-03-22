#pragma once

#include "il2cpp.hpp"
#include "Dpr/Battle/Logic/BTL_SICKCONT.hpp"
#include "BTL_SICKCONT.hpp"

namespace Dpr
{
    namespace Battle
    {
        namespace Logic
        {
            struct SICKCONT
            {
                // 20d47d0
                static BTL_SICKCONT_o MakePermanent(uint8_t causePokeID, MethodInfo * method);
                // 20d4680
                static BTL_SICKCONT_o MakeTurn(uint8_t causePokeID, uint8_t turns, MethodInfo * method);
                static BTL_SICKCONT_o MakeTurnParam(uint8_t causePokeID, uint8_t turns, uint16_t param, MethodInfo *method);
            };
        }
    }
}
