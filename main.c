#include "raylib.h"
#include <stdlib.h>
#include "map.h"

#include <time.h>
#include <stdio.h>
#include <string.h>


typedef struct {
    char name[50];
    double score;
} Player;

int compare(const void* a, const void* b) {
    double scoreA = ((Player*)a)->score;
    double scoreB = ((Player*)b)->score;
    return (scoreA > scoreB) - (scoreA < scoreB);
}

int main(void)
{
    Game game;
    game.screenWidth = 800;
    game.screenHeight = 450;

    InitWindow(game.screenWidth, game.screenHeight, "Trabalho-Pratico");
    InitAudioDevice(); 
    SetTargetFPS(60);

    char playerName[50] = "\0";
    int letterCount = 0;

    while (!IsKeyPressed(KEY_ENTER))
    {
        if (letterCount < 50)
        {
            int key = GetCharPressed();
            while (key > 0)
            {
                if ((key >= 32) && (key <= 125)) playerName[letterCount] = (char)key;
                letterCount++;
                key = GetCharPressed();
            }
        }
        BeginDrawing();
        ClearBackground(RAYWHITE);
        DrawText("Enter your name: ", 10, 10, 20, BLACK);
        DrawText(playerName, 10, 40, 20, BLACK);
        EndDrawing();
    }

    InitGame(&game);

    clock_t t;
    t = clock();

    while (!WindowShouldClose())
    {
        PlayMusicStream(game.music);
        UpdateDrawFrame(&game);
        if (game.gameover) break;
        if (game.curr_map == 8) break;
    }

    t = clock() - t;
    double tempo_seg = ((double)t)/CLOCKS_PER_SEC;

    FILE *fp = fopen("pontuacoes.txt", "a");
    if (fp == NULL)
    {
        printf("Erro ao abrir o arquivo.\n");
        return 1;
    }

    if (game.curr_map == 8)
    fprintf(fp, "%s %lf\n", playerName, tempo_seg);
    fclose(fp);

    char scoreText[100];
    sprintf(scoreText, "%s: %lf", playerName, tempo_seg);

    FILE* file = fopen("pontuacoes.txt", "r");
    Player players[100]; 
    int count = 0;

    while (fscanf(file, "%s %lf\n", players[count].name, &players[count].score) != EOF) {
        count++;
    }

    fclose(file);

    qsort(players, count, sizeof(Player), compare);

    char top3[150] = "\0"; // Inicializa a string como vazia

    if (count > 0) {
        char temp[50];
        sprintf(temp, "1. %s: %lf", players[0].name, players[0].score);
        strcat(top3, temp);
    }

    if (count > 1) {
        char temp[50];
        sprintf(temp, "\n2. %s: %lf", players[1].name, players[1].score);
        strcat(top3, temp);
    }

    if (count > 2) {
        char temp[50];
        sprintf(temp, "\n3. %s: %lf", players[2].name, players[2].score);
        strcat(top3, temp);
    }

    while (!IsKeyDown(KEY_ENTER)) {
        BeginDrawing();
        ClearBackground(RAYWHITE);
        if (game.curr_map == 8)
            DrawText("Congratulations! You're a champion!", GetScreenWidth() / 2 - MeasureText("Congratulations! You're a champion!", 20) / 2, GetScreenHeight() / 2 - 50, 20, BLACK);
        if(game.gameover)
            DrawText("GAME OVER", GetScreenWidth() / 2 - MeasureText("GAME OVER", 20) / 2, GetScreenHeight() / 2 - 50, 20, BLACK);

        DrawText(scoreText, GetScreenWidth() / 2 - MeasureText(scoreText, 20) / 2, GetScreenHeight() / 2 + 30, 20, BLACK);
        DrawText("TOP 3:", GetScreenWidth() / 2 - MeasureText("TOP 3:", 20) / 2, GetScreenHeight() / 2 + 75, 15, BLACK);
        DrawText(top3, GetScreenWidth() / 2 - MeasureText(top3, 20) / 2, GetScreenHeight() / 2 + 95, 15, BLACK);
        CloseAudioDevice();
        EndDrawing();
    }

    return 0;
}
