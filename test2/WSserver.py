import sys
import socket 
import threading

def server(host, port):
	s = socket.socket()
	s.bind((host, port))
	s.listen(1)
	print("waiting")
	conn, addr = s.accept()

	while True:
		data = conn.recv(1024)
		print("server: receive '%s'" % data)
		datalist=str(data)
		datasp=datalist.split(",")
		print(datasp)
		#object.set_value(float(datasp[0]))
		conn.send("sendfrompython")
	conn.close()
	s.close()


class Server(threading.Thread):
	def run(self):
		HOST,PORT ="localhost",12345
		server(HOST,PORT)

if __name__ == "__main__":
	s =Server()
	s.start()

