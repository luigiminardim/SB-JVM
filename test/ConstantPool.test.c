#include "catch.h"
#include "ClassFile.h"
#include <stdlib.h> // malloc
#include <string.h> // strcmp

TEST_CASE("ConstantPool_read")
{
  FILE *fp = fopen("assets/test-ConstantPool/AllConstanPoolCases.class", "rb");
  ClassFile c = ClassFile_read(fp);
  SECTION("CONSTANT_METHODREF")
  {
    CpInfo cp_info = c.constant_pool[1];
    REQUIRE(cp_info.tag == CONSTANT_METHODREF);
    REQUIRE(cp_info.constant_methodref_info.class_index == 24);
    REQUIRE(cp_info.constant_methodref_info.name_and_type_index == 49);
  }
  SECTION("CONSTANT_FIELDREF")
  {
    CpInfo cp_info = c.constant_pool[2];
    REQUIRE(cp_info.tag == CONSTANT_FIELDREF);
    REQUIRE(cp_info.constant_fieldref_info.class_index == 14);
    REQUIRE(cp_info.constant_fieldref_info.name_and_type_index == 50);
  }
  SECTION("CONSTANT_FLOAT")
  {
    CpInfo cp_info = c.constant_pool[3];
    REQUIRE(cp_info.tag == CONSTANT_FLOAT);
    REQUIRE(cp_info.constant_float_info.bytes == 101.0f);
  }
  SECTION("CONSTANT_LONG")
  {
    CpInfo cp_info = c.constant_pool[5];
    REQUIRE(cp_info.tag == CONSTANT_LONG);
    REQUIRE(cp_info.constant_long_info.bytes == 102l);
  }
  SECTION("CONSTANT_DOUBLE")
  {
    CpInfo cp_info = c.constant_pool[8];
    REQUIRE(cp_info.tag == CONSTANT_DOUBLE);
    REQUIRE(cp_info.constant_double_info.bytes == 103.0);
  }
  SECTION("CONSTANT_STRING")
  {
    CpInfo cp_info = c.constant_pool[11];
    REQUIRE(cp_info.tag == CONSTANT_STRING);
    REQUIRE(cp_info.constant_string_info.string_index == 54);
  }
  SECTION("CONSTANT_CLASS")
  {
    CpInfo cp_info = c.constant_pool[14];
    REQUIRE(cp_info.tag == CONSTANT_CLASS);
    REQUIRE(cp_info.constant_class_info.name_index == 57);
  }
  SECTION("CONSTANT_INTERFACE_METHOD_REF")
  {
    CpInfo cp_info = c.constant_pool[17];
    REQUIRE(cp_info.tag == CONSTANT_INTERFACE_METHOD_REF);
    REQUIRE(cp_info.constant_interface_methodref_info.class_index == 25);
    REQUIRE(cp_info.constant_interface_methodref_info.name_and_type_index == 60);
  }
  SECTION("CONSTANT_UTF8")
  {
    CpInfo cp_info = c.constant_pool[26];
    REQUIRE(cp_info.tag == CONSTANT_UTF8);
    REQUIRE(cp_info.constant_utf8_info.length == 15);
    REQUIRE(strcmp(cp_info.constant_utf8_info.bytes, "constantInteger") == 0);
  }
  SECTION("CONSTANT_INTEGER")
  {
    CpInfo cp_info = c.constant_pool[29];
    REQUIRE(cp_info.tag == CONSTANT_INTEGER);
    REQUIRE(cp_info.constant_integer_info.bytes == 100);
  }
  SECTION("CONSTANT_NAME_AND_TYPE")
  {
    CpInfo cp_info = c.constant_pool[49];
    REQUIRE(cp_info.tag == CONSTANT_NAME_AND_TYPE);
    REQUIRE(cp_info.constant_name_and_type_info.name_index == 39);
    REQUIRE(cp_info.constant_name_and_type_info.descriptor_index == 40);
  }
  fclose(fp);
  ClassFile_free(c);
}

TEST_CASE("ConstantPool_to_string")
{
  FILE *fp = fopen("assets/test-ConstantPool/AllConstanPoolCases.class", "rb");
  ClassFile c = ClassFile_read(fp);
  char *s = ConstantPool_to_string(c.constant_pool, c.constant_pool_count);
  printf("\nConstantPool_to_string:\n%s\n\n", s);
  free(s);
  fclose(fp);
  ClassFile_free(c);
}
