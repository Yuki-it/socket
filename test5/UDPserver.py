import socket
import time

M_SIZE = 1024
flag = 0
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
    try:
    	print('Waiting message')
    	message, cli_addr = sock.recvfrom(M_SIZE)
    	if(flag == 0):
    		message = message.decode(encoding='utf-8',errors='ignore')
    		print(type(message))
    		print("flag0",message)
    		flag += 1
    		
    	elif(flag == 1):
    		message = message.decode(encoding='utf-8',errors='ignore')
    		message = message.replace('\x00', '')
    		int_num = int(message)
    		print(type(int_num))
    		print("flag1",int_num)
    		flag += 1
    		
    	elif(flag == 2):
    		message = message.decode(encoding='utf-8',errors='ignore')
    		message = message.replace('\x00', '')
    		confidence = float(message)
    		print(type(confidence))
    		print("flag2",confidence)
    		flag = 0
    		
    	# Clientが受信待ちになるまで待つため
    	time.sleep(1)


    except KeyboardInterrupt:
        print ('\n . . .\n')
        sock.close()
        break
