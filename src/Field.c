#include "Field.h"
#include "ClassFile.h"
#include "java-bytes.h"
#include <stdio.h>  // sprintf
#include <stdlib.h> // malloc

FieldInfo *FieldInfo_read(FILE *fp, u2 fields_count, ConstantPool constant_pool)
{
  FieldInfo *fields = (FieldInfo *)malloc(fields_count * sizeof(FieldInfo));
  FieldInfo *f;
  // itera sobre os fields
  for (f = fields; f < fields + fields_count; f++)
  {
    f->access_flags = u2_read(fp);
    f->name_index = u2_read(fp);
    f->descriptor_index = u2_read(fp);
    f->attributes_count = u2_read(fp);
    f->attributes = AttributeInfo_read(fp, f->attributes_count, constant_pool);
  }
  return fields;
}

void FieldInfo_free(FieldInfo *field_infos, u2 fields_count, ConstantPool constant_pool)
{
  FieldInfo *f;
  for (f = field_infos; f < field_infos + fields_count; f++)
  {
    AttributeInfo_free(f->attributes, f->attributes_count, constant_pool);
  }
  free(field_infos);
}

char *FieldInfo_to_string(FieldInfo *field_infos, u2 fields_count, ConstantPool constant_pool)
{
  char *str = (char *)malloc(65536 * sizeof(char));
  if (fields_count == 0)
  {
    snprintf(str, 65536, "[]");
    return str;
  }
  snprintf(str, 65536, "[");
  for (FieldInfo *field_info = field_infos; field_info < field_infos + fields_count; field_info++)
  {
    char *attribute_info_str = AttributeInfo_to_string(
        field_info->attributes, field_info->attributes_count, constant_pool);
    char separator = field_info == field_infos + fields_count - 1 ? ']' : ',';
    char *str_temp = (char *)malloc(65536 * sizeof(char));
    char *name_utf8 = ConstantPool_get_utf8(
        constant_pool, field_info->name_index);
    char *descriptor_utf8 = ConstantPool_get_utf8(
        constant_pool, field_info->descriptor_index);
    snprintf(
        str_temp, 65536,
        "%s{\"access_flags\": \"0x%X\",\"name_index\":\"#%d // %s\","
        "\"descriptor_index\":\"#%d // %s\",\"attributes_count\":%d,"
        "\"attributes\":%s}%c",
        str, field_info->access_flags, field_info->name_index, name_utf8,
        field_info->descriptor_index, descriptor_utf8, field_info->attributes_count,
        attribute_info_str, separator);
    free(name_utf8);
    free(descriptor_utf8);
    free(attribute_info_str);
    free(str);
    str = str_temp;
  }
  return str;
}
