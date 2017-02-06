/***********************************************************************
* Program:
*    Lab C_lab, ECEN 324 Learning C Lab
*    Brother Jones, ECEN 324
* Author:
*    Brady Field
* Summary:
*    A program that highlights deifferences in C from C++
************************************************************************/

#include <stdio.h>
#include <stdlib.h>

#define PI 3.1415926

/***********************************************************************
* runs various tests for C syntax
***********************************************************************/
int main (void)
{
   int m = 7;
   m = m | m >> 1;
   m = m | m >> 2;
   m = m | m >> 4;
   m = m | m >> 8;
   m = m | m >> 16;
   m = m & ((~m >> 1)^0x80000000);
   printf("m is now %x\n", m);

   return 0;
}

