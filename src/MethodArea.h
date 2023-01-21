#pragma once

#include "java-bytes.h"
#include "ClassFile.h"
#include "Method.h"
#include "jvm.h"

typedef struct MethodArea
{
  ClassFile* classfile;
  // Objetos* instancias;
} MethodArea;

MethodInfo *getMethod(ClassFile* method_class, char* method_name);

ClassFile *loadClass(JVM* jvm, char* classname);

ClassFile *getClass(MethodArea* method_area, u2 n_classes, char* classname);
