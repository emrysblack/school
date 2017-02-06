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
int rsum_list(list_ptr ls)
{
    if (!ls)
	return 0;
    else {
	int val = ls->val;
	int rest = rsum_list(ls->next);
	return val + rest;
    }
}
/* $end examples */
int main()
{
   list_ptr sum;
   rsum_list(sum);
   return 0;
}
