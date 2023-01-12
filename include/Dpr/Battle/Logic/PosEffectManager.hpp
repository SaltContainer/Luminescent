#pragma once 

#include "il2cpp.hpp"
#include "PosEffectStatus.hpp"

namespace Dpr
{
    namespace Battle
    {
        namespace Logic
        {
            struct PosEffectManager_c;

            struct PosEffectManager_Fields {
                struct PosEffectStatus_array_array* m_posEffects;
            };

            struct PosEffectManager_o {
                PosEffectManager_c *klass;
                void *monitor;
                PosEffectManager_Fields fields;
            };
        }
    }
}