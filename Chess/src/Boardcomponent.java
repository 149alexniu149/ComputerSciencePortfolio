
//import color, graphics, Jcomponent
import java.awt.Color;
import java.awt.Graphics;
import java.io.IOException;

import javax.swing.JComponent;
public class Boardcomponent extends JComponent 
{
	//create a new color called background
	Color background = new Color(177,113,24);
	//create a new color for the squares
	Color squares = new Color(233,174,95);
	//create a variable of type Chesswindow
	Chesswindow cw;
	
	//creates a new variable type Boardcomponent which will be used everywhere else because fuck it, why not
	Boardcomponent(Chesswindow cw)
	{
		//uses the chesswindow fed to boardcomponent to draw on
		this.cw = cw;
	}
	public void paintComponent(Graphics g)
	{
		//sets the color to the background color
		g.setColor(background);
		//draws a rectangle of the size and width set in chesswindow
		g.fillRect(0, 0, cw.WINDOWWIDTH, cw.WINDOWHEIGHT);
		g.drawRect(0, 0, cw.WINDOWWIDTH, cw.WINDOWHEIGHT);
		//set the color to the color of the squares
		g.setColor(squares);
		//for each row
		for(int i = 0; i< 8; i++)
		{
			
				//if the row is even
				if(i%2 == 0)
				{
					//iterate through the columns
					for(int j = 0; j < 8; j++)
					{
						//and if the column is even
						if(j%2 == 0)
						{
							//draw a square
							g.fillRect(j*50,i*50,50,50);
						}
					}
				}
				//if the row is odd
				else
				{
					//iterate through the columns
					for(int j = 0; j < 8; j++)
					{
						//and if the column is odd
						if(j%2 != 0)
						{
							//draw a square
							g.fillRect(j*50,i*50,50,50);
						}
					}
				}
				
		}
		//for each row
		for(int i = 0; i < 8; i++)
		{
			//and each column in that row
			for(int j=0; j<8; j++)
			{
				//if the column has a piece in it
				if (cw.p[i][j] != null)
				{
					//draw whatever is in that piece
					cw.p[i][j].draw(g, j, i);
				}
				
			}
		}
		
		
	}

}
