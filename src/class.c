#include "class.h"
#include "java-bytes.h"
#include <stdio.h>  // sprintf
#include <stdlib.h> // malloc

Class Class_read(FILE *fp)
{
  Class c;
  c.magic_number = u4_read(fp);
  return c;
}

char *Class_to_string(Class c)
{
  char *s = (char *)malloc(1000000);
  sprintf(s, "{__cls:\"Class\",magic_number:%X}", c.magic_number);
  return s;
}
