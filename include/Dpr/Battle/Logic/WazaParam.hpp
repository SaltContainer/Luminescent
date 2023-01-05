#pragma once 

#include "il2cpp.hpp"
#include "PokeTypePair.hpp"

namespace Dpr
{
    namespace Battle
    {
        namespace Logic
        {
            struct WazaParam_c;

            struct WazaParam_Fields {
                int32_t wazaID;
                int32_t orgWazaID;
                int32_t gSrcWazaID;
                struct PokeTypePair_o userType;
                uint8_t wazaType;
                int32_t damageType;
                bool touchFlag;
                int32_t targetType;
                int32_t wazaPri;
                uint16_t wazaPower;
                bool fMagicCoat;
                bool fYokodori;
                bool fItazuraGokoro;
                bool fInvalidMessageDisable;
            };

            struct WazaParam_o {
                bool canInvalidMessageDisplay(uint32_t count, MethodInfo *method);

                WazaParam_c *klass;
                void *monitor;
                WazaParam_Fields fields;
            };
        }
    }
}