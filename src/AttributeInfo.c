#include <stdlib.h>
#include "AttributeInfo.h"

// ConstantValueAttribute //////////////////////////////////////////////////////////////////////////

ConstantValueAttribute ConstantValueAttribute_read(FILE *fp) {
  ConstantValueAttribute constant_value_attribute;
  constant_value_attribute.constantvalue_index = u2_read(fp);
  return constant_value_attribute;
}

// CodeAttribute ///////////////////////////////////////////////////////////////////////////////////

CodeAttribute CodeAttribute_read(FILE *fp, ConstantPool constant_pool) {
  CodeAttribute code_attribute;
  code_attribute.max_stack = u2_read(fp);
  code_attribute.max_locals = u2_read(fp);
  code_attribute.code_length = u4_read(fp);
  code_attribute.code = (u1 *)malloc(code_attribute.code_length * sizeof(u1));
  for (u1 *code = code_attribute.code; code < code_attribute.code + code_attribute.code_length; code++)
  {
    *code = u1_read(fp);
  }
  code_attribute.exception_table_length = u2_read(fp);
}

// AttributeInfo ///////////////////////////////////////////////////////////////////////////////////

AttributeInfo *AttributeInfo_read(FILE *fp, u2 attributes_count, ConstantPool constant_pool)
{
  AttributeInfo *attributes = (AttributeInfo *)malloc(attributes_count * sizeof(AttributeInfo));
  printf("attributes_count: %d\n", attributes_count);
  for (AttributeInfo *attribute = attributes; attribute < attributes + attributes_count; attribute++)
  {
    attribute->attribute_name_index = u2_read(fp);
    attribute->attribute_length = u4_read(fp);
    char* type = constant_pool[attribute->attribute_name_index].constant_utf8_info.bytes;
    if (!strcmp(type, "Code"))
    {
      attribute->attribute_code_info = AttributeCodeInfo_read(fp, attribute->attribute_length);
    }
    else if (!strcmp(type, "ConstantValue"))
    {
      attribute->attribute_constant_value_info = AttributeConstantValueInfo_read(fp, attribute->attribute_length);
    }
    else if (!strcmp(type, "Deprecated"))
    {
      attribute->attribute_deprecated_info = AttributeDeprecatedInfo_read(fp, attribute->attribute_length);
    }
    else if (!strcmp(type, "Exceptions"))
    {
      attribute->attribute_exceptions_info = AttributeExceptionsInfo_read(fp, attribute->attribute_length);
    }
    else if (!strcmp(type, "LineNumberTable"))
    {
      attribute->attribute_line_number_table_info = AttributeLineNumberTableInfo_read(fp, attribute->attribute_length);
    }
    else if (!strcmp(type, "LocalVariableTable"))
    {
      attribute->attribute_local_variable_table_info = AttributeLocalVariableTableInfo_read(fp, attribute->attribute_length);
    }
    else if (!strcmp(type, "SourceFile"))
    {
      attribute->attribute_source_file_info = AttributeSourceFileInfo_read(fp, attribute->attribute_length);
    }
    else if (!strcmp(type, "Synthetic"))
    {
      attribute->attribute_synthetic_info = AttributeSyntheticInfo_read(fp, attribute->attribute_length);
    }
    else
    {
      printf("Unknown attribute type: %s", type);
      exit(1);
    }
  }
}

// char* AttributeInfo_to_string(AttributeInfo *attribute_info);
