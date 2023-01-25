#pragma once

#include <stdio.h>
#include <stdint.h>
#include "java-bytes.h"

typedef enum
{
  CONSTANT_UTF8 = 1,
  CONSTANT_INTEGER = 3,
  CONSTANT_FLOAT = 4,
  CONSTANT_LONG = 5,
  CONSTANT_DOUBLE = 6,
  CONSTANT_CLASS = 7,
  CONSTANT_STRING = 8,
  CONSTANT_FIELDREF = 9,
  CONSTANT_METHODREF = 10,
  CONSTANT_INTERFACE_METHOD_REF = 11,
  CONSTANT_NAME_AND_TYPE = 12,
} ConstantType;

/**
 * @brief Cp info for Constant
 * 
 */
typedef struct ConstantMethodrefInfo
{
  u2 class_index;
  u2 name_and_type_index;
} ConstantMethodrefInfo;

/**
 * @brief Cp info for field reference
 * 
 */
typedef struct ConstantFieldrefInfo
{
  u2 class_index;
  u2 name_and_type_index;
} ConstantFieldrefInfo;

/**
 * @brief Cp info for Float
 * 
 */
typedef struct ConstantFloatInfo
{
  float bytes;
} ConstantFloatInfo;

/**
 * @brief Cp info for Long
 * 
 */
typedef struct ConstantLongInfo
{
  int64_t bytes;
} ConstantLongInfo;

/**
 * @brief Cp info for Double
 * 
 */
typedef struct ConstantDoubleInfo
{
  double bytes;
} ConstantDoubleInfo;

/**
 * @brief Cp info for String
 * 
 */
typedef struct ConstantStringInfo
{
  u2 string_index;
} ConstantStringInfo;

/**
 * @brief Cp info for Class
 * 
 */
typedef struct ConstantClassInfo
{
  u2 name_index;
} ConstantClassInfo;

/**
 * @brief Cp info for InterfaceMethod reference
 * 
 */
typedef struct ConstantInterfaceMethodrefInfo
{
  u2 class_index;
  u2 name_and_type_index;
} ConstantInterfaceMethodrefInfo;

/**
 * @brief Cp info for UTF-8
 * 
 */
typedef struct ConstantUtf8Info
{
  u2 length;
  char *bytes;
} ConstantUtf8Info;

/**
 * @brief Cp info for Integer
 * 
 */
typedef struct ConstantIntegerInfo
{
  u4 bytes;
} ConstantIntegerInfo;

/**
 * @brief Cp info for Name and Type
 * 
 */
typedef struct ConstantNameAndTypeInfo
{
  u2 name_index;
  u2 descriptor_index;
} ConstantNameAndTypeInfo;

/**
 * @brief General CP info struct
 * 
 */
typedef struct CpInfo
{
  ConstantType tag;
  union
  {
    ConstantMethodrefInfo constant_methodref_info;
    ConstantFieldrefInfo constant_fieldref_info;
    ConstantFloatInfo constant_float_info;
    ConstantLongInfo constant_long_info;
    ConstantDoubleInfo constant_double_info;
    ConstantStringInfo constant_string_info;
    ConstantClassInfo constant_class_info;
    ConstantInterfaceMethodrefInfo constant_interface_methodref_info;
    ConstantUtf8Info constant_utf8_info;
    ConstantIntegerInfo constant_integer_info;
    ConstantNameAndTypeInfo constant_name_and_type_info;
  };
} CpInfo;

typedef CpInfo *ConstantPool;

/**
 * @brief Reads CP info to memory
 * 
 * @param fp File pointer to .class file
 * @param constant_pool_count Number of CP infos in ConstantPool
 * @return ConstantPool object
 */
ConstantPool ConstantPool_read(FILE *fp, u2 constant_pool_count);

/**
 * @brief Prints CP info
 * 
 * @param cp ConstantPool object
 * @param constant_pool_count Number of CP infos in ConstantPool
 * @return char* 
 */
char *ConstantPool_to_string(ConstantPool cp, u2 constant_pool_count);

/**
 * @brief Get string from UTF-8 CP info
 * 
 * @param cp ConstantPool object
 * @param index index to CP info in Constantpool
 * @return char* 
 */
char *ConstantPool_get_utf8(ConstantPool cp, u2 index);

/**
 * @brief Free's Constantpool allocated memory
 * 
 * @param cp Constantpool object
 * @param constant_pool_count Number of CP info in ConstantPool
 */
void ConstantPool_free(ConstantPool cp, u2 constant_pool_count);
