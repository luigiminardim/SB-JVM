#include "Code.h"
#include "Frame.h"

void sipush(Frame* frame, Code code){
    pushOperandStack(frame->operand_stack, code.short_operands.short_);
}