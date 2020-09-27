import socket
import time

M_SIZE = 1024

# 
host = '127.0.0.1'
port = 9876

locaddr = (host, port)

# ①ソケットを作成する
sock = socket.socket(socket.AF_INET, type=socket.SOCK_DGRAM)
print('create socket')

# ②自ホストで使用するIPアドレスとポート番号を指定
sock.bind(locaddr)

while True:
    try :
        # ③Clientからのmessageの受付開始
        print('Waiting message')
        message, cli_addr = sock.recvfrom(M_SIZE)
        message = message.decode(encoding='utf-8',errors='ignore')
        print(f'Received message is [{message}]')	#print("data: {}, addr: {}".format(message, cli_addr))
		

		
		# Clientが受信待ちになるまで待つため
        time.sleep(1)

        # ④Clientへ受信完了messageを送信
        #print('Send response to Client')
        #sock.sendto('Success to receive message'.encode(encoding='utf-8'), cli_addr)

    except KeyboardInterrupt:
        print ('\n . . .\n')
        sock.close()
        break
