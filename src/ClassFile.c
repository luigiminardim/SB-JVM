#include "Method.h"
#include "Field.h"
#include "ClassFile.h"
#include "java-bytes.h"
#include <stdio.h>  // sprintf
#include <stdlib.h> // malloc
#include <string.h> // strcpy

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

char *ClassFile_major_version_to_string(u2 major_version)
{
  char *version_string = (char *)malloc(100);
  switch (major_version)
  {
  case 45:
    strcpy(version_string, "1.1");
    break;
  case 46:
    strcpy(version_string, "1.2");
    break;
  case 47:
    strcpy(version_string, "1.3");
    break;
  case 48:
    strcpy(version_string, "1.4");
    break;
  case 49:
    strcpy(version_string, "1.5");
    break;
  case 50:
    strcpy(version_string, "1.6");
    break;
  case 51:
    strcpy(version_string, "1.7");
    break;
  case 52:
    strcpy(version_string, "1.8");
    break;
  case 53:
    strcpy(version_string, "1.9");
    break;
  case 54:
    strcpy(version_string, "1.10");
    break;
  case 55:
    strcpy(version_string, "1.11");
    break;
  case 56:
    strcpy(version_string, "1.12");
    break;
  case 57:
    strcpy(version_string, "1.13");
    break;
  case 58:
    strcpy(version_string, "1.14");
    break;
  case 59:
    strcpy(version_string, "1.15");
    break;
  case 60:
    strcpy(version_string, "1.16");
    break;
  case 61:
    strcpy(version_string, "1.17");
    break;
  case 62:
    strcpy(version_string, "1.18");
    break;
  case 63:
    strcpy(version_string, "1.19");
    break;
  default:
    strcpy(version_string, "unknown");
  }
  return version_string;
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
    char *interface_utf8 = ConstantPool_get_utf8(
        c.constant_pool, c.interfaces[i]);
    snprintf(
        tmp, 1000,
        "%s\"#%d // %s\"%c",
        interfaces_string, c.interfaces[i], interface_utf8, comma);
    free(interfaces_string);
    interfaces_string = tmp;
  }
  return interfaces_string;
}

char *ClassFile_to_string(ClassFile c)
{
  char *class_file_string = (char *)malloc(1000000);
  char *major_version_string = ClassFile_major_version_to_string(
      c.major_version);
  char *constant_pool_string = ConstantPool_to_string(
      c.constant_pool, c.constant_pool_count);
  char *this_class_utf8 = ConstantPool_get_utf8(c.constant_pool, c.this_class);
  char *super_class_utf8 = ConstantPool_get_utf8(c.constant_pool, c.super_class);
  char *interfaces_string = ClassFile_intefarces_to_string(c);
  char *fields_string = FieldInfo_to_string(
      c.fields, c.fields_count, c.constant_pool);
  char *methods_string = MethodInfo_to_string(
      c.methods, c.methods_count, c.constant_pool);
  char *attributes_string = AttributeInfo_to_string(
      c.attributes, c.attributes_count, c.constant_pool);
  snprintf(
      class_file_string, 1000000,
      "{\"magic_number\":\"0x%X\",\"minor_version\":%d,"
      "\"major_version\":\"%d [%s]\",\"constant_pool_count\":%d,"
      "\"constant_pool\":%s,\"access_flags\":%d,\"this_class\":\"#%d // %s\","
      "\"super_class\":\"#%d // %s\",\"interfaces_count\":%d,\"interfaces\":%s,"
      "\"fields_count\":%d,\"fields\":%s,\"methods_count\":%d,\"methods\":%s,"
      "\"attributes_count\":%d,\"attributes\":%s}",
      c.magic_number, c.minor_version, c.major_version, major_version_string,
      c.constant_pool_count, constant_pool_string, c.access_flags, c.this_class,
      this_class_utf8, c.super_class, super_class_utf8, c.interfaces_count,
      interfaces_string, c.fields_count, fields_string, c.methods_count,
      methods_string, c.attributes_count, attributes_string);
  free(major_version_string);
  free(constant_pool_string);
  free(this_class_utf8);
  free(super_class_utf8);
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
