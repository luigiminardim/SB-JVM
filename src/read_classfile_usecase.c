#include <stdlib.h>
#include <stdio.h>
#include "ClassFile.h"

const char *DEFAULT_FILE_NAME = "assets/test-ConstantPool/AllConstanPoolCases.class";

void read_classfile_usecase(const char *filename_or_null)
{
  const char *file_name = filename_or_null != NULL
                              ? filename_or_null
                              : DEFAULT_FILE_NAME;
  FILE *fp = fopen(file_name, "rb");
  ClassFile c = ClassFile_read(fp);
  char *s = ClassFile_to_string(c);
  printf("%s\n", s);
  free(s);
  ClassFile_free(c);
  fclose(fp);
}
