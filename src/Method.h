#pragma once

#include <stdint.h>
#include <stdio.h>
#include "java-bytes.h"
#include "AttributeInfo.h"

/**
 * @brief Struct that represents Method from classfile
 * 
 */
typedef struct MethodInfo
{
  u2 access_flags;
  u2 name_index;
  u2 descriptor_index;
  u2 attributes_count;
  AttributeInfo *attributes;
} MethodInfo;

/**
 * @brief Read's method into memory
 * 
 * @param fp pointer to .class file
 * @param methods_count Number of methods
 * @param constant_pool Constantpool object
 * @return MethodInfo* 
 */
MethodInfo *MethodInfo_read(FILE *fp, u2 methods_count, ConstantPool constant_pool);

/**
 * @brief Free's methodinfo struct
 * 
 * @param method_infos Struct to be free
 * @param methods_count Number of methods
 * @param constant_pool Constantpool object
 */
void MethodInfo_free(MethodInfo *method_infos, u2 methods_count, ConstantPool constant_pool);

/**
 * @brief Prints Methodnfo struct
 * 
 * @param method_infos MethodInfo to be printed
 * @param methods_count Number of Methods
 * @param constant_pool ConstantPool Object
 * @return char* 
 */
char *MethodInfo_to_string(MethodInfo* method_infos, u2 methods_count, ConstantPool constant_pool);
