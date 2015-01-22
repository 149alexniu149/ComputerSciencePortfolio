#include "car.h"
#include "physicsengine.h"
#include "ball.h"
#include <QtGui>
//random number between a and b inclusive
int randint(int a, int b)
{
	return (qrand()%(b-a+1))+a;
}
//TODO
Car* Car::mutate()
{
	Car* newcar=new Car(nodes);
	return newcar;
}
//TODO
Car* Car::breed(Car* c)
{
	Car* newcar=new Car(nodes);
	return newcar;
}
//makes a random car
Car::Car(int n)
{
    //make all of the arrays I need
	nodes=n;
	balls_x=new int[nodes];
	balls_y=new int[nodes];
	balls=new int[nodes];
	links=new int*[nodes];
	for(int i=0; i<nodes; i++) links[i]=new int[nodes];
	numlinks=0;
	linkslist=new int[nodes*nodes];
    //make random ball locations on screen from 5 to fifty
	for(int i=0; i<nodes; i++)
	{
		balls_x[i]=randint(5,50);
		balls_y[i]=randint(5,50);
	}
    //makes links, 1/3 probability link will be between any two balls
	for(int i=0; i<nodes; i++)
	{
		for(int j=0; j<nodes; j++)
		{
			links[i][j]=0;
			if(i<=j) continue;
			if(randint(1,3)==1)
			{
				links[i][j]=1;
			}
		}
	}
}
//graphically construct the car
void Car::constructCar()
{
	balls=new int[nodes];
	numlinks=0;
	linkslist=new int[nodes*nodes];
	
	for(int i=0; i<nodes; i++)
	{
		balls[i]=makeBall(balls_x[i],balls_y[i]);
	}
	for(int i=0; i<nodes; i++)
	{
		for(int j=0; j<nodes; j++)
		{
			if(links[i][j])
			{
				linkslist[numlinks++]=makeLink(i,j);
			}
		}
	}
}
//graphically destroy the car
void Car::deconstructCar()
{
	for(int i=0; i<numlinks; i++)
		removeLink(linkslist[i]-i);
	for(int i=0; i<nodes; i++)
		removeBall(balls[i]-i);

	delete balls;
	delete linkslist;
}
//determine where car is at end of race
int Car::getCarPosition()
{
	int sum=0;
	for (int i=0; i<nodes; i++)
		sum+=getBall(i)->position->x;
	return sum / nodes;
}

int Car::score(int itr, int pos)
{
    iterations=itr;
    position=pos;
    int score = position  - iterations;
    return score;
}
