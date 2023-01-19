#pragma once

#include "java-bytes.h"
#include "ClassFile.h"
#include "Method.h"

typedef struct MethodArea
{
  ClassFile* classfile;
  // Objetos* instancias;
} MethodArea;

MethodInfo *getMethod(ClassFile* method_class, char* method_name);