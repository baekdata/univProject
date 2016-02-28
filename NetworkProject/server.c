#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <pthread.h>

#define BUF_SIZE 128
#define MAX_CLNT 4 // It's possible up to 4 people
#define NAME_SIZE 20

void * handle_clnt(void * arg);
void error_handling(char * msg);
int clnt_cnt=0;
int clnt_socks[MAX_CLNT];
char clnt_name[NAME_SIZE]= {0};
char clnt_names[MAX_CLNT][NAME_SIZE]= {0,0};
pthread_mutex_t mutx;

int main(int argc, char *argv[]){
	int serv_sock, clnt_sock, i;
	struct sockaddr_in serv_adr, clnt_adr;
	int clnt_adr_sz;
	pthread_t t_id;
	if(argc!=2) {
		printf("Usage : %s <port>\n", argv[0]);
		exit(1);
	}
  
	pthread_mutex_init(&mutx, NULL);
	serv_sock=socket(PF_INET, SOCK_STREAM, 0);
	memset(&serv_adr, 0, sizeof(serv_adr));
	serv_adr.sin_family=AF_INET; 
	serv_adr.sin_addr.s_addr=htonl(INADDR_ANY);
	serv_adr.sin_port=htons(atoi(argv[1]));
	
	if(bind(serv_sock, (struct sockaddr*) &serv_adr, sizeof(serv_adr))==-1)
		error_handling("bind() error");
	if(listen(serv_sock, 5)==-1)
		error_handling("listen() error");
	
	while(1){
		clnt_adr_sz=sizeof(clnt_adr);
		clnt_sock=accept(serv_sock, (struct sockaddr*)&clnt_adr,&clnt_adr_sz);
	
		if(clnt_cnt >= MAX_CLNT){
			printf("CONNECT FAIL : %d \n", clnt_sock);
			write(clnt_sock, "too many users. sorry", BUF_SIZE);
			continue;
		}
		pthread_mutex_lock(&mutx);

		clnt_socks[clnt_cnt]=clnt_sock;
		read(clnt_sock, clnt_name, NAME_SIZE);		
		strcpy(clnt_names[clnt_cnt++], clnt_name); 
		// input the user name that from the client
		pthread_mutex_unlock(&mutx);
		pthread_create(&t_id, NULL, handle_clnt, (void*)&clnt_sock);
		pthread_detach(t_id);
		printf("--------------------------------------------------\n");
		printf("Connected client IP: %s\n", inet_ntoa(clnt_adr.sin_addr));
		printf("Connected client Name : %s\n", clnt_name);
		printf("--------------------------------------------------\n");
	}
	close(serv_sock);
	return 0;
}
	
void * handle_clnt(void * arg)
{
	int clnt_sock=*((int*)arg);
	int str_len=0, i;
	int fSize = 0;
	const char sig_file[BUF_SIZE] = {"file : cl->sr"};
	const char Fmsg_end[BUF_SIZE] = {"FileEnd_cl->sr"};
	char msg[BUF_SIZE] = {0};
	char file_msg[BUF_SIZE] = {0};

	while((str_len=read(clnt_sock, msg, BUF_SIZE))!=0) 
	{
		if(!strcmp(msg, sig_file))
		{
			int j;
			int noCli = 0;
			int fileGo = NULL;
			char tmpName[NAME_SIZE]= {0};
			read(clnt_sock, tmpName, NAME_SIZE);
			pthread_mutex_lock(&mutx);
						
			for(j=0; j<clnt_cnt; j++){
				if(!strcmp(tmpName, clnt_names[j]) ){
					noCli = 0;
					fileGo = j; // save the socket number
					break;
				}else if(j == clnt_cnt - 1){
					noCli = 1; 
					break;
				}
			}
			if(noCli == 1) {
				write(clnt_sock, "[NoClient_sorry]", BUF_SIZE);
				pthread_mutex_unlock(&mutx);
				continue;
			}else if(noCli == 0) {
				write(clnt_sock, "[continue_ok_nowgo]", BUF_SIZE);
			} // Find whether the user exists
			write(clnt_socks[fileGo], "file : sr->cl", BUF_SIZE); 
			read(clnt_sock, &fSize, sizeof(int));
			printf("File size %d Byte\n", fSize);
			write(clnt_socks[fileGo], &fSize, sizeof(int));
			// transfer to the file size information

			while(1) {
				read(clnt_sock, file_msg, BUF_SIZE);
				if(!strcmp(file_msg, Fmsg_end))
					break;
				write(clnt_socks[fileGo], file_msg, BUF_SIZE);
			}
			write(clnt_socks[fileGo], "FileEnd_sr->cl", BUF_SIZE);
			pthread_mutex_unlock(&mutx);
			printf("(!Notice)File data transfered \n"); // file transfer
		}else{ 
			printf("%s",msg); // message transfer
		}	
	}
	
	pthread_mutex_lock(&mutx);
	for(i=0; i<clnt_cnt; i++){   // remove disconnected client
		if(clnt_sock==clnt_socks[i]){
			while(i++<clnt_cnt-1) {
				clnt_socks[i]=clnt_socks[i+1];
				strcpy(clnt_names[i], clnt_names[i+1]);
			}
			break;
		}
	}
	clnt_cnt--;
	pthread_mutex_unlock(&mutx);
	close(clnt_sock);
	return NULL;
}

void error_handling(char * msg){
	fputs(msg, stderr);
	fputc('\n', stderr);
	exit(1);
}