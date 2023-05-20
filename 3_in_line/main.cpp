#pragma once

#include "Source.cpp"
#include "Fruits.cpp"

int main(int argc, char** argv) {
    // ������������� GLUT
    const int WIDTH = 600;
    const int HEIGHT = 600;
    const float CELL_SIZE = 100.0f;
    const int ROWS = 6;
    const int COLS = 6;
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA);
    glutInitWindowSize(WIDTH, HEIGHT);
    glutCreateWindow("Fruits");

    // ������������� OpenGL
    init();

    // ���������� ������� ������� ���������� ��������
    fruits::fillFruits();

    // ����������� ������� ��������� �������
    glutDisplayFunc(drawField);
    //glutKeyfruitsFunc(keyfruits);
    glutMouseFunc(mouse);

    // ������ ����� ��������� �������
    glutMainLoop();

    return 0;
}
