#pragma once

#include "java-bytes.h"
#include "ClassFile.h"
#include "Method.h"
#include "jvm.h"


typedef struct FieldValue
{
  ConstantUtf8Info name_cpinfo;
  ConstantUtf8Info type_cpinfo;
  union
  {
    // value
  };
} FieldValue;

typedef struct Instance
{
  ClassFile* instance_class;
  FieldValue* fields; 
} Instance;

typedef struct MethodArea
{
  ClassFile* classfile;
  Instance* instances;
  FieldValue* static_fields;
} MethodArea;

MethodInfo *getMethod(ClassFile* method_class, char* method_name);

void loadClass(JVM* jvm, char* classname);

ClassFile *getClass(MethodArea* method_area, u2 n_classes, char* classname);
