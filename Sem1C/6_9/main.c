#include <stdio.h>
#include "board.h"
int main() {
    struct board_t *board;
    int width, height;
    int playerX, playerY;
    int error;

    printf("Enter width and height of the board: ");
    if (scanf("%d %d", &width, &height) != 2)
    {
        printf("Incorrect input\n");
        return 1;
    }
    if (width < 1 || height < 1)
    {
        printf("Incorrect input data\n");
        return 2;
    }

    error = create_board(&board, width, height);
    if (error == 2)
    {
        printf("Failed to allocate memory\n");
        return 8;
    }

    printf("Enter player's initial coordinates (x, y): ");
    if (scanf("%d %d", &playerX, &playerY) != 2)
    {
        printf("Incorrect input\n");
        free_board(board);
        return 1;
    }
    if (playerX < 0 || playerY < 0 || playerX >= width || playerY >= height)
    {
        printf("Incorrect input data\n");
        free_board(board);
        return 2;
    }

    set_player(board, playerX, playerY);

    display_board(board);

    while(1)
    {
        printf("Choose your action: ");

        //Clear buff
        while(getchar()!='\n'){}

        char input = getchar();

        if (input == 'q') break;

        switch (input)
        {
            case 'w':
                board->move_player_up(board);
                display_board(board);
                break;
            case 's':
                board->move_player_down(board);
                display_board(board);
                break;
            case 'a':
                board->move_player_left(board);
                display_board(board);
                break;
            case 'd':
                board->move_player_right(board);
                display_board(board);
                break;
            default:
                printf("Incorrect choice\n");
                break;
        }
    }

    free_board(board);
    return 0;
}
