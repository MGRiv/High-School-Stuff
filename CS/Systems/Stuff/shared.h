#ifndef SHARED_H
#define SHARED_H

typedef struct {
  char mini_board[3][3];  // Each board is 3x3 board!
  char winner;            // 0, X, O who won this board?
  char full;              // 0, 1 is this board full?
} board;

extern board super_board[3][3];
board super_board[3][3];
extern char prev[3];
#endif
