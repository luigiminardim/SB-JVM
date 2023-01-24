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
  u2 instances_count;
  Instance* instances;
  u2 static_fields_count;
  FieldValue* static_fields;
} MethodArea;

MethodArea* initMethodArea();

MethodInfo *getMethod(ClassFile* method_class, char* method_name);

MethodArea* loadClass(JVM* jvm, char* classname);

MethodArea *getClassMethodArea(JVM* jvm, char* classname);

void loadStatic(MethodArea* method_area);

FieldValue* getstatic(JVM* jvm, char* class_name, char* field_name, char* type_name);

Instance* newinstance(MethodArea* method_area, u2 method_area_count, char* class_name);