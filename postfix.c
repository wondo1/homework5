#include<stdio.h>
#include<stdlib.h>
#include<ctype.h>
#include<string.h>

#define MAX_STACK_SIZE 10 // ���� �ִ밪 ���� 
#define MAX_EXPRESSION_SIZE 20 // MAX_EXPRESSION_SIZE �ִ밪 ���� 

/* stack ������ �켱������ ��������, lparen = 0 ���� ���� */
typedef enum{ 
	lparen = 0,  /* ( ���� ��ȣ */
	rparen = 9,  /* ) ������ ��ȣ*/
	times = 7,   /* * ���� */
	divide = 6,  /* / ������ */
	plus = 5,    /* + ���� */
	minus = 4,   /* - ���� */
	operand = 1 /* �ǿ����� */
} precedence;

char infixExp[MAX_EXPRESSION_SIZE]; // ������ infixExp�迭 ����, ����
char postfixExp[MAX_EXPRESSION_SIZE]; // ������ postfixExp �迭 ����, ���� 
char postfixStack[MAX_STACK_SIZE]; // ������ postfixStack �迭 ����, ��������
int evalStack[MAX_STACK_SIZE]; // ������ evalStack �迭 ����, ����

int postfixStackTop = -1; // postfixStackTop �� -1
int evalStackTop = -1; // evalStackTop �� -1

int evalResult = 0; // evalResult �� 0

void postfixPush(char x); // ���ÿ� ���� �Լ� 
char postfixPop(); // ���ÿ��� �����ϴ� �Լ� 
void evalPush(int x); // ��꽺�ÿ� �ִ� �Լ� 
int evalPop(); // ��� ���ÿ��� ���� �Լ� 
void getInfix(); // ����ǥ��� �Լ� 
precedence getToken(char symbol); // symbol�� ��ȯ �Լ� 
precedence getPriority(char x); // x�� ��ȯ �Լ� 
void charCat(char* c); // ���� ���� �Լ� 
void toPostfix(); //  postix ���� �Լ� 
void debug(); // denug �Լ� 
void reset(); // �ʱ�ȭ �Լ� 
void evaluation(); // ��� �Լ� 

int main()
{
	char command; // ������ �Լ� ���� 
	printf("[----- [�����] [2018038099] -----]");
	
	do{ // �ݺ��� 
		printf("----------------------------------------------------------------\n");
		printf("               Infix to Postfix, then Evaluation               \n");
		printf("----------------------------------------------------------------\n");
		printf(" Infix=i,   Postfix=p,  Eval=e,   Debug=d,   Reset=r,   Quit=q \n");
		printf("----------------------------------------------------------------\n");

		printf("Command = ");
		scanf(" %c", &command); // ������ ���� �Է� ����

		switch(command) { // ���ǹ�
		case 'i': case 'I': // i, I �� ������
			getInfix();
			break; // ����
		case 'p': case 'P': // p, P ������
			toPostfix();
			break; // ����
		case 'e': case 'E': // e, E ������ 
			evaluation();
			break; // ����
		case 'd': case 'D': // d, D ������
			debug();
			break; // ����
		case 'r': case 'R': // r, R ������
			reset();
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

void postfixPush(char x) // postfixPush �Լ� ���� 
{
    postfixStack[++postfixStackTop] = x; // postfixStack�� ++�� postfixStackTop���� x�� ���� 
}

char postfixPop() // postfixPop �Լ� ���� 
{
	char x; // ������ ���� ���� 
    if(postfixStackTop == -1) // postfixStackTop���� -1�� ������
        return '\0'; //  \0 �� ��ȯ
    else { // �� �� ��� 
    	x = postfixStack[postfixStackTop--]; //postfixStack[postfixStackTop--]�� x�� ���� 
    }
    return x; // x�� ��ȯ 
}

void evalPush(int x) // evalPush �Լ� ���� 
{
    evalStack[++evalStackTop] = x; // evalstack�� ++evalStackTop ���� x�� ���� 
}

int evalPop() // evalPop �Լ� ���� 
{
    if(evalStackTop == -1) // ���� eval����ž�� -1�� ������ 
        return -1; // -1�� ��ȯ
    else // �� ��
        return evalStack[evalStackTop--]; // evalStack[evalStackTop--]�� ��ȯ 
}

/**
 * infix expression�� �Է¹޴´�.
 * infixExp���� �Էµ� ���� �����Ѵ�.
 */

void getInfix() // getInfix �Լ� ���� 
{
    printf("Type the expression >>> ");
    scanf("%s",infixExp); // infixExp �� �Է� ���� 
}

precedence getToken(char symbol) // �Է� ��Ʈ������ ��ū�� �������� �Լ�  
{
	switch(symbol) { // ���ǹ� 
	case '(' : return lparen; // ( �Է½� lparen ��ȯ
	case ')' : return rparen; // ) �Է½� rparen ��ȯ
	case '+' : return plus; // + �Է½� plus ��ȯ
	case '-' : return minus; // - �Է½� minus ��ȯ 
	case '/' : return divide; // / �Է½� divide ��ȯ 
	case '*' : return times; // * �Է½� times ��ȯ 
	default : return operand; // operand �� ��ȯ
	}
}

precedence getPriority(char x) // getPriority �Լ� ���� 
{
	return getToken(x); // ��ū x�� ��ȯ
}

/**
 * �����ϳ��� ���޹޾�, postfixExp�� �߰�
 */
void charCat(char* c) // charCat �Լ� ����
{
	if (postfixExp == '\0') // postfixExp ���� ���ٸ� 
		strncpy(postfixExp, c, 1); // c���ڸ� postfixExp�� ���� 1�� ��ŭ 
	else // �� �� 
		strncat(postfixExp, c, 1); // c���ڸ� postfixExp�� ���� 1�� ��ŭ 
}

/**
 * infixExp�� ���ڸ� �ϳ��� �о�鼭 stack�� �̿��Ͽ� postfix�� �����Ѵ�.
 * ����� postfix�� postFixExp�� ����ȴ�.
 */
void toPostfix() // toPostfix �Լ� ���� 
{
	/* infixExp�� ���� �ϳ����� �б����� ������ */
	char *exp = infixExp;
	char x; /* �����ϳ��� �ӽ÷� �����ϱ� ���� ���� */

	/* exp�� �������Ѱ��鼭, ���ڸ� �а� postfix�� ���� */
	while(*exp != '\0') // �ݺ��� 
	{
		if(getPriority(*exp) == operand) // 
		{
			x = *exp; // x�� *exp �� ���� 
        	charCat(&x); // charCat�Լ��� &x�� ���� 
		}
        else if(getPriority(*exp) == lparen) { //  ( �� ���� ��� 

        	postfixPush(*exp); // postfixPush �Լ��� *exp�� ����
        }
        else if(getPriority(*exp) == rparen) // ) �� ���� ��� 
        {
        	while((x = postfixPop()) != '(') { // x�� postfixPop()���� (�� ���� �ʴٸ�
        		charCat(&x);  // charCat�Լ��� &x�� ���� 
        	}
        }
        else
        {
            while(getPriority(postfixStack[postfixStackTop]) >= getPriority(*exp)) // ���� ž�� getPriority(*exp)�� ���ų� ū��� 
            {
            	x = postfixPop(); // x�� postfixPop �� ���� 
            	charCat(&x);  // charCat�Լ��� &x�� ���� 
            }
            postfixPush(*exp);  // postfixPush �Լ��� *exp�� ����
        }
        exp++; // exp ���� 
	}

    while(postfixStackTop != -1) // ���� ž�� -1�� �ƴϸ�
    {
    	x = postfixPop(); // x�� postfixPop �� ����
    	charCat(&x); // 
    }

}

void debug() // debug �Լ� ���� 
{
	printf("\n---DEBUG\n");
	printf("infixExp =  %s\n", infixExp);
	printf("postExp =  %s\n", postfixExp);
	printf("eval result = %d\n", evalResult);

	printf("postfixStack : ");
	for(int i = 0; i < MAX_STACK_SIZE; i++) // i�� 0 ���� �ƽ� ������ ��ŭ �ݺ�
		printf("%c  ", postfixStack[i]); // postfixStack[i] �迭 ��� 

	printf("\n");

}

void reset() // reset �Լ� ���� 
{
	infixExp[0] = '\0'; // infixExp[0]�� \0 ���� 
	postfixExp[0] = '\0'; // postfixExp[0] \0 �� ����

	for(int i = 0; i < MAX_STACK_SIZE; i++) // i�� 0 ���� �ƽ� ������ ��ŭ �ݺ� 
		postfixStack[i] = '\0'; // postfixStack[i]�� \0�� ���� 
         
	postfixStackTop = -1; // -1 �� ����
	evalStackTop = -1; // -1 �� ���� 
	evalResult = 0; // 0 �� ���� 
}
void evaluation() // evaluation �Լ� ���� 
{
	int opr1, opr2, i; // ������ ���� 3�� ����

	int length = strlen(postfixExp); // length�� strlen(postfixExp)���� 
	char symbol; // ������ ���� ���� 
	evalStackTop = -1; // -1 �� ���� 

	for(i = 0; i < length; i++) // length ��ŭ �ݺ�
	{
		symbol = postfixExp[i]; // symbol�� postfixExp[i]�� ���� 
		if(getToken(symbol) == operand) { // ���� ��ū �ɺ� ���� operand�� ���ٸ�
			evalPush(symbol - '0'); //symbol - '0'�� ���� 
		}
		else { // �� �� 
			opr2 = evalPop();  // opr2�� evalpop
			opr1 = evalPop(); // opr1�� evalpop
			switch(getToken(symbol)) { // ���ǹ� 
			case plus: evalPush(opr1 + opr2); break; // plus�� ��� opr1 + opr2�� evalPush
			case minus: evalPush(opr1 - opr2); break;  // minus�� ��� opr1 - opr2�� evalPush
			case times: evalPush(opr1 * opr2); break;  // times�� ��� opr1 * opr2�� evalPush
			case divide: evalPush(opr1 / opr2); break;  // divide�� ��� opr1 / opr2�� evalPush
			default: break;
			}
		}
	}
	evalResult = evalPop(); // evalResult �� evalpop�� ���� 
}

