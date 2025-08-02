#include "interface.h"
#include "game.h"
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>


void draw_menu(){
    system("clear");

    const char* ascii_art = "tictactoe :";
    fprintf(stdout,"[1] - Play locally \n");
    fprintf(stdout,"[2] - Start a LAN game \n");
}

void draw_matrix(game_t* game){
    system("clear");

    for(uint8_t i = 0 ; i < 3 ; i++){
        fprintf(stdout , "%2u|%2u|%2u" ,
                game->matrix[0][i] ,
                game->matrix[1][i] ,
                game->matrix[2][i]);
        if(i < 2)
            fprintf(stdout , "\n ⎽⎽⟂⎽⎽⟂⎽⎽");
        fprintf(stdout, "\n");
    }
}
