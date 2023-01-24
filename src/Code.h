#pragma once

#include <stdint.h>
#include "java-bytes.h"
#include "ConstantPool.h"

/**
 * https://en.wikipedia.org/wiki/List_of_Java_bytecode_instructions
 */
enum Opcode
{
  OPCODE_NONE = 0xFF,
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
  OPCODE_BIPUSH = 0x10,
  OPCODE_SIPUSH = 0x11,
  OPCODE_LDC = 0x12,
  OPCODE_LDC_W = 0x13,
  OPCODE_LDC2_W = 0x14,
  OPCODE_ILOAD = 0x15,
  OPCODE_LLOAD = 0x16,
  OPCODE_FLOAD = 0x17,
  OPCODE_DLOAD = 0x18,
  OPCODE_ALOAD = 0x19,
  OPCODE_ILOAD_0 = 0x1A,
  OPCODE_ILOAD_1 = 0x1B,
  OPCODE_ILOAD_2 = 0x1C,
  OPCODE_ILOAD_3 = 0x1D,
  OPCODE_LLOAD_0 = 0x1E,
  OPCODE_LLOAD_1 = 0x1F,
  OPCODE_LLOAD_2 = 0x20,
  OPCODE_LLOAD_3 = 0x21,
  OPCODE_FLOAD_0 = 0x22,
  OPCODE_FLOAD_1 = 0x23,
  OPCODE_FLOAD_2 = 0x24,
  OPCODE_FLOAD_3 = 0x25,
  OPCODE_DLOAD_0 = 0x26,
  OPCODE_DLOAD_1 = 0x27,
  OPCODE_DLOAD_2 = 0x28,
  OPCODE_DLOAD_3 = 0x29,
  OPCODE_ALOAD_0 = 0x2A,
  OPCODE_ALOAD_1 = 0x2B,
  OPCODE_ALOAD_2 = 0x2C,
  OPCODE_ALOAD_3 = 0x2D,
  OPCODE_IALOAD = 0x2E,
  OPCODE_LALOAD = 0x2F,
  OPCODE_FALOAD = 0x30,
  OPCODE_DALOAD = 0x31,
  OPCODE_AALOAD = 0x32,
  OPCODE_BALOAD = 0x33,
  OPCODE_CALOAD = 0x34,
  OPCODE_SALOAD = 0x35,
  OPCODE_ISTORE = 0x36,
  OPCODE_LSTORE = 0x37,
  OPCODE_FSTORE = 0x38,
  OPCODE_DSTORE = 0x39,
  OPCODE_ASTORE = 0x3A,
  OPCODE_ISTORE_0 = 0x3B,
  OPCODE_ISTORE_1 = 0x3C,
  OPCODE_ISTORE_2 = 0x3D,
  OPCODE_ISTORE_3 = 0x3E,
  OPCODE_LSTORE_0 = 0x3F,
  OPCODE_LSTORE_1 = 0x40,
  OPCODE_LSTORE_2 = 0x41,
  OPCODE_LSTORE_3 = 0x42,
  OPCODE_FSTORE_0 = 0x43,
  OPCODE_FSTORE_1 = 0x44,
  OPCODE_FSTORE_2 = 0x45,
  OPCODE_FSTORE_3 = 0x46,
  OPCODE_DSTORE_0 = 0x47,
  OPCODE_DSTORE_1 = 0x48,
  OPCODE_DSTORE_2 = 0x49,
  OPCODE_DSTORE_3 = 0x4A,
  OPCODE_ASTORE_0 = 0x4B,
  OPCODE_ASTORE_1 = 0x4C,
  OPCODE_ASTORE_2 = 0x4D,
  OPCODE_ASTORE_3 = 0x4E,
  OPCODE_IASTORE = 0x4F,
  OPCODE_LASTORE = 0x50,
  OPCODE_FASTORE = 0x51,
  OPCODE_DASTORE = 0x52,
  OPCODE_AASTORE = 0x53,
  OPCODE_BASTORE = 0x54,
  OPCODE_CASTORE = 0x55,
  OPCODE_SASTORE = 0x56,
  OPCODE_POP = 0x57,
  OPCODE_POP2 = 0x58,
  OPCODE_DUP = 0x59,
  OPCODE_DUP_X1 = 0x5A,
  OPCODE_DUP_X2 = 0x5B,
  OPCODE_DUP2 = 0x5C,
  OPCODE_DUP2_X1 = 0x5D,
  OPCODE_DUP2_X2 = 0x5E,
  OPCODE_SWAP = 0x5F,
  OPCODE_IADD = 0x60,
  OPCODE_LADD = 0x61,
  OPCODE_FADD = 0x62,
  OPCODE_DADD = 0x63,
  OPCODE_ISUB = 0x64,
  OPCODE_LSUB = 0x65,
  OPCODE_FSUB = 0x66,
  OPCODE_DSUB = 0x67,
  OPCODE_IMUL = 0x68,
  OPCODE_LMUL = 0x69,
  OPCODE_FMUL = 0x6A,
  OPCODE_DMUL = 0x6B,
  OPCODE_IDIV = 0x6C,
  OPCODE_LDIV = 0x6D,
  OPCODE_FDIV = 0x6E,
  OPCODE_DDIV = 0x6F,
  OPCODE_IREM = 0x70,
  OPCODE_LREM = 0x71,
  OPCODE_FREM = 0x72,
  OPCODE_DREM = 0x73,
  OPCODE_INEG = 0x74,
  OPCODE_LNEG = 0x75,
  OPCODE_FNEG = 0x76,
  OPCODE_DNEG = 0x77,
  OPCODE_ISHL = 0x78,
  OPCODE_LSHL = 0x79,
  OPCODE_ISHR = 0x7A,
  OPCODE_LSHR = 0x7B,
  OPCODE_IUSHR = 0x7C,
  OPCODE_LUSHR = 0x7D,
  OPCODE_IAND = 0x7E,
  OPCODE_LAND = 0x7F,
  OPCODE_IOR = 0x80,
  OPCODE_LOR = 0x81,
  OPCODE_IXOR = 0x82,
  OPCODE_LXOR = 0x83,
  OPCODE_IINC = 0x84,
  OPCODE_I2L = 0x85,
  OPCODE_I2F = 0x86,
  OPCODE_I2D = 0x87,
  OPCODE_L2I = 0x88,
  OPCODE_L2F = 0x89,
  OPCODE_L2D = 0x8A,
  OPCODE_F2I = 0x8B,
  OPCODE_F2L = 0x8C,
  OPCODE_F2D = 0x8D,
  OPCODE_D2I = 0x8E,
  OPCODE_D2L = 0x8F,
  OPCODE_D2F = 0x90,
  OPCODE_I2B = 0x91,
  OPCODE_I2C = 0x92,
  OPCODE_I2S = 0x93,
  OPCODE_LCMP = 0x94,
  OPCODE_FCMPL = 0x95,
  OPCODE_FCMPG = 0x96,
  OPCODE_DCMPL = 0x97,
  OPCODE_DCMPG = 0x98,
  OPCODE_IFEQ = 0x99,
  OPCODE_IFNE = 0x9A,
  OPCODE_IFLT = 0x9B,
  OPCODE_IFGE = 0x9C,
  OPCODE_IFGT = 0x9D,
  OPCODE_IFLE = 0x9E,
  OPCODE_IF_ICMPEQ = 0x9F,
  OPCODE_IF_ICMPNE = 0xA0,
  OPCODE_IF_ICMPLT = 0xA1,
  OPCODE_IF_ICMPGE = 0xA2,
  OPCODE_IF_ICMPGT = 0xA3,
  OPCODE_IF_ICMPLE = 0xA4,
  OPCODE_IF_ACMPEQ = 0xA5,
  OPCODE_IF_ACMPNE = 0xA6,
  OPCODE_GOTO = 0xA7,
  OPCODE_JSR = 0xA8,
  OPCODE_RET = 0xA9,
  OPCODE_TABLESWITCH = 0xAA,
  OPCODE_LOOKUPSWITCH = 0xAB,
  OPCODE_IRETURN = 0xAC,
  OPCODE_LRETURN = 0xAD,
  OPCODE_FRETURN = 0xAE,
  OPCODE_DRETURN = 0xAF,
  OPCODE_ARETURN = 0xB0,
  OPCODE_RETURN = 0xB1,
  OPCODE_GETSTATIC = 0xB2,
  OPCODE_PUTSTATIC = 0xB3,
  OPCODE_GETFIELD = 0xB4,
  OPCODE_PUTFIELD = 0xB5,
  OPCODE_INVOKEVIRTUAL = 0xB6,
  OPCODE_INVOKESPECIAL = 0xB7,
  OPCODE_INVOKESTATIC = 0xB8,
  OPCODE_INVOKEINTERFACE = 0xB9,
  OPCODE_INVOKEDYNAMIC = 0xBA,
  OPCODE_NEW = 0xBB,
  OPCODE_NEWARRAY = 0xBC,
  OPCODE_ANEWARRAY = 0xBD,
  OPCODE_ARRAYLENGTH = 0xBE,
  OPCODE_ATHROW = 0xBF,
  OPCODE_CHECKCAST = 0xC0,
  OPCODE_INSTANCEOF = 0xC1,
  OPCODE_MONITORENTER = 0xC2,
  OPCODE_MONITOREXIT = 0xC3,
  // OPCODE_WIDE = 0xC4,
  OPCODE_MULTIANEWARRAY = 0xC5,
  OPCODE_IFNULL = 0xC6,
  OPCODE_IFNONNULL = 0xC7,
  OPCODE_GOTO_W = 0xC8,
  OPCODE_JSR_W = 0xC9,
  OPCODE_BREAKPOINT = 0xCA,
};

enum OperandType
{
  OPERAND_TYPE_NONE,
  OPERAND_TYPE_BYTE,
  OPERAND_TYPE_SHORT,
  OPERAND_TYPE_INT,
  OPERAND_TYPE_CPINDEX,
  OPERAND_TYPE_BYTE_BYTE,
  OPERAND_TYPE_CPINDEX_BYTE,
  OPERAND_TYPE_TABLESWITCH,
  OPERAND_TYPE_LOOKUPSWITCH,
  OPERAND_TYPE_CPINDEX_BYTE_BYTE,
};

typedef struct
{
  int8_t byte;
} ByteOperands;

typedef struct
{
  int16_t short_;
} ShortOperands;

typedef struct
{
  int8_t index;
  int8_t const_;
} ByteByteOperands;

typedef struct
{
  u2 cpindex;
  int operands_num_bytes;
} CpindexOperands;

typedef struct
{
  u2 cpindex;
  int8_t byte_;
} CpindexByteOperands;

typedef struct
{
  int32_t int_;
} IntOperands;

typedef struct
{
  int32_t default_;
  int32_t low;
  int32_t high;
  int32_t *offsets;
} TableswitchOperands;

struct LookupswitchOperandsPairs
{
  int32_t key;
  int32_t offset;
};

typedef struct
{
  int32_t default_;
  int32_t npairs;
  struct LookupswitchOperandsPairs *pairs;
} LookupswitchOperands;

typedef struct
{
  u2 cpindex;
  int8_t byte1;
  int8_t byte2;
} CpindexByteByteOperands;

typedef struct
{
  enum Opcode opcode;
  char *mnemonic;
  enum OperandType operand_type;
  union
  {
    ByteOperands byte_operands;
    ShortOperands short_operands;
    CpindexOperands cpindex_operands;
    ByteByteOperands byte_byte_operands;
    CpindexByteOperands cpindex_byte_operands;
    IntOperands int_operands;
    TableswitchOperands tableswitch_operands;
    LookupswitchOperands lookupswitch_operands;
    CpindexByteByteOperands cpindex_byte_byte_operands;
  };
} Code;

Code *Code_Parse(u1 *bytes, u4 code_length);

void Code_Free(Code *code, u4 code_length);

char *Code_to_string(Code *code, u4 code_length, ConstantPool constant_pool);
