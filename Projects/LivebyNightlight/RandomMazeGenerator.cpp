#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>

// the map will looks better if you use an odd number
const int MAX = 21, width = 21, height = 21;
char map[60][60];

struct Point {
    int x, y;
};

enum Direction {
    UP, RIGHT, DOWN, LEFT
};


void init() { // initiate wall on the map
    for(int i = 0; i < height; i++)  {
        for(int j = 0; j < width; j++) {
            map[i][j] = '#';
        }
    }
}

void display_map() {
    for(int i = 0; i < height; i++)  {
        for(int j = 0; j < width; j++) {
            printf("%c", map[i][j]);
        }
        puts("");
    }
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

int main() {
    srand(time(NULL));
    init();
    generate_maze();
    display_map();
    return 0;
}
