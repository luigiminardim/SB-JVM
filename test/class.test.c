#include "catch.h"
#include "class.h"
#include <stdlib.h> // malloc

TEST_CASE("Class_read")
{
  FILE *fp = fopen("assets/test-class/SimpleClass.class", "rb");
  Class c = Class_read(fp);
  SECTION("magic_number")
  {
    REQUIRE(c.magic_number == 0xCAFEBABE);
  }
  fclose(fp);
}

TEST_CASE("Class_to_string")
{
  FILE *fp = fopen("assets/test-class/SimpleClass.class", "rb");
  Class c = Class_read(fp);
  char *s = Class_to_string(c);
  printf("\nClass_to_string:\n%s\n\n", s);
  free(s);
  fclose(fp);
}
