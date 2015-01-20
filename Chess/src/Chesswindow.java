import java.awt.event.MouseEvent;
import java.awt.event.MouseListener;

import javax.swing.JFrame;


public class Chesswindow 
{
	//define the size of the window that will be made
	static final int WINDOWWIDTH = 400;
	static final int WINDOWHEIGHT = 400;
	//create a two dimensonal array of pieces (empty)
	Piece[][] p;
	//create a variable of type boardcomponent which is creates in the associated file that can be added to the program
	Boardcomponent bc;
	BoardMouseListener bml;
	public Chesswindow()
	{
		//create the window, name it chess
		JFrame chesswindow = new JFrame("CHESSSSS!!!!");
		//set the size of the window
		chesswindow.setSize(WINDOWWIDTH+100, WINDOWHEIGHT+100);
		// give bc a value of boardcomponent taking in Chesswindow as a param
		bc = new Boardcomponent(this);
		//create the mouse listener
		bml = new BoardMouseListener(this);
		//set the length of the empty two dimensional array to 8x8
		p = new Piece[8][8];
		//iterate through each row
		for(int i=0; i<8; i++)
		{
			//if the row == 1
			if(i == 1)
			{
				//iterate through each column
				for(int j=0; j<8; j++)
				{
					//create a new black pawn, the entire row will be filled
					p[i][j] = new Pawn(true, this);
				}
			}
			if(i == 6)
			{
				//iterate through each column
				for(int j=0; j<8; j++)
				{
					//create a new white pawn, the entire row will be filled
					p[i][j] = new Pawn(false, this);
				}
			}
			//if we are on the first row
			if(i == 0)
			{
				//iterate through each column and make black back pieces
				for(int j=0; j<8; j++)
				{
					if(j==2 || j==5)
						p[i][j] = new Bishop(true, this);
					if(j==1 || j==6)
						p[i][j] = new Knight(true);
					if(j==0 || j==7)
						p[i][j] = new Rook(true, this);
					if(j==3)
						p[i][j] = new Queen(true, this);
					if(j==4)
						p[i][j] = new King(true);
				}
			}
			//if we are on the last row
			if(i == 7)
			{
				//iterate through each column
				for(int j=0; j<8; j++)
				{
					//iterate through each column and make a white back piece
					if(j==2 || j==5)
						p[i][j] = new Bishop(false, this);
					if(j==1 || j==6)
						p[i][j] = new Knight(false);
					if(j==0 || j==7)
						p[i][j] = new Rook(false, this);
					if(j==4)
						p[i][j] = new Queen(false, this);
					if(j==3)
						p[i][j] = new King(false);
				}
			}
			
		}
		//add the boardcomponent to the window
		chesswindow.add(bc);
		//add a mouselistener bml to the boardcomponent
		bc.addMouseListener(bml);
		//make the window visible
		chesswindow.setVisible(true);
		//close when x is pressed
		chesswindow.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
	}
	
	public static void main(String[] args)
	{
		//run the program
		new Chesswindow();
	}



}
