//Aluno: Vitor de Oliveira Fernandez Araujo
//DRE: 115162509

#include <vector>
#include <iostream>
#include <GL/gl.h>     // The GL Header File
#include <GL/freeglut.h>   // The GL Utility Toolkit (Glut) Header
#include <cmath>
#include <list>

#define SCREEN_HEIGHT 700
#define SCREEN_WIDTH 700

using namespace std;

class Point{
    protected:
        float X;
        float Y;
    public:
        Point(){}

        Point (float x, float y){
            this->X = (2.*x)/SCREEN_WIDTH - 1.;
            this->Y = -(2.*y)/SCREEN_HEIGHT + 1.;
        }

        float getX(){
            return this->X;
        }
        float getY(){
            return this->Y;
        }
        void setX(float x){
            this->X = x;
        }
        void setY(float y){
            this->Y = y;
        }
};

class Vector: public Point{
    float norm;
    public:
        Vector(float x, float y): Point(x,y){
            this->norm = sqrt(pow(this->X,2) + pow(this->Y,2));
        }

        Vector(Point* p1, Point* p2){
            this->X = p2->getX() - p1->getX();
            this->Y = p2->getY() - p1->getY();
            this->norm = sqrt(pow(this->X,2) + pow(this->Y,2));
        }

        //calcula o produto vetorial this X v
        float crossProduct(Vector* v){
            return (this->X)*(v->getY()) - (this->Y)*(v->getX());
        }

        float getNorm(){
            return this->norm;
        }
};


int hullClose = 0;

vector<Point*> points;
vector<Point*> hullVertices;

void reset(){
    for(Point* i: points){
        delete i;
    }
    points.clear();
    if(hullClose){
        hullClose = 0;
    }
}

void mouse(int button, int state, int X, int Y){
    // Respond to mouse button presses.
    if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN && !hullClose){
        points.push_back(new Point(X,Y)); 
        glutPostRedisplay();
    }
}

void closeConvexHull(){
    if(!hullClose){
        hullClose = 1;
        //TODO: implementação do algoritmo de Jarvis

    }else{
        hullClose = 0;
    }

}


void keyboard_cb(unsigned char key, int X, int Y){
    switch (key){
        case 27:     //tecla ESC sai do programa
            glutLeaveMainLoop();
            break;

        case ' ':   //tecla 'Espaço' trava a criação de pontos e forma o fecho convexo
            closeConvexHull();
            glutPostRedisplay();
            break;
        case 'r':   //tecla 'r' limpa tudo o que foi feito
            reset();
            glutPostRedisplay();
            break;
    }
}

void display() {
    glClearColor(0.5, 0.5, 0.5, 0.0);
    glClear(GL_COLOR_BUFFER_BIT);
    
    glPointSize(7.);
    glColor3f(1.0,0.0,0.0);

    glBegin(GL_POINTS);
        
    for(Point* i: points){
        glVertex2f(i->getX(),i->getY());
    }

    glEnd();

    if(hullClose){
        glLineWidth(5.);
        glColor3f(1.0,1.0,1.0);
        glBegin(GL_LINE_STRIP);

        for(Point* i: hullVertices){
            glVertex2f(i->getX(),i->getY());
        }
    }

    glFlush();
    glutSwapBuffers();
}


int main(int argc, char **argv)
{
    glutInit(&argc,argv);
    glutInitWindowSize(SCREEN_WIDTH, SCREEN_HEIGHT);
    glutSetOption(GLUT_ACTION_ON_WINDOW_CLOSE, GLUT_ACTION_CONTINUE_EXECUTION);
    glutCreateWindow("Polygon Test");
    glutKeyboardFunc(keyboard_cb);
    glutMouseFunc(mouse);
    
    glutDisplayFunc(display);
    glutMainLoop();    

    return EXIT_SUCCESS;
}