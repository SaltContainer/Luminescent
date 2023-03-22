#pragma once 

#include "il2cpp.hpp"
#include "BTL_POKEPARAM.hpp"

namespace Dpr
{
    namespace Battle
    {
        namespace Logic
        {
            struct PokeSet_c;

            struct PokeSet_Fields {
                struct BTL_POKEPARAM_array* m_bpp;
                struct System_UInt16_array* m_damage;
                struct System_UInt16_array* m_migawariDamage;
                struct System_Byte_array* m_damageType;
                struct System_UInt16_array* m_sortWork;
                uint8_t m_count;
                uint8_t m_countMax;
                uint8_t m_getIdx;
                uint8_t m_targetPosCount;
            };

            struct PokeSet_o {
                BTL_POKEPARAM_o * SeekNext(MethodInfo *method);
                void SeekStart(MethodInfo *method);
                void Remove(BTL_POKEPARAM_o *bpp, MethodInfo *method);

                PokeSet_c *klass;
                void *monitor;
                PokeSet_Fields fields;
            };
        }
    }
}