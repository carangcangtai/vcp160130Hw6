/*
 * Usage of CDK Matrix
 *
 * File:   example1.cc
 * Author: Stephen Perkins
 * Email:  stephen.perkins@utdallas.edu
 */

#include <iostream>
#include "cdk.h"
#include "example1.h"
#include <inttypes.h>
#define MATRIX_WIDTH 3
#define MATRIX_HEIGHT 5
#define BOX_WIDTH 17
#define MATRIX_NAME_STRING "Binary File Contents"

using namespace std;


int main()
{

  WINDOW	*window;
  CDKSCREEN	*cdkscreen;
  CDKMATRIX     *myMatrix;           // CDK Screen Matrix

  const char 		*rowTitles[MATRIX_HEIGHT+1] = {"R0", "a", "b", "c", "d", "e" };
  const char 		*columnTitles[MATRIX_WIDTH+1] = {"C0", "a",  "b", "c" };
  int		boxWidths[MATRIX_WIDTH+1] = {BOX_WIDTH, BOX_WIDTH, BOX_WIDTH, BOX_WIDTH};
  int		boxTypes[MATRIX_WIDTH+1] = {vMIXED, vMIXED, vMIXED, vMIXED};

  /*
   * Initialize the Cdk screen.
   *
   * Make sure the putty terminal is large enough
   */
  window = initscr();
  cdkscreen = initCDKScreen(window);

  /* Start CDK Colors */
  initCDKColor();

  /*
   * Create the matrix.  Need to manually cast (const char**) to (char **)
  */
  myMatrix = newCDKMatrix(cdkscreen, CENTER, CENTER, MATRIX_HEIGHT, MATRIX_WIDTH, MATRIX_HEIGHT, MATRIX_WIDTH,
			  MATRIX_NAME_STRING, (char **) columnTitles, (char **) rowTitles, boxWidths,
				     boxTypes, 1, 1, ' ', ROW, true, true, false);

  if (myMatrix ==NULL)
    {
      printf("Error creating Matrix\n");
      _exit(1);
    }

  /* Display the Matrix */
  drawCDKMatrix(myMatrix, true);

  BinaryFileHeader *myHeader = new BinaryFileHeader();
  ifstream binFile ("cs3377.bin", ios::in | ios::binary);
  binFile.read((char*)myHeader, sizeof(BinaryFileHeader));


  /*
   * Dipslay a message
   */
  char buffer[32];
  sprintf(buffer, "Magic: 0x%X", myHeader -> magicNumber);
  setCDKMatrixCell(myMatrix, 1, 1, buffer);
  sprintf(buffer, "Version: %d", myHeader -> versionNumber);
  setCDKMatrixCell(myMatrix, 1, 2, buffer);
  sprintf(buffer, "NumRecords: %" PRIu64, myHeader ->numRecords);
  setCDKMatrixCell(myMatrix, 1, 3, buffer);

  for (int i = 2; i<6; i++)
    {
      BinaryFileRecord *myRecord = new BinaryFileRecord();
      binFile.read((char*)myRecord, sizeof(BinaryFileRecord));
      sprintf(buffer, "strlen: %" PRIu8, myRecord -> strLength);
      setCDKMatrixCell(myMatrix, i, 1, buffer);
      sprintf(buffer, "%s", myRecord -> stringBuffer);
      setCDKMatrixCell(myMatrix, i, 2, buffer);
    }

  //  setCDKMatrixCell(myMatrix, 2, 2, "Test Message");
  drawCDKMatrix(myMatrix, true);    /* required  */

  /* so we can see results */
  sleep (10);

  binFile.close();
  // Cleanup screen
  endCDK();
}
