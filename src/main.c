#include <stdio.h>
#include <string.h>
#include <stdlib.h> // exit
#include "read_classfile_usecase.h"
#include "jvm.h"
#include <libgen.h>

int main(int argc, char **argv)
{
  const char *command = argc > 1 ? argv[1] : NULL;
  char *file_name = argc > 2 ? argv[2] : NULL;

  if (!strcmp(command, "read") != 0)
  {
    read_classfile_usecase(file_name);
  }
  else if (!strcmp(command, "exec") != 0){
    // Tratamento da entrada
    char *classe = basename(file_name);
    char *dot = strrchr(classe, '.');
    *dot = '\0';

    JVM* jvm = startJVM();
    loadClass(jvm, file_name);
    pushFrame(jvm, classe, "main");
    verifyClinit(jvm);
    runJVM(jvm);
    freeJVM(jvm);
  }
  else
  {
    printf("Usage: %s [exec|read] [file_name]\n", argv[0]);
    exit(1);
  }
}
