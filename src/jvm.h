#pragma once

#include "java-bytes.h"
#include "ClassFile.h"
#include "MethodArea.h"
#include "Frame.h"

struct MethodArea;
struct FieldValue;
struct Instance;

typedef struct JVM
{
  // u4 pc;
  u2 frame_count; // Também atua como index do frame atual já que se trata de uma pilha
  Frame *frames;
  u2 method_area_count;
  MethodArea* method_area;
  // ClassFile* current_class;
  // MethodInfo* current_method; // Index para vetor de Methods da Classe atual
} JVM;

JVM *startJVM();

void popFrame(JVM*);

void pushFrame(JVM* jvm, const char* classname, const char* method_name);

Frame *topFrame(JVM* jvm);

void verifyClinit(JVM*);

char* methodName(MethodInfo*, ClassFile*);

char* className(ClassFile*);

void runJVM(JVM*);

FieldValue* getStatic(JVM* jvm, const char* class_name, const char* field_name, const char* type_name);

// Instance* allocNewInstance(JVM* jvm, const char* class_name);

Code fetchCode(Frame* current_frame);

void freeJVM(JVM* jvm);