#pragma once

#include "il2cpp.hpp"
#include "Dpr/Battle/Logic/BTL_POKEPARAM.hpp"
#include "Dpr/Battle/Logic/EventFactor.hpp"
#include "Dpr/Battle/Logic/Section_FromEvent_Message.hpp"
#include "Section_FromEvent_Damage.hpp"

namespace Dpr
{
    namespace Battle
    {
        namespace Logic
        {
            struct Common
            {
                static bool CheckUnbreakablePokeItem(uint16_t monsno, uint16_t itemID, MethodInfo *method);
                static bool Damage(EventFactor_EventHandlerArgs_o **args, Section_FromEvent_Damage_Description_o **desc,MethodInfo *method);
                static uint8_t DecideWazaTargetAuto(EventFactor_EventHandlerArgs_o **args, uint8_t pokeID, int32_t wazano, MethodInfo *method);
                static int32_t GetEventVar(EventFactor_EventHandlerArgs_o **args, uint16_t label, MethodInfo *method);
                static void * GetEventVarAddress(EventFactor_EventHandlerArgs_o **args, uint16_t label, MethodInfo *method);
                static BTL_POKEPARAM_o * GetPokeParam(EventFactor_EventHandlerArgs_o **args, uint8_t pokeID, MethodInfo *method);
                static void Message(EventFactor_EventHandlerArgs_o ** args, Section_FromEvent_Message::Description_o ** desc, MethodInfo * method);
                static void MulEventVar(EventFactor_EventHandlerArgs_o **args, uint16_t label, int32_t value, MethodInfo *method);
                static bool RewriteEventVar(EventFactor_EventHandlerArgs_o **args, uint16_t label, int32_t value, MethodInfo *method);
            };

            extern void * Common_TypeInfo;
        }
    }
}