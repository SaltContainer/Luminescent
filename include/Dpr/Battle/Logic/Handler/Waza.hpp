#pragma once

#include "il2cpp.hpp"
#include "System/Array.hpp"
#include "Dpr/Battle/Logic/EventFactor.hpp"

namespace Dpr
{
    namespace Battle
    {
        namespace Logic
        {
            namespace Handler
            {
                struct Waza
                {
                    static System::Array<EventFactor_EventHandlerTable_o *> * ADD_KumoNoSu(MethodInfo *method);
                    static void common_feint_proc(EventFactor_EventHandlerArgs_o **args, uint8_t pokeID, uint16_t strID, MethodInfo *method);
                    static void common_Korogaru_Unlock(EventFactor_EventHandlerArgs_o **args, uint8_t pokeID, MethodInfo *method);
                    static void handler_Jisin_checkHide(EventFactor_EventHandlerArgs_o **args, uint8_t pokeID, MethodInfo *method);
                    static void handler_Jisin_damage(EventFactor_EventHandlerArgs_o **args, uint8_t pokeID, MethodInfo *method);
                    static void handler_MetalBurst_Target(EventFactor_EventHandlerArgs_o **args, uint8_t pokeID, MethodInfo *method);
                    static void handler_Tobigeri_NoEffect(EventFactor_EventHandlerArgs_o **args, uint8_t pokeID, MethodInfo *method);
                    static void SleepGuardSideEffects(EventFactor_EventHandlerArgs_o **args, uint8_t pokeID, bool wakeFlag, MethodInfo *method);
                };
            }
        }
    }
}