#pragma once

#include "il2cpp.hpp"
#include "Dpr/Battle/Logic/BTL_POKEPARAM.hpp"

namespace Dpr
{
    namespace Battle
    {
        namespace Logic
        {
            struct Calc
            {
                static uint32_t GetRand(uint32_t range, MethodInfo * method);
                static uint32_t QuotMaxHP(BTL_POKEPARAM_o *bpp, uint32_t denom, bool useBeforeGParam, MethodInfo *method);
            };
        }
    }
}