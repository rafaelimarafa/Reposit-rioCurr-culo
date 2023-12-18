#include <stdlib.h>
#include <stdio.h>
#include "raylib.h"
#include "map.h"

// Initialize game variables
void InitGame(Game *g)
{

    g->music = LoadMusicStream("MapMusic.mp3");
    g->Shoot = LoadSound("ShootSound.mp3");
    g->Enemy = LoadSound("EnemyDiying.mp3");
    g->curr_map = 7;
    g->num_maps = 10;
    g->hero.pos = (Rectangle){150, 300, STD_SIZE_X, STD_SIZE_Y};
    g->hero.color = WHITE;
    g->hero.speed = 4;
    g->hero.special = 0;
    g->hero.direction = KEY_RIGHT;
    g->hero.bullet.direction = KEY_RIGHT;
    g->hero.bullet.Ativo = 0;
    g->hero.bullet.pos.width = 8;
    g->hero.bullet.pos.height = 8;
    g->hero.HeroWalkDown = LoadTexture("HeroWalkDown.png");
    g->hero.HeroWalkUp = LoadTexture("HeroWalkUp.png");
    g->hero.HeroWalkRight = LoadTexture("HeroWalkRight.png");
    g->hero.HeroWalkLeft = LoadTexture("HeroWalkLeft.png");
    g->hero.bullet.BulletTexHero = LoadTexture("fire_heroi.png");
    g->hero.hero_runIndex = 0;
    g->hero.hero_runTimer = HERO_RUNTIME;
    g->hero.runSource1 = (Rectangle){g->hero.hero_runIndex * 64, 0, 64, 64};
    g->hero.runSource2 = (Rectangle){g->hero.hero_runIndex * 64, 0, 64, 64};
    g->hero.runDest = (Rectangle){g->hero.pos.x, g->hero.pos.y, g->hero.runSource1.width, g->hero.runSource1.height};
    for (int i = 0; i < g->maps[g->curr_map].num_enemies; i++)
    {
        g->maps[g->curr_map].enemies[i].bullet.pos.width = 8;
        g->maps[g->curr_map].enemies[i].bullet.pos.height = 8;
        g->maps[g->curr_map].enemies[i].bullet.Ativo = 0;
        g->maps[g->curr_map].enemies[i].bullet.direction = KEY_RIGHT;
    }

    g->gameover = 0;
    g->checkpoint = 0;

    map0_setup(g);
    map1_setup(g);
    map2_setup(g);
    map3_setup(g);
    map4_setup(g);
    map5_setup(g);
    map6_setup(g);
    map7_setup(g);
    map8_setup(g);
}

// Update game (one frame)
void UpdateGame(Game *g)
{
    UpdateMusicStream(g->music);
    SetMusicVolume(g->music, 1.4);
    update_hero_pos(g);

    Map *map = &g->maps[g->curr_map];
    for (int i = 0; i < map->num_enemies; i++)
    {
        if (map->enemies[i].draw_enemy)
        {
            update_enemy_pos(g, &map->enemies[i]);
            if (CheckCollisionRecs(g->hero.pos, map->enemies[i].pos) || (map->enemies[i].bullet.Ativo && CheckCollisionRecs(map->enemies[i].bullet.pos, g->hero.pos)))
            {
                map->enemies[i].bullet.Ativo = 0;
                if (g->curr_map != 7)
                    g->checkpoint = 1;
                else
                    g->gameover = 1;
            }
            if (CheckCollisionRecs(g->hero.bullet.pos, map->enemies[i].pos))
            {
                map->enemies[i].draw_enemy = 0;
                if (g->curr_map == 7 && g->gameover == 0)
                {
                    g->curr_map = 8;
                }
                if (map->enemies[i].has_key)
                {
                    map->door_locked = 0;
                }
            }
        }
    }
    if (g->checkpoint)
    {
        g->checkpoint = 0;
        if (g->curr_map == 1)
            map1_setup(g);
        else if (g->curr_map == 2)
            map2_setup(g);
        else if (g->curr_map == 3)
            map3_setup(g);
        else if (g->curr_map == 4)
            map4_setup(g);
        else if (g->curr_map == 5)
            map5_setup(g);
        else if (g->curr_map == 6)
            map6_setup(g);
        else
            map0_setup(g);
        g->hero.pos = (Rectangle){50, 200, STD_SIZE_X, STD_SIZE_Y};
        g->hero.special = 0;
        g->hero.speed = 4;
    }

    if (CheckCollisionRecs(g->hero.pos, map->special_item) && map->draw_special_item)
    {
        g->hero.pos.width += 10;
        g->hero.pos.height += 10;
        g->hero.special = 1;
        map->draw_special_item = 0;
        g->hero.speed = 8;
    }

    if (CheckCollisionRecs(g->hero.pos, map->door) && !map->door_locked)
    {
        g->curr_map = map->next_map;
        g->hero.pos = (Rectangle){50, 200, STD_SIZE_X, STD_SIZE_Y};
        g->hero.special = 0;
        g->hero.speed = 4;
    }

    if (map->prev_map != -1 && CheckCollisionRecs(g->hero.pos, map->prev_door))
    {
        g->curr_map = map->prev_map;
        g->hero.special = 0;
        g->hero.speed = 4;
        g->hero.pos = (Rectangle){g->screenWidth - 50, g->screenHeight / 3, STD_SIZE_X, STD_SIZE_Y};
    }

    shoot_bullet(g);
    shoot_bullet_enemy(g);
    update_bullet_position(g);
    update_bullet_position_enemy(g);
}

// Draw game (one frame)
void DrawGame(Game *g)
{
    BeginDrawing();

    ClearBackground(RAYWHITE);
    DrawRectangle(0, 0, g->screenWidth, g->screenHeight, GRAY);
    draw_borders(g);
    draw_map(g);

    for (int i = 0; i < g->maps[g->curr_map].num_enemies; i++)
    {
        if (g->maps[g->curr_map].enemies[i].bullet.Ativo && g->maps[g->curr_map].enemies[i].draw_enemy)
        {
            DrawTexture(g->maps[g->curr_map].enemies[i].bullet.BulletTexEnemy, g->maps[g->curr_map].enemies[i].bullet.pos.x, g->maps[g->curr_map].enemies[i].bullet.pos.y, WHITE);
        }
    }
    if (g->hero.bullet.Ativo)
    {
        DrawTextureRec(g->hero.bullet.BulletTexHero, (Rectangle){0, 0, 6, 6}, (Vector2){g->hero.bullet.pos.x, g->hero.bullet.pos.y}, WHITE);
    }

    for (int i = 0; i < g->maps[g->curr_map].num_enemies; i++)
    {
        if (g->maps[g->curr_map].enemies[i].bullet.Ativo && g->maps[g->curr_map].enemies[i].draw_enemy)
        {
            DrawRectangle(g->maps[g->curr_map].enemies[i].bullet.pos.x, g->maps[g->curr_map].enemies[i].bullet.pos.y, 4, 4, YELLOW);
        }
    }

    if (g->hero.direction == KEY_RIGHT)
    {
        DrawTexturePro(g->hero.HeroWalkRight, g->hero.runSource1, g->hero.runDest, (Vector2){15, 5}, 0, WHITE);
    }
    if (g->hero.direction == KEY_LEFT)
    {
        DrawTexturePro(g->hero.HeroWalkLeft, g->hero.runSource1, g->hero.runDest, (Vector2){15, 5}, 0, WHITE);
    }
    if (g->hero.direction == KEY_UP)
    {
        DrawTexturePro(g->hero.HeroWalkUp, g->hero.runSource2, g->hero.runDest, (Vector2){15, 5}, 0, WHITE);
    }
    if (g->hero.direction == KEY_DOWN)
    {
        DrawTexturePro(g->hero.HeroWalkDown, g->hero.runSource2, g->hero.runDest, (Vector2){15, 5}, 0, WHITE);
    }

    for (int i = 0; i < g->maps[g->curr_map].num_enemies; i++)
    {

        if (g->maps[g->curr_map].enemies[i].draw_enemy)
        {
            if (g->maps[g->curr_map].enemies[i].direction == KEY_RIGHT)
            {
                DrawTexturePro(g->maps[g->curr_map].enemies[i].EnemyTexRight, g->maps[g->curr_map].enemies[i].runSource, g->maps[g->curr_map].enemies[i].runDest, (Vector2){0, 0}, 0, WHITE);
            }
            if (g->maps[g->curr_map].enemies[i].direction == KEY_LEFT)
            {
                DrawTexturePro(g->maps[g->curr_map].enemies[i].EnemyTexLeft, g->maps[g->curr_map].enemies[i].runSource, g->maps[g->curr_map].enemies[i].runDest, (Vector2){0, 0}, 0, WHITE);
            }
            if (g->maps[g->curr_map].enemies[i].direction == KEY_UP)
            {
                DrawTexturePro(g->maps[g->curr_map].enemies[i].EnemyTexUp, g->maps[g->curr_map].enemies[i].runSource, g->maps[g->curr_map].enemies[i].runDest, (Vector2){0, 0}, 0, WHITE);
            }
            if (g->maps[g->curr_map].enemies[i].direction == KEY_DOWN)
            {
                DrawTexturePro(g->maps[g->curr_map].enemies[i].EnemyTexDown, g->maps[g->curr_map].enemies[i].runSource, g->maps[g->curr_map].enemies[i].runDest, (Vector2){0, 0}, 0, WHITE);
            }
        }
    }

    EndDrawing();
}

// Update and Draw (one frame)
void UpdateDrawFrame(Game *g)
{
    UpdateGame(g);
    DrawGame(g);
}

void draw_borders(Game *g)
{
    DrawRectangle(0, 0, SCREEN_BORDER, g->screenHeight, BLACK);
    DrawRectangle(0, 0, g->screenWidth, SCREEN_BORDER, BLACK);
    DrawRectangle(g->screenWidth - SCREEN_BORDER, 0, g->screenWidth, g->screenHeight, BLACK);
    DrawRectangle(0, g->screenHeight - SCREEN_BORDER, g->screenWidth, g->screenHeight, BLACK);
}

void shoot_bullet(Game *g)
{
    g->hero.bullet.bulletSpeed = 7;
    g->hero.bullet.BulletTexHero = LoadTexture("fire_heroi.png");
    if (!g->hero.bullet.Ativo)
    {
        // centralizando a posição da bala com o herói
        g->hero.bullet.pos.x = g->hero.pos.x;
        g->hero.bullet.pos.y = g->hero.pos.y + 10;
    }
    if (IsKeyPressed(KEY_SPACE) && !g->hero.bullet.Ativo)
    {
        g->hero.bullet.Ativo = 1;
        PlaySound(g->Shoot);
        // definindo a direção da bala
        if (IsKeyDown(KEY_UP))
        {
            g->hero.bullet.direction = KEY_UP;
        }
        else if (IsKeyDown(KEY_DOWN))
        {
            g->hero.bullet.direction = KEY_DOWN;
        }
        else if (IsKeyDown(KEY_RIGHT))
        {
            g->hero.bullet.direction = KEY_RIGHT;
        }
        else if (IsKeyDown(KEY_LEFT))
        {
            g->hero.bullet.direction = KEY_LEFT;
        }
    }
    if (g->hero.bullet.Ativo)
    {
        if (g->hero.bullet.direction == KEY_UP)
        {
            g->hero.bullet.pos.y -= g->hero.bullet.bulletSpeed;
        }
        else if (g->hero.bullet.direction == KEY_DOWN)
        {
            g->hero.bullet.pos.y += g->hero.bullet.bulletSpeed;
        }
        else if (g->hero.bullet.direction == KEY_LEFT)
        {
            g->hero.bullet.pos.x -= g->hero.bullet.bulletSpeed;
        }
        else if (g->hero.bullet.direction == KEY_RIGHT)
        {
            g->hero.bullet.pos.x += g->hero.bullet.bulletSpeed;
        }
    }
}

void shoot_bullet_enemy(Game *g)
{
    for (int j = 0; j < g->maps[g->curr_map].num_enemies; j++)
    {
        if (!g->maps[g->curr_map].enemies[j].bullet.Ativo && g->maps[g->curr_map].enemies[j].draw_enemy)
        {
            g->maps[g->curr_map].enemies[j].bullet.Ativo = 1;
            g->maps[g->curr_map].enemies[j].bullet.bulletSpeed = 8;
            // centralizing the position of the bullet with the enemy
            g->maps[g->curr_map].enemies[j].bullet.pos.x = g->maps[g->curr_map].enemies[j].pos.x + g->maps[g->curr_map].enemies[j].pos.width / 2;
            g->maps[g->curr_map].enemies[j].bullet.pos.y = g->maps[g->curr_map].enemies[j].pos.y + g->maps[g->curr_map].enemies[j].pos.height / 2;
        }
    }
}

void update_bullet_position(Game *g)
{
    if (g->hero.bullet.Ativo)
    {
        g->hero.bullet.bulletSpeed = 6;
        if (g->hero.bullet.direction == KEY_UP)
        {
            g->hero.bullet.pos.y -= g->hero.bullet.bulletSpeed;
        }
        else if (g->hero.bullet.direction == KEY_DOWN)
        {
            g->hero.bullet.pos.y += g->hero.bullet.bulletSpeed;
        }
        else if (g->hero.bullet.direction == KEY_LEFT)
        {
            g->hero.bullet.pos.x -= g->hero.bullet.bulletSpeed;
        }
        else if (g->hero.bullet.direction == KEY_RIGHT)
        {
            g->hero.bullet.pos.x += g->hero.bullet.bulletSpeed;
        }

        // Verifique se a bala atingiu uma barreira
        for (int i = 0; i < g->maps[g->curr_map].num_barriers; i++)
        {
            if (CheckCollisionRecs(g->hero.bullet.pos, g->maps[g->curr_map].barriers[i]))
            {
                g->hero.bullet.Ativo = 0;
                g->hero.bullet.pos.x = g->hero.pos.x;
                g->hero.bullet.pos.y = g->hero.pos.y;
                break;
            }
        }

        // Verifique se a bala atingiu um inimigo
        for (int i = 0; i < g->maps[g->curr_map].num_enemies; i++)
        {
            if (CheckCollisionRecs(g->hero.bullet.pos, g->maps[g->curr_map].enemies[i].pos) && g->maps[g->curr_map].enemies[i].draw_enemy)
            {
                g->hero.bullet.Ativo = 0;
                PlaySound(g->Enemy);
                break;
            }
        }

        // Verifique se a bala saiu da tela e a desative se saiu
        if (g->hero.bullet.pos.x < 0 || g->hero.bullet.pos.x > g->screenWidth ||
            g->hero.bullet.pos.y < 0 || g->hero.bullet.pos.y > g->screenHeight)
        {
            g->hero.bullet.Ativo = 0;
        }
    }
}

void update_bullet_position_enemy(Game *g)
{
    // Updating Enemies' bullet positions
    for (int j = 0; j < g->maps[g->curr_map].num_enemies; j++)
    {
        if (g->maps[g->curr_map].enemies[j].bullet.Ativo)
        {

            // Check if enemy's bullet hit a barrier
            if (barrier_collision(&g->maps[g->curr_map], &g->maps[g->curr_map].enemies[j].bullet.pos))
            {
                g->maps[g->curr_map].enemies[j].bullet.pos.x = g->maps[g->curr_map].enemies[j].pos.x;
                g->maps[g->curr_map].enemies[j].bullet.pos.y = g->maps[g->curr_map].enemies[j].pos.y;
                g->maps[g->curr_map].enemies[j].bullet.Ativo = 0;
                break;
            }
            // Control bullet direction
            if (g->maps[g->curr_map].enemies[j].bullet.direction == KEY_UP)
            {
                g->maps[g->curr_map].enemies[j].bullet.pos.y -= g->maps[g->curr_map].enemies[j].bullet.bulletSpeed;
            }
            else if (g->maps[g->curr_map].enemies[j].bullet.direction == KEY_DOWN)
            {
                g->maps[g->curr_map].enemies[j].bullet.pos.y += g->maps[g->curr_map].enemies[j].bullet.bulletSpeed;
            }
            else if (g->maps[g->curr_map].enemies[j].bullet.direction == KEY_LEFT)
            {
                g->maps[g->curr_map].enemies[j].bullet.pos.x -= g->maps[g->curr_map].enemies[j].bullet.bulletSpeed;
            }
            else if (g->maps[g->curr_map].enemies[j].bullet.direction == KEY_RIGHT)
            {
                g->maps[g->curr_map].enemies[j].bullet.pos.x += g->maps[g->curr_map].enemies[j].bullet.bulletSpeed;
            }

            // Check if enemy's bullet left the screen and deactivate if it did
            if (g->maps[g->curr_map].enemies[j].bullet.pos.x < 0 || g->maps[g->curr_map].enemies[j].bullet.pos.x > g->screenWidth ||
                g->maps[g->curr_map].enemies[j].bullet.pos.y < 0 || g->maps[g->curr_map].enemies[j].bullet.pos.y > g->screenHeight)
            {
                g->maps[g->curr_map].enemies[j].bullet.Ativo = 0;
                break;
            }
        }
    }
}

void draw_map(Game *g)
{
    Map *map = &g->maps[g->curr_map];

    DrawTextureRec(map->Ground, (Rectangle){0, 0, 800, 450}, (Vector2){0, 0}, WHITE);

    for (int i = 0; i < map->num_barriers; i++)
    {
        DrawRectangleRec(map->barriers[i], BLACK);
    }

    if (map->door_locked)
        DrawRectangleRec(map->door, RED);
    else
        DrawRectangleRec(map->door, GREEN);

    if (map->prev_map != -1)
    {
        DrawRectangleRec(map->prev_door, GREEN);
    }

    if (map->draw_special_item)
    {
        DrawRectangleRec(map->special_item, PURPLE);
    }
}

void update_hero_pos(Game *g)
{
    Hero *h = &g->hero;
    Map *m = &g->maps[g->curr_map];

    g->hero.runSource1 = (Rectangle){g->hero.hero_runIndex * 64, 0, 64, 64};
    g->hero.runSource2 = (Rectangle){g->hero.hero_runIndex * 64, 0, 64, 64};
    g->hero.runDest = (Rectangle){g->hero.pos.x, g->hero.pos.y, g->hero.runSource1.width * 0.7, g->hero.runSource1.height * 0.7};

    if (IsKeyDown(KEY_A) || IsKeyDown(KEY_LEFT))
    {
        h->hero_runTimer -= GetFrameTime();
        if (h->hero_runTimer < 0)
        {
            h->hero_runIndex++;
            h->hero_runTimer = HERO_RUNTIME;
        }
        if (h->hero_runIndex > 5)
            h->hero_runIndex = 0;
        h->direction = KEY_LEFT;
        if (h->pos.x > SCREEN_BORDER)
            h->pos.x -= h->speed;
        if (barrier_collision(m, &h->pos))
            h->pos.x += h->speed;
    }
    else if (IsKeyDown(KEY_D) || IsKeyDown(KEY_RIGHT))
    {
        h->hero_runTimer -= GetFrameTime();
        if (h->hero_runTimer < 0)
        {
            h->hero_runIndex++;
            h->hero_runTimer = HERO_RUNTIME;
        }
        if (h->hero_runIndex > 5)
            h->hero_runIndex = 0;
        h->direction = KEY_RIGHT;
        if (h->pos.x + h->pos.width < g->screenWidth - SCREEN_BORDER)
        {
            h->pos.x += h->speed;
        }
        if (barrier_collision(m, &h->pos))
            h->pos.x -= h->speed;
    }
    else if (IsKeyDown(KEY_W) || IsKeyDown(KEY_UP))
    {
        h->hero_runTimer -= GetFrameTime();
        if (h->hero_runTimer < 0)
        {
            h->hero_runIndex++;
            h->hero_runTimer = HERO_RUNTIME;
        }
        if (h->hero_runIndex > 6)
            h->hero_runIndex = 0;
        h->direction = KEY_UP;
        if (h->pos.y > SCREEN_BORDER)
            h->pos.y -= h->speed;
        if (barrier_collision(m, &h->pos))
            h->pos.y += h->speed;
    }
    else if (IsKeyDown(KEY_S) || IsKeyDown(KEY_DOWN))
    {
        h->hero_runTimer -= GetFrameTime();
        if (h->hero_runTimer < 0)
        {
            h->hero_runIndex++;
            h->hero_runTimer = HERO_RUNTIME;
        }
        if (h->hero_runIndex > 6)
            h->hero_runIndex = 0;
        h->direction = KEY_DOWN;
        if (h->pos.y + h->pos.height < g->screenHeight - SCREEN_BORDER)
            h->pos.y += h->speed;
        if (barrier_collision(m, &h->pos))
            h->pos.y -= h->speed;
    }
}

void update_enemy_pos(Game *g, Enemy *e)
{
    Map *m = &g->maps[g->curr_map];

    e->runSource = (Rectangle){0, 0, 56, 71};
    e->runDest = (Rectangle){e->pos.x, e->pos.y, e->runSource.width, e->runSource.height};
    if (e->draw_enemy)
    {
        if (e->direction == KEY_LEFT)
        {
            if (!e->bullet.Ativo)
                e->bullet.direction = KEY_LEFT;
            if (e->pos.x > SCREEN_BORDER)
                e->pos.x -= e->speed;
            else
            {
                e->direction = KEY_RIGHT + (rand() % 4);
            }
            if (barrier_collision(m, &e->pos))
            {
                e->pos.x += e->speed;
                e->direction = KEY_RIGHT + (rand() % 4);
            }
        }
        else if (e->direction == KEY_RIGHT)
        {
            if (!e->bullet.Ativo)
                e->bullet.direction = KEY_RIGHT;
            if (e->pos.x + e->pos.width < g->screenWidth - SCREEN_BORDER)
                e->pos.x += e->speed;
            else
                e->direction = KEY_RIGHT + (rand() % 4);

            if (barrier_collision(m, &e->pos))
            {
                e->pos.x -= e->speed;
                e->direction = KEY_RIGHT + (rand() % 4);
            }
        }
        else if (e->direction == KEY_UP)
        {
            if (!e->bullet.Ativo)
                e->bullet.direction = KEY_UP;
            if (e->pos.y > SCREEN_BORDER)
                e->pos.y -= e->speed;
            else
                e->direction = KEY_RIGHT + (rand() % 4);

            if (barrier_collision(m, &e->pos))
            {
                e->pos.y += e->speed;
                e->direction = KEY_RIGHT + (rand() % 4);
            }
        }
        else if (e->direction == KEY_DOWN)
        {
            if (!e->bullet.Ativo)
                e->bullet.direction = KEY_DOWN;
            if (e->pos.y + e->pos.height < g->screenHeight - SCREEN_BORDER)
                e->pos.y += e->speed;
            else
                e->direction = KEY_RIGHT + (rand() % 4);

            if (barrier_collision(m, &e->pos))
            {
                e->pos.y -= e->speed;
                e->direction = KEY_RIGHT + (rand() % 4);
            }
        }
        if (rand() % 100 == 1) // 1% de chance do inimigo mudar de direcao
            e->direction = KEY_RIGHT + (rand() % 4);
    }
}