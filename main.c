#include <stdio.h>
#include <stdlib.h>

#define MAXSIZE 255

#define ERROR 0
#define OK 1
#define true 1
#define false 0

typedef int bool;


//定长存储
typedef struct {
	char ch[MAXSIZE + 1]; //下表为0的分量不用闲置，从下表为1开始存储串
	int length;
}SString,*PString;

//打印操作信息
void printMessage() {
	int i = 0;
	printf("\n");
	for (i = 0; i < 40; i++) {
		printf("*");
	}
	printf(" 串的顺序存储结构设计与实现 ");
	for (i = 0; i < 40; i++) {
		printf("*");
	}
	printf("\n");
}

//操作菜单
void operationMenu() {
	printMessage();
	printf("\n");
	printf("\t\t\t \033[40;31m请从键盘输入一个字符(0-8)完成相应操作，输入其他字符退出！\033[0m \n\n");
	printf("\t\t\t\t\t 0.清空字符串\n");
	printf("\t\t\t\t\t 1.拷贝字符串\n");
	printf("\t\t\t\t\t 2.字符串连接\n");
	printf("\t\t\t\t\t 3.比较字符串\n");
	printf("\t\t\t\t\t 4.用Sub返回串S的第pos个字符起长度为len的子串\n"); 
	printf("\t\t\t\t\t 5.主串S中第pos个字符之后存在与T相等的子串\n");
	printf("\t\t\t\t\t 6.在串S的第position个字符之前插入串T\n");
	printf("\t\t\t\t\t 7.从串S中删除第pos个字符起长度为length的字串\n");
	printf("\t\t\t\t\t 8.用V代替主串S中出现的所有与T相等的不重叠的子串\n");
	printMessage();
}

//输入一个字符串
void InputString(char ch[]) {
	printf("请输入一个字符串：");
	rewind(stdin);  //输入前清除缓存区
	gets(ch);
}

//打印串
void PrintString(SString S) {
	printf("输出串：");
	for (int i = 1; i <= S.length; i++)
		printf("%c",S.ch[i]);
	printf("\n");
}

//创建串
SString CreateString() {
	SString str;
	str.ch[0] = '\0';
	str.length = 0;
	return str;
}

//串的长度
int StringLength(SString S) {
	return S.length;
}

//是否为空串
bool IsEmptyString(SString S) {
	return S.length ? false : true;
}

//1、生成一个其值等于chars的串 （结果返回一个串）
SString StringAssign(char ch[]) {
	SString S = CreateString();
	for (int i = 0; ch[i] !='\0'; i++)
		S.ch[++S.length] = ch[i];
	return S;
}

//2、字符串的拷贝
SString StringCopy(SString T,SString S) {
	for (int i = 1; i <= StringLength(S); i++)
		T.ch[++T.length] = S.ch[i];
	return T;
}

//3、清空字符串
int ClearString(SString S) {
	if (IsEmptyString(S)) return ERROR;
	for (int i = 1; i<=S.length; i++)
		S.ch[i] = '\0';
	S.length = 0;
	return OK;
}

//4、连接字符串,将T字符串连接到S字符串中（返回一个新串）
SString ConcatString(SString S, SString T) {
	int sLength = StringLength(S), tLength = StringLength(T);
	if (sLength + tLength > MAXSIZE) return;
	for (int i = 1; i <= tLength; i++)
		S.ch[i + sLength] = T.ch[i];
	S.length = sLength + tLength;
	return S;
}

//5、字符串比较（S>T：1，S=T:0,S<T:-1）
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

//6、返回S字符串中pos字符起长度为len的子串(返回一个字符串)
SString SubString(SString S,int position,int length) {
	SString sub = CreateString();
	if ((position < 1 
		|| position > StringLength(S))
		||length < 0 
		|| length > StringLength(S) - position + 1)
	{
		printf("输入值不合法！！！\n");
		return;
	}
	for (int i = position, j = 1; i <= S.length && j<=length; i++, j++)//从position个开始截取
		sub.ch[j] = S.ch[i];
	sub.length = length;
	return sub;
}

//7、若主串S中第pos个字符之后存在与T相等的子串，则返回第一个这样的子串在S中的位置，否则返回0
int IndexString(SString S, SString T,int position) {  //BF算法
	if (position<1 || position>S.length) return 0;
	int i = position, j = 1;    
	while (i<= StringLength(S) && j <= StringLength(T)) {
		if (S.ch[i] == T.ch[j]) {
			i++;  
			j++;
		}else{   //指针回溯
			i = i - j + 2;  
			j = 1;
		}
	}
	if (j >T.length)return i - T.length; //返回位置
	else return 0;
}

//8、在串S的第position个字符之前插入串T
SString InsertString(SString S,SString T,int position) {
	if (position <= 0 || position >StringLength(S)) {
		printf("输入不合法！！！\n");
		return;
	}
	if (IsEmptyString(S) || IsEmptyString(T)) {
		printf("空串，无法插入！！！\n");
		return;
	}
	int sLength = StringLength(S), tLength = StringLength(T);
	if (sLength + tLength <= MAXSIZE) {
		for (int i = sLength; i >= position; i--)  //所有元素往后移tLength个位置
			S.ch[i + tLength] = S.ch[i];
		for (int i = position; i <=position+tLength-1;i++) //将T串插入到S空出来的位置
			S.ch[i] = T.ch[i-position+1];
	}
	S.length = sLength + tLength; 
	return S;
}

//9、从串S中删除第pos个字符起长度为length的字串
SString DeleteString(SString S,int position,int len) {
	int sLength = StringLength(S);
	if (position < 0 || position >sLength ||len<0 || len>sLength) {
		printf("输入不合法！！！\n");
		return;
	}
	for (int i = position + len; i <= sLength; i++)
		S.ch[i - len] = S.ch[i];
	S.length = sLength - len;
	return S;
}
// 10、用V代替主串S中出现的所有与T相等的不重叠的子串
SString ReplaceString(SString S, SString T, SString V) {
	if (IsEmptyString(V)) {
		printf("字符串为空串！！！\n");
		return;
	}
	int currentPosition = IndexString(S, T, 1); //查找S与T字符相等的字符返回第一个字符的位置
	if (currentPosition != 0) {
	S=DeleteString(S, currentPosition, StringLength(T)); //删除第currentPosition个位置起长度为T.length的字符串
    S=InsertString(S, V, currentPosition); //从currentPosition个位置开始插入V字符串到S中
	}
	return S;
}


int main() {
	int flag = 1;
	char code;
	operationMenu();
	while (flag == 1) {
		printf("你选择的操作是：");
		rewind(stdin);  //清除缓存区
		code = getchar();
		switch (code) {
		case '0':
		{
			char ch[] = "";
			InputString(ch);
			SString S = StringAssign(ch);
			printf("返回值（成功：1，失败：0）：%d\n", ClearString(S));
			break;
		}
		case '1': 
		{
			char ch[] = "";
			InputString(ch);
			SString S = CreateString();
			SString T = StringAssign(ch);
			printf("拷贝成功！！！\n");
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
			printf("返回值（S>T：1，S=T:0,S<T:-1）：%d\n", StringCompare(S,T));
			break;
		}
		case '4':
		{
			char ch[] = "";
			int pos = 0, len = 0;
			InputString(ch);
			SString S = StringAssign(ch);
			printf("请输入起始位置：");
			scanf_s("%d", &pos);
			printf("请输入截取长度：");
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
			printf("请输入起始位置：");
			scanf_s("%d", &pos);
			printf("串S中第i个字符之后存在与T相等的串返回第一个这样的子串在S中的位置，否则返回0：%d\n", IndexString(S,T,pos));
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
			printf("请输入起始位置：");
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
			printf("请输入起始位置：");
			scanf_s("%d", &pos);
			printf("请输入删除的个数：");
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
		default:printf("你选择退出程序，欢迎下次光临！");
			flag = 0;
		}
	}
	system("pause");
	return 0;
}