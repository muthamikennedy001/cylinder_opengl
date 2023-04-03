#include <GL/glut.h>
#include <math.h>

GLfloat radius = 0.5f; // radius of the cylinder
GLfloat height = 1.0f; // height of the cylinder
GLint slices = 20;     // number of slices used to draw the cylinder
GLint stacks = 20;     // number of stacks used to draw the cylinder

void display()
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    glPushMatrix();
    glTranslatef(0.0f, 0.0f, -height / 2.0f); // move the cylinder down to align with the XY plane

    glBegin(GL_QUAD_STRIP);
    for (int j = 0; j <= stacks; j++)
    {
        for (int i = 0; i <= slices; i++)
        {
            GLfloat angle = i * 2.0f * M_PI / slices; // compute the angle of the current slice
            GLfloat x = radius * cos(angle);          // compute the x-coordinate of the current vertex
            GLfloat y = radius * sin(angle);          // compute the y-coordinate of the current vertex
            GLfloat z = j * height / stacks;          // compute the z-coordinate of the current vertex

            glNormal3f(x, y, 0.0f); // set the normal vector of the current vertex
            glVertex3f(x, y, z);    // draw the current vertex

            glNormal3f(x, y, 0.0f);                // set the normal vector of the corresponding vertex in the next stack
            glVertex3f(x, y, z + height / stacks); // draw the corresponding vertex in the next stack
        }
    }
    glEnd();

    glPopMatrix();

    glutSwapBuffers();
}

int main(int argc, char **argv)
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
    glutInitWindowSize(800, 800);
    glutCreateWindow("Cylinder");

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(60, 1, 0.1, 100);

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    gluLookAt(0, 0, 5, 0, 0, 0, 0, 1, 0);

    glEnable(GL_DEPTH_TEST);

    // set the color of the cylinder to blue
    glColor3f(0.0f, 0.0f, 1.0f);

    glutDisplayFunc(display);

    glutMainLoop();

    return 0;
}
