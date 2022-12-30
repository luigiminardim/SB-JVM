#pragma once

#include <stdint.h>
#include <stdio.h>
#include "java-bytes.h"
#include "AttributeInfo.h"

typedef struct MethodInfo {
  u2 access_flags;
  u2 name_index;
  u2 descriptor_index;
  u2 attributes_count;
  AttributeInfo* attributes;
} MethodInfo;

MethodInfo* MethodInfo_read(FILE *fp, u2 methods_count, ConstantPool constant_pool);
void MethodInfo_free(MethodInfo *method_info, u2 methods_count, ConstantPool constant_pool);
char* MethodInfo_to_string(MethodInfo mield_info);