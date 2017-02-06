// Brady Field
// Fellow Conspiritors - Jeff Bickmore, Emmanuel Jones, Kevin Hardy
import java.io.RandomAccessFile;

public class SplitDBF
{
   public static byte[] getDataAndOffsets(String filename, int[] offsets)
      throws Exception
   {
      long size = 0;

      RandomAccessFile file = new RandomAccessFile(filename, "r");
      size = file.length();
      
      byte[] buffer = new byte[(int)size]; // size of total file
      file.readFully(buffer);

      // scan for headers
      int j = 0; // count
      int k = 0; // offset index

      for (int i = 0; i < size; i++)
      {
         if (buffer[i] == 0)
         {
            j++;
         }
         else
         {
            j = 0;
         }
         if (j == 16)
         {
            offsets[k] = i - 26;
            k++;
         }
      }
      offsets[k] = (int)size - 1; //protect from out of bounds
      return buffer;
   }

   // DON'T TOUCH ANYTHING below here!

   private static String[] cFileNames =
   {
      "acctno", "check", "claimno", "dicode", "policy", "recall", "trcode",
   };

   public static String filename(int i)
   {
      return cFileNames[i] + ".dbf";
   }

   public static void main(String[] args)
      throws Exception
   {
      String filename = ((args.length > 0) ? args[0] : "/home/cs246/files/backup");

      int[] offsets = new int[cFileNames.length + 1];
      byte[] buffer = getDataAndOffsets(filename, offsets);

      for (int i = 0; i < offsets.length - 1; i++)
      {
         int offset = offsets[i];
         int len = offsets[i + 1] - offset;
         RandomAccessFile newfile = new RandomAccessFile(filename(i), "rw");
         newfile.write(buffer, offset, len);
         newfile.write((byte) 26); // write the ^Z terminator
         newfile.close();
      }
   }
}
