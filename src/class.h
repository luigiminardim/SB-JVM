#pragma once

#include <stdint.h>
#include <stdio.h>

typedef struct Class
{
  int32_t magic_number;
} Class;

Class Class_read(FILE *fp);

char* Class_to_string(Class c);
