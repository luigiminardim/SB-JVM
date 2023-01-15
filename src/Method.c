#include "Field.h"
#include "ClassFile.h"
#include "java-bytes.h"
#include <stdio.h>  // sprintf
#include <stdlib.h> // malloc
#include <string.h> // strlen

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

char *MethodInfo_access_flags_to_string(u2 access_flags)
{
  const char *public_string = access_flags & 0x0001 ? "public " : "";
  const char *private_string = access_flags & 0x0002 ? "private " : "";
  const char *protected_string = access_flags & 0x0004 ? "protected " : "";
  const char *static_string = access_flags & 0x0008 ? "static " : "";
  const char *final_string = access_flags & 0x0010 ? "final " : "";
  const char *synchronized_string = access_flags & 0x0020 ? "synchronized " : "";
  const char *bridge_string = access_flags & 0x0040 ? "bridge " : "";
  const char *varargs_string = access_flags & 0x0080 ? "varargs " : "";
  const char *native_string = access_flags & 0x0100 ? "native " : "";
  const char *abstract_string = access_flags & 0x0400 ? "abstract " : "";
  const char *strict_string = access_flags & 0x0800 ? "strict " : "";
  const char *synthetic_string = access_flags & 0x1000 ? "synthetic " : "";
  char *access_flags_string = (char *)malloc(1024);
  snprintf(
      access_flags_string, 1024,
      "%s%s%s%s%s%s%s%s%s%s%s%s",
      public_string, private_string, protected_string, static_string,
      final_string, synchronized_string, bridge_string, varargs_string,
      native_string, abstract_string, strict_string, synthetic_string);
  if (strlen(access_flags_string) > 0)
  {
    access_flags_string[strlen(access_flags_string) - 1] = '\0'; // remove trailing space;
  }
  return access_flags_string;
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
    char *access_flags_string = MethodInfo_access_flags_to_string(
        method_info->access_flags);
    char *attributes_str = AttributeInfo_to_string(
        method_info->attributes, method_info->attributes_count, constant_pool);
    char comma = method_info == method_infos + methods_count - 1 ? ']' : ',';
    char *name_utf8 = ConstantPool_get_utf8(
        constant_pool, method_info->name_index);
    char *descriptor_utf8 = ConstantPool_get_utf8(
        constant_pool, method_info->descriptor_index);
    snprintf(
        tmp, 65536,
        "%s{\"access_flags\":\"0x%04X [%s]\","
        "\"name_index\":\"#%d // %s\","
        "\"descriptor_index\":\"#%d // %s\", \"attributes_count\":%d,"
        "\"attributes\":%s}%c",
        methods_string, method_info->access_flags, access_flags_string,
        method_info->name_index, name_utf8,
        method_info->descriptor_index, descriptor_utf8,
        method_info->attributes_count, attributes_str, comma);
    free(access_flags_string);
    free(attributes_str);
    free(name_utf8);
    free(descriptor_utf8);
    free(methods_string);
    methods_string = tmp;
  }
  return methods_string;
}
