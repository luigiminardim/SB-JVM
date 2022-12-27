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
  c.constant_pool = ConstantPool_read(fp, c.constant_pool_count);
  return c;
}

char *ClassFile_to_string(ClassFile c)
{
  char *class_file_string = (char *)malloc(1000000);
  char *constant_pool_string = ConstantPool_to_string(c.constant_pool, c.constant_pool_count);
  sprintf(class_file_string, "{\"__cls\":\"ClassFile\",\"magic_number\":\"0x%X\",\"minor_version\":%d,\"major_version\":%d,\"constant_pool_count\":%d,\"constant_pool\":%s}", c.magic_number, c.minor_version, c.major_version, c.constant_pool_count, constant_pool_string);
  free(constant_pool_string);
  return class_file_string;
}
