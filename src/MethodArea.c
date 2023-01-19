#include <stdlib.h>
#include "Method.h"
#include "ClassFile.h"

MethodInfo *getMethod(ClassFile* method_class, char* method_name){
    MethodInfo* first_method = method_class->methods;
    u2 method_count = method_class->methods_count;
    for (MethodInfo* m = first_method; m < first_method + method_count; m++){
        char* m_name = method_class->constant_pool[m->name_index].constant_utf8_info.bytes;
        if (strcmp(m_name, method_name) == 0){
            return m;
        }
    }

    // TODO: E se o metodo não existir ?
}