//CSC432 FALL 2014, Michael Black
//2D BALL MOVEMENT DEMO
//YOU CAN USE THIS AS A BASIS FOR YOUR PROJECT 1
//
//THIS HAS BALLS MOVING AROUND IN 2D AND BOUNCING OFF WALLS.  COLLISIONS ARE NOT YET DETECTED.
//
//A MOUSE LISTENER IS INCLUDED.  ON DOUBLECLICK, A NEW BALL APPEARS.
//
//When you see the words "TODO", you should add code there

//necessary libraries
#include <iostream>
#include <QApplication>
#include <math.h>
#include <QMouseEvent>
#include <QTime>
//your class definitions
#include "ball.h"

//constants.  these numbers can be adjusted
const int MAXBALLS=1000;	//more than MAXBALLS balls will cause a segmentation fault
const int BOUND=500;		//size of the screen
const int MARGIN=50;		//balls are created at least this far from the edge
const int RADIUS=3;		//all balls start with this radius
const float RESTITUTION=1.0;	//energy lost in a collision: from 0.0 (inelastic: all is lost) to 1.0 (elastic: nothing is lost)
const float GRAVITY=9.8;	//not currently used, but you can add GRAVITY * DT to a ball's y velocity in move() to create a gravity effect

const float DT=0.00125;		//smaller = slower simulation = more accurate
const int TIMEUNIT=1000/66;	//timer update function runs 66 times per second
const int ENERGY = 500;
const int Bound=50;

//globals
int BallCount=50;
const int WallCount=9;//starting with 10 balls.  you can change this.
Ball* balls[MAXBALLS];		//array of ball pointers
Wall* walls[WallCount];
QGraphicsView* view;
//ball constructor
//makes a ball at a random position, with a random velocity, and a random mass
Ball::Ball()
{
//	setPos(0,0);
    type = qrand()%2;
    if (type ==0 )
    {
      setPos(qrand()%20+310,qrand()%210+160);
       color.setBlue(255);
    }
    else if(type == 1 )
    {
       setPos(qrand()%20+170,qrand()%210+160);
       color.setRed(255);
    }

//	position=new Vector(qrand()%(500-Bound*2)+Bound,qrand()%(500-Bound*2)+Bound);
    position=new Vector(x(),y());
    mass=5;

    float speed=qrand()%5+10;
    float angle=(qrand()%360)*2*3.14/360.0;
    velocity=new Vector(speed*cos(angle),speed*sin(angle));

    radius=RADIUS;

}


//where to update screen relative to a ball's center position
//you shouldn't need to change this
QRectF Ball::boundingRect() const
{
	return QRectF(-radius,-radius,radius*2,radius*2);
}

Wall::Wall(float p1, float p2, float p3, bool isV)
{
    setPos(0,0);
    point1=p1; point2=p2; point3=p3; isVertical=isV;
//	if(isVertical)
//		setPos((int)p3,(int)(p1+p2)/2);
//	else
//		setPos((int)(p1+p2)/2,(int)p3);
}

QRectF Wall::boundingRect() const
{
    if(isVertical)
//		return QRectF(-1,-(point2-point1)/2,1,(point2-point1)/2);
        return QRectF(point3,point1,point3,point2);
    else
//		return QRectF(-(point2-point1)/2,-1,(point2-point1)/2,1);
        return QRectF(point1,point3,point2,point3);
}

//called by qt system to paint the ball when it moves.  you shouldn't need to change this
void Ball::paint(QPainter *painter, const QStyleOptionGraphicsItem *, QWidget *)
{
	painter->setBrush(color);
	painter->drawEllipse(-radius,-radius,radius*2,radius*2);
}

void Wall::paint(QPainter *painter, const QStyleOptionGraphicsItem *, QWidget *)
{
    QColor color;
    color.setBlue(0); color.setRed(0); color.setGreen(0);
    painter->setBrush(color);
    if(isVertical)
//		painter->drawLine(0,-(point2-point1)/2,0,(point2-point1)/2);
        painter->drawLine(point3,point1,point3,point2);
    else
//		painter->drawLine(-(point2-point1)/2,0,(point2-point1)/2,0);
        painter->drawLine(point1,point3,point2,point3);
}

//called when a collision happens.  your code will go in here
void handleCollision(Ball* ball1, Ball* ball2)
{
	//cause combustion if balls are of diferent types. Color is to make sure the pistons never combust
    if (ball1->radius == ball2->radius && ball1->type != ball2->type && ball1->color != ball2->color)
    {
        std::cout << "Collision happened" << std::endl;
        Vector* Collision = ball1->position->sub(ball2->position);
        float distance = sqrt(Collision->lengthsquared());
        float adjust = (ball1->radius+ball2->radius-distance)/distance;
        Vector* XAdjust = Collision->mul(adjust);
        Vector* XAdjust1 = XAdjust->mul((1/ball1->mass)/((1/ball1->mass)+(1/ball2->mass)));
        Vector* XAdjust2 = XAdjust->mul((1/ball2->mass)/((1/ball2->mass)+(1/ball1->mass)));
        ball1->position = ball1->position->add(XAdjust1);
        ball2->position = ball2->position->sub(XAdjust2);
        std::cout<< "Ball created" << std::endl;
        //ball2->position = tempx1pos->sub(tempx2pos)->div(2);
        ball2->mass = ball1->mass+ball2->mass;
        ball1->mass = 0;
        ball2->color.black();
        ball2->velocity = ball1->velocity->add(ball2->velocity);

		//create collision vector
        Vector* XCollision = Collision->normalize();
        Vector* VDiff = ball1->velocity->sub(ball2->velocity);
		//adjust ball velocity and direction
        float VAdjust = VDiff->dot(XCollision);
        float vadjust1 = (1+.7)*VAdjust*((1/ball1->mass)/((1/ball1->mass)+(1/ball2->mass)));
        float vadjust2 = (1+.7)*VAdjust*((1/ball2->mass)/((1/ball2->mass)+(1/ball1->mass)));
        Vector* VAdd1 = XCollision->mul(vadjust1);
        Vector* VAdd2 = XCollision->mul(vadjust2);
        Vector* tempx1vel= ball1->velocity;
        Vector* tempx2vel = ball2->velocity;
        ball1->velocity = ball1->velocity->sub(VAdd1);
        ball2->velocity = ball2->velocity->add(VAdd2);
		//combine the balls
        ball2->radius = ball2->radius+1;
		//change the color to exhaust color
        ball2->color = 3;
        std::cout << ball1->position << std::endl;
        std::cout << ball2->position << std::endl;
        for (int i = 0; i<BallCount; i++)
        {

            if (balls[i]==ball2, balls[0], balls[1], balls[2])
            {
                i++;

            }
			//model combustion when hydrogen and oxygen collide by speeding up balls in the system
            else if (balls[i]->velocity->x != 0 && balls[i]->mass > 0 && balls[i] != balls[0])
            {
                float itheta = balls[i]->velocity->theta();
                float veng =sqrt((ENERGY*balls[i]->mass)/ball2->position->dist(balls[i]->position));
                balls[i]->velocity->x=(balls[i]->velocity->x + veng*cos(itheta));
                balls[i]->velocity->y=(balls[i]->velocity->y + veng*sin(itheta));


            }
        }
		//garbage collection
        delete Collision, distance, adjust, XAdjust, XAdjust1, XAdjust2, XCollision, VDiff, VAdjust, vadjust1, vadjust2, VAdd1, VAdd2;
    }
    else
    {
		// make balls bounce off one another without combustion if they are the same type and color.
        std::cout << "Collision happened" << std::endl;
		//create a collision vector
        Vector* Collision = ball1->position->sub(ball2->position);
		//ensure balls don't overlap
        float distance = sqrt(Collision->lengthsquared());
        float adjust = (ball1->radius+ball2->radius-distance)/distance;
        Vector* XAdjust = Collision->mul(adjust);
        Vector* XAdjust1 = XAdjust->mul((1/ball1->mass)/((1/ball1->mass)+(1/ball2->mass)));
        Vector* XAdjust2 = XAdjust->mul((1/ball2->mass)/((1/ball2->mass)+(1/ball1->mass)));
        ball1->position = ball1->position->add(XAdjust1);
        ball2->position = ball2->position->sub(XAdjust2);
        std::cout<< "Ball created" << std::endl;
		//change the velocities of the balls and make them deflect at angles based on how they collided
        Vector* XCollision = Collision->normalize();
        Vector* VDiff = ball1->velocity->sub(ball2->velocity);
        float VAdjust = VDiff->dot(XCollision);
        float vadjust1 = (1+.7)*VAdjust*((1/ball1->mass)/((1/ball1->mass)+(1/ball2->mass)));
        float vadjust2 = (1+.7)*VAdjust*((1/ball2->mass)/((1/ball2->mass)+(1/ball1->mass)));
        Vector* VAdd1 = XCollision->mul(vadjust1);
        Vector* VAdd2 = XCollision->mul(vadjust2);
        //assign new velocities
		Vector* tempx1vel= ball1->velocity;
        Vector* tempx2vel = ball2->velocity;
        ball1->velocity = ball1->velocity->sub(VAdd1);
        ball2->velocity = ball2->velocity->add(VAdd2);
        std::cout << ball1->position << std::endl;
        std::cout << ball2->position << std::endl;
		//garbage collection
        delete Collision, distance, adjust, XAdjust, XAdjust1, XAdjust2, XCollision, VDiff, VAdjust, vadjust1, vadjust2, VAdd1, VAdd2;
      }
        
}

//move a ball one timestep foreward - by Dr. Black
void Ball::move()
{
	position->x+=velocity->x*DT;
    position->y+=velocity->y*DT;
    balls[0]->velocity->y = balls[0]->velocity->y + (GRAVITY*DT);
    balls[1]->velocity->y = balls[1]->velocity->y + (GRAVITY*DT);
    balls[2]->velocity->y = balls[2]->velocity->y + (GRAVITY*DT);

	//TODO: if you want gravity or friction or another movement dimension, put it here
}

//sets up timer.  don't change this.
TimerHandler::TimerHandler(int t)
{
	QTimer* timer=new QTimer(this);
	QObject::connect(timer, SIGNAL(timeout()), this, SLOT(onTimer()));
	timer->start(t);
}

//called automatically 66 times per second (you can adjust this by changing TIMESTEP at the top of the program)
void TimerHandler::onTimer()
{
	int i,j;
	//move each ball
	for(i=0; i<BallCount; i++)
		balls[i]->move();

	//detect collision between balls
	for(i=0; i<BallCount; i++)
	{
		for(j=i+1; j<BallCount; j++)
		{
            if (balls[i]->position->sub(balls[j]->position)->lengthsquared() <= (balls[i]->radius+balls[j]->radius)*(balls[i]->radius+balls[j]->radius))
            {
                handleCollision(balls[i], balls[j]);
            }
		}
	}
    //detect collision with a wall
        for(i=0; i<BallCount; i++)
        {
            for(j=0; j<WallCount; j++)
            {
                if(!walls[j]->isVertical)
                {
                    if(abs(balls[i]->position->y - walls[j]->point3)<balls[i]->radius && balls[i]->position->x+balls[i]->radius >= walls[j]->point1 && balls[i]->position->x-balls[i]->radius <= walls[j]->point2)
                    {
                        //the ball might overlap.  get the ball out of the wall.
                        if(balls[i]->position->y<walls[j]->point3)
                            balls[i]->position->y = walls[j]->point3-balls[i]->radius;
                        else
                            balls[i]->position->y = walls[j]->point3+balls[i]->radius;
							//balls[i]->setPos(balls[i]->position->x,balls[i]->position->y);
							//invert the velocity and damp if needed
                        balls[i]->velocity->y = -balls[i]->velocity->y * RESTITUTION;
                    }
                }
                else
                {
                    if(abs(balls[i]->position->x - walls[j]->point3)<balls[i]->radius && balls[i]->position->y+balls[i]->radius >= walls[j]->point1 && balls[i]->position->y-balls[i]->radius <= walls[j]->point2)
                    {
                        //the ball might overlap.  get the ball out of the wall.
                        if(balls[i]->position->x<walls[j]->point3)
                            balls[i]->position->x = walls[j]->point3-balls[i]->radius;
                        else
                            balls[i]->position->x = walls[j]->point3+balls[i]->radius;
						//balls[i]->setPos(balls[i]->position->x,balls[i]->position->y);
                        //invert the velocity and damp if needed
                        balls[i]->velocity->x = -balls[i]->velocity->x * RESTITUTION;
                    }
                }
            }
        }
        //detect collision with the boundary walls
        //TODO:  you may want to add restitution to these collisions as well
        for(i=0; i<BallCount; i++)
        {
            //Bottom
            if(balls[i]->position->y + balls[i]->radius >= BOUND)
            {
                balls[i]->position->y = BOUND-balls[i]->radius;
                if(balls[i]->velocity->y > 0)
                    balls[i]->velocity->y = -balls[i]->velocity->y;
            }
            //Right
            if(balls[i]->position->x + balls[i]->radius >= BOUND)
            {
                balls[i]->position->x = BOUND-balls[i]->radius;
                if(balls[i]->velocity->x > 0)
                    balls[i]->velocity->x = -balls[i]->velocity->x;
            }
            //Top
            if(balls[i]->position->y - balls[i]->radius <=0)
            {
                balls[i]->position->y = balls[i]->radius;
                if(balls[i]->velocity->y < 0)
                    balls[i]->velocity->y = -balls[i]->velocity->y;
            }
            //Left
            if(balls[i]->position->x - balls[i]->radius <=0)
            {
                balls[i]->position->x = balls[i]->radius;
                if(balls[i]->velocity->x < 0)
                    balls[i]->velocity->x = -balls[i]->velocity->x;
            }
        }



        //redraw the balls
        for(i=0; i<BallCount; i++)
            balls[i]->setPos(balls[i]->position->x,balls[i]->position->y);
        //	view->update();
}

int main(int argc, char **argv)
{
    QApplication app(argc,argv);
    qsrand(QTime(0,0,0).secsTo(QTime::currentTime()));

    QGraphicsScene scene;
    scene.setSceneRect(0,0,500,500);

    for(int i=0; i<BallCount; i++)
    {
        balls[i] = new Ball;
        scene.addItem(balls[i]);
    }

/*	walls[0]=new Wall(1,500,1,false);
    walls[1]=new Wall(1,500,498,false);
    walls[2]=new Wall(1,500,1,true);
    walls[3]=new Wall(1,500,498,true);
*/
	//creating walls for the piston
    walls[0]=new Wall(25,475,360,false);
    //walls[1]=new Wall(100,360,125,true);
    walls[1]=new Wall(100,360,150,true);

    walls[2]=new Wall(100,330,200,true);
    walls[3]=new Wall(100,330,295,true);
    walls[4]=new Wall(100,360,345,true);
    walls[5]=new Wall(100,360,475,true);
    walls[6]=new Wall(25,199,100,false);
    walls[7]=new Wall(296,475,100,false);
    walls[8]=new Wall(244,245,300,false);

	//create balls to use as pistons/drivers
    balls[0]->velocity->x=0;
    balls[0]->velocity->y=0;
    balls[0]->mass=50;
    balls[0]->position->x=248;
    balls[0]->position->y=285;
    balls[0]->radius=45;

    balls[1]->velocity->x=0;
    balls[1]->velocity->y=0;
    balls[1]->mass=1000;
    balls[1]->position->x=150;
    balls[1]->position->y=125;
    balls[1]->radius=25;

    balls[2]->velocity->x=0;
    balls[2]->velocity->y=0;
    balls[2]->mass=1000;
    balls[2]->position->x=320;
    balls[2]->position->y=125;
    balls[2]->radius=25;


	//draw all walls into the window
    for(int i=0; i<WallCount; i++)
        scene.addItem(walls[i]);

    view=new QGraphicsView(&scene);
    view->setWindowTitle("Ball");
    view->resize(500,500);
    view->show();

    TimerHandler timer(DT);

    return app.exec();
}
