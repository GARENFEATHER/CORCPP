#include<glut.h>
#include<math.h>
#pragma comment(linker, "/subsystem:\"windows\" /entry:\"mainCRTStartup\"")//用于去掉控制台
#define PI 3.141592653589793f
void myDisplay(void)

{
	int i,n=150;
	GLfloat R=0.2f,a=1/(2-2*cos(72*PI/180)),x,fc=0.05f;
	GLfloat bx=a*cos(18*PI/180),by=a*sin(18*PI/180),cy=-bx;
	GLfloat
		pointA[2]={0,a},
		pointB[2]={bx,by},
		pointC[2]={0.5,cy},
		pointD[2]={-0.5,cy},
		pointE[2]={-bx,by};
     glClear(GL_COLOR_BUFFER_BIT);

     //glRectf(-0.5f, -0.5f, 0.5f, 0.5f);
	 
	/* glBegin(GL_POLYGON);
     for(i=0;i<n;i++)
		 glVertex2f(R*cos(2*PI/n*i),R*sin(2*PI/n*i));
	 glEnd();

	 glBegin(GL_LINE_LOOP);
	 glVertex2fv(pointA);
	 glVertex2fv(pointD);
	 glVertex2fv(pointB);
	 glVertex2fv(pointE);
	 glVertex2fv(pointC);
	 glEnd();*/

	 glBegin(GL_LINES);
	 glVertex2f(-1.0f,0.0f);
	 glVertex2f(1.0f,0.0f);
	 glVertex2f(-0.5f,-1.0f);
	 glVertex2f(-0.5f,1.0f);
	 glEnd();

	 glBegin(GL_LINE_STRIP);
	 for(x=-0.5f/fc;x<1.0f/fc;x+=0.01f)
		 glVertex2f(x*fc,4*sin(x+0.5f)*fc);
	 glEnd();
     glFlush();

}

int main(int argc, char *argv[])
{
     glutInit(&argc, argv);
     glutInitDisplayMode(GLUT_RGB | GLUT_SINGLE);
     glutInitWindowPosition(100, 100);
     glutInitWindowSize(640, 480);
     glutCreateWindow("第一个OpenGL程序");
     glutDisplayFunc(&myDisplay);
     glutMainLoop();
     return 0;
}