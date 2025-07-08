#include <stdio.h>
#include <unistd.h>
#include <time.h>
#include <fcntl.h>

#define GRID_COLS 35
#define GRID_ROWS 35
#define GRID_CELLS (GRID_COLS*GRID_ROWS)
#define ALIVE '*'
#define DEAD '.'

int cell_to_index(int x, int y){
     if (x < 0){
        x = (-x) % GRID_COLS;
        x = GRID_COLS - x;
     }
     if (y < 0){
        y = (-y) % GRID_ROWS;
        y = GRID_ROWS - y;
     }
     if (x > GRID_COLS) x = x % GRID_COLS;
     if (y > GRID_ROWS) y = y % GRID_ROWS;
     return y*GRID_COLS+x;
}
/* this function sets the specified cell at x,y to the specified state */
void set_cell(char *grid, int x, int y, char state){
  //grid[y*GRID_COLS+x] = state;
  grid[cell_to_index(x,y)] = state;
}

/* this function sets the specified cell a */
char get_cell(char *grid, int x, int y){
   //return grid[y*GRID_COLS+x];
   return grid[cell_to_index(x,y)];
}

void print_grid(char *grid){
    printf("\x1b[3J\x1b[H\x1b[2J"); // Clear screen.
    for (int y = 0; y < GRID_ROWS; y++){
      for (int x = 0; x < GRID_COLS; x++){
         printf("%c", get_cell(grid,x,y));
    }
         printf("\n")    ;
  }
}

/* set all the grid*/
void set_grid(char *grid, char state){
  for (int y = 0; y < GRID_ROWS; y++){
      for (int x = 0; x < GRID_COLS; x++){
        set_cell(grid,x,y,state);
    }
  }
}
/* Return the number of living cells neighbors of x,y. */
int count_living_neighbors(char *grid, int x, int y){
      int alive = 0;

     alive =
      (get_cell(grid, x-1, y) == ALIVE) +
      (get_cell(grid, x-1, y-1) == ALIVE) +
      (get_cell(grid, x, y-1) == ALIVE) +
      (get_cell(grid, x+1, y) == ALIVE) +
      (get_cell(grid, x+1, y+1) == ALIVE) +
      (get_cell(grid, x, y+1) == ALIVE) +
      (get_cell(grid, x-1, y+1) == ALIVE) +
      (get_cell(grid, x+1, y-1) == ALIVE);

     return alive;
   //for (int yo = -1; yo <= 1; yo++) {
     //   for (int xo = -1; xo <= 1; xo++) {
       //     if (xo == 0 && yo == 0) continue;
         //   if (get_cell(grid,x+xo,y+yo) == ALIVE) alive++;
       // }
    // }

}

/* compute new state of GoL */
void compute_new_state(char **old, char *new){
 for (int y = 0; y < GRID_ROWS; y++){
      for (int x = 0; x < GRID_COLS; x++){
        //set_cell(old,x,y,state);
        int n_alive = count_living_neighbors(old,x,y);
        int new_state = DEAD;
        if (get_cell(old,x,y) == ALIVE){
           if (n_alive == 2 || n_alive == 3)
            new_state = ALIVE; // set_cell(old_grid,x,y,ALIVE);
           } else { if (n_alive == 3)
            new_state = ALIVE;
        }
        set_cell(new,x,y,new_state);
    }
  }
}

int main()
{
    int int_clock;
    time_t start_time, end_time;
    char old_grid[GRID_CELLS];
    char new_grid[GRID_CELLS];
    set_grid(old_grid,DEAD);
    set_cell(old_grid,18,18,ALIVE);
    set_cell(old_grid,18,19,ALIVE);
    set_cell(old_grid,18,17,ALIVE);
    set_cell(old_grid,18,16,ALIVE);
    int redirect_fd = open("redirect_stdout_conway_2.txt", O_CREAT | O_TRUNC | O_WRONLY);
    dup2(redirect_fd, STDOUT_FILENO);
    //dup2(STDOUT_FILENO, redirect_fd);
    print_grid(old_grid);

    sleep(2);
    time(&start_time);
    int_clock = 0;
    while(1){
        int_clock++;
        compute_new_state(old_grid,new_grid);
        print_grid(new_grid);
        printf("Numero di passi: %d\n", int_clock);
        usleep(250000);
        compute_new_state(new_grid,old_grid);
        print_grid(old_grid);
        printf("Numero di passi: %d\n", int_clock);
        usleep(250000);
        time(&end_time);
        if (difftime(end_time, start_time) >= 20.0){
         break;
        }
        if (memcmp(old_grid, new_grid, sizeof(old_grid)) == 0) {
    // arrays are equal
         break;
        }
    }
    return 0;
}
