#include "java-bytes.h"

// u4 //////////////////////////////////////////////////////////////////////////////////////////////
u4 u4_read(FILE *fp) {
  u4 result = 0;
  for (int i = 0; i < 4; i++)
  {
    result = (result << 8) | fgetc(fp);
  }
  return result;
}

// u2 //////////////////////////////////////////////////////////////////////////////////////////////
u2 u2_read(FILE *fp)
{
  u2 result = 0;
  for (int i = 0; i < 2; i++)
  {
    result = (result << 8) | fgetc(fp);
  }
  return result;
}

// u1 //////////////////////////////////////////////////////////////////////////////////////////////
// u1 u1_read(FILE *fp)
// {
//   return fgetc(fp);
// }
