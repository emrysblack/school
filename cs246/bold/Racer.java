import java.io.File;

class fileNinja
   extends Thread
{
   private int mFileNumber;   
   private boolean create;
   public fileNinja()
   {
      mFileNumber = 0;
      create = true;
   }
      public fileNinja(boolean c)
   {
      mFileNumber = 0;
      create = c;
   }
   
   public File newFileN(int number)
   {
      return new File(String.format("file.%05d", number));
   }

   public void run()
   {
      try
      {
         if (!create)
            Thread.sleep(2000);
         while (true)
         {
            if (create)
               newFileN(mFileNumber).createNewFile();
            else
               newFileN(mFileNumber).delete();
            mFileNumber++;
            Thread.sleep(500);
         }
      }
      catch (Exception e)
      {
      }
   }   
}

public class Racer
{
   // need to use OutputtingFilerToucher class for display

   // shutdown cleanup
   public static void cleanup()
   {
      Runtime.getRuntime().addShutdownHook(
         new Thread()
         {
            public void run()
            {
               System.out.println("cleaned up");
            }
         });
   }
      public static void main(String[] args)
   {
      new fileNinja(true).start();    
      new fileNinja(false).start();
      cleanup();
   }
}
