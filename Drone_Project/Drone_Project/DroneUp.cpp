#include<iostream>
#include<stdio.h>
#include<stdlib.h>
#include<time.h>
#include<math.h>
#include<stack>
#include<queue>
#include<Windows.h>
#define NMAX 100
#define MAX 999999 // ���Ѵ��� ��
#define mapSize 100
#define nodeNum 20
#define connectNum 5
#define initialDroneSpeed 150
#pragma warning (disable : 4996)

using namespace std;
using std::stack;

typedef struct pointtype{    //��ǥ���� ������ ǥ���ϴ� ����ü ex)�����, ������, ���
	float x, y;             //x y ��ǥ
	int speed;            //����� �ӵ�
	int vDirection, hDirection;  //����� �������
}point;

typedef struct linetype{    // ����� ���(����)�� ǥ���ϴ� ����ü
	point pt1;
	point pt2;
	float distance;
	float cos;
}line;

int direction(point A, point B, point C){   //������ �����ġ �˰���(�Ʒ� �����Ǵ� �˰��򿡼� ���Ǵ� �˰���, å���ִ��ڵ�)
	float dxAB, dxAC;
	float dyAB, dyAC;
	int dir;

	dxAB = B.x - A.x;
	dxAC = C.x - A.x;
	dyAB = B.y - A.y;
	dyAC = C.y - A.y;

	if (dxAB * dyAC < dyAB* dxAC) dir = 1;   //�ð����
	if (dxAB * dyAC > dyAB* dxAC) dir = -1;  //�ݽð����
	if (dxAB * dyAC == dyAB* dxAC){         //������
		if (dxAB == 0 && dyAB == 0) dir = 0;        //A=B
		else if ((dxAB*dxAC<0) || (dyAB*dyAC<0)) dir = -1; //A�� ���
		else if (dxAB*dxAB + dyAB*dyAB >= dxAC*dxAC + dyAC*dyAC) dir = 0; //C�� ���
		else dir = 1; //B�� ���
	}
	return dir;
}

int intersection(line AB, line CD){    //�� ������ �������θ� �Ǵ��ϴ� �˰���(å�� �ִ� �ڵ�)
	int linecrossing;
	if ((direction(AB.pt1, AB.pt2, CD.pt1) * direction(AB.pt1, AB.pt2, CD.pt2) <= 0) && (direction(CD.pt1, CD.pt2, AB.pt1) * direction(CD.pt1, CD.pt2, AB.pt2) <= 0))
		linecrossing = 1;
	else
		linecrossing = 0;
	return linecrossing;
}

float y_point(line AB, float x){   //x��ǥ������ y��ǥ�� ���ϴ� �˰���
	float degree, b;

	degree = (AB.pt2.y - AB.pt1.y) / (AB.pt2.x - AB.pt1.x);
	b = AB.pt1.y - (degree*AB.pt1.x);

	return degree*x + b;
}

bool isSamePoint(point a, point b){  // �� ���� ���� ��ǥ�� �ִ��� �Ǻ��ϴ� �ڵ�
	bool result = false;
	if (a.x == b.x && a.y == b.y) result = true;
	return result;
}

point crossPoint(line AB, line CD, point droneA, point droneB){     // �� ������ �����Ҷ�, �������� ã�� �˰���        
	float a, b, c, d;
	point crosspoint;

	a = (AB.pt2.y - AB.pt1.y) / (AB.pt2.x - AB.pt1.x);   //���� AB�� ������ y=ax+b ���� ���� a
	b = AB.pt1.y - (a*AB.pt1.x);                           //�����Ŀ��� �������� ��� b
	c = (CD.pt2.y - CD.pt1.y) / (CD.pt2.x - CD.pt1.x);
	d = CD.pt1.y - c*(CD.pt1.x);

	crosspoint.x = (d - b) / (a - c);
	crosspoint.y = a*crosspoint.x + b;

	if (a == c && b == d){     //�� ������ �ϳ��� ������ �����Ҷ�
		if ((AB.pt1.x < CD.pt1.x && CD.pt1.x < AB.pt2.x) || (AB.pt1.x < CD.pt2.x && CD.pt2.x < AB.pt2.x))
			cout << "��ΰ� ��Ĩ�ϴ�" << endl;
		else if (isSamePoint(AB.pt1, CD.pt1) || isSamePoint(AB.pt1, CD.pt2)) crosspoint = AB.pt1;
		else if (isSamePoint(AB.pt2, CD.pt1) || isSamePoint(AB.pt2, CD.pt2)) crosspoint = AB.pt2;
	}

	if (droneA.hDirection == 0){  //���A�� ��ΰ� �����϶�
		crosspoint.x = AB.pt1.x;
		crosspoint.y = crosspoint.x*c + d;
	}
	else if (droneA.vDirection == 0){    //���B�� ��ΰ� �����϶�
		crosspoint.y = AB.pt1.y;
		crosspoint.x = (crosspoint.y - d) / c;
	}
	if (droneB.hDirection == 0){    //��� A�� ��ΰ� �����϶�
		crosspoint.x = CD.pt1.x;
		crosspoint.y = crosspoint.x*a + b;
	}
	else if (droneB.vDirection == 0){  //��� B�� ��ΰ� �����϶�
		crosspoint.y = CD.pt1.y;
		crosspoint.x = (crosspoint.y - b) / a;
	}
	return crosspoint;
}

point setDirection(line AB, point drone){   //����� �̵����� ����
	float h = AB.pt2.x - AB.pt1.x;
	float v = AB.pt2.y - AB.pt1.y;

	if (h>0.0) drone.hDirection = 1;          //����� �������� �̵��Ұ��
	else if (h<0.0) drone.hDirection = -1;   //����� �������� �̵��Ұ��
	else drone.hDirection = 0;                //������ǥ���� ��ȭ�� �������

	if (v>0.0) drone.vDirection = 1;            //����� �������� �̵��Ұ��
	else if (v<0.0) drone.vDirection = -1;    //����� �������� �̵��Ұ��
	else drone.vDirection = 0;                 // ������ǥ���� ��ȭ�� �������

	return drone;
}

line setCos(line AB){                //cos���� ���ϴ� �Լ�
	float length = (float)sqrt((double)(AB.pt2.x - AB.pt1.x)*(AB.pt2.x - AB.pt1.x) + (double)(AB.pt2.y - AB.pt1.y)*(AB.pt2.y - AB.pt1.y)); // �� �� ������ �Ÿ�
	float bottom = fabs(AB.pt2.x - AB.pt1.x); // �� ��
	AB.cos = bottom / length;

	return AB;
}

int isArrived(line AB, point drone){  //����� �������� �����ߴ��� �Ǻ��ϴ� �˰���
	int result = 0;

	if (drone.hDirection == 1 && drone.x >= AB.pt2.x) result = 1;    //����� �������� �̵��Ҷ�
	else if (drone.hDirection == -1 && drone.x <= AB.pt2.x) result = 1;  //����� �������� �̵��Ҷ�
	else{  //����� �������� �̵��Ҷ�
		if (drone.vDirection == 1 && drone.y >= AB.pt2.y) result = 1;  //����� ��������
		else if (drone.vDirection == -1 && drone.y <= AB.pt2.y) result = 1;  //��������
	}
	return result;
}

point move(line AB, point drone){    //�̵��Ÿ���ŭ ����� ��ǥ�� �����ϴ� �ڵ�

	if (drone.hDirection == 1){   //����� �������� �̵��Ұ��
		drone.x += AB.cos * drone.speed * (float)(1.0 / 60);   // �̵��� �Ÿ���ŭ x�� ���� , �ӵ� x �̵��ð� = �̵��Ÿ�
		if (drone.vDirection != 0)
			drone.y = y_point(AB, drone.x);  //�������� �̵����� �������  y�� ����, �������� �̵��Ұ�� y���� �������
	}
	else if (drone.hDirection == -1){ // ����� �������� �̵��Ұ��
		drone.x -= AB.cos * drone.speed * (float)(1.0 / 60);   // �̵��� �Ÿ���ŭ x�� ����
		if (drone.vDirection != 0)
			drone.y = y_point(AB, drone.x);  //�������� �̵����� �������  y�� ����, �������� �̵��Ұ�� y���� �������
	}
	else{   //����� �������� �̵��Ұ��(x���� ��ȭ����)
		if (drone.vDirection == 1)  //���� ����
			drone.y += drone.speed * (float)(1.0 / 60);
		else   //���ʹ���
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
	float length[NMAX][NMAX]; // �������
	float dist[NMAX]; // �ִܰŸ��� ������ �迭
	bool s[NMAX]; // �ִܰ�θ� �߰��� ������ ����
	int path[NMAX]; // �ִܰ�θ� �������� �迭
public:
	queue<int> qu;
	Graph(int size);
	void ShortestPath(const int n, const int v);
	void InsertEdge(int u, int v, float w);
	void PrintVertex(const int n, const int v, const int dest);
	int choose(const int n);
};

Graph::Graph(int size)   // ��Ŀ��� �밢���� ��� 0����, �������� ���Ѵ�� �ʱ�ȭ
{
	for (int i = 0; i < size; i++)
		for (int j = 0; j < size; j++){
			length[i][j] = (float)MAX;
			if (i == j) length[i][j] = 0;
		}
}

void Graph::InsertEdge(int u, int v, float w)
{
	length[u][v] = w; // u�� v ���� ������ ����ġ�� w
}

void Graph::PrintVertex(const int n, const int v, const int dest){  // ���� ��� ���
	for (int i = 0; i < n; i++){
		if (i == v)
			continue;  // �ڱ��ڽ������� �ִ� ��δ� ����

		stack<int> s; // ������ ������
		s.push(MAX); // End of Record

		printf("���%2d������ �ִܰ�� : ", i);
		if (dist[i] == (float)MAX){  // ������ �� ���� ������ ���� ó��      
			cout << "������ �� ����" << endl;
			continue;
		}

		// ���� : �� ����, ���� : ���� ������ ���� ���� ��
		// ���� �ε����� �Ǵ� ���� �ݺ��Ͽ� ������
		for (int j = i; j != v; j = path[j])
			s.push(j); // ���ÿ� ����
		cout << v;
		if (i == dest) qu.push(v);

		for (int j; (j = s.top()) != MAX; s.pop()) {   // ���ÿ��� �ϳ��� ���鼭 EOR���� ���
			cout << "->" << j;
			if (i == dest) qu.push(j);
		}
		cout << endl;
	}
}

int Graph::choose(const int n){   // S�� ������ �ʴ� ���� �߿��� ���� ���� ���� ã�Ƽ� ��ȯ
	float min = (float)MAX;
	int min_index = 0;

	for (int i = 0; i < n; i++){
		if (!s[i] && min > dist[i]) { // S�� ������ �ʴ� ���� �߿���
			min = dist[i];
			min_index = i; // ���� ���� ���� ã��   
		}
	}
	return min_index; // ���� ���� ���� ��ȯ
}

// dist[j],0 <= j < n�� n���� ������ ���� ���� �׷��� G���� ���� v�κ��� ���� j
// ������ �ִ� ��� ���̷� ������. ������ ���̴� length[i][j]�� �־���.
void Graph::ShortestPath(const int n, const int start){
	for (int i = 0; i < n; i++) { // �ʱ�ȭ
		s[i] = false; // �ʱⰪ - ������
		dist[i] = length[start][i];  // �ʱⰪ - �����������κ��� ���� ���� �Ÿ�
		path[i] = start; // �ʱⰪ - ���������� ��
	}

	s[start] = true; // �ڱ� �ڽŰ��� �ִ� �Ÿ��� �̹� ������
	dist[start] = 0; // �ڱ� �ڽŰ��� �ִ� �Ÿ��� 0

	for (int i = 0; i < n - 2; i++) {    // ���� v�κ��� n-1�� ��θ� ����
		int u = choose(n); // dist���� ���� ���� ���� ã��
		s[u] = true;  // (���⼭ s[w]=FALSE) 

		for (int w = 0; w < n; w++) {
			if (!s[w] && dist[u] + length[u][w] < dist[w]) {  // S�� ������ �ʴ� ���� �߿���, �ٸ� ������ ���ļ� ���� ���� �� ����� ���� ��ٸ�
				dist[w] = dist[u] + length[u][w];  // �� ������ ����
				path[w] = u; // �������� ���� path �迭�� ����   
			}
		}
	}
}

node makeMap(node nodeList[nodeNum][nodeNum]){
	int a, b;
	//   srand((unsigned)time(NULL));

	for (a = 0; a<nodeNum; a++){              //��� ����Ʈ �ʱ�ȭ
		for (b = 0; b<nodeNum; b++){
			nodeList[a][b].x = 0;
			nodeList[a][b].y = 0;
			nodeList[a][b].connected = 0;
			nodeList[a][b].cos = 0.0;
			nodeList[a][b].nodeNumber = b;
			nodeList[a][b].distance = (float)MAX;
		}
	}

	for (a = 0; a<nodeNum; a++){      //������ ��ǥ�� �����ϰ� ������ ����
		nodeList[0][a].x = rand() % (2 * mapSize) - mapSize;
		nodeList[0][a].y = rand() % (2 * mapSize) - mapSize;
		nodeList[0][a].distance = (float)MAX;
	}

	for (a = 0; a<nodeNum; a++){                       //��忡�� ���� ���� ���� �����ϴ� ������ �ٸ� ������ ����  
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
					xd = abs(nodeList[0][a].x - nodeList[0][b].x);          //���� ������ �Ÿ� ���
					yd = abs(nodeList[0][a].y - nodeList[0][b].y);
					distance = (float)sqrt((double)(xd*xd + yd*yd));
					cos = xd / distance;

					for (int i = nodeList[0][a].connected; i>0; i--){
						if (nodeList[i][a].nodeNumber == nodeList[0][b].nodeNumber) flag = 1;
					}

					if (flag == 0){
						nodeList[Aconnected + 1][a] = nodeList[0][b];          //���� ���� �����ϴ� ������带 ����
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
		printf("%d(%d,%d)�� ����� ���", a, nodeList[0][a].x, nodeList[0][a].y);
		for (int i = nodeList[0][a].connected; i>0; i--){
			printf("\n  %d(%d,%d) �Ÿ�: %.2f", nodeList[i][a].nodeNumber, nodeList[i][a].x, nodeList[i][a].y, nodeList[i][a].distance);
		}
		cout << endl;
	}
	return nodeList[nodeNum][nodeNum];
}

int main(){
	int a, b, flag = 0;   //�ݺ����� ���̴� ����
	int start, dest;   // start�� ��߳��, dest�� �������
	float w;   // w�� ���� ��尣 �Ÿ�
	line AB, CD;
	point droneA = { 0 }, droneC = { 0 };

	Graph g(nodeNum);
	node nodeList[nodeNum][nodeNum];               //���� �̷���� 2���� �迭 ����
	nodeList[nodeNum][nodeNum] = makeMap(nodeList);   //���鿡 �����Է�

	for (a = 0; a<nodeNum; a++){                 //�ִܰ�θ� ���ϱ� ���Ͽ�, �� ���鰣�� �Ÿ��� �Է� 
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

	printf("\n��� A�� ��߳��� ������� �Է�(0~%d): ", nodeNum - 1);
	cin >> start >> dest;
	if (start>-1 && start<nodeNum && dest>-1 && dest<nodeNum){
		g.ShortestPath(nodeNum, start);
		g.PrintVertex(nodeNum, start, dest);
	}
	else printf("�߸��� �Է� �Դϴ�.\n");

	a = 0;
	while (g.qu.size()>0){
		routeA[a].x = (float)nodeList[0][g.qu.front()].x;
		routeA[a].y = (float)nodeList[0][g.qu.front()].y;
		routeA[a].speed = 1;
		g.qu.pop();
		a++;
	}

	printf("\n���C�� ��߳��� ������� �Է�(0~%d): ", nodeNum - 1);
	cin >> start >> dest;
	if (start>-1 && start<nodeNum && dest>-1 && dest<nodeNum){
		g.ShortestPath(nodeNum, start);
		g.PrintVertex(nodeNum, start, dest);
	}
	else printf("�߸��� �Է� �Դϴ�.\n");

	a = 0;
	while (g.qu.size()>0){
		routeC[a].x = (float)nodeList[0][g.qu.front()].x;
		routeC[a].y = (float)nodeList[0][g.qu.front()].y;
		routeC[a].speed = 1;
		g.qu.pop();
		a++;
	}

	for (a = 0; a<20; a++){                           // ������ ��θ� �����ϴ� �ݺ���
		AB.pt1 = routeA[a];
		AB.pt2 = routeA[a + 1];

		CD.pt1 = routeC[a];
		CD.pt2 = routeC[a + 1];

		if (routeA[a].speed == -1 && routeC[a].speed == -1){
			cout << "����� ��� �Ϸ�Ǿ����ϴ�." << endl;
			break;
		}

		if (flag == 0){
			cout << "\n���A�� �ִܰ�δ� ";
			printf("(%.0f,%.0f)", AB.pt1.x, AB.pt1.y);
			for (b = 1; b<20; b++){
				if (routeA[b].speed == -1) break;
				printf(" (%.0f,%.0f)", routeA[b].x, routeA[b].y);
			}
			cout << "�Դϴ�." << endl;

			cout << "���C�� �ִܰ�δ� ";
			printf("(%.0f,%.0f)", CD.pt1.x, CD.pt1.y);
			for (b = 1; b<20; b++){
				if (routeC[b].speed == -1) break;
				printf(" (%.0f,%.0f)", routeC[b].x, routeC[b].y);
			}
			cout << "�Դϴ�.\n" << endl;
			printf("����� �����մϴ�.\n");
			flag = 1;
		}

		AB = setCos(AB);            //������ cos�� ����
		CD = setCos(CD);
		droneA = setDirection(AB, droneA);         //����� ����������� �̵��ϴ��� ����  ex)��,��,��,��,����,����
		droneC = setDirection(CD, droneC);

		float hour = 13, min = 21;     // ����ð� �ʱ�ȭ   
		droneA.x = AB.pt1.x;           //����� ������ġ�� ��������� �ʱ�ȭ      
		droneA.y = AB.pt1.y;
		droneC.x = CD.pt1.x;
		droneC.y = CD.pt1.y;
		droneA.speed = droneC.speed = initialDroneSpeed;    //����� �ӵ� �ʱ�ȭ

		if (intersection(AB, CD) == 1 && !isSamePoint(AB.pt1, CD.pt1)){
			point cp = crossPoint(AB, CD, droneA, droneC);
			AB.distance = CPdistance(AB, cp);
			CD.distance = CPdistance(CD, cp);

			printf("���A�� ��ο� ���C�� ��ο� �������� ���� �մϴ�. ");
			cout << "(" << cp.x << ", " << cp.y << ")\n";

			if (AB.distance>CD.distance){
				cout << "�浹�� ���ϱ� ���Ͽ� droneA�� �ӵ��� 10km/h ������ŵ�ϴ�." << endl;
				droneA.speed += 10;
			}
			else{
				cout << "�浹�� ���ϱ� ���Ͽ� droneC�� �ӵ��� 10km/h ������ŵ�ϴ�." << endl;
				droneC.speed += 10;
			}
		}

		printf("[����ð�]\t| [���A��ġ]\t[���A�ӵ�]\t| [���C��ġ]\t[���C�ӵ�]\n");

		while (true){
			if (isArrived(AB, droneA) == 0 && isArrived(CD, droneC) == 0)   //�Ѵ� �����, �Ѵ� ���
				printf("%.0f��%.0f��\t| (%.1f,%.1f)\t%dkm/h\t\t| (%.1f,%.1f)\t%dkm/h\n)", hour, min, droneA.x, droneA.y, droneA.speed, droneC.x, droneC.y, droneC.speed);
			else if (isArrived(AB, droneA) == 0 && isArrived(CD, droneC) == 1)  //���C ��ۿϷ�, ���A�� ���
				printf("%.0f��%.0f��\t| (%.1f,%.1f)\t%dkm/h\n)", hour, min, droneA.x, droneA.y, droneA.speed);
			else if (isArrived(AB, droneA) == 1 && isArrived(CD, droneC) == 0)  //���A ��ۿϷ�, ���C�� ���
				printf("%.0f��%.0f��\t\t\t\t\t| (%.1f,%.1f)\t%dkm/h\n)", hour, min, droneC.x, droneC.y, droneC.speed);
			else break;

			Sleep(500);
			min += 1;
			if (min>59){
				min = 0;
				hour++;
			}

			droneA = move(AB, droneA);
			droneC = move(CD, droneC);
		} // while���� ��
	} // ��ǥ���� for���� ��

	return 0;
}