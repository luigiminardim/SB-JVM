#include "catch.h"
#include "ClassFile.h"
#include <stdlib.h> // malloc
#include <string.h> // strcmp

TEST_CASE("Method_read"){
    FILE *fp = fopen("assets/test-Method/SumNumber.class", "rb");
    ClassFile c = ClassFile_read(fp);
    CpInfo cpinfo;
    
    SECTION("ACCESS_FLAGS"){
        REQUIRE(c.methods[3].access_flags == 9);
    }
    
    SECTION("NAME_INDEX"){
        cpinfo = c.constant_pool[c.methods[3].name_index];
        char* test_name_index = cpinfo.constant_utf8_info.bytes;
        REQUIRE(strcmp(test_name_index, "Soma") == 0);
    }
    
    SECTION("DESCRIPTOR_INDEX"){
        cpinfo = c.constant_pool[c.methods[3].descriptor_index];
        char* test_descriptor_index = cpinfo.constant_utf8_info.bytes;
        REQUIRE(strcmp(test_descriptor_index, "(II)I") == 0);
    }
    
    SECTION("ATTRIBUTE_COUNT"){
        REQUIRE(c.methods[3].attributes_count == 1);
    }

}