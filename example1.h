#ifndef _EXAMPLE1_H_
#define _EXAMPLE1_H_

#include <iostream>
#include <fstream>
#include <stdint.h>

const int maxRecordStringLength = 25;

class BinaryFileRecord
{
 public:

  uint8_t strLength;
  char stringBuffer[maxRecordStringLength];
};

class BinaryFileHeader
{
 public:

  uint32_t magicNumber;
  uint32_t versionNumber;
  uint64_t numRecords;
};

#endif
