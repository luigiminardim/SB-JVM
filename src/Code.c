#include <stdlib.h> // malloc, free
#include <stdio.h>  // snprintf
#include <string.h> // strcpy
#include "Code.h"

Code Code__parse_1cp_index_operands(u1 *bytes, u4 *pc, Code code)
{
  u2 cp_index = 0;
  for (int i = 0; i < code._1cp_index_operands.operands_num_bytes; i++)
  {
    cp_index = cp_index << 8 | bytes[*pc + i + 1];
  }
  code._1cp_index_operands.cp_index = cp_index;
  *pc += code._1cp_index_operands.operands_num_bytes;
  return code;
}

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
    case OPCODE_ILOAD_0:
    case OPCODE_ILOAD_1:
    case OPCODE_ILOAD_2:
    case OPCODE_ILOAD_3:
    case OPCODE_LLOAD_0:
    case OPCODE_LLOAD_1:
    case OPCODE_LLOAD_2:
    case OPCODE_LLOAD_3:
    case OPCODE_FLOAD_0:
    case OPCODE_FLOAD_1:
    case OPCODE_FLOAD_2:
    case OPCODE_FLOAD_3:
    case OPCODE_DLOAD_0:
    case OPCODE_DLOAD_1:
    case OPCODE_DLOAD_2:
    case OPCODE_DLOAD_3:
    case OPCODE_ALOAD_0:
    case OPCODE_ALOAD_1:
    case OPCODE_ALOAD_2:
    case OPCODE_ALOAD_3:
    case OPCODE_IALOAD:
    case OPCODE_LALOAD:
    case OPCODE_FALOAD:
    case OPCODE_DALOAD:
    case OPCODE_AALOAD:
    case OPCODE_BALOAD:
    case OPCODE_CALOAD:
    case OPCODE_SALOAD:
    case OPCODE_ISTORE_0:
    case OPCODE_ISTORE_1:
    case OPCODE_ISTORE_2:
    case OPCODE_ISTORE_3:
    case OPCODE_LSTORE_0:
    case OPCODE_LSTORE_1:
    case OPCODE_LSTORE_2:
    case OPCODE_LSTORE_3:
    case OPCODE_FSTORE_0:
    case OPCODE_FSTORE_1:
    case OPCODE_FSTORE_2:
    case OPCODE_FSTORE_3:
    case OPCODE_DSTORE_0:
    case OPCODE_DSTORE_1:
    case OPCODE_DSTORE_2:
    case OPCODE_DSTORE_3:
    case OPCODE_ASTORE_0:
    case OPCODE_ASTORE_1:
    case OPCODE_ASTORE_2:
    case OPCODE_ASTORE_3:
    case OPCODE_IASTORE:
    case OPCODE_LASTORE:
    case OPCODE_FASTORE:
    case OPCODE_DASTORE:
    case OPCODE_AASTORE:
    case OPCODE_BASTORE:
    case OPCODE_CASTORE:
    case OPCODE_SASTORE:
    case OPCODE_POP:
    case OPCODE_POP2:
    case OPCODE_DUP:
    case OPCODE_DUP_X1:
    case OPCODE_DUP_X2:
    case OPCODE_DUP2:
    case OPCODE_DUP2_X1:
    case OPCODE_DUP2_X2:
    case OPCODE_SWAP:
    case OPCODE_IADD:
    case OPCODE_LADD:
    case OPCODE_FADD:
    case OPCODE_DADD:
    case OPCODE_ISUB:
    case OPCODE_LSUB:
    case OPCODE_FSUB:
    case OPCODE_DSUB:
    case OPCODE_IMUL:
    case OPCODE_LMUL:
    case OPCODE_FMUL:
    case OPCODE_DMUL:
    case OPCODE_IDIV:
    case OPCODE_LDIV:
    case OPCODE_FDIV:
    case OPCODE_DDIV:
    case OPCODE_IREM:
    case OPCODE_LREM:
    case OPCODE_FREM:
    case OPCODE_DREM:
    case OPCODE_INEG:
    case OPCODE_LNEG:
    case OPCODE_FNEG:
    case OPCODE_DNEG:
    case OPCODE_ISHL:
    case OPCODE_LSHL:
    case OPCODE_ISHR:
    case OPCODE_LSHR:
    case OPCODE_IUSHR:
    case OPCODE_LUSHR:
    case OPCODE_IAND:
    case OPCODE_LAND:
    case OPCODE_IOR:
    case OPCODE_LOR:
    case OPCODE_IXOR:
    case OPCODE_LXOR:
    {
      break;
    }
    // case 1 byte operands
    case OPCODE_BIPUSH:
    case OPCODE_ILOAD:
    case OPCODE_LLOAD:
    case OPCODE_FLOAD:
    case OPCODE_DLOAD:
    case OPCODE_ALOAD:
    case OPCODE_ISTORE:
    case OPCODE_LSTORE:
    case OPCODE_FSTORE:
    case OPCODE_DSTORE:
    case OPCODE_ASTORE:
    {
      code[pc]._1byte_operands.byte = (int8_t)bytes[pc + 1];
      pc++;
      break;
    }
    // case 1 short operands
    case OPCODE_SIPUSH:
    {
      code[pc]._1short_operands.short_ = (int16_t)bytes[pc + 1] << 8 | bytes[pc + 2];
      pc += 2;
      break;
    }
    // case 1 cp_index operands with 1 byte
    case OPCODE_LDC:
    {
      code[pc]._1cp_index_operands.operands_num_bytes = 1;
      code[pc] = Code__parse_1cp_index_operands(bytes, &pc, code[pc]);
    }
    // case 1 cp_index operands with 2 bytes
    case OPCODE_LDC_W:
    case OPCODE_LDC2_W:
    {
      code[pc]._1cp_index_operands.operands_num_bytes = 2;
      code[pc] = Code__parse_1cp_index_operands(bytes, &pc, code[pc]);
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
  snprintf(str, 32, "%s %hhd", mnemonic, byte);
  (*pc)++;
  return str;
}

char *Code_1short_operands_to_string(const char *mnemonic, int16_t short_, u4 *pc)
{
  char *str = (char *)malloc(256 * sizeof(char));
  snprintf(str, 32, "%s %hd", mnemonic, short_);
  (*pc) += 2;
  return str;
}

char *Code_1cp_index_operands_to_string(
    const char *mnemonic, _1CpIndexOperands _1cp_index_operands, u4 *pc,
    ConstantPool constant_pool)
{
  char *str = (char *)malloc(256 * sizeof(char));
  char *cp_str = ConstantPool_get_utf8(
      constant_pool, _1cp_index_operands.cp_index);
  snprintf(
      str, 32,
      "%s #%hd // %s",
      mnemonic, _1cp_index_operands.cp_index, cp_str);
  (*pc) += _1cp_index_operands.operands_num_bytes;
  free(cp_str);
  return str;
}

char *Code_entry_to_string(Code code_entry, u4 *pc, ConstantPool constant_pool)
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
  case OPCODE_SIPUSH:
    return Code_1short_operands_to_string(
        "sipush", code_entry._1short_operands.short_, pc);
  case OPCODE_LDC:
    return Code_1cp_index_operands_to_string(
        "ldc", code_entry._1cp_index_operands, pc, constant_pool);
  case OPCODE_LDC_W:
    return Code_1cp_index_operands_to_string(
        "ldc_w", code_entry._1cp_index_operands, pc, constant_pool);
  case OPCODE_LDC2_W:
    return Code_1cp_index_operands_to_string(
        "ldc2_w", code_entry._1cp_index_operands, pc, constant_pool);
  case OPCODE_ILOAD:
    return Code_1byte_operands_to_string(
        "iload", code_entry._1byte_operands.byte, pc);
  case OPCODE_LLOAD:
    return Code_1byte_operands_to_string(
        "lload", code_entry._1byte_operands.byte, pc);
  case OPCODE_FLOAD:
    return Code_1byte_operands_to_string(
        "fload", code_entry._1byte_operands.byte, pc);
  case OPCODE_DLOAD:
    return Code_1byte_operands_to_string(
        "dload", code_entry._1byte_operands.byte, pc);
  case OPCODE_ALOAD:
    return Code_1byte_operands_to_string(
        "aload", code_entry._1byte_operands.byte, pc);
  case OPCODE_ILOAD_0:
    return Code_0_opcodes_to_string("iload_0");
  case OPCODE_ILOAD_1:
    return Code_0_opcodes_to_string("iload_1");
  case OPCODE_ILOAD_2:
    return Code_0_opcodes_to_string("iload_2");
  case OPCODE_ILOAD_3:
    return Code_0_opcodes_to_string("iload_3");
  case OPCODE_LLOAD_0:
    return Code_0_opcodes_to_string("lload_0");
  case OPCODE_LLOAD_1:
    return Code_0_opcodes_to_string("lload_1");
  case OPCODE_LLOAD_2:
    return Code_0_opcodes_to_string("lload_2");
  case OPCODE_LLOAD_3:
    return Code_0_opcodes_to_string("lload_3");
  case OPCODE_FLOAD_0:
    return Code_0_opcodes_to_string("fload_0");
  case OPCODE_FLOAD_1:
    return Code_0_opcodes_to_string("fload_1");
  case OPCODE_FLOAD_2:
    return Code_0_opcodes_to_string("fload_2");
  case OPCODE_FLOAD_3:
    return Code_0_opcodes_to_string("fload_3");
  case OPCODE_DLOAD_0:
    return Code_0_opcodes_to_string("dload_0");
  case OPCODE_DLOAD_1:
    return Code_0_opcodes_to_string("dload_1");
  case OPCODE_DLOAD_2:
    return Code_0_opcodes_to_string("dload_2");
  case OPCODE_DLOAD_3:
    return Code_0_opcodes_to_string("dload_3");
  case OPCODE_ALOAD_0:
    return Code_0_opcodes_to_string("aload_0");
  case OPCODE_ALOAD_1:
    return Code_0_opcodes_to_string("aload_1");
  case OPCODE_ALOAD_2:
    return Code_0_opcodes_to_string("aload_2");
  case OPCODE_ALOAD_3:
    return Code_0_opcodes_to_string("aload_3");
  case OPCODE_IALOAD:
    return Code_0_opcodes_to_string("iaload");
  case OPCODE_LALOAD:
    return Code_0_opcodes_to_string("laload");
  case OPCODE_FALOAD:
    return Code_0_opcodes_to_string("faload");
  case OPCODE_DALOAD:
    return Code_0_opcodes_to_string("daload");
  case OPCODE_AALOAD:
    return Code_0_opcodes_to_string("aaload");
  case OPCODE_BALOAD:
    return Code_0_opcodes_to_string("baload");
  case OPCODE_CALOAD:
    return Code_0_opcodes_to_string("caload");
  case OPCODE_SALOAD:
    return Code_0_opcodes_to_string("saload");
  case OPCODE_ISTORE:
    return Code_1byte_operands_to_string(
        "istore", code_entry._1byte_operands.byte, pc);
  case OPCODE_LSTORE:
    return Code_1byte_operands_to_string(
        "lstore", code_entry._1byte_operands.byte, pc);
  case OPCODE_FSTORE:
    return Code_1byte_operands_to_string(
        "fstore", code_entry._1byte_operands.byte, pc);
  case OPCODE_DSTORE:
    return Code_1byte_operands_to_string(
        "dstore", code_entry._1byte_operands.byte, pc);
  case OPCODE_ASTORE:
    return Code_1byte_operands_to_string(
        "astore", code_entry._1byte_operands.byte, pc);
  case OPCODE_ISTORE_0:
    return Code_0_opcodes_to_string("istore_0");
  case OPCODE_ISTORE_1:
    return Code_0_opcodes_to_string("istore_1");
  case OPCODE_ISTORE_2:
    return Code_0_opcodes_to_string("istore_2");
  case OPCODE_ISTORE_3:
    return Code_0_opcodes_to_string("istore_3");
  case OPCODE_LSTORE_0:
    return Code_0_opcodes_to_string("lstore_0");
  case OPCODE_LSTORE_1:
    return Code_0_opcodes_to_string("lstore_1");
  case OPCODE_LSTORE_2:
    return Code_0_opcodes_to_string("lstore_2");
  case OPCODE_LSTORE_3:
    return Code_0_opcodes_to_string("lstore_3");
  case OPCODE_FSTORE_0:
    return Code_0_opcodes_to_string("fstore_0");
  case OPCODE_FSTORE_1:
    return Code_0_opcodes_to_string("fstore_1");
  case OPCODE_FSTORE_2:
    return Code_0_opcodes_to_string("fstore_2");
  case OPCODE_FSTORE_3:
    return Code_0_opcodes_to_string("fstore_3");
  case OPCODE_DSTORE_0:
    return Code_0_opcodes_to_string("dstore_0");
  case OPCODE_DSTORE_1:
    return Code_0_opcodes_to_string("dstore_1");
  case OPCODE_DSTORE_2:
    return Code_0_opcodes_to_string("dstore_2");
  case OPCODE_DSTORE_3:
    return Code_0_opcodes_to_string("dstore_3");
  case OPCODE_ASTORE_0:
    return Code_0_opcodes_to_string("astore_0");
  case OPCODE_ASTORE_1:
    return Code_0_opcodes_to_string("astore_1");
  case OPCODE_ASTORE_2:
    return Code_0_opcodes_to_string("astore_2");
  case OPCODE_ASTORE_3:
    return Code_0_opcodes_to_string("astore_3");
  case OPCODE_IASTORE:
    return Code_0_opcodes_to_string("iastore");
  case OPCODE_LASTORE:
    return Code_0_opcodes_to_string("lastore");
  case OPCODE_FASTORE:
    return Code_0_opcodes_to_string("fastore");
  case OPCODE_DASTORE:
    return Code_0_opcodes_to_string("dastore");
  case OPCODE_AASTORE:
    return Code_0_opcodes_to_string("aastore");
  case OPCODE_BASTORE:
    return Code_0_opcodes_to_string("bastore");
  case OPCODE_CASTORE:
    return Code_0_opcodes_to_string("castore");
  case OPCODE_SASTORE:
    return Code_0_opcodes_to_string("sastore");
  case OPCODE_POP:
    return Code_0_opcodes_to_string("pop");
  case OPCODE_POP2:
    return Code_0_opcodes_to_string("pop2");
  case OPCODE_DUP:
    return Code_0_opcodes_to_string("dup");
  case OPCODE_DUP_X1:
    return Code_0_opcodes_to_string("dup_x1");
  case OPCODE_DUP_X2:
    return Code_0_opcodes_to_string("dup_x2");
  case OPCODE_DUP2:
    return Code_0_opcodes_to_string("dup2");
  case OPCODE_DUP2_X1:
    return Code_0_opcodes_to_string("dup2_x1");
  case OPCODE_DUP2_X2:
    return Code_0_opcodes_to_string("dup2_x2");
  case OPCODE_SWAP:
    return Code_0_opcodes_to_string("swap");
  case OPCODE_IADD:
    return Code_0_opcodes_to_string("iadd");
  case OPCODE_LADD:
    return Code_0_opcodes_to_string("ladd");
  case OPCODE_FADD:
    return Code_0_opcodes_to_string("fadd");
  case OPCODE_DADD:
    return Code_0_opcodes_to_string("dadd");
  case OPCODE_ISUB:
    return Code_0_opcodes_to_string("isub");
  case OPCODE_LSUB:
    return Code_0_opcodes_to_string("lsub");
  case OPCODE_FSUB:
    return Code_0_opcodes_to_string("fsub");
  case OPCODE_DSUB:
    return Code_0_opcodes_to_string("dsub");
  case OPCODE_IMUL:
    return Code_0_opcodes_to_string("imul");
  case OPCODE_LMUL:
    return Code_0_opcodes_to_string("lmul");
  case OPCODE_FMUL:
    return Code_0_opcodes_to_string("fmul");
  case OPCODE_DMUL:
    return Code_0_opcodes_to_string("dmul");
  case OPCODE_IDIV:
    return Code_0_opcodes_to_string("idiv");
  case OPCODE_LDIV:
    return Code_0_opcodes_to_string("ldiv");
  case OPCODE_FDIV:
    return Code_0_opcodes_to_string("fdiv");
  case OPCODE_DDIV:
    return Code_0_opcodes_to_string("ddiv");
  case OPCODE_IREM:
    return Code_0_opcodes_to_string("irem");
  case OPCODE_LREM:
    return Code_0_opcodes_to_string("lrem");
  case OPCODE_FREM:
    return Code_0_opcodes_to_string("frem");
  case OPCODE_DREM:
    return Code_0_opcodes_to_string("drem");
  case OPCODE_INEG:
    return Code_0_opcodes_to_string("ineg");
  case OPCODE_LNEG:
    return Code_0_opcodes_to_string("lneg");
  case OPCODE_FNEG:
    return Code_0_opcodes_to_string("fneg");
  case OPCODE_DNEG:
    return Code_0_opcodes_to_string("dneg");
  case OPCODE_ISHL:
    return Code_0_opcodes_to_string("ishl");
  case OPCODE_LSHL:
    return Code_0_opcodes_to_string("lshl");
  case OPCODE_ISHR:
    return Code_0_opcodes_to_string("ishr");
  case OPCODE_LSHR:
    return Code_0_opcodes_to_string("lshr");
  case OPCODE_IUSHR:
    return Code_0_opcodes_to_string("iushr");
  case OPCODE_LUSHR:
    return Code_0_opcodes_to_string("lushr");
  case OPCODE_IAND:
    return Code_0_opcodes_to_string("iand");
  case OPCODE_LAND:
    return Code_0_opcodes_to_string("land");
  case OPCODE_IOR:
    return Code_0_opcodes_to_string("ior");
  case OPCODE_LOR:
    return Code_0_opcodes_to_string("lor");
  case OPCODE_IXOR:
    return Code_0_opcodes_to_string("ixor");
  case OPCODE_LXOR:
    return Code_0_opcodes_to_string("lxor");
  default:
    char *final_str = (char *)malloc(2048 * sizeof(char));
    snprintf(final_str, 2048, "0x%02X", code_entry.opcode);
    return final_str;
    break;
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
  snprintf(str, 2048, "{");
  for (u4 pc = 0; pc < code_lenght; pc++)
  {
    char *str_temp = (char *)malloc(2048 * sizeof(char));
    u4 pc_inc = 0;
    char *code_entry_str = Code_entry_to_string(
        code[pc], &pc_inc, constant_pool);
    char separator = (pc + pc_inc >= code_lenght - 1) ? '}' : ',';
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
