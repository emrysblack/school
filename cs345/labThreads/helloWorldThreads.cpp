
#include <iostream>
#include <pthread.h>
using namespace std;

void *print_message_function( void *ptr ); 
  
int main()
{
   pthread_t thread1;
   pthread_t thread2;

   char message1[] = "hello,";
   char message2[] = "world!";
   
   pthread_create( &thread1, NULL, print_message_function, (void*) message1);
   pthread_create( &thread2, NULL, print_message_function, (void*) message2);

   /* now wait for the thread to exit */
   pthread_join(thread1,NULL);
   pthread_join(thread2,NULL);

   cout << endl;

   return 0;
}
  
void *print_message_function( void *ptr )
{
   char *message;
   message = (char *) ptr;
   cout << message << " ";

   pthread_exit(0);
}

