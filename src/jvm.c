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

    return jvm;
}

void setClass(JVM* jvm, char* classname){
    ClassFile* cf;
    // ClassFile* cf = loadClass(char* classname)
    jvm->current_class = cf;
}

void setMethod(JVM* jvm, char* method_name){
    MethodInfo* m;
    m = getMethod(jvm->current_class, method_name);
    jvm->current_method = m;
}

void popFrame(JVM* jvm){
    // JVM
    // Frame *f = jvm->frames[jvm->frame_count - 1];
    // jvm->frame_count = jvm->frame_count - 1;
    
    // Frame
    // freeFrame(f);
}

void pushFrame(JVM* jvm){
    ClassFile *new_current_class = jvm->current_class;
    MethodInfo *new_curret_method = jvm->current_method;

    jvm->frame_count = jvm->frame_count + 1
    // Frame* new_frame_stack = realloc(jvm->frames, jvm->frame_count);
    // Frame* new_frame = createframe(jvm, new_current_class, new_current_method);
    
    // new_frame_stack[jvm->frame_count-1] = new_frame;
    // jvm->frames = new_frame_stack;
    jvm->pc = 0;
}