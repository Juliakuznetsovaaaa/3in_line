#pragma once

#include "Source.cpp"
#include "Fruits.cpp"

int main(int argc, char** argv) {
    // Инициализация GLUT
    const int WIDTH = 600;
    const int HEIGHT = 600;
    const float CELL_SIZE = 100.0f;
    const int ROWS = 6;
    const int COLS = 6;
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA);
    glutInitWindowSize(WIDTH, HEIGHT);
    glutCreateWindow("Fruits");

    // Инициализация OpenGL
    init();

    // Заполнение матрицы фруктов случайными фруктами
    fruits::fillFruits();

    // Регистрация функций обработки событий
    glutDisplayFunc(drawField);
    //glutKeyfruitsFunc(keyfruits);
    glutMouseFunc(mouse);

    // Запуск цикла обработки событий
    glutMainLoop();

    return 0;
}
