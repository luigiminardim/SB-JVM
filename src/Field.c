#include "Field.h"
#include "ClassFile.h"
#include "java-bytes.h"
#include <stdio.h>  // sprintf
#include <stdlib.h> // malloc

FieldInfo* FieldInfo_read(FILE *fp, u2 fields_count){

    FieldInfo* fields = (FieldInfo*) malloc(fields_count * sizeof(FieldInfo));
    FieldInfo* f;

    // itera sobre os fields
    for(f=fields; f<fields+fields_count; f++){
        f->access_flags = u2_read(fp);
        f->name_index = u2_read(fp);
        f->descriptor_index = u2_read(fp);
        f->attributes_count = u2_read(fp);
        // f->attributes = AttributeInfo_read(fp, attributes_count)
    }

    return fields;
}

void FieldInfo_release(FieldInfo* field_info, u2 fields_count){
    
    FieldInfo* f;

    for(f=field_info; f<field_info+fields_count; f++){
        // AttributeInfo_release(f->attributes)
    }
    
    free(field_info);
}