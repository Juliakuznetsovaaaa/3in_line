#include <glut.h>
#include <GL/gl.h>
#include <cstdlib>
#include <ctime>
#include <iostream>
#include <windows.h>
#include <algorithm>
#include <vector>
using namespace std;

// Размеры окна
int random(int min, int max) {
    return min + rand() % (max - min + 1);
}
// Функция инициализации окна и установки параметров OpenGL
void init() {
    // Установить цвет фона
    glClearColor(0.9f, 0.9f, 0.9f, 1.0f);

    // Установить режим проекции
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();

    // Установить ортографическую проекцию
    glOrtho(0, 600, 0, 600, -1, 1);

    // Включить сглаживание
    glEnable(GL_BLEND);
    glEnable(GL_LINE_SMOOTH);
    glEnable(GL_POLYGON_SMOOTH);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
}