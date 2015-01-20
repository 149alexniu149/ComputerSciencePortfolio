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


public class Bishop extends Piece
{
	
	//build the ishop and define its color and chesswindow
	public Bishop(boolean isblack, Chesswindow cw)
	{
		this.isblack = isblack;
		this.cw = cw;
		if(isblack)
			img =new ImageIcon("bbishop.gif");
		else
			img =new ImageIcon("wbishop.gif");
		
	}
	public boolean canMove(int posxi, int posxf, int posyi, int posyf) 
	{
		System.out.println("bishop canmove activated");
		System.out.println(posxi + " " + posxf + " " + posyi + " " + posyf);
		if(Math.abs(posxf - posxi) != Math.abs(posyf-posyi))
		{
			return false;
		}
		for(int i = 1; i < Math.abs(posxf-posxi); i++ )
		{ // check each space the bishop moves over and make sure it hasnt jumped anyone
			if(cw.p[posyf>posyi?posyi+i:posyi-i][posxf>posxi?posxi+i:posxi-i] != null)
				return false;
		}
		//the bishop can only move in diagonals
		
		System.out.println("bishop canMove returned false");
		return true;
	}

}