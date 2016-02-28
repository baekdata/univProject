#include <stdio.h>
#include <stdlib.h>
#include <unistd.h> 
#include <string.h>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <pthread.h>
#define BUF_SIZE 128
#define NAME_SIZE 20
#define NOTSET 0
#define EXIST 1
#define NOTEXIST 2

void * send_msg(void * arg);
void * recv_msg(void * arg);
void error_handling(char * msg);
	
char name[NAME_SIZE]= {0};
char msg[BUF_SIZE] = {0};
int cli_exist = NOTSET;
int setFName = 0;
int wOk = 1;
	
int main(int argc, char *argv[])
{
	int sock;
	struct sockaddr_in serv_addr;
	pthread_t snd_thread, rcv_thread;
	void * thread_return;
	if(argc!=4) {
		printf("Usage : %s <IP> <port> <name>\n", argv[0]);
		exit(1);
	 }

	sprintf(name, "%s", argv[3]);
	sock=socket(PF_INET, SOCK_STREAM, 0);
	
	memset(&serv_addr, 0, sizeof(serv_addr));
	serv_addr.sin_family=AF_INET;
	serv_addr.sin_addr.s_addr=inet_addr(argv[1]);
	serv_addr.sin_port=htons(atoi(argv[2]));
	  
	if(connect(sock, (struct sockaddr*)&serv_addr, sizeof(serv_addr))==-1)
		error_handling("connect() error");

	write(sock, name, NAME_SIZE);
	// transfer name to server

	printf("\n\n");
	printf("Chatting Program CONNECTING..... \n [TIP] If you want \"MENU\" -> /menu \n\n");
	printf("Chatting Program Connecting Completion !\n Start Chatting Now !!\n");
	printf("--------------------------------------------------\n");

	pthread_create(&snd_thread, NULL, send_msg, (void*)&sock);
	pthread_create(&rcv_thread, NULL, recv_msg, (void*)&sock);
	pthread_join(snd_thread, &thread_return);
	pthread_join(rcv_thread, &thread_return);
	close(sock);  
	return 0;
}
	
void * send_msg(void * arg)   // send thread main
{
	int sock=*((int*)arg);
	int Flength = 0;
	int i=0;
	int fSize = 0;
	int fEnd = 0;
	char name_msg[NAME_SIZE+BUF_SIZE] = {0};
	char t_msg[BUF_SIZE] = {0};
	char last_msg[BUF_SIZE] = {0};
	char t_name_msg[BUF_SIZE] = {0};
	char noUse[BUF_SIZE] = {0};
	const char enter[BUF_SIZE] = {"\n"};
	const char whisper[BUF_SIZE] = {"/whisper\n"};

	while(1) 
	{
		if(wOk == 0) {
			sleep(1);
		} fgets(msg, BUF_SIZE, stdin);

		if(!strcmp(msg,"/exit\n")){
			close(sock);
			exit(0);
		}else if(!strcmp(msg, "/sendfile\n")){
			char location[BUF_SIZE];
			char who[NAME_SIZE];
			FILE *fp;
			FILE *size;

			printf("(!Record)File location : ");
			scanf("%s", location);
			size = fopen(location, "rb");
			if(size == NULL) {
				printf("(!Notice)No file like that \n");
				continue;
			}
			// confirmation(valid file to send)
			
			printf("(!Record)To who(ID)? : ");
			scanf("%s", who);
			write(sock, "file : cl->sr", BUF_SIZE);
			// At first, the signal that sends the file transfer to server
			write(sock, who, NAME_SIZE);
			// Send the user ID you want to send

			while(cli_exist == NOTSET) {
				sleep(1);
			}

			if(cli_exist == NOTEXIST) {
				printf("(!Notice)No user like that \n");
				cli_exist = NOTSET;
				continue;
			} 
			// if client not exists, firstly exit

			while(1) {	
				fEnd = fread(noUse, 1 , BUF_SIZE, size);
				fSize += fEnd;
				if(fEnd != BUF_SIZE)
					break;
			}
			fclose(size);

			printf("(!Notice)File transfer start \n(File Size : %d Byte)\n", fSize); 
			write(sock, &fSize, sizeof(int)); // At first, send the file size information
			fSize = 0;
			fp = fopen(location, "rb");
			
			while(1) {
				Flength = fread(t_msg, 1 , BUF_SIZE, fp);
				if(Flength != BUF_SIZE) {
					for(i=0; i<Flength; i++) {
						last_msg[i] = t_msg[i];
					} // fread prevention
					write(sock, last_msg, BUF_SIZE);
					write(sock, "FileEnd_cl->sr", BUF_SIZE);
					break;
				}
				write(sock, t_msg, BUF_SIZE); 
			}
			// transfer the file contents to the server	
			fclose(fp);
			printf("(!Notice)File transfer finish \n");
			cli_exist = NOTSET;
		
		}else if(!strcmp(msg, "/menu\n")) {	
			printf("\n");
			printf("[MENU]\n\n");
			printf("1. /menu -> some orders \n");
			//printf("2. /whisper -> whispering to someone\n");
			printf("2. /sendfile -> 1:1 file transfer \n");
			//printf("4. /sendfile all -> 1:N file transfer \n");
			printf("3. /exit -> chatting program exit \n");
			printf("\n[END MENU] \n\n");

		}else if(setFName == 1) {  // if show the menu
			if(strcmp(msg, enter)) 
				setFName = 0;
		}else{
			strcpy(t_msg, "\n");
			sprintf(t_name_msg,"[%s] %s", name, t_msg);
			sprintf(name_msg,"[%s] %s", name, msg);

			if(strcmp(name_msg, t_name_msg) != 0) 
				write(sock, name_msg, BUF_SIZE);
			// If you did not receive any input, not output
			// transfer message
		}
	}
	return NULL;
}
	
void * recv_msg(void * arg)   // read thread main
{
	int sock=*((int*)arg);
	char name_msg[BUF_SIZE] = {0};
	char file_msg[BUF_SIZE] = {0};
	const char signal[BUF_SIZE] = {"file : sr->cl"};
	const char end_msg[BUF_SIZE] = {"FileEnd_sr->cl"};
	const char nocl_msg[BUF_SIZE] = {"[NoClient_sorry]"};
	const char yescl_msg[BUF_SIZE] = {"[continue_ok_nowgo]"};
	const char noConnect[BUF_SIZE] = {"too many users. sorry"};
	int str_len = 0;
	int fSize = 0;

	while(1){
		str_len=read(sock, name_msg, BUF_SIZE);
		if(!strcmp(name_msg, signal)) {
			setFName = 1;
			wOk = 0;

			printf("(!Notice)receive request. ");
			read(sock, &fSize, sizeof(int));
			printf("(File size : %d Byte)\n [press Enter key to continue]", fSize);
			// Outputting after the received file size
			printf("(!Notice)set file name : ");
			
			wOk = 1;
			while(setFName == 1) {
				sleep(1);
			}
			msg[strlen(msg)-1] = '\0';
			FILE *fp;
			fp = fopen(msg, "wb"); 
		
			while(1)
			{		
				read(sock, file_msg, BUF_SIZE);
				
				if(!strcmp(file_msg, end_msg)) 
					break;
				fwrite(file_msg, 1, BUF_SIZE, fp);
			}

			fclose(fp);
			printf("(!Notice)File receive finished \n");
			// reactivates the send_msg thread
		}else if(strcmp(name_msg, yescl_msg) == 0) {
			cli_exist = EXIST;
		}else if(strcmp(name_msg, nocl_msg) == 0) {
			cli_exist = NOTEXIST; 
		}else if(!strcmp(name_msg, noConnect)) {
			printf("too many users. sorry \n");
			exit(0);
		}else {
			fputs(name_msg, stdout);
		}
	}
	return NULL;
}
	
void error_handling(char *msg){
	fputs(msg, stderr);
	fputc('\n', stderr);
	exit(1);
}