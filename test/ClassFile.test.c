#include "catch.h"
#include "ClassFile.h"
#include <stdlib.h> // malloc

TEST_CASE("ClassFile_read")
{
  FILE *fp = fopen("assets/test-ClassFile/SimpleClass.class", "rb");
  ClassFile c = ClassFile_read(fp);
  SECTION("magic_number")
  {
    REQUIRE(c.magic_number == 0xCAFEBABE);
    REQUIRE(c.minor_version == 0);
    REQUIRE(c.major_version == 52);
  }
  fclose(fp);
}

TEST_CASE("ClassFile_to_string")
{
  FILE *fp = fopen("assets/test-ClassFile/SimpleClass.class", "rb");
  ClassFile c = ClassFile_read(fp);
  char *s = ClassFile_to_string(c);
  printf("\nClassFile_to_string:\n%s\n\n", s);
  free(s);
  fclose(fp);
}
