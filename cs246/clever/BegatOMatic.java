import java.text.MessageFormat; // DO NOT REMOVE!

import java.util.StringTokenizer; // DO NOT REMOVE!

// DO NOT ADD any other import statements, or use anything from any other package!!

/**
 * A highly special class with a narrowly focused purpose.
 */
public class BegatOMatic
   implements Runnable
{
   /**
    * Default value for the starting verse;
    */
   private static final int DEFAULT_STARTVERSE = 9;

   /**
    * Default value for the field separator.
    */
   private static final String DEFAULT_FIELD_SEPARATOR = ",";

   /**
    * Default value for the record separator.
    */
   private static final String DEFAULT_RECORD_SEPARATOR = ":";

   /**
    * Default value for the message format.
    */
   private static MessageFormat cFormat = new MessageFormat(
      "{0}. And {1} lived {2} years, and begat {3}:\n" +
      "{4}. And {1} lived after he begat {3} {5} years, and begat sons and daughters:\n" +
      "{6}. And all the days of {1} were {7} years: and he died.");

   /**
    * Data lookup key.
    */
   private static final String DKEY = System.getProperty("data");

   /**
    * Main starts by asserting that the args array is empty.
    *
    * Enable assertions by using the -ea option with the java interpreter, e.g.
    *
    * java -ea BegatOMatic
    *
    * @param args the command-line arguments.
    */
   public static void main(String[] args)
   {
      assert args.length == 0 : "No args allowed!";
      new BegatOMatic().run();// add one line of code here (and several below!)
   }

   // provided here just so this stub code will compile -- you must flesh it out
   public void run()
   {
      // read in data in 3 records
      StringTokenizer st = new StringTokenizer(DKEY, DEFAULT_RECORD_SEPARATOR);
      String [] test = new String [8];
 
      // split data records into fields and display message
      StringTokenizer st1;
      for (int i = DEFAULT_STARTVERSE; st.hasMoreTokens(); i = i + 3)
      {
         // get next record data
         st1 = new StringTokenizer(st.nextToken(), DEFAULT_FIELD_SEPARATOR);

         // set start verse
         test[0] = Integer.toString(i);

         // 3 tokens
         for (int j = 1; j < 4; j++)
         {
            test[j] = st1.nextToken();
         }

         // verse
         test[4] = Integer.toString(i + 1);

         //token
         test[5] = st1.nextToken();

         //verse
         test[6] = Integer.toString(i + 2);

         //token
         test[7] = st1.nextToken();

         // display current 3 verse record
         System.out.println(cFormat.format(test));
      }
   }
}
