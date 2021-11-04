//
// Created by Adam Ludwiczak on 08/06/2021.
//

#include "board.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int create_board(struct board_t **board, int width,int height)
{
    if (board == NULL || width < 1 || height < 1) return 1;

    *board = malloc(sizeof(struct board_t));
    if (board == NULL) return 2;
    char **mBoard;

    mBoard = malloc(height * sizeof(char*));
    if (mBoard == NULL)
    {
        free(*board);
        return 2;
    }

    for (int i = 0; i < height; ++i)
    {
        *(mBoard + i) = malloc((width + 1) * sizeof(char));
        if (*(mBoard + i) == NULL)
        {
            for (int j = 0; j < i; ++j)
            {
                free(*(mBoard + j));
            }
            free(mBoard);
            free(*board);
            return 2;
        }
    }

    for (int i = 0; i < height; ++i)
    {
        for (int j = 0; j < width; ++j)
        {
            *(*(mBoard + i) + j) = '.';
        }
        *(*(mBoard + i) + width) = '\0';
    }

    (*board)->board = mBoard;
    (*board)->width = width;
    (*board)->height = height;
    (*board)->is_init = 0;
    (*board)->move_player_up = move_player_up;
    (*board)->move_player_down = move_player_down;
    (*board)->move_player_left = move_player_left;
    (*board)->move_player_right = move_player_right;

    return 0;
}
void display_board(const struct board_t *board)
{
    if (board == NULL || board->board == NULL || board->height < 1 || board->width < 1) return;

    for (int i = 0; i < board->height; ++i)
    {
        for (int j = 0; j < board->width; ++j)
        {
            printf("%c", *(*(board->board + i) + j));
        }
        printf("\n");
    }
}

void free_board(struct board_t *board)
{
    if (board == NULL || board->board == NULL || board->height < 1 || board->width < 1) return;

    for (int i = 0; i < board->height; ++i)
    {
        free(*(board->board + i));
    }
    free(board->board);
    board->board = NULL;
    free(board);
}

int set_player(struct board_t *board, int x, int y)
{
    if (board == NULL || board->board == NULL || x > board->width - 1|| y > board->height - 1 || board->is_init == 1 ||
        x < 0 || y < 0) return 1;

    board->player.x = x;
    board->player.y = y;
    *(*(board->board + y) + x) = '@';
    board->is_init = 1;

    return 0;
}

struct board_t* move_player_up(struct board_t* board)
{
    if (board == NULL || board->board == NULL || board->height < 1 || board->width < 1 || board->is_init == 0 ||
        board->player.x < 0 || board->player.y < 0 || board->player.x > board->width - 1 || board->player.y > board->height - 1)
        return NULL;

    int currentX =  board->player.x;
    int currentY =  board->player.y;

    int newX = currentX;
    int newY = currentY;

    newY--;
    if (newY < 0) newY = board->height - 1;

    board->player.x = newX;
    board->player.y = newY;

    *(*(board->board + currentY) + currentX) = '.';
    *(*(board->board + newY) + newX) = '@';

    return board;
}
struct board_t* move_player_down(struct board_t* board)
{
    if (board == NULL || board->board == NULL || board->height < 1 || board->width < 1 || board->is_init == 0 ||
        board->player.x < 0 || board->player.y < 0 || board->player.x > board->width - 1 || board->player.y > board->height - 1)
        return NULL;

    int currentX =  board->player.x;
    int currentY =  board->player.y;

    int newX = currentX;
    int newY = currentY;

    newY++;
    if (newY >= board->height) newY = 0;

    board->player.x = newX;
    board->player.y = newY;

    *(*(board->board + currentY) + currentX) = '.';
    *(*(board->board + newY) + newX) = '@';

    return board;
}
struct board_t* move_player_left(struct board_t* board)
{
    if (board == NULL || board->board == NULL || board->height < 1 || board->width < 1 || board->is_init == 0 ||
        board->player.x < 0 || board->player.y < 0 || board->player.x > board->width - 1 || board->player.y > board->height - 1)
        return NULL;

    int currentX =  board->player.x;
    int currentY =  board->player.y;

    int newX = currentX;
    int newY = currentY;

    newX--;
    if (newX < 0) newX = board->width - 1;

    board->player.x = newX;
    board->player.y = newY;

    *(*(board->board + currentY) + currentX) = '.';
    *(*(board->board + newY) + newX) = '@';

    return board;
}
struct board_t* move_player_right(struct board_t* board)
{
    if (board == NULL || board->board == NULL || board->height < 1 || board->width < 1 || board->is_init == 0 ||
        board->player.x < 0 || board->player.y < 0 || board->player.x > board->width - 1 || board->player.y > board->height - 1)
        return NULL;

    int currentX =  board->player.x;
    int currentY =  board->player.y;

    int newX = currentX;
    int newY = currentY;

    newX++;
    if (newX >= board->width) newX = 0;

    board->player.x = newX;
    board->player.y = newY;

    *(*(board->board + currentY) + currentX) = '.';
    *(*(board->board + newY) + newX) = '@';

    return board;
}