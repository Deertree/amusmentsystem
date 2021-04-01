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
	int vertex[MAX];//������
	char name[MAX][1000];//��������
	char introduce[MAX][1000];//�������
	int side[MAX][MAX];//�߾���
	int n,v;//������������
	bool c;
}Graph,*gLink;
int LocateVex(gLink &G, int v)//�������㣻
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
        cout<<"������ţ�"<<g->vertex[i]<<"   "<<"�������ƣ�"<<g->name[i]<<"   "<<"������ܣ�"<<g->introduce[i]<<endl;
    }
	cout<<"�ڽӾ���Ϊ��"<<endl;
	for(i=0;i<g->n;i++)
	{
		for(j=0;j<g->n;j++)
		{
			cout<<left<<setw(8)<<g->side[i][j];
		}
		cout<<endl;
	}
}

void createGraph(gLink g)//���ļ�����ͼ
{
	int i,j;
	for(i=0;i<MAX;i++)
	{
		for(j=0;j<MAX;j++)
		{
			g->side[i][j]=0;
		}
	}
	fstream file("G:\\���ݽṹ�γ����\\Vex.txt");
	file>>g->n;
	for(i=0;i<g->n;i++)
	{
		file>>g->vertex[i];
		file>>g->name[i];
		file>>g->introduce[i];

	}
	file.close();
	ifstream file1("G:\\���ݽṹ�γ����\\Edge.txt");
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
	cout<<"������ɣ�"<<endl;
	Show(g);
}



void select(gLink g)//��ѯ����
{
	int x;
	cout<<"������Ҫ��ѯ�ľ�����"<<endl;
	cin>>x;
	cout<<"�þ�����Ϊ��"<<g->name[x]<<"   "<<"������ܣ�"<<g->introduce[x]<<endl;
	int j;
	cout<<"��"<<g->name[x]<<"���ڵľ����У�"<<endl;
	for(j=0;j<g->n;j++)
	{
		if(g->side[x][j]!=INFINITY&&g->side[j][x]!=INFINITY)
		{
			cout<<g->name[j]<<"��"<<g->name[x]<<"���"<<g->side[x][j]<<"��Զ"<<endl;
		}
	}

}

int visit[MAX][MAX]={0};//��¼����·��
int DFS[MAX];//��¼������������
void navigation(gLink g,int index,int temp)//���ξ��㵼��,indexΪ��㣬tempΪָ��
{
    DFS[temp]=index;
    if(temp)
    {
        int index1=DFS[temp-1];
        visit[index][index1]=1;
        visit[index1][index]=1;
    }

    if(temp==g->n-1)//����Ѿ������꣬�������·��
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
                if(m==DFS[j])//��m��DFS�У���m�ѱ�������������m��δ��������
                    notnew=true;
            }
            if(g->side[index][m]!=INFINITY&&visit[index][m]!=1&&visit[m][index]!=1&&notnew!=true)//��m����һ���������Ľڵ�֮����·������·û�б��߹���mδ����������
            {

                navigation(g,m,temp+1);
            }

        }

    }
     for(int i=0;i<g->n;i++)//����visited
     {
               visit[i][index]=0;
               visit[index][i]=0;
     }


}

void shortestpath(gLink g)//�������·��
{
	int i,j,x;
	cout<<"������������յ�ı�ţ�"<<endl;
	cin>>i>>j;
	int num;
	num=g->side[i][j];
	cout<<"���·��Ϊ��"<<g->name[i];
	for(x=0;x<g->n;x++)
	{
		if(g->side[i][x]+g->side[x][j]<num)
		{
			num=g->side[i][x]+g->side[x][j];
			cout<<g->name[x];
		}
	}
	cout<<g->name[j]<<"�ܳ�Ϊ"<<num<<"��"<<endl;
}

void prim(gLink g)//�����·�滮
{
	int length=0;
	int v;
	cout<<"�����������·����㣺";
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
		cout<<"��"<<g->name[closest[k]]<<"��"<<g->name[k]<<"��һ��·����Ϊ"<<g->side[closest[k]][k]<<"��"<<endl;
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
	cout<<"�ܳ���"<<length<<"��"<<endl;
}
//�޸�ͼ
void insertver(gLink g)//���붥��
{
	int v,i;
	char na[1000];
	char intro[1000];
	cout<<"��������Ҫ���붥��ı����������ܣ�"<<endl;
	cin>>v>>na>>intro;
	ofstream outfile;
	outfile.open("G:\\���ݽṹ�γ����\\Vex.txt");
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
	cout<<"д�붥��ɹ��������³�ʼ��ͼ"<<endl;

}


void deletever(gLink g)//ɾ������
{
	int v,i;
	cout<<"��������Ҫɾ������ı�ţ�"<<endl;
	cin>>v;
	ofstream outfile;
	outfile.open("G:\\���ݽṹ�γ����\\Vex.txt");
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
	cout<<"ɾ������ɹ��������³�ʼ��ͼ"<<endl;

}

void insertside(gLink g)//�����
{
	int a,b,length,i,j;
	cout<<"��������Ҫ����ߵ����������ż����ȣ�"<<endl;
	cin>>a>>b>>length;
	ofstream outfile;
	outfile.open("G:\\���ݽṹ�γ����\\Edge.txt");
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
	cout<<"����߳ɹ��������³�ʼ��ͼ"<<endl;

}

void deleteside(gLink g)//ɾ����
{
	int a,b,i,j;
	cout<<"��������Ҫɾ���ߵ����������ţ�"<<endl;
	cin>>a>>b;
	ofstream outfile;
	outfile.open("G:\\���ݽṹ�γ����\\Edge.txt");
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
	cout<<"ɾ���߳ɹ��������³�ʼ��ͼ"<<endl;
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
			<<"          ��ӭʹ�þ�����Ϣ����ϵͳ          "<<endl
		    <<"              ***��ѡ��˵�***              "<<endl
			<<"--------------------------------------------"<<endl
			<<"       (1)������������ֲ�ͼ                "<<endl
			<<"       (2)��ѯ����                          "<<endl
			<<"       (3)���ξ��㵼��                      "<<endl
			<<"       (4)�������·��                      "<<endl
			<<"       (5)�����·�滮                      "<<endl
			<<"       (6)���붥��                          "<<endl
			<<"       (7)ɾ������                          "<<endl
			<<"       (8)�����                            "<<endl
			<<"       (9)ɾ����                            "<<endl
			<<"��������Ҫѡ��Ĳ˵��                    "<<endl;
		cin>>choose;
		if(choose<=9&&choose>0)
		{
			if(choose!=1&&g->c==false)
			{
				cout<<"����û�д���ͼ��������ѡ��"<<endl;
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
                    cout<<"�����뿪ʼ�ı�ţ�"<<endl;
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
					cout<<"���������������������룺"<<endl;
				}
			}
		}
	}
	return 0;
}
