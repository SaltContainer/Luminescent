#pragma once 

#include "il2cpp.hpp"
#include "PosEffect.hpp"

namespace Dpr
{
    namespace Battle
    {
        namespace Logic
        {
            struct PosEffectStatus_Data_c;

            struct PosEffectStatus_Data_Fields {
                uint8_t pos;
                int32_t posEffect;
                bool isEffective;
                struct PosEffect_EffectParam_o effectParam;
            };

            struct PosEffectStatus_Data_o {
                PosEffectStatus_Data_c *klass;
                void *monitor;
                PosEffectStatus_Data_Fields fields;
            };

            struct PosEffectStatus_c;

            struct PosEffectStatus_Fields {
                struct PosEffectStatus_Data_o* m_data;
            };

            struct PosEffectStatus_o {
                PosEffectStatus_c *klass;
                void *monitor;
                PosEffectStatus_Fields fields;
            };

            struct PosEffectStatus_array {
                Il2CppObject obj;
                Il2CppArrayBounds *bounds;
                il2cpp_array_size_t max_length;
                PosEffectStatus_o* m_Items[65535];
            };

            struct PosEffectStatus_array_array {
                Il2CppObject obj;
                Il2CppArrayBounds *bounds;
                il2cpp_array_size_t max_length;
                PosEffectStatus_array* m_Items[65535];
            };

            extern void *PosEffectStatus_Data_TypeInfo;
            extern void *PosEffectStatus_TypeInfo;
        }
    }
}