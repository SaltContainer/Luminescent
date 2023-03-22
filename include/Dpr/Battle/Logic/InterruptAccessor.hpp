#pragma once 

#include "il2cpp.hpp"

namespace Dpr
{
    namespace Battle
    {
        namespace Logic
        {
            struct InterruptAccessor_c;

            struct InterruptAccessor_Fields {
                uint8_t m_interrupt;
            };

            struct InterruptAccessor_o {
                InterruptAccessor_c *klass;
                void *monitor;
                InterruptAccessor_Fields fields;

                bool IsRequested(uint8_t _interrupt, MethodInfo *method);
            };
        }
    }
}