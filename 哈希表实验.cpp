#include <stdio.h>
#include<stdlib.h>   //�����srand�õ���ͷ�ļ�
#include<ctype.h>    //toascii()�õ���ͷ�ļ�
#include<string.h>   //��������ʱ�Ƚ��ַ����õ�ͷ�ļ�
#include<time.h>     //time�õ���ͷ�ļ�
#define HASH_LEN 150
#define NAME_LEN 67
#define ppp 59

int k;
int d[60]; 

typedef struct //������
{
    char *key;    //���ֵ�ƴ��
    int m;        //ƴ������Ӧ��ASCII��
}NAME;

typedef struct //��ϣ��
{
    char *key;   //���ֵ�ƴ��
    int m;       //ƴ������Ӧ��ASCII�ܺͣ����ؼ���
    int si;      //���ҳ���
}HASH;

NAME Name[HASH_LEN];        //ȫ�ֶ���������,��󳤶�Ϊ50
HASH Hash[HASH_LEN];        //ȫ�ֶ����ϣ����󳤶�Ϊ50

void InitName()   // ���������� 
{
	Name[0].key="sunyao";
    Name[1].key="shijiayi";
    Name[2].key="lixingriu";
    Name[3].key="xuwenqi";
    Name[4].key="guanjiale";
    Name[5].key="liuxue";
    Name[6].key="changsijia";
    Name[7].key="songyazheng";
    Name[8].key="wangaiwen";
    Name[9].key="mazhibo";
    Name[10].key="xizeeng";
    Name[11].key="tangyuzhou";
    Name[12].key="xiaochaoyan";
    Name[13].key="zhangyibo";
    Name[14].key="lanpengli";
    Name[15].key="zhangkeqiang";
    Name[16].key="zhaoyongheng";
    Name[17].key="liuyuhan";
    Name[18].key="wangchongguang";
    Name[19].key="lishihao";
    Name[20].key="gongtaian";
    Name[21].key="huijunjie";
    Name[22].key="huguanjun";
    Name[23].key="liuhaoxin";
    Name[24].key="wanghaonan";
    Name[25].key="zhangsike";
    Name[26].key="liushuhang";
    Name[27].key="xueyunqing";
    Name[28].key="zhaopeng";
    Name[29].key="chengfuming";
    Name[30].key="jiangyishang";
    Name[31].key="zhangzuhao";
    Name[32].key="zhangyuhan";
    Name[33].key="jinriuxi";
    Name[34].key="zhaoning";
    Name[35].key="tangmiao";
    Name[36].key="xiaoyujun";
    Name[37].key="hanjing";
    Name[38].key="liuzhixin";
    Name[39].key="libeining";
    Name[40].key="fengshihao";
    Name[41].key="dingyue";
    Name[42].key="xuhaizhou";
    Name[43].key="zhufangyuan";
    Name[44].key="lisiqi";
    Name[45].key="xianglei";
	Name[46].key="lijianhao";
	Name[47].key="zhangpengtao";
	Name[48].key="lixiao";
	Name[49].key="dingkunyu";
	Name[50].key="wangyifang";
	Name[51].key="xujiahao";
	Name[52].key="yansihan";
	Name[53].key="renzheng";
	Name[54].key="lizongbin";
	Name[55].key="yumenghao";
	Name[56].key="liuheng";
	Name[57].key="gaojunjie";
	Name[58].key="kangzijun";
	Name[59].key="pengrunhao";
	Name[60].key="zhangmingtao";
	Name[61].key="hanyutong";
	Name[62].key="wangyuxuan";
	Name[63].key="lixinyi";
	Name[64].key="yangjirui";
	Name[65].key="gaojiayan";
	Name[66].key="kangboao";
	
	for (int i = 0; i < NAME_LEN; i ++ ) {
		int s = 0;
		char *p = Name[i].key;
		for (int j = 0; *(p+j) != '\0'; j ++ ) {
			s += toascii( *(p+j) );
			Name[i].m = s;
		}
	}
	
}

void CreateHash()  // ������ϣ�� 
{
	//��չ�ϣ��
	for (int i = 0; i < HASH_LEN; i ++ ) {
		Hash[i].key = "\0";
		Hash[i].m = 0;
		Hash[i].si = 0;
	}
	for (int i = 0; i < NAME_LEN; i ++ ) {
		int sum = 1;
		int adr = Name[i].m % ppp;
		// ������ͻ��������������ϣ�� 
		if (Hash[adr].si == 0) {
			Hash[adr].key = Name[i].key;
			Hash[adr].m = Name[i].m;
			Hash[adr].si = 1; 
		}
		// ����ͻ�������̽����ɢ�з����� 
		else {
			adr = (adr + d[k++]) % HASH_LEN;
			sum ++;
			if (Hash[adr].si == 0) {
				Hash[adr].key = Name[i].key;
				Hash[adr].m = Name[i].m;
				Hash[adr].si = 1; 				
			}
		} 
	}
	
}

void DisplayName()    //��ʾ������
{
	printf("\n��ַ \t\t ���� \t\t �ؼ���\n");
	for (int i = 0; i < NAME_LEN; i ++ )
		printf("%2d %18s \t\t  %d  \n",i,Name[i].key,Name[i].m);
}

void DisplayHash()   // ��ʾ��ϣ��
{
	float asl=0.0;
    printf("\n\n ��ַ \t\t ���� \t\t �ؼ��� \t ��������\n"); //��ʾ�ĸ�ʽ
    for (int i = 0; i < HASH_LEN; i ++ )
   {
        printf("%2d %18s \t\t  %d \t\t  %d\n", i, Hash[i].key, Hash[i].m, Hash[i].si);
        asl += Hash[i].si;
   }
   asl /= NAME_LEN;    //���ASL
   printf("\n\nƽ�����ҳ��ȣ�ASL(%d)=%f \n", NAME_LEN, asl);
}

void FindName()//����
{
    char name[20]={0};
    int s = 0, sum = 1; 
    printf("\n��������Ҫ���ҵ�������ƴ��:");
    scanf("%s", name);
    getchar();
    for (int j = 0; j < 20; j ++ )//���������ƴ������Ӧ��ASCII��Ϊ�ؼ���
        s+=toascii(name[j]);
    for (int i = 0; i < HASH_LEN; i ++ ) {
    	if (Hash[i].m == s) {
    		printf("\n����:%s   �ؼ���:%d   ��ַ:%d \n", Hash[i].key, Hash[i].m, i);
    		break;
		}
	}
}

void view()    //��������
{
    printf("=======================================================\n");
    printf("=                   ������ϣ��                        =\n");
    printf("=  1: ��ӡ������                                      =\n");
    printf("=  2: ��ӡ��ϣ��                                      =\n");
    printf("=  3: ����                                            =\n");
    printf("=  4: �˳�����                                        =\n");
    printf("=======================================================\n");
}

int main()
{
	int a = 1;
	int choice;
    srand((int)time(0));//�Ե�ǰʱ���Ӧ��intֵΪ���������㣬ÿ�����г���������㲻ͬ���Եõ���ͬ�����������
	for(int i = 0; i < 60; i ++ )  //������������α�������d[i]����1��60֮�䣩
        d[i] = 1 + (int)(HASH_LEN*rand()/(RAND_MAX+1.0));
        
    InitName();                 //���ó�ʼ����������
    CreateHash();               //���ô�����ϣ����
    view();                     //���ý������溯��
    
    while (a)
    {
       printf("\n����ѡ��:");
       scanf("%d", &choice);
       getchar();
       switch(choice)
       {
           case 1: DisplayName(); break;                //��ӡ������
           case 2: DisplayHash(); break;                //��ӡ��ϣ��
           case 3: FindName(); break;                   //���ò��Һ���
           case 4: a=0; break;                        //�˳�ѭ������ֹ����
           default: printf("\n��������ȷ��ѡ��!\n"); break;
       }
    }
    return 0;
 } 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
