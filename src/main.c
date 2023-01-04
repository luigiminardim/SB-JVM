#include "ClassFile.h"
#include <stdlib.h>
#include <stdio.h>

int main(int argc, char **argv)
{
  char default_file_name[] = "assets/test-ConstantPool/AllConstanPoolCases.class";
  char *file_name = argc > 1 ? argv[1] : default_file_name;
  FILE *fp = fopen(file_name, "rb");
  ClassFile c = ClassFile_read(fp);
  char *s = ClassFile_to_string(c);
  printf("%s\n", s);
  free(s);
  ClassFile_free(c);
  fclose(fp);
}
