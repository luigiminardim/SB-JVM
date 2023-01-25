#include <stdlib.h>
#include "Method.h"
#include "ClassFile.h"
#include "MethodArea.h"
#include "jvm.h"
#include <string.h>

MethodInfo *getMethod(ClassFile* method_class, const char* method_name){
    MethodInfo* first_method = method_class->methods;
    u2 method_count = method_class->methods_count;
    for (MethodInfo* m = first_method; m < first_method + method_count; m++){
        char* m_name = method_class->constant_pool[m->name_index].constant_utf8_info.bytes;
        if (strcmp(m_name, method_name) == 0){
            return m;
        }
    }

    return NULL;
}

void loadStatic(MethodArea* method_area){
    // iterar sobre os fields
    int contador = 0;
    FieldInfo *f;
    FieldInfo * field_infos = method_area->classfile.fields;
    u2 fields_count = method_area->classfile.fields_count;
    for (f = field_infos; f < field_infos + fields_count; f++){
        // verifica se static
        if (f->access_flags >= 8 && f->access_flags <= 12){
            contador++;
        }
    }
    
    FieldValue *field_values = (FieldValue *)realloc(method_area->static_fields,sizeof(FieldValue) * (contador));
    FieldValue *fv_iter = field_values;
    for (f = field_infos; f < field_infos + fields_count; f++){
        // verifica se static
        if (f->access_flags >= 8 && f->access_flags <= 12){
            fv_iter->name_cpinfo = method_area->classfile.constant_pool[f->name_index].constant_utf8_info;
            fv_iter->type_cpinfo = method_area->classfile.constant_pool[f->descriptor_index].constant_utf8_info;
            fv_iter++;
        }
    }

    method_area->static_fields_count = contador;
    method_area->static_fields = field_values;
}

FieldValue *getstatic(JVM* jvm, const char* class_name, const char* field_name, const char* type_name){
    MethodArea* ma = getClassMethodArea(jvm, class_name);

    for (FieldValue *fv_iter = ma->static_fields; fv_iter < ma->static_fields + ma->static_fields_count; fv_iter++){
        if ((strcmp(fv_iter->name_cpinfo.bytes, field_name) == 0) && 
            (strcmp(fv_iter->type_cpinfo.bytes, type_name) == 0)){
            return fv_iter;
        }
    }

    return NULL;
}

MethodArea *getClassMethodArea(JVM* jvm, const char* classname){
    MethodArea* method_area = jvm->method_area;
    u2 n_classes = jvm->method_area_count;
    for(MethodArea* ma=method_area; ma< method_area + n_classes; ma++){
        // Fazer uma função de acesso a valores do CP pode ser interessante
        CpInfo cp_record = ma->classfile.constant_pool[ma->classfile.this_class];
        cp_record = ma->classfile.constant_pool[cp_record.constant_class_info.name_index];
        char* name = cp_record.constant_utf8_info.bytes;
        if (strcmp(name, classname) == 0){
            return ma;
        }
    }

    return loadClass(jvm, classname);
}

MethodArea* loadClass(JVM* jvm, const char* classname){

    // +1 pelo '\0' no final
    char * copy = (char *)malloc(sizeof(char) *(strlen(classname) + 7)); 
    strcpy(copy, classname);
    strcat(copy, ".class");

    FILE *fp = fopen(copy, "rb");
    ClassFile cf = ClassFile_read(fp);

    jvm->method_area_count++;
    MethodArea* new_ma_ptr = (MethodArea *)realloc(jvm->method_area, sizeof(MethodArea)*(jvm->method_area_count));
    jvm->method_area = new_ma_ptr;

    MethodArea* ma = &(jvm->method_area[jvm->method_area_count - 1]);
    initMethodArea(ma);
    ma->classfile = cf;
    loadStatic(ma);

    free(copy);

    return ma;
}


void initMethodArea(MethodArea* new_ma){
    new_ma->instances_count = 0;
    new_ma->static_fields_count = 0;
    new_ma->instances = (Instance *)malloc(sizeof(Instance));
    new_ma->static_fields = (FieldValue *)malloc(sizeof(FieldValue));
}

void freeMethodArea(MethodArea* ma){
    free(ma->static_fields);
    free(ma->instances);
    ClassFile_free(ma->classfile);
    free(ma);
}