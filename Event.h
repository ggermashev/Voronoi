
#ifndef Event_h
#define Event_h

#include "Figures.h"

class Event
{
public:
	Point2* point;
	bool	parevent;
	Parabola* arch;
	double rad;


	Event(Point2* p, bool parev)
	{
		point = p;
		parevent = parev;
		arch = 0;
		rad = 0;
	}


};

#endif
