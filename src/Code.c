#include <stdlib.h> // malloc, free
#include <stdio.h>  // snprintf
#include "Code.h"

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
  char *str;
  switch (code_entry.opcode)
  {
  case OPCODE_NOP:
    str = "nop";
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
