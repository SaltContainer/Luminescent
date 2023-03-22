#pragma once 

#include "il2cpp.hpp"
#include "Dpr/Battle/Logic/StrParam.hpp"

namespace Dpr
{
    namespace Battle
    {
        namespace Logic
        {
            struct Section_FromEvent_FormChange_Description_c;

            struct Section_FromEvent_FormChange_Description_Fields {
                uint8_t pokeID;
                uint8_t formNo;
                bool isDontResetFormByOut;
                bool isEnableInCaseOfDead;
                bool isDisplayTokuseiWindow;
                bool isDisplayChangeEffect;
                struct StrParam_o* successMessage;
            };

            struct Section_FromEvent_FormChange_Description_o {
                void ctor(MethodInfo *method);

                Section_FromEvent_FormChange_Description_c *klass;
                void *monitor;
                Section_FromEvent_FormChange_Description_Fields fields;
            };

            extern void *Section_FromEvent_FormChange_Description_TypeInfo;
        }
    }
}
