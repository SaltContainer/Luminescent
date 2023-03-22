#pragma once 

#include "il2cpp.hpp"
#include "Dpr/Battle/Logic/StrParam.hpp"

namespace Dpr
{
    namespace Battle
    {
        namespace Logic
        {
            struct Section_FromEvent_RankEffect_Description_c;

            struct Section_FromEvent_RankEffect_Description_Fields {
                uint8_t pokeID;
                uint8_t targetPokeCount;
                struct System_Byte_array* targetPokeID;
                int32_t rankType;
                int8_t rankVolume;
                uint8_t cause;
                uint16_t itemID;
                uint32_t effectSerial;
                bool isDisplayTokuseiWindow;
                bool isStandardMessageDisable;
                bool isSpFailMessageDisplay;
                bool byWazaEffect;
                bool isPreEffectMessageEnable;
                uint8_t effectViewType;
                bool isMigawariThrew;
                struct StrParam_o* message;
            };

            struct Section_FromEvent_RankEffect_Description_o {
                void ctor(MethodInfo *method);

                Section_FromEvent_RankEffect_Description_c *klass;
                void *monitor;
                Section_FromEvent_RankEffect_Description_Fields fields;
            };

            extern void *Section_FromEvent_RankEffect_Description_TypeInfo;
        }
    }
}