#include <stdio.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <netdb.h>
#include <unistd.h>
#include <string.h>
#include <unistd.h>
#include <time.h>
#include <iostream>

enum classname{car = 1, person = 2, other = 0};

struct detection{
    int classtype;
    double confidence;
    double box[4];
};


int main() {
  /* IPアドレス、ポート番号、ソケット */
  //char destination[80];
  unsigned short port = 9876;
  int destSocket;

  /* sockaddr_in 構造体 */
  struct sockaddr_in destSockAddr;

  /* 各種パラメータ */
  double x,y,w,h,confidence,X,Y,W,H;


  /************************************************************/
  /* 相手先アドレスの入力 */
  //printf("Connect to ? : (name or IP address) ");
  //scanf("%s", destination);

  /* sockaddr_in 構造体のセット */
  memset(&destSockAddr, 0, sizeof(destSockAddr));
  destSockAddr.sin_addr.s_addr = inet_addr("127.0.0.1");//inet_addr(destination);
  destSockAddr.sin_port = htons(port);
  destSockAddr.sin_family = AF_INET;

  /* ソケット生成 */
  destSocket = socket(AF_INET, SOCK_STREAM, 0);
 
  // サーバ接続
  connect( destSocket, (struct sockaddr *)&destSockAddr, sizeof( struct sockaddr_in ) );

  X = 180.7411;
  Y = 150.767;
  W = 20.6122;
  H = 30.9844;

  enum classname{car = 1,
	person = 2,
	other = 0};


  /* パケット送出 */
  while(1) {
	
	x = X+(double)rand()/RAND_MAX;
	y = Y+(double)rand()/RAND_MAX;
	w = W+(double)rand()/RAND_MAX;
	h = H+(double)rand()/RAND_MAX;
	confidence = (double)rand()/RAND_MAX;

	classname label = static_cast<classname>(rand() % 3);

 	detection detect = {label,confidence,{x,y,w,h}};

    	printf("sending...\n");
        if( send(destSocket, (char*)&detect, sizeof(detect), 0) < 0 ) {
            perror( "send" );
        };

    sleep(1);

  }


  /* ソケットの終了 */
  close(destSocket);
 
  return 0;
}



