#pragma once

#include "java-bytes.h"
#include "ClassFile.h"
#include "MethodArea.h"
#include "Frame.h"

struct MethodArea;
struct FieldValue;
struct Instance;

/**
 * @brief JVM basic structure
 * 
 */
typedef struct JVM
{
  u2 frame_count;
  Frame *frames;
  u2 method_area_count;
  MethodArea* method_area;
} JVM;

/**
 * @brief Initializes, allocs the JVM and return a pointer to it
 * 
 * @return JVM*
 */
JVM *startJVM();

/**
 * @brief Pop top frame from jvm frames
 * 
 * @param jvm Pointer to jvm structure
 * 
 */
void popFrame(JVM* jvm);

/**
 * @brief Pushes new frame into frame stack
 * 
 * @param jvm JVM pointer
 * @param classname name of the new frame class
 * @param method_name name of the new frame method
 */
void pushFrame(JVM* jvm, const char* classname, const char* method_name);

/**
 * @brief Get top frame from frame stack
 * 
 * @param jvm JVM pointer
 * @return Frame* Pointer to frame
 */
Frame *topFrame(JVM* jvm);

/**
 * @brief Verifies existence of clinit and set it to top frame 
 * 
 */
void verifyClinit(JVM*);

/**
 * @brief Get name from MethodInfo
 * 
 * @return char* name of the method
 */
char* methodName(MethodInfo*, ClassFile*);

/**
 * @brief Get name from ClassFile
 * 
 * @return char* name of the class
 */
char* className(ClassFile*);

/**
 * @brief Execute code from frame stack
 * 
 */
void runJVM(JVM*);

/**
 * @brief Get the Static object
 * 
 * @param jvm JVM pointer
 * @param class_name class name
 * @param field_name field name
 * @param type_name type of the variable
 * @return FieldValue* pointer to static variable
 */
FieldValue* getStatic(JVM* jvm, const char* class_name, const char* field_name, const char* type_name);

// Instance* allocNewInstance(JVM* jvm, const char* class_name);

/**
 * @brief Get code from frame
 * 
 * @param current_frame Top frame
 * @return Code Vector of opcodes and operands
 */
Code fetchCode(Frame* current_frame);

/**
 * @brief Free allocated memmory
 * 
 * @param jvm JVM pointer
 */
void freeJVM(JVM* jvm);