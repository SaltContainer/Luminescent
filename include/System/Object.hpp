#pragma once 
#include "il2cpp.hpp"

namespace System
{
    class Type;
    struct Object
    {
        static void ctor(void * item, MethodInfo * method);
        Type* GetType(MethodInfo * method);
    };
}