#include <stdlib.h>
#include <string.h> // strcmp
#include "AttributeInfo.h"

// ConstantValueAttribute //////////////////////////////////////////////////////////////////////////

ConstantValueAttribute ConstantValueAttribute_read(FILE *fp) {
  ConstantValueAttribute constant_value_attribute;
  constant_value_attribute.constantvalue_index = u2_read(fp);
  return constant_value_attribute;
}

// ExceptionTable /////////////////////////////////////////////////////////////////////////////////

ExceptionTable* ExceptionTable_read(FILE *fp, u2 exception_table_length){
  ExceptionTable *table = (ExceptionTable *)malloc(exception_table_length * sizeof(ExceptionTable));
  
  for (ExceptionTable *table_entry = table; table_entry < table + exception_table_length; table_entry++){
    table_entry->start_pc = u2_read(fp);
    table_entry->end_pc = u2_read(fp);
    table_entry->handler_pc = u2_read(fp);
    table_entry->catch_type = u2_read(fp);
  }

  return table;
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
  code_attribute.exception_table = ExceptionTable_read(fp, code_attribute.exception_table_length);
  
  code_attribute.attributes_count = u2_read(fp);
  code_attribute.attributes = AttributeInfo_read(fp, code_attribute.attributes_count, constant_pool);

  return code_attribute;
}

// ExceptionsAttribute /////////////////////////////////////////////////////////////////////////////

ExceptionsAttribute ExceptionsAttribute_read(FILE *fp){
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

// SourceFileAttribute /////////////////////////////////////////////////////////////////////////////

SourceFileAttribute SourceFileAttribute_read(FILE *fp){
  SourceFileAttribute source_file_attribute;
  source_file_attribute.sourcefile_index = u2_read(fp);
  return source_file_attribute;
}

// AttributeInfo ///////////////////////////////////////////////////////////////////////////////////

AttributeInfo *AttributeInfo_read(FILE *fp, u2 attributes_count, ConstantPool constant_pool)
{
  AttributeInfo *attributes = (AttributeInfo *)malloc(attributes_count * sizeof(AttributeInfo));
  for (AttributeInfo *attribute = attributes; attribute < attributes + attributes_count; attribute++)
  {
    attribute->attribute_name_index = u2_read(fp);
    attribute->attribute_length = u4_read(fp);
    char* type = constant_pool[attribute->attribute_name_index].constant_utf8_info.bytes;
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
    //else if (!strcmp(type, "Deprecated"))
    //{
    //  attribute->attribute_deprecated_info = AttributeDeprecatedInfo_read(fp, attribute->attribute_length);
    //}
    //else if (!strcmp(type, "LineNumberTable"))
    //{
    //  attribute->attribute_line_number_table_info = AttributeLineNumberTableInfo_read(fp, attribute->attribute_length);
    //}
    //else if (!strcmp(type, "LocalVariableTable"))
    //{
    //  attribute->attribute_local_variable_table_info = AttributeLocalVariableTableInfo_read(fp, attribute->attribute_length);
    //}
    //else if (!strcmp(type, "Synthetic"))
    //{
    //  attribute->attribute_synthetic_info = AttributeSyntheticInfo_read(fp, attribute->attribute_length);
    //}
    else
    {
      // Pular attribute_length bytes caso seja atributo que não implementamos
      for (u4 i = attribute->attribute_length; i>0; i--){
        u1_read(fp);
      }
    }
  }

  return attributes;
}

void AttributeInfo_free(AttributeInfo* attributes, u2 attributes_count, ConstantPool constant_pool){
  for (AttributeInfo *attribute = attributes; attribute < attributes + attributes_count; attribute++)
  {
    char* type = constant_pool[attribute->attribute_name_index].constant_utf8_info.bytes;
    if (!strcmp(type, "Code")){
      free(attribute->code.exception_table);
      free(attribute->code.code);
      AttributeInfo_free(attribute->code.attributes, attribute->code.attributes_count, constant_pool);
    } else if (!strcmp(type, "Exceptions")){
      free(attribute->exceptions.exception_index_table);
    } else {
      continue;
    }
  }
  free(attributes);
}

// char* AttributeInfo_to_string(AttributeInfo *attribute_info);
