#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>

//Source List 구조체 부분
typedef struct SourceList{
	int num;
	char *lable;
	char *inst;
	char *value;
	struct SourceList *link;
}SourceList;

//Cross-reference List 구조체 부분
typedef struct CrossReferList{
	int num;
	char *lable;
	int usedLine[10];
	struct CrossReferList *link;
}CrossReferList;

//유효하지 않은 명령어를 담을 구조체 부분
typedef struct OpCodeErrorList{
	int num;
	char *errorLable;
	struct OpCodeErrorList *link;
}OpCodeErrorList;
 //oplist txt를로드
//char *opcode[80];
FILE *opcode2 = fopen("oplist.txt", "r");
//char *opcode[80]={0};
char opcode[50][60]={0};

//Opcode 목록 정의 부분

//Cross-reference List 노드 생성 부분
CrossReferList *cNodeCrossReferList(int num, char *lable, CrossReferList *link);
//Cross-reference List 역순 정렬 부분
CrossReferList *inverseCrossReferList(CrossReferList *head);
//Source List 노드 생성 부분
SourceList *cNodeSourceList(int num, char *lable, char *b, char *c, SourceList *link);
//Source List 역순 정렬 부분
SourceList *inverseSourceList(SourceList *head);
//명령어 오류 확인(체크)
OpCodeErrorList *checkErrorOpcodeList(SourceList *head);
//Cross-reference List 초기화
void initCrossReferList(CrossReferList *head);
//사용된 라인 검색
void findUsedLine(SourceList *headSourceList, CrossReferList *head);
//opcode 오류 출력
void printOpCodeErrorList(OpCodeErrorList *head);
//Source List 출력
void printSourceList(SourceList *head ,FILE *a);
//Fixed Format Source 출력
void printFixedList(SourceList *head, FILE *a);
//Cross-reference List 출력
void printCrossReferList(CrossReferList *head);

//Source List / Cross-reference List / Instruction List 노드 연결 함수
void insertNodeSourceList(SourceList **phead, SourceList *p, SourceList *new_node);
void insertNodeOpCodeErrorList(OpCodeErrorList **phead, OpCodeErrorList *p, OpCodeErrorList *new_node);
void insertNodeCrossReferList(CrossReferList **phead, CrossReferList *p, CrossReferList *new_node);
