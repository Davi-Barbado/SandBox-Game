#include <raylib.h>
#include <stdbool.h>
#include <stdlib.h>
#define RAYLIB_NUKLEAR_IMPLEMENTATION
#include <nuklear/raylib-nuklear.h>
#define GW 700
#define GH 500

Texture screen;
typedef struct{
    int id;
    bool occupied;
} pixel;

pixel grade[GW][GH];
Color colors[GW * GH];

int selected = 0;

float pencil_size = 50;
Rectangle Pencil = {0, 0, 0, 0};

void init_grade(){
    for (int x = 0; x < GW - 1; x++){
        for (int y = 0; y < GH - 1; y++){
            grade[x][y].id = 0;
            grade[x][y].occupied = false;
        }
    }
}
void process_grade(){
    for (int x = 0; x < GW - 1; x++){
        for (int y = 0; y < GH - 1; y++){
            if (grade[x][y].id == 1){
                colors[y * GW + x] = YELLOW;
            }
            else if (grade[x][y].id == 2){
                colors[y * GW + x] = BLUE;
            }
            else if (grade[x][y].id == 3){
                colors[y * GW + x] = BLACK;
            }
            else if (grade[x][y].id == 4){
                colors[y * GW + x] = RED;
            }
            else if (grade[x][y].id == 0){
                colors[y * GW + x] = GRAY;
            }
        }
    }
    UpdateTexture(screen, &colors);
}
void show_grade(){
    DrawTexture(screen, 0, 0, WHITE);
}
void Update_Pencil(){
    Pencil.x = (float)GetMouseX() - pencil_size/2;
    Pencil.y = (float)GetMouseY() - pencil_size/2;
}
void Draw_Pencil(){
    DrawRectangleRec(Pencil, Fade(SKYBLUE, 0.5f));
}
void gen_pixel(){
    if (IsMouseButtonDown(MOUSE_BUTTON_LEFT)){
        int startx = (int)Pencil.x;
        int starty = (int)Pencil.y;
        for (int x = startx; x < startx + pencil_size; x++){
            for (int y = starty; y < starty + pencil_size; y++){
                if (x >= 0 && x < GW && y > 0 && y < GH){
                    if (grade[x][y].occupied == false){
                        if (grade[x][y].occupied == false){
                            if (selected == 0){
                                grade[x][y].id = 1;
                                grade[x][y].occupied = true;
                            }
                            else if (selected == 1){
                                grade[x][y].id = 2;
                                grade[x][y].occupied = true;
                            }
                            else if (selected == 2){
                                grade[x][y].id = 3;
                                grade[x][y].occupied = true;
                            }
                            else if (selected == 3){
                                grade[x][y].id = 4;
                                grade[x][y].occupied = true;
                            }
                        }
                    }
                }
            }
        }
    }
    else if (IsMouseButtonDown(MOUSE_BUTTON_RIGHT)){
        int startx = (int)Pencil.x;
        int starty = (int)Pencil.y;
        for (int x = startx; x < startx + pencil_size; x++){
            for (int y = starty; y < starty + pencil_size; y++){
                if (x >= 0 && x < GW && y > 0 && y < GH){
                    if (grade[x][y].occupied == true){
                        grade[x][y].id = 0;
                        grade[x][y].occupied = false;
                    }
                }
            }
        }
    }
}
void process_pixels(){
    for (int x = GW - 1; x >= 0; x--){
        for (int y = GH - 1; y >= 0; y--){
            if (grade[x][y].id == 1){
                if (y + 1 < 500 && grade[x][y + 1].occupied == false){
                    grade[x][y].id = 0;
                    grade[x][y].occupied = false;
                    grade[x][y + 1].id = 1;
                    grade[x][y + 1].occupied = true;
                }
                else if (y + 1 < 500 && x + 1 < 700 && grade[x + 1][y + 1].occupied == false){
                    grade[x][y].id = 0;
                    grade[x][y].occupied = false;
                    grade[x + 1][y + 1].id = 1;
                    grade[x + 1][y + 1].occupied = true;
                }
                else if (y + 1 < 500 && x - 1 > 0 && grade[x - 1][y + 1].occupied == false){
                    grade[x][y].id = 0;
                    grade[x][y].occupied = false;
                    grade[x - 1][y + 1].id = 1;
                    grade[x - 1][y + 1].occupied = true;
                }
            }
            else if (grade[x][y].id == 2){
                int way = GetRandomValue(0, 1);
                int velocity = 5;
                if (y + 5 < 500 && grade[x][y + 1].occupied == false && grade[x][y + 2].occupied == false && grade[x][y + 3].occupied == false && grade[x][y + 4].occupied == false && grade[x][y + 5].occupied == false){
                    grade[x][y].id = 0;
                    grade[x][y].occupied = false;
                    grade[x][y + velocity].id = 2;
                    grade[x][y + velocity].occupied = true;
                }
                else if (y + 5 < 500 && x + 5 < 700 && grade[x + 1][y + 1].occupied == false && grade[x + 2][y + 2].occupied == false && grade[x + 3][y + 3].occupied == false && grade[x + 4][y + 4].occupied == false && grade[x + 5][y + 5].occupied == false){
                    grade[x][y].id = 0;
                    grade[x][y].occupied = false;
                    grade[x + velocity][y + velocity].id = 2;
                    grade[x + velocity][y + velocity].occupied = true;
                }
                else if (y + 5 < 500 && x - 5 > 0 && grade[x - 1][y + 1].occupied == false && grade[x - 2][y + 2].occupied == false && grade[x - 3][y + 3].occupied == false && grade[x - 4][y + 4].occupied == false && grade[x - 5][y + 5].occupied == false){
                    grade[x][y].id = 0;
                    grade[x][y].occupied = false;
                    grade[x - velocity][y + velocity].id = 2;
                    grade[x - velocity][y + velocity].occupied = true;
                }
                else if (x - 5 > 0 && grade[x - 5][y].occupied == false && way == 0){
                    grade[x][y].id = 0;
                    grade[x][y].occupied = false;
                    grade[x - velocity][y].id = 2;
                    grade[x - velocity][y].occupied = true;
                }
                else if (x + 5 < 700 && grade[x + 5][y].occupied == false && way == 1){
                    grade[x][y].id = 0;
                    grade[x][y].occupied = false;
                    grade[x + velocity][y].id = 2;
                    grade[x + velocity][y].occupied = true;
                }
            }
            else if (grade[x][y].id == 4){
                int way = GetRandomValue(0, 1);
                int velocity = 2;
                if (y + 2 < 500 && grade[x][y + 1].occupied == false && grade[x][y + 2].occupied == false ){
                    grade[x][y].id = 0;
                    grade[x][y].occupied = false;
                    grade[x][y + velocity].id = 4;
                    grade[x][y + velocity].occupied = true;
                }
                else if (y + 2 < 500 && x + 2 < 700 && grade[x + 1][y + 1].occupied == false && grade[x + 2][y + 2].occupied == false ){
                    grade[x][y].id = 0;
                    grade[x][y].occupied = false;
                    grade[x + velocity][y + velocity].id = 4;
                    grade[x + velocity][y + velocity].occupied = true;
                }
                else if (y + 2 < 500 && x - 2 > 0 && grade[x - 1][y + 1].occupied == false && grade[x - 2][y + 2].occupied == false){
                    grade[x][y].id = 0;
                    grade[x][y].occupied = false;
                    grade[x - velocity][y + velocity].id = 4;
                    grade[x - velocity][y + velocity].occupied = true;
                }
                else if (x - 2 > 0 && grade[x - 2][y].occupied == false && way == 0){
                    grade[x][y].id = 0;
                    grade[x][y].occupied = false;
                    grade[x - velocity][y].id = 4;
                    grade[x - velocity][y].occupied = true;
                }
                else if (x + 2 < 700 && grade[x + 2][y].occupied == false && way == 1){
                    grade[x][y].id = 0;
                    grade[x][y].occupied = false;
                    grade[x + velocity][y].id = 4;
                    grade[x + velocity][y].occupied = true;
                }
                else if (x + 1 < 700 && x - 1 > 0 && y + 1 < 500 && y - 1 > 0){
                    if (grade[x + 1][y].id == 2 || grade[x - 1][y].id == 2 || grade[x][y + 1].id == 2 || grade[x][y - 1].id == 2 || grade[x + 1][y + 1].id == 2 || grade[x - 1][y + 1].id == 2 || grade[x + 1][y - 1].id == 2 || grade[x - 1][y - 1].id == 2){
                        grade[x + 1][y].id = 3;
                        grade[x][y].id = 3;
                    }
                }
            }
        }
    }
}
void change_selection(){
    if (GetMouseWheelMoveV().y > 0){
        if (selected + 1 > 3){
            selected = 0;
        }
        else{
            selected += 1;
        }
    }
    else if (GetMouseWheelMoveV().y < 0){
        if (selected - 1 < 0){
            selected = 3;
        }
        else{
            selected -= 1;
        }
    }

    
    Color c;
    if (selected == 0){
        c = YELLOW;
    }
    else if (selected == 1){
        c = BLUE;
    }
    else if (selected == 2){
        c = BLACK;
    }
    else if (selected == 3){
        c = RED;
    }
    DrawRectangle(0, 0, 20, 20, c);
    DrawRectangleLines(0, 0, 20, 20, BROWN);
}
int main(){
    struct nk_context *ctx = InitNuklear(10);
    InitWindow(700, 500, "SandBox");
    SetTargetFPS(120);
    init_grade();
    Image Image = GenImageColor(700, 500, WHITE);
    screen = LoadTextureFromImage(Image);
    UnloadImage(Image);
    while (!(WindowShouldClose())) {
        UpdateNuklear(ctx);

        if (nk_begin(ctx, "Tools", nk_rect(500, 0, 200, 200),NK_WINDOW_BORDER|NK_WINDOW_MOVABLE|NK_WINDOW_MINIMIZABLE)) {
            nk_layout_row_static(ctx, 10, 150, 1);
            nk_text(ctx, "Pencil Size", 12, NK_TEXT_ALIGN_LEFT);
            nk_slider_float(ctx, 10.0f, &pencil_size, 100.0f, 1.0f);
        }
        nk_end(ctx);
        Update_Pencil();
        BeginDrawing();
            Pencil.height = pencil_size;
            Pencil.width = pencil_size;
            ClearBackground(GRAY);
            process_grade();
            show_grade();
            Draw_Pencil();
            if (!nk_item_is_any_active(ctx) && !nk_window_is_any_hovered(ctx)){
                gen_pixel();
            }
            process_pixels();
            change_selection();
            DrawNuklear(ctx);
        EndDrawing();
    }
    UnloadNuklear(ctx);
    CloseWindow();
}