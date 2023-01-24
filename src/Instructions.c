#include "Code.h"
#include "Frame.h"

void sipush(Frame* frame, Code code){
    pushOperandStack(frame, code.short_operands.short_);
}