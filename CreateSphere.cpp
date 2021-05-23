#include <math.h>
#include "CreateSphere.h"
#include <iostream>
#include "Figures.h"
#include "Diagram.h"
#include "Event.h"
#include <time.h>

void CreateSphere( P3 **mas, int n) {
	// равномерно 

	
	float dlg =  3.14159265358979323846 * (3 - sqrt(5));
	float dz = 2.0 / n;
	float lg = 0;
	float z = 1 - dz / 2;
	for (int i = 0; i < n; i++) {
		mas[i] = (P3*)calloc(1, sizeof(P3));
		float rad = sqrt(1 - z * z);
		mas[i]->x = cos(lg) * rad;
		mas[i]->y = sin(lg) * rad;
		mas[i]->z = z;
		z = z - dz;
		lg = lg + dlg;
		//std::cout << (mas[i]->x)* (mas[i]->x) + mas[i]->y* mas[i]->y + mas[i]->z* mas[i]->z << std::endl;
	}
	

	// случайно //
	/*
	float rad = 1;
	srand(time(NULL));
	for (int i = 0; i < n; i++) {
		mas[i] = (P3*)calloc(1, sizeof(P3));
		float a1 = rand();
		float a2 = rand();
		mas[i]->x = rad * sin(a1) * cos(a2);
		mas[i]->y = rad * sin(a1) * sin(a2);
		mas[i]->z = rad * cos(a1);
		mas[i]->connect = false;
	}
	*/
}


void OutputMas(P3** mas, int n) {
	for (int i = 0; i < n; i++) {
		std::cout << mas[i]->x << " " << mas[i]->y << " " << mas[i]->z << std::endl;
	}
}

vor::Vertices *D3toD2(P3 * *mas, int n, vor::Vertices *ver, double *w ) {
	
	
	for (int i = 0; i < n; i++) {
		ver->push_back(new Point2(mas[i]->x / (1 - mas[i]->z), mas[i]->y / (1 - mas[i]->z)));
		
		if (abs (mas[i]->x / (1 - mas[i]->z)) > abs( *w)) {
			*w = mas[i]->x / (1 - mas[i]->z); 
		}
		if (abs(mas[i]->y / (1 - mas[i]->z)) > abs(*w)) {
			*w = mas[i]->y / (1 - mas[i]->z);
		}
		
	}
	
	return ver;

}

void check(P3** mas, int n, vor::Vertices* ver) {
	int j = 0;
	for (auto i = ver->begin(); i != ver->end(); i++) {
		mas[j]->x = 2 * (*i)->x / (1 + (*i)->x * (*i)->x + (*i)->y * (*i)->y);
		mas[j]->y = 2 * (*i)->y / (1 + (*i)->x * (*i)->x + (*i)->y * (*i)->y);
		mas[j]->z = (-1 + (*i)->x * (*i)->x + (*i)->y * (*i)->y) / (1 + (*i)->x * (*i)->x + (*i)->y * (*i)->y);
		j++;
	}
}

void count(vor::Edges* edg, int* m) {
	*m = 0;
	for (auto i = edg->begin(); i != edg->end(); i++) {
		(*m)++;
	}
}

void D2toD3(vor::Edges *edg, Edge3 **edg3, int n, int *m) {
	int j = 0;
	
	for (auto i = edg->begin(); i != edg->end(); i++) {
		edg3[j] = (Edge3 *) calloc(*m, sizeof(Edge3));

		edg3[j]->start = (P3*) calloc(1, sizeof(P3));
		edg3[j]->end = (P3*) calloc(1, sizeof(P3));

		edg3[j]->start->x = 2 * (*i)->start->x / (1 + (*i)->start->x * (*i)->start->x + (*i)->start->y * (*i)->start->y);
		edg3[j]->end->x = 2 * (*i)->end->x / (1 + (*i)->end->x * (*i)->end->x + (*i)->end->y * (*i)->end->y);

		edg3[j]->start->y = 2 * (*i)->start->y / (1 + (*i)->start->x * (*i)->start->x + (*i)->start->y * (*i)->start->y);
		edg3[j]->end->y = 2 * (*i)->end->y / (1 + (*i)->end->x * (*i)->end->x + (*i)->end->y * (*i)->end->y);

		edg3[j]->start->z = (-1 + (*i)->start->x * (*i)->start->x + (*i)->start->y * (*i)->start->y) / (1 + (*i)->start->x * (*i)->start->x + (*i)->start->y * (*i)->start->y);
		edg3[j]->end->z = (-1 + (*i)->end->x * (*i)->end->x + (*i)->end->y * (*i)->end->y) / (1 + (*i)->end->x * (*i)->end->x + (*i)->end->y * (*i)->end->y);

		edg3[j]->l = (P3 *) calloc(1, sizeof(P3));
		edg3[j]->r = (P3*)calloc(1, sizeof(P3));

		edg3[j]->l->x = 2 * (*i)->l->x / (1 + (*i)->l->x * (*i)->l->x + (*i)->l->y * (*i)->l->y);
		edg3[j]->r->x = 2 * (*i)->r->x / (1 + (*i)->r->x * (*i)->r->x + (*i)->r->y * (*i)->r->y);

		edg3[j]->l->y = 2 * (*i)->l->y / (1 + (*i)->l->x * (*i)->l->x + (*i)->l->y * (*i)->l->y);
		edg3[j]->r->y = 2 * (*i)->r->y / (1 + (*i)->r->x * (*i)->r->x + (*i)->r->y * (*i)->r->y);

		edg3[j]->l->z = (-1 + (*i)->l->x * (*i)->l->x + (*i)->l->y * (*i)->l->y) / (1 + (*i)->l->x * (*i)->l->x + (*i)->l->y * (*i)->l->y);
		edg3[j]->r->z = (-1 + (*i)->r->x * (*i)->r->x + (*i)->r->y * (*i)->r->y) / (1 + (*i)->r->x * (*i)->r->x + (*i)->r->y * (*i)->r->y);

		edg3[j]->flag = (*i)->for_sphere;

		edg3[j]->start->count = 0;
		edg3[j]->end->count = 0;

		j++;

//		edg3[j]->used = 0;
	}
	*m = j;		
}


void add_point(struct P3** a, Edge3** edg3, int* m, P3** mas, int* k, int n) { // если конец = начало соединяем центр с этой вершиной(mas[i])
	int j = 0;
	for (int i = 0; i < *m; i++) {
		if (edg3[i]->flag == 1) {
			j++;
		}
	}
	a = (struct P3**)calloc(j, sizeof(P3));
	*k = j;
	int f = 0;
	int ff = 0;
	for (int i = 0; i < *m; i++) {
		if (ff >= n) return;
		if (edg3[i]->flag == 1) {
			a[f] = mas[ff];
			f++;
		}
		ff++;
	}
}

void find_connect(struct P3** mas, vor::Edges* edg, int *k) {
	int j = 0;
	for (auto i = edg->begin(); i != edg->end(); i++) {
		if ((*i)->for_sphere == true) { mas[j]->connect = true; }
		j++;
	}
	*k = j;
}

P3* Find_norm(Edge3* edg1, Edge3* edg2)
{
	P3* A = new P3;
	P3* B = new P3;
	A->x = edg1->end->x - edg1->start->x;
	A->y = edg1->end->y - edg1->start->y;
	A->z = edg1->end->z - edg1->start->z;
	B->x = edg2->end->x - edg2->start->x;
	B->y = edg2->end->y - edg2->start->y;
	B->z = edg2->end->z - edg2->start->z;
	P3* norm = new P3;
	norm->x = A->y * B->z - B->y * A->z;
	norm->y = A->z * B->x - A->x * B->z;
	norm->z = A->x * B->y - A->y * B->x;
	return norm;
}