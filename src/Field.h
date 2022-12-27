#pragma once

#include <stdint.h>
#include <stdio.h>
#include "java-bytes.h"

typedef struct FieldInfo {
  u2 access_flags;
  u2 name_index;
  u2 descriptor_index;
  u2 attributes_count;
  // AttributeInfo* attributes[];
} FieldInfo;


FieldInfo* FieldInfo_read(FILE *fp, u2 fields_count);
char* FieldInfo_to_string(FieldInfo field_info);