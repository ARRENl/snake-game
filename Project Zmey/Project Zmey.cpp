#include "StdAfx.h"
#include <ctime>
#include <glut.h>
#include <random>
#include <Windows.h>
#include <stdlib.h>

int N=30,M=20;
int Scale=21;

int w = Scale*N;
int h = Scale*M;

unsigned int Speed = 70;

int dir,num=4;

struct
{
  int x;
  int y;
} s[100];

class Fruct
{
  public:
    int x,y;
    void New()
    {
      x=rand() % N;
      y=rand() % M;
    }
    void DrawApple()
    {
      glColor3f(1.0,0.5,0.0);
      glRectf(x*Scale,y*Scale,(x+1)*Scale,(y+1)*Scale);
    }
}m[3]; 

void DrawField()
{
  glColor3f(0.0,1.0,0.0);
  glBegin(GL_LINES);

  for(int i=0; i<w;i+=Scale)
  {
    glVertex2f(i,0);
    glVertex2f(i,h);
  }
  for(int j=0;j<h;j+=Scale)
  {
    glVertex2f(0,j);
    glVertex2f(w,j);
  }
  glEnd();
}

void Tick()
{
  for(int i=num;i>0;--i)
  {
    s[i].x=s[i-1].x;
    s[i].y=s[i-1].y;
  }
  if(dir==0)
    s[0].y+=1;
  if(dir==1)
    s[0].x-=1;
  if(dir==2)
    s[0].x+=1;
  if(dir==3)
    s[0].y-=1;
  for(int i=0;i<3;i++)
    if((s[0].x==m[i].x) && (s[0].y==m[i].y))
    {
      num++;
      m[i].New();
    }
  if(s[0].x>N)
    s[0].x=0;
  if(s[0].y>M)
    s[0].y=0;
  if(s[0].x<0)
    s[0].x=N;
  if(s[0].y<0)
    s[0].y=M;
  for(int i=1;i<num;i++)
    if(s[0].x==s[i].x && s[0].y==s[i].y)
      num=i;
}

void DrawSnake()
{
  glColor3f(0.0,0.0,0.8);
  for(int i=1;i<num;i++)
  {
    glRectf(s[i].x*Scale,s[i].y*Scale,(s[i].x+1)*Scale, (s[i].y+1)*Scale);
  }
}

void DrawHead()
{
  glColor3f(0.8,0.0,0.0);
  glRectf(s[0].x*Scale,s[0].y*Scale,(s[0].x+1)*Scale, (s[0].y+1)*Scale);
}

void MyKeyboard(int key, int a, int b)
{
  switch(key)
  {
    case 101: dir=0;
              break;
    case 102: dir=2;
              break;
    case 100: dir=1;
              break;
    case 103: dir=3;
              break;
  }
}

void KeyboardEvent(unsigned char key, int x, int y)
{   
  switch(key)
  {
    case 'W':
    case 'w': if(dir==3)
                break;
              else dir=0;
              break;
    case 'D':
    case 'd': if(dir==1)
                break;
              else dir=2;
              break;
    case 'A':
    case 'a': if(dir==2)
                break;
              else dir=1;
              break;
    case 'S':
    case 's': if(dir==0)
                break;
              else dir=3;
              break;
    case 'Q':
    case 'q': exit(EXIT_FAILURE);
              break;
    case 'E':
    case 'e': Speed+=50;
              break;
    case 'R':
    case 'r': Speed-=50;
              break;
  }
}

void display()
{
  glClear(GL_COLOR_BUFFER_BIT);
  for(int i=0;i<3;i++)
    m[i].DrawApple();
  DrawHead();
  DrawField();
  DrawSnake();
  glFlush();
}

void timer(int = 0) 
{
  display();
  Tick();
  glutTimerFunc(Speed,timer,0);
}

int main(int argc, char **argv)
{
  srand(time(NULL));
  for(int i=0;i<3;i++)
    m[i].New();
  s[0].x=10;
  s[0].y=10;
  glutInit(&argc, argv);
  glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
  glutInitWindowSize(w,h);
  glutCreateWindow("Моя змея");
  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();
  gluOrtho2D(0,w,0,h);
  glutDisplayFunc(display);
  glutKeyboardFunc(KeyboardEvent);
  glutTimerFunc(50,timer,0);
  glutSpecialFunc(MyKeyboard);
  glutMainLoop();
  return 0;
}
