#pragma once

#include "java-bytes.h"
#include "ConstantPool.h"
#include "Code.h"

struct AttributeInfo;

/**
 * @brief Struct that represent constant attribute
 * 
 */
typedef struct ConstantValueAttribute
{
  u2 constantvalue_index;
} ConstantValueAttribute;

/**
 * @brief Struct that represents Exception table attribute
 * 
 */
typedef struct ExceptionTable
{
  u2 start_pc;
  u2 end_pc;
  u2 handler_pc;
  u2 catch_type;
} ExceptionTable;

/**
 * @brief Struct that represents Code Attribute
 * 
 */
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

/**
 * @brief Struct that represents Exceptions Attribute
 * 
 */
typedef struct ExceptionsAttribute
{
  u2 number_of_exceptions;
  u2 *exception_index_table;
} ExceptionsAttribute;

/**
 * @brief Struct that represents SourceFile Attribute
 * 
 */
typedef struct SourceFileAttribute
{
  u2 sourcefile_index;
} SourceFileAttribute;

/**
 * @brief Struct that represents Unkown Attribute
 * 
 */
typedef struct UnknownAttribute
{
  u1 *info;
} UnknownAttribute;

/**
 * @brief General attribute struct
 * 
 */
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

/**
 * @brief Reads attribute into memory
 * 
 * @param fp File pointer to .class file
 * @param attributes_count Number of attributes
 * @param constant_pool Constantpool object
 * @return AttributeInfo* 
 */
AttributeInfo *AttributeInfo_read(FILE *fp, u2 attributes_count, ConstantPool constant_pool);

/**
 * @brief Free's allocated memory from Attribute
 * 
 * @param attributes Pointer to attributes
 * @param attributes_count Number of attributes
 * @param constant_pool Constantpool object
 */
void AttributeInfo_free(AttributeInfo *attributes, u2 attributes_count, ConstantPool constant_pool);

/**
 * @brief Prints Attributes
 * 
 * @param attribute_infos Pointer to attributes
 * @param attributes_count Number of attributes
 * @param constant_pool Constantpool object
 * @return char* 
 */
char *AttributeInfo_to_string(AttributeInfo *attribute_infos, u2 attributes_count, ConstantPool constant_pool);
