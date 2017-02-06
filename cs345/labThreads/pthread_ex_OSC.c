
#include <stdio.h>
#include <pthread.h>

int sum = 0;			/* this data is shared by the thread(s) */
void runner(void *param);	/* the thread */

main(int argc, char *argv[])
{
   //check for a parameter, if there is none you'll seg fault


   pthread_t tid;		/* declare tid to be the thread identifier */
   pthread_attr_t attr;		/* declare attr to hold thread attributes */

   /* get the default attributes */
   pthread_attr_init(&attr);

   /* create the thread */
   pthread_create(&tid, &attr, (void*) &runner, argv[1]);

   /* now wait for the thread to exit */
   pthread_join(tid,NULL);
   printf("sum = %d\n",sum);
}

void runner(void *param) 
{
   int upper = atoi(param);
   int i;
   sum = 0;

   for (i = 1; i <= upper; i++)
      sum += i;

   pthread_exit(0);
}

