#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <windows.h>
#include <conio.h>
#include <unistd.h>
#include <time.h>

// map variables
struct Point {
    int x, y;
};

enum Direction {
    UP, RIGHT, DOWN, LEFT
};

int coins = 25, random_coin = 25;
int x_coins[30], y_coins[30];
int x_player = 25, y_player = 12;
const int width = 50, height = 25;
int x_enemy = 0, y_enemy = 0;
char map[65][65];

// utilities
void hide_cursor() {
   HANDLE consoleHandle = GetStdHandle(STD_OUTPUT_HANDLE);
   CONSOLE_CURSOR_INFO info;
   info.dwSize = 100;
   info.bVisible = FALSE;
   SetConsoleCursorInfo(consoleHandle, &info);
}

int random_number_gen(int a, int b) {
    srand(time(NULL));
    int num = rand() % b + a;
    return num;
}

void delay() {
    for(int i = 0; i < 1000000000; i++);
}

// generate_enemy
void spawn_enemy() {
    bool flag = false;
    int x, y;
    while(!flag) {
        srand(time(NULL));
        x = rand() % width;
        y = rand() % height;
        if(map[y][x] == ' ') {
            map[y][x] = 'V';
            x_enemy = x;
            y_enemy = y;
            flag = true;
        }
    }
}

void move_enemy() {
    srand(time(NULL));
    bool flag = false;
    while (!flag) {
        int move = rand() % 4;
        printf("%d\n", move);
        if(move == 0 && map[y_enemy + 1][x_enemy] == ' ') {
            map[y_enemy][x_enemy] = ' ';
            map[y_enemy + 1][x_enemy] = 'V';
            y_enemy += 1;
            flag = true;
        }
        else if(move == 1 && map[y_enemy - 1][x_enemy] == ' ') {
            map[y_enemy][x_enemy] = ' ';
            map[y_enemy - 1][x_enemy] = 'V';
            y_enemy -= 1;
            flag = true;
        }
        else if(move == 2 && map[y_enemy][x_enemy + 1] == ' ') {
            map[y_enemy][x_enemy] = ' ';
            map[y_enemy][x_enemy + 1] = 'V';
            x_enemy += 1;
            flag = true;
        }
        else if(move == 3 && map[y_enemy][x_enemy - 1] == ' ') {
            map[y_enemy][x_enemy] = ' ';
            map[y_enemy][x_enemy - 1] = 'V';
            x_enemy -= 1;
            flag = true;
        }
    }
    
}

bool check_losing() {
    if(x_enemy == x_player && y_enemy == y_player) {
        return true;
    }
    else {
        return false;
    }
}

// Generate the map
void init() { // initiate wall on the map
    for(int i = 0; i < height; i++)  {
        for(int j = 0; j < width; j++) {
            map[i][j] = 178;
        }
    }
}

void display_map() {
    hide_cursor();
    // printf("Position: %d %d\n", x_player, y_player);
    system("cls");
    for(int i = 0; i < height; i++) {
        for(int j = 0; j < width; j++) {
            if(y_player == i && x_player == j) {
                map[i][j] = 'O';
            }
            printf("%c", map[i][j]);
        }
        puts("");
    }
    printf("Coins left: %d\n", coins);
}

int is_valid(Point p) {
    // validation to keep the maze stay in border
    if(p.x > 0 && p.x < width - 1 && p.y > 0 && p.y < height - 1 && map[p.y][p.x] != ' ') {
        return 1;
    }
    return 0;
}

int can_connect(Point p) {
    // validation to keep the maze stay in border
    if(p.x > 0 && p.x < width - 1 && p.y > 0 && p.y < height - 1 && map[p.y][p.x] == ' ') {
        return 1;
    }
    return 0;
}

void connnect(Point src, Point dst) {
    map[dst.y][dst.x] = ' ';
    int x = src.x;
    int y = src.y;

    if(dst.x > x) {
        x += 1;
    }
    else if(dst.x < x) {
        x -= 1;
    }
    else if(dst.y > y) {
        y += 1;
    }
    else if(dst.y < y) {
        y -= 1;
    }
    map[y][x] = ' ';
}

Point get_position(Point p, Direction d) {
    if(d == UP) {
        return Point{p.x, p.y - 2};
    }
    if(d == DOWN) {
        return Point{p.x, p.y + 2};
    }
    if(d == LEFT) {
        return Point{p.x - 2, p.y};
    }
    if(d == RIGHT) {
        return Point{p.x + 2, p.y};
    }
}

// get a frontier -> pick 4 different locations 
void get_frontier(Point curr, Point frontier[], int *frontier_size) {
    for(int i = 0; i < 4; i++) {
        Point candidate = get_position(curr, Direction(i));
        if(is_valid(candidate) == 1) {
            int is_exist = 0;
            // checking wether the candidate is located in the array or not
            for(int j = 0; j < *frontier_size; j++) {
                Point curr_frontier = frontier[j];
                if(curr_frontier.x == candidate.x && curr_frontier.y == candidate.y) {
                    // candidate is located in the array
                    is_exist = 1;
                    break;
                }
            }
            if(is_exist == 1) {
                continue;
            }
            frontier[*frontier_size] = candidate;
            map[candidate.y][candidate.x] = '*'; // debug
            *frontier_size += 1;
        }
    }
}

void shift_array(Point frontier[], int frontier_size, int delete_frontier) {
    for(int i = delete_frontier; i < frontier_size - 1; i++) {
         frontier[i] = frontier[i + 1];
    }
}

void generate_maze() {
    // initiate a random node
    int init_x= -1, init_y = -1;
    while(is_valid(Point{init_x, init_y}) == 0 || init_x % 2 != 1 || init_y % 2 != 1) {
        init_x = rand() % width;
        init_y = rand() % height;
    }
    map[init_y][init_x] = ' ';
    // create frontier lists
    Point frontier[width * height + 5]; 
    int frontier_size = 0;
    get_frontier(Point{init_x, init_y}, frontier, &frontier_size);

    // expand the maze
    while(frontier_size > 0) {
        int curr_frontier_idx = rand() % frontier_size;
        Point curr_frontier = frontier[curr_frontier_idx];
        // Find the connections
        Direction connect_dir;
        Point connect_position;

        do {
            connect_dir = Direction(rand() % 4); // 4 directions
            connect_position = get_position(curr_frontier, connect_dir);
        } while(can_connect(connect_position) == 0);
        // connect the line
        connnect(connect_position, curr_frontier);
        shift_array(frontier, frontier_size, curr_frontier_idx);
        frontier_size -= 1;
        get_frontier(curr_frontier, frontier, &frontier_size);
    }
}

// generate coin
void generate_coin() {
    int i = 0;
    while(random_coin > 0) {
        int x = rand() % width;
        int y = rand() % height;
        if(map[y][x] == ' ') {
            map[y][x] = '*';
            x_coins[i] = x;
            y_coins[i] = y;
            random_coin -= 1;
            i += 1;
            // printf("%d\n", random_coin);
            // delay();
        }
    }
}

void randomize_map() {
    srand(time(NULL));
    init();
    generate_maze();
    generate_coin();
    spawn_enemy();
    display_map();
}

void validate_coin() {
    if(map[y_player][x_player] == '*') {
        coins -= 1;
    }
 }

bool check_winning() {
    if(coins <= 0) {
        return true;
    }
    else return false;
}

// generate movement for player
void player_movement() {
    bool flag = true;
    while(flag) {
        if(kbhit()) {
            char ch = getch();
            if(ch == 'w' || ch == 'W') {
                if(map[y_player - 1][x_player] == ' ' || map[y_player - 1][x_player] == '*') {
                    map[y_player][x_player] = ' ';  
                    y_player -= 1;
                }
            }

            else if(ch == 'a' || ch == 'A'){
                if(map[y_player][x_player - 1] == ' ' || map[y_player][x_player - 1] == '*') {
                    map[y_player][x_player] = ' ';   
                    x_player -= 1;
                }
            }

            else if(ch == 'd' || ch == 'D'){
                if(map[y_player][x_player + 1] == ' ' || map[y_player][x_player + 1] == '*') {
                    map[y_player][x_player] = ' ';   
                    x_player += 1;
                }
            }
            
            else if(ch == 's' || ch == 'S'){
                if(map[y_player + 1][x_player] == ' ' || map[y_player + 1][x_player] == '*') {
                    map[y_player][x_player] = ' ';   
                    y_player += 1;
                }
            }
            validate_coin();
            move_enemy();
            if(check_winning()) {
                system("cls");
                puts("Live by Nightlight");
                break;
            }
            if(check_losing()) {
                system("cls");
                puts("Dead by daylight");
                break;
            }
            system("cls");
            display_map();
        }
    }
}

// win and lose condition
void win_lose() {
    if(coins <= 0) {
        system("cls");
        puts("Live by Nightlive");
    }
    else if(x_enemy == x_player && y_enemy == y_player) {
        system("cls");
        puts("Dead by Daylight");
    }
}

int main() {
    randomize_map();
    player_movement();
    return 0;
}
