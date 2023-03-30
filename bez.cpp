#include <windows.h>
#include <iostream>
#include <algorithm>
#include <vector>
#ifdef __APPLE__
#else
#include <GL/glut.h>
#endif

#define HEIGHT 600
#define WIDTH 600

using namespace std;

void init() {
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(0, WIDTH, 0, HEIGHT);
    glClearColor(0, 0, 0, 1);
}

static void drawPoint(int x, int y) {
    glPointSize(2.0f);
    glBegin(GL_POINTS);
        glColor3f(0, 1, 1);
        glVertex2f(x, y);
    glEnd();
    glFlush();
}

void drawBezierCurve(vector<pair<int, int>> points) {
    for(float t = 0; t <= 1; t += 0.001) {
        float t3 = t * t * t, t2 = t * t;
        float x = (-t3 + 3 * t2 - 3 * t + 1) * points[0].first + (3 * t3 - 6 * t2 + 3 * t) * points[1].first + (-3 * t3 + 3 * t2) * points[2].first + t3 * points[3].first;
        float y = (-t3 + 3 * t2 - 3 * t + 1) * points[0].second + (3 * t3 - 6 * t2 + 3 * t) * points[1].second + (-3 * t3 + 3 * t2) * points[2].second + t3 * points[3].second;
        drawPoint(x, y);
     }
}

static void display(void) {
    glClear(GL_COLOR_BUFFER_BIT);
//    drawBezierCurve({make_pair(0, 0), make_pair(WIDTH, 0), make_pair(WIDTH, HEIGHT), make_pair(0, HEIGHT)});
//    drawBezierCurve({make_pair(WIDTH, 0), make_pair(WIDTH, HEIGHT), make_pair(0, HEIGHT), make_pair(0, 0)});
//    drawBezierCurve({make_pair(WIDTH, HEIGHT), make_pair(0, HEIGHT), make_pair(0, 0), make_pair(WIDTH, 0)});
//    drawBezierCurve({make_pair(0, HEIGHT), make_pair(0, 0), make_pair(WIDTH, 0), make_pair(WIDTH, HEIGHT)});
//    drawBezierCurve({make_pair(WIDTH / 2, 0), make_pair(WIDTH, HEIGHT / 2), make_pair(WIDTH / 2, HEIGHT), make_pair(0, HEIGHT / 2)});
//    drawBezierCurve({make_pair(WIDTH, HEIGHT / 2), make_pair(WIDTH / 2, HEIGHT), make_pair(0, HEIGHT / 2), make_pair(WIDTH / 2, 0)});
//    drawBezierCurve({make_pair(WIDTH / 2, HEIGHT), make_pair(0, HEIGHT / 2), make_pair(WIDTH / 2, 0), make_pair(WIDTH, HEIGHT / 2)});
//    drawBezierCurve({make_pair(0, HEIGHT / 2), make_pair(WIDTH / 2, 0), make_pair(WIDTH, HEIGHT / 2), make_pair(WIDTH / 2, HEIGHT)});
    glFlush();
}

static void mouseHandler(int button, int state, int x, int y) {
    static vector<pair<int, int>> points;
    static int c = 0;
    if(button == GLUT_LEFT_BUTTON && state == GLUT_DOWN && c < 4) {
        drawPoint(x, y = HEIGHT - y);
        points.push_back(make_pair(x, y));
        c++;
    }
    if(c == 4) {
        drawBezierCurve(points);
        points.clear();
        c = 0;
    }
    else if(button == GLUT_RIGHT_BUTTON && state == GLUT_DOWN) {
        display();
        points.clear();
        c = 0;
    }
}

int main(int argc, char *argv[])
{
    glutInit(&argc, argv);
    glutInitWindowSize(WIDTH, HEIGHT);
    glutInitWindowPosition(0, 0);
    glutInitDisplayMode(GLUT_RGB | GLUT_SINGLE);
    glutCreateWindow("Bezier Curves");
    init();
    glutDisplayFunc(display);
    glutMouseFunc(mouseHandler);
    glutMainLoop();

    return EXIT_SUCCESS;
}
