import javax.swing.*;
import java.awt.*;
import java.awt.event.*;

public class SimpleGui3C implements ActionListener
{
   JFrame frame;

   public static void main(String[] args)
   {
      // class has member variables, so we need to create an instance
      SimpleGui3C gui = new SimpleGui3C();

      // start the program using the class go behavior
      gui.go();
   }
   public void go()
   {
      // create a frame
      frame = new JFrame();

      // exit when window closes
      frame.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);

      // create button
      JButton button = new JButton("Swap Color");
      // allow button to react
      button.addActionListener(this);

      // creates an object to draw, in this case - a circle
      MyDrawPanel drawPanel = new MyDrawPanel();

      // put button on bottom of window
      frame.getContentPane().add(BorderLayout.SOUTH, button);

      // put circle in middle frame of window
      frame.getContentPane().add(BorderLayout.CENTER, drawPanel);

      // set window size
      frame.setSize(300, 300);

      //make window visible
      frame.setVisible(true);
   }

   public void actionPerformed(ActionEvent event)
   {
      // when button reacts to event, redraw window and everything in it
      frame.repaint();
   }
}

class MyDrawPanel extends JPanel
{
   public void paintComponent(Graphics g)
   {
      // typecast into 2D for extra options
      Graphics2D g2d = (Graphics2D) g;

      // generate a random color
      int red = (int) (Math.random() * 256);
      int green = (int) (Math.random() * 256);
      int blue = (int) (Math.random() * 256);

      // create color from random RGB values
      Color color = new Color(red, green, blue);

      // prep color
      g2d.setPaint(color);

      // change the circle to random generated color
      g2d.fillOval(70,70,100,100);
   }
}