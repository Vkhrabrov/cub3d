#include <stdio.h>
#include <stdbool.h>
#include <string.h>

#define MAP_WIDTH 18
#define MAP_HEIGHT 7

char map[MAP_HEIGHT][MAP_WIDTH] = {
    "1111 1111    1111",
    "1001110011  11001",
    "100001111    1001",
    "100001    1111001",
    "10000111111000001",
    "10000000000000001",
    "11111111111111111"
};

bool visited[MAP_HEIGHT][MAP_WIDTH];

bool is_valid(int x, int y) {
    return x >= 0 && x < MAP_HEIGHT && y >= 0 && y < MAP_WIDTH;
}

void flood_fill(int x, int y) {
    if (!is_valid(x, y) || map[x][y] != '0' || visited[x][y])
        return;

    visited[x][y] = true;

    flood_fill(x + 1, y); // down
    flood_fill(x - 1, y); // up
    flood_fill(x, y + 1); // right
    flood_fill(x, y - 1); // left
}

bool check_map() {
    // Initialize visited array
    memset(visited, 0, sizeof(visited));

    // Flood-fill from the border
    for (int i = 0; i < MAP_HEIGHT; i++) {
        for (int j = 0; j < MAP_WIDTH; j++) {
            if ((i == 0 || i == MAP_HEIGHT - 1 || j == 0 || j == MAP_WIDTH - 1) && map[i][j] == '1')
                flood_fill(i, j);
        }
    }

    // Check if there are any unvisited cells inside the border
    for (int i = 0; i < MAP_HEIGHT; i++) {
        for (int j = 0; j < MAP_WIDTH; j++) {
            if (map[i][j] == '1' && !visited[i][j]) {
                return false; // Found an unvisited cell inside the border
            }
        }
    }

    return true; // All border cells are properly enclosed
}

int main() {
    if (check_map()) {
        printf("The map border is closed.\n");
    } else {
        printf("The map border is not closed.\n");
    }

    return 0;
}
