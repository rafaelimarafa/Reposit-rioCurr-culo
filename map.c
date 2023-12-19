#include <stdlib.h>
#include <stdio.h>
#include "raylib.h"
#include "map.h"

int barrier_collision(Map* map, Rectangle* target) {
    for (int i = 0; i < map->num_barriers; i++) {
        if (CheckCollisionRecs(*target, map->barriers[i])) {
            return 1;
        }
    }
    return 0;
}

// Maps Setup
void map0_setup(Game* g) {
    g->maps[0].num_barriers = 1;
    g->maps[0].barriers[0] = (Rectangle){ g->screenWidth / 2, 0, 2, 0.8 * g->screenHeight };
    g->maps[0].color = GRAY;
    g->maps[0].door = (Rectangle){ g->screenWidth - (SCREEN_BORDER + 5), g->screenHeight / 3, SCREEN_BORDER, 50 };
    g->maps[0].num_enemies = 2;
    g->maps[0].door_locked = 1;
    g->maps[0].Ground = LoadTexture("Ground.png");

    for (int i = 0; i < g->maps[0].num_enemies; i++) {
        g->maps[0].enemies[i].pos = (Rectangle){ 2 * g->screenWidth / 3, 2 * g->screenHeight / 3, ENEMY_SIZE_X, ENEMY_SIZE_Y };
        g->maps[0].enemies[i].color = BLACK;
        g->maps[0].enemies[i].speed = 2;
        g->maps[0].enemies[i].direction = KEY_RIGHT + (rand() % 4);
        g->maps[0].enemies[i].draw_enemy = 1;
        g->maps[0].enemies[i].EnemyTexUp = LoadTexture("Grue_cima.png");
        g->maps[0].enemies[i].EnemyTexDown = LoadTexture("Grue_baixo.png");
        g->maps[0].enemies[i].EnemyTexLeft = LoadTexture("Grue_esquerda.png");
        g->maps[0].enemies[i].EnemyTexRight = LoadTexture("Grue_direita.png");
        g->maps[0].enemies[i].bullet.BulletTexEnemy = LoadTexture("fire_inimigo.png"); 
        g->maps[0].enemies[i].bullet.direction = KEY_RIGHT;
        
    }
    g->maps[0].enemies[0].has_key = 1;
    g->maps[0].special_item = (Rectangle){ 2 * g->screenWidth / 3, 20, 15, 15 };
    g->maps[0].draw_special_item = 0;
    g->maps[0].prev_map = -1;
    g->maps[0].next_map = 1;
    g->maps[0].SpecialTex = LoadTexture("especial.png");
}

void map1_setup(Game* g) {
    g->maps[1].num_barriers = 2;
    g->maps[1].barriers[0] = (Rectangle){ 3 * g->screenWidth / 4, 0, 2, 0.6 * g->screenHeight };
    g->maps[1].barriers[1] = (Rectangle){ g->screenWidth / 4, 0.4 * g->screenHeight, 2, g->screenHeight };
    g->maps[1].color = GRAY;
    g->maps[1].door = (Rectangle){ g->screenWidth - (SCREEN_BORDER + 5), g->screenHeight / 3, SCREEN_BORDER, 50 };
    g->maps[1].prev_door = (Rectangle){ SCREEN_BORDER, g->screenHeight / 3, 5, 50 };
    g->maps[1].num_enemies = 3;
    g->maps[1].door_locked = 1;
    g->maps[1].Ground = LoadTexture("Ground.png");

    for (int i = 0; i < g->maps[1].num_enemies; i++) {
        g->maps[1].enemies[i].pos = (Rectangle){ 2 * g->screenWidth / 3, 2 * g->screenHeight / 3, ENEMY_SIZE_X, ENEMY_SIZE_Y };
        g->maps[1].enemies[i].color = BLACK;
        g->maps[1].enemies[i].speed = 4;
        g->maps[1].enemies[i].direction = KEY_RIGHT + (rand() % 4);
        g->maps[1].enemies[i].draw_enemy = 1;
        g->maps[1].enemies[i].has_key = 0;
        g->maps[1].enemies[i].EnemyTexUp = LoadTexture("Grue_cima.png");
        g->maps[1].enemies[i].EnemyTexDown = LoadTexture("Grue_baixo.png");
        g->maps[1].enemies[i].EnemyTexLeft = LoadTexture("Grue_esquerda.png");
        g->maps[1].enemies[i].EnemyTexRight = LoadTexture("Grue_direita.png");
        g->maps[1].enemies[i].bullet.BulletTexEnemy = LoadTexture("fire_inimigo.png");
        g->maps[1].enemies[i].bullet.direction = KEY_RIGHT;
    }
    g->maps[1].enemies[0].has_key = 1;
    g->maps[1].special_item = (Rectangle){ 4 * g->screenWidth / 5, 20, 15, 15 };
    g->maps[1].draw_special_item = 1;
    g->maps[1].prev_map = 0;
    g->maps[1].next_map = 2;
    g->maps[1].SpecialTex = LoadTexture("especial.png");
}

void map2_setup(Game* g) {
    g->maps[2].num_barriers = 3;
    g->maps[2].barriers[0] = (Rectangle){ g->screenWidth / 4, 0, 2, 0.6 * g->screenHeight };
    g->maps[2].barriers[1] = (Rectangle){ 2 * g->screenWidth / 4, 0, 2, 0.6 * g->screenHeight };
    g->maps[2].barriers[2] = (Rectangle){ 3 * g->screenWidth / 4, 0, 2, 0.6 * g->screenHeight };
    g->maps[2].color = GRAY;
    g->maps[2].door = (Rectangle){ g->screenWidth - (SCREEN_BORDER + 5), g->screenHeight / 3, SCREEN_BORDER, 50 };
    g->maps[2].prev_door = (Rectangle){ SCREEN_BORDER, g->screenHeight / 3, 5, 50 };
    g->maps[2].num_enemies = 4;
    g->maps[2].door_locked = 1;
    g->maps[2].Ground = LoadTexture("Ground.png");

    for (int i = 0; i < g->maps[2].num_enemies; i++) {
        g->maps[2].enemies[i].pos = (Rectangle){ 2 * g->screenWidth / 3, 2 * g->screenHeight / 3, ENEMY_SIZE_X, ENEMY_SIZE_Y };
        g->maps[2].enemies[i].color = BLACK;
        g->maps[2].enemies[i].speed = 3;
        g->maps[2].enemies[i].direction = KEY_RIGHT + (rand() % 4);
        g->maps[2].enemies[i].draw_enemy = 1;
        g->maps[2].enemies[i].has_key = 0;
        g->maps[2].enemies[i].EnemyTexUp = LoadTexture("Grue_cima.png");
        g->maps[2].enemies[i].EnemyTexDown = LoadTexture("Grue_baixo.png");
        g->maps[2].enemies[i].EnemyTexLeft = LoadTexture("Grue_esquerda.png");
        g->maps[2].enemies[i].EnemyTexRight = LoadTexture("Grue_direita.png");
        g->maps[2].enemies[i].bullet.BulletTexEnemy = LoadTexture("fire_inimigo.png"); 
        g->maps[2].enemies[i].bullet.direction = KEY_RIGHT;
    }
    g->maps[2].enemies[0].has_key = 1;
    g->maps[2].special_item = (Rectangle){ 4 * g->screenWidth / 5, 20, 15, 15 };
    g->maps[2].draw_special_item = 0;
    g->maps[2].prev_map = 1;
    g->maps[2].next_map = 3;
    g->maps[2].SpecialTex = LoadTexture("especial.png");
}

void map3_setup(Game* g) {
    g->maps[3].num_barriers = 1;
    g->maps[3].barriers[0] = (Rectangle){ g->screenWidth / 2, 0, 2, 0.8 * g->screenHeight };
    g->maps[3].color = GRAY;
    g->maps[3].door = (Rectangle){ g->screenWidth - (SCREEN_BORDER + 5), g->screenHeight / 3, SCREEN_BORDER, 50 };
    g->maps[3].num_enemies = 5;
    g->maps[3].door_locked = 1;
    g->maps[3].Ground = LoadTexture("Ground.png");

    for (int i = 0; i < g->maps[3].num_enemies; i++) {
        g->maps[3].enemies[i].pos = (Rectangle){ 2 * g->screenWidth / 3, 2 * g->screenHeight / 3, ENEMY_SIZE_X, ENEMY_SIZE_Y };
        g->maps[3].enemies[i].color = BLACK;
        g->maps[3].enemies[i].speed = 4;
        g->maps[3].enemies[i].direction = KEY_RIGHT + (rand() % 4);
        g->maps[3].enemies[i].draw_enemy = 1;
        g->maps[3].enemies[i].has_key = 0;
        g->maps[3].enemies[i].EnemyTexUp = LoadTexture("Grue_cima.png");
        g->maps[3].enemies[i].EnemyTexDown = LoadTexture("Grue_baixo.png");
        g->maps[3].enemies[i].EnemyTexLeft = LoadTexture("Grue_esquerda.png");
        g->maps[3].enemies[i].EnemyTexRight = LoadTexture("Grue_direita.png");
        g->maps[3].enemies[i].bullet.BulletTexEnemy = LoadTexture("fire_inimigo.png"); 
        g->maps[3].enemies[i].bullet.direction = KEY_RIGHT;

    }
    g->maps[3].enemies[0].has_key = 1;
    g->maps[3].special_item = (Rectangle){ 2 * g->screenWidth / 3, 20, 15, 15 };
    g->maps[3].draw_special_item = 0;
    g->maps[3].prev_map = 2;
    g->maps[3].next_map = 4;
    g->maps[3].SpecialTex = LoadTexture("especial.png");
}

void map4_setup(Game* g) {
    g->maps[4].num_barriers = 2;
    g->maps[4].barriers[0] = (Rectangle){ 3 * g->screenWidth / 4, 0, 2, 0.6 * g->screenHeight };
    g->maps[4].barriers[1] = (Rectangle){ g->screenWidth / 4, 0.4 * g->screenHeight, 2, g->screenHeight };
    g->maps[4].color = GRAY;
    g->maps[4].door = (Rectangle){ g->screenWidth - (SCREEN_BORDER + 5), g->screenHeight / 3, SCREEN_BORDER, 50 };
    g->maps[4].prev_door = (Rectangle){ SCREEN_BORDER, g->screenHeight / 3, 5, 50 };
    g->maps[4].num_enemies = 6;
    g->maps[4].door_locked = 1;
    g->maps[4].Ground = LoadTexture("Ground.png");

    for (int i = 0; i < g->maps[4].num_enemies; i++) {
        g->maps[4].enemies[i].pos = (Rectangle){ 2 * g->screenWidth / 3, 2 * g->screenHeight / 3, ENEMY_SIZE_X, ENEMY_SIZE_Y };
        g->maps[4].enemies[i].color = BLACK;
        g->maps[4].enemies[i].speed = 2;
        g->maps[4].enemies[i].direction = KEY_RIGHT + (rand() % 4);
        g->maps[4].enemies[i].draw_enemy = 1;
        g->maps[4].enemies[i].has_key = 0;
        g->maps[4].enemies[i].EnemyTexUp = LoadTexture("Grue_cima.png");
        g->maps[4].enemies[i].EnemyTexDown = LoadTexture("Grue_baixo.png");
        g->maps[4].enemies[i].EnemyTexLeft = LoadTexture("Grue_esquerda.png");
        g->maps[4].enemies[i].EnemyTexRight = LoadTexture("Grue_direita.png");
        g->maps[4].enemies[i].bullet.BulletTexEnemy = LoadTexture("fire_inimigo.png"); 
        g->maps[4].enemies[i].bullet.direction = KEY_RIGHT;
    }
    g->maps[4].enemies[0].has_key = 1;
    g->maps[4].special_item = (Rectangle){ 4 * g->screenWidth / 5, 20, 15, 15 };
    g->maps[4].draw_special_item = 0;
    g->maps[4].prev_map = 3;
    g->maps[4].next_map = 5;
    g->maps[4].SpecialTex = LoadTexture("especial.png");
}

void map5_setup(Game* g) {
    g->maps[5].num_barriers = 3;
    g->maps[5].barriers[0] = (Rectangle){ g->screenWidth / 4, 0, 2, 0.6 * g->screenHeight };
    g->maps[5].barriers[1] = (Rectangle){ 2 * g->screenWidth / 4, 0, 2, 0.6 * g->screenHeight };
    g->maps[5].barriers[2] = (Rectangle){ 3 * g->screenWidth / 4, 0, 2, 0.6 * g->screenHeight };
    g->maps[5].color = GRAY;
    g->maps[5].door = (Rectangle){ g->screenWidth - (SCREEN_BORDER + 5), g->screenHeight / 3, SCREEN_BORDER, 50 };
    g->maps[5].prev_door = (Rectangle){ SCREEN_BORDER, g->screenHeight / 3, 5, 50 };
    g->maps[5].num_enemies = 4;
    g->maps[5].door_locked = 1;
    g->maps[5].Ground = LoadTexture("Ground.png");

    for (int i = 0; i < g->maps[5].num_enemies; i++) {
        g->maps[5].enemies[i].pos = (Rectangle){ 2 * g->screenWidth / 3, 2 * g->screenHeight / 3, ENEMY_SIZE_X, ENEMY_SIZE_Y };
        g->maps[5].enemies[i].color = BLACK;
        g->maps[5].enemies[i].speed = 6;
        g->maps[5].enemies[i].direction = KEY_RIGHT + (rand() % 4);
        g->maps[5].enemies[i].draw_enemy = 1;
        g->maps[5].enemies[i].has_key = 0;
        g->maps[5].enemies[i].EnemyTexUp = LoadTexture("Grue_cima.png");
        g->maps[5].enemies[i].EnemyTexDown = LoadTexture("Grue_baixo.png");
        g->maps[5].enemies[i].EnemyTexLeft = LoadTexture("Grue_esquerda.png");
        g->maps[5].enemies[i].EnemyTexRight = LoadTexture("Grue_direita.png");
        g->maps[5].enemies[i].bullet.BulletTexEnemy = LoadTexture("fire_inimigo.png"); 
        g->maps[5].enemies[i].bullet.direction = KEY_RIGHT;
    }
    g->maps[5].enemies[0].has_key = 1;
    g->maps[5].special_item = (Rectangle){ 4 * g->screenWidth / 5, 20, 15, 15 };
    g->maps[5].draw_special_item = 1;
    g->maps[5].prev_map = 4;
    g->maps[5].next_map = 6;
    g->maps[5].SpecialTex = LoadTexture("especial.png");
}

void map6_setup(Game* g) {
    g->maps[6].num_barriers = 1;
    g->maps[6].barriers[0] = (Rectangle){ g->screenWidth / 2, 0, 2, 0.8 * g->screenHeight };
    g->maps[6].color = GRAY;
    g->maps[6].door = (Rectangle){ g->screenWidth - (SCREEN_BORDER + 5), g->screenHeight / 3, SCREEN_BORDER, 50 };
    g->maps[6].num_enemies = 4;
    g->maps[6].door_locked = 1;
    g->maps[6].Ground = LoadTexture("Ground.png");

    for (int i = 0; i < g->maps[6].num_enemies; i++) {
        g->maps[6].enemies[i].pos = (Rectangle){ 2 * g->screenWidth / 3, 2 * g->screenHeight / 3, ENEMY_SIZE_X, ENEMY_SIZE_Y };
        g->maps[6].enemies[i].color = BLACK;
        g->maps[6].enemies[i].speed = 7;
        g->maps[6].enemies[i].direction = KEY_RIGHT + (rand() % 4);
        g->maps[6].enemies[i].draw_enemy = 1;
        g->maps[6].enemies[i].has_key = 0;
        g->maps[6].enemies[i].EnemyTexUp = LoadTexture("Grue_cima.png");
        g->maps[6].enemies[i].EnemyTexDown = LoadTexture("Grue_baixo.png");
        g->maps[6].enemies[i].EnemyTexLeft = LoadTexture("Grue_esquerda.png");
        g->maps[6].enemies[i].EnemyTexRight = LoadTexture("Grue_direita.png");
        g->maps[6].enemies[i].bullet.BulletTexEnemy = LoadTexture("fire_inimigo.png"); 
        g->maps[6].enemies[i].bullet.direction = KEY_RIGHT;

    }
    g->maps[6].enemies[0].has_key = 1;
    g->maps[6].special_item = (Rectangle){ 2 * g->screenWidth / 3, 20, 15, 15 };
    g->maps[6].draw_special_item = 0;
    g->maps[6].prev_map = 5;
    g->maps[6].next_map = 7;
    g->maps[6].SpecialTex = LoadTexture("especial.png");
}

void map7_setup(Game* g) {
    g->maps[7].num_barriers = 2;
    g->maps[7].barriers[0] = (Rectangle){ 3 * g->screenWidth / 4, 0, 2, 0.6 * g->screenHeight };
    g->maps[7].barriers[1] = (Rectangle){ g->screenWidth / 4, 0.4 * g->screenHeight, 2, g->screenHeight };
    g->maps[7].color = GRAY;
    g->maps[7].door = (Rectangle){ g->screenWidth - (SCREEN_BORDER + 5), g->screenHeight / 3, SCREEN_BORDER, 50 };
    g->maps[7].prev_door = (Rectangle){ SCREEN_BORDER, g->screenHeight / 3, 5, 50 };
    g->maps[7].num_enemies = 1;
    g->maps[7].door_locked = 1;
    g->maps[7].Ground = LoadTexture("Ground.png");

    for (int i = 0; i < g->maps[7].num_enemies; i++) {
        g->maps[7].enemies[i].pos = (Rectangle){ 2 * g->screenWidth / 3, 2 * g->screenHeight / 3, 60, 60 };
        g->maps[7].enemies[i].color = BLACK;
        g->maps[7].enemies[i].speed = 5;
        g->maps[7].enemies[i].direction = KEY_RIGHT + (rand() % 4);
        g->maps[7].enemies[i].draw_enemy = 1;
        g->maps[7].enemies[i].has_key = 0;
        g->maps[7].enemies[i].EnemyTexLeft = LoadTexture("BossLeft.png");
        g->maps[7].enemies[i].EnemyTexRight = LoadTexture("BossRight.png");
        g->maps[7].enemies[i].bullet.BulletTexEnemy = LoadTexture("fire_inimigo.png"); 
        g->maps[7].enemies[i].bullet.direction = KEY_RIGHT;
    }
    g->maps[7].enemies[0].has_key = 1;
    g->maps[7].special_item = (Rectangle){ 4 * g->screenWidth / 5, 20, 15, 15 };
    g->maps[7].draw_special_item = 1;
    g->maps[7].prev_map = 6;
    g->maps[7].next_map = 8;
    g->maps[7].SpecialTex = LoadTexture("especial.png");
}

void map8_setup(Game* g) {
    g->maps[8].Ground = LoadTexture("Ground.png");
    g->maps[8].SpecialTex = LoadTexture("especial.png");
}