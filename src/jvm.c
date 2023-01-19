#include <stdlib.h>
#include "jvm.h"

JVM *startJVM(){
    JVM *jvm = (JVM *)malloc(sizeof(JVM));
    jvm->pc = 0;
    jvm->frame_count = 0;
    jvm->method_area_count = 0;
    jvm->method_area = (ClassFile *)malloc(sizeof(ClassFile));
    jvm->current_class = (ClassFile *)malloc(sizeof(ClassFile));
    jvm->current_method = (MethodInfo *)malloc(sizeof(MethodInfo));

    return jvm;
}

