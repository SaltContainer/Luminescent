#pragma once 

#include "il2cpp.hpp"

namespace Dpr
{
    namespace Battle
    {
        namespace Logic
        {
            struct PosPoke_c;

            struct PosPoke_Fields {
                struct Dpr_Battle_Logic_PosPoke_State_array* m_state;
                struct Dpr_Battle_Logic_BtlPokePos_array* m_lastPosInst;
                uint8_t m_lastPosDmy;
            };

            struct PosPoke_o {
                PosPoke_c *klass;
                void *monitor;
                PosPoke_Fields fields;

                bool IsExist(uint8_t pokeID, MethodInfo *method);
            };
        }
    }
}