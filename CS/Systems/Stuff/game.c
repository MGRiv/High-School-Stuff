#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>

#include "game.h"

void board_init() {
  // initialize empty board
  int R, C, r, c;
  
  for ( R = 0; R < 3; R++) {
    for ( C = 0; C < 3; C++) {
      for ( r = 0; r < 3; r++) {
	for ( c = 0; c < 3; c++) {
	  super_board[R][C].mini_board[r][c] = '0';
	}
      }
      super_board[R][C].winner = 0;
      super_board[R][C].full = 0;
    }
  }

}

char check_win() {
  //check to see if the super_board is won
  //return 0, X, O depending on who won
  int r, c;

  if ( ( super_board[1][1].winner == super_board[0][2].winner &&
	 super_board[1][1].winner == super_board[2][0].winner ) ||
       ( super_board[0][0].winner == super_board[1][1].winner &&
	 super_board[0][0].winner == super_board[2][2].winner ) ) {
    //if diagonals are all the same, return the winner
    //note that if a diagonal is all 0s, row/column wins are impossible
    return super_board[1][1].winner;
  }

  for ( c = 0; c < 3; c++) {
    if ( super_board[0][c].winner == super_board[1][c].winner &&
	 super_board[0][c].winner == super_board[2][c].winner ) {
      //if any column is all the same, return the winner
      return super_board[0][c].winner;
    }
  }

  for ( r = 0; r < 3; r++) {
    if ( super_board[r][0].winner == super_board[r][1].winner &&
         super_board[r][0].winner == super_board[r][2].winner ) {
      // if any row is all the same, return the winner
      return super_board[r][0].winner;
    }
  }

  return 0;
}


int turn( char player, int R, int C, int r, int c) {
  // react to player input
  /* return 0 if game continues normally
   * return 1 if square is already taken
   * return 2 if X wins
   * return 3 if O wins
   */
  
  if ( super_board[R][C].mini_board[r][c] ) {
    //if the space is already taken
    return 1;
  }
  else {
    super_board[R][C].mini_board[r][c] = player;
    update_full( super_board[R][C] );
    update_winner( super_board[R][C] );

    switch (check_win()) {
    case 'X': return 2;
    case 'O': return 3;
    }

    return 0;
  }
}



void update_winner( board b ) {
  // check to see if a mini_board is won
  // update winner variable accordingly
  int r, c;

  if ( b.winner ) {
    // if the board already has a winner
    return;
  }

  if ( ( b.mini_board[0][2] == b.mini_board[1][1] &&
	 b.mini_board[1][1] == b.mini_board[2][0] ) ||
       ( b.mini_board[0][0] == b.mini_board[1][1] &&
	 b.mini_board[1][1] == b.mini_board[2][2] ) ) {
    //if diagonals are all the same, return the winner
    //note that if a diagonal is all 0s, row/column wins are impossible
    b.winner = b.mini_board[1][1];
  }

  for ( c = 0; c < 3; c++) {
    if ( b.mini_board[0][c] == b.mini_board[1][c] &&
	 b.mini_board[1][c] == b.mini_board[2][c] ) {
      //if any column is all the same, return the winner
      b.winner = b.mini_board[0][c];
    }
  }

  for ( r = 0; r < 3; r++) {
    if ( b.mini_board[r][0] == b.mini_board[r][1] &&
	 b.mini_board[r][1] == b.mini_board[r][2] ) {
      // if any row is all the same, return the winner
      b.winner = b.mini_board[r][0];
    }
  }

}


void update_full( board b ) {
  // update full variable
  int r, c;
  b.full = 1;

  for ( r = 0; r < 3; r++ ) {
    for ( c = 0; c < 3; c++ ) {
      if ( b.mini_board[r][c] == 0 ) {
	b.full = 0;
      }
    }
  }
  
}
