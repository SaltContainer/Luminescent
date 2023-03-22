#pragma once

#include "il2cpp.hpp"
#include "InsertActionInfo.hpp"

namespace Dpr
{
    namespace Battle
    {
        namespace Logic
        {
            struct ActionDesc_c;

            struct ActionDesc_Fields {
                uint32_t serialNo;
                bool isOiutiInterruptAction;
                bool isYokodoriRobAction;
                bool isMagicCoatReaction;
                bool isOdorikoReaction;
                bool isSaihaiReaction;
                struct InsertActionInfo_o* insertInfo;
            };

            struct ActionDesc_o {
                ActionDesc_c *klass;
                void *monitor;
                ActionDesc_Fields fields;
            };
        }
    }
}