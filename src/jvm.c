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

void setClass(JVM *jvm, char *classname)
{
    MethodArea *ma;
    ma = getClassMethodArea(jvm, classname);
    Frame *frame = topFrame(jvm);
    frame->frame_class = ma->classfile;
}

void setMethod(JVM *jvm, char *method_name)
{
    MethodInfo *m;
    Frame *frame = topFrame(jvm);
    m = getMethod(frame->frame_class, method_name);
    frame->frame_method = m;
}

void popFrame(JVM *jvm)
{
    Frame *f = topFrame(jvm);
    jvm->frame_count--;
    Frame *new_frame_stack = realloc(jvm->frames, sizeof(Frame) * jvm->frame_count);
    jvm->frames = new_frame_stack;

    freeFrame(f);
}

void pushFrame(JVM *jvm, char *classname, char *method_name)
{
    MethodArea *ma = getClassMethodArea(jvm, classname);
    ClassFile *new_current_class = ma->classfile;
    MethodInfo *new_current_method = getMethod(new_current_class, method_name);

    jvm->frame_count++;
    Frame *new_frame_stack = realloc(jvm->frames, sizeof(Frame) * jvm->frame_count);
    Frame *new_frame = createFrame(jvm, new_current_class, new_current_method);

    new_frame_stack[jvm->frame_count - 1] = *new_frame;
    jvm->frames = new_frame_stack;
    // jvm->pc = 0;
}

void verifyClinit(JVM *jvm)
{
    MethodInfo *clinit = getMethod(topFrame(jvm)->frame_class, "clinit");
    if (clinit == NULL)
    {
        return;
    }

    saveContext(jvm);
    setMethod(jvm, "clinit");
    pushFrame(jvm, topFrame(jvm)->frame_class, "clinit");
}

char *methodName(MethodInfo *method, ClassFile *class)
{
    CpInfo cpinfo = class->constant_pool[method->name_index];
    char *method_name = cpinfo.constant_utf8_info.bytes;
    return method_name;
}

char *className(ClassFile *class)
{
    CpInfo cpinfo = class->constant_pool[class->this_class];
    cpinfo = class->constant_pool[cpinfo.constant_class_info.name_index];
    char *classname = cpinfo.constant_utf8_info.bytes;
    return classname;
}

FieldValue *getStatic(JVM *jvm, char *class_name, char *field_name, char *type_name)
{
    return getstatic(jvm, class_name, field_name, type_name);
}

Instance *allocNewInstance(JVM *jvm, char *class_name)
{
    return newinstance(jvm->method_area, jvm->method_area_count, class_name);
}

Code fetchCode(Frame *current_frame)
{
    AttributeInfo* att_iter = getCodeAttribute(current_frame);
    return att_iter->code.code[current_frame->pc];
}

void runJVM(JVM *jvm)
{

    while (jvm->frame_count != 0)
    {
        Frame* current_frame = topFrame;
        Code code = fetchCode(current_frame);

        if (code.opcode == OPCODE_NONE){
            current_frame->pc++;
            continue;
        }

        
    }

    // code = fetch(topFrame(jvm), jmv->pc);

    // if code.opcode == NONE
    //      pc ++
    //      continue

    // code.exec(jvm)

    // pc++
}