#pragma once

#include "Fruits.hpp"
#include "Source.cpp"
#include "Bonus.hpp"

void fruits::fillFruits() {
    // ������������� ���������� ��������� �����
    srand(time(NULL));

    // ���� �� �������
    for (int row = 0; row < 6; row++) {
        // ���� �� ��������
        for (int col = 0; col < 6; col++) {
            // ��������� ���������� ���� ������
            fruit[row][col] = random(1, NUM_FRUITS);
        }
    }
}

void fruits::drawField() {
    // �������� �����
    glClear(GL_COLOR_BUFFER_BIT);

    // ���� �� �������
    for (int row = 0; row < 6; row++) {
        // ���� �� ��������
        for (int col = 0; col < 6; col++) {
            // ���������� ��������� �������� ������ ���� ������
            float x = col * CELL_SIZE;
            float y = row * CELL_SIZE;

            // ����������� ����� ������ � ����������� �� ���� ������
            switch (fruit[row][col]) {

            case 0:
                glColor4f(1.0f, 1.0f, 1.0f, 0.0f);//white
                break;
            case 1:
                glColor3f(0.0f, 0.5f, 1.0f);//baby blue

                //glColor3f(1.0f, 0.0f, 0.0f); // �������
                break;
            case 2:
                //glColor3f(0.0f, 0.1f, 0.0f);
                glColor3f(0.0f, 1.0f, 0.0f); // �������
                break;
            case 3:
                glColor3f(0.0f, 0.0f, 1.0f); // �����
                break;
            case 4:
                glColor3f(1.0f, 1.0f, 0.0f); // ������
                break;
            case 5:
                //glColor3f(0.1f, 0.1f, 0.0f);
                glColor3f(1.0f, 0.0f, 1.0f); // ����������
                break;
            case 6:
                glColor3f(0.0f, 1.0f, 1.0f); // �������
                break;
            case 7:
                glColor3f(1.0f, 0.0f, 0.0f);//red
                break;
            case 8:
                glColor3f(0.0f, 0.0f, 0.0f);
                break;
            default:
                break;
            }

            // ��������� �������������� � ������� ������� glRectf()
            glRectf(x, y, x + CELL_SIZE, y + CELL_SIZE);
        }
    }

    // �������� �����
    glutSwapBuffers();
}


// ������� ��� ������ �������� ����
void fruits::printfruits() {
    for (int i = 0; i < ROWS; i++) {
        for (int j = 0; j < COLS; j++) {
            std::cout << fruit[i][j] << " ";
        }
        std::cout << std::endl;
    }
    std::cout << std::endl;
}

void fruits::shiftDown() {
    for (int col = 0; col < 6; col++) {
        for (int row = 0; row < 6; row++) {

            if (fruit[row][col] == 0) {
                bool isChange = false;
                for (int newrow = row + 1; newrow < 6; newrow++) {
                    if (fruit[newrow][col] != 0) {
                        fruit[row][col] = fruit[newrow][col];
                        fruit[newrow][col] = 0;
                        isChange = true;
                        break;
                    }
                }

                if (!isChange) {
                    fruit[row][col] = random(1, 6);
                }

            }
        }
    }
}


int mark[6][6];
void fruits::findGroups(int row, int col, int dx, int dy) {
    int newRow = row + dx;
    int newCol = col + dy;
    int count = 0;

    while (newRow < 6 && newCol < 6 && newRow >= 0 && newCol >= 0 && fruit[newRow][newCol] == fruit[row][col]) {

        mark[5 - newRow][newCol] = 1;
        newRow += dx;
        newCol += dy;
        count = 1;

    }
}

bool fruits::delGroups() {
    bool is_change = false;
    for (int c = 1; c < 7; c++) {
        for (int i = 0; i < ROWS; i++) {
            for (int j = 0; j < COLS; j++) {
                mark[i][j] = 0;
            }
        }
        int col = 0;
        int row = 0;
        while (col <= 5 && row < 6) {


            if ((fruit[row][col] == 7 || fruit[row][col] == 8 || fruit[row][col] == c) && (row < 4 && fruit[row + 1][col] == c && fruit[row + 2][col] == c || row >= 1 && row <= 4 && fruit[row + 1][col] == c && fruit[row - 1][col] == c || row>1 && fruit[row - 1][col] == c && fruit[row - 2][col] == c || col < 4 && fruit[row][col + 1] == c && fruit[row][col + 2] == c || col >= 1 && col <= 4 && fruit[row][col + 1] == c && fruit[row][col - 1] == c || col >= 1 && fruit[row][col - 1] == c && fruit[row][col - 2] == c)) {
                mark[5 - row][col] = 1;
                is_change = true;
                findGroups(row, col, 1, 0);
                findGroups(row, col, 0, 1);
                findGroups(row, col, -1, 0);
                findGroups(row, col, 0, -1);
            }
            if (row == 5) {
                col += 1;
                row = 0;
            }
            else {
                row += 1;
            }

        }
        cout << endl;

        for (int i = 0; i < ROWS; i++) {
            for (int j = 0; j < COLS; j++) {
                if (mark[i][j] == 1) {
                    if (fruit[5 - i][j] == 7) {
                        Bomb bomb;
                        bomb.use(5 - i, j);
                    }
                    else if (fruit[5 - i][j] == 8) {
                        Brush brush;
                        brush.use(5 - i, j);
                    }
                    else {
                        fruit[5 - i][j] = 0;
                    }

                }
            }
        }
    }
    if (is_change) {
        return true;
    }
    return false;
}

// ������� ��������� ������� ����
void fruits::mouse(int button, int state, int x, int y) {
    int arra[6] = { 0, 0, 0, 0, 0, 0 };
    int q = 0;
    // ���� ������ ����� ������ ����
    if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN) {
        // ���������� �������� ������, �� ������� ���� ������

        int row = 6 - y / CELL_SIZE;
        int col = x / CELL_SIZE;
        int tempFruit = fruit[row][col];
        // findGroups(tempFruit);
        cout << q << " " << row << " " << col << endl;
        if (q > 0 && (arra[0] != row || arra[1] != col)) {
            arra[q] = row; q++;
            arra[q] = col; q++;
            arra[q] = tempFruit; q++;
        }
        if (q == 0) {
            arra[q] = row; q++;
            arra[q] = col; q++;
            arra[q] = tempFruit; q++;
        }

        // ���������� ���� ������ �� ��������� ����������

        if (q == 6) {
            if ((arra[0] == arra[3] + 1 && arra[1] == arra[4]) || (arra[0] == arra[3] - 1 && arra[1] == arra[4]) || (arra[1] == arra[4] + 1 && arra[0] == arra[3]) || (arra[1] == arra[4] - 1 && arra[0] == arra[3])) {
                fruit[arra[0]][arra[1]] = arra[5];
                fruit[arra[3]][arra[4]] = arra[2];
                if (delGroups()) {
                    if (random(1, 10) % 6 == 0) {
                        int xBomb = random(arra[0] - 3, arra[0] + 3);
                        int yBomb = random(arra[1] - 3, arra[1] + 3);
                        Bomb bomb;
                        bomb.create(xBomb, yBomb);
                    }
                    if (random(1, 27) % 8 == 0) {
                        int xBrush = random(arra[3] - 3, arra[3] + 3);
                        int yBrush = random(arra[4] - 3, arra[4] + 3);
                        Brush brush;
                        brush.create(xBrush, yBrush);
                    }
                    shiftDown();
                }
                if (delGroups()) {
                    shiftDown();
                }

            }
            cout << "chosen pair" << endl;

            for (int k = 0; k < 6; k++) {
                std::cout << arra[k] << " ";
                arra[k] = 0;
            }
            q = 0;
            std::cout << endl;
        }

    }

    glutPostRedisplay();

}


