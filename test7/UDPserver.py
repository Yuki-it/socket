import socket
import time
import struct
import time
import sys

def server():
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

	tmp_number=-1
	while True:

		print('Waiting message')
		message, cli_addr = sock.recvfrom(M_SIZE)
		tmp = struct.unpack('iiddddd',message)	
		

		if tmp[0] < tmp_number:
		    print('Error: configuration failed', file=sys.stderr)
		    print(tmp[0])
		    sys.exit(1)

		print(tmp)
		tmp_number = tmp[0]		

		#time.sleep(0.1)

	s.close()

if __name__ == "__main__":
	server()
