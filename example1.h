//Van Pham
//CS 3377
//email: vcp160130@utdallas.edu

#ifndef _EXAMPLE1_H_
#define _EXAMPLE1_H_

#include <iostream>
#include <fstream>
#include <stdint.h>

/*
* Records in the file have a fixed length buffer
* that will hold a C-Style string. This is the
* size of the fixed length buffer.
*/
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
