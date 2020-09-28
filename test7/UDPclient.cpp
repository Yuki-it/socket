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
    int number;
    int classtype;
    double confidence;
    double box[4];
};
int i=0;

int main() {
  /* IPアドレス、ポート番号、ソケット */
  char destination[80];
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
  destSocket = socket(AF_INET, SOCK_DGRAM, 0);

/* 
   パケット送出 
  for(i=0; i<10; i++) {
    printf("sending...\n");
    sendto(destSocket, toSendText, strlen(toSendText)+1, 0, (const sockaddr*)&destSockAddr, sizeof(destSockAddr));
    sleep(1);
  }
*/

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

 	detection detect = {i,label,confidence,{x,y,w,h}};

    	printf("sending...\n");
    	sendto(destSocket, (char*)&detect, sizeof(detect), 0, (const sockaddr*)&destSockAddr, sizeof(destSockAddr));

	i++;	

    sleep(0.1);

  }


  /* ソケットの終了 */
  close(destSocket);
}



