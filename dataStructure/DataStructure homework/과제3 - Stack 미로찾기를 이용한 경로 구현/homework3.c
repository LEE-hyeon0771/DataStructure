/*

영상 읽기, 저장, 화면 출력하는 작업은 아래의 코드를 참조함.
https://github.com/psh4204/C_ImageProcessing

*/

#pragma warning(disable:4996)
#define _CRT_SECURE_NO_WARNINGS

#define UC unsigned char
#define MAX_STACK_SIZE 10000

#include <stdio.h>
#include <math.h>
#include <stdlib.h>

#include <conio.h>
#include <Windows.h>

HDC hdc;
HWND hwnd;

UC** m_InImage = NULL;
UC** m_OutImage = NULL;

UC** maze = NULL;
UC** mark = NULL;

int m_inH, m_inW, m_outH, m_outW;

UC** malloc2D(int, int);
void free2D(UC**, int);

void equalImage();
void displayImage();

UC** malloc2D(int  h, int w) {
    UC** mem;
    mem = (UC**)malloc(h * sizeof(UC*));
    for (int i = 0; i < h; i++)
        mem[i] = (UC*)malloc(w * sizeof(UC));

    // 초기화(Clear)
    for (int i = 0; i < h; i++) {
        for (int k = 0; k < w; k++) {
            mem[i][k] = 0;
        }
    }

    return mem;
}

void free2D(UC** memory, int h) {
    if (memory != NULL) {
        for (int i = 0; i < h; i++)
            free(memory[i]);
        free(memory);
    }
}


void openImage() {

    system("cls");

    FILE* fp = fopen("path6_thin.bin", "rb");

    if (fp == NULL) return;

    fseek(fp, 0L, SEEK_END);
    unsigned long size = ftell(fp);

    rewind(fp);

    m_inH = m_inW = (int)sqrt(size);
    m_InImage = malloc2D(m_inH, m_inW);

    printf("\n size=%d, m_inH=%d, m_inW=%d\n", size, m_inH, m_inW);

    for (int i = 0; i < m_inH; i++)
        fread(m_InImage[i], sizeof(UC), m_inW, fp);
    fclose(fp);

    equalImage();

}

void equalImage() {
    // 기존 출력 메모리 해제
    free2D(m_OutImage, m_outH);
    m_outH = m_inH;
    m_outW = m_inW;
    m_OutImage = malloc2D(m_outH, m_outW);
    for (int i = 0; i < m_inH; i++) {
        for (int k = 0; k < m_inW; k++) {
            m_OutImage[i][k] = m_InImage[i][k];
        }
    }
    displayImage();
}

void displayImage() {
    //system("cls");
    int px;
    for (int i = 0; i < m_outH; i++) {
        for (int k = 0; k < m_outW; k++) {
            px = m_OutImage[i][k];
            SetPixel(hdc, k + 200, i + 300, 255 * RGB(1 - px, 1 - px, 1 - px));
        }
    }
}


void create_maze() {

    maze = malloc2D(m_outH, m_outW);
    for (int i = 0; i < m_inH; i++) {
        for (int k = 0; k < m_inW; k++) {
            maze[i][k] = m_InImage[i][k];
        }
    }
}

void create_mark() {

    mark = malloc2D(m_outH, m_outW);
    for (int i = 0; i < m_inH; i++) {
        for (int k = 0; k < m_inW; k++) {
            mark[i][k] = m_InImage[i][k];
        }
    }
}


typedef struct {
    short int row;
    short int col;
    short int dir;
}element;


typedef struct {
    short int vert;
    short int horiz;
} offsets;


typedef struct ArrayStack {

    element stack[MAX_STACK_SIZE];
    int top;

} Stack;

Stack* create() {

    Stack* S = (Stack*)malloc(sizeof(Stack));
    S->top = -1;

    return S;
}


int isFull(Stack* S) {

    return S->top == MAX_STACK_SIZE - 1;

}

int isEmpty(Stack* S) {

    return S->top == -1;
}


element pop(Stack* S) {

    if (isEmpty(S)) {
        printf("error  stack is empty\n");
        exit(0);
    }
    else {

        element e = S->stack[S->top];
        S->top -= 1;
        return e;
    }
}


void push(Stack* S, element x) {

    if (isFull(S)) {
        printf("error stack is full\n");
        return;
    }
    else {
        S->top += 1;
        S->stack[S->top] = x;
    }

}


Stack* path(int row_init, int col_init, int row_target, int col_target) { /* this finds a path and prints it out. */
    int i, row, col, nextRow, nextCol, dir, found = FALSE;
    int top;

    element position;
    offsets move[8];

    Stack* S;
   
    move[0].vert = -1; move[0].horiz = 0;
    move[1].vert = -1; move[1].horiz = 1;
    move[2].vert = 0; move[2].horiz = 1;
    move[3].vert = 1; move[3].horiz = 1;
    move[4].vert = 1; move[4].horiz = 0;
    move[5].vert = 1; move[5].horiz = -1;
    move[6].vert = 0; move[6].horiz = -1;
    move[7].vert = -1; move[7].horiz = -1;


    //mark[1][1] = 1; 

    create_maze();
    create_mark();


    S = create();
    
    // initialize a stack
    position.row = row_init;
    position.col = col_init;
    position.dir = 0;
    push(S, position);


    // 강의 슬라이드에 나오는 while문을 적절히 변형.
    
    top = 0;
    while (top > -1 && !found) {
        position = pop(S);
        
        row = position.row;
        col = position.col;
        dir = position.dir;
        while (dir < 8 && !found) {
            nextRow = row + move[dir].vert;
            nextCol = col + move[dir].horiz;
            if (nextRow == row_target && nextCol == col_target) {
                found = TRUE;
            }
            else if (!maze[nextRow][nextCol] && !mark[nextRow][nextCol]) {
                mark[nextRow][nextCol] = 1;
                
                position.row = row;
                position.col = col;
                position.dir = ++dir;
                push(S, position);
                row = nextRow;
                col = nextCol;
                dir = 0;
            }
            else
                ++dir;
        }
    }

    if (found) { // 경로를 찾았으므로 출력

       /*
       printf("The path is:\n");
       printf("row col \n");
       for (i = 0; i <= S->top; i++)
          printf("%2d%5d\n", S->stack[i].row, S->stack[i].col);
       printf("%2d%5d\n", row, col);
       printf("%2d%5d\n", row_target, col_target);
       */
        printf("[SUCCESS]");

        return S;
    }
    else {
        printf("The maze does not have a path\n");
        exit(0);
    }
}

Stack* pathS1(int row_init, int col_init, int row_target, int col_target) { /* this finds a path and prints it out. */
    int i, row, col, nextRow, nextCol, dir, found = FALSE;
    int top;

    element position;
    offsets move[8];

    Stack* S;
    Stack* S1;
    move[0].vert = -1; move[0].horiz = 0;
    move[1].vert = -1; move[1].horiz = 1;
    move[2].vert = 0; move[2].horiz = 1;
    move[3].vert = 1; move[3].horiz = 1;
    move[4].vert = 1; move[4].horiz = 0;
    move[5].vert = 1; move[5].horiz = -1;
    move[6].vert = 0; move[6].horiz = -1;
    move[7].vert = -1; move[7].horiz = -1;


    //mark[1][1] = 1; 

    create_maze();
    create_mark();


    S = create();
    S1 = create();
    // initialize a stack
    position.row = row_init;
    position.col = col_init;
    position.dir = 0;
    push(S, position);


    // 강의 슬라이드에 나오는 while문을 적절히 변형.

    top = 0;
    while (top > -1 && !found) {
        position = pop(S);
        push(S1, position);
        row = position.row;
        col = position.col;
        dir = position.dir;
        while (dir < 8 && !found) {
            nextRow = row + move[dir].vert;
            nextCol = col + move[dir].horiz;
            if (nextRow == row_target && nextCol == col_target) {
                found = TRUE;
            }
            else if (!maze[nextRow][nextCol] && !mark[nextRow][nextCol]) {
                mark[nextRow][nextCol] = 1;
                
                position.row = row;
                position.col = col;
                position.dir = ++dir;
                push(S, position);
                row = nextRow;
                col = nextCol;
                dir = 0;
            }
            else
                ++dir;
        }
    }

    if (found) { // 경로를 찾았으므로 출력

       /*
       printf("The path is:\n");
       printf("row col \n");
       for (i = 0; i <= S->top; i++)
          printf("%2d%5d\n", S->stack[i].row, S->stack[i].col);
       printf("%2d%5d\n", row, col);
       printf("%2d%5d\n", row_target, col_target);
       */
        printf("[SUCCESS]");

        return S1;
    }
    else {
        printf("The maze does not have a path\n");
        exit(0);
    }
}



void draw_path_on_maze(Stack* S, Stack* S1, char input) {

    // stack의 위치 정보를 영상 화면에 컬러로 출력.
    int px;
    int go = 1;
   
    //SetPixel(hdc, k + 200 + (go) * 150, i + 300, 255 * RGB(1 - px, 1 - px, 1 - px));
    //openImage();
    //displayImage();
    //for (int i = 0; i < S->top; i++) {
       // px = m_OutImage[S->stack[i].row][S->stack[i].col];


        switch (input) {
        case 'a':
            for (int i = 0; i < S->top; i++) {
                px = m_OutImage[S->stack[i].row][S->stack[i].col];
                if (px == 0) {
                    SetPixel(hdc, S->stack[i].col + 200, S->stack[i].row + 300, 255 * RGB(1, 0, 0));
                }
            }
            for (int i = 0; i < S1->top; i++) {
                px = m_OutImage[S1->stack[i].row][S1->stack[i].col];
                if (px == 0) {
                    SetPixel(hdc, S1->stack[i].col + 200, S1->stack[i].row + 300, 255 * RGB(1, 1, 0));
                }
            }
            
            
            

            break;

        case 'b':

            for (int i = 0; i < S->top; i++) {
                px = m_OutImage[S->stack[i].row][S->stack[i].col];
                if (px == 0) {
                    SetPixel(hdc, S->stack[i].col + 370, S->stack[i].row + 300, 255 * RGB(0, 1, 0));
                }
            }
            for (int i = 0; i < S1->top; i++) {
                px = m_OutImage[S1->stack[i].row][S1->stack[i].col];
                if (px == 0) {
                    SetPixel(hdc, S1->stack[i].col + 370, S1->stack[i].row + 300, 255 * RGB(1, 1, 0));
                }
            }
            break;

        case 'c':

            for (int i = 0; i < S->top; i++) {
                px = m_OutImage[S->stack[i].row][S->stack[i].col];
                if (px == 0) {
                    SetPixel(hdc, S->stack[i].col + 470, S->stack[i].row + 300, 255 * RGB(0, 0, 1));
                }
            }
            for (int i = 0; i < S1->top; i++) {
                px = m_OutImage[S1->stack[i].row][S1->stack[i].col];
                if (px == 0) {
                    SetPixel(hdc, S1->stack[i].col + 470, S1->stack[i].row + 300, 255 * RGB(1, 1, 0));
                }
            }
            break;

        case 'd':

            for (int i = 0; i < S->top; i++) {
                px = m_OutImage[S->stack[i].row][S->stack[i].col];
                if (px == 0) {
                    SetPixel(hdc, S->stack[i].col + 570, S->stack[i].row + 300, 255 * RGB(1, 0, 1));
                }
            }
            for (int i = 0; i < S1->top; i++) {
                px = m_OutImage[S1->stack[i].row][S1->stack[i].col];
                if (px == 0) {
                    SetPixel(hdc, S1->stack[i].col + 570, S1->stack[i].row + 300, 255 * RGB(0, 1, 1));
                }
            }
            break;

        case 'e':

            for (int i = 0; i < S->top; i++) {
                px = m_OutImage[S->stack[i].row][S->stack[i].col];
                if (px == 0) {
                    SetPixel(hdc, S->stack[i].col + 670, S->stack[i].row + 300, 255 * RGB(0, 1, 1));
                }
            }
            for (int i = 0; i < S1->top; i++) {
                px = m_OutImage[S1->stack[i].row][S1->stack[i].col];
                if (px == 0) {
                    SetPixel(hdc, S1->stack[i].col + 670, S1->stack[i].row + 300, 255 * RGB(1, 1, 0));
                }
            }
            break;
        }
    }
    



    





    int main(void) {

        system("cls");

        hwnd = GetForegroundWindow();
        hdc = GetWindowDC(hwnd);

        char input = 0;

        int row_init = 15;
        int col_init = 22;

        int row_target1 = 96;
        int col_target1 = 7;

        int row_target2 = 120;
        int col_target2 = 26;

        int row_target3 = 43;
        int col_target3 = 53;

        int row_target4 = 16;
        int col_target4 = 106;

        int row_target5 = 116;
        int col_target5 = 114;


        Stack* S1;
        Stack* S2;


        int px;
        int go = 1;
        while ((input = getchar()) != 'q') {


            switch (input) {
            case 'o':
                openImage();
                break;
            case 'q':
                printf("Quit!");
                break;
            case 'a':
                S1 = path(row_init, col_init, row_target1, col_target1);
                S2 = pathS1(row_init, col_init, row_target1, col_target1);
                draw_path_on_maze(S1, S2, input);
                
                


                break;
            case 'b':
                for (int i = 0; i < m_outH; i++) {
                    for (int k = 0; k < m_outW; k++) {
                        px = m_OutImage[i][k];
                        SetPixel(hdc, k + 200 + (go) * 170, i + 300, 255 * RGB(1 - px, 1 - px, 1 - px));
                    }
                }
                S1 = path(row_init, col_init, row_target2, col_target2);
                S2 = pathS1(row_init, col_init, row_target2, col_target2);
                draw_path_on_maze(S1, S2, input);
                
                break;
            case 'c':
                for (int i = 0; i < m_outH; i++) {
                    for (int k = 0; k < m_outW; k++) {
                        px = m_OutImage[i][k];
                        SetPixel(hdc, k + 200 + (go) * 270, i + 300, 255 * RGB(1 - px, 1 - px, 1 - px));
                    }
                }
                S1 = path(row_init, col_init, row_target3, col_target3);
                S2 = pathS1(row_init, col_init, row_target3, col_target3);
                draw_path_on_maze(S1, S2, input);
                
                
                break;
            case 'd':
                for (int i = 0; i < m_outH; i++) {
                    for (int k = 0; k < m_outW; k++) {
                        px = m_OutImage[i][k];
                        SetPixel(hdc, k + 200 + (go) * 370, i + 300, 255 * RGB(1 - px, 1 - px, 1 - px));
                    }
                }
                S1 = path(row_init, col_init, row_target4, col_target4);
                S2 = pathS1(row_init, col_init, row_target4, col_target4);
                draw_path_on_maze(S1, S2, input);
                
               
                break;
            case 'e':
                for (int i = 0; i < m_outH; i++) {
                    for (int k = 0; k < m_outW; k++) {
                        px = m_OutImage[i][k];
                        SetPixel(hdc, k + 200 + (go) * 470, i + 300, 255 * RGB(1 - px, 1 - px, 1 - px));
                    }
                }
                S1 = path(row_init, col_init, row_target5, col_target5);
                S2 = pathS1(row_init, col_init, row_target5, col_target5);
                draw_path_on_maze(S1, S2, input);
                
               
                break;
            }
        }
    }
