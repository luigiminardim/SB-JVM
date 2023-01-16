#pragma once

#include "java-bytes.h"

enum Opcode
{
  OPCODE_NOP = 0x00,
  OPCODE_ACONST_NULL = 0x01,
  OPCODE_ICONST_M1 = 0x02,
  OPCODE_ICONST_0 = 0x03,
  OPCODE_ICONST_1 = 0x04,
  OPCODE_ICONST_2 = 0x05,
  OPCODE_ICONST_3 = 0x06,
  OPCODE_ICONST_4 = 0x07,
  OPCODE_ICONST_5 = 0x08,
  OPCODE_LCONST_0 = 0x09,
  OPCODE_LCONST_1 = 0x0A,
  OPCODE_FCONST_0 = 0x0B,
  OPCODE_FCONST_1 = 0x0C,
  OPCODE_FCONST_2 = 0x0D,
  OPCODE_DCONST_0 = 0x0E,
  OPCODE_DCONST_1 = 0x0F,
};

typedef struct
{
  Opcode opcode;
} Code;

Code *Code_Parse(u1 *bytes, u4 code_length);

void Code_Free(Code *code, u4 code_length);

char *Code_to_string(Code *code, u4 code_length);
