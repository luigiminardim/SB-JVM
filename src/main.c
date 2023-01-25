#include <stdio.h>
#include <string.h>
#include <stdlib.h> // exit
#include "read_classfile_usecase.h"
#include "jvm.h"
#include <unistd.h>

int main(int argc, char **argv)
{
  //const char *command = argc > 1 ? argv[1] : NULL;
  //char *file_name = argc > 2 ? argv[2] : NULL;
  const char* command = "exec";
  const char* file_name = "assets/test-JVM/Soma";
  JVM* jvm = startJVM();
  loadClass(jvm, file_name);
  pushFrame(jvm,"Soma","main");
  runJVM(jvm);
  freeJVM(jvm);
  //printf("%d",m->classfile->this_class);
  //if (!strcmp(command, "read") != 0)
  //{
  //  read_classfile_usecase(file_name);
  //}
  //else if (!strcmp(command, "exec") != 0)
  //{
  //  printf("a");
  //  JVM* jvm = startJVM();
  //  loadClass(jvm, file_name);
  //  pushFrame(jvm, "Soma", "main");
  //  verifyClinit(jvm);
  //  runJVM(jvm);
  //  freeJVM(jvm);
  //  printf("Not implemented yet\n");
  //}
  //else
  //{
  //  printf("Usage: %s [exec|read] [file_name]\n", argv[0]);
  //  exit(1);
  //}
}
