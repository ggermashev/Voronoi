
#include "Diagram.h"
#include <iostream>
#include <time.h>
#include <fstream>

using namespace vor;

Edges* Voronoi::CreateEdges(Vertices* v, int w)
{
		root = 0;
		edges = new Edges();
		connect = new Edges();

		for (auto i = v->begin(); i != v->end(); ++i)
		{
			queue.push(new Event(*i, true));
		}

		Event* event;
		while (!queue.empty())
		{
			event = queue.top();
			queue.pop();
			liney = event->point->y;
			if (event->parevent) ParEvent(event->point);
			else {
				if (done.find(event) != done.end()) { delete(event); done.erase(event); continue; }
				CirEvent(event);
			}
			delete(event);

		}


		FinishEdge(root, w);
		
		
		auto i = edges->begin();
		auto j = connect->begin();
		int k = 0;
		int size = edges->size();
		while (k < size) {
			if ((*i) && (*j)) {
				(*i)->start = (*j)->end;
				if ((*j)->for_sphere == true) (*i)->for_sphere = true;
			}
			k++;
			i++;
			j++;
		}
		

		delete(connect);
		return edges;
		
}

void	Voronoi::ParEvent(Point2* p)
{
	if (!root) { root = new Parabola(p); return; }

	Parabola* par = FindParabola(p->x);

	Point2* start = new Point2(p->x, FindY(par->site, p->x));


	Edge* l = new Edge(start, par->site, p);
	Edge* r = new Edge(start, p, par->site);

	edges->push_back(l);
	connect->push_back(r);

	par->edge = r;

	Parabola* pl = new Parabola(par->site);
	Parabola* p1 = new Parabola(p);
	Parabola* pr = new Parabola(par->site);

	par->Right = pr;
	pr->parent = par;

	par->Left = new Parabola(l);
	par->Left->parent = par;
	
	par->Left->Left = pl;
	par->Left->Left->parent = par->Left;
	
	par->Left->Right = p1;
	par->Left->Right->parent = par->Left;


	done.insert(par->CircleEvent);
	
	CheckCircle(pl);
	CheckCircle(pr);

}

void	Voronoi::CirEvent(Event* event)
{
	Parabola* p1 = event->arch;

	Parabola* l = Parabola::GetLeftEdge(p1);
	Parabola* r = Parabola::GetRightEdge(p1);

	Parabola* pl = Parabola::GetLeftArch(l);
	Parabola* pr = Parabola::GetRightArch(r);

	Point2* p = new Point2(event->point->x, event->point->y + event->rad);

	l->edge->end = p;
	r->edge->end = p;

	l->edge = new Edge(p, pl->site, pr->site);
	r->edge = new Edge(p, pl->site, pr->site);

	l->edge->end = p;
	r->edge->end = p;

	edges->push_back(l->edge);
	connect->push_back(r->edge);
	
	
	Parabola* gparent = p1->parent->parent;
	if (p1->parent->Left == p1)
	{
		if (gparent->Left == p1->parent)
		{
			gparent->Left = p1->parent->Right;
			gparent->Left->parent = gparent;
		}
		if (gparent->Right == p1->parent) 
		{
			gparent->Right = p1->parent->Right;
			gparent->Right->parent = gparent;
		}
	}
	else
	{
		if (gparent->Left == p1->parent) 
		{
			gparent->Left = p1->parent->Left;
			gparent->Left->parent = gparent;
		}
		
		if (gparent->Right == p1->parent)
		{
			gparent->Right = p1->parent->Left;
			gparent->Right->parent = gparent;
		}
	}

	delete p1->parent;
	delete p1;
	


	done.insert(pl->CircleEvent);
	done.insert(pr->CircleEvent);
	

	CheckCircle(pl);
	CheckCircle(pr);

}

void	Voronoi::CheckCircle(Parabola* p1)
{
	Parabola* l = Parabola::GetLeftEdge(p1);
	Parabola* r = Parabola::GetRightEdge(p1);


	Parabola* pl = Parabola::GetLeftArch(l);
	Parabola* pr = Parabola::GetRightArch(r);

	if (!pl || !pr || pl->site == pr->site) return;

	Point2* intersection;

	intersection = GetEdgeIntersection(l->edge, r->edge);
	if (intersection == 0) return;

	double radius = GetRadius(pl, p1, pr);

	p1->CircleEvent = new Event(new Point2(intersection->x, intersection->y - radius), false);
	p1->CircleEvent->arch = p1;
	p1->CircleEvent->rad = radius;
	queue.push(p1->CircleEvent);
}

void	Voronoi::FinishEdge(Parabola* par, int w)
{
	if (!par->edge) { delete par; return; }

	double endx;

	if (par->edge->right )	endx = 2.0 * (double) w;
	else						endx = -2.0 * (double) w;
	
	//par->edge->end = new Point2(endx, endx * par->edge->k + par->edge->h);;
	par->edge->end = par->edge->start;
	par->edge->for_sphere = true;
	//std::cout << "()\n";

	FinishEdge(par->Left,w);
	FinishEdge(par->Right,w);
	delete par;
}

double Voronoi::FindX(Parabola* par)
{			
	using namespace std;

	Point2* l = Parabola::GetLeftArch(par)->site;
	Point2* r = Parabola::GetRightArch(par)->site;
	double p1 = l->y - liney;
	double p2 = r->y - liney;
	double k = p1 * r->x - p2 * l->x;
	double y1 = l->y - p1 / 2;
	double y2 = r->y - p2 / 2;
	double d = p1 * p2 * ((l->x - r->x) * (l->x - r->x) + 2 * (y2 - y1) * (p2 - p1));

	double x1 =  (k + sqrt(d)) / (p1 - p2);
	double x2 =  (k - sqrt(d)) / (p1 - p2);

	double res;
	if (l->y < r->y) res = std::max(x1, x2);
	else res = std::min(x1, x2); 

	return res;	
}

Parabola* Voronoi::FindParabola(double parx)
{
	Parabola* par = root;
	double x;
	
	while (par->edge) 
	{
		x = FindX(par);
		if (x > parx) par = par->Left;
		else par = par->Right;
	}
	return par;
}

double	Voronoi::FindY(Point2* foc, double x) // focus, x-coordinates
{
	double p = (foc->y - liney);
	return (foc->y - p / 2 + (x - foc->x) * (x - foc->x) / (2 * p));
}

Point2* Voronoi::GetEdgeIntersection(Edge* a, Edge* b)
{
	double x = (b->h - a->h) / (a->k - b->k);
	double y = b->k * x + b->h;
	
	if ((x > a->start->x) && (!a->right )) return 0;
	if ((x < b->start->x) && (b->right) ) return 0;
	
	Point2* p = new Point2(x, y);
	return p;
} 

double Voronoi::GetRadius(Parabola* p1, Parabola* p2, Parabola* p3)
{
	using namespace std;
	double x1 = p1->site->x;
	double y1 = p1->site->y;
	double x2 = p2->site->x;
	double y2 = p2->site->y;
	double x3 = p3->site->x;
	double y3 = p3->site->y;

	double a = sqrt((x3 - x2) * (x3 - x2) + (y3 - y2) * (y3 - y2));
	double b = sqrt((x3 - x1) * (x3 - x1) + (y3 - y1) * (y3 - y1));
	double c = sqrt((x1 - x2) * (x1 - x2) + (y1 - y2) * (y1 - y2));

	double p = (a + b + c) / 2;
	double s = sqrt(p * (p - a) * (p - b) * (p - c));

	double r = a * b * c / (4 * s);
	return r;
}
