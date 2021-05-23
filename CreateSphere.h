#pragma once
#include "Diagram.h"
#include "Figures.h"

struct P3 {
	float x;
	float y;
	float z;
	bool connect;
	int count;
};

struct Edge3 {
	P3 *start;
	P3 *end;
	P3 *l;
	P3 *r;
	bool flag;
	int used;

};
void CreateSphere(struct P3** mas, int n);

void OutputMas(P3** mas, int n);

vor::Vertices* D3toD2(P3** mas, int n, vor::Vertices* ver,  double* w);

void D2toD3(vor::Edges* edg, struct Edge3 **edg3, int n, int *m);

void check(P3** mas, int n, vor::Vertices* ver);

void count(vor::Edges* edg, int* m);

void add_point(struct P3** a, struct Edge3** edg3, int* m, P3** mas, int* k, int n);

void find_connect(struct P3** mas, vor::Edges* edg, int *k);

P3* Find_norm(Edge3* edg1, Edge3* edg2);
