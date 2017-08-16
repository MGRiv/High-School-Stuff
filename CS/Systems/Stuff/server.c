#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <signal.h>
#include <errno.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include "shared.h"

int socket_id, socket_client;
int socket_client_2;
char to_client[85]; // board status + previous r + previous c + board data + \0
char prev[3]; // previous r and previous c + \0

static void sighandler( int signo ) {
  if ( signo == SIGINT ) {
    printf( "Interrupted... how rude!\n" );
    to_client[0] = '5';

    write( socket_client, to_client, 85 );
    close(socket_client);

    write( socket_client_2, to_client, 85);
    close(socket_client_2);
    exit(0);
  }
}



// updates/populates to_client;
void parse_output() {
  int r, n;
  for ( r = 0; r < 3; r++ ) {
    for ( n = 0; n < 27; n++ ) {
      to_client[ 3+n+(27*r) ] = super_board[r][(n/3)%3].mini_board[n/9][n%3];
      //printf( "r: %d, n: %d\n", r, n );
      //printf( "to_client[%d] = super_board[%d][%d].mini_board[%d][%d]\n", 3+n+(27*r), r, (n/3)%3, n/9, n%3 );
      //printf( "|%s|\n", to_client );
    }
  }
}



int main() {

  signal( SIGINT, sighandler );

  struct sockaddr_in listener;
  char from_client[5];
  int option = 1;
  int f = 1;
  int t = 0;
  prev[2] = 0;
  to_client[0] = '4';
  to_client[84] = 0;
  board_init();

  while (1) {

    //instructions for parent, or any server process that has yet to connect to clients
    if (f) {
      //create the socket
      socket_id = socket( AF_INET, SOCK_STREAM, 0 );
      setsockopt( socket_id, SOL_SOCKET, SO_REUSEADDR, &option, sizeof(option) );
      //bind to port/address
      //struct sockaddr_in listener;
      listener.sin_family = AF_INET;  //socket type IPv4
      listener.sin_port = htons(5000); //port #
      listener.sin_addr.s_addr = INADDR_ANY; //bind to any incoming address
      bind( socket_id, (struct sockaddr *)&listener, sizeof(listener) );
  
      listen( socket_id, 2 );
      printf("<server> listening\n");
      // player 1 connection
      socket_client = accept( socket_id, NULL, NULL );
      if ( socket_client < 0 ) printf( "ERROR: %s\n", strerror(errno) );
      printf( "<server> connected: %d\n", socket_client );

      // player 2 connection
      socket_client_2 = accept( socket_id, NULL, NULL );
      if( socket_client_2 < 0 )	printf( "ERROR: %s\n", strerror(errno) );
      printf( "<server> connected: %d\n", socket_client_2 );

      printf("<server> Waiting for player 1 to be ready\n");
      read( socket_client, from_client, sizeof(from_client) );
      printf("<server> Waiting for player 2 to be ready\n");
      read (socket_client_2, from_client, sizeof(from_client) );

      f = fork();
    }

    //errno
    if ( f < 0 ) {
      printf( "%s\n", strerror(errno) );
    }

    //instructions for child
    if ( !f ) {

      if( !t ) {
	//receive and send for player 1
	printf("<child server> Writing board to player 1\n");
	parse_output();
	write( socket_client, to_client, sizeof(to_client) );

	printf("<child server> Reading, waiting for player 1's response\n");
	read( socket_client, from_client, sizeof(from_client) );
	printf( "Received <%s> from player 1\n", from_client );
	printf("Initiate Turn\n");
	t = turn( 'X', from_client[0], from_client[1], from_client[2], from_client[3] );
	printf("\nMove Taken\n");
	prev[0] = from_client[2];
	prev[1] = from_client[3];
	if ( super_board[prev[0]][prev[1]].full ) {
	  // errno for trying to play in a full board is 4
	  prev[0] = '4';
	  prev[1] = '4';
	  to_client[1] = '4';
	  to_client[2] = '4';
	}
	
	if ( !t ) {
	  // no error. receive and send for player 2
	  //wait for player 2 to be ready
	  printf("<child server> sending board to player 2\n");
	  parse_output();
	  write( socket_client_2, to_client, sizeof(to_client) );
	  printf("waiting for player 2 response\n");
	  read( socket_client_2, from_client, sizeof(from_client) );
	  printf("received <%s> from player 2\n",from_client);
	  printf("initiate player 2's turn\n");
	  t = turn( 'O', from_client[0], from_client[1], from_client[2], from_client[3] );
	  prev[0] = from_client[2];
	  prev[1] = from_client[3];
	  if ( super_board[prev[0]][prev[1]].full ){
	    // errno for trying to play in a full board is 4
	    prev[0] = '4';
	    prev[1] = '4';
	    to_client[1] = '4';
	    to_client[2] = '4';
	  }
	}

	switch (t) {
	case 1:
	  // space was taken
	  to_client[0] = '1';
	  write( socket_client, to_client, sizeof(to_client) );
	  
	case 2:
	  //if X won
	  to_client[0] = '2';
	  write( socket_client, to_client, sizeof(to_client) );
	  to_client[0] = '3';
	  write( socket_client_2, to_client, sizeof(to_client));
	  
	case 3:
	  //if O won
	  to_client[0] = '3';
	  write( socket_client, to_client, sizeof(to_client) );
	  to_client[0] = '2';
	  write( socket_client_2, to_client, sizeof(to_client) ); 
	
	}
	if ( t == 2 || t == 3 ) {
	  //exit on win
	  printf( "Game Over.\n" );
	  close(socket_client);
	  close(socket_client_2);
	  exit(0);
	}
	
      }
      
    }
    
    else {
      // parent closes connections, waits for new connections
      close(socket_client);
      close(socket_client_2);
    }
  }
  
  return 0;
}
