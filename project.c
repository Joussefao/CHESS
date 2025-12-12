#include <stdio.h>

#define SIZE 8
#define EMPTY '.'

int my_abs(int x) {
    int a = x;
    if (a < 0)
        a = -a;
    return a;
}

int my_islower(char c) {
    int r = 0;
    if (c >= 'a' && c <= 'z')
        r = 1;
    return r;
}

char my_toupper(char c) {
    char r = c;
    if (c >= 'a' && c <= 'z')
        r = c - 32;
    return r;
}

int in_board(int x, int y) {
    int r = 0;
    if (x >= 0 && x < SIZE && y >= 0 && y < SIZE)
        r = 1;
    return r;
}


void display(char board[SIZE][SIZE]) {
    int i, j;
    printf("\n  0 1 2 3 4 5 6 7\n");
    for (i = 0; i < SIZE; i++) {
        printf("%d ", i);
        for (j = 0; j < SIZE; j++)
            printf("%c ", board[i][j]);
        printf("\n");
    }
}


int valid_pawn(int x, int y,int nx,int ny,char p){
    int valid = 0;

    if (my_islower(p)) { 
        if (nx == x - 1 && ny == y)
            valid = 1;
        if (x == 6 && nx == 4 && ny == y)
            valid = 1;
    } else { 
        if (nx == x + 1 && ny == y)
            valid = 1;
        if (x == 1 && nx == 3 && ny == y)
            valid = 1;
    }

    return valid;
}


int valid_rook(int x,int y,int nx,int ny) {
    int r = 0;
    if (x == nx || y == ny)
        r = 1;
    return r;
}


int valid_bishop(int x,int y,int nx,int ny) {
    int r = 0;
    if (my_abs(nx - x) == my_abs(ny - y))
        r = 1;
    return r;
}


int valid_queen(int x,int y,int nx,int ny) {
    int r = 0;
    if (valid_rook(x, y, nx, ny) 
    || valid_bishop(x, y, nx, ny))
        r = 1;
    return r;
}


int valid_king(int x,int y,int nx,int ny) {
    int r = 0;
    if (my_abs(nx - x) <= 1 
    && my_abs(ny - y) <= 1)
        r = 1;
    return r;
}


int valid_knight(int x,int y,int nx,int ny) {
    int r = 0;
    if ((my_abs(nx - x) == 2 
    && my_abs(ny - y) == 1) ||
        (my_abs(nx - x) == 1 
        && my_abs(ny - y) == 2))
        r = 1;
    return r;
}

int is_valid_move(char piece,int x,int y,int nx,int ny){
    switch (my_toupper(piece)) {
        case 'P': return valid_pawn(x, y, nx, ny, piece);
        case 'T': return valid_rook(x, y, nx, ny);
        case 'F': return valid_bishop(x, y, nx, ny);
        case 'Q': return valid_queen(x, y, nx, ny);
        case 'R': return valid_king(x, y, nx, ny);
        case 'C': return valid_knight(x, y, nx, ny);
        default: return 0;
    }
}

int main() {
    char board[SIZE][SIZE];
    char temp_board[SIZE][SIZE];
    char piece;
    int x, y, nx, ny;
    int i, j;
    int found = 0;

    
    for (i = 0; i < SIZE; i++)
        for (j = 0; j < SIZE; j++)
            board[i][j] = EMPTY;

    
    printf("Choose a piece from: P T F Q R C\n");
    printf("Uppercase = Black | Lowercase = White\n");
    scanf(" %c", &piece);

    int valid_start = 0;
    while (!valid_start) {
        printf("Enter initial position (row column): ");
        scanf("%d %d", &x, &y);

        if (!in_board(x, y)) {
            printf("Invalid board position ❌, try again.\n");
        } else if (my_toupper(piece) == 'P' && 
                   ((piece >= 'A' && piece <= 'Z' 
                    && x == 0) ||
                    (piece >= 'a' && piece <= 'z' 
                        && x == 7))) {
            printf("Invalid pawn start line ❌, try again.\n");
        } else {
            valid_start = 1; 
        }
    }

    board[x][y] = piece;
    display(board);

    
    for (i = 0; i < SIZE; i++)
        for (j = 0; j < SIZE; j++)
            temp_board[i][j] = board[i][j];

    
    for (i = 0; i < SIZE; i++) {
        for (j = 0; j < SIZE; j++) {
            if (!(i == x && j == y) && is_valid_move(piece, x, y, i, j)) {
                temp_board[i][j] = 'o';
                found = 1;
            }
        }
    }

    if (!found) {
        printf("No possible moves ❌\n");
        return 0;
    }

    printf("\nPossible moves are marked with 'o':\n");
    display(temp_board);

    
    int valid_move_chosen = 0;
    while (!valid_move_chosen) {
        printf("\nChoose one of the 'o' positions (row column): ");
        scanf("%d %d", &nx, &ny);

        if ((nx == x && ny == y) || !is_valid_move(piece, x, y, nx, ny)) {
            printf("Invalid move ❌, try again.\n");
        } else {
            printf("Valid move ✅\n");
            board[x][y] = EMPTY;
            board[nx][ny] = piece;
            display(board);
            valid_move_chosen = 1; 
        }
    }

    return 0;
}
