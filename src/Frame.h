#pragma once

#include "ClassFile.h"
#include "Method.h"

/**
 * @brief Struct that represents a frame of the JVM
 * 
 */
typedef struct Frame
{
    u4 pc;
    ClassFile frame_class;
    MethodInfo* frame_method;
    int32_t* local_variables;
    u2 stack_count;
    int32_t* operand_stack;
    // ConstantPool* constant_pool;
} Frame;

/**
 * @brief Create a Frame object
 * 
 * @return Frame* 
 */
Frame *createFrame(Frame* ,ClassFile, MethodInfo*);

/**
 * @brief Get the Code Attribute object
 * 
 * @param f pointer to Frame
 * @return AttributeInfo* 
 */
AttributeInfo* getCodeAttribute(Frame* f);

/**
 * @brief Pushes new operando into the stack
 * 
 */
void pushOperandStack(Frame*, int32_t);

/**
 * @brief Pop operand from operand stack
 * 
 * @return int32_t value
 */
int32_t popOperandStack(Frame*);

/**
 * @brief Free's frame allocated memory
 * 
 */
void freeFrame(Frame*);