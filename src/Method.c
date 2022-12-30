#include "Field.h"
#include "ClassFile.h"
#include "java-bytes.h"
#include <stdio.h>  // sprintf
#include <stdlib.h> // malloc

MethodInfo *MethodInfo_read(FILE *fp, u2 methods_count, ConstantPool constant_pool){

  MethodInfo *methods = (MethodInfo *)malloc(methods_count * sizeof(MethodInfo));
  MethodInfo *m;

  // itera sobre os methods
  for (m = methods; m < methods + methods_count; m++)
  {
    m->access_flags = u2_read(fp);
    m->name_index = u2_read(fp);
    m->descriptor_index = u2_read(fp);
    m->attributes_count = u2_read(fp);
    m->attributes = AttributeInfo_read(fp, m->attributes_count, constant_pool);
  }

  return methods;
}

void MethodInfo_free(MethodInfo *method_info, u2 methods_count, ConstantPool constant_pool){

  MethodInfo *m;

  for (m = method_info; m < method_info + methods_count; m++){
    AttributeInfo_free(m->attributes, m->attributes_count, constant_pool);
  }

  free(method_info);
}