#!/usr/bin/python

# This is TCPServer.py


from socket import *
serverPort = 6789
serverSocket = socket(AF_INET, SOCK_STREAM)
serverSocket.bind(('', serverPort))
serverSocket.listen(1)
print 'The Server is ready to receive'

try:
   while 1:
      connectionSocket, addr = serverSocket.accept()
      sentence = connectionSocket.recv(1024)
      capitalizedSentence = sentence.upper()
      connectionSocket.send(capitalizedSentence)
      connectionSocket.close()

except KeyboardInterrupt:
   print "\nClosing Server"
   serverSocket.close()

