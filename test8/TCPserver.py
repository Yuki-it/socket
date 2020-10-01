import socket
import time
import struct
import time

def server():
	M_SIZE = 1024
	flag = 0
	# 
	host = '127.0.0.1'
	port = 9876

	locaddr = (host, port)

	# ①ソケットを作成する
	sock = socket.socket(socket.AF_INET, type=socket.SOCK_STREAM)

	print('create socket')

	# ②自ホストで使用するIPアドレスとポート番号を指定
	sock.bind(locaddr)
	# クライアントをいくつまでキューイングするか
	sock.listen(128)

	while True:
		# クライアントからの接続を待ち受ける (接続されるまでブロックする)
		clientsocket, (client_address, client_port) = sock.accept()

		while True:

			try:
		
				print('Waiting message')
				message  = clientsocket.recv(M_SIZE)
				tmp = struct.unpack('iiddddd',message)	
				print(tmp)
			except OSError:
				break

			# 受信したデータの長さが 0 ならクライアントからの切断を表す
			if len(message) == 0:
				break
			
			# 受信したデータをそのまま送り返す (エコー)
			sent_message = message
			while True:
				# 送信できたバイト数が返ってくる
				sent_len = clientsocket.send(sent_message)
				# 全て送れたら完了
				if sent_len == len(sent_message):
					break
				# 送れなかった分をもう一度送る
				sent_message = sent_message[sent_len:]
			#print('Send: {}'.format(message))

		# 後始末
		clientsocket.close()
		print('Disconnected: {0}:{1}'.format(client_address, client_port))


if __name__ == '__main__':
    server()

