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

	for i in range(6):
		print('Waiting message')
		message, cli_addr = sock.recvfrom(M_SIZE)
		
		if(flag == 0):
			classname = message.decode(encoding='utf-8',errors='ignore')
			print(type(classname))
			print("flag0",classname)
			flag += 1

		elif(flag == 1):
			confidence = message.decode(encoding='utf-8',errors='ignore')
			confidence = confidence.replace('\x00', '')
			confidence = float(confidence)
			print(type(confidence))
			print("flag1",confidence)
			flag += 1
	    	
		elif(flag == 2):
			x = message.decode(encoding='utf-8',errors='ignore')
			x = x.replace('\x00', '')
			x = float(x)
			print(type(x))
			print("flag2",x)
			flag += 1
		
		elif(flag == 3):
			y = message.decode(encoding='utf-8',errors='ignore')
			y = y.replace('\x00', '')
			y = float(y)
			print(type(y))
			print("flag3",y)
			flag += 1
		
		elif(flag == 4):
			w = message.decode(encoding='utf-8',errors='ignore')
			w = w.replace('\x00', '')
			w = float(w)
			print(type(w))
			print("flag4",w)
			flag += 1

		elif(flag == 5):
			h = message.decode(encoding='utf-8',errors='ignore')
			h = h.replace('\x00', '')
			h = float(h)
			print(type(h))
			print("flag5",h)
			flag = 0;
		
		time.sleep(1)

	detect = (classname.encode(encoding='utf-8'),confidence,(x,y,w,h))
	print(detect)

