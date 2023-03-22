#pragma once

#include "il2cpp.hpp"
#include "PokeActionParam_Fight.hpp"

namespace Dpr
{
    namespace Battle
    {
        namespace Logic
        {
            struct PokeAction_c;

            struct PokeAction_Fields {
                struct BTL_POKEPARAM_o* bpp;
                int32_t actionCategory;
                struct PokeActionParam_Fight_o* actionParam_Fight;
                struct PokeActionParam_Item_o* actionParam_Item;
                struct PokeActionParam_PokeChange_o* actionParam_PokeChange;
                struct ActionDesc_o* actionDesc;
                uint32_t priority;
                uint8_t clientID;
                bool fDone;
                bool fIntrCheck;
                bool fRecalcPriority;
            };

            struct PokeAction_o {
                PokeAction_c *klass;
                void *monitor;
                PokeAction_Fields fields;
            };

            struct PokeAction_array {
                Il2CppObject obj;
                Il2CppArrayBounds *bounds;
                il2cpp_array_size_t max_length;
                PokeAction_o* m_Items[65535];
            };

            struct PokeAction {
                static int32_t GetWazaID(PokeAction_o *action, MethodInfo *method);
            };
        }
    }
}