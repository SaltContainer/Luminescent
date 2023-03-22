#pragma once

#include "il2cpp.hpp"

namespace Dpr
{
    namespace Battle
    {
        namespace Logic
        {
            struct PokeActionParam_Fight_c;

            struct PokeActionParam_Fight_Fields {
                uint8_t targetPos;
                uint8_t aimTargetID;
                int32_t waza;
                bool gFlag;
                bool forbidGWaza;
                bool forceGWaza;
            };

            struct PokeActionParam_Fight_o {
                PokeActionParam_Fight_c *klass;
                void *monitor;
                PokeActionParam_Fight_Fields fields;
            };
        }
    }
}