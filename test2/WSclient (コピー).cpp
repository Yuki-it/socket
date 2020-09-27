#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <cstring>
#include <cstdio>
#include <cstdlib>
#include <sstream>
#include <iostream>
#include <unistd.h>

using namespace std;


int main(){

int sockmode=1;
int forwardflag = 1;
int stopflag =1;

if(sockmode==1){
struct sockaddr_in server;

int sock;
char buf[64];

int n;

 
sock = socket(AF_INET, SOCK_STREAM, 0);

server.sin_family = AF_INET;
server.sin_port = htons(12345);
server.sin_addr.s_addr = inet_addr("127.0.0.1");


connect(sock, (struct sockaddr *)&server, sizeof(server));

while(1){ 
    memset(buf, 0, sizeof(buf));
    stringstream sts;
    string str="0,0,end";

	if(forwardflag ==1){
		str="100,100,end";
	}

    if(stopflag==1){
		str="0,0,end";
	}

    cout << "send:" <<str <<endl;

    char sdata[64];
    sts <<  str;
    sts >> sdata;

    const char* sdataconst= sdata;

    write(sock, sdataconst, strlen(sdataconst));

    cout<<"senddata"<<sdataconst <<endl;

    int n = read(sock, buf, sizeof(buf));

    cout <<"resdata" <<buf << endl;

    sleep(1);

    sts.clear();
}

 close(sock);
}

return 0;
}
