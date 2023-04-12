#pragma once
#include "UnityEngine/MonoBehaviour.hpp"
#include "Dpr/UI/UIWindow.hpp"
#include "UnityEngine/Vector3.hpp"
#include "UnityEngine/Color32.hpp"

namespace XLSXContent
{
	namespace UIDatabase
	{
		class SheetPokemonVoice;
	} // namespace UIDatabase
	
} // namespace XLSXContent


namespace Audio
{
	class AudioInstance;
} // namespace Audio


namespace UnityEngine
{
	class CanvasGroup;
	class RectTransform;
	class Color32_array;
	class Coroutine;
	class Sprite_array;
	namespace UI
	{
		class RawImage;
		class Image;
		class Image_array;
	} // namespace UI
	
} // namespace UnityEngine

namespace System
{
	namespace Collections
	{
		namespace Generic
		{
			class List_PoketchAppBase;
		} // namespace Generic
		
	} // namespace Collections
	
} // namespace System

namespace DG
{
	namespace Tweening
	{
		class Sequence;
	} // namespace Tweening
	
} // namespace DG



namespace Dpr {
	namespace UI {
		class PoketchButton;
		class UIInputButton;

		struct PoketchWindow_Fields
		{
			UIWindow_Fields super;
			struct UnityEngine::CanvasGroup* _canvasGroup;
			struct UnityEngine::UI::RawImage* _imageBg;
			struct UnityEngine::RectTransform* _root;
			struct UnityEngine::RectTransform* _rootTopShutter;
			struct UnityEngine::RectTransform* _rootBottomShutter;
			struct PoketchButton* _changeButton;
			struct UnityEngine::UI::Image* _cursor;
			struct UnityEngine::UI::RawImage* _appBG;
			struct UnityEngine::UI::Image_array* _bodyImages;
			struct UnityEngine::Sprite_array* _bodySprites;
			struct UnityEngine::UI::Image_array* _numImages;
			struct UnityEngine::Sprite_array* _numSprites;
			struct System::Collections::Generic::List_PoketchAppBase* _poketchAppList;
			float _resizeDuration;
			float _changeDuration;
			float _closeWait;
			float _changeWait;
			float _smallScale;
			float _largeScale;
			struct UnityEngine::Vector3 _smallPos;
			struct UnityEngine::Vector3 _largePos;
			float _toSmallDelay;
			float _toLargeDelay;
			struct UnityEngine::Color32 _lightColor;
			struct UnityEngine::Color32_array* _bgColors;
			float _cursolMoveValue;
			float _voiceWait;
			struct UIInputButton* _buttonR;
			struct UIInputButton* _buttonSR;
			bool _isSizeChanging;
			bool _isBackLight;
			bool _isTouch;
			bool _isSelecting;
			struct PoketchButton* _preButton;
			struct UnityEngine::Coroutine* _appChangeCoroutine;
			float _appCloseTime;
			struct DG::Tweening::Sequence* _twSeqence;
			struct UnityEngine::Coroutine* penColoutine;
			struct UnityEngine::Coroutine* _closeColoutine;
			int32_t _voiceMonsNo;
			struct Audio::AudioInstance* _voiceInstance;
			struct XLSXContent::UIDatabase::SheetPokemonVoice* _voiceData;
			float _voiceTimer;
			float _cursorMinX;
			float _cursorMaxX;
			float _cursorMinY;
			float _cursorMaxY;
			int32_t _CurrentAppIndex_k__BackingField;
			bool _IsLarge_k__BackingField;
			bool _IsPauseContinue_k__BackingField;
			bool _IsCloseOnce_k__BackingField;
			int32_t AppWidth;
			int32_t AppHeight;
			float _cursorX;
			float _cursorY;
			int32_t _touchState;
		};
		
		struct PoketchWindow_StaticFields
		{
			struct PoketchWindow* _Instance_k__BackingField;
		};

		struct PoketchWindow_RGCTXs {
			/* data */
		};

		struct PoketchWindow_VTable {
			VirtualInvokeData _0_Equals;
			VirtualInvokeData _1_Finalize;
			VirtualInvokeData _2_GetHashCode;
			VirtualInvokeData _3_ToString;
			VirtualInvokeData _4_OnCreate;
			VirtualInvokeData _5_OnDestroy;
			VirtualInvokeData _6_OnTransition;
			VirtualInvokeData _7_OnTransitionComplete;
			VirtualInvokeData _8_OnOpen;
			VirtualInvokeData _9_PlayOpenWindowAnimation;
			VirtualInvokeData _10_OpPlayOpenWindowAnimation;
			VirtualInvokeData _11_GetWindowAnimationConnectId;
			VirtualInvokeData _12_OpPlayCloseWindowAnimationAndWaiting;
			VirtualInvokeData _13_EnableMainCameraByUiMode;
			VirtualInvokeData _14_OnCloseKeyguide;
			VirtualInvokeData _15_OpenMessageWindow;
			VirtualInvokeData _16_CloseMessageWindow;
			VirtualInvokeData _17_IsActiveMessageWindow;
			VirtualInvokeData _18_CreateContextMenuYesNo;
			VirtualInvokeData _19_CreateContextMenuYesNo;
			VirtualInvokeData _20_OnAddContextMenuYesNoItemParams;
		};
		
		struct PoketchWindow_Klass
		{
			Il2CppClass_1 _1;
			struct PoketchWindow_StaticFields* static_fields;
			PoketchWindow_RGCTXs* rgctx_data;
			Il2CppClass_2 _2;
			PoketchWindow_VTable vtable;
		};

		struct PoketchWindow : UIWindow
		{
			PoketchWindow_Klass *klass;
			void *monitor;
			PoketchWindow_Fields fields;

			static PoketchWindow get_Instance(MethodInfo *method);
			void SelectApp(bool isForward, MethodInfo *method);
			bool IsInRange(PoketchButton *target, float posX, float posY, MethodInfo *method);
		};

		extern MethodInfo* Dpr_UI_PoketchWindow__OnCreate_b__90_0;
	}
}