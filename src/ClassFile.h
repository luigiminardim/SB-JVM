#pragma once

#include <stdint.h>
#include <stdio.h>
#include "java-bytes.h"
#include "ConstantPool.h"

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
  u2 fields_count;
  FieldInfo* fields[];
} ClassFile;

ClassFile ClassFile_read(FILE *fp);

char *ClassFile_to_string(ClassFile c);

void ClassFile_free(ClassFile c);
