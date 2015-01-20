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


public class King extends Piece
{
	

	public King(boolean isblack)
	{
		this.isblack = isblack;
		if(isblack)
			img =new ImageIcon("bking.gif");
		else
			img =new ImageIcon("wking.gif");
		
	}
	@Override
	public boolean canMove(int posxi, int posxf, int posyi, int posyf) 
	{
		System.out.println("King canmove activated");
		//the king can only move one space in the x and y direction during a move
		if(Math.abs(posxf - posxi) > 1 || Math.abs(posyf-posyi) > 1)
		{
			System.out.println("King canMove returned false");
			return false;
		}
		
		return true;
	}
	
}
