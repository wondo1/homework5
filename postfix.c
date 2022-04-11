#include<stdio.h>
#include<stdlib.h>
#include<ctype.h>
#include<string.h>

#define MAX_STACK_SIZE 10 // 스택 최대값 정의 
#define MAX_EXPRESSION_SIZE 20 // MAX_EXPRESSION_SIZE 최대값 정의 

/* stack 내에서 우선순위는 내림차순, lparen = 0 가장 낮음 */
typedef enum{ 
	lparen = 0,  /* ( 왼쪽 괄호 */
	rparen = 9,  /* ) 오른쪽 괄호*/
	times = 7,   /* * 곱셈 */
	divide = 6,  /* / 나눗셈 */
	plus = 5,    /* + 덧셈 */
	minus = 4,   /* - 뺄셈 */
	operand = 1 /* 피연산자 */
} precedence;

char infixExp[MAX_EXPRESSION_SIZE]; // 문자형 infixExp배열 선언, 중위
char postfixExp[MAX_EXPRESSION_SIZE]; // 문자형 postfixExp 배열 선언, 후위 
char postfixStack[MAX_STACK_SIZE]; // 문자형 postfixStack 배열 선언, 후위스택
int evalStack[MAX_STACK_SIZE]; // 정수형 evalStack 배열 선언, 연산

int postfixStackTop = -1; // postfixStackTop 값 -1
int evalStackTop = -1; // evalStackTop 값 -1

int evalResult = 0; // evalResult 값 0

void postfixPush(char x); // 스택에 넣은 함수 
char postfixPop(); // 스택에서 제거하는 함수 
void evalPush(int x); // 계산스택에 넣는 함수 
int evalPop(); // 계산 스택에서 삭제 함수 
void getInfix(); // 중위표기식 함수 
precedence getToken(char symbol); // symbol값 반환 함수 
precedence getPriority(char x); // x값 반환 함수 
void charCat(char* c); // 문자 전달 함수 
void toPostfix(); //  postix 변경 함수 
void debug(); // denug 함수 
void reset(); // 초기화 함수 
void evaluation(); // 계산 함수 

int main()
{
	char command; // 문자형 함수 정의 
	printf("[----- [장원도] [2018038099] -----]");
	
	do{ // 반복문 
		printf("----------------------------------------------------------------\n");
		printf("               Infix to Postfix, then Evaluation               \n");
		printf("----------------------------------------------------------------\n");
		printf(" Infix=i,   Postfix=p,  Eval=e,   Debug=d,   Reset=r,   Quit=q \n");
		printf("----------------------------------------------------------------\n");

		printf("Command = ");
		scanf(" %c", &command); // 문자형 변수 입력 받음

		switch(command) { // 조건문
		case 'i': case 'I': // i, I 를 누르면
			getInfix();
			break; // 멈춤
		case 'p': case 'P': // p, P 누르면
			toPostfix();
			break; // 멈춤
		case 'e': case 'E': // e, E 누르면 
			evaluation();
			break; // 멈춤
		case 'd': case 'D': // d, D 누르면
			debug();
			break; // 멈춤
		case 'r': case 'R': // r, R 누르면
			reset();
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

void postfixPush(char x) // postfixPush 함수 정의 
{
    postfixStack[++postfixStackTop] = x; // postfixStack에 ++된 postfixStackTop값에 x값 넣음 
}

char postfixPop() // postfixPop 함수 정의 
{
	char x; // 문자형 변수 선언 
    if(postfixStackTop == -1) // postfixStackTop값에 -1과 같으면
        return '\0'; //  \0 값 반환
    else { // 그 외 경우 
    	x = postfixStack[postfixStackTop--]; //postfixStack[postfixStackTop--]값 x에 넣음 
    }
    return x; // x값 반환 
}

void evalPush(int x) // evalPush 함수 정의 
{
    evalStack[++evalStackTop] = x; // evalstack에 ++evalStackTop 값에 x값 넣음 
}

int evalPop() // evalPop 함수 정의 
{
    if(evalStackTop == -1) // 만약 eval스택탑과 -1이 같으면 
        return -1; // -1값 반환
    else // 그 외
        return evalStack[evalStackTop--]; // evalStack[evalStackTop--]값 반환 
}

/**
 * infix expression을 입력받는다.
 * infixExp에는 입력된 값을 저장한다.
 */

void getInfix() // getInfix 함수 정의 
{
    printf("Type the expression >>> ");
    scanf("%s",infixExp); // infixExp 값 입력 받음 
}

precedence getToken(char symbol) // 입력 스트링으로 토큰을 가져오는 함수  
{
	switch(symbol) { // 조건문 
	case '(' : return lparen; // ( 입력시 lparen 반환
	case ')' : return rparen; // ) 입력시 rparen 반환
	case '+' : return plus; // + 입력시 plus 반환
	case '-' : return minus; // - 입력시 minus 반환 
	case '/' : return divide; // / 입력시 divide 반환 
	case '*' : return times; // * 입력시 times 반환 
	default : return operand; // operand 값 반환
	}
}

precedence getPriority(char x) // getPriority 함수 정의 
{
	return getToken(x); // 토큰 x값 반환
}

/**
 * 문자하나를 전달받아, postfixExp에 추가
 */
void charCat(char* c) // charCat 함수 정의
{
	if (postfixExp == '\0') // postfixExp 값과 같다면 
		strncpy(postfixExp, c, 1); // c문자를 postfixExp로 복사 1개 만큼 
	else // 그 외 
		strncat(postfixExp, c, 1); // c문자를 postfixExp로 붙임 1개 만큼 
}

/**
 * infixExp의 문자를 하나씩 읽어가면서 stack을 이용하여 postfix로 변경한다.
 * 변경된 postfix는 postFixExp에 저장된다.
 */
void toPostfix() // toPostfix 함수 정의 
{
	/* infixExp의 문자 하나씩을 읽기위한 포인터 */
	char *exp = infixExp;
	char x; /* 문자하나를 임시로 저장하기 위한 변수 */

	/* exp를 증가시켜가면서, 문자를 읽고 postfix로 변경 */
	while(*exp != '\0') // 반복문 
	{
		if(getPriority(*exp) == operand) // 
		{
			x = *exp; // x에 *exp 값 넣음 
        	charCat(&x); // charCat함수에 &x값 전달 
		}
        else if(getPriority(*exp) == lparen) { //  ( 와 같은 경우 

        	postfixPush(*exp); // postfixPush 함수에 *exp값 전달
        }
        else if(getPriority(*exp) == rparen) // ) 와 같은 경우 
        {
        	while((x = postfixPop()) != '(') { // x에 postfixPop()값과 (와 같지 않다면
        		charCat(&x);  // charCat함수에 &x값 전달 
        	}
        }
        else
        {
            while(getPriority(postfixStack[postfixStackTop]) >= getPriority(*exp)) // 스택 탑이 getPriority(*exp)와 같거나 큰경우 
            {
            	x = postfixPop(); // x에 postfixPop 값 넣음 
            	charCat(&x);  // charCat함수에 &x값 전달 
            }
            postfixPush(*exp);  // postfixPush 함수에 *exp값 전달
        }
        exp++; // exp 증가 
	}

    while(postfixStackTop != -1) // 스택 탑이 -1이 아니면
    {
    	x = postfixPop(); // x에 postfixPop 값 넣음
    	charCat(&x); // 
    }

}

void debug() // debug 함수 정의 
{
	printf("\n---DEBUG\n");
	printf("infixExp =  %s\n", infixExp);
	printf("postExp =  %s\n", postfixExp);
	printf("eval result = %d\n", evalResult);

	printf("postfixStack : ");
	for(int i = 0; i < MAX_STACK_SIZE; i++) // i값 0 부터 맥스 사이즈 만큼 반복
		printf("%c  ", postfixStack[i]); // postfixStack[i] 배열 출력 

	printf("\n");

}

void reset() // reset 함수 정의 
{
	infixExp[0] = '\0'; // infixExp[0]에 \0 넣음 
	postfixExp[0] = '\0'; // postfixExp[0] \0 값 넣음

	for(int i = 0; i < MAX_STACK_SIZE; i++) // i값 0 부터 맥스 사이즈 만큼 반복 
		postfixStack[i] = '\0'; // postfixStack[i]에 \0값 넣음 
         
	postfixStackTop = -1; // -1 값 넣음
	evalStackTop = -1; // -1 값 넣음 
	evalResult = 0; // 0 값 넣음 
}
void evaluation() // evaluation 함수 정의 
{
	int opr1, opr2, i; // 정수형 변수 3개 선언

	int length = strlen(postfixExp); // length에 strlen(postfixExp)넣음 
	char symbol; // 문자형 변수 선언 
	evalStackTop = -1; // -1 값 넣음 

	for(i = 0; i < length; i++) // length 만큼 반복
	{
		symbol = postfixExp[i]; // symbol에 postfixExp[i]값 넣음 
		if(getToken(symbol) == operand) { // 만약 토큰 심볼 값과 operand가 같다면
			evalPush(symbol - '0'); //symbol - '0'값 넣음 
		}
		else { // 그 외 
			opr2 = evalPop();  // opr2에 evalpop
			opr1 = evalPop(); // opr1에 evalpop
			switch(getToken(symbol)) { // 조건문 
			case plus: evalPush(opr1 + opr2); break; // plus일 경우 opr1 + opr2값 evalPush
			case minus: evalPush(opr1 - opr2); break;  // minus일 경우 opr1 - opr2값 evalPush
			case times: evalPush(opr1 * opr2); break;  // times일 경우 opr1 * opr2값 evalPush
			case divide: evalPush(opr1 / opr2); break;  // divide일 경우 opr1 / opr2값 evalPush
			default: break;
			}
		}
	}
	evalResult = evalPop(); // evalResult 에 evalpop값 넣음 
}

