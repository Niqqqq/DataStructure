#include <stdio.h>
#include <stdlib.h>

#define MAXSIZE 255

#define ERROR 0
#define OK 1
#define true 1
#define false 0

typedef int bool;


//�����洢
typedef struct {
	char ch[MAXSIZE + 1]; //�±�Ϊ0�ķ����������ã����±�Ϊ1��ʼ�洢��
	int length;
}SString,*PString;

//��ӡ������Ϣ
void printMessage() {
	int i = 0;
	printf("\n");
	for (i = 0; i < 40; i++) {
		printf("*");
	}
	printf(" ����˳��洢�ṹ�����ʵ�� ");
	for (i = 0; i < 40; i++) {
		printf("*");
	}
	printf("\n");
}

//�����˵�
void operationMenu() {
	printMessage();
	printf("\n");
	printf("\t\t\t \033[40;31m��Ӽ�������һ���ַ�(0-8)�����Ӧ���������������ַ��˳���\033[0m \n\n");
	printf("\t\t\t\t\t 0.����ַ���\n");
	printf("\t\t\t\t\t 1.�����ַ���\n");
	printf("\t\t\t\t\t 2.�ַ�������\n");
	printf("\t\t\t\t\t 3.�Ƚ��ַ���\n");
	printf("\t\t\t\t\t 4.��Sub���ش�S�ĵ�pos���ַ��𳤶�Ϊlen���Ӵ�\n"); 
	printf("\t\t\t\t\t 5.����S�е�pos���ַ�֮�������T��ȵ��Ӵ�\n");
	printf("\t\t\t\t\t 6.�ڴ�S�ĵ�position���ַ�֮ǰ���봮T\n");
	printf("\t\t\t\t\t 7.�Ӵ�S��ɾ����pos���ַ��𳤶�Ϊlength���ִ�\n");
	printf("\t\t\t\t\t 8.��V��������S�г��ֵ�������T��ȵĲ��ص����Ӵ�\n");
	printMessage();
}

//����һ���ַ���
void InputString(char ch[]) {
	printf("������һ���ַ�����");
	rewind(stdin);  //����ǰ���������
	gets(ch);
}

//��ӡ��
void PrintString(SString S) {
	printf("�������");
	for (int i = 1; i <= S.length; i++)
		printf("%c",S.ch[i]);
	printf("\n");
}

//������
SString CreateString() {
	SString str;
	str.ch[0] = '\0';
	str.length = 0;
	return str;
}

//���ĳ���
int StringLength(SString S) {
	return S.length;
}

//�Ƿ�Ϊ�մ�
bool IsEmptyString(SString S) {
	return S.length ? false : true;
}

//1������һ����ֵ����chars�Ĵ� ���������һ������
SString StringAssign(char ch[]) {
	SString S = CreateString();
	for (int i = 0; ch[i] !='\0'; i++)
		S.ch[++S.length] = ch[i];
	return S;
}

//2���ַ����Ŀ���
SString StringCopy(SString T,SString S) {
	for (int i = 1; i <= StringLength(S); i++)
		T.ch[++T.length] = S.ch[i];
	return T;
}

//3������ַ���
int ClearString(SString S) {
	if (IsEmptyString(S)) return ERROR;
	for (int i = 1; i<=S.length; i++)
		S.ch[i] = '\0';
	S.length = 0;
	return OK;
}

//4�������ַ���,��T�ַ������ӵ�S�ַ����У�����һ���´���
SString ConcatString(SString S, SString T) {
	int sLength = StringLength(S), tLength = StringLength(T);
	if (sLength + tLength > MAXSIZE) return;
	for (int i = 1; i <= tLength; i++)
		S.ch[i + sLength] = T.ch[i];
	S.length = sLength + tLength;
	return S;
}

//5���ַ����Ƚϣ�S>T��1��S=T:0,S<T:-1��
int StringCompare(SString S,SString T) {
	if (IsEmptyString(S) || IsEmptyString(S)) return -2;
	int i = 1;
	while (i<S.length && i<T.length)
	{
		if ((int)S.ch[i] > (int)T.ch[i]) return 1; //S>T:1
		if ((int)S.ch[i] < (int)T.ch[i]) return -1; //S<T:-1
		if ((int)S.ch[i] == (int)T.ch[i]) {
			i++;
			continue;
		}
		i++;
	}
	if (i == S.length && i != T.length) return -1;
	if (i != S.length && i == T.length) return 1;
	if (i == S.length && i == T.length) return 0;  //S==T
}

//6������S�ַ�����pos�ַ��𳤶�Ϊlen���Ӵ�(����һ���ַ���)
SString SubString(SString S,int position,int length) {
	SString sub = CreateString();
	if ((position < 1 
		|| position > StringLength(S))
		||length < 0 
		|| length > StringLength(S) - position + 1)
	{
		printf("����ֵ���Ϸ�������\n");
		return;
	}
	for (int i = position, j = 1; i <= S.length && j<=length; i++, j++)//��position����ʼ��ȡ
		sub.ch[j] = S.ch[i];
	sub.length = length;
	return sub;
}

//7��������S�е�pos���ַ�֮�������T��ȵ��Ӵ����򷵻ص�һ���������Ӵ���S�е�λ�ã����򷵻�0
int IndexString(SString S, SString T,int position) {  //BF�㷨
	if (position<1 || position>S.length) return 0;
	int i = position, j = 1;    
	while (i<= StringLength(S) && j <= StringLength(T)) {
		if (S.ch[i] == T.ch[j]) {
			i++;  
			j++;
		}else{   //ָ�����
			i = i - j + 2;  
			j = 1;
		}
	}
	if (j >T.length)return i - T.length; //����λ��
	else return 0;
}

//8���ڴ�S�ĵ�position���ַ�֮ǰ���봮T
SString InsertString(SString S,SString T,int position) {
	if (position <= 0 || position >StringLength(S)) {
		printf("���벻�Ϸ�������\n");
		return;
	}
	if (IsEmptyString(S) || IsEmptyString(T)) {
		printf("�մ����޷����룡����\n");
		return;
	}
	int sLength = StringLength(S), tLength = StringLength(T);
	if (sLength + tLength <= MAXSIZE) {
		for (int i = sLength; i >= position; i--)  //����Ԫ��������tLength��λ��
			S.ch[i + tLength] = S.ch[i];
		for (int i = position; i <=position+tLength-1;i++) //��T�����뵽S�ճ�����λ��
			S.ch[i] = T.ch[i-position+1];
	}
	S.length = sLength + tLength; 
	return S;
}

//9���Ӵ�S��ɾ����pos���ַ��𳤶�Ϊlength���ִ�
SString DeleteString(SString S,int position,int len) {
	int sLength = StringLength(S);
	if (position < 0 || position >sLength ||len<0 || len>sLength) {
		printf("���벻�Ϸ�������\n");
		return;
	}
	for (int i = position + len; i <= sLength; i++)
		S.ch[i - len] = S.ch[i];
	S.length = sLength - len;
	return S;
}
// 10����V��������S�г��ֵ�������T��ȵĲ��ص����Ӵ�
SString ReplaceString(SString S, SString T, SString V) {
	if (IsEmptyString(V)) {
		printf("�ַ���Ϊ�մ�������\n");
		return;
	}
	int currentPosition = IndexString(S, T, 1); //����S��T�ַ���ȵ��ַ����ص�һ���ַ���λ��
	if (currentPosition != 0) {
	S=DeleteString(S, currentPosition, StringLength(T)); //ɾ����currentPosition��λ���𳤶�ΪT.length���ַ���
    S=InsertString(S, V, currentPosition); //��currentPosition��λ�ÿ�ʼ����V�ַ�����S��
	}
	return S;
}


int main() {
	int flag = 1;
	char code;
	operationMenu();
	while (flag == 1) {
		printf("��ѡ��Ĳ����ǣ�");
		rewind(stdin);  //���������
		code = getchar();
		switch (code) {
		case '0':
		{
			char ch[] = "";
			InputString(ch);
			SString S = StringAssign(ch);
			printf("����ֵ���ɹ���1��ʧ�ܣ�0����%d\n", ClearString(S));
			break;
		}
		case '1': 
		{
			char ch[] = "";
			InputString(ch);
			SString S = CreateString();
			SString T = StringAssign(ch);
			printf("�����ɹ�������\n");
			PrintString(StringCopy(S,T));
			break;
		}
		case '2':
		{
			char ch1[] = "";
			char ch2[] = "";
			InputString(ch1);
			InputString(ch2);
			SString S = StringAssign(ch1);
			SString T = StringAssign(ch2);
			PrintString(ConcatString(S,T));
			break;
		}
		case '3':
		{
			char ch1[] = "";
			char ch2[] = "";
			InputString(ch1);
			InputString(ch2);
			SString S = StringAssign(ch1);
			SString T = StringAssign(ch2);
			printf("����ֵ��S>T��1��S=T:0,S<T:-1����%d\n", StringCompare(S,T));
			break;
		}
		case '4':
		{
			char ch[] = "";
			int pos = 0, len = 0;
			InputString(ch);
			SString S = StringAssign(ch);
			printf("��������ʼλ�ã�");
			scanf_s("%d", &pos);
			printf("�������ȡ���ȣ�");
			scanf_s("%d", &len);
			PrintString(SubString(S, pos, len));
			break;
		}
		case '5':
		{
			char ch1[] = "";
			char ch2[] = "";
			int pos = 0;
			InputString(ch1);
			InputString(ch2);
			SString S = StringAssign(ch1);
			SString T = StringAssign(ch2);
			printf("��������ʼλ�ã�");
			scanf_s("%d", &pos);
			printf("��S�е�i���ַ�֮�������T��ȵĴ����ص�һ���������Ӵ���S�е�λ�ã����򷵻�0��%d\n", IndexString(S,T,pos));
			break;
		}
		case '6':
		{
			char ch1[] = "";
			char ch2[] = "";
			int pos = 0;
			InputString(ch1);
			InputString(ch2);
			SString S = StringAssign(ch1);
			SString T = StringAssign(ch2);
			printf("��������ʼλ�ã�");
			scanf_s("%d", &pos);
			PrintString(InsertString(S,T,pos));
			break;
		}
		case '7':
		{
			char ch[] = "";
			int pos = 0, len = 0;
			InputString(ch);
			SString S = StringAssign(ch);
			printf("��������ʼλ�ã�");
			scanf_s("%d", &pos);
			printf("������ɾ���ĸ�����");
			scanf_s("%d", &len);
			PrintString(DeleteString(S, pos, len));
			break;
		}
		case '8':
		{
			char ch1[] = "";
			char ch2[] = "";
			char ch3[] = "";
			InputString(ch1);
			InputString(ch2);
			InputString(ch3);
			SString S = StringAssign(ch1);
			SString T = StringAssign(ch2);
			SString V = StringAssign(ch3);
			PrintString(ReplaceString(S, T, V));
			break;
		}
		default:printf("��ѡ���˳����򣬻�ӭ�´ι��٣�");
			flag = 0;
		}
	}
	system("pause");
	return 0;
}