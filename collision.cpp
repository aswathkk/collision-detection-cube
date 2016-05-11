
#include <GLUT/glut.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdarg.h>

struct Cube{

	float wall_color[3], specular[3], shininess[3];
	float x, y, z, roll_z_angle, roll_x_angle, roll_z_up, roll_x_up;
	float roll_z_flag=0, roll_x_flag;
	
	int num_cubes; // No. of cubes to be checked for collision
	Cube *cube[10]; // check collision with these cubes

	Cube(float xx, float yy, float zz, float r, float g, float b) {

		specular[0] = 1;
		specular[1] = 1;
		specular[2] = 1;
		
		shininess[0] = 20;

		wall_color[0] = r;
		wall_color[1] = g;
		wall_color[2] = b;

		x=xx;
		y=yy;
		z=zz;
	}

	void rollZ(int l){
		roll_z_flag = l;
	}

	void rollX(int l){
		roll_x_flag = l;
	}

	void idle(){
		int moveFactor = 10;
		if(roll_z_flag == 1) { // left
			if(!this->isCollide(1, 1)) {
				roll_z_up = 0;
				if(roll_z_angle < 90)
					roll_z_angle += moveFactor;
				else if(roll_z_angle >= 90) {
					roll_z_flag = 0;
					roll_z_angle = 0;
					x -= 1;
				}
			} else {
				roll_z_up = 1;
				if(roll_z_angle < 180)
					roll_z_angle += moveFactor;
				else if(roll_z_angle >= 180) {
					roll_z_flag = 0;
					roll_z_angle = 0;
					roll_z_up = 0;
					x -= 1;
					y += 1;
				}
			}
		} else if(roll_z_flag == 2) { // right
			if(!this->isCollide(1, 2)) {
				roll_z_up = 0;
				if(roll_z_angle > -90)
					roll_z_angle -= moveFactor;
				else if(roll_z_angle >= -90) {
					roll_z_flag = 0;
					roll_z_angle = 0;
					x += 1;
				}
			} else {
				roll_z_up = 1;
				if(roll_z_angle > -180)
					roll_z_angle -= moveFactor;
				else if(roll_z_angle >= -180) {
					roll_z_flag = 0;
					roll_z_angle = 0;
					roll_z_up = 0;
					x += 1;
					y += 1;
				}
			}
		}
		else if(roll_x_flag == 1) {  // down
			if(!this->isCollide(2, 1)) {
				roll_x_up = 0;
				if(roll_x_angle < 90)
					roll_x_angle += moveFactor;
				else if(roll_x_angle >= 90) {
					roll_x_flag = 0;
					roll_x_angle = 0;
					z += 1;
				}
			} else {
				roll_x_up = 1;
				if(roll_x_angle < 180)
					roll_x_angle += moveFactor;
				else if(roll_x_angle >= 180) {
					roll_x_flag = 0;
					roll_x_angle = 0;
					roll_x_up = 0;
					z += 1;
					y += 1;
				}
			}
		} else if(roll_x_flag == 2) { // up
			if(!this->isCollide(2, 2)) {
				roll_x_up = 0;
				if(roll_x_angle > -90)
					roll_x_angle -= moveFactor;
				else if(roll_x_angle >= -90) {
					roll_x_flag = 0;
					roll_x_angle = 0;
					z -= 1;
				}
			} else {
				roll_x_up = 1;
				if(roll_x_angle > -180)
					roll_x_angle -= moveFactor;
				else if(roll_x_angle >= -180) {
					roll_x_flag = 0;
					roll_x_angle = 0;
					roll_x_up = 0;
					z -= 1;
					y += 1;
				}
			}
		}

		if(x >= 10 || x < 0 || z >= 10 || z < 0) // fall condition ( Gravity )
			y -= .1;
		if((y >= 1) && (y > 0.5)) {
			if(y > 1)
				y -= .1;
		}
		if(noSupport() && y > 0)
			y -= .1;
	}

	int noSupport() {
		for(int i = 0; i < num_cubes; i++)
			if(x == cube[i]->x && z == cube[i]->z)
				return 0;
		return 1;
	}

	void draw() {
		if(y > -5) { // bounding condition to reduce computaion
			idle();

			glPushMatrix();
			glMaterialfv(GL_FRONT, GL_AMBIENT, wall_color);
			glMaterialfv(GL_FRONT, GL_DIFFUSE, wall_color);
			glMaterialfv(GL_FRONT, GL_SPECULAR, specular);
			glMaterialfv(GL_FRONT, GL_SHININESS, shininess);

			glTranslatef(x + .5, y + .5, z + .5);
			if(roll_z_flag == 1) {
				if(roll_z_up == 0) {
					glTranslatef(-.5, -.5, 0);
					glRotatef(roll_z_angle, 0, 0, 1);
					glTranslatef(.5, .5, 0);
				} else {
					glTranslatef(-.5, .5, 0);
					glRotatef(roll_z_angle, 0, 0, 1);
					glTranslatef(.5, -.5, 0);
				}
			} else if(roll_z_flag == 2) {
				if(roll_z_up == 0) {
					glTranslatef(.5, -.5, 0);
					glRotatef(roll_z_angle, 0, 0, 1);
					glTranslatef(-.5, .5, 0);
				} else {
					glTranslatef(.5, .5, 0);
					glRotatef(roll_z_angle, 0, 0, 1);
					glTranslatef(-.5, -.5, 0);
				}
			}
			if(roll_x_flag == 1) {
				if(roll_x_up == 0) {
					glTranslatef(0, -.5, .5);
					glRotatef(roll_x_angle, 1, 0, 0);
					glTranslatef(0, .5, -.5);
				} else {
					glTranslatef(0, .5, .5);
					glRotatef(roll_x_angle, 1, 0, 0);
					glTranslatef(0, -.5, -.5);
				}
			} else if(roll_x_flag == 2) {
				if(roll_x_up == 0) {
					glTranslatef(0, -.5, -.5);
					glRotatef(roll_x_angle, 1, 0, 0);
					glTranslatef(0, .5, .5);
				} else {
					glTranslatef(0, .5, -.5);
					glRotatef(roll_x_angle, 1, 0, 0);
					glTranslatef(0, -.5, .5);
				}
			}
			glutSolidCube(1);
			glPopMatrix();
		}
	}
	int isCollide(int d, int l) {
		for(int i = 0; i < num_cubes; i++) {
			Cube *c = cube[i];
			if(y >= 0.9)
				return 0;
			if(d == 1) {
				if((l == 1)&&(c->x == x-1 && c->z == z))
					return 1;
				else if((l == 2)&&(c->x == x+1 && c->z == z))
					return 1;
			} else if(d == 2) {
				if((l == 1)&&(c->z == z+1 && c->x == x))
					return 1;
				else if((l == 2)&&(c->z == z-1 && c->x == x))
					return 1;
			}
		}
		return 0;
	}
	void setCollisions(int n, ...) {
		num_cubes = n;
		va_list args;
		va_start(args, n);
		for(int i = 0; i < n; i++) 
			cube[i] = va_arg(args, Cube*);
		va_end(args);
	}
};

Cube c1(4, 0, 6, 1, 0, 0),
	c2(6, 0, 4, 0, 1, 0),
	c3(5, 0, 5, 0, 0, 1);

int win_width = 600, win_height = 600;

void plane() {
	glPushMatrix();

	glDisable(GL_LIGHTING);
	glDisable(GL_LIGHT0);

	glBegin(GL_LINES);
	glColor3f(.8, .8, .8);
	for(int i = 0; i < 10; i++) {
		glVertex3f(i, 0, 0);
		glVertex3f(i, 0, 10);
		glVertex3f(0, 0, i);
		glVertex3f(10, 0, i);
	}
	glEnd();

	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);

	float color[]={1, 1, 1}, specular[] = {0, 0, 1, 1}, shininess[] = {50};
		glMaterialfv(GL_FRONT, GL_AMBIENT, color);
		glMaterialfv(GL_FRONT, GL_DIFFUSE, color);
		glMaterialfv(GL_FRONT, GL_SPECULAR, specular);
		glMaterialfv(GL_FRONT, GL_SHININESS, shininess);

	glBegin(GL_POLYGON);
	glNormal3f(0, 1, 0);
	glVertex3f(0, 0, 0);
	glVertex3f(10, 0, 0);
	glVertex3f(10, 0, 10);
	glVertex3f(0, 0, 10);
	glEnd();

	glPopMatrix();
}

void light() {
	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);
	
	float position[] = {10, 10, 10, 1},
		diffuse_l[] = {.8, .8, .8, 1},
		ambient_l[] = {.2, .2, .2, 1};

	glLightfv(GL_LIGHT0, GL_POSITION, position);
	glLightfv(GL_LIGHT0, GL_AMBIENT, ambient_l);
	glLightfv(GL_LIGHT0, GL_DIFFUSE, diffuse_l);
}

void display(){
	glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);
	glLoadIdentity();
	gluLookAt(12, 5, 15, 2, 0, 2, 0, 1, 0);
	light();
	plane();
	c1.draw();
	c2.draw();
	c3.draw();
	glutSwapBuffers();
	glutPostRedisplay();
}

float ang;
void keyboard(unsigned char k, int x, int y) {
	switch(k) {
		case 27:
		case 'q':
		case 'Q':
			exit(0);
			break;

		case 'a':
			c2.rollZ(1);
			break;

		case 'd':
			c2.rollZ(2);
			break;

		case 's':
			c2.rollX(1);
			break;

		case 'w':
			c2.rollX(2);
			break;

		case 'j':
			c1.rollZ(1);
			break;

		case 'l':
			c1.rollZ(2);
			break;

		case 'k':
			c1.rollX(1);
			break;

		case 'i':
			c1.rollX(2);
			break;
	}
}

void reshape(int w, int h) {
	win_width = w;
	win_height = h;
	glViewport(0, 0, w, h);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(45, (float)w / (float)h, .1, 1000);
	glMatrixMode(GL_MODELVIEW);
}

void init() {

	c1.setCollisions(3, &c2, &c3);
	c2.setCollisions(3, &c1, &c3);

	glClearColor(0, 0, 0, 0);

	glEnable(GL_DEPTH_TEST);
	glShadeModel(GL_SMOOTH);
	glEnable(GL_NORMALIZE);

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(45, (float)win_width/(float)win_height, .1, 1000);
	glMatrixMode(GL_MODELVIEW);
}

int main(int argc, char **argv) {

	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE | GLUT_DEPTH);
	glutInitWindowSize(win_width, win_height);
	glutInitWindowPosition(300, 300);
	glutCreateWindow("Maze Runner");
	glutDisplayFunc(display);	
	glutKeyboardFunc(keyboard);
	init();
	glutReshapeFunc(reshape);
	//glutFullScreen();
	glutMainLoop();
}
