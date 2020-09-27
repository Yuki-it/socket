#include <stdio.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <unistd.h>
 
int main() {
    int sockfd;
    int client_sockfd;
    struct sockaddr_in addr;
 
    socklen_t len = sizeof( struct sockaddr_in );
    struct sockaddr_in from_addr;
 
    char buf1[1024];
    char buf2[1024]; 
    // 受信バッファ初期化
    memset( buf1, 0, sizeof( buf1 ) );
    memset( buf2, 0, sizeof( buf2 ) );
 
    // ソケット生成
    if( ( sockfd = socket( AF_INET, SOCK_STREAM, 0 ) ) < 0 ) {
        perror( "socket" );
    }
 
    // 待ち受け用IP・ポート番号設定
    addr.sin_family = AF_INET;
    addr.sin_port = htons( 1234 );
    addr.sin_addr.s_addr = INADDR_ANY;
 
    // バインド
    if( bind( sockfd, (struct sockaddr *)&addr, sizeof( addr ) ) < 0 ) {
        perror( "bind" );
    }
 
    // 受信待ち
    if( listen( sockfd, SOMAXCONN ) < 0 ) {
        perror( "listen" );
    }
 
    // クライアントからのコネクト要求待ち
    if( ( client_sockfd = accept( sockfd, (struct sockaddr *)&from_addr, &len ) ) < 0 ) {
        perror( "accept" );
    }

    // 受信
    int rsize1,rsize2;
    while( 1 ) {
        rsize1 = recv( client_sockfd, buf1, sizeof( buf1 ), 0 );


        if ( rsize1 == 0 ) {
            break;
        } else if ( rsize1 == -1 ) {
            perror( "recv" );
        } else {
            printf( "receive:%s\n", buf1 );

            //sleep( 1 );
 
            // 応答
            //printf( "send:%s\n", buf );
            //write( client_sockfd, buf, rsize );
        }
	*/


    }
 
    // ソケットクローズ
    close( client_sockfd );
    close( sockfd );
 
    return 0;
}
