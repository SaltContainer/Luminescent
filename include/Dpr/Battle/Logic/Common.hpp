#pragma once

#include "il2cpp.hpp"
#include "Dpr/Battle/Logic/BTL_POKEPARAM.hpp"
#include "Dpr/Battle/Logic/EventFactor.hpp"
#include "Dpr/Battle/Logic/Section_FromEvent_Message.hpp"
#include "Dpr/Battle/Logic/Section_FromEvent_FormChange.hpp"
#include "Dpr/Battle/Logic/Section_FieldEffect_Add_Description.hpp"
#include "Dpr/Battle/Logic/Section_FromEvent_FieldEffect_Remove_Description.hpp"
#include "PokeAction.hpp"
#include "Section_AddSick.hpp"
#include "Section_CureSick.hpp"
#include "Section_FromEvent_Damage.hpp"
#include "Section_FromEvent_FormChange.hpp"
#include "Section_FromEvent_PosEffect_Add.hpp"
#include "Section_FromEvent_RankEffect.hpp"
#include "Section_FromEvent_RankReset.hpp"

namespace Dpr
{
    namespace Battle
    {
        namespace Logic
        {
            struct Common
            {
                // 1d0a260
                static bool CheckFieldEffect(EventFactor_EventHandlerArgs_o ** args, int32_t * effType, MethodInfo * method);
                // 1d0b730
                static bool AddFieldEffect(EventFactor_EventHandlerArgs_o ** args, Section_FieldEffect_Add_Description_o ** desc, MethodInfo * method);
                // 1d0b7c0
                static bool RemoveFieldEffect(EventFactor_EventHandlerArgs_o * * args, Section_FromEvent_FieldEffect_Remove_Description_o ** desc, MethodInfo * method);

                static bool AddPosEffect(EventFactor_EventHandlerArgs_o **args, Section_FromEvent_PosEffect_Add_Description_o **desc, MethodInfo *method);
                static bool AddSick(EventFactor_EventHandlerArgs_o **args, Section_AddSick_Description_o **desc,MethodInfo *method);
                static bool CheckShowDown(EventFactor_EventHandlerArgs_o **args, MethodInfo *method);
                static bool CureSick(EventFactor_EventHandlerArgs_o **args, Section_CureSick_Description_o **desc, MethodInfo *method);
                static bool Damage(EventFactor_EventHandlerArgs_o **args, Section_FromEvent_Damage_Description_o **desc,MethodInfo *method);
                static uint8_t DecideWazaTargetAuto(EventFactor_EventHandlerArgs_o **args, uint8_t pokeID, int32_t wazano, MethodInfo *method);
                static bool FormChange(EventFactor_EventHandlerArgs_o **args, Section_FromEvent_FormChange_Description_o **desc,MethodInfo *method);
                static int32_t GetEventVar(EventFactor_EventHandlerArgs_o **args, uint16_t label, MethodInfo *method);
                static void * GetEventVarAddress(EventFactor_EventHandlerArgs_o **args, uint16_t label, MethodInfo *method);
                static uint8_t GetFrontPokeID(EventFactor_EventHandlerArgs_o **args, uint8_t *pos, MethodInfo *method);
                static uint32_t GetKillCount(EventFactor_EventHandlerArgs_o **args, uint8_t pokeID, MethodInfo *method);
                static uint8_t GetLocalWeather(EventFactor_EventHandlerArgs_o **args, uint8_t pokeID, MethodInfo *method);
                static BTL_POKEPARAM_o * GetPokeParam(EventFactor_EventHandlerArgs_o **args, uint8_t pokeID, MethodInfo *method);
                static uint16_t GetSubID(EventFactor_EventHandlerArgs_o **args,MethodInfo *method);
                static bool IsFriendPokeID(EventFactor_EventHandlerArgs_o **args, uint8_t pokeID1, uint8_t pokeID2, MethodInfo *method);
                static void Message(EventFactor_EventHandlerArgs_o ** args, Section_FromEvent_Message::Description_o ** desc, MethodInfo * method);
                static bool CheckUnbreakablePokeItem(uint16_t monsno, uint16_t itemID, MethodInfo *method);
                // 1d0a010
                static int32_t PokeIDtoOpponentSide (EventFactor_EventHandlerArgs_o ** args, uint8_t * pokeID, MethodInfo * method);
                // 1d09d20
                static int32_t GetWorkValue(EventFactor_EventHandlerArgs_o ** args, uint8_t workIdx, MethodInfo * method);
                // 1d09da0
                static void SetWorkValue(EventFactor_EventHandlerArgs_o ** args, uint8_t workIdx, int32_t value, MethodInfo * method);
                // 1d0a060
                static uint8_t GetGround(EventFactor_EventHandlerArgs_o ** args, MethodInfo * method);
                // 1d0a090
                static void AttachSkipCheckHandler(EventFactor_EventHandlerArgs_o ** args, EventFactor_SkipCheckHandler_o ** handler, MethodInfo * method);
                // 1d0a0c0
                static void DetachSkipCheckHandler(EventFactor_EventHandlerArgs_o ** args, MethodInfo * method);
                static void MulEventVar(EventFactor_EventHandlerArgs_o **args, uint16_t label, int32_t value, MethodInfo *method);
                static uint8_t PokeIDtoPokePos(EventFactor_EventHandlerArgs_o **args, uint8_t *pokeID, MethodInfo *method);
                static bool RankEffect(EventFactor_EventHandlerArgs_o **args, Section_FromEvent_RankEffect_Description_o **desc, MethodInfo *method);
                static bool RankReset(EventFactor_EventHandlerArgs_o **args, Section_FromEvent_RankReset_Description_o **desc, MethodInfo *method);
                static bool RewriteEventVar(EventFactor_EventHandlerArgs_o **args, uint16_t label, int32_t value, MethodInfo *method);
                static PokeAction_o * SearchByPokeID(EventFactor_EventHandlerArgs_o **args, uint8_t pokeID, bool isSkipGStart, bool isSkipNull, MethodInfo *method);
            };

            extern void * Common_TypeInfo;

            // 4c6b3f8
            extern MethodInfo * Method_Common_Katayaburi_SkipCheck;
        }
    }
}
