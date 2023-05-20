#include "Fruits.hpp"
#include "Bonus.hpp"

void fruits::fillFruits() {
    srand(time(NULL));
    for (int row = 0; row < 6; row++) {
        for (int col = 0; col < 6; col++) {
            // ��������� ���������� ���� ������
            fruit[row][col] = randomazer(1, NUM_FRUITS);
        }
    }
}

 void fruits::drawField() {
    // �������� �����
    glClear(GL_COLOR_BUFFER_BIT);

    for (int row = 0; row < NUM_FRUITS; row++) {
        for (int col = 0; col < NUM_FRUITS; col++) {
            // ���������� ��������� �������� ������ ���� ������
            float x = col * 100.0f;
            float y = row * 100.0f;

            // ����������� ����� ������ � ����������� �� ���� ������
            switch (fruit[row][col]) {

            case 0:
                glColor4f(1.0f, 1.0f, 1.0f, 0.0f);//white
                break;
            case 1:
                glColor3f(0.0f, 0.5f, 1.0f);//baby blue
                break;
            case 2:
                glColor3f(0.0f, 1.0f, 0.0f); // �������
                break;
            case 3:
                glColor3f(0.0f, 0.0f, 1.0f); // �����
                break;
            case 4:
                glColor3f(1.0f, 1.0f, 0.0f); // ������
                break;
            case 5:
                glColor3f(1.0f, 0.0f, 1.0f); // ����������
                break;
            case 6:
                glColor3f(0.0f, 1.0f, 1.0f); //�������
                break;
            case 7:
                glColor3f(1.0f, 0.0f, 0.0f);//�������
                break;
            case 8:
                glColor3f(0.0f, 0.0f, 0.0f);//������
                break;
            default:
                break;
            }
            // ��������� �������������� � ������� ������� glRectf()
            glRectf(x, y, x + 100.0f, y + 100.0f);
        }
    }
    // �������� �����
    glutSwapBuffers();
}


// ������� ��� ������ �������� ����
void fruits::printfruits() {
    for (int i = 0; i < NUM_FRUITS; i++) {
        for (int j = 0; j < NUM_FRUITS; j++) {
            std::cout << fruit[i][j] << " ";
        }
        std::cout << std::endl;
    }
    std::cout << std::endl;
}

//������� ��� ������ ����� ����
void fruits::shiftDown() {
    for (int col = 0; col < NUM_FRUITS; col++) {
        for (int row = 0; row < NUM_FRUITS; row++) {
            if (fruit[row][col] == 0) {
                bool isChange = false;
                for (int newrow = row + 1; newrow < NUM_FRUITS; newrow++) {
                    if (fruit[newrow][col] != 0) {
                        fruit[row][col] = fruit[newrow][col];
                        fruit[newrow][col] = 0;
                        isChange = true;
                        break;
                    }
                }
                //���� ��� ��������, ��������� ������� ���������� 
                if (!isChange) {
                    fruit[row][col] = randomazer(1, 6);
                }

            }
        }
    }
}


int mark[6][6];
//������� ������, ���� ������� ������� ����
void fruits::findGroups(int row, int col, int dx, int dy) {
    int newRow = row + dx;
    int newCol = col + dy;
    while (newRow < NUM_FRUITS && newCol < NUM_FRUITS && newRow >= 0 && newCol >= 0 && fruit[newRow][newCol] == fruit[row][col]) {
        mark[5 - newRow][newCol] = 1;
        newRow += dx;
        newCol += dy;
    }
}

bool fruits::delGroups() {
    bool is_change = false;
    for (int c = 1; c < 7; c++) {
        for (int i = 0; i < NUM_FRUITS; i++) {
            for (int j = 0; j < NUM_FRUITS; j++) {
                mark[i][j] = 0;
            }
        }
        int col = 0;
        int row = 0;
        //���������� ������� ��� �������� 
        while (col <= NUM_FRUITS-1 && row < NUM_FRUITS) {
            if ((fruit[row][col] == 7 || fruit[row][col] == 8 || fruit[row][col] == c) && (row < 4 && fruit[row + 1][col] == c && fruit[row + 2][col] == c || row >= 1 && row <= 4 && fruit[row + 1][col] == c && fruit[row - 1][col] == c || row>1 && fruit[row - 1][col] == c && fruit[row - 2][col] == c || col < 4 && fruit[row][col + 1] == c && fruit[row][col + 2] == c || col >= 1 && col <= 4 && fruit[row][col + 1] == c && fruit[row][col - 1] == c || col >= 1 && fruit[row][col - 1] == c && fruit[row][col - 2] == c)) {
                mark[5 - row][col] = 1;
                is_change = true;
                //������� �� ������� ������� 3+
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
        //�������� ��������
        for (int i = 0; i < NUM_FRUITS; i++) {
            for (int j = 0; j < NUM_FRUITS; j++) {
                if (mark[i][j] == 1) {
                    //�������� �� �����
                    if (fruit[NUM_FRUITS-1 - i][j] == 7) {
                        Bomb bomb;
                        bomb.use(NUM_FRUITS-1 - i, j);
                    }
                    //�������� �� �����
                    else if (fruit[NUM_FRUITS-1 - i][j] == 8) {
                        Brush brush;
                        brush.use(NUM_FRUITS-1 - i, j);
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
int arra[6] = { 0, 0, 0, 0, 0, 0 };
int q = 0;
// ������� ��������� ������� ����
void fruits::mouse(int button, int state, int x, int y) {
    // ���� ������ ����� ������ ����
    if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN) {
        // ���������� �������� ������, �� ������� ���� ������
        int row = NUM_FRUITS - y / 100.0f;
        int col = x / 100.0f;
        int tempFruit = fruit[row][col];
        //���������� ��������� � ����� 
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
        //�������� �� �� ��� ������� ��� ������
        if (q == NUM_FRUITS) {
            //�������� ����� �� �� �������� �������
            if ((arra[0] == arra[3] + 1 && arra[1] == arra[4]) || (arra[0] == arra[3] - 1 && arra[1] == arra[4]) || (arra[1] == arra[4] + 1 && arra[0] == arra[3]) || (arra[1] == arra[4] - 1 && arra[0] == arra[3])) {
                fruit[arra[0]][arra[1]] = arra[5];
                fruit[arra[3]][arra[4]] = arra[2];
                if (delGroups()) {
                    //������������� �����
                    if (randomazer(1, 10) % 2 == 0) {
                        int xBomb = randomazer(arra[0] - 3, arra[0] + 3);
                        int yBomb = randomazer(arra[1] - 3, arra[1] + 3);
                        Bomb bomb;
                        bomb.create(xBomb, yBomb);
                    }
                    //������������� �����
                    if (randomazer(1, 27) % 8 == 0) {
                        int xBrush = randomazer(arra[3] - 3, arra[3] + 3);
                        int yBrush = randomazer(arra[4] - 3, arra[4] + 3);
                        Brush brush;
                        brush.create(xBrush, yBrush);
                    }
                    shiftDown();
                }
                if (delGroups()) {
                    shiftDown();
                }

            }
            for (int k = 0; k < NUM_FRUITS; k++) {
                arra[k] = 0;
            }
            q = 0;
        }
    }
    glutPostRedisplay();
}
void Bomb::create(int x, int y) {
    fruit[x][y] = 7;
}
void Bomb::use(int x, int y) {
    // ���������� 5 ������������ ��������� �� ����
    for (int i = 0; i < 5; ++i) {
        int a = randomazer(0, 5);
        int b = randomazer(0, 5);
        fruit[a][b] = 0;
    }
    // ���������� �������, ���� ������ �����
    fruit[x][y] = 0;
}
void Brush::create(int x, int y) {
    fruit[x][y] = 8;
}
void Brush::use(int x, int y) {
    // ������������� 3 �������� 
    for (int i = 0; i < 3; ++i) {
        int a = randomazer(0, 5);
        int b = randomazer(0, 5);
        fruit[a][b] = randomazer(1, 6);
    }
    // ���������� �������, ���� ������ �����
    fruit[x][y] = 0;
}



