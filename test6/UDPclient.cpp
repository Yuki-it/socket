#include <stdio.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <netdb.h>
#include <unistd.h>
#include <string.h>
#include <unistd.h>

int main() {
  /* IPアドレス、ポート番号、ソケット */
  char destination[80];
  unsigned short port = 9876;
  int destSocket;

  /* sockaddr_in 構造体 */
  struct sockaddr_in destSockAddr;

  /* 各種パラメータ */
  double x,y,w,h,confidence;
  char classname[] = "car";
  char toSendText[32],toSendText2[32],toSendText3[32],toSendText4[32],toSendText5[32],toSendText6[32];
  //char *toSendText = "This is a test";

  /************************************************************/
  /* 相手先アドレスの入力 */
  printf("Connect to ? : (name or IP address) ");
  scanf("%s", destination);

  /* sockaddr_in 構造体のセット */
  memset(&destSockAddr, 0, sizeof(destSockAddr));
  destSockAddr.sin_addr.s_addr = inet_addr(destination);
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

  x = 180.7411;
  y = 150.767;
  w = 20.6122;
  h = 30.9844;
  confidence =0.81;

  /* パケット送出 */
  while(1) {

    sprintf( toSendText, "%s", classname );
    printf("sending1...\n");
    sendto(destSocket, toSendText, strlen(toSendText)+1, 0, (const sockaddr*)&destSockAddr, sizeof(destSockAddr));

    sprintf( toSendText2, "%f", confidence );
    printf("sending2...\n");
    sendto(destSocket, toSendText2, strlen(toSendText2)+1, 0, (const sockaddr*)&destSockAddr, sizeof(destSockAddr));


    sprintf( toSendText3, "%f", x );
    printf("sending3...\n");
    sendto(destSocket, toSendText3, strlen(toSendText3)+1, 0, (const sockaddr*)&destSockAddr, sizeof(destSockAddr));

    sprintf( toSendText4, "%f", y );
    printf("sending4...\n");
    sendto(destSocket, toSendText4, strlen(toSendText4)+1, 0, (const sockaddr*)&destSockAddr, sizeof(destSockAddr));

    sprintf( toSendText5, "%f", w );
    printf("sending5...\n");
    sendto(destSocket, toSendText5, strlen(toSendText5)+1, 0, (const sockaddr*)&destSockAddr, sizeof(destSockAddr));

    sprintf( toSendText6, "%f", h );
    printf("sending6...\n");
    sendto(destSocket, toSendText6, strlen(toSendText6)+1, 0, (const sockaddr*)&destSockAddr, sizeof(destSockAddr));

    sleep(1);

  }


  /* ソケットの終了 */
  close(destSocket);
}
