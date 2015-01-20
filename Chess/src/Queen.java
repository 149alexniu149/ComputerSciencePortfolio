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


public class Queen extends Piece
{
	

	public Queen(boolean isblack, Chesswindow cw)
	{
		this.isblack = isblack;
		this.cw = cw;
		if(isblack)
			img =new ImageIcon("bqueen.gif");
		else
			img =new ImageIcon("wqueen.gif");
		
	}

	@Override
	public boolean canMove(int posxi, int posxf, int posyi, int posyf) 
	{
		System.out.println("Queen clicked");
		if(Math.abs(posxf-posxi) == Math.abs(posyf-posyi))
		{
			for(int i = 1; i < Math.abs(posxf-posxi); i++ )
			{
				if(cw.p[posyf>posyi?posyi+i:posyi-i][posxf>posxi?posxi+i:posxi-i] != null)
					return false;
			}
		}
		else if(posxi == posxf || posyi == posyf)
		{
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
		}
		else
		{
			return false;
		}
		if(Math.abs(posxf - posxi) >0 || Math.abs(posyf-posyi) > 0)
		{
			System.out.println("queen canMove returned true");
			return true;
		}
		return false;
	}
	
}

