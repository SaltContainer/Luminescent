#pragma once 

#include "il2cpp.hpp"
#include "PokeAction.hpp"
#include "Section.hpp"

namespace Dpr
{
    namespace Battle
    {
        namespace Logic
        {
            struct Section_ProcessActionCore_Fields{
                Section_Fields super;
            };

            struct Section_ProcessActionCore_c;

            struct Section_ProcessActionCore_o {
                Section_ProcessActionCore_c *klass;
                void *monitor;
                Section_ProcessActionCore_Fields fields;

                void action(PokeAction_o *pokeAction, MethodInfo *method);
                void action_Cheer(PokeAction_o *pPokeAction, MethodInfo *method);
                void reinforceRaidBoss(PokeAction_o *pokeAction, MethodInfo *method);
            };

            struct Section_ProcessActionCore_Result_o;

            struct Section_ProcessActionCore_Description_c;

            struct Section_ProcessActionCore_Description_Fields {
                struct PokeAction_o* pokeAction;
            };

            struct Section_ProcessActionCore_Description_o {
                Section_ProcessActionCore_Description_c *klass;
                void *monitor;
                Section_ProcessActionCore_Description_Fields fields;
            };
        }
    }
}