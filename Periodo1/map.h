#ifndef MAP_H_
#define MAP_H_

#include "raylib.h"


#define STD_SIZE_X 15
#define STD_SIZE_Y 40
#define ENEMY_SIZE_X 55
#define ENEMY_SIZE_Y 70
#define SCREEN_BORDER 4
#define HERO_RUNTIME 0.12
#define TIME_BETWEEN_MOVE 2
#define ENEMY_RUNTIME 0.12

typedef struct{
    int bulletSpeed;
    int direction;
    int Ativo;
    Rectangle pos;
    Texture2D BulletTexEnemy;
    Texture2D BulletTexHero;
}Bullet;

typedef struct{
    Rectangle pos;
    Color color;
    int speed;
    int special;
    Bullet bullet;
    Texture2D HeroWalkDown;
    Texture2D HeroWalkUp;
    Texture2D HeroWalkRight;
    Texture2D HeroWalkLeft;
    Rectangle runSource1;
    Rectangle runSource2;
    Rectangle runDest;
    int hero_runIndex;
    float hero_runTimer;
    int direction;
}Hero;

typedef struct{
    Rectangle pos;
    Color color;
    int speed;
    int direction;
    int draw_enemy;
    int has_key;
    Bullet bullet;
    Texture2D EnemyTexUp;
    Texture2D EnemyTexDown;
    Texture2D EnemyTexRight;
    Texture2D EnemyTexLeft;
    Rectangle runSource;
    Rectangle runDest;
}Enemy;

typedef struct{
    Rectangle barriers[10];
    int num_barriers;
    Rectangle door;
    Rectangle prev_door;
    Color color;
    Enemy enemies[10];
    int num_enemies;
    Rectangle special_item;
    int draw_special_item;
    int door_locked;
    int next_map;
    int prev_map;
    Texture2D Ground;
    Texture2D SpecialTex;
} Map;

typedef struct Game {
    Map maps[10];
    int num_maps;
    int curr_map;
    Hero hero;
    int screenWidth;
    int screenHeight;
    int gameover;
    int checkpoint;
    unsigned frameSpeed;
    unsigned frameCounter;
    unsigned currentFrame;
    Sound Shoot;
    Sound Enemy;
    Music music;
} Game;

int barrier_collision(Map* m, Rectangle* t);
void map0_setup(Game* g);
void map1_setup(Game* g);
void map2_setup(Game* g);
void map3_setup(Game* g);
void map4_setup(Game* g);
void map5_setup(Game* g);
void map6_setup(Game* g);
void map7_setup(Game* g);
void map8_setup(Game* g);

#endif