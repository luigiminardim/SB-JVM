#include <stdlib.h>
#include <string.h> // strcmp, strcat
#include "AttributeInfo.h"

// ConstantValueAttribute //////////////////////////////////////////////////////////////////////////

ConstantValueAttribute ConstantValueAttribute_read(FILE *fp)
{
  ConstantValueAttribute constant_value_attribute;
  constant_value_attribute.constantvalue_index = u2_read(fp);
  return constant_value_attribute;
}

char *ConstantValueAttribute_to_string(
    ConstantValueAttribute constant_value_attribute, ConstantPool constant_pool)
{
  char *str = (char *)malloc(100 * sizeof(char));
  char *constant_value_utf8 = ConstantPool_get_utf8(
      constant_pool, constant_value_attribute.constantvalue_index);
  snprintf(
      str, 100,
      "\"constantvalue_index\":\"#%d // %s\"",
      constant_value_attribute.constantvalue_index, constant_value_utf8);
  free(constant_value_utf8);
  return str;
}

// ExceptionTable /////////////////////////////////////////////////////////////////////////////////

ExceptionTable *ExceptionTable_read(FILE *fp, u2 exception_table_length)
{
  ExceptionTable *table = (ExceptionTable *)malloc(exception_table_length * sizeof(ExceptionTable));
  for (ExceptionTable *table_entry = table; table_entry < table + exception_table_length; table_entry++)
  {
    table_entry->start_pc = u2_read(fp);
    table_entry->end_pc = u2_read(fp);
    table_entry->handler_pc = u2_read(fp);
    table_entry->catch_type = u2_read(fp);
  }
  return table;
}

char *ExceptionTable_to_string(ExceptionTable *table, u2 exception_table_length)
{
  char *str = (char *)malloc(2048 * sizeof(char));
  if (exception_table_length == 0)
  {
    snprintf(str, 2048, "[]");
    return str;
  }
  snprintf(str, 2048, "[");
  for (ExceptionTable *table_entry = table; table_entry < table + exception_table_length; table_entry++)
  {
    char *str_temp = (char *)malloc(2048 * sizeof(char));
    char separator = (table_entry == table + exception_table_length - 1) ? ']' : ',';
    snprintf(
        str_temp, 2048,
        "%s{\"start_pc\":\"%d\",\"end_pc\":\"%d\",\"handler_pc\":\"%d\",\"catch_type\":\"%d\"}%c",
        str, table_entry->start_pc, table_entry->end_pc, table_entry->handler_pc,
        table_entry->catch_type, separator);
    free(str);
    str = str_temp;
  }
  return str;
}

// CodeAttribute ///////////////////////////////////////////////////////////////////////////////////

CodeAttribute CodeAttribute_read(FILE *fp, ConstantPool constant_pool)
{
  CodeAttribute code_attribute;
  code_attribute.max_stack = u2_read(fp);
  code_attribute.max_locals = u2_read(fp);
  code_attribute.code_length = u4_read(fp);
  u1 *code_bytes = (u1 *)malloc(code_attribute.code_length * sizeof(u1));
  for (u1 *code_entry = code_bytes;
       code_entry < code_bytes + code_attribute.code_length;
       code_entry++)
  {
    *code_entry = u1_read(fp);
  }
  code_attribute.code = Code_Parse(code_bytes, code_attribute.code_length);
  free(code_bytes);
  code_attribute.exception_table_length = u2_read(fp);
  code_attribute.exception_table = ExceptionTable_read(fp, code_attribute.exception_table_length);
  code_attribute.attributes_count = u2_read(fp);
  code_attribute.attributes = AttributeInfo_read(fp, code_attribute.attributes_count, constant_pool);
  return code_attribute;
}

void CodeAttribute_free(CodeAttribute code_attribute, ConstantPool constant_pool)
{
  Code_Free(code_attribute.code, code_attribute.code_length);
  free(code_attribute.exception_table);
  AttributeInfo_free(
      code_attribute.attributes,
      code_attribute.attributes_count,
      constant_pool);
}

char *CodeAttribute_to_string(CodeAttribute code_attribute, ConstantPool constant_pool)
{
  char *str = (char *)malloc(65536 * sizeof(char));
  char *exception_table_str = ExceptionTable_to_string(
      code_attribute.exception_table,
      code_attribute.exception_table_length);
  char *instructions_str = Code_to_string(
      code_attribute.code, code_attribute.code_length, constant_pool);
  char *attributes_str = AttributeInfo_to_string(
      code_attribute.attributes,
      code_attribute.attributes_count,
      constant_pool);
  snprintf(str, 65536,
           "\"max_stack\":%d,\"max_locals\":%d,\"code_length\":%d,\"code\":%s,\"exception_table_length\":%d,\"exception_table\":%s,\"attributes_count\":%d,\"attributes\":%s",
           code_attribute.max_stack, code_attribute.max_locals, code_attribute.code_length,
           instructions_str, code_attribute.exception_table_length, exception_table_str,
           code_attribute.attributes_count, attributes_str);
  free(exception_table_str);
  free(instructions_str);
  free(attributes_str);
  return str;
}

// ExceptionsAttribute /////////////////////////////////////////////////////////////////////////////

ExceptionsAttribute ExceptionsAttribute_read(FILE *fp)
{
  ExceptionsAttribute exception_attribute;
  exception_attribute.number_of_exceptions = u2_read(fp);
  exception_attribute.exception_index_table = (u2 *)malloc(exception_attribute.number_of_exceptions * sizeof(u2));
  for (u2 *entry = exception_attribute.exception_index_table;
       entry < exception_attribute.exception_index_table + exception_attribute.number_of_exceptions; entry++)
  {
    *entry = u2_read(fp);
  }
  return exception_attribute;
}

char *ExceptionsAttribute_to_string(ExceptionsAttribute exceptions_attribute)
{
  char *str = (char *)malloc(2048 * sizeof(char));
  snprintf(
      str, 2048,
      "\"number_of_exceptions\":%d,\"exception_index_table\":[",
      exceptions_attribute.number_of_exceptions);
  if (exceptions_attribute.number_of_exceptions == 0)
  {
    strcat(str, "]");
  }
  for (u2 *entry = exceptions_attribute.exception_index_table;
       entry < exceptions_attribute.exception_index_table + exceptions_attribute.number_of_exceptions;
       entry++)
  {
    char str_temp[2048];
    char separator = (entry == exceptions_attribute.exception_index_table + exceptions_attribute.number_of_exceptions - 1)
                         ? ']'
                         : ',';
    snprintf(
        str_temp, 2048,
        "%s\"#%d\"%c",
        str, *entry, separator);
    strcat(str, str_temp);
  }
  return str;
}

// SourceFileAttribute /////////////////////////////////////////////////////////////////////////////

SourceFileAttribute SourceFileAttribute_read(FILE *fp)
{
  SourceFileAttribute source_file_attribute;
  source_file_attribute.sourcefile_index = u2_read(fp);
  return source_file_attribute;
}

char *SourceFileAttribute_to_string(
    SourceFileAttribute source_file_attribute,
    ConstantPool constant_pool)
{
  char *str = (char *)malloc(256 * sizeof(char));
  char *sourcefile_utf8 = ConstantPool_get_utf8(
      constant_pool, source_file_attribute.sourcefile_index);
  snprintf(
      str, 256,
      "\"sourcefile_index\":\"#%d // %s\"",
      source_file_attribute.sourcefile_index, sourcefile_utf8);
  free(sourcefile_utf8);
  return str;
}

// UnknownAttribute ////////////////////////////////////////////////////////////////////////////////

UnknownAttribute UnknownAttribute_read(FILE *fp, u4 attribute_length)
{
  UnknownAttribute unknown_attribute;
  unknown_attribute.info = (u1 *)malloc(attribute_length * sizeof(u1));
  for (u1 *info = unknown_attribute.info; info < unknown_attribute.info + attribute_length; info++)
  {
    *info = u1_read(fp);
  }
  return unknown_attribute;
}

char *UnknownAttribute_to_string(UnknownAttribute unknown_attribute, u4 attribute_length)
{
  char *str = (char *)malloc(65536 * sizeof(char));
  if (attribute_length == 0)
  {
    snprintf(str, 65536, "\"info\":[]");
    return str;
  }
  snprintf(str, 65536, "\"info\":[");
  for (u1 *info = unknown_attribute.info; info < unknown_attribute.info + attribute_length; info++)
  {
    char *str_temp = (char *)malloc(65536 * sizeof(char));
    char separator = (info == unknown_attribute.info + attribute_length - 1) ? ']' : ',';
    snprintf(
        str_temp, 65536,
        "%s\"0x%X\"%c",
        str, *info, separator);
    free(str);
    str = str_temp;
  }
  return str;
}

// AttributeInfo ///////////////////////////////////////////////////////////////////////////////////

AttributeInfo *AttributeInfo_read(FILE *fp, u2 attributes_count, ConstantPool constant_pool)
{
  AttributeInfo *attributes = (AttributeInfo *)malloc(attributes_count * sizeof(AttributeInfo));
  for (AttributeInfo *attribute = attributes; attribute < attributes + attributes_count; attribute++)
  {
    attribute->attribute_name_index = u2_read(fp);
    attribute->attribute_length = u4_read(fp);
    char *type = constant_pool[attribute->attribute_name_index].constant_utf8_info.bytes;
    if (!strcmp(type, "Code"))
    {
      attribute->code = CodeAttribute_read(fp, constant_pool);
    }
    else if (!strcmp(type, "ConstantValue"))
    {
      attribute->constant_value = ConstantValueAttribute_read(fp);
    }
    else if (!strcmp(type, "Exceptions"))
    {
      attribute->exceptions = ExceptionsAttribute_read(fp);
    }
    else if (!strcmp(type, "SourceFile"))
    {
      attribute->source_file = SourceFileAttribute_read(fp);
    }
    else
    {
      attribute->unknown = UnknownAttribute_read(fp, attribute->attribute_length);
    }
  }
  return attributes;
}

void AttributeInfo_free(AttributeInfo *attributes, u2 attributes_count, ConstantPool constant_pool)
{
  for (AttributeInfo *attribute = attributes; attribute < attributes + attributes_count; attribute++)
  {
    char *type = constant_pool[attribute->attribute_name_index].constant_utf8_info.bytes;
    if (!strcmp(type, "Code"))
    {
      CodeAttribute_free(attribute->code, constant_pool);
    }
    else if (!strcmp(type, "Exceptions"))
    {
      free(attribute->exceptions.exception_index_table);
    }
    else if (!strcmp(type, "ConstantValue"))
    {
      continue;
    }
    else if (!strcmp(type, "SourceFile"))
    {
      continue;
    }
    else
    {
      free(attribute->unknown.info);
    }
  }
  free(attributes);
}

char *AttributeInfo_to_string(
    AttributeInfo *attribute_infos,
    u2 attributes_count,
    ConstantPool constant_pool)
{
  char *str = (char *)malloc(65536 * sizeof(char));
  if (attributes_count == 0)
  {
    snprintf(str, 65536, "[]");
    return str;
  }
  snprintf(str, 65536, "[");
  for (AttributeInfo *attribute = attribute_infos; attribute < attribute_infos + attributes_count; attribute++)
  {
    char *str_temp = (char *)malloc(65536 * sizeof(char));
    char *str_union;
    char *type = constant_pool[attribute->attribute_name_index].constant_utf8_info.bytes;
    if (!strcmp(type, "Code"))
    {
      str_union = CodeAttribute_to_string(attribute->code, constant_pool);
    }
    else if (!strcmp(type, "ConstantValue"))
    {
      str_union = ConstantValueAttribute_to_string(attribute->constant_value, constant_pool);
    }
    else if (!strcmp(type, "Exceptions"))
    {
      str_union = ExceptionsAttribute_to_string(attribute->exceptions);
    }
    else if (!strcmp(type, "SourceFile"))
    {
      str_union = SourceFileAttribute_to_string(
          attribute->source_file, constant_pool);
    }
    else
    {
      str_union = UnknownAttribute_to_string(attribute->unknown, attribute->attribute_length);
    }
    char separator = attribute == attribute_infos + attributes_count - 1 ? ']' : ',';
    char *attribute_name_utf8 = ConstantPool_get_utf8(
        constant_pool, attribute->attribute_name_index);
    snprintf(
        str_temp, 65536,
        "%s{\"attribute_name_index\":\"#%d // %s\",\"attribute_lenght\":%d,%s}%c",
        str, attribute->attribute_name_index, attribute_name_utf8,
        attribute->attribute_length, str_union, separator);
    free(str_union);
    free(attribute_name_utf8);
    free(str);
    str = str_temp;
  }
  return str;
}
