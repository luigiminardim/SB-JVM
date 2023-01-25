#include "Code.h"
#include "Frame.h"

void sipush(Frame *frame, Code *code)
{
    pushOperandStack(frame, code->short_operands.short_);
}

void bipush(Frame *frame, Code *code)
{
    pushOperandStack(frame, code->byte_operands.byte);
}

void istore_1(Frame *frame, Code *code)
{
    int32_t val = popOperandStack(frame);
    frame->local_variables[1] = val;
}

void istore_2(Frame *frame, Code *code)
{
    int32_t val = popOperandStack(frame);
    frame->local_variables[2] = val;
}

void iload_1(Frame *frame, Code *code)
{
    pushOperandStack(frame, frame->local_variables[1]);
}

void iload_2(Frame *frame, Code *code)
{
    pushOperandStack(frame, frame->local_variables[2]);
}

void iadd(Frame *frame, Code *code)
{
    int32_t value1 = popOperandStack(frame);
    int32_t value2 = popOperandStack(frame);

    // overflow ?

    pushOperandStack(frame, value1 + value2);
}

void __return(Frame *frame, Code *code)
{
    return;
}

void if_icmpeq(Frame *frame, Code *code)
{
    return;
}

void if_icmpne(Frame *frame, Code *code) { return; }

void if_icmplt(Frame *frame, Code *code) { return; }

void if_icmpge(Frame *frame, Code *code) { return; }

void if_icmpgt(Frame *frame, Code *code) { return; }

void if_icmple(Frame *frame, Code *code) { return; }

void if_acmpeq(Frame *frame, Code *code) { return; }

void if_acmpne(Frame *frame, Code *code) { return; }

void __goto(Frame *frame, Code *code) { return; }

void jsr(Frame *frame, Code *code) { return; }

void ifnull(Frame *frame, Code *code) { return; }

void ifnonnull(Frame *frame, Code *code) { return; }

void nop(Frame *frame, Code *code) { return; }

void aconst_null(Frame *frame, Code *code) { return; }

void iconst_m1(Frame *frame, Code *code) { return; }
void iconst_0(Frame *frame, Code *code) { return; }
void iconst_1(Frame *frame, Code *code) { return; }
void iconst_2(Frame *frame, Code *code) { return; }
void iconst_3(Frame *frame, Code *code) { return; }
void iconst_4(Frame *frame, Code *code) { return; }
void iconst_5(Frame *frame, Code *code) { return; }

void lconst_0(Frame *frame, Code *code) { return; }
void lconst_1(Frame *frame, Code *code) { return; }

void fconst_0(Frame *frame, Code *code) { return; }
void fconst_1(Frame *frame, Code *code) { return; }
void fconst_2(Frame *frame, Code *code) { return; }

void dconst_0(Frame *frame, Code *code) { return; }
void dconst_1(Frame *frame, Code *code) { return; }

void ldc(Frame *frame, Code *code) { return; }
void ldc_w(Frame *frame, Code *code) { return; }
void ldc2_w(Frame *frame, Code *code) { return; }

void iload(Frame *frame, Code *code) { return; }
void lload(Frame *frame, Code *code) { return; }
void fload(Frame *frame, Code *code) { return; }
void dload(Frame *frame, Code *code) { return; }
void aload(Frame *frame, Code *code) { return; }

void iload_0(Frame *frame, Code *code) { return; }
void iload_3(Frame *frame, Code *code) { return; }

void lload_0(Frame *frame, Code *code) { return; }
void lload_1(Frame *frame, Code *code) { return; }
void lload_2(Frame *frame, Code *code) { return; }
void lload_3(Frame *frame, Code *code) { return; }

void fload_0(Frame *frame, Code *code) { return; }
void fload_1(Frame *frame, Code *code) { return; }
void fload_2(Frame *frame, Code *code) { return; }
void fload_3(Frame *frame, Code *code) { return; }

void dload_0(Frame *frame, Code *code) { return; }
void dload_1(Frame *frame, Code *code) { return; }
void dload_2(Frame *frame, Code *code) { return; }
void dload_3(Frame *frame, Code *code) { return; }

void aload_0(Frame *frame, Code *code) { return; }
void aload_1(Frame *frame, Code *code) { return; }
void aload_2(Frame *frame, Code *code) { return; }
void aload_3(Frame *frame, Code *code) { return; }

void iaload(Frame *frame, Code *code) { return; }
void laload(Frame *frame, Code *code) { return; }
void faload(Frame *frame, Code *code) { return; }
void daload(Frame *frame, Code *code) { return; }
void aaload(Frame *frame, Code *code) { return; }
void baload(Frame *frame, Code *code) { return; }
void caload(Frame *frame, Code *code) { return; }
void saload(Frame *frame, Code *code) { return; }

void istore(Frame *frame, Code *code) { return; }
void lstore(Frame *frame, Code *code) { return; }
void fstore(Frame *frame, Code *code) { return; }
void dstore(Frame *frame, Code *code) { return; }
void astore(Frame *frame, Code *code) { return; }

void istore_0(Frame *frame, Code *code) { return; }
void istore_3(Frame *frame, Code *code) { return; }

void lstore_0(Frame *frame, Code *code) { return; }
void lstore_1(Frame *frame, Code *code) { return; }
void lstore_2(Frame *frame, Code *code) { return; }
void lstore_3(Frame *frame, Code *code) { return; }

void fstore_0(Frame *frame, Code *code) { return; }
void fstore_1(Frame *frame, Code *code) { return; }
void fstore_2(Frame *frame, Code *code) { return; }
void fstore_3(Frame *frame, Code *code) { return; }

void dstore_0(Frame *frame, Code *code) { return; }
void dstore_1(Frame *frame, Code *code) { return; }
void dstore_2(Frame *frame, Code *code) { return; }
void dstore_3(Frame *frame, Code *code) { return; }

void astore_0(Frame *frame, Code *code) { return; }
void astore_1(Frame *frame, Code *code) { return; }
void astore_2(Frame *frame, Code *code) { return; }
void astore_3(Frame *frame, Code *code) { return; }

void iastore(Frame *frame, Code *code) { return; }
void lastore(Frame *frame, Code *code) { return; }
void fastore(Frame *frame, Code *code) { return; }
void dastore(Frame *frame, Code *code) { return; }
void aastore(Frame *frame, Code *code) { return; }
void bastore(Frame *frame, Code *code) { return; }
void castore(Frame *frame, Code *code) { return; }
void sastore(Frame *frame, Code *code) { return; }

void pop(Frame *frame, Code *code) { return; }
void pop2(Frame *frame, Code *code) { return; }

void dup(Frame *frame, Code *code) { return; }
void dup_x1(Frame *frame, Code *code) { return; }
void dup_x2(Frame *frame, Code *code) { return; }

void dup2(Frame *frame, Code *code) { return; }

void dup2_x1(Frame *frame, Code *code) { return; }

void dup2_x2(Frame *frame, Code *code) { return; }

void swap(Frame *frame, Code *code) { return; }

void ladd(Frame *frame, Code *code) { return; }

void fadd(Frame *frame, Code *code) { return; }

void dadd(Frame *frame, Code *code) { return; }

void isub(Frame *frame, Code *code) { return; }

void lsub(Frame *frame, Code *code) { return; }

void fsub(Frame *frame, Code *code) { return; }

void dsub(Frame *frame, Code *code) { return; }

void imul(Frame *frame, Code *code) { return; }

void lmul(Frame *frame, Code *code) { return; }

void fmul(Frame *frame, Code *code) { return; }

void dmul(Frame *frame, Code *code) { return; }

void idiv(Frame *frame, Code *code) { return; }

void ldiv(Frame *frame, Code *code) { return; }

void fdiv(Frame *frame, Code *code) { return; }

void ddiv(Frame *frame, Code *code) { return; }

void irem(Frame *frame, Code *code) { return; }

void lrem(Frame *frame, Code *code) { return; }

void frem(Frame *frame, Code *code) { return; }

void drem(Frame *frame, Code *code) { return; }

void ineg(Frame *frame, Code *code) { return; }

void lneg(Frame *frame, Code *code) { return; }

void fneg(Frame *frame, Code *code) { return; }

void dneg(Frame *frame, Code *code) { return; }

void ishl(Frame *frame, Code *code) { return; }

void lshl(Frame *frame, Code *code) { return; }

void ishr(Frame *frame, Code *code) { return; }

void lshr(Frame *frame, Code *code) { return; }

void iushr(Frame *frame, Code *code) { return; }

void lushr(Frame *frame, Code *code) { return; }

void iand(Frame *frame, Code *code) { return; }

void land(Frame *frame, Code *code) { return; }

void ior(Frame *frame, Code *code) { return; }

void lor(Frame *frame, Code *code) { return; }

void ixor(Frame *frame, Code *code) { return; }

void lxor(Frame *frame, Code *code) { return; }

void iinc(Frame *frame, Code *code) { return; }

void i2l(Frame *frame, Code *code) { return; }

void i2f(Frame *frame, Code *code) { return; }

void i2d(Frame *frame, Code *code) { return; }

void l2i(Frame *frame, Code *code) { return; }

void l2f(Frame *frame, Code *code) { return; }

void l2d(Frame *frame, Code *code) { return; }

void f2i(Frame *frame, Code *code) { return; }

void f2l(Frame *frame, Code *code) { return; }

void f2d(Frame *frame, Code *code) { return; }

void d2i(Frame *frame, Code *code) { return; }

void d2l(Frame *frame, Code *code) { return; }

void d2f(Frame *frame, Code *code) { return; }

void i2b(Frame *frame, Code *code) { return; }

void i2c(Frame *frame, Code *code) { return; }

void i2s(Frame *frame, Code *code) { return; }

void lcmp(Frame *frame, Code *code) { return; }

void fcmpl(Frame *frame, Code *code) { return; }

void fcmpg(Frame *frame, Code *code) { return; }

void dcmpl(Frame *frame, Code *code) { return; }

void dcmpg(Frame *frame, Code *code) { return; }

void ifeq(Frame *frame, Code *code) { return; }

void ifne(Frame *frame, Code *code) { return; }

void iflt(Frame *frame, Code *code) { return; }

void ifge(Frame *frame, Code *code) { return; }

void ifgt(Frame *frame, Code *code) { return; }

void ifle(Frame *frame, Code *code) { return; }

void ret(Frame *frame, Code *code) { return; }

void tableswitch(Frame *frame, Code *code) { return; }

void lookupswitch(Frame *frame, Code *code) { return; }

void ireturn(Frame *frame, Code *code) { return; }

void lreturn(Frame *frame, Code *code) { return; }

void freturn(Frame *frame, Code *code) { return; }

void dreturn(Frame *frame, Code *code) { return; }

void areturn(Frame *frame, Code *code) { return; }

void getstatic(Frame *frame, Code *code) { return; }

void putstatic(Frame *frame, Code *code) { return; }

void getfield(Frame *frame, Code *code) { return; }

void putfield(Frame *frame, Code *code) { return; }

void invokevirtual(Frame *frame, Code *code) { return; }

void invokespecial(Frame *frame, Code *code) { return; }

void invokestatic(Frame *frame, Code *code) { return; }

void invokeinterface(Frame *frame, Code *code) { return; }

void invokedynamic(Frame *frame, Code *code) { return; }

void __new(Frame *frame, Code *code) { return; }

void newarray(Frame *frame, Code *code) { return; }

void anewarray(Frame *frame, Code *code) { return; }

void arraylength(Frame *frame, Code *code) { return; }

void athrow(Frame *frame, Code *code) { return; }

void checkcast(Frame *frame, Code *code) { return; }

void instanceof (Frame * frame, Code *code) { return; }

void monitorenter(Frame *frame, Code *code) { return; }

void monitorexit(Frame *frame, Code *code) { return; }

void multianewarray(Frame *frame, Code *code) { return; }

void goto_w(Frame *frame, Code *code) { return; }

void jsr_w(Frame *frame, Code *code) { return; }

void breakpoint(Frame *frame, Code *code) { return; }
