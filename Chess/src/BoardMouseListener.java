import java.awt.event.MouseEvent;
import java.awt.event.MouseListener;
import java.util.Random;


public class BoardMouseListener implements MouseListener
{
	//the mouse listener will need initial and final positions
	int posxi;
	int posyi;
	int posxf;
	int posyf;
	//and a chesswindow
	Chesswindow cw;
	BoardMouseListener(Chesswindow cw)
	{
		//uses the chesswindow fed to boardcomponent to draw on
		this.cw = cw;
	}
	@Override
	public void mouseClicked(MouseEvent e) {
		// TODO Auto-generated method stub
		
	}

	@Override
	public void mouseEntered(MouseEvent e) {
		// TODO Auto-generated method stub
		
	}

	@Override
	public void mouseExited(MouseEvent e) {
		// TODO Auto-generated method stub
		
	}

	@Override
	public void mousePressed(MouseEvent e)
	{
		//collect the coordiates the mouse was pressed at and devide them by 50 to get a position on the array
		System.out.println("pressed");
		posxi = e.getX()/50;
		posyi = e.getY()/50;
		
	}

	@Override
	public void mouseReleased(MouseEvent e)
	{
		//collect ehe pixels the mouse was released at and divide them by 50 to get a position in the array
		System.out.println("released");
		posxf = e.getX()/50;
		posyf = e.getY()/50;
		//if the final position in the array is not null and both pieces are of the same color
		/*if( )
		{
			//DO NOTHING
			
		}*/
		//if the move is invalid
		if (cw.p[posyf][posxf] != null && cw.p[posyf][posxf].isblack == cw.p[posyi][posxi].isblack || cw.p[posyi][posxi].canMove(posxi, posxf, posyi, posyf) == false || cw.p[posyi][posxi]==cw.p[posyf][posxf])
		{
			//DO NOTHING
			System.out.println("canMove returned false");
		}
		//otherwise, if the move is valid
		else 
		{
			System.out.println("canMove True");
			//set the final position equal to the initial position
			cw.p[posyf][posxf] = cw.p[posyi][posxi];
			//and the initial position to null
			cw.p[posyi][posxi] = null;
			Random rand = new Random();
			int counter = 0;
			while(true)
			{
				//selects a random piece and moves it to a random valid space
				System.out.println("Searching...");
				int posxir = rand.nextInt(8);
				int posxfr = rand.nextInt(8);
				int posyir = rand.nextInt(8);
				int posyfr = rand.nextInt(8);
				if(cw.p[posyir][posxir] != null && cw.p[posyir][posxir].isblack  && cw.p[posyir][posxir].canMove(posxir, posxfr, posyir, posyfr) && (cw.p[posyfr][posxfr] == null || cw.p[posyfr][posxfr].isblack == false) )
				{
					System.out.println("Move found!");
					cw.p[posyfr][posxfr] = cw.p[posyir][posxir];
					cw.p[posyir][posxir] = null;
					cw.bc.repaint();
					break;
				}
				counter++;
				if(counter >= 10000)
				{
					break;
				}
				
				
			}
		}
		//repaints it all
		cw.bc.repaint();
		System.out.println(posxi);
		System.out.println(posyi);
		System.out.println(posxf);
		System.out.println(posyf);
		
	}
	

}
