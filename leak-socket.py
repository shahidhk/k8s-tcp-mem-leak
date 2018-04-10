#!/usr/bin/python

import socket
import time
import os

BLOCK_SIZE=320000
count = 0
holdSockets = []

while True:
   count += 1
   nextSock = socket.socket( socket.AF_INET, socket.SOCK_STREAM )
   nextSock.connect(("0.0.0.0", 8888))
   nextSock.send(repr(os.urandom(BLOCK_SIZE)))
   holdSockets.append(nextSock)
   time.sleep(0.1)
   print "Created %i sockets" % count
