#pragma once 

#include "il2cpp.hpp"
#include "ActionSharedData.hpp"
#include "BattleEnv.hpp"
#include "EventLauncher.hpp"
#include "MainModule.hpp"
#include "PokeActionContainer.hpp"
#include "SectionContainer.hpp"
#include "SectionSharedData.hpp"
#include "ServerCommandPutter.hpp"

namespace Dpr
{
    namespace Battle
    {
        namespace Logic
        {
            struct Section_c;
            
            struct Section_Fields {
                struct MainModule_o* m_pMainModule;
                struct BattleEnv_o* m_pBattleEnv;
                struct ServerCommandQueue_o* m_pServerCmdQueue;
                struct ServerCommandPutter_o* m_pServerCmdPutter;
                struct WazaCommandPutter_o* m_pWazaCmdPutter;
                struct EventSystem_o* m_pEventSystem;
                struct EventLauncher_o* m_pEventLauncher;
                struct SectionSharedData_o* m_pSharedData;
                struct PokeActionContainer_o* m_pPokemonActionContainer;
                struct PokeChangeRequest_o* m_pPokeChangeRequest;
                struct CaptureInfo_o* m_pCaptureInfo;
                struct SectionContainer_o* m_pSectionContainer;
            };
            
            struct Section_o {
                int32_t CheckEncoreWazaChange(PokeAction_o *action, MethodInfo *method);
                ActionSharedData_o * GetActionSharedData(MethodInfo *method);
                uint8_t GetPokePos(uint8_t pokeID, MethodInfo *method);

                Section_c *klass;
                void *monitor;
                Section_Fields fields;
            };
        }
    }
}