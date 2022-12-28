#include <stdio.h>
#include <stdlib.h>
#include "ConstantPool.h"

// ConstantMethodrefInfo ///////////////////////////////////////////////////////////////////////////

ConstantMethodrefInfo ConstantMethodrefInfo_read(FILE *fp)
{
  ConstantMethodrefInfo cfi;
  cfi.class_index = u2_read(fp);
  cfi.name_and_type_index = u2_read(fp);
  return cfi;
};

char *ConstantMethodrefInfo_to_string(ConstantMethodrefInfo cfi)
{
  char *s = (char *)malloc(256);
  sprintf(s, "{\"__cls\":\"ConstantMethodrefInfo\",\"class_index\":\"#%d\",\"name_and_type_index\":\"#%d\"}", cfi.class_index, cfi.name_and_type_index);
  return s;
};

// ConstantFieldrefInfo ////////////////////////////////////////////////////////////////////////////

ConstantFieldrefInfo ConstantFieldrefInfo_read(FILE *fp)
{
  ConstantFieldrefInfo cfi;
  cfi.class_index = u2_read(fp);
  cfi.name_and_type_index = u2_read(fp);
  return cfi;
};

char *ConstantFieldrefInfo_to_string(ConstantFieldrefInfo cfi)
{
  char *s = (char *)malloc(256);
  sprintf(s, "{\"__cls\":\"ConstantFieldrefInfo\",\"class_index\":\"#%d\",\"name_and_type_index\":\"#%d\"}", cfi.class_index, cfi.name_and_type_index);
  return s;
};

// ConstantFloatInfo ///////////////////////////////////////////////////////////////////////////////

ConstantFloatInfo ConstantFloatInfo_read(FILE *fp)
{
  ConstantFloatInfo cfi;
  // bytes is in big endian. We need to convert it to little endian.
  u4 bytes = u4_read(fp);
  void *ptr = &bytes;
  cfi.bytes = *(float *)ptr;
  return cfi;
};

char *ConstantFloatInfo_to_string(ConstantFloatInfo cfi)
{
  char *s = (char *)malloc(256);
  sprintf(s, "{\"__cls\":\"ConstantFloatInfo\",\"bytes\":%f}", cfi.bytes);
  return s;
};

// ConstantLongInfo ////////////////////////////////////////////////////////////////////////////////

ConstantLongInfo ConstantLongInfo_read(FILE *fp)
{
  ConstantLongInfo cfi;
  u4 high_bytes = u4_read(fp);
  u4 low_bytes = u4_read(fp);
  cfi.bytes = ((int64_t)high_bytes << 32) | low_bytes;
  return cfi;
};

char *ConstantLongInfo_to_string(ConstantLongInfo cfi)
{
  char *s = (char *)malloc(256);
  sprintf(s, "{\"__cls\":\"ConstantLongInfo\",\"bytes\":%ld}", cfi.bytes);
  return s;
};

// ConstantDoubleInfo //////////////////////////////////////////////////////////////////////////////

ConstantDoubleInfo ConstantDoubleInfo_read(FILE *fp)
{
  ConstantDoubleInfo cfi;
  u4 high_bytes = u4_read(fp);
  u4 low_bytes = u4_read(fp);
  uint64_t bytes = ((int64_t)high_bytes << 32) | low_bytes;
  void *ptr = &bytes;
  cfi.bytes = *(double *)ptr;
  return cfi;
};

char *ConstantDoubleInfo_to_string(ConstantDoubleInfo cfi)
{
  char *s = (char *)malloc(256);
  sprintf(s, "{\"__cls\":\"ConstantDoubleInfo\",\"bytes\":%f}", cfi.bytes);
  return s;
};

// ConstantStringInfo //////////////////////////////////////////////////////////////////////////////

ConstantStringInfo ConstantStringInfo_read(FILE *fp)
{
  ConstantStringInfo csi;
  csi.string_index = u2_read(fp);
  return csi;
};

char *ConstantStringInfo_to_string(ConstantStringInfo csi)
{
  char *s = (char *)malloc(256);
  sprintf(s, "{\"__cls\":\"ConstantStringInfo\",\"string_index\":\"#%d\"}", csi.string_index);
  return s;
};

// ConstantClassInfo ///////////////////////////////////////////////////////////////////////////////

ConstantClassInfo ConstantClassInfo_read(FILE *fp)
{
  ConstantClassInfo cci;
  cci.name_index = u2_read(fp);
  return cci;
};

char *ConstantClassInfo_to_string(ConstantClassInfo cci)
{
  char *s = (char *)malloc(256);
  sprintf(s, "{\"__cls\":\"ConstantClassInfo\",\"name_index\":\"#%d\"}", cci.name_index);
  return s;
};

// ConstantInterfaceMethodrefInfo //////////////////////////////////////////////////////////////////

ConstantInterfaceMethodrefInfo ConstantInterfaceMethodrefInfo_read(FILE *fp)
{
  ConstantInterfaceMethodrefInfo cimi;
  cimi.class_index = u2_read(fp);
  cimi.name_and_type_index = u2_read(fp);
  return cimi;
};

char *ConstantInterfaceMethodrefInfo_to_string(ConstantInterfaceMethodrefInfo cimi)
{
  char *s = (char *)malloc(256);
  sprintf(s, "{\"__cls\":\"ConstantInterfaceMethodrefInfo\",\"class_index\":\"#%d\",\"name_and_type_index\":\"#%d\"}", cimi.class_index, cimi.name_and_type_index);
  return s;
};

// ConstantUtf8Info ////////////////////////////////////////////////////////////////////////////////

ConstantUtf8Info ConstantUtf8Info_read(FILE *fp)
{
  ConstantUtf8Info cui;
  cui.length = u2_read(fp);
  cui.bytes = (char *)malloc(cui.length + 1);
  fread(cui.bytes, cui.length, 1, fp);
  cui.bytes[cui.length] = '\0';
  return cui;
};

char *ConstantUtf8Info_to_string(ConstantUtf8Info cui)
{
  char *s = (char *)malloc(256);
  sprintf(s, "{\"__cls\":\"ConstantUtf8Info\",\"length\":%d,\"bytes\":\"%s\"}", cui.length, cui.bytes);
  return s;
};

// ConstantIntegerInfo /////////////////////////////////////////////////////////////////////////////

ConstantIntegerInfo ConstantIntegerInfo_read(FILE *fp)
{
  ConstantIntegerInfo cii;
  cii.bytes = u4_read(fp);
  return cii;
};

char *ConstantIntegerInfo_to_string(ConstantIntegerInfo cii)
{
  char *s = (char *)malloc(256);
  sprintf(s, "{\"__cls\":\"ConstantIntegerInfo\",\"bytes\":%d}", cii.bytes);
  return s;
};

// ConstantNameAndTypeInfo /////////////////////////////////////////////////////////////////////////

ConstantNameAndTypeInfo ConstantNameAndTypeInfo_read(FILE *fp)
{
  ConstantNameAndTypeInfo cti;
  cti.name_index = u2_read(fp);
  cti.descriptor_index = u2_read(fp);
  return cti;
};

char *ConstantNameAndTypeInfo_to_string(ConstantNameAndTypeInfo cti)
{
  char *s = (char *)malloc(256);
  sprintf(s, "{\"__cls\":\"ConstantNameAndTypeInfo\",\"name_index\":\"#%d\",\"descriptor_index\":\"#%d\"}", cti.name_index, cti.descriptor_index);
  return s;
};

// CpInfo //////////////////////////////////////////////////////////////////////////////////////////

CpInfo CpInfo_read(FILE *fp)
{
  CpInfo ci;
  ci.tag = (ConstantType)u1_read(fp);
  switch (ci.tag)
  {
  case CONSTANT_METHODREF:
    ci.constant_methodref_info = ConstantMethodrefInfo_read(fp);
    break;
  case CONSTANT_FIELDREF:
    ci.constant_fieldref_info = ConstantFieldrefInfo_read(fp);
    break;
  case CONSTANT_FLOAT:
    ci.constant_float_info = ConstantFloatInfo_read(fp);
    break;
  case CONSTANT_LONG:
    ci.constant_long_info = ConstantLongInfo_read(fp);
    break;
  case CONSTANT_DOUBLE:
    ci.constant_double_info = ConstantDoubleInfo_read(fp);
    break;
  case CONSTANT_STRING:
    ci.constant_string_info = ConstantStringInfo_read(fp);
    break;
  case CONSTANT_CLASS:
    ci.constant_class_info = ConstantClassInfo_read(fp);
    break;
  case CONSTANT_INTERFACE_METHOD_REF:
    ci.constant_interface_methodref_info = ConstantInterfaceMethodrefInfo_read(fp);
    break;
  case CONSTANT_UTF8:
    ci.constant_utf8_info = ConstantUtf8Info_read(fp);
    break;
  case CONSTANT_INTEGER:
    ci.constant_integer_info = ConstantIntegerInfo_read(fp);
    break;
  case CONSTANT_NAME_AND_TYPE:
    ci.constant_name_and_type_info = ConstantNameAndTypeInfo_read(fp);
    break;
  default:
    break;
  }
  return ci;
}

char *CpInfo_to_string(CpInfo ci)
{
  char *s;
  switch (ci.tag)
  {
  case CONSTANT_METHODREF:
    s = ConstantMethodrefInfo_to_string(ci.constant_methodref_info);
    break;
  case CONSTANT_FIELDREF:
    s = ConstantFieldrefInfo_to_string(ci.constant_fieldref_info);
    break;
  case CONSTANT_FLOAT:
    s = ConstantFloatInfo_to_string(ci.constant_float_info);
    break;
  case CONSTANT_LONG:
    s = ConstantLongInfo_to_string(ci.constant_long_info);
    break;
  case CONSTANT_DOUBLE:
    s = ConstantDoubleInfo_to_string(ci.constant_double_info);
    break;
  case CONSTANT_STRING:
    s = ConstantStringInfo_to_string(ci.constant_string_info);
    break;
  case CONSTANT_CLASS:
    s = ConstantClassInfo_to_string(ci.constant_class_info);
    break;
  case CONSTANT_INTERFACE_METHOD_REF:
    s = ConstantInterfaceMethodrefInfo_to_string(ci.constant_interface_methodref_info);
    break;
  case CONSTANT_UTF8:
    s = ConstantUtf8Info_to_string(ci.constant_utf8_info);
    break;
  case CONSTANT_INTEGER:
    s = ConstantIntegerInfo_to_string(ci.constant_integer_info);
    break;
  case CONSTANT_NAME_AND_TYPE:
    s = ConstantNameAndTypeInfo_to_string(ci.constant_name_and_type_info);
    break;
  default:
    s = (char *)malloc(256);
    snprintf(s, 255, "null");
    break;
  }
  return s;
}

// ConstantPool ////////////////////////////////////////////////////////////////////////////////////

ConstantPool ConstantPool_read(FILE *fp, u2 constant_pool_count)
{
  ConstantPool cp = (CpInfo *)malloc((constant_pool_count + 1) * sizeof(CpInfo));
  for (u2 i = 1; i < constant_pool_count; i++)
  {
    cp[i] = CpInfo_read(fp);
    if (cp[i].tag == CONSTANT_LONG || cp[i].tag == CONSTANT_DOUBLE)
    {
      i++; // Long and Double take up two slots in the constant pool (see JVM Spec 4.5.5)
    }
  }
  return cp;
}

char *ConstantPool_to_string(ConstantPool cp, u2 constant_pool_count)
{
  char *cp_string = (char *)malloc(1000000);
  snprintf(cp_string, 1000000, "{\"__cls\":\"ConstantPool\",");
  for (int i = 1; i < constant_pool_count; i++)
  {
    char *ci_string = CpInfo_to_string(cp[i]);
    char *final_string = (char *)malloc(1000000);
    char comma_string = i == constant_pool_count - 1 ? '}' : ',';
    snprintf(final_string, 1000000, "%s\"#%d\":%s%c", cp_string, i, ci_string, comma_string);
    free(cp_string);
    free(ci_string);
    cp_string = final_string;
    if (cp[i].tag == CONSTANT_LONG || cp[i].tag == CONSTANT_DOUBLE)
    {
      i++; // Long and Double take up two slots in the constant pool (see JVM Spec 4.5.5)
    }
  }
  return cp_string;
}


void ConstantPool_free(ConstantPool cp) {
  free(cp);
}
