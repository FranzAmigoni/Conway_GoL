Conway Game of Life as expalined in the 8th lesson from antirez in this YT channel

Working code is on CodeBlocks, maybe one day I will use it here.
open() and dup2() are working only if the file is newly created. Not possible to change an existing one;
Putting the printf into a file is much quicker, insted of 25 steps, 38 were executed!!

Seed for The Champions.png
    set_cell(old_grid,18,18,ALIVE);
    set_cell(old_grid,18,19,ALIVE);
    set_cell(old_grid,18,17,ALIVE);
    set_cell(old_grid,18,16,ALIVE);
    set_cell(old_grid,19,19,ALIVE);
    set_cell(old_grid,17,19,ALIVE);
