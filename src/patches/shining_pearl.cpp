#include "il2cpp-api.h"
#include "util.hpp"
#include "logger.hpp"

namespace UnityEngine::UI {
    struct RawImage_o;
}

namespace System {
    struct Action_o;
}

namespace Dpr::Movie {

    struct TitlePlayer_o;
    struct MoviePlayer_o;



    void TitlePlayer_Initialize(TitlePlayer_o* __this, MoviePlayer_o* moviePlayer, bool diaVersion, int32_t lang,
                                UnityEngine::UI::RawImage_o* fadeImage, System::Action_o* endCallback, MethodInfo* method);
}

void Init_Title_SP(Dpr::Movie::TitlePlayer_o* __this, Dpr::Movie::MoviePlayer_o* moviePlayer, bool diaVersion,
                   int32_t lang, UnityEngine::UI::RawImage_o* fadeImage, System::Action_o* endCallback, MethodInfo* method) {
    socket_log_fmt("Init Title\n");
    Dpr::Movie::TitlePlayer_Initialize(__this, moviePlayer, true, lang, fadeImage, endCallback, method);
}

int32_t Force_Diamond_Casset() {
    return 10; // Returned by EvDataManager$$GetOriginalCassetVersion when PlayerWork$$get_cassetVersion returns 0x30 (Diamond)
}