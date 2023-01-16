#pragma once

#include "java-bytes.h"

enum Opcode
{
  OPCODE_NOP = 0x00,
};

typedef struct
{
  Opcode opcode;
} Code;

Code *Code_Parse(u1 *bytes, u4 code_length);

void Code_Free(Code *code, u4 code_length);

char *Code_to_string(Code *code, u4 code_length);
