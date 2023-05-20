#include "Source.cpp"
#include "Fruits.hpp"

void initl() {
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

int main(int argc, char** argv) {
    //размеры окна
    const int WIDTH = 600;
    const int HEIGHT = 600;
    // Инициализация GLUT
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA);
    glutInitWindowSize(WIDTH, HEIGHT);
    glutCreateWindow("Fruits");

    // Инициализация OpenGL
    initl();
    // Заполнение матрицы фруктов случайными фруктами
    fruits::fillFruits();
    glutDisplayFunc(fruits::drawField);
    glutMouseFunc(fruits::mouse);
    // Запуск цикла обработки событий
    glutMainLoop();
    return 0;
}
