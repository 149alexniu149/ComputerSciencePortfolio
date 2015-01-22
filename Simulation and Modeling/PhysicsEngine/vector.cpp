//VECTOR METHODS GO HERE
//YOU SHOULD ADD ON THE add, normalize, AND OTHER METHODS AS YOU NEED THEM

#include "ball.h"
#include <math.h>
//creates class vector
Vector::Vector(float xx, float yy)
{
    x=xx; y=yy;
}
//subtraction of vectors
Vector* Vector::sub(Vector* v)
{
    Vector *vnew=new Vector(x,y);
    vnew->x-=v->x;
    vnew->y-=v->y;
    return vnew;
}

//finding the length squared of the vectors
float Vector::lengthsquared()
{
    return (x*x+y*y);
}

//TODO:  YOU NEED TO ADD THE REST OF THE VECTOR METHODS...
Vector* Vector::mul(float n)
{
    Vector *vnew=new Vector(x,y);
    vnew->x*=n;
    vnew->y*=n;
    return vnew;
}
//adding method
Vector* Vector::add(Vector* v)
{
    Vector *vnew=new Vector(x,y);
    vnew->x+=v->x;
    vnew->y+=v->y;
    return vnew;
}
//normalizing method
Vector* Vector::normalize()
{
    Vector *vnew=new Vector(x,y);
    vnew->x=x/sqrt((x * x) + (y * y));
    vnew->y=y/sqrt((x * x) + (y * y));
    return vnew;
}

//gets the dot product of the vectors
float Vector::dot(Vector* v)
{
   float value = x*v->x + y*v->y;
   return value;
}
//division method
Vector* Vector::div(float n)
{
    Vector *vnew=new Vector(x,y);
    vnew->x/=n;
    vnew->y/=n;
    return vnew;
}
//finds the angle between two vectors
float Vector::theta()
{

    {
        return atan2(y,x);
    }

}
//finds the distance between vectors
float Vector::dist(Vector* v)
{
	//partner's variable name...
    float shaheenisawesome= sqrt(pow(v->x-x,2)+pow(v->y-y,2));
    return shaheenisawesome;
}


