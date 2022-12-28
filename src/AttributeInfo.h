#pragma once

#include "java-bytes.h"
#include "ConstantPool.h"

struct AttributeInfo;

typedef struct ConstantValueAttribute
{
  u2 constantvalue_index;
} ConstantValueAttribute;

ConstantValueAttribute ConstantValueAttribute_read(FILE *fp);

typedef struct ExceptionTable
{
  u2 start_pc;
  u2 end_pc;
  u2 handler_pc;
  u2 catch_type;
} ExceptionTable;

ExceptionTable* ExceptionTable_read(FILE *fp, u2 exception_table_length);

typedef struct CodeAttribute
{
  u2 max_stack;
  u2 max_locals;
  u4 code_length;
  u1 *code;
  u2 exception_table_length;
  ExceptionTable *exception_table;
  u2 attributes_count;
  AttributeInfo *attributes;
} CodeAttribute;

CodeAttribute CodeAttribute_read(FILE *fp, ConstantPool constant_pool);

typedef struct ExceptionsAttribute
{
  u2 number_of_exceptions;
  u2 *exception_index_table;
} ExceptionsAttribute;

ExceptionsAttribute ExceptionsAttribute_read(FILE *fp);

// @todo Maybe implement this later
// typedef struct InnerClassesAttribute
// {
//   u2 number_of_classes;
//   InnerClass *classes;
// } InnerClassesAttribute;

typedef struct SourceFileAttribute
{
  u2 sourcefile_index;
} SourceFileAttribute;

typedef struct AttributeInfo
{
  u2 attribute_name_index;
  u4 attribute_length;
  union
  {
    ConstantValueAttribute constant_value;
    CodeAttribute code;
    ExceptionsAttribute exceptions;
    // InnerClassesAttribute inner_classes; @todo Maybe implement this later
    SourceFileAttribute source_file;
  };
} AttributeInfo;

AttributeInfo* AttributeInfo_read(FILE *fp, u2 attributes_count, ConstantPool constant_pool);

void AttributeInfo_free(AttributeInfo* attributes, u2 attributes_count, ConstantPool constant_pool);

char* AttributeInfo_to_string(AttributeInfo *attribute_info);

