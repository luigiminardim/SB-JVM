#pragma once

#include "java-bytes.h"
#include "ClassFile.h"
#include "MethodArea.h"

typedef struct JVM
{
  u4 pc;
  u2 frame_count; // Também atua como index do frame atual já que se trata de uma pilha
  // Frame *frames;
  u2 method_area_count;
  ClassFile* method_area;
  ClassFile* current_class;
  MethodInfo* current_method; // Index para vetor de Methods da Classe atual
} JVM;

JVM *startJVM();

// Classfile ou Class
void setClass(JVM* jvm, char* classname);

void setMethod(JVM* jvm, char* method_name);

void popFrame(JVM*);

void pushFrame(JVM*);

void saveContext(JVM*);

void restoreContext(JVM*);

void runJVM(JVM*);

void freeJVM(JVM* jvm);