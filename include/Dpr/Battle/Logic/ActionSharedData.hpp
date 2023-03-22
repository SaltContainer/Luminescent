#pragma once 

#include "il2cpp.hpp"

namespace Dpr
{
    namespace Battle
    {
        namespace Logic
        {
            struct ActionSharedData_c;

            struct ActionSharedData_Fields {
                struct WazaMessageParam_o* wazaMessageParam;
                struct WazaEffectParams_o* wazaEffectParams;
                struct WazaRobParam_o* magicCoatParam;
                bool isWazaFailMessageDisplayed;
                bool isWazaFailMessageRoundUp;
                bool isInterruptAction;
            };

            struct ActionSharedData_o {
                ActionSharedData_c *klass;
                void *monitor;
                ActionSharedData_Fields fields;
            };
        }
    }
}