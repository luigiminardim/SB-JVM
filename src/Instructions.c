#include "Code.h"
#include "Frame.h"

void sipush(Frame* frame, Code* code){
    pushOperandStack(frame, code->short_operands.short_);
}

void bipush(Frame* frame, Code* code){
    pushOperandStack(frame, code->byte_operands.byte);
}

void istore_2(Frame* frame, Code* code){
    int32_t val = popOperandStack(frame);
    frame->local_variables[2];
}

void iload_1(Frame* frame, Code* code){
    pushOperandStack(frame, frame->local_variables[1]);
}

void iadd(Frame* frame, Code* code){
    int32_t value1 = popOperandStack(frame);
    int32_t value2 = popOperandStack(frame);

    // overflow ?

    pushOperandStack(frame, value1 + value2);
}

void __return(Frame* frame, Code* code){
    return;
}