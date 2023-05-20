#pragma once
#include "Fruits.hpp"
#include "Source.cpp"
#include "Bonus.hpp"
#include "Fruits.cpp"

void Bomb::create(int x, int y) {
    fruit[x][y] = 7;
}
void Bomb::use(int x, int y) {
    // ”ничтожаем 5 произвольных квадратов на поле

    for (int i = 0; i < 5; ++i) {
        int a = random(0, 5);
        int b = random(0, 5);
        fruits::fruit[a][b] = 0;
    }

    // ”ничтожаем квадрат, куда попала бомба
    fruits::fruit[x][y] = 0;
}
void Brush::create(int x, int y) {
    fruits::fruit[x][y] = 8;
}
void Brush::use(int x, int y) {
    // ”ничтожаем 5 произвольных квадратов на поле

    for (int i = 0; i < 2; ++i) {
        int a = random(0, 5);
        int b = random(0, 5);
        fruit[a][b] = random(1, 6);
    }
    // ”ничтожаем квадрат, куда попала бомба
    fruit[x][y] = random(1, 6);

}