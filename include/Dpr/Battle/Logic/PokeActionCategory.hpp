#pragma once

namespace Dpr
{
    namespace Battle
    {
        namespace Logic 
        {
            namespace PokeActionCategory
            {
                enum PokeActionCategory
                {
                    Null,
                    Fight,
                    Item,
                    PokeChange,
                    Escape,
                    Skip,
                    GStart,
                    Cheer,
                    RaidBossExtraAction,
                    RecPlay_TimeOver,
                    RecPlay_Error
                };
            }
        }
    }
}