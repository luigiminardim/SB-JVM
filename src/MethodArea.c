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

ClassFile *getClass(MethodArea* method_area, u2 n_classes,char* classname){
    for(MethodArea* ma=method_area; ma< method_area + n_classes; ma++){
        // Fazer uma função de acesso a valores do CP pode ser interessante
        CpInfo cp_record = ma->classfile->constant_pool[ma->classfile->this_class];
        cp_record = ma->classfile->constant_pool[cp_record.constant_class_info.name_index];
        char* name = cp_record.constant_utf8_info.bytes;
        if (strcmp(name, classname) == 0){
            return ma;
        }
    }
    return NULL;
}

ClassFile *loadClass(JVM* jvm, char* classname){
    
    if (getClass(jvm->method_area, jvm->method_area_count, classname) == NULL){
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
