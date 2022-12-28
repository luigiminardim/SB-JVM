#include "catch.h"
#include "ClassFile.h"
#include <stdlib.h> // malloc
#include <string.h> // strcmp

TEST_CASE("Attribute_read"){
    FILE *fp = fopen("assets/test-AttributeInfo/SumNumber.class", "rb");
    ClassFile c = ClassFile_read(fp);
    CpInfo cpinfo;

    SECTION("CONSTANT_VALUE"){
        cpinfo = c.constant_pool[c.fields[1].attributes->constant_value.constantvalue_index];
        REQUIRE(cpinfo.constant_integer_info.bytes == 2);
    }
    
    // Precisam de methodinfo implementado
    //SECTION("CODE"){
    //    
    //}
    
    //SECTION("EXCEPTION"){
    //    
    //}
    
    //SECTION("SOURCEFILE"){
    //}

}