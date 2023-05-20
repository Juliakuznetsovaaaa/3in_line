#include "Source.cpp"
#include "Fruits.hpp"

void initl() {
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

int main(int argc, char** argv) {
    //������� ����
    const int WIDTH = 600;
    const int HEIGHT = 600;
    // ������������� GLUT
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA);
    glutInitWindowSize(WIDTH, HEIGHT);
    glutCreateWindow("Fruits");

    // ������������� OpenGL
    initl();
    // ���������� ������� ������� ���������� ��������
    fruits::fillFruits();
    glutDisplayFunc(fruits::drawField);
    glutMouseFunc(fruits::mouse);
    // ������ ����� ��������� �������
    glutMainLoop();
    return 0;
}
