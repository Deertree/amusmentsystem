#include<iostream>
#include<malloc.h>
#include<string.h>
#include<stdio.h>
#include<iomanip>
#include<fstream>
#include<string>
#define MAX 20
#define INFINITY 32767
using namespace std;

typedef struct Graph
{
	int vertex[MAX];//景点编号
	char name[MAX][1000];//景点名称
	char introduce[MAX][1000];//景点介绍
	int side[MAX][MAX];//边矩阵
	int n,v;//顶点数，边数
	bool c;
}Graph,*gLink;
int LocateVex(gLink &G, int v)//锁定顶点；
{
	int i;
	for (i = 0; i < G->n; i++)
	{
		if (G->vertex[i] == v )
			return i;

	}
	return -1;
}

void Show(gLink g)
{
    int i,j;
    for(i=0;i<g->n;i++)
    {
        cout<<"景区编号："<<g->vertex[i]<<"   "<<"景点名称："<<g->name[i]<<"   "<<"景点介绍："<<g->introduce[i]<<endl;
    }
	cout<<"邻接矩阵为："<<endl;
	for(i=0;i<g->n;i++)
	{
		for(j=0;j<g->n;j++)
		{
			cout<<left<<setw(8)<<g->side[i][j];
		}
		cout<<endl;
	}
}

void createGraph(gLink g)//读文件创建图
{
	int i,j;
	for(i=0;i<MAX;i++)
	{
		for(j=0;j<MAX;j++)
		{
			g->side[i][j]=0;
		}
	}
	fstream file("G:\\数据结构课程设计\\Vex.txt");
	file>>g->n;
	for(i=0;i<g->n;i++)
	{
		file>>g->vertex[i];
		file>>g->name[i];
		file>>g->introduce[i];

	}
	file.close();
	ifstream file1("G:\\数据结构课程设计\\Edge.txt");
	file1>>g->v;
	int a,b;
	int ai,aj;
	for(i=0;i<g->v;i++)
	{
		file1>>a>>b;
		ai=LocateVex(g,a);
		aj=LocateVex(g,b);
		file1>>g->side[ai][aj];
		g->side[aj][ai]=g->side[ai][aj];
	}
	for(i=0;i<g->n;i++)
	{
		for(j=0;j<g->n;j++)
		{
			if(g->side[i][j]==0)
			{
				g->side[i][j]=INFINITY;
			}
		}
	}
	file1.close();
	g->c=true;
	cout<<"创建完成！"<<endl;
	Show(g);
}



void select(gLink g)//查询景点
{
	int x;
	cout<<"输入想要查询的景点编号"<<endl;
	cin>>x;
	cout<<"该景点名为："<<g->name[x]<<"   "<<"景点介绍："<<g->introduce[x]<<endl;
	int j;
	cout<<"与"<<g->name[x]<<"相邻的景区有："<<endl;
	for(j=0;j<g->n;j++)
	{
		if(g->side[x][j]!=INFINITY&&g->side[j][x]!=INFINITY)
		{
			cout<<g->name[j]<<"与"<<g->name[x]<<"相距"<<g->side[x][j]<<"米远"<<endl;
		}
	}

}

int visit[MAX][MAX]={0};//记录游览路线
int DFS[MAX];//记录已游览景点编号
void navigation(gLink g,int index,int temp)//旅游景点导航,index为起点，temp为指针
{
    DFS[temp]=index;
    if(temp)
    {
        int index1=DFS[temp-1];
        visit[index][index1]=1;
        visit[index1][index]=1;
    }

    if(temp==g->n-1)//如果已经游览完，输出游览路线
    {
        for(int i=0;i<temp;i++)
            cout<<g->name[DFS[i]]<<"-->";
        cout<<g->name[DFS[temp]]<<endl;
    }

    else{

        for(int m=0;m<g->n;m++)
        {
            bool notnew=false;
            for(int j=0;j<temp+1;j++)
            {
                if(m==DFS[j])//若m在DFS中，则m已被游览过，否则，m还未被游览。
                    notnew=true;
            }
            if(g->side[index][m]!=INFINITY&&visit[index][m]!=1&&visit[m][index]!=1&&notnew!=true)//当m与上一个游览过的节点之间有路且这条路没有被走过且m未被游览过。
            {

                navigation(g,m,temp+1);
            }

        }

    }
     for(int i=0;i<g->n;i++)//重置visited
     {
               visit[i][index]=0;
               visit[index][i]=0;
     }


}

void shortestpath(gLink g)//搜索最短路径
{
	int i,j,x;
	cout<<"请输入起点与终点的编号："<<endl;
	cin>>i>>j;
	int num;
	num=g->side[i][j];
	cout<<"最短路径为："<<g->name[i];
	for(x=0;x<g->n;x++)
	{
		if(g->side[i][x]+g->side[x][j]<num)
		{
			num=g->side[i][x]+g->side[x][j];
			cout<<g->name[x];
		}
	}
	cout<<g->name[j]<<"总长为"<<num<<"米"<<endl;
}

void prim(gLink g)//铺设电路规划
{
	int length=0;
	int v;
	cout<<"请输入铺设电路的起点：";
	cin>>v;
	int lowcost[MAX];
	int min;
	int closest[MAX],i,j,k;
	for(i=0;i<g->n;i++)
	{
		lowcost[i]=g->side[v][i];
		closest[i]=v;
	}
	lowcost[v]=0;
	for(i=1;i<g->n;i++)
	{
		min=INFINITY;
		for(j=0;j<g->n;j++)
		{
			if(lowcost[j]!=0&&lowcost[j]<min)
			{
				min=lowcost[j];
				k=j;
			}
		}
		cout<<"从"<<g->name[closest[k]]<<"到"<<g->name[k]<<"修一条路，长为"<<g->side[closest[k]][k]<<"米"<<endl;
		length=length+g->side[closest[k]][k];
		lowcost[k]=0;
		for(j=0;j<g->n;j++)
		{
			if(g->side[k][j]!=INFINITY&&g->side[k][j]<lowcost[j])
			{
				lowcost[j]=g->side[k][j];
				closest[j]=k;
			}
		}
	}
	cout<<"总长："<<length<<"米"<<endl;
}
//修改图
void insertver(gLink g)//插入顶点
{
	int v,i;
	char na[1000];
	char intro[1000];
	cout<<"请输入您要插入顶点的编号名称与介绍："<<endl;
	cin>>v>>na>>intro;
	ofstream outfile;
	outfile.open("G:\\数据结构课程设计\\Vex.txt");
	if(outfile.is_open())
	{
		outfile<<g->n+1<<endl;
		for(i=0;i<g->n;i++)
		{
			outfile<<g->vertex[i]<<endl<<g->name[i]<<endl<<g->introduce[i]<<endl;
		}
		outfile<<v<<endl<<na<<endl<<intro<<endl;
		outfile.close();
	}
	cout<<"写入顶点成功，请重新初始化图"<<endl;

}


void deletever(gLink g)//删除顶点
{
	int v,i;
	cout<<"请输入您要删除顶点的编号："<<endl;
	cin>>v;
	ofstream outfile;
	outfile.open("G:\\数据结构课程设计\\Vex.txt");
	if(outfile.is_open())
	{
		outfile<<g->n-1<<endl;
		for(i=0;i<v;i++)
		{
			outfile<<i<<endl<<g->name[i]<<endl<<g->introduce[i]<<endl;
		}
		for(i=v;i<g->n-1;i++)
		{
			outfile<<i<<endl<<g->name[i+1]<<endl<<g->introduce[i+1]<<endl;
		}
		outfile.close();
	}
	cout<<"删除顶点成功，请重新初始化图"<<endl;

}

void insertside(gLink g)//插入边
{
	int a,b,length,i,j;
	cout<<"请输入您要插入边的两个顶点编号及长度："<<endl;
	cin>>a>>b>>length;
	ofstream outfile;
	outfile.open("G:\\数据结构课程设计\\Edge.txt");
	if(outfile.is_open())
	{
		outfile<<g->v+1<<endl;
		for(i=0;i<g->n;i++)
		{
			for(j=0;j<g->n;j++)
			{
				if(i<j&&g->side[i][j]!=INFINITY)
					outfile<<i<<' '<<j<<' '<<g->side[i][j]<<endl;
			}
		}
		outfile<<a<<' '<<b<<' '<<length<<endl;
	}
	outfile.close();
	cout<<"插入边成功，请重新初始化图"<<endl;

}

void deleteside(gLink g)//删除边
{
	int a,b,i,j;
	cout<<"请输入您要删除边的两个顶点编号："<<endl;
	cin>>a>>b;
	ofstream outfile;
	outfile.open("G:\\数据结构课程设计\\Edge.txt");
	if(outfile.is_open())
	{
		outfile<<g->v-1<<endl;
		for(i=0;i<g->n;i++)
		{
			for(j=0;j<g->n;j++)
			{
				if(i==a&&j==b)
				{}
				else
					if(i<j&&g->side[i][j]!=INFINITY)
						outfile<<i<<' '<<j<<' '<<g->side[i][j]<<endl;
			}
		}
	}
	outfile.close();
	cout<<"删除边成功，请重新初始化图"<<endl;
}




int main()
{
	gLink g=(gLink)malloc(sizeof(Graph));
	g->c=false;
	int choose=0;
	while(true)
	{
r:
		cout<<"--------------------------------------------"<<endl
			<<"          欢迎使用景区信息管理系统          "<<endl
		    <<"              ***请选择菜单***              "<<endl
			<<"--------------------------------------------"<<endl
			<<"       (1)创建景区景点分布图                "<<endl
			<<"       (2)查询景点                          "<<endl
			<<"       (3)旅游景点导航                      "<<endl
			<<"       (4)搜索最短路径                      "<<endl
			<<"       (5)铺设电路规划                      "<<endl
			<<"       (6)插入顶点                          "<<endl
			<<"       (7)删除顶点                          "<<endl
			<<"       (8)插入边                            "<<endl
			<<"       (9)删除边                            "<<endl
			<<"请输入您要选择的菜单项：                    "<<endl;
		cin>>choose;
		if(choose<=9&&choose>0)
		{
			if(choose!=1&&g->c==false)
			{
				cout<<"您还没有创建图，请重新选择："<<endl;
				goto r;
			}
			else
			{
				switch(choose)
				{
				case 1:
					createGraph(g);continue;
			    case 2:
				    select(g);continue;
			    case 3:
					int temp;
					temp=0;
                    cout<<"请输入开始的编号："<<endl;
                    int index;
					cin>>index;
                    navigation(g,index,temp);continue;
			    case 4:
					shortestpath(g);continue;
			    case 5:
					prim(g);continue;
			    case 6:
					insertver(g);continue;
				case 7:
					deletever(g);continue;
				case 8:
					insertside(g);continue;
				case 9:
					deleteside(g);continue;
				default:
					cout<<"您的输入有误，请重新输入："<<endl;
				}
			}
		}
	}
	return 0;
}
