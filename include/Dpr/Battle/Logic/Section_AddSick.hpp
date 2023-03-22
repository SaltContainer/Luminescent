#pragma once 

#include "il2cpp.hpp"
#include "Dpr/Battle/Logic/BTL_SICKCONT.hpp"
#include "Dpr/Battle/Logic/StrParam.hpp"

namespace Dpr
{
    namespace Battle
    {
        namespace Logic
        {
            struct Section_AddSick_Description_c;

            struct Section_AddSick_Description_Fields {
                uint8_t pokeID;
                uint8_t targetPokeID;
                int32_t sickID;
                struct BTL_SICKCONT_o sickCont;
                uint8_t sickCause;
                uint8_t overWriteMode;
                bool isDisplayTokuseiWindow;
                bool isFailResultDisplay;
                bool isEffectDisplay;
                bool isStandardMessageDisable;
                bool isItemReactionDisable;
                bool isEffectiveToDeadPoke;
                struct StrParam_o* specialMessage;
            };

            struct Section_AddSick_Description_o {
                void ctor(MethodInfo *method);

                Section_AddSick_Description_c *klass;
                void *monitor;
                Section_AddSick_Description_Fields fields;
            };

            extern void *Section_AddSick_Description_TypeInfo;
        }
    }
}