import java.awt.Color;
import java.awt.Graphics;
import java.awt.Graphics2D;
import java.awt.Image;
import java.awt.Toolkit;
import java.awt.image.BufferedImage;
import java.awt.image.ImageObserver;
import java.io.File;
import java.io.IOException;

import javax.imageio.ImageIO;
import javax.swing.ImageIcon;


public class Pawn extends Piece
{	// create a counter, just wait, you'll see
	int counter = 0;
	//constructor
	public Pawn(boolean isblack, Chesswindow cw)
	{
		this.cw = cw;
		this.isblack = isblack;
		if(isblack)
			img =new ImageIcon("bpawn.gif");
		else
			img =new ImageIcon("wpawn.gif");
	}
	@Override
	public boolean canMove(int posxi, int posxf, int posyi, int posyf)
	{	//make sure the pawn doesnt jump over any pieces
		for(int i = posyi+1; i < posyf; i++)
		{
			if(cw.p[i][posxi] != null)
			{
				return false;
			}
		}
		for(int i = posyi-1; i > posyf; i--)
		{
			if(cw.p[i][posxi] != null)
			{
				return false;
			}
		}
		
		if(isblack && posyf-posyi>0 && posxf-posxi == 0 && Math.abs(posyf-posyi) <=2 && Math.abs(posyf-posyi) >=1 && counter == 0 && cw.p[posyf][posxf] == null)
		{
			System.out.println(posyf);
			System.out.println(posxf);
			System.out.println(cw.p[0][0]);
			
			System.out.println("Valid pawn move");
			counter++;
			return true;
			
		}
		else if( isblack && posyf-posyi>0 && posxf-posxi == 0 && Math.abs(posyf-posyi) == 1 && counter > 0 && cw.p[posyf][posxf] == null)
		{
			return true;
		}
		else if( isblack && posyf-posyi>0 && Math.abs(posxf-posxi) == 1 && Math.abs(posyf-posyi) == 1 && cw.p[posyf][posxf] != null && cw.p[posyf][posxf].isblack == false)
		{
			return true;
		}
		//white pawn
		if(!isblack && posyf-posyi<0 && posxf-posxi == 0 && Math.abs(posyf-posyi) <=2 && Math.abs(posyf-posyi) >=1 && counter == 0 && cw.p[posyf][posxf] == null)
		{
			System.out.println(posyf);
			System.out.println(posxf);
			System.out.println(cw.p[0][0]);
			
			System.out.println("Valid pawn move");
			counter++;
			return true;
			
		}
		else if( !isblack && posyf-posyi<0 && posxf-posxi == 0 && Math.abs(posyf-posyi) == 1 && counter > 0 && cw.p[posyf][posxf] == null)
		{
			return true;
		}
		else if( !isblack && posyf-posyi<0 && Math.abs(posxf-posxi) == 1 && Math.abs(posyf-posyi) == 1 && cw.p[posyf][posxf] != null && cw.p[posyf][posxf].isblack == true)
		{
			return true;
		}
		return false;
	}
}
