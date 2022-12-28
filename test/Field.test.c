#include "catch.h"
#include "ClassFile.h"
#include <stdlib.h> // malloc
#include <string.h> // strcmp

TEST_CASE("Field_read"){
    FILE *fp = fopen("assets/test-Field/SimpleClassField.class", "rb");
    ClassFile c = ClassFile_read(fp);
    CpInfo cpinfo;
    
    SECTION("ACCESS_FLAGS"){
        REQUIRE(c.fields[1].access_flags == 1);
    }
    
    SECTION("NAME_INDEX"){
        cpinfo = c.constant_pool[c.fields[2].name_index];
        char* test_name_index = cpinfo.constant_utf8_info.bytes;
        REQUIRE(strcmp(test_name_index, "third_attribute") == 0);
    }
    
    SECTION("DESCRIPTOR_INDEX"){
        cpinfo = c.constant_pool[c.fields[2].descriptor_index];
        char* test_descriptor_index = cpinfo.constant_utf8_info.bytes;
        REQUIRE(strcmp(test_descriptor_index, "Z") == 0);
    }
    
    SECTION("ATTRIBUTE_COUNT"){
        REQUIRE(c.fields[1].attributes_count == 0);
    }

}