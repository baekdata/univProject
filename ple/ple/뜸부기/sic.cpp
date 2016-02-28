#include "convert.hpp" // 헤더파일을 이용한다.

int main() // 메인함수 부분
{
	int LineNum = 10; // 초기 라인넘버는 10으로 지정한다.
	char buf[80], *buffer1, *buffer2, *buffer3, *buffer1M, *buffer2M, *buffer3M;
	FILE *readFile; // 읽어 온 파일 명을 저장 할 파일포인터를 지정한다.
	FILE *writeFixedFile; // Fixed Format File로 출력 시킬 파일포인터변수
	FILE *writeLinesFile; // Lines List File로 출력 시킬 파일포인터 변수
	char FileName[20]; // FreeFormat의 파일명이 저장된다.
    
	for(int i=0 ; i<1000; i++){ // oplist.txt에서optxt에저장
        fscanf(opcode2, "%s", opcode[i]);
    }

	printf("\nPlease enter the Filename here.\n: "); // 가장 먼저 출력하는 문구
	ReadFile:
	scanf("%s", &FileName[0]);// FreeFormat의 텍스트 파일명을 입력 받는다.

	SourceList *SourceListRefer = NULL; //초기화
	SourceList *SourceListPrint = NULL; //초기화
	CrossReferList *CrossReferList = NULL; //초기화

	readFile = fopen(FileName,"r+"); // FreeFormat으로 된 파일을 로드해서 readFile에 저장한다.
	  if(readFile == NULL){ // FileName의파일을찾을수없을경우
               fprintf(stderr, "%sThe file does not exist. Please enter check back later.\n : ", FileName);              
               goto ReadFile; // 파일name 오류 시 위의 ReadFile:로 돌아가서 다시 FreeFormat파일명을 입력 받는다.
      }

	writeFixedFile = fopen("Fixed Format Source.txt", "w+"); // Fixed된 파일로 로드하고 저장한다.
	writeLinesFile = fopen("Source List (+line#).txt","w+"); // Line번호가 들어간 파일Format으로 로드하고 저장한다.

	while(1) // 무한루프로 돌린다.
	{
		if(feof(readFile) != 0 )
			break;
		fgets(buf,256,readFile); //한줄을 얻어온다.
		buffer1 = strtok(buf, " \n\t"); //토큰을 분리한다.
		
		//일단 먼저 초기화시킨다.
		buffer1M = (char *)malloc(sizeof(strlen("  ")));
		buffer2M = (char *)malloc(sizeof(strlen("  ")));
		buffer3M = (char *)malloc(sizeof(strlen("  ")));
		strcpy(buffer1M, "  ");
		strcpy(buffer2M, "  ");
		strcpy(buffer3M, "  ");
	
		if(buffer1 != NULL){
			buffer2 = strtok(NULL, " \t\n"); //한번 더 토큰 분리한다.
			if(buffer2 != NULL){
				buffer3 = strtok(NULL, " \t\n"); //마지막 토큰 분리한다.
				if(buffer3 != NULL){
					fprintf(writeFixedFile,"%s\t\t%s\t\t%s\t\t\n", buffer1, buffer2, buffer3);

					buffer1M = (char *)malloc(sizeof(strlen(buffer1)));
					buffer2M = (char *)malloc(sizeof(strlen(buffer2)));
					buffer3M = (char *)malloc(sizeof(strlen(buffer3)));

					strcpy(buffer1M, buffer1);
					strcpy(buffer2M, buffer2);
					strcpy(buffer3M, buffer3);

					//상호참조 연결한다.
					insertNodeCrossReferList(&CrossReferList, NULL, cNodeCrossReferList(LineNum, buffer1M, NULL));
					
					}else{ // if의 조건이 아닐 경우
					fprintf(writeFixedFile,"\t\t%s\t\t%s\t\t\n", buffer1, buffer2);

					buffer2M = (char *)malloc(sizeof(strlen(buffer1)));
					buffer3M = (char *)malloc(sizeof(strlen(buffer2)));

					strcpy(buffer2M, buffer1);
					strcpy(buffer3M, buffer2);
				}
			}else if(buffer2 == NULL){ // buffer2내용이 NULL일 경우
				fprintf(writeFixedFile,"\t\t%s\t\t\t\t\n", buffer1);
				buffer2M = (char *)malloc(sizeof(strlen(buffer1)));
				strcpy(buffer2M, buffer1);			
			}

			//소스 리스트 연결한다.
			insertNodeSourceList(&SourceListRefer, NULL, cNodeSourceList(LineNum, buffer1M, buffer2M, buffer3M, NULL));
			insertNodeSourceList(&SourceListPrint, NULL, cNodeSourceList(LineNum, buffer1M, buffer2M, buffer3M, NULL));
		}
		LineNum += 10; //라인 넘버는 10씩 증가하기로 한다.
	}
	
	//역순 정렬 해야 한다.
	SourceListRefer = inverseSourceList(SourceListRefer);
	SourceListPrint = inverseSourceList(SourceListPrint);
	CrossReferList = inverseCrossReferList(CrossReferList);
	
	//Cross-reference List 초기화 시킨다.
	initCrossReferList(CrossReferList);

	//usedLine 검색 및 완성 부분
	findUsedLine(SourceListRefer,CrossReferList);
	/*
	//FixedFormat File의 출력 부분
	printf("\n*********************************\n");
	printf("*****Fixed FormatSource File*****\n");
	printf("*********************************\n");
	printFixedList(SourceListPrint,writeFixedFile);
	printf("\n\n");
	*/
	//라인번호가 들어간 소스 리스트 출력 부분
	printf("*********************************\n");
	printf("*****Line Format Source File*****\n");
	printf("*********************************\n");
	printSourceList(SourceListPrint,writeLinesFile);
	printf("\n\n");

	//상호 참조 리스트를 출력하는 부분
	printf("*********************************\n");
	printf("***Cross reference Source File***\n");
	printf("*********************************\n");
	printf("Symbol\tDefined\tLines\n");
	printCrossReferList(CrossReferList);	

	//잘못된 명령어 입력 즉, 선언되지 않은 레이블을 입력시 오류를 출력하는 부분
	printf("\n\n[Error : Undeclared lable lines]\n");
	printf("*********************************\n");
	printf("Lines\t\tLables\n");
	printf("*********************************\n");
	printOpCodeErrorList(checkErrorOpcodeList(SourceListRefer));
	printf("\n");
	return 0;
}

CrossReferList *cNodeCrossReferList(int num, char *lable, CrossReferList *link){
	CrossReferList *new_node;
	new_node = (CrossReferList *)malloc(sizeof(CrossReferList));
	new_node->num = num;
	new_node->lable = lable;
	new_node->link = link;
	return new_node;
}

OpCodeErrorList *cNodeOpCodeErrorList(int num, char *lable, OpCodeErrorList *link){
	OpCodeErrorList *new_node;
	new_node = (OpCodeErrorList *)malloc(sizeof(OpCodeErrorList));
	new_node->num = num;
	new_node->errorLable = lable;
	new_node->link = link;
	return new_node;
}

SourceList *cNodeSourceList(int num, char *lable, char *inst, char *value, SourceList *link){
	SourceList *new_node;
	new_node = (SourceList *)malloc(sizeof(SourceList));
	new_node->num = num;
	new_node->lable = lable;
	new_node->inst = inst;
	new_node->value = value;
	new_node->link = link;
	return new_node;
}

// 사용된 라인을 찾는 부분이다.
void findUsedLine(SourceList *headSourceList, CrossReferList *head){ 
	char *temp;
	int cnt;
	int k;
	char *null= "  ";
	
	CrossReferList *q = head;
	SourceList *p = headSourceList;
	
	while(q != NULL){
		cnt =0;
		while(p != NULL){
		if(strcmp(p->value,null) != 0){		
			temp = (char *)malloc(sizeof(char));
			temp = p->value;
			if(temp != NULL){
				k = strcmp(q->lable,p->value);
				if(k == 0){
					q->usedLine[cnt] = p->num;
					cnt++;
					p = p->link;
				}else
					p = p->link;
			}
			else 
				p = p->link;
		}else
			p = p->link;
		}
		p = headSourceList;
		q = q->link;
	}
} 

void insertNodeSourceList(SourceList **phead, SourceList *p, SourceList *new_node){
	if(*phead == NULL){
		new_node->link = NULL;
		*phead = new_node;
	}
	else if( p == NULL){
		new_node->link = *phead;
		*phead = new_node;
	}
	else{
		new_node->link = p->link;
		p->link = new_node;
	}
}

void insertNodeOpCodeErrorList(OpCodeErrorList **phead, OpCodeErrorList *p, OpCodeErrorList *new_node){
	if(*phead == NULL){
		new_node->link = NULL;
		*phead = new_node;
	}
	else if( p == NULL){
		new_node->link = *phead;
		*phead = new_node;
	}
	else{
		new_node->link = p->link;
		p->link = new_node;
	}
}

void insertNodeCrossReferList(CrossReferList **phead, CrossReferList *p, CrossReferList *new_node){
	if(*phead == NULL){
		new_node->link = NULL;
		*phead = new_node;
	}
	else if( p == NULL){
		new_node->link = *phead;
		*phead = new_node;
	}
	else{
		new_node->link = p->link;
		p->link = new_node;
	}
}

//미리 선언해 놓은 lable에 해당하지 않는 lable이 있을 경우 에러처리를 해서 에러메시지를 출력한다.
void printOpCodeErrorList(OpCodeErrorList *head){
	OpCodeErrorList *p = head;	
	if(p == NULL)
		printf("\tThere is no error.\n\n"); // 에러 메시지 출력한다.

	while( p != NULL){ // 에러가 발생한 라인번호와 에러 lable이 무엇인지 출력한다.
		printf("%d\t\t", p->num);
		printf("%s\n",  p->errorLable);
		p = p->link;
	}	
}

//Fixed Format Source File을 출력하는 부분이다.
void printFixedList(SourceList *head ,FILE *a){
	FILE *f = a;
	SourceList *p = head;
	while( p != NULL){ // lable과 inst, vlaue를 차례로 출력한다.
		printf("%s\t",p->lable);
		printf("%s\t",  p->inst);
		printf("%s\n",  p->value);
		p = p->link;
	}	
}

//Line번호가 들어간 Source를 출력하는 부분이다.
void printSourceList(SourceList *head ,FILE *a){
	FILE *f = a;
	SourceList *p = head;
	while( p != NULL){
		printf("%d\t",p->num);
		fprintf(f,"%d\t",p->num);
		printf("%s\t",p->lable);
		fprintf(f,"%s\t",p->lable);
		printf("%s\t",  p->inst);
		fprintf(f,"%s\t",p->inst);
		printf("%s\n",  p->value);
		fprintf(f,"%s\n",  p->value);
		p = p->link;
	}	
}

void initCrossReferList(CrossReferList *head){
	int i;
	CrossReferList *p = head;
	while( p != NULL){
		for(i=0;i<10; i++){
		p->usedLine[i] = 0;
		}
		p = p->link;
	}
}

//crossReference 부분을 출력하는 부분이다.
void printCrossReferList(CrossReferList *head){
	int f;
	CrossReferList *p = head;
	while( p != NULL){ // 어디에 어떤 lable이 사용되었는지 출력한다.		
		printf("%s\t", p->lable);
		printf("%d\t", p->num);
		for(f=0; f<10; f++){
			if(p->usedLine[f] != 0)
			printf("%d ", p->usedLine[f]);
		}
		printf("\n");
		p = p->link;
	}
}

SourceList *inverseSourceList(SourceList *head){
	SourceList *p,*q,*r;
	p = head;
	q = NULL;
	while(p != NULL){
		r = q;
		q = p;
		p = p->link;
		q->link = r;
	}
	return q;
}

CrossReferList *inverseCrossReferList(CrossReferList *head){
	CrossReferList *p,*q,*r;
	p = head;
	q = NULL;
	while(p != NULL){
		r = q;
		q = p;
		p = p->link;
		q->link = r;
	}
	return q;
}

OpCodeErrorList *checkErrorOpcodeList(SourceList *head){	
	SourceList *p = head;
	OpCodeErrorList *q= NULL;
	int i=0;
	int flag = 0;
	char *temp;
	char *temp2;
	while(p != NULL){
			temp = (char *)malloc(sizeof(strlen(p->inst)+1));
			temp = strtok(p->inst, "+");
			for(i=0; i<73; i++){
				temp2 = (char *)malloc(sizeof(strlen(opcode[i])+1));
				temp2= opcode[i];
				if(strcmp(temp,temp2) == 0){
					flag = 1;
				}
			}
		if(flag == 0)
			insertNodeOpCodeErrorList(&q, NULL, cNodeOpCodeErrorList(p->num,p->inst ,NULL));
			flag = 0;
			p = p->link;
		}
		return q;
}
