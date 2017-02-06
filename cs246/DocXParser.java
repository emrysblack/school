import java.io.InputStream;
import java.util.ArrayList;
import java.util.List;

import java.util.zip.ZipEntry;
import java.util.zip.ZipInputStream;

import javax.xml.parsers.DocumentBuilder;
import javax.xml.parsers.DocumentBuilderFactory;

import org.w3c.dom.Document;
/**
 * DocX file parser and text extractor.
 */
public class DocXParser
{
   private List<String> mText;

   private Document mDocument;

   public DocXParser(Document pDoc)
   {
      mText = new ArrayList<String>();
      mDocument = pDoc;
   }
   
   public void parseDocument()
   {
      try
      {
         // NodeList nodeList = mDocument.getElementsByTagName("w:t");
         
         // for (int i = 0; i < nodeList.getLength(); i++)
         {
            // TODO: do something with nodeList.item(i) in one line here:
            
         }
      }
      catch (Exception e)
      {
      }
   }
   public void display()
   {
      for (String text : mText)
      {
         System.out.print(text);
         System.out.print(" ");
      }
      System.out.println();
   }
   public static void main(String[] args)
   {
      //DocXParser a = new DocXParser();
      //a.display();
   }
}