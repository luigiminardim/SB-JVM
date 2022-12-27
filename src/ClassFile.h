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
} ClassFile;

ClassFile ClassFile_read(FILE *fp);

char *ClassFile_to_string(ClassFile c);
