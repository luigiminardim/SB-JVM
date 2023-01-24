#pragma once

#include "jvm.h"
#include "ClassFile.h"
#include "Method.h"

typedef struct Frame
{
    u4 pc;
    ClassFile* frame_class;
    MethodInfo* frame_method;
    int32_t* local_variables;
    u2 stack_count;
    int32_t* operand_stack;
    ConstantPool* constant_pool;
} Frame;

Frame *topFrame(JVM* jvm);

Frame *createFrame(JVM*, ClassFile*, MethodInfo*);

AttributeInfo* getCodeAttribute(Frame* f);

void pushOperandStack(Frame*, int32_t);

void freeFrame(Frame*);