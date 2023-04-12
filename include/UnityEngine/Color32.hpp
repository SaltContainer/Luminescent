#pragma once

namespace UnityEngine {
	struct Color32_Fields
	{
		int32_t rgba;
		uint8_t r;
		uint8_t g;
		uint8_t b;
		uint8_t a;
	};
	
	struct Color32
	{
		Color32_Fields fields;
	};
}