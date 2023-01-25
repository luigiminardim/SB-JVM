#pragma once

#include "java-bytes.h"
#include "ConstantPool.h"
#include "Code.h"

struct AttributeInfo;

/**
 * @brief É atributo
 * 
 */
typedef struct ConstantValueAttribute
{
  u2 constantvalue_index;
} ConstantValueAttribute;

typedef struct ExceptionTable
{
  u2 start_pc;
  u2 end_pc;
  u2 handler_pc;
  u2 catch_type;
} ExceptionTable;

typedef struct CodeAttribute
{
  u2 max_stack;
  u2 max_locals;
  u4 code_length;
  Code *code;
  u2 exception_table_length;
  ExceptionTable *exception_table;
  u2 attributes_count;
  AttributeInfo *attributes;
} CodeAttribute;

typedef struct ExceptionsAttribute
{
  u2 number_of_exceptions;
  u2 *exception_index_table;
} ExceptionsAttribute;

typedef struct SourceFileAttribute
{
  u2 sourcefile_index;
} SourceFileAttribute;

typedef struct UnknownAttribute
{
  u1 *info;
} UnknownAttribute;

typedef struct AttributeInfo
{
  u2 attribute_name_index;
  u4 attribute_length;
  union
  {
    ConstantValueAttribute constant_value;
    CodeAttribute code;
    ExceptionsAttribute exceptions;
    SourceFileAttribute source_file;
    UnknownAttribute unknown;
  };
} AttributeInfo;

AttributeInfo *AttributeInfo_read(FILE *fp, u2 attributes_count, ConstantPool constant_pool);

void AttributeInfo_free(AttributeInfo *attributes, u2 attributes_count, ConstantPool constant_pool);

char *AttributeInfo_to_string(AttributeInfo *attribute_infos, u2 attributes_count, ConstantPool constant_pool);
