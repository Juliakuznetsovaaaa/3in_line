#pragma once
#include "Fruits.hpp"

class Bonus {
public:
    virtual void create(int x, int y) = 0;
    virtual void use(int x, int y) = 0;
};

class Bomb : public Bonus {
public:

    void create(int x, int y);
    void use(int x, int y) override;
};

class Brush : public Bonus {
public:
    void create(int x, int y);
    void use(int x, int y) override;

};