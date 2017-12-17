#include <time.h>
#include <stdlib.h>
#include <stdio.h>
#include <GL/glut.h>

#include "GLdefs.h"

int p1[10][10] = {0};

void draw_flag(const int i, const int j)
{
    glColor3ub(64, 0, 64);
    glBegin(GL_QUADS);
      glVertex2f(i * size_cell + 1, (j + 1) * size_cell - 1);
      glVertex2f(i * size_cell + 1, j * size_cell + 1);
      glVertex2f((i + 1) * size_cell - 1, j * size_cell + 1);
      glVertex2f((i + 1) * size_cell - 1, (j + 1) * size_cell - 1);
    glEnd();

    glColor3ub(128, 0, 128);
    glBegin(GL_QUADS);
      glVertex2f(i * size_cell + depth_of_cell, (j + 1) * size_cell - depth_of_cell);
      glVertex2f(i * size_cell + depth_of_cell, j * size_cell + depth_of_cell);
      glVertex2f((i + 1) * size_cell - depth_of_cell, j * size_cell + depth_of_cell);
      glVertex2f((i + 1) * size_cell - depth_of_cell, (j + 1) * size_cell - depth_of_cell);
    glEnd();
}

void draw_number(const int i, const int j, const int field, const int num)
{
    glRasterPos2i(field * origin2 + i * size_cell + 1, j * size_cell + 1);
    glDrawPixels(
        size_im,
        size_im,
        GL_RGB,
        GL_UNSIGNED_BYTE,
        im_number[num]);
}

void draw_tree(const int i, const int j, const int field)
{
    glRasterPos2i(field * origin2 + i * size_cell + 1, j * size_cell + 1);
    glDrawPixels(
        size_im,
        size_im,
        GL_RGB,
        GL_UNSIGNED_BYTE,
        im_tree);
}

void draw_body(const int i, const int j, const int field)
{
    glRasterPos2i(field * origin2 + i * size_cell + 1, j * size_cell + 1);
    glDrawPixels(
        size_im,
        size_im,
        GL_RGB,
        GL_UNSIGNED_BYTE,
        im_body);
}

void draw_fox(const int i, const int j, const int field)
{
    glRasterPos2i(field * origin2 + i * size_cell + 1, j * size_cell + 1);
    glDrawPixels(
        size_im,
        size_im,
        GL_RGB,
        GL_UNSIGNED_BYTE,
        im_fox);
}

void draw_empty(const int i, const int j, const int field)
{
    glColor3ub(0, 64, 0);
    glBegin(GL_QUADS);
      glVertex2f(field * origin2 + i * size_cell + 1, (j + 1) * size_cell - 1);
      glVertex2f(field * origin2 + i * size_cell + 1, j * size_cell + 1);
      glVertex2f(field * origin2 + (i + 1) * size_cell - 1, j * size_cell + 1);
      glVertex2f(field * origin2 + (i + 1) * size_cell - 1, (j + 1) * size_cell - 1);
    glEnd();

    glColor3ub(0, 128, 0);
    glBegin(GL_QUADS);
      glVertex2f(field * origin2 + i * size_cell + depth_of_cell, (j + 1) * size_cell - depth_of_cell);
      glVertex2f(field * origin2 + i * size_cell + depth_of_cell, j * size_cell + depth_of_cell);
      glVertex2f(field * origin2 + (i + 1) * size_cell - depth_of_cell, j * size_cell + depth_of_cell);
      glVertex2f(field * origin2 + (i + 1) * size_cell - depth_of_cell, (j + 1) * size_cell - depth_of_cell);
    glEnd();
}

void Display(void) // отрисовка экрана
{
    glClearColor(0, 0, 0, 1);
    glClear(GL_COLOR_BUFFER_BIT);

    int i, j;

    for (i = 0; i < 10; ++i)
    {
        for (j = 0; j < 10; ++j)
        {
            switch(p1[i][j])
            {
            case 2:
                draw_flag(i, j);
                break;
            case 1:
                if (i * 10 + j < 11)
                {
                    draw_number(i, j, 0, i * 10 + j);
                }
                else
                {
                    draw_tree(i, j, 0);
                }
                break;
            case 0:
                draw_empty(i, j, 0);
                break;
            }
        }
    }

    for (i = 0; i < 10; ++i)
    {
        for (j = 0; j < 10; ++j)
        {
            draw_empty(i, j, 1);
        }
    }



    glutSwapBuffers();
    glFinish();
}


void Reshape(GLint w, GLint h) /* Функция вызывается при изменении размеров окна */
{

    /* устанавливаем размеры области отображения */
    glViewport(0, 0, w, h);

    /* ортографическая проекция */
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(0, w, 0, h, -1.0, 1.0);

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
}


void Keyboard(unsigned char key, int x, int y) /* Функция обрабатывает сообщения от клавиатуры */
{
#define ESCAPE '\033'

    if( key == ESCAPE )
        exit(0);
}

void MouseFunc(int button, int state, int x, int y) // читает действия мыши - Истинный int main()
{
    if (state == 0)
    {
        if (y <= height)
        {
            if (x <= 10 * size_cell)
            {
                x /= size_cell;
                y /= size_cell;
                switch( button )
                {
                case GLUT_LEFT_BUTTON:
                    p1[x][9 - y] = 1;
                    break;
                case GLUT_RIGHT_BUTTON:
                    if (p1[x][9 - y] == 0)
                    {
                        p1[x][9 - y] = 2;
                    }
                    break;
                }
            }
        }
    }

    glutPostRedisplay();
}

int main(int argc, char *argv[])
{
    int i, j;
    for (i = 0; i < 10; ++i)
        for (j = 0; j < 10; ++j)
        {
            p1[i][j] = 0;
        }
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_RGB);
    glutInitWindowSize(width, height);
    glutCreateWindow("Fox Hunting 1.0");

    glutDisplayFunc(Display);
    glutReshapeFunc(Reshape);
    glutKeyboardFunc(Keyboard);
    glutMouseFunc(MouseFunc);

    glutMainLoop();

    return 0;
}
