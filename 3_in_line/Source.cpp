#include <glut.h>
#include <GL/gl.h>
#include <cstdlib>
#include <ctime>
#include <iostream>
#include <windows.h>
#include <algorithm>
#include <vector>
using namespace std;

// ������� ����
int random(int min, int max) {
    return min + rand() % (max - min + 1);
}
// ������� ������������� ���� � ��������� ���������� OpenGL
void init() {
    // ���������� ���� ����
    glClearColor(0.9f, 0.9f, 0.9f, 1.0f);

    // ���������� ����� ��������
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();

    // ���������� ��������������� ��������
    glOrtho(0, 600, 0, 600, -1, 1);

    // �������� �����������
    glEnable(GL_BLEND);
    glEnable(GL_LINE_SMOOTH);
    glEnable(GL_POLYGON_SMOOTH);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
}