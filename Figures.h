
#ifndef Figures_h
#define Figures_h

struct Point2
{
public:

	double x, y;

	Point2(double xx, double yy)
	{
		x = xx;
		y = yy;
	}
};

class Edge
{
public:
	Point2* start;
	Point2* end;
	bool right;
	Point2* l;
	Point2* r;
	bool for_sphere;

	double		k;
	double		h;

	Edge(Point2* s, Point2* a, Point2* b)
	{
		l = a;
		r = b;
		start = s;
		end = 0; 
		right = b->y > a->y;
		k = (b->x - a->x) / (a->y - b->y);
		h = s->y - k * s->x;
		if (for_sphere != true) for_sphere = false;
	}

};

class Event;

class Parabola
{
public:

	Point2* site;
	Edge* edge;
	Event* CircleEvent;
	Parabola* parent;
	Parabola* Left;
	Parabola* Right;

	Parabola(Edge* edg);
	Parabola(Point2* s);

	static Parabola* GetLeftEdge(Parabola* p);
	static Parabola* GetRightEdge(Parabola* p);
	static Parabola* GetLeftArch(Parabola* p);
	static Parabola* GetRightArch(Parabola* p);

};

#endif