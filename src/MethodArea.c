#include <stdlib.h>
#include "Method.h"
#include "ClassFile.h"
#include "MethodArea.h"
#include "jvm.h"

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

int classLoaded(MethodArea* method_area, char* classname){
    
}

ClassFile *loadClass(JVM* jvm, char* classname){
    
    if (class_loaded(jvm->method_area, classname)){
        return;
    }

    // +1 because of '\0' at the end
    char * copy = malloc(strlen(classname) + 1); 
    strcpy(copy, classname);
    strcat(copy, ".class");

    FILE *fp = fopen(copy, "rb");
    ClassFile cf = ClassFile_read(fp);

    jvm->method_area_count++;
    MethodArea* new_method_area = realloc(jvm->method_area, jvm->method_area_count*sizeof(MethodArea));
    // Não tenho certeza se é assim mesmo: 
    new_method_area[jvm->method_area_count-1].classfile = &cf;

    jvm->method_area = new_method_area;

    free(copy); // at the end, free it again.
}