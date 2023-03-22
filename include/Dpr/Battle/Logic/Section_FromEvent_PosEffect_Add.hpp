#pragma once 

#include "il2cpp.hpp"
#include "Dpr/Battle/Logic/PosEffect.hpp"

namespace Dpr
{
    namespace Battle
    {
        namespace Logic
        {
            struct Section_FromEvent_PosEffect_Add_Description_c;

            struct Section_FromEvent_PosEffect_Add_Description_Fields {
                uint8_t userPokeID;
                uint8_t pos;
                int32_t effect;
                struct PosEffect_EffectParam_o effectParam;
                bool isSkipHpRecoverSpFailCheck;
            };

            struct Section_FromEvent_PosEffect_Add_Description_o {
                void ctor(MethodInfo *method);

                Section_FromEvent_PosEffect_Add_Description_c *klass;
                void *monitor;
                Section_FromEvent_PosEffect_Add_Description_Fields fields;
            };

            extern void * Section_FromEvent_PosEffect_Add_Description_TypeInfo;
        }
    }
}