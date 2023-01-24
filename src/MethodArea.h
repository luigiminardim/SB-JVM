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

MethodInfo *getMethod(ClassFile* method_class, char* method_name);

void loadClass(JVM* jvm, char* classname);

MethodArea *getClassMethodArea(MethodArea* method_area, u2 n_classes, char* classname);

void loadStatic(MethodArea* method_area);

FieldValue* getstatic(MethodArea* method_area, u2 method_area_count, char* class_name, char* field_name, char* type_name);

Instance* newinstance(MethodArea* method_area, u2 method_area_count, char* class_name);