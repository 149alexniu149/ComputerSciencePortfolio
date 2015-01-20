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


public class Rook extends Piece
{
	

	public Rook(boolean isblack, Chesswindow cw)
	{
		this.isblack = isblack;
		this.cw = cw;
		if(isblack)
			img =new ImageIcon("brook.gif");
		else
			img =new ImageIcon("wrook.gif");
		
	}

	public boolean canMove(int posxi, int posxf, int posyi, int posyf) 
	{
		System.out.println("rook canmove activated");
		System.out.println(posxi + " "  + posxf + " " + posyi+ " " + posyf);
		for(int i = posxi+1; i < posxf; i++)
		{
			if(cw.p[posyi][i] != null)
			{
				return false;
			}
		}
		for(int i = posxi-1; i > posxf; i--)
		{
			if(cw.p[posyi][i] != null)
			{
				return false;
			}
		}
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
		
		//the king can only move one space in the x and y direction during a move
		if(Math.abs(posxf - posxi) > 0 && Math.abs(posyf-posyi) == 0 || Math.abs(posyf - posyi) > 0 && Math.abs(posxf-posxi) == 0)
		{
			
			System.out.println("rook canMove returned true");
			return true;
		}
		
		return false;
	}


}