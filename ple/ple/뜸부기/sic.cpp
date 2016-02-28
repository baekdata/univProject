#include "convert.hpp" // ��������� �̿��Ѵ�.

int main() // �����Լ� �κ�
{
	int LineNum = 10; // �ʱ� ���γѹ��� 10���� �����Ѵ�.
	char buf[80], *buffer1, *buffer2, *buffer3, *buffer1M, *buffer2M, *buffer3M;
	FILE *readFile; // �о� �� ���� ���� ���� �� ���������͸� �����Ѵ�.
	FILE *writeFixedFile; // Fixed Format File�� ��� ��ų ���������ͺ���
	FILE *writeLinesFile; // Lines List File�� ��� ��ų ���������� ����
	char FileName[20]; // FreeFormat�� ���ϸ��� ����ȴ�.
    
	for(int i=0 ; i<1000; i++){ // oplist.txt����optxt������
        fscanf(opcode2, "%s", opcode[i]);
    }

	printf("\nPlease enter the Filename here.\n: "); // ���� ���� ����ϴ� ����
	ReadFile:
	scanf("%s", &FileName[0]);// FreeFormat�� �ؽ�Ʈ ���ϸ��� �Է� �޴´�.

	SourceList *SourceListRefer = NULL; //�ʱ�ȭ
	SourceList *SourceListPrint = NULL; //�ʱ�ȭ
	CrossReferList *CrossReferList = NULL; //�ʱ�ȭ

	readFile = fopen(FileName,"r+"); // FreeFormat���� �� ������ �ε��ؼ� readFile�� �����Ѵ�.
	  if(readFile == NULL){ // FileName��������ã�����������
               fprintf(stderr, "%sThe file does not exist. Please enter check back later.\n : ", FileName);              
               goto ReadFile; // ����name ���� �� ���� ReadFile:�� ���ư��� �ٽ� FreeFormat���ϸ��� �Է� �޴´�.
      }

	writeFixedFile = fopen("Fixed Format Source.txt", "w+"); // Fixed�� ���Ϸ� �ε��ϰ� �����Ѵ�.
	writeLinesFile = fopen("Source List (+line#).txt","w+"); // Line��ȣ�� �� ����Format���� �ε��ϰ� �����Ѵ�.

	while(1) // ���ѷ����� ������.
	{
		if(feof(readFile) != 0 )
			break;
		fgets(buf,256,readFile); //������ ���´�.
		buffer1 = strtok(buf, " \n\t"); //��ū�� �и��Ѵ�.
		
		//�ϴ� ���� �ʱ�ȭ��Ų��.
		buffer1M = (char *)malloc(sizeof(strlen("  ")));
		buffer2M = (char *)malloc(sizeof(strlen("  ")));
		buffer3M = (char *)malloc(sizeof(strlen("  ")));
		strcpy(buffer1M, "  ");
		strcpy(buffer2M, "  ");
		strcpy(buffer3M, "  ");
	
		if(buffer1 != NULL){
			buffer2 = strtok(NULL, " \t\n"); //�ѹ� �� ��ū �и��Ѵ�.
			if(buffer2 != NULL){
				buffer3 = strtok(NULL, " \t\n"); //������ ��ū �и��Ѵ�.
				if(buffer3 != NULL){
					fprintf(writeFixedFile,"%s\t\t%s\t\t%s\t\t\n", buffer1, buffer2, buffer3);

					buffer1M = (char *)malloc(sizeof(strlen(buffer1)));
					buffer2M = (char *)malloc(sizeof(strlen(buffer2)));
					buffer3M = (char *)malloc(sizeof(strlen(buffer3)));

					strcpy(buffer1M, buffer1);
					strcpy(buffer2M, buffer2);
					strcpy(buffer3M, buffer3);

					//��ȣ���� �����Ѵ�.
					insertNodeCrossReferList(&CrossReferList, NULL, cNodeCrossReferList(LineNum, buffer1M, NULL));
					
					}else{ // if�� ������ �ƴ� ���
					fprintf(writeFixedFile,"\t\t%s\t\t%s\t\t\n", buffer1, buffer2);

					buffer2M = (char *)malloc(sizeof(strlen(buffer1)));
					buffer3M = (char *)malloc(sizeof(strlen(buffer2)));

					strcpy(buffer2M, buffer1);
					strcpy(buffer3M, buffer2);
				}
			}else if(buffer2 == NULL){ // buffer2������ NULL�� ���
				fprintf(writeFixedFile,"\t\t%s\t\t\t\t\n", buffer1);
				buffer2M = (char *)malloc(sizeof(strlen(buffer1)));
				strcpy(buffer2M, buffer1);			
			}

			//�ҽ� ����Ʈ �����Ѵ�.
			insertNodeSourceList(&SourceListRefer, NULL, cNodeSourceList(LineNum, buffer1M, buffer2M, buffer3M, NULL));
			insertNodeSourceList(&SourceListPrint, NULL, cNodeSourceList(LineNum, buffer1M, buffer2M, buffer3M, NULL));
		}
		LineNum += 10; //���� �ѹ��� 10�� �����ϱ�� �Ѵ�.
	}
	
	//���� ���� �ؾ� �Ѵ�.
	SourceListRefer = inverseSourceList(SourceListRefer);
	SourceListPrint = inverseSourceList(SourceListPrint);
	CrossReferList = inverseCrossReferList(CrossReferList);
	
	//Cross-reference List �ʱ�ȭ ��Ų��.
	initCrossReferList(CrossReferList);

	//usedLine �˻� �� �ϼ� �κ�
	findUsedLine(SourceListRefer,CrossReferList);
	/*
	//FixedFormat File�� ��� �κ�
	printf("\n*********************************\n");
	printf("*****Fixed FormatSource File*****\n");
	printf("*********************************\n");
	printFixedList(SourceListPrint,writeFixedFile);
	printf("\n\n");
	*/
	//���ι�ȣ�� �� �ҽ� ����Ʈ ��� �κ�
	printf("*********************************\n");
	printf("*****Line Format Source File*****\n");
	printf("*********************************\n");
	printSourceList(SourceListPrint,writeLinesFile);
	printf("\n\n");

	//��ȣ ���� ����Ʈ�� ����ϴ� �κ�
	printf("*********************************\n");
	printf("***Cross reference Source File***\n");
	printf("*********************************\n");
	printf("Symbol\tDefined\tLines\n");
	printCrossReferList(CrossReferList);	

	//�߸��� ��ɾ� �Է� ��, ������� ���� ���̺��� �Է½� ������ ����ϴ� �κ�
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

// ���� ������ ã�� �κ��̴�.
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

//�̸� ������ ���� lable�� �ش����� �ʴ� lable�� ���� ��� ����ó���� �ؼ� �����޽����� ����Ѵ�.
void printOpCodeErrorList(OpCodeErrorList *head){
	OpCodeErrorList *p = head;	
	if(p == NULL)
		printf("\tThere is no error.\n\n"); // ���� �޽��� ����Ѵ�.

	while( p != NULL){ // ������ �߻��� ���ι�ȣ�� ���� lable�� �������� ����Ѵ�.
		printf("%d\t\t", p->num);
		printf("%s\n",  p->errorLable);
		p = p->link;
	}	
}

//Fixed Format Source File�� ����ϴ� �κ��̴�.
void printFixedList(SourceList *head ,FILE *a){
	FILE *f = a;
	SourceList *p = head;
	while( p != NULL){ // lable�� inst, vlaue�� ���ʷ� ����Ѵ�.
		printf("%s\t",p->lable);
		printf("%s\t",  p->inst);
		printf("%s\n",  p->value);
		p = p->link;
	}	
}

//Line��ȣ�� �� Source�� ����ϴ� �κ��̴�.
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

//crossReference �κ��� ����ϴ� �κ��̴�.
void printCrossReferList(CrossReferList *head){
	int f;
	CrossReferList *p = head;
	while( p != NULL){ // ��� � lable�� ���Ǿ����� ����Ѵ�.		
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
