#include "Frame.h"
#include <string.h>
#include "stdlib.h"

AttributeInfo* getCodeAttribute(Frame* current_frame){
    AttributeInfo *att_iter;
    for (att_iter = current_frame->frame_method->attributes;
         att_iter < current_frame->frame_method->attributes + current_frame->frame_method->attributes_count;
         att_iter++)
    {
        if(!strcmp(current_frame->frame_class.constant_pool[att_iter->attribute_name_index].constant_utf8_info.bytes, "Code")){
            break;
        }
    }

    return att_iter;
}

void pushOperandStack(Frame* frame, int32_t value){
    frame->operand_stack[frame->stack_count++] = value;
}

int32_t popOperandStack(Frame* frame){
    int32_t val = frame->operand_stack[frame->stack_count - 1];
    frame->stack_count--;
    return val;
}

Frame* createFrame(Frame* f ,ClassFile cf, MethodInfo* mi){
    f->pc = 0;
    f->frame_class = cf;
    f->frame_method = mi;
    // f->constant_pool = &(cf.constant_pool);
    
    AttributeInfo* code_attr = getCodeAttribute(f);

    f->local_variables = (int32_t *)malloc(sizeof(int32_t) * (code_attr->code.max_locals));
    f->operand_stack = (int32_t *)malloc(sizeof(int32_t) * (code_attr->code.max_stack));
    f->stack_count = 0;
    return f;
}

void freeFrame(Frame* f){
    free(f->operand_stack);
    free(f->local_variables);
}