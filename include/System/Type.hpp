#pragma once

#include "il2cpp.hpp"
#include "String.hpp"


namespace System {
	struct Type
	{
		static Type* GetType(String *typeName, MethodInfo *method);
	};
	
}