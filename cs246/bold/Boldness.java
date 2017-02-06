/*
 Will be boldness exploration
 */
import javax.swing.*;
import java.awt.*;
import java.awt.event.*;

public class Boldness implements ActionListener
{
   JFrame frame;
   public static void main(String[] args)
   {
      Boldness gui = new Boldness();
      gui.go();
   }
   public void go()
   {
      // create a frame
      frame = new JFrame();

      // exit when window closes
      frame.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);

      // create button
      JButton button = new JButton("Start");
      // allow button to react
      button.addActionListener(this);

      // create another button
      JButton button1 = new JButton("Stop");
      //allow button to react
      button1.addActionListener(this);

      JButton button2 = new JButton("Load");
      button2.addActionListener(this);
 

      // put button on bottom of window
      frame.getContentPane().add(BorderLayout.SOUTH, button);

 

      // put second button in right side of window
      frame.getContentPane().add(BorderLayout.EAST, button1);
      frame.getContentPane().add(BorderLayout.NORTH, button2);
      // set window size
      frame.setSize(600, 600);

      //make window visible
      frame.setVisible(true);
   }

   public void actionPerformed(ActionEvent event)
   {
      // when button reacts to event, redraw window and everything in it
   }
}