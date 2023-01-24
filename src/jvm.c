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
    Frame *new_frame_stack = (Frame *)realloc(jvm->frames, sizeof(Frame) * jvm->frame_count);
    jvm->frames = new_frame_stack;

    freeFrame(f);
}

void pushFrame(JVM *jvm, const char *classname, const char *method_name)
{
    MethodArea *ma = getClassMethodArea(jvm, classname);
    ClassFile *new_current_class = ma->classfile;
    MethodInfo *new_current_method = getMethod(new_current_class, method_name);

    jvm->frame_count++;
    Frame *new_frame_stack = (Frame *)realloc(jvm->frames, sizeof(Frame) * jvm->frame_count);
    Frame *new_frame = createFrame(new_current_class, new_current_method);

    new_frame_stack[jvm->frame_count - 1] = *new_frame;
    jvm->frames = new_frame_stack;
    // jvm->pc = 0;
}

Frame *topFrame(JVM* jvm){
    Frame* f = jvm->frames + ((jvm->frame_count-1) * sizeof(Frame));
    return f;
}

void verifyClinit(JVM *jvm)
{
    MethodInfo *clinit = getMethod(topFrame(jvm)->frame_class, "clinit");
    if (clinit == NULL)
    {
        return;
    }
    pushFrame(jvm, className(topFrame(jvm)->frame_class), "clinit");
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

Instance *allocNewInstance(JVM *jvm, const char *class_name)
{
    return newinstance(jvm->method_area, jvm->method_area_count, class_name);
}

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

        if (code.opcode == OPCODE_NONE)
        {
            current_frame->pc++;
            continue;
        }

        code.exec(current_frame, &code);
    }


    // code.exec(jvm)

    // pc++
}