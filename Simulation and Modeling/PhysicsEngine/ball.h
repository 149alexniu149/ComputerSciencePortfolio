#include <QGraphicsItem>
#include <QGraphicsView>
#include <QTimer>
#include <QWidget>

class QGraphicsScene;

class BallView : public QGraphicsView
{
	Q_OBJECT
public:
	BallView(QGraphicsScene*, QWidget*x=  NULL);
	int pressX,pressY;
};
//class definition of vector including operations that can be performed on them
class Vector
{
public:
	float x,y;
	Vector(float,float);
	Vector* add(Vector*);
	Vector* sub(Vector*);
	Vector* mul(float);
    Vector* div(float);
	float dot(Vector*);
	Vector* normalize();
	float length();
	float lengthsquared();
	float angle();	
    float theta();
    float dist(Vector*);
};
//class definition of ball, defined by Dr. Black
class Ball : public QGraphicsItem
{
public:
	Ball();
	QRectF boundingRect() const;
	void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);
	float mass;
	float radius;
	Vector* velocity;
	Vector* position;
	void move();
	bool contains(float,float);
    int type;

	QColor color;
};
//class definition of wall, by Dr. Black
class Wall : public QGraphicsItem
{
public:
    Wall(float,float,float,bool);
    QRectF boundingRect() const;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);
    float point1,point2,point3;
    bool isVertical;
};

//class definition of the timing element, by Dr. Black
class TimerHandler : public QWidget
{
Q_OBJECT
public:
	TimerHandler(int);
protected slots:
	void onTimer();
};
//creation of function to handle collisions.
void handleCollision(Ball*,Ball*);
