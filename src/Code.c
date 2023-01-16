#include <stdlib.h> // malloc, free
#include <stdio.h>  // snprintf
#include <string.h> // strcpy
#include "Code.h"

Code *Code_Parse(u1 *bytes, u4 code_length)
{
  Code *code = (Code *)malloc(sizeof(Code) * code_length);
  for (u4 pc = 0; pc < code_length; pc++)
  {
    code[pc].opcode = (Opcode)bytes[pc];
    switch (code[pc].opcode)
    {
    // case: 0 operands
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
    {
      break;
    }
    // case 1 byte operands
    case OPCODE_BIPUSH:
    {
      code[pc]._1byte_operands.byte = (int8_t)bytes[pc + 1];
      pc++;
      break;
    }
    }
  }
  return code;
}

void Code_Free(Code *code, u4 code_length)
{
  free(code);
}

char *Code_0_opcodes_to_string(const char *mnemonic)
{
  char *str = (char *)malloc(32 * sizeof(char));
  return strcpy(str, mnemonic);
}

char *Code_1byte_operands_to_string(const char *mnemonic, int8_t byte, u4 *pc)
{
  char *str = (char *)malloc(256 * sizeof(char));
  snprintf(str, 32, "%s %hhd  ", mnemonic, byte);
  (*pc)++;
  return str;
}

char *Code_entry_to_string(Code code_entry, u4 *pc)
{
  switch (code_entry.opcode)
  {
  case OPCODE_NOP:
    return Code_0_opcodes_to_string("nop");
  case OPCODE_ACONST_NULL:
    return Code_0_opcodes_to_string("aconst_null");
  case OPCODE_ICONST_M1:
    return Code_0_opcodes_to_string("iconst_m1");
  case OPCODE_ICONST_0:
    return Code_0_opcodes_to_string("iconst_0");
  case OPCODE_ICONST_1:
    return Code_0_opcodes_to_string("iconst_1");
  case OPCODE_ICONST_2:
    return Code_0_opcodes_to_string("iconst_2");
  case OPCODE_ICONST_3:
    return Code_0_opcodes_to_string("iconst_3");
  case OPCODE_ICONST_4:
    return Code_0_opcodes_to_string("iconst_4");
  case OPCODE_ICONST_5:
    return Code_0_opcodes_to_string("iconst_5");
  case OPCODE_LCONST_0:
    return Code_0_opcodes_to_string("lconst_0");
  case OPCODE_LCONST_1:
    return Code_0_opcodes_to_string("lconst_1");
  case OPCODE_FCONST_0:
    return Code_0_opcodes_to_string("fconst_0");
  case OPCODE_FCONST_1:
    return Code_0_opcodes_to_string("fconst_1");
  case OPCODE_FCONST_2:
    return Code_0_opcodes_to_string("fconst_2");
  case OPCODE_DCONST_0:
    return Code_0_opcodes_to_string("dconst_0");
  case OPCODE_DCONST_1:
    return Code_0_opcodes_to_string("dconst_1");
  case OPCODE_BIPUSH:
    return Code_1byte_operands_to_string(
        "bipush", code_entry._1byte_operands.byte, pc);
  default:
    char *final_str = (char *)malloc(2048 * sizeof(char));
    snprintf(final_str, 2048, "0x%02X", code_entry.opcode);
    return final_str;
    break;
  }
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
    u4 pc_inc = 0;
    char *code_entry_str = Code_entry_to_string(code[pc], &pc_inc);
    snprintf(
        str_temp, 2048,
        "%s\"%d\":\"%s\"%c",
        str, pc, code_entry_str, separator);
    free(code_entry_str);
    free(str);
    str = str_temp;
    pc += pc_inc;
  }
  return str;
}
