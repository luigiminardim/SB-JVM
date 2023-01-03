#include "Field.h"
#include "ClassFile.h"
#include "java-bytes.h"
#include <stdio.h>  // sprintf
#include <stdlib.h> // malloc

MethodInfo *MethodInfo_read(FILE *fp, u2 methods_count, ConstantPool constant_pool)
{
  MethodInfo *methods = (MethodInfo *)malloc(methods_count * sizeof(MethodInfo));
  MethodInfo *m;
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

void MethodInfo_free(MethodInfo *method_info, u2 methods_count, ConstantPool constant_pool)
{
  MethodInfo *m;
  for (m = method_info; m < method_info + methods_count; m++)
  {
    AttributeInfo_free(m->attributes, m->attributes_count, constant_pool);
  }
  free(method_info);
}

char *MethodInfo_to_string(MethodInfo *method_infos, u2 methods_count, ConstantPool constant_pool)
{
  char *methods_string = (char *)malloc(65536);
  snprintf(methods_string, 65536, "[");
  if (methods_count == 0)
  {
    snprintf(methods_string, 65536, "%s]", methods_string);
  }
  for (MethodInfo *method_info = method_infos; method_info < method_infos + methods_count; method_info++)
  {
    char *tmp = (char *)malloc(65536);
    char *attributes_str = AttributeInfo_to_string(
        method_info->attributes, method_info->attributes_count, constant_pool);
    char comma = method_info == method_infos + methods_count - 1 ? ']' : ',';
    snprintf(
        tmp, 65536,
        "%s{\"access_flags\":\"0x%X\",\"name_index\":\"#%d\",\"descriptor_index\":\"#%d\", \"attributes_count\":%d,\"attributes\":%s}%c",
        methods_string, method_info->access_flags, method_info->name_index,
        method_info->descriptor_index, method_info->attributes_count, attributes_str, comma);
    free(attributes_str);
    free(methods_string);
    methods_string = tmp;
  }
  return methods_string;
}
