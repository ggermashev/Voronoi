/*
#include <GL/glut.h> 

#include <time.h>
#include <iostream>
#include "figures.h"
#include"Diagram.h"
#include <fstream>
#include "CreateSphere.h"

void display (void);

vor::Voronoi * v;
vor::Vertices * ver; 
vor::Edges * edg;	 

double w = 5000;

int main(int argc, char** argv)
{
	using namespace vor;


	srand(time(NULL));



	v = new Voronoi();
	ver = new Vertices();

	
	for (int i = 0; i < 150; i++)
	{
		ver->push_back(new Point2(w * (double)rand() / (double)RAND_MAX, w * (double)rand() / (double)RAND_MAX));
	}
	


	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_SINGLE);
	glutInitWindowSize(1800, 2000);
	glutInitWindowPosition(0, 0);
	glutCreateWindow("Voronoi diagram");
	glutDisplayFunc(display);
	glutMainLoop();
	display();

	delete(v);
	delete [] ver;
	delete [] edg;



	return 0;
}

void drawDiagram()
{
	edg =  v->CreateEdges(ver, w);
	for (auto i = ver->begin(); i != ver->end(); ++i)
	{
		glBegin(GL_POINTS);
		glVertex2f((*i)->x / w, (*i)->y / w);
		glEnd();
	}
	
	for (auto i = edg->begin(); i != edg->end(); ++i)
	{
		glBegin(GL_LINES);
		glVertex2f((*i)->start->x / w, (*i)->start->y / w);
		glVertex2f((*i)->end->x / w, (*i)->end->y / w);
		glEnd();
	}
	
}


void display (void) 
{
	float x1 = 0.5, y1 = 0.5, z1 = 0.0; // положение камеры
	float x2 = 0.5, y2 = 0.5, z2 = 1.0; // положение точки, в которую смотрит камера
	gluLookAt(x1, y1, z1, x2, y2, z2, 0.0, 1.0, 0.0);
	drawDiagram();
	glFlush();	
}

*/


#include <iostream>
#include "CreateSphere.h"
#include <GL/glut.h>
#include <GLFW/glfw3.h>
#include <GL/glut.h>
#include "Diagram.h"
#include <fstream>


vor::Voronoi* v;
vor::Vertices* ver;
vor::Edges* edg;
Edge3** edg3;


double* w = (double*) calloc(1, sizeof(double));



P3** mas;
P3** a;

struct P3* center = (P3*)calloc(1, sizeof(P3));


int n;
int* m;
int* k  = (int*)calloc(1, sizeof(int));;

void reshape(int w, int h)
{

	glViewport(0, 0, w, h);
	glMatrixMode(GL_PROJECTION);
	
	glLoadIdentity();
	//glTranslatef(0.0, 0, 0);
	//glRotatef(45, 0, 0, 1);
	glMatrixMode(GL_MODELVIEW);	
	//MoveCamera();
}

void display()
{
	glClear(GL_COLOR_BUFFER_BIT);
	
	glColor3f(1.0f, 0.0f, 0.0f);


	float x1 = 0, y1 = 0.0, z1 = 0.0; // положение камеры
	float x2 = 0, y2 = 0.0, z2 = 1.0; // положение точки, в которую смотрит камера
	gluLookAt(x1, y1, z1, x2, y2, z2, 0.0, 1.0, 0.0);
	
	
	
	glBegin(GL_POINTS);
	for (int i = 0; i < n; i++) {
		if (mas[i]->z >= 0) {
			//glVertex3f(mas[i]->x, mas[i]->y, mas[i]->z);
		}
	}
	glEnd();
	
	
	/*
	glColor3f(0.0f, 1.0f, 1.0f);
	for (auto i = ver->begin(); i != ver->end(); ++i)
	{
		glBegin(GL_POINTS);
		glVertex2f((*i)->x    , (*i)->y );
		glEnd();
	}

	for (auto i = edg->begin(); i != edg->end(); ++i) //2d
	{
		glBegin(GL_LINES);
		glVertex2f((*i)->start->x , (*i)->start->y);
		glVertex2f((*i)->end->x , (*i)->end->y);
		//glVertex2f((*i)->l->x , (*i)->l->y );
		//glVertex2f((*i)->r->x , (*i)->r->y );
		glEnd();
	}
	*/
	
	
	
	
	for (int i = 0; i < *m; i++) { //diagram and triangl
		if (edg3[i]->start->z >= 0 || edg3[i]->end->z >=0) 
		//if (edg3[i]->l->z >= 0 && edg3[i]->r->z >= 0)
		{
			
			glBegin(GL_LINES);
			glColor3f(1.0f, 1.0f, 0.0f);// voronoi
			//if (edg3[i]->start.z <= 0) glColor3f(0.1f, 1.0f, 0.0f);
			glVertex3f(edg3[i]->start->x, edg3[i]->start->y, edg3[i]->start->z);
			glVertex3f(edg3[i]->end->x, edg3[i]->end->y, edg3[i]->end->z);
			glEnd();
			
			/*
			glBegin(GL_LINES); //triangl
			glColor3f(0.0f, 1.0f, 1.0f);
			glVertex3f(edg3[i]->l->x, edg3[i]->l->y, edg3[i]->l->z);
			glVertex3f(edg3[i]->r->x, edg3[i]->r->y, edg3[i]->r->z);
			glEnd();
			*/
		}

	}
	
	
	
	/*
	for (int i = 0; i < *m; i++) { //for triangl connect with center
		if (edg3[i]->start->z >= 0 || edg3[i]->end->z >= 0)
		{
			if (edg3[i]->flag == true) {
				std::cout << "*\n";
				//if (edg3[i]->start.z <= 0) glColor3f(0.1f, 1.0f, 0.0f);
				//glVertex3f(edg3[i]->start.x, edg3[i]->start.y, edg3[i]->start.z);
				//glVertex3f(edg3[i]->end.x, edg3[i]->end.y, edg3[i]->end.z);
				glBegin(GL_LINES);
				glColor3f(0.0f, 1.0f, 1.0f);
				glVertex3f(edg3[i]->l->x, edg3[i]->l->y, edg3[i]->l->z);
				glVertex3f(center->x,center->y,center->z);
				glEnd();

				glBegin(GL_LINES);
				glVertex3f(edg3[i]->r->x, edg3[i]->r->y, edg3[i]->r->z);
				glVertex3f(center->x, center->y, center->z);
				glEnd();
			}
		}

	}
	*/
	
	
	for (int i = 0; i < *m; i++) { //for voronoi ending diagram
		for (int j = i + 1; j < *m; j++) {
			if (edg3[i]->start->z >= 0 || edg3[i]->end->z >= 0)
			{
				if (edg3[i]->flag == true && edg3[j]->flag == true) {
					if ( (edg3[i]->l->x == edg3[j]->l->x && edg3[i]->l->y == edg3[j]->l->y && edg3[i]->l->z == edg3[j]->l->z) || (edg3[i]->l->x == edg3[j]->r->x && edg3[i]->l->y == edg3[j]->r->y && edg3[i]->l->z == edg3[j]->r->z) || (edg3[i]->r->x == edg3[j]->l->x && edg3[i]->r->y == edg3[j]->l->y && edg3[i]->r->z == edg3[j]->l->z) || (edg3[i]->r->x == edg3[j]->r->x && edg3[i]->r->y == edg3[j]->r->y && edg3[i]->r->z == edg3[j]->r->z)) {
						glBegin(GL_LINES);
						glColor3f(1.0f, 1.0f, 0.0f);
						if ( (edg3[i]->start->z >= edg3[i]->end->z) && (edg3[j]->start->z >= edg3[j]->end->z)) {
glVertex3f(edg3[i]->start->x, edg3[i]->start->y, edg3[i]->start->z);
glVertex3f(edg3[j]->start->x, edg3[j]->start->y, edg3[j]->start->z);
std::cout << "1!\n";

						}
 else
 if ((edg3[i]->start->z >= edg3[i]->end->z) && (edg3[j]->end->z >= edg3[j]->start->z)) {
	 glVertex3f(edg3[i]->start->x, edg3[i]->start->y, edg3[i]->start->z);
	 glVertex3f(edg3[j]->end->x, edg3[j]->end->y, edg3[j]->end->z);
	 std::cout << "2!\n";

 }
 else
	 if ((edg3[i]->end->z >= edg3[i]->start->z) && (edg3[j]->start->z >= edg3[j]->end->z)) {
		 glVertex3f(edg3[i]->end->x, edg3[i]->end->y, edg3[i]->end->z);
		 glVertex3f(edg3[j]->start->x, edg3[j]->start->y, edg3[j]->start->z);
		 std::cout << "3!\n";

	 }
	 else
		 if ((edg3[i]->end->z >= edg3[i]->start->z) && (edg3[j]->end->z >= edg3[j]->start->z)) {
			 glVertex3f(edg3[i]->end->x, edg3[i]->end->y, edg3[i]->end->z);
			 glVertex3f(edg3[j]->end->x, edg3[j]->end->y, edg3[j]->end->z);
			 std::cout << "4!\n";

		 }
		 glEnd();
					}
				}
			}
		}
		if (edg3[i]->start->z >= 0 || edg3[i]->end->z >= 0) {
			if (edg3[i]->flag == true) {
				glBegin(GL_LINES);
				if ((edg3[i]->start->z >= edg3[i]->end->z)) {
					glVertex3f(edg3[i]->start->x, edg3[i]->start->y, edg3[i]->start->z);
					glVertex3f(center->x, center->y, center->z);
				}
				else {
					glVertex3f(edg3[i]->end->x, edg3[i]->end->y, edg3[i]->end->z);
					glVertex3f(center->x, center->y, center->z);
				}
				glEnd();
			}
		}
	}



	glFlush;
	glutSwapBuffers();
}



int main(int argc, char* argv[])
{

	v = new vor::Voronoi();
	ver = new vor::Vertices();
	*w = 0;


	std::cout << "input n\n";
	std::cin >> n;
	mas = (P3**)calloc(n, sizeof(P3));
	CreateSphere(mas, n);

	ver = D3toD2(mas, n, ver, w);

	edg = v->CreateEdges(ver, *w);
	m = (int*)calloc(1, sizeof(int));
	count(edg, m);

	edg3 = (struct Edge3**)calloc(*m, sizeof(struct Edge3));
	D2toD3(edg, edg3, n, m);


	center->x = 0;
	center->y = 0;
	center->z = 1;

	std::ofstream fout;
	std::ofstream fout2;
	std::ofstream ffout;
	std::ofstream ffout2;

	fout.open("Sphere/Triangl.obj");
	fout2.open("Sphere/Voronoi.obj");
	ffout.open("Sphere/SidesTriangl.obj");
	ffout2.open("Sphere/SidesVoronoi.obj");
	//fout << " mtllib Sphere.mtl\n g ground_1\n usemtl ground_1\n v 0.19136047 0.0 - 3.861855\n v 0.19136047 0.0 3.7581449\n v 152.59135 0.0 3.7581449\n v 152.59135 0.0 - 3.861855\n vn 0.0 1.0 0.0\n vn 0.0 0.0 0.0\n f 1//1 2//1 3//1\n f 1//1 3//1 4//1\n g ground_1\n usemtl ground_1\n v 0.19136047 0.0 - 0.051855087\n v 152.59135 0.0 - 0.051855087\n vn 0.0 - 1.0 0.0\n f 4//3 6//3 5//3\n f 4//3 5//3 1//3\n g ground_1\n usemtl ground_1\n v 0.19136047 243.84 - 0.051855087\n v 0.19136047 243.84 - 3.861855\n v 152.59135 243.84 - 3.861855\n v 152.59135 243.84 - 0.051855087\n vn - 1.0 0.0 0.0\n vn 1.0 0.0 0.0\n vn 0.0 0.0 - 1.0\n f 1//4 5//4 7//4 8//4\n f 6//5 4//5 9//5 10//5\n f 4//6 1//6 8//6 9//6\n g ground_1\n usemtl ground_1\n f 8//1 7//1 10//1\n f 8//1 10//1 9//1\n g ground_1\n usemtl ground_1\n f 6//3 3//3 2//3\n f 6//3 2//3 5//3 \ng ground_1\n usemtl ground_1\n v 0.19136047 243.84 3.7581449\n v 152.59135 243.84 3.7581449\n vn 0.0 0.0 1.0\n f 5//4 2//4 11//4 7//4\n f 2//7 3//7 12//7 11//7\n f 3//5 6//5 10//5 12//5\n g ground_1\n usemtl ground_1\n f 7//1 11//1 12//1\n f 7//1 12//1 10//1";
	fout << "mtllib Triangl.mtl\n  usemtl ground_8\n";
	fout2 << "mtllib Triangl.mtl\n  usemtl ground_8\n";
	ffout << "mtllib Triangl.mtl\n  usemtl ground_1\n";
	ffout2 << "mtllib Triangl.mtl\n  usemtl ground_1\n";
	
	int cnt = 0;
	int prev = 0;
	srand(time(NULL));

	//d2vor
	std::ofstream vor2;
	vor2.open("D2/Voronoi2.obj");
	vor2 << "mtllib Triangl.mtl\n  usemtl ground_2\n";
	int zero = -1;
	int cvor2 = 0;
	for (auto i = edg->begin(); i != edg->end(); ++i)
	{
		vor2 << "v " << (*i)->start->x << " " << (*i)->start->y << " " << zero << " \n";
		vor2 << "v " << (*i)->end->x << " " << (*i)->end->y << " " << zero << " \n";
		cvor2++;
		vor2 << "l " << cvor2 << " ";
		cvor2++;
		vor2 << cvor2 << " \n";
	}
	vor2.close();

	int normx, normy, normz;
	int prevn = 0;
	int cntn = 0;
	for (int i = 0; i < *m; i++) {
		edg3[i]->used = 0;
	}
	//voronoi with sides
	P3* norm;
	for (int i = 0; i < *m; i++) {
		//if (edg3[i]->used == 2) continue;
		prev = cnt;
		prevn = cntn;
		if ((edg3[i]->used == 2) || (edg3[i]->used == 0)) {
			ffout2 << "v " << edg3[i]->start->x << " " << edg3[i]->start->y << " " << edg3[i]->start->z << " \n";			
			ffout2 << "v " << edg3[i]->end->x << " " << edg3[i]->end->y << " " << edg3[i]->end->z << " \n";			
			cnt++;
			cnt++;			
			edg3[i]->used += 1;	
			for (int j = 0; j < *m; j++) {			
				if (((edg3[i]->l->x == edg3[j]->l->x) && (edg3[i]->l->y == edg3[j]->l->y) && (edg3[i]->l->z == edg3[j]->l->z)) || ((edg3[i]->l->x == edg3[j]->r->x) && (edg3[i]->l->y == edg3[j]->r->y) && (edg3[i]->l->z == edg3[j]->r->z))) {
					//if ((edg3[j]->used == 1) || (edg3[j]->used >= 3)) continue;
					if (((edg3[i]->l->x == edg3[j]->l->x) && (edg3[i]->l->y == edg3[j]->l->y) && (edg3[i]->l->z == edg3[j]->l->z))) {
						if ((edg3[j]->used == 2) || (edg3[j]->used == 0)) edg3[j]->used += 1;
						else continue;
					}
					else
						if ((edg3[j]->used == 1) || (edg3[j]->used == 0)) edg3[j]->used += 2;
						else continue;

					cnt++;
					cnt++;
					ffout2 << "v " << edg3[j]->start->x << " " << edg3[j]->start->y << " " << edg3[j]->start->z << " \n";					
					ffout2 << "v " << edg3[j]->end->x << " " << edg3[j]->end->y << " " << edg3[j]->end->z << " \n";					
					
					
				}
			}

			ffout2 << "usemtl ground_" << 10 << " \n";	
			ffout2 << "f ";
			prev++;
			prevn++;
			int back = prev;
			while (prev <= cnt) {
				
				ffout2 << prev << " " ;
				prev++;
				
			}
			ffout2 << std::endl;
		}
		prev = cnt;
		prevn = cntn;
		if ((edg3[i]->used == 1) || (edg3[i]->used == 0)) {
			ffout2 << "v " << edg3[i]->start->x << " " << edg3[i]->start->y << " " << edg3[i]->start->z << " \n";
			ffout2 << "v " << edg3[i]->end->x << " " << edg3[i]->end->y << " " << edg3[i]->end->z << " \n";
			cnt++;
			cnt++;
			edg3[i]->used += 2;
			for (int j = 0; j < *m; j++) {
				
				if (((edg3[i]->r->x == edg3[j]->l->x) && (edg3[i]->r->y == edg3[j]->l->y) && (edg3[i]->r->z == edg3[j]->l->z)) || ((edg3[i]->r->x == edg3[j]->r->x) && (edg3[i]->r->y == edg3[j]->r->y) && (edg3[i]->r->z == edg3[j]->r->z))) {
					//if ((edg3[j]->used == 2) || (edg3[j]->used >= 3)) continue;
					if (((edg3[i]->r->x == edg3[j]->l->x) && (edg3[i]->r->y == edg3[j]->l->y) && (edg3[i]->r->z == edg3[j]->l->z))) {
						if ((edg3[j]->used == 2) || (edg3[j]->used == 0)) edg3[j]->used += 1;
						else continue;
					}
					else
						if ((edg3[j]->used == 1) || (edg3[j]->used == 0)) edg3[j]->used += 2;
						else continue;

					cnt++;
					cnt++;
					ffout2 << "v " << edg3[j]->start->x << " " << edg3[j]->start->y << " " << edg3[j]->start->z << " \n";
					ffout2 << "v " << edg3[j]->end->x << " " << edg3[j]->end->y << " " << edg3[j]->end->z << " \n";
				}
			}

			ffout2 << "usemtl ground_" << 10 << " \n";
			ffout2 << "f ";
			prev++;
			prevn++;
			int back = prev;
			
			while (prev <= cnt) {
				
				ffout2 << prev << " ";
				prev++;
				
			}
			ffout2 << std::endl;	
		}
	}
	prev = cnt;
	for (int i = 0; i < *m; i++)
	{
		prev = cnt;
		if (edg3[i]->flag == true)
		{
			/*
			if (edg3[i]->start->z > edg3[i]->end->z) ffout2 << "v " << edg3[i]->start->x << " " << edg3[i]->start->y << " " << edg3[i]->start->z << "\n";
			else ffout2 << "v " << edg3[i]->end->x << " " << edg3[i]->end->y << " " << edg3[i]->end->z << "\n";
			cnt ++;
			*/
			for (int j = 0; j < *m; j++)
			{
				if ((edg3[j]->flag == true) && (((edg3[i]->l->x == edg3[j]->l->x) && (edg3[i]->l->y == edg3[j]->l->y) && (edg3[i]->l->z == edg3[j]->l->z)) || ((edg3[i]->l->x == edg3[j]->r->x) && (edg3[i]->l->y == edg3[j]->r->y) && (edg3[i]->l->z == edg3[j]->r->z)) || ((edg3[i]->r->x == edg3[j]->l->x) && (edg3[i]->r->y == edg3[j]->l->y) && (edg3[i]->r->z == edg3[j]->l->z)) || ((edg3[i]->r->x == edg3[j]->r->x) && (edg3[i]->r->y == edg3[j]->r->y) && (edg3[i]->r->z == edg3[j]->r->z))))
				{
					if (edg3[i]->start->z > edg3[i]->end->z) ffout2 << "v " << edg3[i]->start->x << " " << edg3[i]->start->y << " " << edg3[i]->start->z << "\n";
					else ffout2 << "v " << edg3[i]->end->x << " " << edg3[i]->end->y << " " << edg3[i]->end->z << "\n";

					if (edg3[j]->start->z > edg3[j]->end->z) ffout2 << "v " << edg3[j]->start->x << " " << edg3[j]->start->y << " " << edg3[j]->start->z << "\n";
					else ffout2 << "v " << edg3[j]->end->x << " " << edg3[j]->end->y << " " << edg3[j]->end->z << "\n";

					ffout2 << "v " << center->x << " " << center->y << " " << center->z << "\n";
					cnt++;
					ffout2 << "usemtl ground_" << 10 << " \n";
					ffout2 << "f " << cnt << " ";
					cnt++;
					ffout2 << cnt << " ";
					cnt++;
					ffout2 << cnt << "\n";
				}
			}
			prev = cnt;
			if (edg3[i]->start->z > edg3[i]->end->z) ffout2 << "v " << edg3[i]->start->x << " " << edg3[i]->start->y << " " << edg3[i]->start->z << "\n";
			else ffout2 << "v " << edg3[i]->end->x << " " << edg3[i]->end->y << " " << edg3[i]->end->z << "\n";
			cnt++;
			for (int j = 0; j < *m; j++)
			{
				if ((((edg3[i]->l->x == edg3[j]->l->x) && (edg3[i]->l->y == edg3[j]->l->y) && (edg3[i]->l->z == edg3[j]->l->z)) || ((edg3[i]->l->x == edg3[j]->r->x) && (edg3[i]->l->y == edg3[j]->r->y) && (edg3[i]->l->z == edg3[j]->r->z)) || ((edg3[i]->r->x == edg3[j]->l->x) && (edg3[i]->r->y == edg3[j]->l->y) && (edg3[i]->r->z == edg3[j]->l->z)) || ((edg3[i]->r->x == edg3[j]->r->x) && (edg3[i]->r->y == edg3[j]->r->y) && (edg3[i]->r->z == edg3[j]->r->z))))
				{
					ffout2 << "v " << edg3[j]->start->x << " " << edg3[j]->start->y << " " << edg3[j]->start->z << "\n";
					ffout2 << "v " << edg3[j]->end->x << " " << edg3[j]->end->y << " " << edg3[j]->end->z << "\n";
					cnt += 2;
				}
			}
			ffout2 << "usemtl ground_" << 10 << " \n";
			ffout2 << "f ";
			prev++;
			prevn++;
			int back = prev;

			while (prev <= cnt) {

				ffout2 << prev << " ";
				prev++;

			}
			ffout2 << std::endl;
		}
	}
	/*
	ffout2 << "usemtl ground_" << 9 << " \n";
	ffout2 << "f ";
	prev++;
	while (prev <= cnt) {

		ffout2 << prev << " ";
		prev++;

	}
	ffout2 << std::endl;
	*/	

	///////////////////triangl with sides
	
	for (int i = 0; i < *m; i++) {
		std::cout << edg3[i]->used << "\n";
		edg3[i]->used = 0;
	}
	int count = 0;
	cnt = 0;
	prev = 0;
	int prevc;
	
	int normc = 0;
	for (int i = 0; i < *m; i++) {
		//if (edg3[i]->used == 2) continue;
			prev = cnt;
			prevc = normc;
			for (int j = i + 1; j < *m; j++) {
				if ((edg3[i]->start->x == edg3[j]->start->x) && (edg3[i]->start->y == edg3[j]->start->y) && (edg3[i]->start->z == edg3[j]->start->z)) {
					edg3[j]->used++;
					cnt++;
					cnt++;
					cnt++;
					cnt++;

					ffout << "v " << edg3[i]->l->x << " " << edg3[i]->l->y << " " << edg3[i]->l->z << " \n";
					
					if (edg3[i]->l->x > 0) normx = 1; else normx = -1;//
					if (edg3[i]->l->y > 0) normy = 1; else normy = -1;//
					if (edg3[i]->l->z > 0) normz = 1; else normz = -1;//
					//ffout << "vn " << normx << " " << normy << " " << normz << " \n";//
					normc++;
					
					ffout << "v " << edg3[i]->r->x << " " << edg3[i]->r->y << " " << edg3[i]->r->z << " \n";
					if (edg3[i]->r->x > 0) normx = 1; else normx = -1;
					if (edg3[i]->r->y > 0) normy = 1; else normy = -1;
					if (edg3[i]->r->z > 0) normz = 1; else normz = -1;
					//ffout << "vn " << normx << " " << normy << " " << normz << " \n";
					normc++;

					ffout << "v " << edg3[j]->l->x << " " << edg3[j]->l->y << " " << edg3[j]->l->z << " \n";
					if (edg3[j]->l->x > 0) normx = 1; else normx = -1;
					if (edg3[j]->l->y > 0) normy = 1; else normy = -1;
					if (edg3[j]->l->z > 0) normz = 1; else normz = -1;
					//ffout << "vn " << normx << " " << normy << " " << normz << " \n";
					normc++;

					ffout << "v " << edg3[j]->r->x << " " << edg3[j]->r->y << " " << edg3[j]->r->z << " \n";
					if (edg3[j]->r->x > 0) normx = 1; else normx = -1;
					if (edg3[j]->r->y > 0) normy = 1; else normy = -1;
					if (edg3[j]->r->z > 0) normz = 1; else normz = -1;
					//ffout << "vn " << normx << " " << normy << " " << normz << " \n";
					normc++;

					
					//посчитать векторное произведение и найти нормали для точек
					//проверить две нормали. сложить координаты с одной из вершин и посмотреть где длина вектора от начала координат больше.
					
				}
				if ((edg3[i]->start->x == edg3[j]->end->x) && (edg3[i]->start->y == edg3[j]->end->y) && (edg3[i]->start->z == edg3[j]->end->z)) {
					edg3[j]->used++;
					cnt++;
					cnt++;
					cnt++;
					cnt++;
					ffout << "v " << edg3[i]->l->x << " " << edg3[i]->l->y << " " << edg3[i]->l->z << " \n";
					if (edg3[i]->l->x > 0) normx = 1; else normx = -1;//
					if (edg3[i]->l->y > 0) normy = 1; else normy = -1;//
					if (edg3[i]->l->z > 0) normz = 1; else normz = -1;//
					//ffout << "vn " << normx << " " << normy << " " << normz << " \n";//
					normc++;

					ffout << "v " << edg3[i]->r->x << " " << edg3[i]->r->y << " " << edg3[i]->r->z << " \n";
					if (edg3[i]->r->x > 0) normx = 1; else normx = -1;
					if (edg3[i]->r->y > 0) normy = 1; else normy = -1;
					if (edg3[i]->r->z > 0) normz = 1; else normz = -1;
					//ffout << "vn " << normx << " " << normy << " " << normz << " \n";
					normc++;

					ffout << "v " << edg3[j]->r->x << " " << edg3[j]->r->y << " " << edg3[j]->r->z << " \n";
					if (edg3[j]->r->x > 0) normx = 1; else normx = -1;
					if (edg3[j]->r->y > 0) normy = 1; else normy = -1;
					if (edg3[j]->r->z > 0) normz = 1; else normz = -1;
					//ffout << "vn " << normx << " " << normy << " " << normz << " \n";
					normc++;

					ffout << "v " << edg3[j]->l->x << " " << edg3[j]->l->y << " " << edg3[j]->l->z << " \n";
					if (edg3[j]->l->x > 0) normx = 1; else normx = -1;
					if (edg3[j]->l->y > 0) normy = 1; else normy = -1;
					if (edg3[j]->l->z > 0) normz = 1; else normz = -1;
					//ffout << "vn " << normx << " " << normy << " " << normz << " \n";
					normc++;
				}
			}
			ffout << "usemtl ground_" << rand() % 7 + 1 << " \n";
			ffout << "f ";
			prev++;
			prevc++;
			while (prev <= cnt) {
				ffout << prev << /*"//" << prevc <<*/ " ";
				prev++;
				prevc++;
			}
			ffout << std::endl;
			prev = cnt;
			for (int j = i + 1; j < *m; j++) {
				if ((edg3[i]->end->x == edg3[j]->start->x) && (edg3[i]->end->y == edg3[j]->start->y) && (edg3[i]->end->z == edg3[j]->start->z)) {
					edg3[j]->used++;
					cnt++;
					cnt++;
					cnt++;
					cnt++;/*
					ffout << "v " << edg3[i]->r->x << " " << edg3[i]->r->y << " " << edg3[i]->r->z << " \n";
					ffout << "v " << edg3[i]->l->x << " " << edg3[i]->l->y << " " << edg3[i]->l->z << " \n";
					ffout << "v " << edg3[j]->l->x << " " << edg3[j]->l->y << " " << edg3[j]->l->z << " \n";
					ffout << "v " << edg3[j]->r->x << " " << edg3[j]->r->y << " " << edg3[j]->r->z << " \n";
					*/
					ffout << "v " << edg3[i]->l->x << " " << edg3[i]->l->y << " " << edg3[i]->l->z << " \n";
					if (edg3[i]->l->x > 0) normx = 1; else normx = -1;//
					if (edg3[i]->l->y > 0) normy = 1; else normy = -1;//
					if (edg3[i]->l->z > 0) normz = 1; else normz = -1;//
					//ffout << "vn " << normx << " " << normy << " " << normz << " \n";//
					normc++;

					ffout << "v " << edg3[i]->r->x << " " << edg3[i]->r->y << " " << edg3[i]->r->z << " \n";
					if (edg3[i]->r->x > 0) normx = 1; else normx = -1;
					if (edg3[i]->r->y > 0) normy = 1; else normy = -1;
					if (edg3[i]->r->z > 0) normz = 1; else normz = -1;
					//ffout << "vn " << normx << " " << normy << " " << normz << " \n";
					normc++;

					ffout << "v " << edg3[j]->r->x << " " << edg3[j]->r->y << " " << edg3[j]->r->z << " \n";
					if (edg3[j]->r->x > 0) normx = 1; else normx = -1;
					if (edg3[j]->r->y > 0) normy = 1; else normy = -1;
					if (edg3[j]->r->z > 0) normz = 1; else normz = -1;
					//ffout << "vn " << normx << " " << normy << " " << normz << " \n";
					normc++;

					ffout << "v " << edg3[j]->l->x << " " << edg3[j]->l->y << " " << edg3[j]->l->z << " \n";
					if (edg3[j]->l->x > 0) normx = 1; else normx = -1;
					if (edg3[j]->l->y > 0) normy = 1; else normy = -1;
					if (edg3[j]->l->z > 0) normz = 1; else normz = -1;
					//ffout << "vn " << normx << " " << normy << " " << normz << " \n";
					normc++;
					
				}
				if ((edg3[i]->end->x == edg3[j]->end->x) && (edg3[i]->end->y == edg3[j]->end->y) && (edg3[i]->end->z == edg3[j]->end->z)) {
					edg3[j]->used++;
					cnt++;
					cnt++;
					cnt++;
					cnt++;
					/*
					ffout << "v " << edg3[i]->r->x << " " << edg3[i]->r->y << " " << edg3[i]->r->z << " \n";
					ffout << "v " << edg3[i]->l->x << " " << edg3[i]->l->y << " " << edg3[i]->l->z << " \n";
					ffout << "v " << edg3[j]->r->x << " " << edg3[j]->r->y << " " << edg3[j]->r->z << " \n";
					ffout << "v " << edg3[j]->l->x << " " << edg3[j]->l->y << " " << edg3[j]->l->z << " \n";
					*/
					ffout << "v " << edg3[i]->l->x << " " << edg3[i]->l->y << " " << edg3[i]->l->z << " \n";
					if (edg3[i]->l->x > 0) normx = 1; else normx = -1;//
					if (edg3[i]->l->y > 0) normy = 1; else normy = -1;//
					if (edg3[i]->l->z > 0) normz = 1; else normz = -1;//
					//ffout << "vn " << normx << " " << normy << " " << normz << " \n";//
					normc++;

					ffout << "v " << edg3[i]->r->x << " " << edg3[i]->r->y << " " << edg3[i]->r->z << " \n";
					if (edg3[i]->r->x > 0) normx = 1; else normx = -1;
					if (edg3[i]->r->y > 0) normy = 1; else normy = -1;
					if (edg3[i]->r->z > 0) normz = 1; else normz = -1;
					//ffout << "vn " << normx << " " << normy << " " << normz << " \n";
					normc++;

					ffout << "v " << edg3[j]->r->x << " " << edg3[j]->r->y << " " << edg3[j]->r->z << " \n";
					if (edg3[j]->r->x > 0) normx = 1; else normx = -1;
					if (edg3[j]->r->y > 0) normy = 1; else normy = -1;
					if (edg3[j]->r->z > 0) normz = 1; else normz = -1;
					//ffout << "vn " << normx << " " << normy << " " << normz << " \n";
					normc++;

					ffout << "v " << edg3[j]->l->x << " " << edg3[j]->l->y << " " << edg3[j]->l->z << " \n";
					if (edg3[j]->l->x > 0) normx = 1; else normx = -1;
					if (edg3[j]->l->y > 0) normy = 1; else normy = -1;
					if (edg3[j]->l->z > 0) normz = 1; else normz = -1;
					//ffout << "vn " << normx << " " << normy << " " << normz << " \n";
					normc++;
				}
			}
			ffout << "usemtl ground_" << rand() % 7 + 1 << " \n";
			ffout << "f ";
			prev++;
			prevc++;
			while (prev <= cnt) {
				ffout << prev << /*"//" << prevc <<*/ " ";
				prev++;
				prevc++;
			}
			ffout << std::endl;
		
	}
	
	ffout << "vn " << "0 0 1 \n";
	for (int i = 0; i < *m; i++) {
		if (edg3[i]->flag == true) {
			
			ffout << "v " << edg3[i]->l->x << " " << edg3[i]->l->y << " " << edg3[i]->l->z << " \n";
			ffout << "v " << edg3[i]->r->x << " " << edg3[i]->r->y << " " << edg3[i]->r->z << " \n";
			ffout << "v " << center->x << " " << center->y << " " << center->z << " \n";
			ffout << "usemtl ground_" << rand() % 7 + 1 << " \n";
			cnt++;
			ffout << "f " << cnt << "//" << "1" << " ";
			cnt++;
			ffout << cnt << "//" << "1" << " ";
			cnt++;
			ffout << cnt << "//" << "1" << " \n";

			ffout << "usemtl ground_" << rand() % 7 + 1 << " \n";
			ffout << "f " << cnt << "//" << "1" << " ";
			cnt--;
			ffout << cnt << "//" << "1" << " ";
			cnt--;
			ffout << cnt << "//" << "1" << " \n";
			cnt++; cnt++;

		}
	}
	ffout << "usemtl ground_8\n";
	
	//triangl
	for (int i = 0; i < *m; i++) { 
			fout << "v " << edg3[i]->l->x << " " << edg3[i]->l->y << " " << edg3[i]->l->z << " \n";
			fout << "v " << edg3[i]->r->x << " " << edg3[i]->r->y << " " << edg3[i]->r->z << " \n";
			count++;
			fout << "l " << count << " ";
			count++;
			fout << count << " \n";
		}
			
			
	for (int i = 0; i < *m; i++) { 
			if (edg3[i]->flag == true) {
				
				fout << "v " << edg3[i]->l->x << " " << edg3[i]->l->y << " " << edg3[i]->l->z << " \n";
				fout << "v " << center->x << " " << center->y << " " << center->z << " \n";
				count++;
				fout << "l " << count << " ";
				count++;
				fout << count << " \n";
				
				fout << "v " << edg3[i]->r->x << " " << edg3[i]->r->y << " " << edg3[i]->r->z << " \n";
				fout << "v " << center->x << " " << center->y << " " << center->z << " \n";
				count++;
				fout << "l " << count << " ";
				count++;
				fout << count << " \n";				
			}
	}
	int count2 = 0;
	//voronoi
	
	for (int i = 0; i < *m; i++) {
			
			fout2 << "v " << edg3[i]->start->x << " " << edg3[i]->start->y << " " << edg3[i]->start->z << " \n";
			fout2 << "v " << edg3[i]->end->x << " " << edg3[i]->end->y << " " << edg3[i]->end->z << " \n";
			count2++;
			fout2 << "l " << count2 << " ";
			count2++;
			fout2 << count2 << " \n";	
	}
	
	for (int i = 0; i < *m; i++) { 
		for (int j = i + 1; j < *m; j++) {
			if (edg3[i]->start->z >= 0 || edg3[i]->end->z >= 0)
			{
				if (edg3[i]->flag == true && edg3[j]->flag == true) {
					if ((edg3[i]->l->x == edg3[j]->l->x && edg3[i]->l->y == edg3[j]->l->y && edg3[i]->l->z == edg3[j]->l->z) || (edg3[i]->l->x == edg3[j]->r->x && edg3[i]->l->y == edg3[j]->r->y && edg3[i]->l->z == edg3[j]->r->z) || (edg3[i]->r->x == edg3[j]->l->x && edg3[i]->r->y == edg3[j]->l->y && edg3[i]->r->z == edg3[j]->l->z) || (edg3[i]->r->x == edg3[j]->r->x && edg3[i]->r->y == edg3[j]->r->y && edg3[i]->r->z == edg3[j]->r->z)) {
						if ((edg3[i]->start->z >= edg3[i]->end->z) && (edg3[j]->start->z >= edg3[j]->end->z)) {
							fout2 << "v " << edg3[i]->start->x << " " << edg3[i]->start->y << " " << edg3[i]->start->z << " \n";
							fout2 << "v " << edg3[j]->start->x << " " << edg3[j]->start->y << " " << edg3[j]->start->z << " \n";
							count2++;
							fout2 << "l " << count2 << " ";
							count2++;
							fout2 << count2 << " \n";
							
							if (edg3[i]->start->z >= edg3[j]->start->z) {
								fout2 << "v " << edg3[i]->end->x << " " << edg3[i]->end->y << " " << edg3[i]->end->z << " \n";
								fout2 << "v " << edg3[j]->start->x << " " << edg3[j]->start->y << " " << edg3[j]->start->z << " \n";
								count2++;
								fout2 << "l " << count2 << " ";
								count2++;
								fout2 << count2 << " \n";
							}
							else {
								fout2 << "v " << edg3[i]->start->x << " " << edg3[i]->start->y << " " << edg3[i]->start->z << " \n";
								fout2 << "v " << edg3[j]->end->x << " " << edg3[j]->end->y << " " << edg3[j]->end->z << " \n";
								count2++;
								fout2 << "l " << count2 << " ";
								count2++;
								fout2 << count2 << " \n";
							}
							
						}
						else
							if ((edg3[i]->start->z >= edg3[i]->end->z) && (edg3[j]->end->z >= edg3[j]->start->z)) {
								fout2 << "v " << edg3[i]->start->x << " " << edg3[i]->start->y << " " << edg3[i]->start->z << " \n";
								fout2 << "v " << edg3[j]->end->x << " " << edg3[j]->end->y << " " << edg3[j]->end->z << " \n";
								count2++;
								fout2 << "l " << count2 << " ";
								count2++;
								fout2 << count2 << " \n";
								
								if (edg3[i]->start->z >= edg3[j]->end->z) {
									fout2 << "v " << edg3[i]->end->x << " " << edg3[i]->end->y << " " << edg3[i]->end->z << " \n";
									fout2 << "v " << edg3[j]->end->x << " " << edg3[j]->end->y << " " << edg3[j]->end->z << " \n";
									count2++;
									fout2 << "l " << count2 << " ";
									count2++;
									fout2 << count2 << " \n";
								}
								else {
									fout2 << "v " << edg3[i]->start->x << " " << edg3[i]->start->y << " " << edg3[i]->start->z << " \n";
									fout2 << "v " << edg3[j]->start->x << " " << edg3[j]->start->y << " " << edg3[j]->start->z << " \n";
									count2++;
									fout2 << "l " << count2 << " ";
									count2++;
									fout2 << count2 << " \n";
								}
								
							}
							else
								if ((edg3[i]->end->z >= edg3[i]->start->z) && (edg3[j]->start->z >= edg3[j]->end->z)) {
									fout2 << "v " << edg3[i]->end->x << " " << edg3[i]->end->y << " " << edg3[i]->end->z << " \n";
									fout2 << "v " << edg3[j]->start->x << " " << edg3[j]->start->y << " " << edg3[j]->start->z << " \n";
									count2++;
									fout2 << "l " << count2 << " ";
									count2++;
									fout2 << count2 << " \n";
									
									if (edg3[i]->end->z >= edg3[j]->start->z) {
										fout2 << "v " << edg3[i]->start->x << " " << edg3[i]->start->y << " " << edg3[i]->start->z << " \n";
										fout2 << "v " << edg3[j]->start->x << " " << edg3[j]->start->y << " " << edg3[j]->start->z << " \n";
										count2++;
										fout2 << "l " << count2 << " ";
										count2++;
										fout2 << count2 << " \n";
									}
									else {
										fout2 << "v " << edg3[i]->end->x << " " << edg3[i]->end->y << " " << edg3[i]->end->z << " \n";
										fout2 << "v " << edg3[j]->end->x << " " << edg3[j]->end->y << " " << edg3[j]->end->z << " \n";
										count2++;
										fout2 << "l " << count2 << " ";
										count2++;
										fout2 << count2 << " \n";
									}
									

								}
								else 
									if ((edg3[i]->end->z >= edg3[i]->start->z) && (edg3[j]->end->z >= edg3[j]->start->z)) {
										fout2 << "v " << edg3[i]->end->x << " " << edg3[i]->end->y << " " << edg3[i]->end->z << " \n";
										fout2 << "v " << edg3[j]->end->x << " " << edg3[j]->end->y << " " << edg3[j]->end->z << " \n";
										count2++;
										fout2 << "l " << count2 << " ";
										count2++;
										fout2 << count2 << " \n";
										
										if (edg3[i]->end->z >= edg3[j]->end->z) {
											fout2 << "v " << edg3[i]->start->x << " " << edg3[i]->start->y << " " << edg3[i]->start->z << " \n";
											fout2 << "v " << edg3[j]->end->x << " " << edg3[j]->end->y << " " << edg3[j]->end->z << " \n";
											count2++;
											fout2 << "l " << count2 << " ";
											count2++;
											fout2 << count2 << " \n";
										}
										else {
											fout2 << "v " << edg3[i]->end->x << " " << edg3[i]->end->y << " " << edg3[i]->end->z << " \n";
											fout2 << "v " << edg3[j]->start->x << " " << edg3[j]->start->y << " " << edg3[j]->start->z << " \n";
											count2++;
											fout2 << "l " << count2 << " ";
											count2++;
											fout2 << count2 << " \n";
										}
										
									}
					}
				}
			}
		}
		if (edg3[i]->start->z >= 0 || edg3[i]->end->z >= 0) {
			if (edg3[i]->flag == true) {
				
				if ((edg3[i]->start->z >= edg3[i]->end->z)) {
					fout2 << "v " << edg3[i]->start->x << " " << edg3[i]->start->y << " " << edg3[i]->start->z << " \n";
					fout2 << "v " << center->x << " " << center->y << " " <<center->z << " \n";
					count2++;
					fout2 << "l " << count2 << " ";
					count2++;
					fout2 << count2 << " \n";
				}
				else {
					fout2 << "v " << edg3[i]->end->x << " " << edg3[i]->end->y << " " << edg3[i]->end->z << " \n";
					fout2 << "v " << center->x << " " << center->y << " " << center->z << " \n";
					count2++;
					fout2 << "l " << count2 << " ";
					count2++;
					fout2 << count2 << " \n";			
				}
				
			}
		}
	}
	
	fout.close();
	fout2.close();
	ffout.close();
	ffout2.close();

	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);

	glutInitWindowSize(1200, 800);
	glutInitWindowPosition(200, 200);
	glutCreateWindow("Sphere");

	

	glutDisplayFunc(display);
	glutReshapeFunc(reshape);
	
	glutMainLoop();
	
	
	return 0;
}


