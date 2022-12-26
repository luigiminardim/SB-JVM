#include "ClassFile.h"
#include "java-bytes.h"
#include <stdio.h>  // sprintf
#include <stdlib.h> // malloc

ClassFile ClassFile_read(FILE *fp)
{
  ClassFile c;
  c.magic_number = u4_read(fp);
  c.minor_version = u2_read(fp);
  c.major_version = u2_read(fp);
  c.constant_pool_count = u2_read(fp);
  return c;
}

char *ClassFile_to_string(ClassFile c)
{
  char *s = (char *)malloc(1000000);
  sprintf(s, "{__cls:\"ClassFile\",magic_number:%X;minor_version:%d;major_version:%d;constant_pool_count:%d}", c.magic_number, c.minor_version, c.major_version, c.constant_pool_count);
  return s;
}
