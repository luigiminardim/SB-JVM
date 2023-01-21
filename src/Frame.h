#pragma once

#include "jvm.h"
#include "ClassFile.h"
#include "Method.h"

typedef struct Frame
{
    u4 pc;
    ClassFile* frame_class;
    MethodInfo* frame_method;
} Frame;

Frame * topFrame(JVM* jvm);