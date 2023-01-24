#include "Frame.h"
#include <string.h>

AttributeInfo* getCodeAttribute(Frame* current_frame){
    AttributeInfo *att_iter;
    for (att_iter = current_frame->frame_method->attributes;
         att_iter < current_frame->frame_method->attributes + current_frame->frame_method->attributes_count;
         att_iter++)
    {
        if(!strcmp(current_frame->constant_pool[att_iter->attribute_name_index]->constant_utf8_info.bytes, "Code")){
            break;
        }
    }

    return att_iter;
}

void pushOperandStack(Frame* frame, int32_t value){
    frame->operand_stack[frame->stack_count++] = value;
}