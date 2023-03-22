#pragma once 

#include "il2cpp.hpp"
#include "Dpr/Battle/Logic/StrParam.hpp"

namespace Dpr
{
    namespace Battle
    {
        namespace Logic
        {
            struct Section_FromEvent_Damage_Description_c;

            struct Section_FromEvent_Damage_Description_Fields {
                uint8_t pokeID;
                uint8_t targetPokeID;
                uint16_t damage;
                uint8_t damageCause;
                uint8_t damageCausePokeID;
                bool canHidePokeAvoid;
                bool disableDeadProcess;
                bool isDisplayTokuseiWindow;
                uint8_t exEffectPlayMode;
                uint16_t exEffectNo;
                uint8_t exEffectPos_from;
                uint8_t exEffectPos_to;
                struct StrParam_o* successMessage;
            };

            struct Section_FromEvent_Damage_Description_o {
                void ctor(MethodInfo *method);

                Section_FromEvent_Damage_Description_c *klass;
                void *monitor;
                Section_FromEvent_Damage_Description_Fields fields;
            };

            extern void *Section_FromEvent_Damage_Description_TypeInfo;
        }
    }
}