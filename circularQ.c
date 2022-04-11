#include <stdio.h>
#include <stdlib.h>

#define MAX_QUEUE_SIZE 4 // max ������ ���� 

typedef char element; // typedef �� ����� ������ ���� ���� 
typedef struct { // typedef ����� QueueType ����ü ���� 
	element queue[MAX_QUEUE_SIZE]; // ������ �迭 ť ���� 
	int front, rear; // ����, ������ ���� ������ ���� 2�� ����
}QueueType;


QueueType *createQueue(); // ť ���� �Լ� 
int freeQueue(QueueType *cQ); // ť �����޸� ��ü �Լ� 
int isEmpty(QueueType *cQ); // ť�� ������� Ȯ�� �Լ�
int isFull(QueueType *cQ); // ť�� �����ִ��� Ȯ�� �Լ�
void enQueue(QueueType *cQ, element item); // ť�� ������ ���� �Լ�
void deQueue(QueueType *cQ, element* item); // ť�� ������ ���� �Լ� 
void printQ(QueueType *cQ); // ť ��� �Լ�
void debugQ(QueueType *cQ); // ť ����� �Լ� 
element getElement(); // ť ������ �Է� �޴� �Լ� 


int main(void)
{
	QueueType *cQ = createQueue(); // ť ���� 
	element data; // ������ ���� ����

	char command; // ������ ���� ���� 
    printf("[----- [�����] [2018038099] -----]");

	do{ // �ݺ���
		printf("\n-----------------------------------------------------\n");
		printf("                     Circular Q                   \n");
		printf("------------------------------------------------------\n");
		printf(" Insert=i,  Delete=d,   PrintQ=p,   Debug=b,   Quit=q \n");
		printf("------------------------------------------------------\n");

		printf("Command = ");
		scanf(" %c", &command); // ������ ���� �Է� ����

		switch(command) { // ���ǹ� 
		case 'i': case 'I': // i, I �� ������ 
			data = getElement();
			enQueue(cQ, data); //enQueue ť ������ ����
			break; // ���� 
		case 'd': case 'D': // d, D ������
			deQueue(cQ,&data); // deQueue ���� 
			break; // ���� 
		case 'p': case 'P': // p, P ������
			printQ(cQ); // printQ �Լ� ȣ�� ť ��� 
			break; // ���� 
		case 'b': case 'B': // b, B ������
			debugQ(cQ); // debugQ �Լ� 
			break; // ���� 
		case 'q': case 'Q': // q, Q ������ 
			break; // ���� 
		default:
			printf("\n       >>>>>   Concentration!!   <<<<<     \n");
			break; // ���� 
		}

	}while(command != 'q' && command != 'Q'); //  q �� Q�� �ԷµǱ� ������ �ݺ�


	return 1; // 1�� ��ȯ
}

QueueType *createQueue() // ť ����
{
	QueueType *cQ; // QueueType *cQ���� 
	cQ = (QueueType *)malloc(sizeof(QueueType)); // ť �����޸� �Ҵ� 
	cQ->front = 0; // front �ʱⰪ 0  
	cQ->rear = 0; // rear �ʱⰪ 0
	return cQ; // cQ�� ��ȯ 
}

int freeQueue(QueueType *cQ) // �����޸� ��ü �Լ� ����
{
    if(cQ == NULL) return 1; // cQ �� Null �̸� 1�� ��ȯ
    free(cQ); // cQ �����޸� ����
    return 1; // 1�� ��ȯ 
}

element getElement() // ť�� ���� ��� �Է� �ޱ� ���� �Լ�  
{
	element item; // element item ���� ������
	printf("Input element = "); 
	scanf(" %c", &item); // ������ ���� �Է� ���� 
	return item; // item �� ��ȯ 
}


int isEmpty(QueueType *cQ) // ť�� ������� Ȯ�� �Լ� 
{
	if (cQ->front == cQ->rear){ // ť front �� rear�� ������ 
		printf("Circular Queue is empty!");
		return 1; // 1�� ��ȯ
	}
	else return 0; // �� ���� ��� 0�� ��ȯ 
}

int isFull(QueueType *cQ) // ť�� full �������� Ȯ�� �Լ� 
{
	if (((cQ->rear+1)%MAX_QUEUE_SIZE) == cQ->front) { // rear ����ĭ�� front�� ���ٸ�  
		printf(" Circular Queue is full!");
		return 1; // 1�� ��ȯ
	}
	else return 0; // �� ���� ��� 0�� ��ȯ 
}

void enQueue(QueueType *cQ, element item) // ť�� ������ �ִ� �Լ� ���� 
{
	if(isFull(cQ)) return; // ���� ť�� Ǯ�̸� ��ȯ
	else { // �� ���� ��� 
		cQ->rear = (cQ->rear + 1) % MAX_QUEUE_SIZE; // rear�� rear+1 �� ���� 
		cQ->queue[cQ->rear] = item; // ť�� item �� ���� 
	}
}

void deQueue(QueueType *cQ, element *item) // ť ���� �Լ� ���� 
{
	if(isEmpty(cQ)) return; // ���� ť�� Ǯ�̸� ��ȯ
	else { // �� �� ��� 
		cQ->front = (cQ->front + 1)%MAX_QUEUE_SIZE; // front�� front+1 �� ���� 
		*item = cQ->queue[cQ->front]; // *item�� ť front �� ���� 
		return; 
	}
}


void printQ(QueueType *cQ) // ��� �Լ� ���� 
{
	int i, first, last; // ������ ���� 3�� ���� 

	first = (cQ->front + 1)%MAX_QUEUE_SIZE; // first�� front �� ���� 
	last = (cQ->rear + 1)%MAX_QUEUE_SIZE; // last�� rear �� ���� 

	printf("Circular Queue : [");

	i = first; // i �� first �� ���� 
	while(i != last){ // i�� last�� ���� ������ �ݺ�
		printf("%3c", cQ->queue[i]);
		i = (i+1)%MAX_QUEUE_SIZE; // i �� i+1�� ���� 

	}
	printf(" ]\n");
}


void debugQ(QueueType *cQ) // ����� �Լ� ���� 
{

	printf("\n---DEBUG\n");
	for(int i = 0; i < MAX_QUEUE_SIZE; i++) // i�� 0 ���� max�� ���� �ݺ� 
	{
		if(i == cQ->front) { // i�� front���� ������
			printf("  [%d] = front\n", i); // i���� ���� front�� ���
			continue; // ���
		}
		printf("  [%d] = %c\n", i, cQ->queue[i]); // ť ���

	}
	//printQ(cQ);
	printf("front = %d, rear = %d\n", cQ->front, cQ->rear); // front, rear ��� 
}


