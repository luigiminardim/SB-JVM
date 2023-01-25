#include <stdlib.h>
#include "jvm.h"

JVM *startJVM()
{
    JVM *jvm = (JVM *)malloc(sizeof(JVM));
    // jvm->pc = 0;
    jvm->frame_count = 0;
    jvm->method_area_count = 0;
    jvm->method_area = (MethodArea *)malloc(sizeof(MethodArea));
    jvm->frames = (Frame *)malloc(sizeof(Frame));
    return jvm;
}

void popFrame(JVM *jvm)
{
    Frame *f = topFrame(jvm);
    jvm->frame_count--;
    freeFrame(f);
    Frame *new_frame_stack = (Frame *)realloc(jvm->frames, sizeof(Frame) * jvm->frame_count);
    jvm->frames = new_frame_stack;
}

void pushFrame(JVM *jvm, const char *classname, const char *method_name)
{
    MethodArea *ma = getClassMethodArea(jvm, classname);
    ClassFile new_current_class = ma->classfile;
    MethodInfo *new_current_method = getMethod(&new_current_class, method_name);

    jvm->frame_count++;
    Frame *new_frame_stack = (Frame *)realloc(jvm->frames, sizeof(Frame) * (jvm->frame_count));

    jvm->frames = new_frame_stack;

    createFrame(topFrame(jvm), new_current_class, new_current_method);
}

Frame *topFrame(JVM* jvm){
    Frame* f = jvm->frames + ((jvm->frame_count-1) * sizeof(Frame));
    return f;
}

void verifyClinit(JVM *jvm)
{
    MethodInfo *clinit = getMethod(&topFrame(jvm)->frame_class, "clinit");
    if (clinit == NULL)
    {
        return;
    }
    pushFrame(jvm, className(&topFrame(jvm)->frame_class), "clinit");
}

char *methodName(MethodInfo *method, ClassFile *classfile)
{
    CpInfo cpinfo = classfile->constant_pool[method->name_index];
    char *method_name = cpinfo.constant_utf8_info.bytes;
    return method_name;
}

char *className(ClassFile *classfile)
{
    CpInfo cpinfo = classfile->constant_pool[classfile->this_class];
    cpinfo = classfile->constant_pool[cpinfo.constant_class_info.name_index];
    char *classname = cpinfo.constant_utf8_info.bytes;
    return classname;
}

FieldValue *getStatic(JVM *jvm, const char *class_name, const char *field_name, const char *type_name)
{
    return getstatic(jvm, class_name, field_name, type_name);
}

//Instance *allocNewInstance(JVM *jvm, const char *class_name)
//{
//    return newinstance(jvm->method_area, jvm->method_area_count, class_name);
//}

Code fetchCode(Frame *current_frame)
{
    AttributeInfo *att_iter = getCodeAttribute(current_frame);
    return att_iter->code.code[current_frame->pc];
}

void runJVM(JVM *jvm)
{

    while (jvm->frame_count != 0)
    {
        Frame *current_frame = topFrame(jvm);
        Code code = fetchCode(current_frame);

        //printf("OPCODE: %s, %d \n", code.mnemonic, current_frame->stack_count);
        //for(int i=0; i< current_frame->stack_count; i++){
        //    printf("%u ", current_frame->operand_stack[i]);
        //}
        //printf("PILHA DE OPERANDOS %d %d %d \n", current_frame->local_variables[0], current_frame->local_variables[1], current_frame->local_variables[2]);
        //printf("\n---\n");
        if (code.opcode == OPCODE_NONE)
        {
            current_frame->pc++;
            continue;
        } else if (code.opcode == OPCODE_RETURN){
            popFrame(jvm);
            continue;
        } else {
            code.exec(current_frame, &code);
        }

        current_frame->pc++;
    }
}

void freeJVM(JVM* jvm){
    
    MethodArea* method_area = jvm->method_area;
    u2 n_classes = jvm->method_area_count;
    MethodArea* ma;
    for(ma=method_area; ma< method_area + n_classes; ma++){
        freeMethodArea(ma);
    }
    free(jvm->frames);
    free(jvm);
}