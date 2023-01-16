#include <stdlib.h> // malloc, free
#include <stdio.h>  // snprintf
#include "Code.h"

int Code_is_0_operands(Code code_entry)
{
  switch (code_entry.opcode)
  {
  case OPCODE_NOP:
  case OPCODE_ACONST_NULL:
  case OPCODE_ICONST_M1:
  case OPCODE_ICONST_0:
  case OPCODE_ICONST_1:
  case OPCODE_ICONST_2:
  case OPCODE_ICONST_3:
  case OPCODE_ICONST_4:
  case OPCODE_ICONST_5:
  case OPCODE_LCONST_0:
  case OPCODE_LCONST_1:
  case OPCODE_FCONST_0:
  case OPCODE_FCONST_1:
  case OPCODE_FCONST_2:
  case OPCODE_DCONST_0:
  case OPCODE_DCONST_1:
    return 1;
  default:
    return 0;
  }
}

Code *Code_Parse(u1 *bytes, u4 code_length)
{
  Code *code = (Code *)malloc(sizeof(Code) * code_length);
  for (u4 i = 0; i < code_length; i++)
  {
    code[i].opcode = (Opcode)bytes[i];
  }
  return code;
}

void Code_Free(Code *code, u4 code_length)
{
  free(code);
}

char *Code_entry_to_string(Code code_entry)
{
  char *final_str = (char *)malloc(2048 * sizeof(char));
  const char *str;
  switch (code_entry.opcode)
  {
  case OPCODE_NOP:
    str = "nop";
    break;
  case OPCODE_ACONST_NULL:
    str = "aconst_null";
    break;
  case OPCODE_ICONST_M1:
    str = "iconst_m1";
    break;
  case OPCODE_ICONST_0:
    str = "iconst_0";
    break;
  case OPCODE_ICONST_1:
    str = "iconst_1";
    break;
  case OPCODE_ICONST_2:
    str = "iconst_2";
    break;
  case OPCODE_ICONST_3:
    str = "iconst_3";
    break;
  case OPCODE_ICONST_4:
    str = "iconst_4";
    break;
  case OPCODE_ICONST_5:
    str = "iconst_5";
    break;
  case OPCODE_LCONST_0:
    str = "lconst_0";
    break;
  case OPCODE_LCONST_1:
    str = "lconst_1";
    break;
  case OPCODE_FCONST_0:
    str = "fconst_0";
    break;
  case OPCODE_FCONST_1:
    str = "fconst_1";
    break;
  case OPCODE_FCONST_2:
    str = "fconst_2";
    break;
  case OPCODE_DCONST_0:
    str = "dconst_0";
    break;
  case OPCODE_DCONST_1:
    str = "dconst_1";
    break;
  default:
    snprintf(final_str, 2048, "\"0x%02X\"", code_entry.opcode);
    return final_str;
    break;
  }
  snprintf(final_str, 2048, "\"%s\"", str);
  return final_str;
}

char *Code_to_string(Code *code, u4 code_lenght)
{
  char *str = (char *)malloc(2048 * sizeof(char));
  if (code_lenght == 0)
  {
    snprintf(str, 2048, "{}");
    return str;
  }
  snprintf(str, 2048, "{");
  for (u4 pc = 0; pc < code_lenght; pc++)
  {
    char *str_temp = (char *)malloc(2048 * sizeof(char));
    char separator = (pc == code_lenght - 1) ? '}' : ',';
    char *code_entry_str = Code_entry_to_string(code[pc]);
    snprintf(
        str_temp, 2048,
        "%s\"%d\":%s%c",
        str, pc, code_entry_str, separator);
    free(code_entry_str);
    free(str);
    str = str_temp;
  }
  return str;
}
