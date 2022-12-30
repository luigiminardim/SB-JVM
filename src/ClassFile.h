#pragma once

#include <stdint.h>
#include <stdio.h>
#include "java-bytes.h"
#include "ConstantPool.h"
#include "Field.h"
#include "Method.h"

typedef struct ClassFile
{
  u4 magic_number;
  u2 minor_version;
  u2 major_version;
  u2 constant_pool_count;
  ConstantPool constant_pool;
  u2 access_flags;
  u2 this_class;
  u2 super_class;
  u2 interfaces_count;
  u2 *interfaces;
  u2 fields_count;
  FieldInfo* fields;
  u2 methods_count;
  MethodInfo* methods;
  u2 attributes_count;
  AttributeInfo* attributes;
} ClassFile;

ClassFile ClassFile_read(FILE *fp);

char *ClassFile_to_string(ClassFile c);

void ClassFile_free(ClassFile c);
