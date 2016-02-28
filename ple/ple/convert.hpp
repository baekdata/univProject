#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>

//Source List ����ü �κ�
typedef struct SourceList{
	int num;
	char *lable;
	char *inst;
	char *value;
	struct SourceList *link;
}SourceList;

//Cross-reference List ����ü �κ�
typedef struct CrossReferList{
	int num;
	char *lable;
	int usedLine[10];
	struct CrossReferList *link;
}CrossReferList;

//��ȿ���� ���� ��ɾ ���� ����ü �κ�
typedef struct OpCodeErrorList{
	int num;
	char *errorLable;
	struct OpCodeErrorList *link;
}OpCodeErrorList;
 //oplist txt���ε�
//char *opcode[80];
FILE *opcode2 = fopen("oplist.txt", "r");
//char *opcode[80]={0};
char opcode[50][60]={0};

//Opcode ��� ���� �κ�

//Cross-reference List ��� ���� �κ�
CrossReferList *cNodeCrossReferList(int num, char *lable, CrossReferList *link);
//Cross-reference List ���� ���� �κ�
CrossReferList *inverseCrossReferList(CrossReferList *head);
//Source List ��� ���� �κ�
SourceList *cNodeSourceList(int num, char *lable, char *b, char *c, SourceList *link);
//Source List ���� ���� �κ�
SourceList *inverseSourceList(SourceList *head);
//��ɾ� ���� Ȯ��(üũ)
OpCodeErrorList *checkErrorOpcodeList(SourceList *head);
//Cross-reference List �ʱ�ȭ
void initCrossReferList(CrossReferList *head);
//���� ���� �˻�
void findUsedLine(SourceList *headSourceList, CrossReferList *head);
//opcode ���� ���
void printOpCodeErrorList(OpCodeErrorList *head);
//Source List ���
void printSourceList(SourceList *head ,FILE *a);
//Fixed Format Source ���
void printFixedList(SourceList *head, FILE *a);
//Cross-reference List ���
void printCrossReferList(CrossReferList *head);

//Source List / Cross-reference List / Instruction List ��� ���� �Լ�
void insertNodeSourceList(SourceList **phead, SourceList *p, SourceList *new_node);
void insertNodeOpCodeErrorList(OpCodeErrorList **phead, OpCodeErrorList *p, OpCodeErrorList *new_node);
void insertNodeCrossReferList(CrossReferList **phead, CrossReferList *p, CrossReferList *new_node);
