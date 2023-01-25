#include "exec_classfile_usecase.h"
#include <stdlib.h>
#include <string.h>
#include <libgen.h>
#include "jvm.h"

void exec_classfile_usecase(const char* file_name){

    char * copy = (char *)malloc(sizeof(char) *(strlen(file_name) + 1)); 
    strcpy(copy, file_name);

    char *dot = strrchr(copy, '.');
    *dot = '\0';

    JVM* jvm = startJVM();
    loadClass(jvm, copy);

    char *classe = basename(copy);
    pushFrame(jvm, classe, "main");
    verifyClinit(jvm);
    runJVM(jvm);
    freeJVM(jvm);
    free(copy);
}