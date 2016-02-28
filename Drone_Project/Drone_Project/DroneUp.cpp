#include<iostream>
#include<stdio.h>
#include<stdlib.h>
#include<time.h>
#include<math.h>
#include<stack>
#include<queue>
#include<Windows.h>
#define NMAX 100
#define MAX 999999 // 무한대의 수
#define mapSize 100
#define nodeNum 20
#define connectNum 5
#define initialDroneSpeed 150
#pragma warning (disable : 4996)

using namespace std;
using std::stack;

typedef struct pointtype{    //좌표상의 점들을 표현하는 구조체 ex)출발점, 도착점, 드론
	float x, y;             //x y 좌표
	int speed;            //드론의 속도
	int vDirection, hDirection;  //드론의 비행방향
}point;

typedef struct linetype{    // 드론의 경로(직선)을 표현하는 구조체
	point pt1;
	point pt2;
	float distance;
	float cos;
}line;

int direction(point A, point B, point C){   //세점의 상대위치 알고리즘(아래 교차판단 알고리즘에서 사용되는 알고리즘, 책에있는코드)
	float dxAB, dxAC;
	float dyAB, dyAC;
	int dir;

	dxAB = B.x - A.x;
	dxAC = C.x - A.x;
	dyAB = B.y - A.y;
	dyAC = C.y - A.y;

	if (dxAB * dyAC < dyAB* dxAC) dir = 1;   //시계방향
	if (dxAB * dyAC > dyAB* dxAC) dir = -1;  //반시계방향
	if (dxAB * dyAC == dyAB* dxAC){         //일직선
		if (dxAB == 0 && dyAB == 0) dir = 0;        //A=B
		else if ((dxAB*dxAC<0) || (dyAB*dyAC<0)) dir = -1; //A가 가운데
		else if (dxAB*dxAB + dyAB*dyAB >= dxAC*dxAC + dyAC*dyAC) dir = 0; //C가 가운데
		else dir = 1; //B가 가운데
	}
	return dir;
}

int intersection(line AB, line CD){    //두 선분의 교차여부를 판단하는 알고리즘(책에 있는 코드)
	int linecrossing;
	if ((direction(AB.pt1, AB.pt2, CD.pt1) * direction(AB.pt1, AB.pt2, CD.pt2) <= 0) && (direction(CD.pt1, CD.pt2, AB.pt1) * direction(CD.pt1, CD.pt2, AB.pt2) <= 0))
		linecrossing = 1;
	else
		linecrossing = 0;
	return linecrossing;
}

float y_point(line AB, float x){   //x좌표값으로 y좌표값 구하는 알고리즘
	float degree, b;

	degree = (AB.pt2.y - AB.pt1.y) / (AB.pt2.x - AB.pt1.x);
	b = AB.pt1.y - (degree*AB.pt1.x);

	return degree*x + b;
}

bool isSamePoint(point a, point b){  // 두 점이 같은 좌표상에 있는지 판별하는 코드
	bool result = false;
	if (a.x == b.x && a.y == b.y) result = true;
	return result;
}

point crossPoint(line AB, line CD, point droneA, point droneB){     // 두 선분이 교차할때, 교차점을 찾는 알고리즘        
	float a, b, c, d;
	point crosspoint;

	a = (AB.pt2.y - AB.pt1.y) / (AB.pt2.x - AB.pt1.x);   //직선 AB의 방정식 y=ax+b 에서 기울기 a
	b = AB.pt1.y - (a*AB.pt1.x);                           //방정식에서 더해지는 상수 b
	c = (CD.pt2.y - CD.pt1.y) / (CD.pt2.x - CD.pt1.x);
	d = CD.pt1.y - c*(CD.pt1.x);

	crosspoint.x = (d - b) / (a - c);
	crosspoint.y = a*crosspoint.x + b;

	if (a == c && b == d){     //두 선분이 하나의 직선상에 존재할때
		if ((AB.pt1.x < CD.pt1.x && CD.pt1.x < AB.pt2.x) || (AB.pt1.x < CD.pt2.x && CD.pt2.x < AB.pt2.x))
			cout << "경로가 겹칩니다" << endl;
		else if (isSamePoint(AB.pt1, CD.pt1) || isSamePoint(AB.pt1, CD.pt2)) crosspoint = AB.pt1;
		else if (isSamePoint(AB.pt2, CD.pt1) || isSamePoint(AB.pt2, CD.pt2)) crosspoint = AB.pt2;
	}

	if (droneA.hDirection == 0){  //드론A의 경로가 수직일때
		crosspoint.x = AB.pt1.x;
		crosspoint.y = crosspoint.x*c + d;
	}
	else if (droneA.vDirection == 0){    //드론B의 경로가 수평일때
		crosspoint.y = AB.pt1.y;
		crosspoint.x = (crosspoint.y - d) / c;
	}
	if (droneB.hDirection == 0){    //드론 A의 경로가 수직일때
		crosspoint.x = CD.pt1.x;
		crosspoint.y = crosspoint.x*a + b;
	}
	else if (droneB.vDirection == 0){  //드론 B의 경로가 수평일때
		crosspoint.y = CD.pt1.y;
		crosspoint.x = (crosspoint.y - b) / a;
	}
	return crosspoint;
}

point setDirection(line AB, point drone){   //드론의 이동방향 설정
	float h = AB.pt2.x - AB.pt1.x;
	float v = AB.pt2.y - AB.pt1.y;

	if (h>0.0) drone.hDirection = 1;          //드론이 동쪽으로 이동할경우
	else if (h<0.0) drone.hDirection = -1;   //드론이 서쪽으로 이동할경우
	else drone.hDirection = 0;                //수평좌표에서 변화가 없을경우

	if (v>0.0) drone.vDirection = 1;            //드론이 북쪽으로 이동할경우
	else if (v<0.0) drone.vDirection = -1;    //드론이 남쪽으로 이동할경우
	else drone.vDirection = 0;                 // 수직좌표에서 변화가 없을경우

	return drone;
}

line setCos(line AB){                //cos값을 구하는 함수
	float length = (float)sqrt((double)(AB.pt2.x - AB.pt1.x)*(AB.pt2.x - AB.pt1.x) + (double)(AB.pt2.y - AB.pt1.y)*(AB.pt2.y - AB.pt1.y)); // 두 점 사이의 거리
	float bottom = fabs(AB.pt2.x - AB.pt1.x); // 밑 변
	AB.cos = bottom / length;

	return AB;
}

int isArrived(line AB, point drone){  //드론이 도착지에 도달했는지 판별하는 알고리즘
	int result = 0;

	if (drone.hDirection == 1 && drone.x >= AB.pt2.x) result = 1;    //드론이 동쪽으로 이동할때
	else if (drone.hDirection == -1 && drone.x <= AB.pt2.x) result = 1;  //드론이 서쪽으로 이동할때
	else{  //드론이 수직으로 이동할때
		if (drone.vDirection == 1 && drone.y >= AB.pt2.y) result = 1;  //드론이 북쪽으로
		else if (drone.vDirection == -1 && drone.y <= AB.pt2.y) result = 1;  //남쪽으로
	}
	return result;
}

point move(line AB, point drone){    //이동거리만큼 드론의 좌표를 변경하는 코드

	if (drone.hDirection == 1){   //드론이 동쪽으로 이동할경우
		drone.x += AB.cos * drone.speed * (float)(1.0 / 60);   // 이동한 거리만큼 x값 증가 , 속도 x 이동시간 = 이동거리
		if (drone.vDirection != 0)
			drone.y = y_point(AB, drone.x);  //수평으로 이동하지 않을경우  y값 변경, 수평으로 이동할경우 y값은 변경없음
	}
	else if (drone.hDirection == -1){ // 드론이 서쪽으로 이동할경우
		drone.x -= AB.cos * drone.speed * (float)(1.0 / 60);   // 이동한 거리만큼 x값 감소
		if (drone.vDirection != 0)
			drone.y = y_point(AB, drone.x);  //수평으로 이동하지 않을경우  y값 변경, 수평으로 이동할경우 y값은 변경없음
	}
	else{   //드론이 수직으로 이동할경우(x값에 변화없음)
		if (drone.vDirection == 1)  //북쪽 방향
			drone.y += drone.speed * (float)(1.0 / 60);
		else   //남쪽방향
			drone.y -= drone.speed * (float)(1.0 / 60);
	}
	return drone;
}

float CPdistance(line AB, point cp){
	float x, y, distance;

	x = abs(cp.x - AB.pt1.x);
	y = abs(cp.y - AB.pt1.y);
	distance = (float)sqrt(x*x + y*y);

	return distance;
}

typedef struct nodetype{
	int x, y;
	int nodeNumber;
	float distance, cos;
	int connected;
}node;

class Graph
{
private:
	float length[NMAX][NMAX]; // 인접행렬
	float dist[NMAX]; // 최단거리를 저장할 배열
	bool s[NMAX]; // 최단경로를 발견한 정점의 집합
	int path[NMAX]; // 최단경로를 역추적할 배열
public:
	queue<int> qu;
	Graph(int size);
	void ShortestPath(const int n, const int v);
	void InsertEdge(int u, int v, float w);
	void PrintVertex(const int n, const int v, const int dest);
	int choose(const int n);
};

Graph::Graph(int size)   // 행렬에서 대각선은 모두 0으로, 나머지는 무한대로 초기화
{
	for (int i = 0; i < size; i++)
		for (int j = 0; j < size; j++){
			length[i][j] = (float)MAX;
			if (i == j) length[i][j] = 0;
		}
}

void Graph::InsertEdge(int u, int v, float w)
{
	length[u][v] = w; // u와 v 사이 간선의 가중치는 w
}

void Graph::PrintVertex(const int n, const int v, const int dest){  // 인접 행렬 출력
	for (int i = 0; i < n; i++){
		if (i == v)
			continue;  // 자기자신으로의 최단 경로는 없음

		stack<int> s; // 스택을 선언함
		s.push(MAX); // End of Record

		printf("노드%2d까지의 최단경로 : ", i);
		if (dist[i] == (float)MAX){  // 도달할 수 없는 정점에 대한 처리      
			cout << "도달할 수 없음" << endl;
			continue;
		}

		// 시작 : 각 정점, 종료 : 시작 정점과 같지 않을 때
		// 값이 인덱스가 되는 것을 반복하여 역추적
		for (int j = i; j != v; j = path[j])
			s.push(j); // 스택에 넣음
		cout << v;
		if (i == dest) qu.push(v);

		for (int j; (j = s.top()) != MAX; s.pop()) {   // 스택에서 하나씩 빼면서 EOR까지 출력
			cout << "->" << j;
			if (i == dest) qu.push(j);
		}
		cout << endl;
	}
}

int Graph::choose(const int n){   // S에 속하지 않는 정점 중에서 가장 작은 값을 찾아서 반환
	float min = (float)MAX;
	int min_index = 0;

	for (int i = 0; i < n; i++){
		if (!s[i] && min > dist[i]) { // S에 속하지 않는 정점 중에서
			min = dist[i];
			min_index = i; // 가장 작은 값을 찾음   
		}
	}
	return min_index; // 가장 작은 값을 반환
}

// dist[j],0 <= j < n은 n개의 정점을 가진 방향 그래프 G에서 정점 v로부터 정점 j
// 까지의 최단 경로 길이로 설정됨. 간선의 길이는 length[i][j]로 주어짐.
void Graph::ShortestPath(const int n, const int start){
	for (int i = 0; i < n; i++) { // 초기화
		s[i] = false; // 초기값 - 공집합
		dist[i] = length[start][i];  // 초기값 - 시작정점으로부터 직접 가는 거리
		path[i] = start; // 초기값 - 시작정점의 값
	}

	s[start] = true; // 자기 자신과의 최단 거리는 이미 정해짐
	dist[start] = 0; // 자기 자신과의 최단 거리는 0

	for (int i = 0; i < n - 2; i++) {    // 정점 v로부터 n-1개 경로를 결정
		int u = choose(n); // dist에서 가장 작은 값을 찾음
		s[u] = true;  // (여기서 s[w]=FALSE) 

		for (int w = 0; w < n; w++) {
			if (!s[w] && dist[u] + length[u][w] < dist[w]) {  // S에 속하지 않는 정점 중에서, 다른 정점을 거쳐서 가는 것이 더 비용이 적게 든다면
				dist[w] = dist[u] + length[u][w];  // 그 정점을 택함
				path[w] = u; // 역추적을 위한 path 배열에 저장   
			}
		}
	}
}

node makeMap(node nodeList[nodeNum][nodeNum]){
	int a, b;
	//   srand((unsigned)time(NULL));

	for (a = 0; a<nodeNum; a++){              //노드 리스트 초기화
		for (b = 0; b<nodeNum; b++){
			nodeList[a][b].x = 0;
			nodeList[a][b].y = 0;
			nodeList[a][b].connected = 0;
			nodeList[a][b].cos = 0.0;
			nodeList[a][b].nodeNumber = b;
			nodeList[a][b].distance = (float)MAX;
		}
	}

	for (a = 0; a<nodeNum; a++){      //임의의 좌표로 랜덤하게 노드들을 생성
		nodeList[0][a].x = rand() % (2 * mapSize) - mapSize;
		nodeList[0][a].y = rand() % (2 * mapSize) - mapSize;
		nodeList[0][a].distance = (float)MAX;
	}

	for (a = 0; a<nodeNum; a++){                       //노드에서 일정 범위 내에 존재하는 인접한 다른 노드들을 연결  
		int Aconnected = nodeList[0][a].connected;
		int gap = 1;
		int xd, yd;
		float distance, cos;
		while (nodeList[0][a].connected<connectNum){
			int flag = 0;
			for (b = 0; b<nodeNum; b++){
				int Bconnected = nodeList[0][b].connected;
				if (a != b &&
					((nodeList[0][a].y - gap == nodeList[0][b].y && nodeList[0][a].x - gap <= nodeList[0][b].x && nodeList[0][b].x <= nodeList[0][a].x + gap)
					|| (nodeList[0][a].y + gap == nodeList[0][b].y && nodeList[0][a].x - gap <= nodeList[0][b].x && nodeList[0][b].x <= nodeList[0][a].x + gap)
					|| (nodeList[0][a].x - gap == nodeList[0][b].x  && nodeList[0][a].y - gap <= nodeList[0][b].y && nodeList[0][b].y <= nodeList[0][a].y + gap)
					|| (nodeList[0][a].x + gap == nodeList[0][b].x  && nodeList[0][a].y - gap <= nodeList[0][b].y && nodeList[0][b].y <= nodeList[0][a].y + gap)
					)
					) {
					xd = abs(nodeList[0][a].x - nodeList[0][b].x);          //노드와 노드사이 거리 계산
					yd = abs(nodeList[0][a].y - nodeList[0][b].y);
					distance = (float)sqrt((double)(xd*xd + yd*yd));
					cos = xd / distance;

					for (int i = nodeList[0][a].connected; i>0; i--){
						if (nodeList[i][a].nodeNumber == nodeList[0][b].nodeNumber) flag = 1;
					}

					if (flag == 0){
						nodeList[Aconnected + 1][a] = nodeList[0][b];          //범위 내에 존재하는 인접노드를 연결
						nodeList[Bconnected + 1][b] = nodeList[0][a];
						nodeList[Aconnected + 1][a].distance = distance;
						nodeList[Aconnected + 1][a].cos = cos;
						nodeList[Bconnected + 1][b].distance = distance;
						nodeList[Bconnected + 1][b].cos = cos;
						Aconnected++;
						Bconnected++;
						nodeList[0][a].connected++;
						nodeList[0][b].connected++;
					}
				} // if
			} // for
			gap++;
		} // while
	} // for

	for (a = 0; a<nodeNum; a++){
		printf("%d(%d,%d)와 연결된 노드", a, nodeList[0][a].x, nodeList[0][a].y);
		for (int i = nodeList[0][a].connected; i>0; i--){
			printf("\n  %d(%d,%d) 거리: %.2f", nodeList[i][a].nodeNumber, nodeList[i][a].x, nodeList[i][a].y, nodeList[i][a].distance);
		}
		cout << endl;
	}
	return nodeList[nodeNum][nodeNum];
}

int main(){
	int a, b, flag = 0;   //반복문에 쓰이는 변수
	int start, dest;   // start는 출발노드, dest는 도착노드
	float w;   // w는 노드와 노드간 거리
	line AB, CD;
	point droneA = { 0 }, droneC = { 0 };

	Graph g(nodeNum);
	node nodeList[nodeNum][nodeNum];               //노드로 이루어진 2차원 배열 선언
	nodeList[nodeNum][nodeNum] = makeMap(nodeList);   //노드들에 지도입력

	for (a = 0; a<nodeNum; a++){                 //최단경로를 구하기 위하여, 각 노드들간의 거리를 입력 
		for (b = 1; b<nodeNum; b++){
			if (nodeList[b][a].distance != (float)MAX){
				start = nodeList[0][a].nodeNumber;
				dest = nodeList[b][a].nodeNumber;
				w = nodeList[b][a].distance;
				g.InsertEdge(start, dest, w);
			}
		}
	}

	point routeA[20], routeC[20];
	for (a = 0; a<20; a++)
		routeA[a].speed = routeC[a].speed = -1;

	printf("\n드론 A의 출발노드와 도착노드 입력(0~%d): ", nodeNum - 1);
	cin >> start >> dest;
	if (start>-1 && start<nodeNum && dest>-1 && dest<nodeNum){
		g.ShortestPath(nodeNum, start);
		g.PrintVertex(nodeNum, start, dest);
	}
	else printf("잘못된 입력 입니다.\n");

	a = 0;
	while (g.qu.size()>0){
		routeA[a].x = (float)nodeList[0][g.qu.front()].x;
		routeA[a].y = (float)nodeList[0][g.qu.front()].y;
		routeA[a].speed = 1;
		g.qu.pop();
		a++;
	}

	printf("\n드론C의 출발노드와 도착노드 입력(0~%d): ", nodeNum - 1);
	cin >> start >> dest;
	if (start>-1 && start<nodeNum && dest>-1 && dest<nodeNum){
		g.ShortestPath(nodeNum, start);
		g.PrintVertex(nodeNum, start, dest);
	}
	else printf("잘못된 입력 입니다.\n");

	a = 0;
	while (g.qu.size()>0){
		routeC[a].x = (float)nodeList[0][g.qu.front()].x;
		routeC[a].y = (float)nodeList[0][g.qu.front()].y;
		routeC[a].speed = 1;
		g.qu.pop();
		a++;
	}

	for (a = 0; a<20; a++){                           // 목적지 경로를 갱신하는 반복문
		AB.pt1 = routeA[a];
		AB.pt2 = routeA[a + 1];

		CD.pt1 = routeC[a];
		CD.pt2 = routeC[a + 1];

		if (routeA[a].speed == -1 && routeC[a].speed == -1){
			cout << "배송이 모두 완료되었습니다." << endl;
			break;
		}

		if (flag == 0){
			cout << "\n드론A의 최단경로는 ";
			printf("(%.0f,%.0f)", AB.pt1.x, AB.pt1.y);
			for (b = 1; b<20; b++){
				if (routeA[b].speed == -1) break;
				printf(" (%.0f,%.0f)", routeA[b].x, routeA[b].y);
			}
			cout << "입니다." << endl;

			cout << "드론C의 최단경로는 ";
			printf("(%.0f,%.0f)", CD.pt1.x, CD.pt1.y);
			for (b = 1; b<20; b++){
				if (routeC[b].speed == -1) break;
				printf(" (%.0f,%.0f)", routeC[b].x, routeC[b].y);
			}
			cout << "입니다.\n" << endl;
			printf("배송을 시작합니다.\n");
			flag = 1;
		}

		AB = setCos(AB);            //라인의 cos값 세팅
		CD = setCos(CD);
		droneA = setDirection(AB, droneA);         //드론이 어느방향으로 이동하는지 세팅  ex)동,서,남,북,동북,서남
		droneC = setDirection(CD, droneC);

		float hour = 13, min = 21;     // 현재시간 초기화   
		droneA.x = AB.pt1.x;           //드론의 현재위치를 출발점으로 초기화      
		droneA.y = AB.pt1.y;
		droneC.x = CD.pt1.x;
		droneC.y = CD.pt1.y;
		droneA.speed = droneC.speed = initialDroneSpeed;    //드론의 속도 초기화

		if (intersection(AB, CD) == 1 && !isSamePoint(AB.pt1, CD.pt1)){
			point cp = crossPoint(AB, CD, droneA, droneC);
			AB.distance = CPdistance(AB, cp);
			CD.distance = CPdistance(CD, cp);

			printf("드론A의 경로와 드론C의 경로에 교차점이 존재 합니다. ");
			cout << "(" << cp.x << ", " << cp.y << ")\n";

			if (AB.distance>CD.distance){
				cout << "충돌을 피하기 위하여 droneA의 속도를 10km/h 증가시킵니다." << endl;
				droneA.speed += 10;
			}
			else{
				cout << "충돌을 피하기 위하여 droneC의 속도를 10km/h 증가시킵니다." << endl;
				droneC.speed += 10;
			}
		}

		printf("[현재시간]\t| [드론A위치]\t[드론A속도]\t| [드론C위치]\t[드론C속도]\n");

		while (true){
			if (isArrived(AB, droneA) == 0 && isArrived(CD, droneC) == 0)   //둘다 배송중, 둘다 출력
				printf("%.0f시%.0f분\t| (%.1f,%.1f)\t%dkm/h\t\t| (%.1f,%.1f)\t%dkm/h\n)", hour, min, droneA.x, droneA.y, droneA.speed, droneC.x, droneC.y, droneC.speed);
			else if (isArrived(AB, droneA) == 0 && isArrived(CD, droneC) == 1)  //드론C 배송완료, 드론A만 출력
				printf("%.0f시%.0f분\t| (%.1f,%.1f)\t%dkm/h\n)", hour, min, droneA.x, droneA.y, droneA.speed);
			else if (isArrived(AB, droneA) == 1 && isArrived(CD, droneC) == 0)  //드론A 배송완료, 드론C만 출력
				printf("%.0f시%.0f분\t\t\t\t\t| (%.1f,%.1f)\t%dkm/h\n)", hour, min, droneC.x, droneC.y, droneC.speed);
			else break;

			Sleep(500);
			min += 1;
			if (min>59){
				min = 0;
				hour++;
			}

			droneA = move(AB, droneA);
			droneC = move(CD, droneC);
		} // while문의 끝
	} // 좌표설정 for문의 끝

	return 0;
}