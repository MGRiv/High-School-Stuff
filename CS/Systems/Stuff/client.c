#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <errno.h>

#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>


int main(){
  char* clear = "\x1b[2J";
  char* hide =  "\x1b[?25l";
  char* show =  "\x1b[?25h";
  char* go = "\x1b[0;0H";
  int socket_id = socket(AF_INET, SOCK_STREAM,0);

  //server to client board stuff
  char from_server[85];
  from_server[85] = 0;

  //client input stuff
  char user_input[4];

  //client to server stuff
  char to_server[5];

  char init[2];
  int i;
  int addrs;
  char *server_ip = "127.0.0.1";
  
  struct sockaddr_in sock;
  sock.sin_family = AF_INET;
  sock.sin_port = htons(5000);
  inet_aton( server_ip, &(sock.sin_addr) );
  bind( socket_id, (struct sockaddr*)&sock, sizeof(sock) );
  i = connect( socket_id, (struct sockaddr*)&sock, sizeof(sock) );
  //printf("Connected to socket: %d\n", i);
  //printf( "error: %s\n", strerror(errno) );
  

  printf("""%s %s %sWelcome to Ultimate Tic-Tac-Toe, the better way to play!\nAre you tired of ordinary Tic-Tac-Toe? Is the game is too simple for you?\nHave you gotten so good that you can never lose?\n\nWell then, Ultimate Tic-Tac-Toe is the game for you!\nUltimate Tic-Tac-Toe has the same goal as the original game: get three in a row.\nHowever, in Ultimate TTT, you need to win another game of Tic-Tac-Toe to even make a mark on the board! Nested in each square is its own 3x3 tic-tac-toe board. You need to get three squares in a row on the smaller board to win on that larger square. When you win 3 of those in a row, you've just won Ultimate Tic-Tac-Toe!\n\nThere is one more catch though. The game starts with one player making a mark in any\nsquare on any of the nine boards. Then the other player must make a mark on the smaller board that corresponds to where the first player played.\nIf a mark is made in the upper lefthand corner of one of the smaller boards, then the next player's mark must be made somewhere on the upper lefthand board.\n\nHAVE FUN!!!\n(Press enter to continue)\n""", hide, clear, go );
  fgets( init, sizeof(init), stdin );
  //printf("read from user: |%s|\n", init);
  strcpy( to_server, "0000" );
  printf("Please wait for your opponent.\n\n");
  
  while (1) {
    //tell server that client is ready for info
    write( socket_id, to_server, sizeof(to_server) );

    //Reads in initial game
    read( socket_id, from_server, sizeof(from_server) );
    //printf( "%d\n", strlen(from_server) );
    //printf( "read from socket: |%s|\n", from_server);

    //printf("Begin printing\n");
    /*int i = 3;
    int j = 0;
    int k = 0;
    char outpu[612];
    //outpu is the board display of 35x17
    //to account for \n 36*17= 612
    //rows are larger due to the following format
    // 4 | 6 | 7 =  0
    //-----------=  1
    // 5 | 9 | 0 =  2   <- upper left corner design
    //-----------=  3
    // 1 | 3 | 8 =  4
    //============  5
    //123456789012
    while ( k < 17 ) {
      //checks if odd or even row
      if ( (k % 2) == 1){
	if ( ((j + 1) % 4) == 0 ) {
	  if ( ((j + 1) % 12) == 0 ) {
	    outpu[j] = '=';
	  } else {
	    outpu[j] = '+';
	  }
	} else {
	  outpu[j] = '-';
	}
      } else {
	if ( (j % 2) == 0 ) {
	  outpu[j] = ' ';
	} else {
	  if ( ((j + 1) % 12) == 0 ) {
	    outpu[j] = '=';
	  } else if ( ((j + 1) % 4) == 0 ) {
	    outpu[j] = '|';
	  } else {
	    outpu[j] = from_server[i];
	    i++;
	  }
	}
      }
      j++;
      if ( j == 35 ) {
	k++;
	outpu[j] = '\n';
	j++;
      }
    }
    //Prints board
    printf("%s %s %s%s",hide,clear,go,from_server);
*/
    int wow;
    for( wow = 0; wow < 9; wow++ ){
      printf("%.9s\n",from_server + 3 + (9 * wow));
    }

    // Respond to opponent's move. 
    char R;
    char C;
    char r;
    char c;
    switch (from_server[0]) {

    case '0':
      R = from_server[1];
      C = from_server[2];
      break;

    case '1':
      printf( "Sorry, that space is already occupied. Please try again.\n" );
      from_server[0] = '4';

    case '2':
      printf( "Congratulations, you win! :)\n" );
      exit(0);

    case '3':
      printf( "Sorry, you lose :(\n");
      exit(0);

    case '4':
      printf("\nPlease choose which of the larger boards you would like to make your move on.\nPlease select the row(0-2) and column(0-2) of the larger board(R,C)\nwhere 0,0 is the top left.\n");
      while (1) {
	fgets( user_input, sizeof(user_input), stdin );
	printf( "user_input: |%s|\n", user_input );
	if ( (user_input[0] >= '0' && user_input[0] < '3') &&
	     (user_input[2] >= '0' && user_input[2] < '3') ) {
	  R = user_input[0];
	  C = user_input[2];
	  break;
	}
	else {
	  printf( "Sorry, did you use numbers from 0-2 and type it in the correct format?\nTry typing your move as R,C, where R is the row and C is the column.\n" );
	}
      }
      break;

    case '5':
      printf( "Server disconnected unexpectedly\n" );
      exit(EXIT_FAILURE);
    }

    //Ask for square
    char *strR;
    char *strC;
    switch (R) {
    case '0':
      strR = "upper";
      break;
    case '1':
      strR = "center";
      break;
    case '2':
      strR = "lower";
      break;
    }

    switch (C) {
    case '0':
      strC = "left";
      break;
    case '1':
      strC = "middle";
      break;
    case '2':
      strC = "right";
      break;
    }

    while (1) {
      printf("\nNow choose which of the squares to play on in the %s %s board.\nPlease select the row(0-2) and column(0-2) of the smaller board(r,c)\nwhere (0,0) is the top left corner\n", strR, strC );
      fgets( user_input, sizeof(user_input), stdin );
      if ( (user_input[0] >= '0' && user_input[0] < '3') &&
	   (user_input[2] >= '0' && user_input[2] < '3') ) {
	r = user_input[0];
	c = user_input[2];
	break;
      }
      else {
	printf( "Sorry, did you use numbers from 0-2 and type it in the correct format?\nTry typing your move as R,C, where R is the row and C is the column.\n" );
      }
    }

    printf("\nPlease wait for your opponent's turn\n");
    to_server[0] = R;
    to_server[1] = C;
    to_server[2] = r;
    to_server[3] = c;
    to_server[4] = 0;
    write( socket_id, to_server, 5 );
  }
  
  //printf( "%s %s %s%s", hide, clear, go, from_server );
  //hide,clear,go,stuff,\n,show
  return 0;
}
