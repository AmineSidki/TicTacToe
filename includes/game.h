#pragma once

#include <_types/_uint16_t.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <sys/_types/_mode_t.h>

enum gmode_t{
    LOCAL,NET
};

typedef enum gmode_t gmode_t;

struct player_t{
  char* name;
  uint16_t name_size;
  uint16_t score;
  bool is_x;
};

struct game_t{
    bool mode;
    uint16_t round;
    struct player_t** players;
    uint8_t** matrix;
};

typedef struct player_t player_t;
typedef struct game_t game_t;

//Player-specific functions :


//  Game-specific functions :
game_t* start_game(gmode_t mode , player_t* p1 , player_t* p2);
void check_win(game_t* game);
void new_round(game_t* game , player_t* winner);
void end_game(game_t* game);
