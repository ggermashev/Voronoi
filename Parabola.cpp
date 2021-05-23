#include <iostream>
#include "Figures.h"

Parabola::Parabola(Edge *edg)
{
	site = 0;
	CircleEvent = 0;
	edge = edg;
	parent = 0;
}

Parabola::Parabola(Point2* s)
{
	site = s;
	CircleEvent = 0;
	edge = 0;
	parent = 0;
}


Parabola* Parabola::GetLeftEdge(Parabola* p)
{
	Parabola* par = p->parent;
	Parabola* prev= p;
	while (par->Left == prev)
	{
		if (!par->parent) return 0;
		prev = par;
		par = par->parent;
	}
	return par;
}

Parabola* Parabola::GetRightEdge(Parabola* p)
{
	Parabola* par = p->parent;
	Parabola* prev = p;
	while (par->Right == prev)
	{
		if (!par->parent) return 0;
		prev = par;
		par = par->parent;
	}
	return par;
}

Parabola* Parabola::GetLeftArch(Parabola* p)
{
	if (!p) return 0;
	Parabola* par = p->Left;
	while (par->edge) par = par->Right;
	return par;
}

Parabola* Parabola::GetRightArch(Parabola* p)
{
	if (!p) return 0;
	Parabola* par = p->Right;
	while (par->edge) par = par->Left;
	return par;
}
