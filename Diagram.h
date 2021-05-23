
#ifndef Diagram_h
#define Diagram_h

#include <queue>
#include <set>

#include "Figures.h"
#include "Event.h"


namespace vor
{

	typedef std::vector<Point2*>	Vertices;
	typedef std::vector<Edge*>		Edges;

	class Compare
	{
	public:
		bool operator() (Event* l, Event* r)
		{
			return (l->point->y < r->point->y);
		}
	};


	class Voronoi
	{
	public:

		Edges* CreateEdges(Vertices* v, int w);

	private:

		Edges*			edges;
		Edges*			connect;
		Parabola*		root;
		double			liney;

		std::set<Event*>	done; 
		std::priority_queue<Event*, std::vector<Event*>, Compare> queue;

		void		ParEvent(Point2* p);
		void		CirEvent(Event* event);
		void		FinishEdge(Parabola* par, int w);
		Parabola*	FindParabola(double xx);
		double		FindY(Point2* foc, double x);
		void		CheckCircle(Parabola* p1);
		Point2*		GetEdgeIntersection(Edge* a, Edge* b); 
		double		FindX(Parabola* par);
		double		GetRadius(Parabola* p1, Parabola* p2, Parabola* p3);
	};
}

#endif
