#pragma once

#include "il2cpp.hpp"
#include "StrParam.hpp"

namespace Dpr
{
    namespace Battle
    {
        namespace Logic
        {
            struct InsertActionInfo_c;

            struct InsertActionInfo_Fields {
                bool isTokuseiWindowDisplay;
                struct StrParam_o* prevActionMessage;
            };

            struct InsertActionInfo_o {
                InsertActionInfo_c *klass;
                void *monitor;
                InsertActionInfo_Fields fields;
            };
        }
    }
}