import javax.swing.*;

public class GiantButton
{
   public static void main (String[] args)
   {
      JFrame frame = new JFrame(); // JFrame is a window
      JButton button = new JButton("Giant Button"); // create button

      // stop running program if window closes
      frame.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);

      // put constucted button in the window
      frame.getContentPane().add(button);

      // set window size
      frame.setSize(300, 300);

      // make window visible when program starts
      frame.setVisible(true);
   }
}
