#pragma once

namespace Dpr
{
    namespace Battle
    {
        namespace Logic 
        {
            namespace InterruptCode
            {
                enum InterruptCode
                {
                    NONE,
                    POKE_CHANGE,
                    POKE_COVER,
                    LEVELUP,
                    QUIT_SHOWDOWN,
                    QUIT_ESCAPE,
                    QUIT_CAPTURE,
                    QUIT_TURNOVER,
                    QUIT_SAFARIBALL
                };
            }
        }
    }
}