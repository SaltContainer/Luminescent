#pragma once

#include "il2cpp.hpp"
#include "Dpr/Battle/Logic/BTL_POKEPARAM.hpp"
#include "Dpr/Battle/Logic/BTL_SICKCONT.hpp"

namespace Dpr
{
    namespace Battle
    {
        namespace Logic
        {
            struct Calc
            {
                static uint32_t GetRand(uint32_t range, MethodInfo * method);
                static bool IsBasicSickID(int32_t sickID, MethodInfo * method);
                static uint32_t RandRange(uint32_t min, uint32_t max, MethodInfo *method);
                static bool IsOccurPer(uint32_t per, MethodInfo *method);
                static BTL_SICKCONT_o MakeDefaultPokeSickCont(uint32_t sick, uint8_t causePokeID, bool isCantUseRand, MethodInfo *method);
                static uint32_t QuotMaxHP(BTL_POKEPARAM_o *bpp, uint32_t denom, bool useBeforeGParam, MethodInfo *method);
                static uint32_t QuotMaxHP_Zero(BTL_POKEPARAM_o *bpp, uint32_t denom, bool useBeforeGParam, MethodInfo *method);
            };
        }
    }
}
