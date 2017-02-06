// Brady Field
// Fellow Conspiritors - Jordan Balls, Devin Lacrosse, Sam Graham,
//                       Davis McClellan
// File Toucher Lab Exercise

import java.io.File;

public class FileToucher
{
   public static void main(String[] args)
   {
// get current time (now) in milliseconds
      long now = System.currentTimeMillis();
      try {
// use command line args for filenames
         for (int i = 0; i < args.length; i++)
         {
            File file = new File(args[i]);

            if (!file.setLastModified(now) )
            {
               // try to create file
               
               if(!file.exists())
               {
                  boolean create = file.createNewFile();
               }

               // file exists, but was not able to be Modified
               
               else
               {
                  System.out.println("Failed to touch " + file);
               }            
            }            
         }
      }
      catch(Exception e)
      {
         System.out.println("Exception thrown: " + e.getMessage());
      }
   }
}

