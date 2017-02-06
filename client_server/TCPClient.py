#!/usr/bin/python

# This is TCPClient.py

from socket import *
serverName = 'AUS213L10'
serverPort = 6789
clientSocket = socket(AF_INET, SOCK_STREAM)
clientSocket.connect((serverName, serverPort))

sentence = raw_input('Input lowercase sentence: ')

clientSocket.send(sentence)
modifiedSentence = clientSocket.recv(1024)
print 'From Server:', modifiedSentence
clientSocket.close()


