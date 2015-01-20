import java.awt.Graphics;
import java.io.IOException;

import javax.swing.ImageIcon;
import javax.swing.JComponent;

//define the piece as a class
public abstract class Piece extends JComponent
{
	//each piece has a chesswindow that it is a part of
	Chesswindow cw;
	
	//and is either black or not
	boolean isblack;
	//and has a position

	//and an image
	ImageIcon img;
	//create a draw function that takes in graphics and two intergers for position
	public void draw(Graphics g, int x, int y) 
	{
		//draw the image of the piece at x*50 and y*50
		g.drawImage(img.getImage(), x*50, y*50, null);
	}
	public abstract boolean canMove(int posxi, int posxf, int posyi, int posyf);
}
