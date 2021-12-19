#include <stdio.h>
#include<stdlib.h>   //随机数srand用到的头文件
#include<ctype.h>    //toascii()用到的头文件
#include<string.h>   //查找姓名时比较字符串用的头文件
#include<time.h>     //time用到的头文件
#define HASH_LEN 150
#define NAME_LEN 67
#define ppp 59

int k;
int d[60]; 

typedef struct //姓名表
{
    char *key;    //名字的拼音
    int m;        //拼音所对应的ASCII和
}NAME;

typedef struct //哈希表
{
    char *key;   //名字的拼音
    int m;       //拼音所对应的ASCII总和，即关键字
    int si;      //查找长度
}HASH;

NAME Name[HASH_LEN];        //全局定义姓名表,最大长度为50
HASH Hash[HASH_LEN];        //全局定义哈希表，最大长度为50

void InitName()   // 构建姓名表 
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

void CreateHash()  // 创建哈希表 
{
	//清空哈希表
	for (int i = 0; i < HASH_LEN; i ++ ) {
		Hash[i].key = "\0";
		Hash[i].m = 0;
		Hash[i].si = 0;
	}
	for (int i = 0; i < NAME_LEN; i ++ ) {
		int sum = 1;
		int adr = Name[i].m % ppp;
		// 若不冲突，则将姓名表赋给哈希表 
		if (Hash[adr].si == 0) {
			Hash[adr].key = Name[i].key;
			Hash[adr].m = Name[i].m;
			Hash[adr].si = 1; 
		}
		// 若冲突，用随机探测再散列法处理 
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

void DisplayName()    //显示姓名表
{
	printf("\n地址 \t\t 姓名 \t\t 关键字\n");
	for (int i = 0; i < NAME_LEN; i ++ )
		printf("%2d %18s \t\t  %d  \n",i,Name[i].key,Name[i].m);
}

void DisplayHash()   // 显示哈希表
{
	float asl=0.0;
    printf("\n\n 地址 \t\t 姓名 \t\t 关键字 \t 搜索长度\n"); //显示的格式
    for (int i = 0; i < HASH_LEN; i ++ )
   {
        printf("%2d %18s \t\t  %d \t\t  %d\n", i, Hash[i].key, Hash[i].m, Hash[i].si);
        asl += Hash[i].si;
   }
   asl /= NAME_LEN;    //求得ASL
   printf("\n\n平均查找长度：ASL(%d)=%f \n", NAME_LEN, asl);
}

void FindName()//查找
{
    char name[20]={0};
    int s = 0, sum = 1; 
    printf("\n请输入想要查找的姓名的拼音:");
    scanf("%s", name);
    getchar();
    for (int j = 0; j < 20; j ++ )//求出姓名的拼音所对应的ASCII作为关键字
        s+=toascii(name[j]);
    for (int i = 0; i < HASH_LEN; i ++ ) {
    	if (Hash[i].m == s) {
    		printf("\n姓名:%s   关键字:%d   地址:%d \n", Hash[i].key, Hash[i].m, i);
    		break;
		}
	}
}

void view()    //交互界面
{
    printf("=======================================================\n");
    printf("=                   人名哈希表                        =\n");
    printf("=  1: 打印姓名表                                      =\n");
    printf("=  2: 打印哈希表                                      =\n");
    printf("=  3: 查找                                            =\n");
    printf("=  4: 退出程序                                        =\n");
    printf("=======================================================\n");
}

int main()
{
	int a = 1;
	int choice;
    srand((int)time(0));//以当前时间对应的int值为随机序列起点，每次运行程序由于起点不同可以得到不同的随机数序列
	for(int i = 0; i < 60; i ++ )  //用随机函数求得伪随机数列d[i]（在1到60之间）
        d[i] = 1 + (int)(HASH_LEN*rand()/(RAND_MAX+1.0));
        
    InitName();                 //调用初始化姓名表函数
    CreateHash();               //调用创建哈希表函数
    view();                     //调用交互界面函数
    
    while (a)
    {
       printf("\n输入选项:");
       scanf("%d", &choice);
       getchar();
       switch(choice)
       {
           case 1: DisplayName(); break;                //打印姓名表
           case 2: DisplayHash(); break;                //打印哈希表
           case 3: FindName(); break;                   //调用查找函数
           case 4: a=0; break;                        //退出循环，终止程序
           default: printf("\n请输入正确的选择!\n"); break;
       }
    }
    return 0;
 } 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
