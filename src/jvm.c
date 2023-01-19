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