#include "game.h"
#include <stdint.h>

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

    for(uint16_t i = 0 ; i < 3 ; i++){
        matrix[i] = (uint8_t*)malloc(3*sizeof(uint8_t));
        if(matrix[i] == NULL){
            goto ram_error;
        }
    }

    players[0] = p1;
    players[1] = p2;

    *game = (game_t){.mode = mode , .round = 0 , .players = players , .matrix = matrix};

    ram_error:
        perror("RAM error !");
        exit(1);
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
