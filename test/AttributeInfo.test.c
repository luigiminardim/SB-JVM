#include "catch.h"
#include "ClassFile.h"
#include <stdlib.h> // malloc
#include <string.h> // strcmp

TEST_CASE("Attribute_read"){
    FILE *fp = fopen("assets/test-AttributeInfo/SumNumber.class", "rb");
    ClassFile c = ClassFile_read(fp);
    CpInfo cpinfo;
    CpInfo tmpCPinfo;

    SECTION("CONSTANT_VALUE"){
        cpinfo = c.constant_pool[c.fields[1].attributes->constant_value.constantvalue_index];
        REQUIRE(cpinfo.constant_integer_info.bytes == 2);
    }
    
    SECTION("CODE"){
        REQUIRE(c.methods[3].attributes[0].code.max_stack == 2);
    }
    
    //SECTION("EXCEPTION"){
    //    
    //}
    
    SECTION("EXCEPTION_Table"){
        cpinfo = c.constant_pool[c.methods[2].attributes[0].code.exception_table[0].catch_type];
        tmpCPinfo = c.constant_pool[cpinfo.constant_class_info.name_index];
        char* test_catch_type = tmpCPinfo.constant_utf8_info.bytes;
        REQUIRE(strcmp(test_catch_type, "java/lang/ArrayIndexOutOfBoundsException") == 0);
    }

    SECTION("SOURCEFILE"){
        cpinfo = c.constant_pool[c.attributes[0].source_file.sourcefile_index];
        char* test_source = cpinfo.constant_utf8_info.bytes;
        REQUIRE(strcmp(test_source, "SumNumber.java") == 0);
    }

}