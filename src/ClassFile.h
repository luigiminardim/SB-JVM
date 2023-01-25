#pragma once

#include <stdint.h>
#include <stdio.h>
#include "java-bytes.h"
#include "ConstantPool.h"
#include "Field.h"
#include "Method.h"

/**
 * @brief Struct that represents a classfile in memory
 * 
 */
typedef struct ClassFile
{
  u4 magic_number;
  u2 minor_version;
  u2 major_version;
  u2 constant_pool_count;
  ConstantPool constant_pool;
  u2 access_flags;
  u2 this_class;
  u2 super_class;
  u2 interfaces_count;
  u2 *interfaces;
  u2 fields_count;
  FieldInfo* fields;
  u2 methods_count;
  MethodInfo* methods;
  u2 attributes_count;
  AttributeInfo* attributes;
} ClassFile;

/**
 * @brief Reads classfile into memory
 * 
 * @param fp File pointer to .class file
 * @return ClassFile 
 */
ClassFile ClassFile_read(FILE *fp);

/**
 * @brief Prints classfile
 * 
 * @param c Classfile object
 * @return char* 
 */
char *ClassFile_to_string(ClassFile c);

/**
 * @brief Free's classfile allocated memory
 * 
 * @param c 
 */
void ClassFile_free(ClassFile c);
