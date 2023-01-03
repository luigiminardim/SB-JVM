#include "Method.h"
#include "Field.h"
#include "ClassFile.h"
#include "java-bytes.h"
#include <stdio.h>  // sprintf
#include <stdlib.h> // malloc

ClassFile ClassFile_read(FILE *fp)
{
  ClassFile c;
  c.magic_number = u4_read(fp);
  c.minor_version = u2_read(fp);
  c.major_version = u2_read(fp);
  c.constant_pool_count = u2_read(fp);
  c.constant_pool = ConstantPool_read(fp, c.constant_pool_count);
  c.access_flags = u2_read(fp);
  c.this_class = u2_read(fp);
  c.super_class = u2_read(fp);
  c.interfaces_count = u2_read(fp);
  c.interfaces = (u2 *)malloc(sizeof(u2) * c.interfaces_count);
  for (int i = 0; i < c.interfaces_count; i++)
  {
    c.interfaces[i] = u2_read(fp);
  }
  c.fields_count = u2_read(fp);
  c.fields = FieldInfo_read(fp, c.fields_count, c.constant_pool);
  c.methods_count = u2_read(fp);
  c.methods = MethodInfo_read(fp, c.methods_count, c.constant_pool);
  c.attributes_count = u2_read(fp);
  c.attributes = AttributeInfo_read(fp, c.attributes_count, c.constant_pool);
  return c;
}

char *ClassFile_intefarces_to_string(ClassFile c)
{
  char *interfaces_string = (char *)malloc(1000);
  snprintf(interfaces_string, 1000, "[");
  if (c.interfaces_count == 0)
  {
    sprintf(interfaces_string, "%s]", interfaces_string);
  }
  for (int i = 0; i < c.interfaces_count; i++)
  {
    char *tmp = (char *)malloc(1000);
    char comma = i == c.interfaces_count - 1 ? ']' : ',';
    sprintf(tmp, "%s\"#%d\"%c", interfaces_string, c.interfaces[i], comma);
    free(interfaces_string);
    interfaces_string = tmp;
  }
  return interfaces_string;
}

char *ClassFile_to_string(ClassFile c)
{
  char *class_file_string = (char *)malloc(1000000);
  char *constant_pool_string = ConstantPool_to_string(c.constant_pool, c.constant_pool_count);
  char *interfaces_string = ClassFile_intefarces_to_string(c);
  char *fields_string = FieldInfo_to_string(c.fields, c.fields_count, c.constant_pool);
  char *methods_string = MethodInfo_to_string(c.methods, c.methods_count, c.constant_pool);
  char *attributes_string = AttributeInfo_to_string(c.attributes, c.attributes_count, c.constant_pool);
  snprintf(
      class_file_string, 1000000,
      "{\"__cls\":\"ClassFile\",\"magic_number\":\"0x%X\",\"minor_version\":%d,\"major_version\":%d,\"constant_pool_count\":%d,\"constant_pool\":%s,\"access_flags\":%d,\"this_class\":\"#%d\",\"super_class\":\"#%d\",\"interfaces_count\":%d,\"interfaces\":%s,\"fields_count\":%d,\"fields\":%s,\"methods_count\":%d,\"methods\":%s,\"attributes_count\":%d,\"attributes\":%s}",
      c.magic_number, c.minor_version, c.major_version, c.constant_pool_count, constant_pool_string,
      c.access_flags, c.this_class, c.super_class, c.interfaces_count, interfaces_string,
      c.fields_count, fields_string, c.methods_count, methods_string, c.attributes_count,
      attributes_string);
  free(constant_pool_string);
  free(interfaces_string);
  free(fields_string);
  free(methods_string);
  free(attributes_string);
  return class_file_string;
}

void ClassFile_free(ClassFile c)
{
  AttributeInfo_free(c.attributes, c.attributes_count, c.constant_pool);
  MethodInfo_free(c.methods, c.methods_count, c.constant_pool);
  FieldInfo_free(c.fields, c.fields_count, c.constant_pool);
  free(c.interfaces);
  ConstantPool_free(c.constant_pool, c.constant_pool_count);
}
