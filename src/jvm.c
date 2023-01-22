#include <stdlib.h>
#include "jvm.h"

JVM *startJVM(){
    JVM *jvm = (JVM *)malloc(sizeof(JVM));
    jvm->pc = 0;
    jvm->frame_count = 0;
    jvm->method_area_count = 0;
    jvm->method_area = (MethodArea *)malloc(sizeof(MethodArea));
    jvm->current_class = (ClassFile *)malloc(sizeof(ClassFile));
    jvm->current_method = (MethodInfo *)malloc(sizeof(MethodInfo));
    jvm->frames = (Frame *)malloc(sizeof(Frame));
    return jvm;
}

void setClass(JVM* jvm, char* classname){
    ClassFile* cf;
    cf = getClass(jvm->method_area, jvm->method_area_count, classname);
    jvm->current_class = cf;
}

void setMethod(JVM* jvm, char* method_name){
    MethodInfo* m;
    m = getMethod(jvm->current_class, method_name);
    jvm->current_method = m;
}

void popFrame(JVM* jvm){
    Frame *f = topFrame(jvm);
    jvm->frame_count--;
    Frame* new_frame_stack = realloc(jvm->frames, sizeof(Frame)*jvm->frame_count);
    jvm->frames = new_frame_stack;
    
    freeFrame(f);
}

void pushFrame(JVM* jvm){
    ClassFile *new_current_class = jvm->current_class;
    MethodInfo *new_current_method = jvm->current_method;

    jvm->frame_count++;
    Frame* new_frame_stack = realloc(jvm->frames, sizeof(Frame)*jvm->frame_count);
    Frame* new_frame = createFrame(jvm, new_current_class, new_current_method);
    
    new_frame_stack[jvm->frame_count-1] = *new_frame;
    jvm->frames = new_frame_stack;
    jvm->pc = 0;
}

void verifyClinit(JVM* jvm){
    MethodInfo *clinit = getMethod(jvm->current_class, "clinit");
    if (clinit == NULL){return;}

    saveContext(jvm);
    setMethod(jvm, "clinit");
    pushFrame(jvm);
}

void saveContext(JVM* jvm){
    Frame *f = topFrame(jvm);
    // Assume que jvm já calculou pc da proximo instrução antes de salvar o contexto
    f->pc = jvm->pc;
    f->frame_class = jvm->current_class;
    f->frame_method = jvm->current_method;
}

void restoreContext(JVM* jmv) {
    // Frame *f = topFrame(jvm);
    // jvm->pc = f->pc;
    // jvm->current_class = f->frame_class;
    // jvm->current_method = f->frame_method;
}

char* methodName(MethodInfo* method, ClassFile* class){
    CpInfo cpinfo = class->constant_pool[method->name_index];
    char *method_name = cpinfo.constant_utf8_info.bytes;
    return method_name;
}

char* className(ClassFile* class){
    CpInfo cpinfo = class->constant_pool[class->this_class];
    cpinfo = class->constant_pool[cpinfo.constant_class_info.name_index];
    char* classname = cpinfo.constant_utf8_info.bytes;
    return classname;
}

int inMain(JVM* jvm){
    char* curr_method_name = methodName(jvm->current_method, jvm->current_class);
    if (strcmp(curr_method_name, "main") == 0){
        return 1;
    } else {
        return 0;
    }
}