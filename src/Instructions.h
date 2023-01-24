#include "Frame.h"

void sipush(Frame* frame, Code* code);

void bipush(Frame* frame, Code* code);

void istore_2(Frame* frame, Code* code);

void if_icmpeq(Frame* frame, Code* code);

void if_icmpne(Frame* frame, Code* code);

void if_icmplt(Frame* frame, Code* code);

void if_icmpge(Frame* frame, Code* code);

void if_icmpgt(Frame* frame, Code* code);

void if_icmple(Frame* frame, Code* code);

void if_acmpeq(Frame* frame, Code* code);

void if_acmpne(Frame* frame, Code* code);

void __goto(Frame* frame, Code* code);

void jsr(Frame* frame, Code* code);

void ifnull(Frame* frame, Code* code);

void ifnonnull(Frame* frame, Code* code);

void __return(Frame* frame, Code* code);

void nop(Frame* frame, Code* code);

void aconst_null(Frame* frame, Code* code);

void iconst_m1(Frame* frame, Code* code);
void iconst_0(Frame* frame, Code* code);
void iconst_1(Frame* frame, Code* code);
void iconst_2(Frame* frame, Code* code);
void iconst_3(Frame* frame, Code* code);
void iconst_4(Frame* frame, Code* code);
void iconst_5(Frame* frame, Code* code);

void lconst_0(Frame* frame, Code* code);
void lconst_1(Frame* frame, Code* code);

void fconst_0(Frame* frame, Code* code);
void fconst_1(Frame* frame, Code* code);
void fconst_2(Frame* frame, Code* code);

void dconst_0(Frame* frame, Code* code);
void dconst_1(Frame* frame, Code* code);

void ldc(Frame* frame, Code* code);
void ldc_w(Frame* frame, Code* code);
void ldc2_w(Frame* frame, Code* code);

void iload(Frame* frame, Code* code);
void lload(Frame* frame, Code* code);
void fload(Frame* frame, Code* code);
void dload(Frame* frame, Code* code);
void aload(Frame* frame, Code* code);

void iload_0(Frame* frame, Code* code);
void iload_1(Frame* frame, Code* code);
void iload_2(Frame* frame, Code* code);
void iload_3(Frame* frame, Code* code);

void lload_0(Frame* frame, Code* code);
void lload_1(Frame* frame, Code* code);
void lload_2(Frame* frame, Code* code);
void lload_3(Frame* frame, Code* code);

void fload_0(Frame* frame, Code* code);
void fload_1(Frame* frame, Code* code);
void fload_2(Frame* frame, Code* code);
void fload_3(Frame* frame, Code* code);

void dload_0(Frame* frame, Code* code);
void dload_1(Frame* frame, Code* code);
void dload_2(Frame* frame, Code* code);
void dload_3(Frame* frame, Code* code);

void aload_0(Frame* frame, Code* code);
void aload_1(Frame* frame, Code* code);
void aload_2(Frame* frame, Code* code);
void aload_3(Frame* frame, Code* code);

void iaload(Frame* frame, Code* code);
void laload(Frame* frame, Code* code);
void faload(Frame* frame, Code* code);
void daload(Frame* frame, Code* code);
void aaload(Frame* frame, Code* code);
void baload(Frame* frame, Code* code);
void caload(Frame* frame, Code* code);
void saload(Frame* frame, Code* code);

void istore(Frame* frame, Code* code);
void lstore(Frame* frame, Code* code);
void fstore(Frame* frame, Code* code);
void dstore(Frame* frame, Code* code);
void astore(Frame* frame, Code* code);

void istore_0(Frame* frame, Code* code);
void istore_1(Frame* frame, Code* code);
void istore_3(Frame* frame, Code* code);

void lstore_0(Frame* frame, Code* code);
void lstore_1(Frame* frame, Code* code);
void lstore_2(Frame* frame, Code* code);
void lstore_3(Frame* frame, Code* code);

void fstore_0(Frame* frame, Code* code);
void fstore_1(Frame* frame, Code* code);
void fstore_2(Frame* frame, Code* code);
void fstore_3(Frame* frame, Code* code);

void dstore_0(Frame* frame, Code* code);
void dstore_1(Frame* frame, Code* code);
void dstore_2(Frame* frame, Code* code);
void dstore_3(Frame* frame, Code* code);

void astore_0(Frame* frame, Code* code);
void astore_1(Frame* frame, Code* code);
void astore_2(Frame* frame, Code* code);
void astore_3(Frame* frame, Code* code);

void iastore(Frame* frame, Code* code);
void lastore(Frame* frame, Code* code);
void fastore(Frame* frame, Code* code);
void dastore(Frame* frame, Code* code);
void aastore(Frame* frame, Code* code);
void bastore(Frame* frame, Code* code);
void castore(Frame* frame, Code* code);
void sastore(Frame* frame, Code* code);

void pop(Frame* frame, Code* code);
void pop2(Frame* frame, Code* code);

void dup(Frame* frame, Code* code);
void dup_x1(Frame* frame, Code* code);
void dup_x2(Frame* frame, Code* code);

void dup2(Frame* frame, Code* code);

void dup2_x1(Frame* frame, Code* code);

void dup2_x2(Frame* frame, Code* code);

void swap(Frame* frame, Code* code);

void iadd(Frame* frame, Code* code);

void ladd(Frame* frame, Code* code);

void fadd(Frame* frame, Code* code);

void dadd(Frame* frame, Code* code);

void isub(Frame* frame, Code* code);

void lsub(Frame* frame, Code* code);

void fsub(Frame* frame, Code* code);

void dsub(Frame* frame, Code* code);

void imul(Frame* frame, Code* code);

void lmul(Frame* frame, Code* code);

void fmul(Frame* frame, Code* code);

void dmul(Frame* frame, Code* code);

void idiv(Frame* frame, Code* code);

void ldiv(Frame* frame, Code* code);

void fdiv(Frame* frame, Code* code);

void ddiv(Frame* frame, Code* code);

void irem(Frame* frame, Code* code);

void lrem(Frame* frame, Code* code);

void frem(Frame* frame, Code* code);

void drem(Frame* frame, Code* code);

void ineg(Frame* frame, Code* code);

void lneg(Frame* frame, Code* code);

void fneg(Frame* frame, Code* code);

void dneg(Frame* frame, Code* code);

void ishl(Frame* frame, Code* code);

void lshl(Frame* frame, Code* code);

void ishr(Frame* frame, Code* code);

void lshr(Frame* frame, Code* code);

void iushr(Frame* frame, Code* code);

void lushr(Frame* frame, Code* code);

void iand(Frame* frame, Code* code);

void land(Frame* frame, Code* code);

void ior(Frame* frame, Code* code);

void lor(Frame* frame, Code* code);

void ixor(Frame* frame, Code* code);

void lxor(Frame* frame, Code* code);

void iinc(Frame* frame, Code* code);

void i2l(Frame* frame, Code* code);

void i2f(Frame* frame, Code* code);

void i2d(Frame* frame, Code* code);

void l2i(Frame* frame, Code* code);

void l2f(Frame* frame, Code* code);

void l2d(Frame* frame, Code* code);

void f2i(Frame* frame, Code* code);

void f2l(Frame* frame, Code* code);

void f2d(Frame* frame, Code* code);

void d2i(Frame* frame, Code* code);

void d2l(Frame* frame, Code* code);

void d2f(Frame* frame, Code* code);

void i2b(Frame* frame, Code* code);

void i2c(Frame* frame, Code* code);

void i2s(Frame* frame, Code* code);

void lcmp(Frame* frame, Code* code);

void fcmpl(Frame* frame, Code* code);

void fcmpg(Frame* frame, Code* code);

void dcmpl(Frame* frame, Code* code);

void dcmpg(Frame* frame, Code* code);

void ifeq(Frame* frame, Code* code);

void ifne(Frame* frame, Code* code);

void iflt(Frame* frame, Code* code);

void ifge(Frame* frame, Code* code);

void ifgt(Frame* frame, Code* code);

void ifle(Frame* frame, Code* code);

void if_icmpeq(Frame* frame, Code* code);

void if_icmpne(Frame* frame, Code* code);

void if_icmplt(Frame* frame, Code* code);

void if_icmpge(Frame* frame, Code* code);

void if_icmpgt(Frame* frame, Code* code);

void if_icmple(Frame* frame, Code* code);

void if_acmpeq(Frame* frame, Code* code);

void if_acmpne(Frame* frame, Code* code);

void __goto(Frame* frame, Code* code);

void jsr(Frame* frame, Code* code);

void ret(Frame* frame, Code* code);

void tableswitch(Frame* frame, Code* code);

void lookupswitch(Frame* frame, Code* code);

void ireturn(Frame* frame, Code* code);

void lreturn(Frame* frame, Code* code);

void freturn(Frame* frame, Code* code);

void dreturn(Frame* frame, Code* code);

void areturn(Frame* frame, Code* code);

void getstatic(Frame* frame, Code* code);

void putstatic(Frame* frame, Code* code);

void getfield(Frame* frame, Code* code);

void putfield(Frame* frame, Code* code);

void invokevirtual(Frame* frame, Code* code);

void invokespecial(Frame* frame, Code* code);

void invokestatic(Frame* frame, Code* code);

void invokeinterface(Frame* frame, Code* code);

void invokedynamic(Frame* frame, Code* code);

void __new(Frame* frame, Code* code);

void newarray(Frame* frame, Code* code);

void anewarray(Frame* frame, Code* code);

void arraylength(Frame* frame, Code* code);

void athrow(Frame* frame, Code* code);

void checkcast(Frame* frame, Code* code);

void instanceof(Frame* frame, Code* code);

void monitorenter(Frame* frame, Code* code);

void monitorexit(Frame* frame, Code* code);

void multianewarray(Frame* frame, Code* code);

void ifnull(Frame* frame, Code* code);

void ifnonnull(Frame* frame, Code* code);

void goto_w(Frame* frame, Code* code);

void jsr_w(Frame* frame, Code* code);

void breakpoint(Frame* frame, Code* code);
