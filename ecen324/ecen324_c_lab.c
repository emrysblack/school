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
   /* Printing various items */
 
   const char LETTER = 'A';
   printf("%d\n", 24);
   printf("%.5f\n", PI);
   printf("%c\n", LETTER);
 
   float payRate = 10.50;
   int hours = 40;
 
   printf("Users pay rate: $%.1f\n", payRate);
   printf(" Hours worked: %d\n", hours);
   printf("    Gross Pay: $%.0f\n", hours * payRate);
 
   int number;
   fprintf(stderr,"Enter number: ");
   scanf("%d", &number);
   printf("Twice %d is %d\n", number, number * 2);
 
   /*********************************************************************/
   /*********************** Output an Integer ***************************/
   /*********************************************************************/
   int anInt = 99;
   float aFloat = 43.2;
 
   /* Output the integer with the default formatting. */
                  
   printf("\nInteger: %d ###\n", anInt);
 
   /* Output the integer in a fixed field width of 10. */
   /* The object will be right justified in the field. */
   
   printf("Integer: %10d ###\n", anInt);
 
   /* Output the integer in a fixed field width of 10 */
   /* and left justified in the field. */
   
   printf("Integer: %-10d ###\n\n", anInt);
 
   
   /*********************************************************************/
   /************************* Output a Float ****************************/
   /*********************************************************************/
 
   /* Output the float with one decimal place. */
   
   printf("  Float: %.1f ###\n", aFloat);
 
   /* Output the float in a fixed field width of 10. */
   /* Keep a precision of 1 and left justify. */
   
   printf("  Float: %-10.1f ###\n", aFloat);
 
   /* Output the float right justified in a field width of 10 with   */
   /* a precision of 2 places after the decimal point for the float.  */
   
   printf("  Float: %10.2f ###\n", aFloat);
 
   /* Output the float with 3 places of precision after the decimal point */
   
   printf("  Float: %.3f ###\n", aFloat);
 
   /* Output the float with 3 places of precision after the decimal point */
   /* with a field width of 10. */
   
   printf("  Float: %10.3f ###\n", aFloat);
  
   /* Output the float with 4 places of precision after the decimal point */
   /* with a field width of 10 and left justify the number. */
   
   printf("  Float: %-10.4f ###\n\n", aFloat);
 
   /*********************************************************************
    *************** Create some code to output a table ******************
    *********************************************************************
 
    * The following table has a leading tab.
 
        Oct   Dec   Hex   Char
        ----------------------
        141   97    61    a
        142   98    62    b
        143   99    63    c
        144   100   64    d
        145   101   65    e
        146   102   66    f
        147   103   67    g
        150   104   68    h
        151   105   69    i
        152   106   6a    j
        153   107   6b    k
        154   108   6c    l
        155   109   6d    m
        156   110   6e    n
        157   111   6f    o
        160   112   70    p
        161   113   71    q
        162   114   72    r
        163   115   73    s
        164   116   74    t
        165   117   75    u
        166   118   76    v
        167   119   77    w
        170   120   78    x
        171   121   79    y
        172   122   7a    z
 
    *********************************************************************/
   printf("\tOct   Dec   Hex   Char\n");
   printf("\t----------------------\n");
   char letter;
   for (letter = 'a'; letter <= 'z'; letter = letter + 1)
   {
      printf("\t%o   %-3d   %-3x   %c\n", letter, letter, letter, letter);
   }
   printf("\n");
   /*********************************************************************
    *************** Now play with pointers to finish up *****************
    *********************************************************************/
 
   int *p1;
   int *p2;
 
   p1 = (int *) malloc(sizeof(int));
   *p1 = 42;
   p2 = p1;
   printf("*p1 == %d\n", *p1);
   printf("*p2 == %d\n", *p2);
 
   *p2 = 53;
   printf("*p1 == %d\n", *p1);
   printf("*p2 == %d\n", *p2);
 
   p1 = (int *) malloc(sizeof(int));
   *p1 = 88;
   printf("*p1 == %d\n", *p1);
   printf("*p2 == %d\n", *p2);
 
   printf("Hope you got the point of this example!\n");
 
   free (p1);
   free (p2);

   return 0;
}

