#pragma once

#include "il2cpp.hpp"
#include "Section.hpp"

namespace Dpr
{
    namespace Battle
    {
        namespace Logic
        {
            struct Section_InterruptAction_c;

            struct Section_InterruptAction_Fields {
                Section_Fields super;
            };

            struct Section_InterruptAction_o {
                Section_InterruptAction_c *klass;
                void *monitor;
                Section_InterruptAction_Fields fields;

                void processAction(PokeAction_o *pokeAction, MethodInfo *method);
            };
        }
    }
}