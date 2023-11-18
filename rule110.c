// this means i have to write it frim facking scratch without looking at any thinkg hhhhhhhhh
#include <stdio.h>
#include <stdlib.h>
#include <threads.h>
#include <unistd.h>
#include <time.h>

#define ROW_SIZE 53
#define ITTER 100

//Define the structure of the cell and the row
// to facilitate the code we use this enum
typedef enum {
  O = 0,
  I = 1,
} Cell;


#define pattern(A,B,C) ((A<<2)|(B<<1)|C)

Cell patterns[1<<3] = {
  [pattern(O,O,O)] = O,
  [pattern(O,O,I)] = I,
  [pattern(O,I,O)] = I,
  [pattern(O,I,I)] = I,
  [pattern(I,O,O)] = O,
  [pattern(I,O,I)] = I,
  [pattern(I,I,O)] = I,
  [pattern(I,I,I)] = O,
};

typedef struct{
  Cell cells[ROW_SIZE];
} ROW;

ROW next_row(ROW prev){
  ROW next = {0};
  for(int i = 1; i<ROW_SIZE-1;++i){
    next.cells[i] = patterns[pattern(prev.cells[i-1], prev.cells[i] , prev.cells[(i+1)%ROW_SIZE])];
  }
  return next;
}
const char cell_image[2] = {
  [O] = ' ',
  [I] = '*',
};

void print_row(ROW r){
  printf("|");
  for(int i=0; i<ROW_SIZE;++i){
    putc(cell_image[r.cells[i]],stdout);
  }
  printf("|\n");
}

ROW random_row(){
  ROW out = {0};
  for (int i=0;i<ROW_SIZE;++i) {
    out.cells[i] = rand()%2;
    
  }
  return out;
}

int main(int argc, char *argv[])
{
  // srand(time(0));
  ROW next = random_row();

  for (int i=0;i<ITTER;i++) {
    print_row(next);
    next = next_row(next);
    sleep(1);
  }
  
  return EXIT_SUCCESS;
}
