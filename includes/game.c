#include "game.h"
#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <sys/types.h>

//Player-specific functions
player_t* new_player(char *name, uint16_t size){
    if(name == NULL){
        perror("Player is Null : invalid name !");
        return NULL;
    }

    player_t* player = (player_t*)malloc(sizeof(player_t));
    if(player == NULL){
        perror("RAM error !");
        exit(1);
    }

    *player = (player_t){.is_x = false , .name = name , .name_size = size , .score = 0};
    return player;
}

bool make_move(game_t *game, player_t *player, uint8_t x, uint8_t y){
    if(x >= 3 || y >= 3 || x < 0 || y < 0 || game->matrix[x][y]){
        perror("Invalid move !");
        return false;
    }

    game->matrix[x][y] = player->is_x ? 1 : 2 ;
    return true;
}



//Game-specific functions
void free_matrix(void** mat , uint16_t size){
    for(uint16_t i = 0 ; i < size ; i++){
        free(mat[i]);
    }
}

game_t* start_game(gmode_t mode , player_t* p1 , player_t* p2){
    game_t* game ;
    if(p1 == NULL || p2 == NULL)
    {
        perror("Players are not properly set !");
        return NULL;
    }

    game = (game_t*)malloc(sizeof(game_t));
    player_t** players = (player_t**)malloc(2*sizeof(player_t*));
    uint8_t** matrix = (uint8_t**)malloc(3*sizeof(uint8_t*));

    if(game == NULL || players == NULL || matrix == NULL)
        goto ram_error;

    for(uint8_t i = 0 ; i < 3 ; i++){
        matrix[i] = (uint8_t*)malloc(3*sizeof(uint8_t));
        if(matrix[i] == NULL){
            goto ram_error;
        }

        for(uint8_t j = 0 ; j < 3 ; j++){
            matrix[i][j] = 0;
        }
    }

    players[0] = p1;
    players[1] = p2;

    *game = (game_t){.mode = mode , .round = 0 , .players = players , .matrix = matrix};

    ram_error:
        perror("RAM error !");
        exit(1);
}

player_t* check_win(game_t *game){
    uint8_t** mat = game->matrix;

    if(mat == NULL){
        perror("Matrix is Null !");
        exit(1);
    }

    for(uint8_t i = 0 ; i < 3 ; i++)
    {
        uint8_t tmp = mat[i][0];
        if(!(tmp ^ mat[i][1]) && !(tmp ^ mat[i][2]))
            return tmp == 1 ?
                    game->players[0]->is_x ? game->players[0] : game->players[1] :
                    !game->players[0]->is_x ? game->players[0] : game->players[1] ;

        tmp = mat[0][i];
        if(!(tmp ^ mat[1][i]) && !(tmp ^ mat[2][i]))
            return tmp == 1 ?
                    game->players[0]->is_x ? game->players[0] : game->players[1] :
                    !game->players[0]->is_x ? game->players[0] : game->players[1] ;
    }

    if(!(mat[0][0] ^ mat[1][1]) && !(mat[1][1] ^ mat[2][2])
        || !(mat[2][0] ^ mat[1][1]) && !(mat[1][1] ^ mat[0][2]))
    {
        return mat[0][0] == 1 ?
                game->players[0]->is_x ? game->players[0] : game->players[1] :
                !game->players[0]->is_x ? game->players[0] : game->players[1] ;
    }

    return NULL;
}

void new_round(game_t *game , player_t* winner){
    if(game == NULL){
        perror("An error has occurred , Game is Null .");
        exit(1);
    }

    for(uint8_t i = 0 ; i < 2 ; i++)
        if(winner->is_x == game->players[i]->is_x)
            game->players[i]->score++;

    free_matrix((void*)game->matrix, 3);
}

void end_game(game_t *game){
    player_t *p1 = game->players[0] , *p2 = game->players[1] ;

    free(p1);
    free(p2);

    free(game->players);
    free_matrix((void*)game->matrix, 3);
}
