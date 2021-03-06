﻿/*****************************************
> File Name : client_test.cpp
> Description : C ECHO client example using sockets
	g++ -g client_test.cpp -o Client -levent
> Author : linden
> Date : 2015-08-07
*******************************************/

#include <unistd.h>
#include <stdio.h>		//printf
#include <string.h>		//strlen
#include <sys/socket.h>	//socket
#include <arpa/inet.h>	//inet_addr
#include <iostream>
//#include <json/json.h>

#define PORT		8090
#define IPADDRESS	"127.0.0.1"

using namespace std;

int main(int argc, char *argv[])
{
	int sockfd;
	struct sockaddr_in server;
	string message = "test buf";
	//char message[1024] = { 0 };
	char server_reply[2048] = { 0 };

	//Create socket
	sockfd = socket(AF_INET, SOCK_STREAM, 0);
	if (sockfd == -1)
	{
		printf("Could not create socket");
	}
	puts("Socket created");

	server.sin_addr.s_addr = inet_addr(IPADDRESS);
	server.sin_family = AF_INET;
	server.sin_port = htons(PORT);

	//Connect to remote server
	if (connect(sockfd, (struct sockaddr *)&server, sizeof(server)) < 0)
	{
		perror("connect failed. Error");
		return 1;
	}

	puts("Connected\n");

	//keep communicating with server
//	while (1)
//	{
		//sprintf(message, "POST / HTTP/1.1\r\nHost: www.qujiatuan.com\r\nContent-Type: application/x-www-form-urlencoded\r\nContent-Length: 12\r\nConnection:close\r\n\r\nsn=123&n=asa");
	//sprintf(message, "sn=123&n=asa");Json::Value root;

	//	Json::Value root;
	
	//	root["FunctionName"] = "login";
		//root["CountryCode"] = 86;
	//	root["User_login"] = "13814381438";
	//	root["User_pass"] = "123456";
	
		// 转换为字符串（带格式）
		//root.toStyledString();
		//std::string out = root.toStyledString();
		// 输出无格式json字符串
	//	Json::FastWriter writer;
	//	std::string out = writer.write(root);
	//	std::cout << out << std::endl;
		//memcpy(message, "\x54\x89\x0\x1\x0\x4\x1\x2\x3\x4\x0\xCD\xEA",13);
	//	message = out;
		printf("Send message : %s\n",message.c_str());

		//Send some data
		if (send(sockfd, message.c_str(), message.size()/*strlen(message)13*/, 0) < 0)
		{
			puts("Send failed");
			return -1;
		}
		while (1)
		{
			//Receive a reply from the server
			int n = recv(sockfd, server_reply, 1024 * 1024, 0);
			if (n < 0)
			{
				puts("recv failed");
				break;
			}

			puts("Server reply :");
			printf("n = %d\n", n);
			puts(server_reply);
		}

//	}

	close(sockfd);
	return 0;
}
/*
GET / path HTTP / 1.1
Header1: Value1
Header2 : Value2
Header3 : Value3

POST /path HTTP/1.1
Header1: Value1
Header2: Value2
Header3: Value3

body data goes here...

HTTP响应的格式：
200 OK
Header1: Value1
Header2: Value2
Header3: Value3

body data goes here...

*/
