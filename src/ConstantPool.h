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

typedef struct ConstantMethodrefInfo
{
  u2 class_index;
  u2 name_and_type_index;
} ConstantMethodrefInfo;

typedef struct ConstantFieldrefInfo
{
  u2 class_index;
  u2 name_and_type_index;
} ConstantFieldrefInfo;

typedef struct ConstantFloatInfo
{
  float bytes;
} ConstantFloatInfo;

typedef struct ConstantLongInfo
{
  int64_t bytes;
} ConstantLongInfo;

typedef struct ConstantDoubleInfo
{
  double bytes;
} ConstantDoubleInfo;

typedef struct ConstantStringInfo
{
  u2 string_index;
} ConstantStringInfo;

typedef struct ConstantClassInfo
{
  u2 name_index;
} ConstantClassInfo;

typedef struct ConstantInterfaceMethodrefInfo
{
  u2 class_index;
  u2 name_and_type_index;
} ConstantInterfaceMethodrefInfo;

typedef struct ConstantUtf8Info
{
  u2 length;
  char *bytes;
} ConstantUtf8Info;

typedef struct ConstantIntegerInfo
{
  u4 bytes;
} ConstantIntegerInfo;

typedef struct ConstantNameAndTypeInfo
{
  u2 name_index;
  u2 descriptor_index;
} ConstantNameAndTypeInfo;

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

ConstantPool ConstantPool_read(FILE *fp, u2 constant_pool_count);

char *ConstantPool_to_string(ConstantPool cp, u2 constant_pool_count);

char *ConstantPool_get_utf8(ConstantPool cp, u2 index);

void ConstantPool_free(ConstantPool cp, u2 constant_pool_count);
