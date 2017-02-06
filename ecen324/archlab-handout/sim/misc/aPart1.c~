/* 
 * Architecture Lab: Part A 
 * 
 * High level specs for the functions that the students will rewrite
 * in Y86 assembly language
 */

/* $begin examples */
/* linked list element */
typedef struct ELE {
    int val;
    struct ELE *next;
} *list_ptr;

/* sum_list - Sum the elements of a linked list */
int sum_list(list_ptr ls)
{
    int val = 0;
    while (ls) {
	val += ls->val;
	ls = ls->next;
    }
    return val;
}
/* $end examples */
int main()
{
   list_ptr sum;
   sum_list(sum);
   return 0;
}
