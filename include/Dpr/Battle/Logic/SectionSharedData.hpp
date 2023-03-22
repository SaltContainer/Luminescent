#pragma once 

#include "il2cpp.hpp"
#include "InterruptAccessor.hpp"

namespace Dpr
{
    namespace Battle
    {
        namespace Logic
        {
            struct SectionSharedData_c;

            struct SectionSharedData_Fields {
                struct Dpr_Battle_Logic_ActionSharedDataStack_o* m_actionSharedDataStack;
                struct InterruptAccessor_o* m_interruptAccessor;
                struct Dpr_Battle_Logic_PartyAllDeadRecorder_o* m_partyAllDeadRecorder;
                struct Dpr_Battle_Logic_PokemonBattleInRegister_o* m_pokemonBattleInRegister;
                struct System_UInt16_array* m_itemChangeCounter;
                uint8_t m_turnCheckStep;
                uint64_t m_turnFlag;
            };

            struct SectionSharedData_o {
                SectionSharedData_c *klass;
                void *monitor;
                SectionSharedData_Fields fields;
            };
        }
    }
}