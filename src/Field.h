#pragma once

#include <stdint.h>
#include <stdio.h>
#include "java-bytes.h"
#include "AttributeInfo.h"

/**
 * @brief Struct to represent field from classfile
 * 
 */
typedef struct FieldInfo
{
  u2 access_flags;
  u2 name_index;
  u2 descriptor_index;
  u2 attributes_count;
  AttributeInfo *attributes;
} FieldInfo;

/**
 * @brief Read field from classfile into memory
 * 
 * @param fp File pointer to .class file
 * @param fields_count Number of fields
 * @param constant_pool Constantpool Object
 * @return FieldInfo* 
 */
FieldInfo *FieldInfo_read(FILE *fp, u2 fields_count, ConstantPool constant_pool);

/**
 * @brief Free's field allocated memory
 * 
 * @param field_infos Pointer's to fields
 * @param fields_count Number of fields
 * @param constant_pool Constantpool object
 */
void FieldInfo_free(FieldInfo *field_infos, u2 fields_count, ConstantPool constant_pool);

/**
 * @brief Prints fields
 * 
 * @param field_infos Pointer's to fields
 * @param fields_count Number of fields
 * @param constant_pool Constantpool object
 * @return char* 
 */
char *FieldInfo_to_string(FieldInfo *field_infos, u2 fields_count, ConstantPool constant_pool);
