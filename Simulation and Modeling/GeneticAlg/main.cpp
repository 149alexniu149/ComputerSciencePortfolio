//GENETIC CARS
//
//Template: Michael Black, 2014
//
//main.cpp does the following in order:
//	1) creates a population of cars
//	2) creates a racecourse
//	3) genetically improves the cars by racing them
//	4) creates the window
//	5) shows the winning cars

#include <iostream>
#include <QtWidgets>
#include <math.h>
#include "main.h"
#include "physicsengine.h"
#include "car.h"
const int BALLS_IN_CAR=10;
const int GENERATIONS=20;		//how many breeding generations
const int MAXCARS=1000;			//maximum # of cars.  more than this will segfault
const int SURVIVORS=20;			//kill all but this many cars
const int INITIAL_POPULATION=30;	//how many cars we start with
const int SIMULATION_LENGTH = 3000;
const int BREEDRATE=20;
const int MUTATERATE=50;
const int BALL_MUTATE=1;
const int LINK_CHANCE=1;
void makeRaceCourse(int);
int WIDTH=1000,HEIGHT=1000;		//screen width and height
QGraphicsScene* thescene;		//window component
WindowView* view;               //window
int timeunit=1000/660;			//when we're actually showing the car, do a frame every this many milliseconds

Car* car[MAXCARS];              //cars are stored here
int CarCount=INITIAL_POPULATION;//keeps track of how many valid cars there are
int currentCar;                 //which car we're currently racing
int iterations;                 //how many frames we have simulated so far
extern bool simulating;			//TRUE if actively racing a car, FALSE during setup
extern bool dontdographics;		//TRUE if no window is open, FALSE if we want to see the cars in the window
//sets up a timer for visualization
TimerHandler::TimerHandler(int t)
{
	QTimer* timer=new QTimer(this);
	QObject::connect(timer, SIGNAL(timeout()), this, SLOT(onTimer()));
	timer->start(t);
}
//when a timer goes off, ready to show a frame
//this only happens where we're ready to see the winning cars
void TimerHandler::onTimer()
{
	if(!simulating) return;
	doFrame();
	int pos=car[currentCar]->getCarPosition();
	iterations++;
    if(iterations>=SIMULATION_LENGTH || pos>=WIDTH)
	{
		qDebug() << iterations<<" iterations, position="<<pos<<endl;
		car[currentCar]->score(iterations,pos);
		car[currentCar]->deconstructCar();
		currentCar++;
		if(currentCar>=CarCount)
		{
            //simulating=FALSE;
            currentCar=0;
            makeRaceCourse(1);

			for (int i=0; i<CarCount; i++)
            {
                qDebug()<<"Car "<<i<<": itr: "<<car[i]->iterations<<", pos: "<<car[i]->position<<endl;
			}
            car[currentCar]->constructCar();
		}
		else
		{
			car[currentCar]->constructCar();
		}
		iterations=0;
	}
}
WindowView::WindowView(QGraphicsScene *scene, QWidget* parent):QGraphicsView(scene, parent) { }
//if a car is racing stop it by right clicking
void WindowView::mousePressEvent(QMouseEvent *event)
{
	if(event->button() == Qt::RightButton)
	{
		simulating=!simulating; return;
	}
}
//if no car is breeding, make a new car on double click
void WindowView::mouseDoubleClickEvent(QMouseEvent *event)
{
	if(event->button() == Qt::LeftButton)
	{
		currentCar=0;
		car[currentCar]->constructCar();
		simulating=TRUE;
	}
}
//sort and kill by average distance traveled
    //car that gets furthest wins(by average ball position)
    //if car distance is bigger than end of track, then lowesttime (in frames) takes precedence
void kill()
{
    for(int i =0; i<CarCount; i++)
    {
        //std::cout<<i<<std::endl;
        for(int j = 0; j<CarCount-1; j++)
        {
            //std::cout<<j<<std::endl;
            if(car[j+1]->scr > car[j]->scr)
            {
                Car* swap = car[j+1];
                car[j+1]=car[j];
                car[j] = swap;
            }

        }

    }
    CarCount = SURVIVORS;


}
//TODO: consider every pair of cars, roll random to decide to breed, begin breeding
void breed()
{
   
    int breedingpop = CarCount;
    for(int i = 0; i<breedingpop; i++)
    {
        for(int j = 0; j<breedingpop; j++)
        {
            if(i==j)
                continue;
            //go into loop
            if(rand()%100<=BREEDRATE)
            {

                //creating a baby car
                Car* baby = new Car(BALLS_IN_CAR);
                //establishing a random value for crossover
                int randval = rand()%BALLS_IN_CAR;
                //starting the crossover loop
                for(int k = 0; k<randval; k++)
                {
                    //giving the baby car its balls
                    baby->balls_x[k] = car[i]->balls_x[k];
                    baby->balls_y[k] = car[i]->balls_y[k];
                }
                //gives the baby car its balls from mom
                for(int k = BALLS_IN_CAR-1; k>=randval; k--)
                {
                    baby->balls_x[k] = car[j]->balls_x[k];
                    baby->balls_y[k] = car[j]->balls_y[k];
                }
                //create new links between balls
                for (int f=0; f<BALLS_IN_CAR; f++)
                {
                    for (int m=0; m<BALLS_IN_CAR; m++)
                    {
						//don't link balls together more than once
                       if (f<=m)
                       {
                            continue;
                       }
					   //use random value to determine whether or not to place a new linkage
                       if(f<randval)
                       {
                           baby->links[f][m] = car[i]->links[f][m];
                       }
                       else
                       {
                           baby->links[f][m] = car[j]->links[f][m];
                       }

                    }
                }
				//add the new car to the population
                car[CarCount++]=baby;
              


            }

        }

    }
}
//pick a random car, clone if random returns true
void mutate()
{
    
    int mutantpop = CarCount;
   //starting the mutation loop
    for(int i = 0; i<mutantpop; i++)
    {
       //determine whether the car will mutate
        if(rand()%100<=MUTATERATE)
        {
            //creating the clone car
            Car* clone = new Car(BALLS_IN_CAR);
            //starting a copy loop
            for(int j = 0; j < BALLS_IN_CAR; j++)
            {
                //copying the balls over
                clone->balls_x[j] = car[i]->balls_x[j];
                clone->balls_y[j] = car[i]->balls_y[j];
            }
            //pick random balls to move to different positions
            for(int j = 0; j<BALLS_IN_CAR; j++)
            {
                if(rand()%100<=BALL_MUTATE)
                {
                    clone->balls_x[j] = rand()%45 + 5;
                    clone->balls_y[j] = rand()%45 + 5;
                }
            }
			//randomly mutate linkages
            for (int f=0; f<BALLS_IN_CAR; f++)
            {
                for (int m=0; m<BALLS_IN_CAR; m++)
                {
                   clone->links[f][m] = car[i]->links[f][m];
				   //no tow way links
                   if (f<=m)
                   {
                        continue;
                   }
				   //create or remove the links 
                   if (rand()%100<LINK_CHANCE)
                   {
                      
                       if(clone->links[f][m]==1)
                       {
                           
                           clone->links[f][m]=0;
                       }
                       else
                       {
                           
                           clone->links[f][m]=1;
                       }
                   }

                }
            }
            //add mutant to array
            car[CarCount++]=clone;
        }
    }
}
//does all racing, breding, etc behind the scenes, cars are assumed to be random , when ended senetically mutated cars have been added, ready to display
void doCars()
{
    //no window, dont make visible
	dontdographics=TRUE;
    //do the entire thnig for GENERATIONS number of times
	for(int gen=0; gen<GENERATIONS; gen++) {
		qDebug() << "****** GENERATION "<<gen<<" **********" <<endl;
        for(int track=0; track<2; track++)
        {
            makeRaceCourse(track);
            //for each car, race it, get its score
            for (int i=0; i<CarCount; i++)
            {
                //construct it
                //put the car into physics engie
                car[i]->constructCar();
                //tell the physics engine it can simulate now
                simulating=TRUE;
                int t=0;    //frame count
                int pos;    //how far teh car has gone
                //runs 2k frames then stops
                for(t=0; t<SIMULATION_LENGTH; t++)
                {
                    //move everything by one epsilon
                    doFrame();
                    //get car pos and save it
                    pos=car[i]->getCarPosition();
                    //did we make it to the finish line? if so, stom the sim
                    if(pos>=WIDTH) break;
                }
                //print out what happened
                //qDebug() << t<<" iterations, score="<<scr<<endl;
                //pass to car scoring funcion:how long it ran, how far it got
                car[i]->scr = car[i]->score(t,pos);
                qDebug() << t<<" iterations, score="<<car[i]->scr<<endl;
                //stop sim
                simulating=FALSE;
                //yank car off track
                car[i]->deconstructCar();
            }
	}
    //debugging loop: print out all car scores
	for (int i=0; i<CarCount; i++)
	{
		qDebug()<<"Car "<<i<<": itr: "<<car[i]->iterations<<", pos: "<<car[i]->position<<endl;
	}

    kill();     //call kill


    breed();    // call breed
    mutate();   //call mutate
}
    kill(); //kill off the worst cars the sort them best to worst
    //future cars constructed will show up on screen
	dontdographics=FALSE;
}
//racecourse stored here
extern Wall* walls[];
extern int WallCount;
void makeRaceCourse(int coursenumber)
{
    thescene->clear();
    WallCount=10;
	//creat a first course
    if(coursenumber==0)
    {
        walls[0]=new Wall(1,500,499,500);
        walls[1]=new Wall(-20,132,123,285);
        walls[2]=new Wall(104,285,203,277);
        walls[3]=new Wall(202,275,271,344);
        walls[4]=new Wall(271,600,320,344);
        walls[5]=new Wall(321,345,354,354);
        walls[6]=new Wall(354,354,394,400);
        walls[7]=new Wall(394,400,429,410);
        walls[8]=new Wall(429,410,498,420);
        walls[9]=new Wall(1,132,1,500);
    }
	//create a second course
    if(coursenumber==1)
    {
        walls[0]=new Wall(1,500,499,500);
        walls[1]=new Wall(-20,132,123,285);
        walls[2]=new Wall(104,285,203,277);
        walls[3]=new Wall(271,300,320,344);
        walls[4]=new Wall(271,600,320,344);
        walls[5]=new Wall(321,345,354,354);
        walls[6]=new Wall(354,354,394,400);
        walls[7]=new Wall(394,400,429,410);
        walls[8]=new Wall(429,410,498,420);
        walls[9]=new Wall(1,132,1,500);
    }



	for(int i=0; i<WallCount; i++)
		thescene->addItem(walls[i]);
}

int main(int argc, char **argv)
{
	QApplication app(argc,argv);
	qsrand(QTime(0,0,0).secsTo(QTime::currentTime()));

	thescene=new QGraphicsScene();
	thescene->setSceneRect(0,0,WIDTH,HEIGHT);

	for (int i=0; i<CarCount; i++)
        car[i]=new Car(BALLS_IN_CAR);
    //race and breed cars
    doCars();
    makeRaceCourse(0);
    //time to display car, set up first car to run
	currentCar=0;
    //car[currentCar]->constructCar();
    //simulating=TRUE;
    //make the window
	view=new WindowView(thescene);
	view->setWindowTitle("Genetic Cars");
	view->resize(WIDTH+50,HEIGHT+50);
	view->show();
	view->setMouseTracking(true);
    //start the timer
    TimerHandler timer(timeunit);

	return app.exec();
}
