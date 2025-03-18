#include <ncurses.h>
#include <stdlib.h>
#include <unistd.h>
#include <time.h>

#define WIDTH 40
#define HEIGHT 20
#define DELAY 200000  // microseconds between moves

// Directions
typedef enum { UP, DOWN, LEFT, RIGHT } Direction;

// Linked list node for the snake's body
typedef struct SnakeNode {
    int x, y;
    struct SnakeNode *next;
} SnakeNode;

SnakeNode *head = NULL;   // pointer to snake head (front)
SnakeNode *tail = NULL;   // pointer to snake tail (end)

// Game state variables
int food_x, food_y;
int score = 0;
Direction dir = RIGHT;

// Function prototypes
void init_game();
void end_game();
void add_head(int x, int y);
void remove_tail();
int collision(int x, int y);
void place_food();
void draw_game();
void free_snake();
void update_direction(int ch);

int main() {
    int ch;
    int new_x, new_y;
    
    // Initialize ncurses
    initscr();
    noecho();
    curs_set(FALSE);
    keypad(stdscr, TRUE);
    nodelay(stdscr, TRUE); // non-blocking input
    timeout(0);
    
    srand(time(0));
    init_game();
    place_food();

    // Main game loop
    while (1) {
        ch = getch();
        update_direction(ch);
        
        // Determine new head position based on current direction
        new_x = head->x;
        new_y = head->y;
        switch (dir) {
            case UP:    new_y--; break;
            case DOWN:  new_y++; break;
            case LEFT:  new_x--; break;
            case RIGHT: new_x++; break;
        }
        
        // Check collisions with walls
        if (new_x <= 0 || new_x >= WIDTH-1 || new_y <= 0 || new_y >= HEIGHT-1) {
            break; // game over
        }
        
        // Check collision with self
        if (collision(new_x, new_y)) {
            break; // game over
        }
        
        // Add new head node
        add_head(new_x, new_y);
        
        // Check if food is eaten
        if (new_x == food_x && new_y == food_y) {
            score += 10;
            place_food(); // generate new food
        } else {
            // Remove tail if no food eaten (snake moves forward)
            remove_tail();
        }
        
        draw_game();
        usleep(DELAY);
    }
    
    // Game Over
    end_game();
    free_snake();
    return 0;
}

// Initialize snake with a starting length of 3 in the middle of the board
void init_game() {
    int mid_x = WIDTH / 2;
    int mid_y = HEIGHT / 2;
    
    // Create initial snake: tail -> middle -> head (moving right)
    add_head(mid_x, mid_y);
    add_head(mid_x + 1, mid_y);
    add_head(mid_x + 2, mid_y);
}

// Free allocated ncurses resources and display game over message
void end_game() {
    clear();
    mvprintw(HEIGHT / 2, (WIDTH - 10) / 2, "Game Over!");
    mvprintw(HEIGHT / 2 + 1, (WIDTH - 20) / 2, "Final Score: %d", score);
    refresh();
    nodelay(stdscr, FALSE);
    getch();
    endwin();
}

// Add a new node at the beginning of the snake (the head)
void add_head(int x, int y) {
    SnakeNode *node = malloc(sizeof(SnakeNode));
    node->x = x;
    node->y = y;
    node->next = head;
    head = node;
    
    // If the snake was empty, set tail to new node
    if (tail == NULL)
        tail = node;
}

// Remove the tail node of the snake
void remove_tail() {
    // If only one node exists, do nothing
    if (head == tail)
        return;
    
    SnakeNode *current = head;
    // Traverse until node just before tail
    while (current->next != tail) {
        current = current->next;
    }
    free(tail);
    tail = current;
    tail->next = NULL;
}

// Check if the given position collides with any part of the snake
int collision(int x, int y) {
    SnakeNode *current = head;
    while (current != NULL) {
        if (current->x == x && current->y == y)
            return 1;
        current = current->next;
    }
    return 0;
}

// Place food randomly within the board (not on walls or snake body)
void place_food() {
    do {
        food_x = rand() % (WIDTH - 2) + 1;
        food_y = rand() % (HEIGHT - 2) + 1;
    } while (collision(food_x, food_y));
}

// Draw the game board, snake, and food
void draw_game() {
    clear();
    
    // Draw top and bottom borders
    for (int i = 0; i < WIDTH; i++) {
        mvprintw(0, i, "#");
        mvprintw(HEIGHT-1, i, "#");
    }
    // Draw left and right borders
    for (int i = 1; i < HEIGHT-1; i++) {
        mvprintw(i, 0, "#");
        mvprintw(i, WIDTH-1, "#");
    }
    
    // Draw food
    mvprintw(food_y, food_x, "*");
    
    // Draw snake (head as 'O', body as 'o')
    SnakeNode *current = head;
    int first = 1;
    while (current != NULL) {
        if (first) {
            mvprintw(current->y, current->x, "O");
            first = 0;
        } else {
            mvprintw(current->y, current->x, "o");
        }
        current = current->next;
    }
    
    // Display score
    mvprintw(HEIGHT, 0, "Score: %d", score);
    refresh();
}

// Free all nodes in the snake's linked list
void free_snake() {
    SnakeNode *current = head;
    while (current != NULL) {
        SnakeNode *temp = current;
        current = current->next;
        free(temp);
    }
}

// Update snake's direction based on key input
void update_direction(int ch) {
    switch(ch) {
        case KEY_UP:
            if (dir != DOWN) dir = UP;
            break;
        case KEY_DOWN:
            if (dir != UP) dir = DOWN;
            break;
        case KEY_LEFT:
            if (dir != RIGHT) dir = LEFT;
            break;
        case KEY_RIGHT:
            if (dir != LEFT) dir = RIGHT;
            break;
        case 'q':  // Allow quitting the game
            end_game();
            free_snake();
            exit(0);
    }
}

