#include <stdio.h>
#include <stdlib.h>

#define MAX_QUEUE_SIZE 4 // max 사이즈 정의 

typedef char element; // typedef 을 사용한 문자형 변수 선언 
typedef struct { // typedef 사용한 QueueType 구조체 선언 
	element queue[MAX_QUEUE_SIZE]; // 문자형 배열 큐 선언 
	int front, rear; // 삽입, 삭제를 위한 정수형 변수 2개 선언
}QueueType;


QueueType *createQueue(); // 큐 생성 함수 
int freeQueue(QueueType *cQ); // 큐 동적메모리 해체 함수 
int isEmpty(QueueType *cQ); // 큐가 비었는지 확인 함수
int isFull(QueueType *cQ); // 큐가 다차있는지 확인 함수
void enQueue(QueueType *cQ, element item); // 큐에 데이터 삽입 함수
void deQueue(QueueType *cQ, element* item); // 큐에 데이터 삭제 함수 
void printQ(QueueType *cQ); // 큐 출력 함수
void debugQ(QueueType *cQ); // 큐 디버그 함수 
element getElement(); // 큐 데이터 입력 받는 함수 


int main(void)
{
	QueueType *cQ = createQueue(); // 큐 생성 
	element data; // 문자형 변수 선언

	char command; // 문자형 변수 선언 
    printf("[----- [장원도] [2018038099] -----]");

	do{ // 반복문
		printf("\n-----------------------------------------------------\n");
		printf("                     Circular Q                   \n");
		printf("------------------------------------------------------\n");
		printf(" Insert=i,  Delete=d,   PrintQ=p,   Debug=b,   Quit=q \n");
		printf("------------------------------------------------------\n");

		printf("Command = ");
		scanf(" %c", &command); // 문자형 변수 입력 받음

		switch(command) { // 조건문 
		case 'i': case 'I': // i, I 를 누르면 
			data = getElement();
			enQueue(cQ, data); //enQueue 큐 데이터 넣음
			break; // 멈춤 
		case 'd': case 'D': // d, D 누르면
			deQueue(cQ,&data); // deQueue 삭제 
			break; // 멈춤 
		case 'p': case 'P': // p, P 누르면
			printQ(cQ); // printQ 함수 호출 큐 출력 
			break; // 멈춤 
		case 'b': case 'B': // b, B 누르면
			debugQ(cQ); // debugQ 함수 
			break; // 멈춤 
		case 'q': case 'Q': // q, Q 누르면 
			break; // 멈춤 
		default:
			printf("\n       >>>>>   Concentration!!   <<<<<     \n");
			break; // 멈춤 
		}

	}while(command != 'q' && command != 'Q'); //  q 나 Q가 입력되기 전까지 반복


	return 1; // 1값 반환
}

QueueType *createQueue() // 큐 생성
{
	QueueType *cQ; // QueueType *cQ선언 
	cQ = (QueueType *)malloc(sizeof(QueueType)); // 큐 동적메모리 할당 
	cQ->front = 0; // front 초기값 0  
	cQ->rear = 0; // rear 초기값 0
	return cQ; // cQ값 반환 
}

int freeQueue(QueueType *cQ) // 동적메모리 해체 함수 정의
{
    if(cQ == NULL) return 1; // cQ 가 Null 이면 1값 반환
    free(cQ); // cQ 동적메모리 해제
    return 1; // 1값 반환 
}

element getElement() // 큐에 넣을 요소 입력 받기 위한 함수  
{
	element item; // element item 선언 문자형
	printf("Input element = "); 
	scanf(" %c", &item); // 문자형 변수 입력 받음 
	return item; // item 값 반환 
}


int isEmpty(QueueType *cQ) // 큐가 비었는지 확인 함수 
{
	if (cQ->front == cQ->rear){ // 큐 front 와 rear가 같으면 
		printf("Circular Queue is empty!");
		return 1; // 1값 반환
	}
	else return 0; // 그 외의 경우 0값 반환 
}

int isFull(QueueType *cQ) // 큐가 full 상태인지 확인 함수 
{
	if (((cQ->rear+1)%MAX_QUEUE_SIZE) == cQ->front) { // rear 다음칸과 front가 같다면  
		printf(" Circular Queue is full!");
		return 1; // 1값 반환
	}
	else return 0; // 그 외의 경우 0값 반환 
}

void enQueue(QueueType *cQ, element item) // 큐에 데이터 넣는 함수 정의 
{
	if(isFull(cQ)) return; // 만약 큐가 풀이면 반환
	else { // 그 외의 경우 
		cQ->rear = (cQ->rear + 1) % MAX_QUEUE_SIZE; // rear에 rear+1 값 넣음 
		cQ->queue[cQ->rear] = item; // 큐에 item 값 넣음 
	}
}

void deQueue(QueueType *cQ, element *item) // 큐 삭제 함수 정의 
{
	if(isEmpty(cQ)) return; // 만약 큐가 풀이면 반환
	else { // 그 외 경우 
		cQ->front = (cQ->front + 1)%MAX_QUEUE_SIZE; // front에 front+1 값 넣음 
		*item = cQ->queue[cQ->front]; // *item에 큐 front 값 넣음 
		return; 
	}
}


void printQ(QueueType *cQ) // 출력 함수 정의 
{
	int i, first, last; // 정수형 변수 3개 선언 

	first = (cQ->front + 1)%MAX_QUEUE_SIZE; // first에 front 값 넣음 
	last = (cQ->rear + 1)%MAX_QUEUE_SIZE; // last에 rear 값 넣음 

	printf("Circular Queue : [");

	i = first; // i 에 first 값 넣음 
	while(i != last){ // i와 last가 같지 않으면 반복
		printf("%3c", cQ->queue[i]);
		i = (i+1)%MAX_QUEUE_SIZE; // i 에 i+1값 넣음 

	}
	printf(" ]\n");
}


void debugQ(QueueType *cQ) // 디버그 함수 정의 
{

	printf("\n---DEBUG\n");
	for(int i = 0; i < MAX_QUEUE_SIZE; i++) // i가 0 부터 max값 까지 반복 
	{
		if(i == cQ->front) { // i와 front값이 같으면
			printf("  [%d] = front\n", i); // i값과 같은 front값 출력
			continue; // 계속
		}
		printf("  [%d] = %c\n", i, cQ->queue[i]); // 큐 출력

	}
	//printQ(cQ);
	printf("front = %d, rear = %d\n", cQ->front, cQ->rear); // front, rear 출력 
}


