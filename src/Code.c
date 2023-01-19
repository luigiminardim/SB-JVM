#include <stdlib.h> // malloc, free
#include <stdio.h>  // snprintf
#include <string.h> // strcpy, strlen, strcpy, strcat
#include "Code.h"

int Code__parse_none_operands(
    Code *code, const char *mnemonic, u1 *bytes, u4 pc)
{
  code->mnemonic = (char *)malloc(sizeof(char) * (strlen(mnemonic) + 1));
  strcpy(code->mnemonic, mnemonic);
  code->operand_type = OPERAND_TYPE_NONE;
  return 0;
}

int Code__parse_byte_operands(
    Code *code, const char *mnemonic, u1 *bytes, u4 pc)
{
  code->mnemonic = (char *)malloc(sizeof(char) * (strlen(mnemonic) + 1));
  strcpy(code->mnemonic, mnemonic);
  code->operand_type = OPERAND_TYPE_BYTE;
  code->byte_operands.byte = bytes[pc + 1];
  return 1;
}

int Code__parse_short_operands(
    Code *code, const char *mnemonic, u1 *bytes, u4 pc)
{
  code->mnemonic = (char *)malloc(sizeof(char) * (strlen(mnemonic) + 1));
  strcpy(code->mnemonic, mnemonic);
  code->operand_type = OPERAND_TYPE_SHORT;
  code->short_operands.short_ = bytes[pc + 1] << 8 | bytes[pc + 2];
  return 2;
}

int Code__parse_cpindex_operands(Code *code, const char *mnemonic, u1 *bytes, u4 pc, int operands_num_bytes)
{
  code->mnemonic = (char *)malloc(sizeof(char) * (strlen(mnemonic) + 1));
  strcpy(code->mnemonic, mnemonic);
  code->operand_type = OPERAND_TYPE_CPINDEX;
  code->cpindex_operands.operands_num_bytes = operands_num_bytes;
  u2 cp_index = 0;
  for (int i = 1; i <= operands_num_bytes; i++)
  {
    cp_index = cp_index << 8 | bytes[pc + i];
  }
  code->cpindex_operands.cpindex = cp_index;
  return operands_num_bytes;
}

int Code__parse_byte_byte_operands(Code *code, const char *mnemonic, u1 *bytes, u4 pc)
{
  code->mnemonic = (char *)malloc(sizeof(char) * (strlen(mnemonic) + 1));
  strcpy(code->mnemonic, mnemonic);
  code->operand_type = OPERAND_TYPE_BYTE_BYTE;
  code->byte_byte_operands.index = bytes[pc + 1];
  code->byte_byte_operands.const_ = bytes[pc + 2];
  return 2;
}

Code *Code_Parse(u1 *bytes, u4 code_length)
{
  Code *code = (Code *)malloc(sizeof(Code) * code_length);
  for (u4 pc = 0; pc < code_length; pc++)
  {
    code[pc].opcode = (Opcode)bytes[pc];
    int op_size;
    switch (code[pc].opcode)
    {
    case OPCODE_NOP:
      op_size = Code__parse_none_operands(&code[pc], "nop", bytes, pc);
      break;
    case OPCODE_ACONST_NULL:
      op_size = Code__parse_none_operands(&code[pc], "aconst_null", bytes, pc);
      break;
    case OPCODE_ICONST_M1:
      op_size = Code__parse_none_operands(&code[pc], "iconst_m1", bytes, pc);
      break;
    case OPCODE_ICONST_0:
      op_size = Code__parse_none_operands(&code[pc], "iconst_0", bytes, pc);
      break;
    case OPCODE_ICONST_1:
      op_size = Code__parse_none_operands(&code[pc], "iconst_1", bytes, pc);
      break;
    case OPCODE_ICONST_2:
      op_size = Code__parse_none_operands(&code[pc], "iconst_2", bytes, pc);
      break;
    case OPCODE_ICONST_3:
      op_size = Code__parse_none_operands(&code[pc], "iconst_3", bytes, pc);
      break;
    case OPCODE_ICONST_4:
      op_size = Code__parse_none_operands(&code[pc], "iconst_4", bytes, pc);
      break;
    case OPCODE_ICONST_5:
      op_size = Code__parse_none_operands(&code[pc], "iconst_5", bytes, pc);
      break;
    case OPCODE_LCONST_0:
      op_size = Code__parse_none_operands(&code[pc], "lconst_0", bytes, pc);
      break;
    case OPCODE_LCONST_1:
      op_size = Code__parse_none_operands(&code[pc], "lconst_1", bytes, pc);
      break;
    case OPCODE_FCONST_0:
      op_size = Code__parse_none_operands(&code[pc], "fconst_0", bytes, pc);
      break;
    case OPCODE_FCONST_1:
      op_size = Code__parse_none_operands(&code[pc], "fconst_1", bytes, pc);
      break;
    case OPCODE_FCONST_2:
      op_size = Code__parse_none_operands(&code[pc], "fconst_2", bytes, pc);
      break;
    case OPCODE_DCONST_0:
      op_size = Code__parse_none_operands(&code[pc], "dconst_0", bytes, pc);
      break;
    case OPCODE_DCONST_1:
      op_size = Code__parse_none_operands(&code[pc], "dconst_1", bytes, pc);
      break;
    case OPCODE_BIPUSH:
      op_size = Code__parse_byte_operands(&code[pc], "bipush", bytes, pc);
      break;
    case OPCODE_SIPUSH:
      op_size = Code__parse_short_operands(&code[pc], "sipush", bytes, pc);
      break;
    case OPCODE_LDC:
      op_size = Code__parse_cpindex_operands(&code[pc], "ldc", bytes, pc, 1);
      break;
    case OPCODE_LDC_W:
      op_size = Code__parse_cpindex_operands(&code[pc], "ldc_w", bytes, pc, 2);
      break;
    case OPCODE_LDC2_W:
      op_size = Code__parse_cpindex_operands(&code[pc], "ldc2_w", bytes, pc, 2);
      break;
    case OPCODE_ILOAD:
      op_size = Code__parse_byte_operands(&code[pc], "iload", bytes, pc);
      break;
    case OPCODE_LLOAD:
      op_size = Code__parse_byte_operands(&code[pc], "lload", bytes, pc);
      break;
    case OPCODE_FLOAD:
      op_size = Code__parse_byte_operands(&code[pc], "fload", bytes, pc);
      break;
    case OPCODE_DLOAD:
      op_size = Code__parse_byte_operands(&code[pc], "dload", bytes, pc);
      break;
    case OPCODE_ALOAD:
      op_size = Code__parse_byte_operands(&code[pc], "aload", bytes, pc);
      break;
    case OPCODE_ILOAD_0:
      op_size = Code__parse_none_operands(&code[pc], "iload_0", bytes, pc);
      break;
    case OPCODE_ILOAD_1:
      op_size = Code__parse_none_operands(&code[pc], "iload_1", bytes, pc);
      break;
    case OPCODE_ILOAD_2:
      op_size = Code__parse_none_operands(&code[pc], "iload_2", bytes, pc);
      break;
    case OPCODE_ILOAD_3:
      op_size = Code__parse_none_operands(&code[pc], "iload_3", bytes, pc);
      break;
    case OPCODE_LLOAD_0:
      op_size = Code__parse_none_operands(&code[pc], "lload_0", bytes, pc);
      break;
    case OPCODE_LLOAD_1:
      op_size = Code__parse_none_operands(&code[pc], "lload_1", bytes, pc);
      break;
    case OPCODE_LLOAD_2:
      op_size = Code__parse_none_operands(&code[pc], "lload_2", bytes, pc);
      break;
    case OPCODE_LLOAD_3:
      op_size = Code__parse_none_operands(&code[pc], "lload_3", bytes, pc);
      break;
    case OPCODE_FLOAD_0:
      op_size = Code__parse_none_operands(&code[pc], "fload_0", bytes, pc);
      break;
    case OPCODE_FLOAD_1:
      op_size = Code__parse_none_operands(&code[pc], "fload_1", bytes, pc);
      break;
    case OPCODE_FLOAD_2:
      op_size = Code__parse_none_operands(&code[pc], "fload_2", bytes, pc);
      break;
    case OPCODE_FLOAD_3:
      op_size = Code__parse_none_operands(&code[pc], "fload_3", bytes, pc);
      break;
    case OPCODE_DLOAD_0:
      op_size = Code__parse_none_operands(&code[pc], "dload_0", bytes, pc);
      break;
    case OPCODE_DLOAD_1:
      op_size = Code__parse_none_operands(&code[pc], "dload_1", bytes, pc);
      break;
    case OPCODE_DLOAD_2:
      op_size = Code__parse_none_operands(&code[pc], "dload_2", bytes, pc);
      break;
    case OPCODE_DLOAD_3:
      op_size = Code__parse_none_operands(&code[pc], "dload_3", bytes, pc);
      break;
    case OPCODE_ALOAD_0:
      op_size = Code__parse_none_operands(&code[pc], "aload_0", bytes, pc);
      break;
    case OPCODE_ALOAD_1:
      op_size = Code__parse_none_operands(&code[pc], "aload_1", bytes, pc);
      break;
    case OPCODE_ALOAD_2:
      op_size = Code__parse_none_operands(&code[pc], "aload_2", bytes, pc);
      break;
    case OPCODE_ALOAD_3:
      op_size = Code__parse_none_operands(&code[pc], "aload_3", bytes, pc);
      break;
    case OPCODE_IALOAD:
      op_size = Code__parse_none_operands(&code[pc], "iaload", bytes, pc);
      break;
    case OPCODE_LALOAD:
      op_size = Code__parse_none_operands(&code[pc], "laload", bytes, pc);
      break;
    case OPCODE_FALOAD:
      op_size = Code__parse_none_operands(&code[pc], "faload", bytes, pc);
      break;
    case OPCODE_DALOAD:
      op_size = Code__parse_none_operands(&code[pc], "daload", bytes, pc);
      break;
    case OPCODE_AALOAD:
      op_size = Code__parse_none_operands(&code[pc], "aaload", bytes, pc);
      break;
    case OPCODE_BALOAD:
      op_size = Code__parse_none_operands(&code[pc], "baload", bytes, pc);
      break;
    case OPCODE_CALOAD:
      op_size = Code__parse_none_operands(&code[pc], "caload", bytes, pc);
      break;
    case OPCODE_SALOAD:
      op_size = Code__parse_none_operands(&code[pc], "saload", bytes, pc);
      break;
    case OPCODE_ISTORE:
      op_size = Code__parse_byte_operands(&code[pc], "istore", bytes, pc);
      break;
    case OPCODE_LSTORE:
      op_size = Code__parse_byte_operands(&code[pc], "lstore", bytes, pc);
      break;
    case OPCODE_FSTORE:
      op_size = Code__parse_byte_operands(&code[pc], "fstore", bytes, pc);
      break;
    case OPCODE_DSTORE:
      op_size = Code__parse_byte_operands(&code[pc], "dstore", bytes, pc);
      break;
    case OPCODE_ASTORE:
      op_size = Code__parse_byte_operands(&code[pc], "astore", bytes, pc);
      break;
    case OPCODE_ISTORE_0:
      op_size = Code__parse_none_operands(&code[pc], "istore_0", bytes, pc);
      break;
    case OPCODE_ISTORE_1:
      op_size = Code__parse_none_operands(&code[pc], "istore_1", bytes, pc);
      break;
    case OPCODE_ISTORE_2:
      op_size = Code__parse_none_operands(&code[pc], "istore_2", bytes, pc);
      break;
    case OPCODE_ISTORE_3:
      op_size = Code__parse_none_operands(&code[pc], "istore_3", bytes, pc);
      break;
    case OPCODE_LSTORE_0:
      op_size = Code__parse_none_operands(&code[pc], "lstore_0", bytes, pc);
      break;
    case OPCODE_LSTORE_1:
      op_size = Code__parse_none_operands(&code[pc], "lstore_1", bytes, pc);
      break;
    case OPCODE_LSTORE_2:
      op_size = Code__parse_none_operands(&code[pc], "lstore_2", bytes, pc);
      break;
    case OPCODE_LSTORE_3:
      op_size = Code__parse_none_operands(&code[pc], "lstore_3", bytes, pc);
      break;
    case OPCODE_FSTORE_0:
      op_size = Code__parse_none_operands(&code[pc], "fstore_0", bytes, pc);
      break;
    case OPCODE_FSTORE_1:
      op_size = Code__parse_none_operands(&code[pc], "fstore_1", bytes, pc);
      break;
    case OPCODE_FSTORE_2:
      op_size = Code__parse_none_operands(&code[pc], "fstore_2", bytes, pc);
      break;
    case OPCODE_FSTORE_3:
      op_size = Code__parse_none_operands(&code[pc], "fstore_3", bytes, pc);
      break;
    case OPCODE_DSTORE_0:
      op_size = Code__parse_none_operands(&code[pc], "dstore_0", bytes, pc);
      break;
    case OPCODE_DSTORE_1:
      op_size = Code__parse_none_operands(&code[pc], "dstore_1", bytes, pc);
      break;
    case OPCODE_DSTORE_2:
      op_size = Code__parse_none_operands(&code[pc], "dstore_2", bytes, pc);
      break;
    case OPCODE_DSTORE_3:
      op_size = Code__parse_none_operands(&code[pc], "dstore_3", bytes, pc);
      break;
    case OPCODE_ASTORE_0:
      op_size = Code__parse_none_operands(&code[pc], "astore_0", bytes, pc);
      break;
    case OPCODE_ASTORE_1:
      op_size = Code__parse_none_operands(&code[pc], "astore_1", bytes, pc);
      break;
    case OPCODE_ASTORE_2:
      op_size = Code__parse_none_operands(&code[pc], "astore_2", bytes, pc);
      break;
    case OPCODE_ASTORE_3:
      op_size = Code__parse_none_operands(&code[pc], "astore_3", bytes, pc);
      break;
    case OPCODE_IASTORE:
      op_size = Code__parse_none_operands(&code[pc], "iastore", bytes, pc);
      break;
    case OPCODE_LASTORE:
      op_size = Code__parse_none_operands(&code[pc], "lastore", bytes, pc);
      break;
    case OPCODE_FASTORE:
      op_size = Code__parse_none_operands(&code[pc], "fastore", bytes, pc);
      break;
    case OPCODE_DASTORE:
      op_size = Code__parse_none_operands(&code[pc], "dastore", bytes, pc);
      break;
    case OPCODE_AASTORE:
      op_size = Code__parse_none_operands(&code[pc], "aastore", bytes, pc);
      break;
    case OPCODE_BASTORE:
      op_size = Code__parse_none_operands(&code[pc], "bastore", bytes, pc);
      break;
    case OPCODE_CASTORE:
      op_size = Code__parse_none_operands(&code[pc], "castore", bytes, pc);
      break;
    case OPCODE_SASTORE:
      op_size = Code__parse_none_operands(&code[pc], "sastore", bytes, pc);
      break;
    case OPCODE_POP:
      op_size = Code__parse_none_operands(&code[pc], "pop", bytes, pc);
      break;
    case OPCODE_POP2:
      op_size = Code__parse_none_operands(&code[pc], "pop2", bytes, pc);
      break;
    case OPCODE_DUP:
      op_size = Code__parse_none_operands(&code[pc], "dup", bytes, pc);
      break;
    case OPCODE_DUP_X1:
      op_size = Code__parse_none_operands(&code[pc], "dup_x1", bytes, pc);
      break;
    case OPCODE_DUP_X2:
      op_size = Code__parse_none_operands(&code[pc], "dup_x2", bytes, pc);
      break;
    case OPCODE_DUP2:
      op_size = Code__parse_none_operands(&code[pc], "dup2", bytes, pc);
      break;
    case OPCODE_DUP2_X1:
      op_size = Code__parse_none_operands(&code[pc], "dup2_x1", bytes, pc);
      break;
    case OPCODE_DUP2_X2:
      op_size = Code__parse_none_operands(&code[pc], "dup2_x2", bytes, pc);
      break;
    case OPCODE_SWAP:
      op_size = Code__parse_none_operands(&code[pc], "swap", bytes, pc);
      break;
    case OPCODE_IADD:
      op_size = Code__parse_none_operands(&code[pc], "iadd", bytes, pc);
      break;
    case OPCODE_LADD:
      op_size = Code__parse_none_operands(&code[pc], "ladd", bytes, pc);
      break;
    case OPCODE_FADD:
      op_size = Code__parse_none_operands(&code[pc], "fadd", bytes, pc);
      break;
    case OPCODE_DADD:
      op_size = Code__parse_none_operands(&code[pc], "dadd", bytes, pc);
      break;
    case OPCODE_ISUB:
      op_size = Code__parse_none_operands(&code[pc], "isub", bytes, pc);
      break;
    case OPCODE_LSUB:
      op_size = Code__parse_none_operands(&code[pc], "lsub", bytes, pc);
      break;
    case OPCODE_FSUB:
      op_size = Code__parse_none_operands(&code[pc], "fsub", bytes, pc);
      break;
    case OPCODE_DSUB:
      op_size = Code__parse_none_operands(&code[pc], "dsub", bytes, pc);
      break;
    case OPCODE_IMUL:
      op_size = Code__parse_none_operands(&code[pc], "imul", bytes, pc);
      break;
    case OPCODE_LMUL:
      op_size = Code__parse_none_operands(&code[pc], "lmul", bytes, pc);
      break;
    case OPCODE_FMUL:
      op_size = Code__parse_none_operands(&code[pc], "fmul", bytes, pc);
      break;
    case OPCODE_DMUL:
      op_size = Code__parse_none_operands(&code[pc], "dmul", bytes, pc);
      break;
    case OPCODE_IDIV:
      op_size = Code__parse_none_operands(&code[pc], "idiv", bytes, pc);
      break;
    case OPCODE_LDIV:
      op_size = Code__parse_none_operands(&code[pc], "ldiv", bytes, pc);
      break;
    case OPCODE_FDIV:
      op_size = Code__parse_none_operands(&code[pc], "fdiv", bytes, pc);
      break;
    case OPCODE_DDIV:
      op_size = Code__parse_none_operands(&code[pc], "ddiv", bytes, pc);
      break;
    case OPCODE_IREM:
      op_size = Code__parse_none_operands(&code[pc], "irem", bytes, pc);
      break;
    case OPCODE_LREM:
      op_size = Code__parse_none_operands(&code[pc], "lrem", bytes, pc);
      break;
    case OPCODE_FREM:
      op_size = Code__parse_none_operands(&code[pc], "frem", bytes, pc);
      break;
    case OPCODE_DREM:
      op_size = Code__parse_none_operands(&code[pc], "drem", bytes, pc);
      break;
    case OPCODE_INEG:
      op_size = Code__parse_none_operands(&code[pc], "ineg", bytes, pc);
      break;
    case OPCODE_LNEG:
      op_size = Code__parse_none_operands(&code[pc], "lneg", bytes, pc);
      break;
    case OPCODE_FNEG:
      op_size = Code__parse_none_operands(&code[pc], "fneg", bytes, pc);
      break;
    case OPCODE_DNEG:
      op_size = Code__parse_none_operands(&code[pc], "dneg", bytes, pc);
      break;
    case OPCODE_ISHL:
      op_size = Code__parse_none_operands(&code[pc], "ishl", bytes, pc);
      break;
    case OPCODE_LSHL:
      op_size = Code__parse_none_operands(&code[pc], "lshl", bytes, pc);
      break;
    case OPCODE_ISHR:
      op_size = Code__parse_none_operands(&code[pc], "ishr", bytes, pc);
      break;
    case OPCODE_LSHR:
      op_size = Code__parse_none_operands(&code[pc], "lshr", bytes, pc);
      break;
    case OPCODE_IUSHR:
      op_size = Code__parse_none_operands(&code[pc], "iushr", bytes, pc);
      break;
    case OPCODE_LUSHR:
      op_size = Code__parse_none_operands(&code[pc], "lushr", bytes, pc);
      break;
    case OPCODE_IAND:
      op_size = Code__parse_none_operands(&code[pc], "iand", bytes, pc);
      break;
    case OPCODE_LAND:
      op_size = Code__parse_none_operands(&code[pc], "land", bytes, pc);
      break;
    case OPCODE_IOR:
      op_size = Code__parse_none_operands(&code[pc], "ior", bytes, pc);
      break;
    case OPCODE_LOR:
      op_size = Code__parse_none_operands(&code[pc], "lor", bytes, pc);
      break;
    case OPCODE_IXOR:
      op_size = Code__parse_none_operands(&code[pc], "ixor", bytes, pc);
      break;
    case OPCODE_LXOR:
      op_size = Code__parse_none_operands(&code[pc], "lxor", bytes, pc);
      break;
    case OPCODE_IINC:
      op_size = Code__parse_byte_byte_operands(&code[pc], "iinc", bytes, pc);
      break;
    case OPCODE_I2L:
      op_size = Code__parse_none_operands(&code[pc], "i2l", bytes, pc);
      break;
    case OPCODE_I2F:
      op_size = Code__parse_none_operands(&code[pc], "i2f", bytes, pc);
      break;
    case OPCODE_I2D:
      op_size = Code__parse_none_operands(&code[pc], "i2d", bytes, pc);
      break;
    case OPCODE_L2I:
      op_size = Code__parse_none_operands(&code[pc], "l2i", bytes, pc);
      break;
    case OPCODE_L2F:
      op_size = Code__parse_none_operands(&code[pc], "l2f", bytes, pc);
      break;
    case OPCODE_L2D:
      op_size = Code__parse_none_operands(&code[pc], "l2d", bytes, pc);
      break;
    case OPCODE_F2I:
      op_size = Code__parse_none_operands(&code[pc], "f2i", bytes, pc);
      break;
    case OPCODE_F2L:
      op_size = Code__parse_none_operands(&code[pc], "f2l", bytes, pc);
      break;
    case OPCODE_F2D:
      op_size = Code__parse_none_operands(&code[pc], "f2d", bytes, pc);
      break;
    case OPCODE_D2I:
      op_size = Code__parse_none_operands(&code[pc], "d2i", bytes, pc);
      break;
    case OPCODE_D2L:
      op_size = Code__parse_none_operands(&code[pc], "d2l", bytes, pc);
      break;
    case OPCODE_D2F:
      op_size = Code__parse_none_operands(&code[pc], "d2f", bytes, pc);
      break;
    case OPCODE_I2B:
      op_size = Code__parse_none_operands(&code[pc], "i2b", bytes, pc);
      break;
    case OPCODE_I2C:
      op_size = Code__parse_none_operands(&code[pc], "i2c", bytes, pc);
      break;
    case OPCODE_I2S:
      op_size = Code__parse_none_operands(&code[pc], "i2s", bytes, pc);
      break;
    case OPCODE_LCMP:
      op_size = Code__parse_none_operands(&code[pc], "lcmp", bytes, pc);
      break;
    case OPCODE_FCMPL:
      op_size = Code__parse_none_operands(&code[pc], "fcmpl", bytes, pc);
      break;
    case OPCODE_FCMPG:
      op_size = Code__parse_none_operands(&code[pc], "fcmpg", bytes, pc);
      break;
    case OPCODE_DCMPL:
      op_size = Code__parse_none_operands(&code[pc], "dcmpl", bytes, pc);
      break;
    case OPCODE_DCMPG:
      op_size = Code__parse_none_operands(&code[pc], "dcmpg", bytes, pc);
      break;
    case OPCODE_IFEQ:
      op_size = Code__parse_short_operands(&code[pc], "ifeq", bytes, pc);
      break;
    case OPCODE_IFNE:
      op_size = Code__parse_short_operands(&code[pc], "ifne", bytes, pc);
      break;
    case OPCODE_IFLT:
      op_size = Code__parse_short_operands(&code[pc], "iflt", bytes, pc);
      break;
    case OPCODE_IFGE:
      op_size = Code__parse_short_operands(&code[pc], "ifge", bytes, pc);
      break;
    case OPCODE_IFGT:
      op_size = Code__parse_short_operands(&code[pc], "ifgt", bytes, pc);
      break;
    case OPCODE_IFLE:
      op_size = Code__parse_short_operands(&code[pc], "ifle", bytes, pc);
      break;
    case OPCODE_IF_ICMPEQ:
      op_size = Code__parse_short_operands(&code[pc], "if_icmpeq", bytes, pc);
      break;
    case OPCODE_IF_ICMPNE:
      op_size = Code__parse_short_operands(&code[pc], "if_icmpne", bytes, pc);
      break;
    case OPCODE_IF_ICMPLT:
      op_size = Code__parse_short_operands(&code[pc], "if_icmplt", bytes, pc);
      break;
    case OPCODE_IF_ICMPGE:
      op_size = Code__parse_short_operands(&code[pc], "if_icmpge", bytes, pc);
      break;
    case OPCODE_IF_ICMPGT:
      op_size = Code__parse_short_operands(&code[pc], "if_icmpgt", bytes, pc);
      break;
    case OPCODE_IF_ICMPLE:
      op_size = Code__parse_short_operands(&code[pc], "if_icmple", bytes, pc);
      break;
    case OPCODE_IF_ACMPEQ:
      op_size = Code__parse_short_operands(&code[pc], "if_acmpeq", bytes, pc);
      break;
    case OPCODE_IF_ACMPNE:
      op_size = Code__parse_short_operands(&code[pc], "if_acmpne", bytes, pc);
      break;
    case OPCODE_GOTO:
      op_size = Code__parse_short_operands(&code[pc], "goto", bytes, pc);
      break;
    case OPCODE_JSR:
      op_size = Code__parse_short_operands(&code[pc], "jsr", bytes, pc);
      break;
    case OPCODE_RET:
      op_size = Code__parse_byte_operands(&code[pc], "ret", bytes, pc);
      break;
    // case OPCODE_TABLESWITCH:
    //   op_size = Code__parse_tableswitch_operands(&code[pc], bytes, pc);
    //   break;
    // case OPCODE_LOOKUPSWITCH:
    //   op_size = Code__parse_lookupswitch_operands(&code[pc], bytes, pc);
    //   break;
    case OPCODE_IRETURN:
      op_size = Code__parse_none_operands(&code[pc], "ireturn", bytes, pc);
      break;
    case OPCODE_LRETURN:
      op_size = Code__parse_none_operands(&code[pc], "lreturn", bytes, pc);
      break;
    case OPCODE_FRETURN:
      op_size = Code__parse_none_operands(&code[pc], "freturn", bytes, pc);
      break;
    case OPCODE_DRETURN:
      op_size = Code__parse_none_operands(&code[pc], "dreturn", bytes, pc);
      break;
    case OPCODE_ARETURN:
      op_size = Code__parse_none_operands(&code[pc], "areturn", bytes, pc);
      break;
    case OPCODE_RETURN:
      op_size = Code__parse_none_operands(&code[pc], "return", bytes, pc);
      break;
    case OPCODE_GETSTATIC:
      op_size = Code__parse_cpindex_operands(&code[pc], "getstatic", bytes, pc, 2);
      break;
    case OPCODE_PUTSTATIC:
      op_size = Code__parse_cpindex_operands(&code[pc], "putstatic", bytes, pc, 2);
      break;
    case OPCODE_GETFIELD:
      op_size = Code__parse_cpindex_operands(&code[pc], "getfield", bytes, pc, 2);
      break;
    case OPCODE_PUTFIELD:
      op_size = Code__parse_cpindex_operands(&code[pc], "putfield", bytes, pc, 2);
      break;
    case OPCODE_INVOKEVIRTUAL:
      op_size = Code__parse_cpindex_operands(&code[pc], "invokevirtual", bytes, pc, 2);
      break;
    case OPCODE_INVOKESPECIAL:
      op_size = Code__parse_cpindex_operands(&code[pc], "invokespecial", bytes, pc, 2);
      break;
    case OPCODE_INVOKESTATIC:
      op_size = Code__parse_cpindex_operands(&code[pc], "invokestatic", bytes, pc, 2);
      break;
    // case OPCODE_INVOKEINTERFACE:
    //   op_size = Code__parse_cpindex_operands(&code[pc], "invokeinterface", bytes, pc, 4);
    //   break;
    // case OPCODE_INVOKEDYNAMIC:
    //   op_size = Code__parse_cpindex_operands(&code[pc], "invokedynamic", bytes, pc, 4);
    //   break;
    case OPCODE_NEW:
      op_size = Code__parse_cpindex_operands(&code[pc], "new", bytes, pc, 2);
      break;
    case OPCODE_NEWARRAY:
      op_size = Code__parse_byte_operands(&code[pc], "newarray", bytes, pc);
      break;
    case OPCODE_ANEWARRAY:
      op_size = Code__parse_cpindex_operands(&code[pc], "anewarray", bytes, pc, 2);
      break;
    case OPCODE_ARRAYLENGTH:
      op_size = Code__parse_none_operands(&code[pc], "arraylength", bytes, pc);
      break;
    default:
      char *str = (char *)malloc(32 * sizeof(char));
      snprintf(str, 32, "0x%02X", code[pc].opcode);
      op_size = Code__parse_none_operands(&code[pc], str, bytes, pc);
      free(str);
      break;
    }
    while (op_size--)
    {
      pc++;
      code[pc].opcode = OPCODE_NONE;
    }
  }
  return code;
}

void Code_Free(Code *code, u4 code_length)
{
  for (u4 i = 0; i < code_length; i++)
  {
    if (code[i].opcode == OPCODE_NONE)
    {
      continue;
    }
    free(code[i].mnemonic);
  }
  free(code);
}

char *Code__none_operands_to_string(Code code)
{
  char *str = (char *)malloc(32 * sizeof(char));
  return strcpy(str, code.mnemonic);
}

char *Code__byte_operands_to_string(Code code)
{
  char *str = (char *)malloc(32 * sizeof(char));
  snprintf(str, 32, "%s %hhd", code.mnemonic, code.byte_operands.byte);
  return str;
}

char *Code__short_operands_to_string(Code code)
{
  char *str = (char *)malloc(32 * sizeof(char));
  snprintf(str, 32, "%s %hd", code.mnemonic, code.short_operands.short_);
  return str;
}

char *Code__cpindex_operands_to_string(
    Code code, ConstantPool constant_pool)
{
  char *str = (char *)malloc(256 * sizeof(char));
  char *cp_str = ConstantPool_get_utf8(
      constant_pool, code.cpindex_operands.cpindex);
  snprintf(
      str, 256,
      "%s #%hd // %s",
      code.mnemonic, code.cpindex_operands.cpindex, cp_str);
  free(cp_str);
  return str;
}

char *Code__byte_byte_operands_to_string(
    Code code)
{
  char *str = (char *)malloc(256 * sizeof(char));
  snprintf(
      str, 256,
      "%s %hhd, %hhd",
      code.mnemonic,
      code.byte_byte_operands.index,
      code.byte_byte_operands.const_);
  return str;
}

char *Code_entry_to_string(Code code_entry, ConstantPool constant_pool)
{
  switch (code_entry.operand_type)
  {
  case OPERAND_TYPE_NONE:
    return Code__none_operands_to_string(code_entry);
  case OPERAND_TYPE_BYTE:
    return Code__byte_operands_to_string(code_entry);
  case OPERAND_TYPE_SHORT:
    return Code__short_operands_to_string(code_entry);
  case OPERAND_TYPE_CPINDEX:
    return Code__cpindex_operands_to_string(code_entry, constant_pool);
  case OPERAND_TYPE_BYTE_BYTE:
    return Code__byte_byte_operands_to_string(code_entry);
  default:
    char *final_str = (char *)malloc(2048 * sizeof(char));
    snprintf(final_str, 2048, "0x%02X", code_entry.opcode);
    return final_str;
  }
}

char *Code_to_string(Code *code, u4 code_lenght, ConstantPool constant_pool)
{
  char *str = (char *)malloc(2048 * sizeof(char));
  if (code_lenght == 0)
  {
    snprintf(str, 2048, "{}");
    return str;
  }
  strcpy(str, "");
  for (u4 pc = 0; pc < code_lenght; pc++)
  {
    if (code[pc].opcode == OPCODE_NONE)
    {
      continue;
    }
    char *str_temp = (char *)malloc(2048 * sizeof(char));
    char *code_entry_str = Code_entry_to_string(
        code[pc], constant_pool);
    char separator = (pc == 0) ? '{' : ',';
    snprintf(
        str_temp, 2048,
        "%s%c\"%d\":\"%s\"",
        str, separator, pc, code_entry_str);
    free(code_entry_str);
    free(str);
    str = str_temp;
  }
  strcat(str, "}");
  return str;
}
