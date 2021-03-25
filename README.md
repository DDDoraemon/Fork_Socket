# Fork_Socket
Linux multiprocess servert&amp;client

If you download this file
you should modify some things
include:
  C/server.c:   20 & 21 line
    //inet_pton(AF_INET, IP, (struct sockaddr*)&server_addr.sin_addr);    //if you choose this one, you should modify C/server.h 11 line, at ther use yourself IP
    server_addr.sin_addr.s_addr = htonl(INADDR_ANY);  //if you choose this one, your client will not know your ip address, but you'r client can use 127.0.0.1 as server's ip address
