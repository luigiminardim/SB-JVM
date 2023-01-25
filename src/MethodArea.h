#pragma once

#include "java-bytes.h"
#include "ClassFile.h"
#include "Method.h"
#include "jvm.h"

/**
 * @brief Struct representing a variable
 * 
 */
typedef struct FieldValue
{
  ConstantUtf8Info name_cpinfo;
  ConstantUtf8Info type_cpinfo;
  union
  {
    // value
  };
} FieldValue;

/**
 * @brief Struct representing a class instance
 * 
 */
typedef struct Instance
{
  ClassFile* instance_class;
  FieldValue* fields;
} Instance;

/**
 * @brief Struct that represents the MethodArea (one per class)
 * 
 */
typedef struct MethodArea
{
  ClassFile classfile;
  u2 instances_count;
  Instance* instances;
  u2 static_fields_count;
  FieldValue* static_fields;
} MethodArea;

struct JVM;

/**
 * @brief Initializes new MethodArea
 * 
 * @param new_ma pointer to methodarea
 */
void initMethodArea(MethodArea* new_ma);

/**
 * @brief Get the Method object
 * 
 * @param method_class pointer to method class classfile
 * @param method_name method name
 * @return MethodInfo* 
 */
MethodInfo *getMethod(ClassFile* method_class, const char* method_name);

/**
 * @brief Load .class into memory
 * 
 * @param jvm pointer to JVM
 * @param classname Name of the class to load
 * @return MethodArea* 
 */
MethodArea* loadClass(JVM* jvm, const char* classname);

/**
 * @brief Get the Class Method Area object
 * 
 * @param jvm pointer to JVM
 * @param classname classname
 * @return MethodArea* 
 */
MethodArea *getClassMethodArea(JVM* jvm, const char* classname);

/**
 * @brief Loads all static fields into FieldValue struct
 * 
 * @param method_area Method area from class to load static fields from
 */
void loadStatic(MethodArea* method_area);

/**
 * @brief Get static variable from class
 * 
 * @param jvm pointer to JVM
 * @param class_name class name
 * @param field_name field name
 * @param type_name field descriptor
 * @return FieldValue* 
 */
FieldValue* getstatic(JVM* jvm, const char* class_name, const char* field_name, const char* type_name);

// Instance* newinstance(MethodArea* method_area, u2 method_area_count, const char* class_name);

/**
 * @brief Free's memory from MethodArea
 * 
 */
void freeMethodArea(MethodArea*);