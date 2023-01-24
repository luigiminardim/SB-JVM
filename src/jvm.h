#pragma once

#include "java-bytes.h"
#include "ClassFile.h"
#include "MethodArea.h"
#include "Frame.h"

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

void setClass(JVM* jvm, char* classname);

void setMethod(JVM* jvm, char* method_name);

void popFrame(JVM*);

void pushFrame(JVM* jvm, char* classname, char* method_name);

void verifyClinit(JVM*);

char* methodName(MethodInfo*, ClassFile*);

char* className(ClassFile*);

void runJVM(JVM*);

FieldValue* getStatic(JVM* jvm, char* class_name, char* field_name, char* type_name);

Instance* allocNewInstance(JVM* jvm, char* class_name);

Code fetchCode(Frame* current_frame);

void freeJVM(JVM* jvm);