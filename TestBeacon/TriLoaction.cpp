#include "TriLoaction.h"
#include <time.h>
#include <stdlib.h>
//#include <qmessagebox.h>	//stdlib.h

CVector2 svv[5];

#define MINVALUE 0.000001
#define PI 3.14159265358979323846264338327950288419716939937510

#define DIV_NUM 100				//分区间
#define Sample_NUM 600			//样本数
#define Sample_KalmanNum 120	//kalman样本数
#define Sample_KalmanScale 60	//kalman绘图缩放

//三边余弦求角度
double inline cosine(double tri_a,double tri_b,double tri_c)	//定义cosine函数-余弦定理
{																//tri_a、tri_b、tri_c分别是三角形三边的长度
	if (tri_a<=MINVALUE || tri_b<=MINVALUE) return 0;			//如果tri_a,tri_b=0,返回0
	return acos((tri_a*tri_a+tri_b*tri_b-tri_c*tri_c)/(tri_a*tri_b*2.0));   //余弦定理求角度（弧度）
}

double AngPoint(CVector2 point_a,CVector2 point_b)	//定义AngPoint函数 原点到点point_c的线与x轴正方向形成的夹角
{
    CVector2 point_c;
    point_c.x=point_b.x-point_a.x;
    point_c.y=point_b.y-point_a.y;

    if(point_c.y<0) return (2.0f*PI+atan2(point_c.y,point_c.x));	//求原点到点point_c的线与x轴正方向形成的夹角 负的
       else	return (atan2(point_c.y,point_c.x));			//求原点到点point_c的线与x轴正方向形成的夹角（弧度）
}

CVector2 RotPoint(CVector2 point_a,double f_distance,float fAngle)	//定义RotPoint函数 求两圆交点坐标
{
	CVector2 point_c;
	point_c.x = (f_distance*cos(fAngle));
	point_c.y = (f_distance*sin(fAngle));
	return (point_c+point_a);	//两圆交点的坐标
}


//三个Beacon坐标的求定位点
//入口：三个圆心坐标 v1,v2,v3  三个到beacon的距离 l1,l2,l3
//出口： out
//返回： bool 成功标志
bool GetTriLocation(CVector2 v1,CVector2 v2,CVector2 v3,double l1,double l2, double l3,CVector2 &out)
{
	CVector2 CrossV12[2],CrossV13[2],CrossV23[2];	//圆的两个交点 V12=v1与v2的交点
	CVector2 CrossI11,CrossI12,CrossI21,CrossI22,CrossI31,CrossI32; //定义两圆的最小交点/切点 I11=V12中距离v3最近的交点
	
	double l12=(v1-v2).length();		//l12=v1与v2之间的距离
	double l13=(v1-v3).length();		//l13=v1与v3
	double l23=(v2-v3).length();		//l23=v2与v3

	//1
	if (l1+l2<l12)  //两半径与基站间距的比较判断
	{
		double delta=1.0/(l1*l1)+1.0/(l2*l2);
		CrossI11=(v1/(l1*l1)+v2/(l2*l2))/delta;		//求相离切点坐标并赋值
		CrossI12=(v1/(l1*l1)+v2/(l2*l2))/delta;
	}
	else if(l1-l2>l12 || l1-l2<-l12)
	{
		double epsilon=1.0/(l1*l1)-1.0/(l2*l2);
		CrossI11=(v1/(l1*l1)-v2/(l2*l2))/epsilon;	//求内含切点坐标并赋值
		CrossI12=(v1/(l1*l1)-v2/(l2*l2))/epsilon;
	}
	else
	{
		//1、2和两圆求交点
		double ang12=AngPoint(v1,v2); //求角
		double rot12=cosine(l1,l12,l2); //求余弦
		CrossV12[0]=RotPoint(v1,l1,ang12+rot12); //交点的两个坐标
		CrossV12[1]=RotPoint(v1,l1,ang12-rot12);
		//圆1圆2的两交点到圆3的距离进行比较
		(CrossV12[0]-v3).length()<(CrossV12[1]-v3).length()? CrossI11=CrossV12[0]:CrossI11=CrossV12[1]; //12-3
	}
	//2
	if (l1+l3<l13)
	{
		double delta=1.0/(l1*l1)+1.0/(l3*l3);
		CrossI21=(v1/(l1*l1)+v3/(l3*l3))/delta; //求切点坐标
		CrossI22=(v1/(l1*l1)+v3/(l3*l3))/delta; //求切点坐标
	}
	else if(l1-l3>l13 || l1-l3<-l13)
	{
		double epsilon=1.0/(l1*l1)-1.0/(l3*l3);
		CrossI21=(v1/(l1*l1)-v3/(l3*l3))/epsilon;	//求切点坐标并赋值
		CrossI22=(v1/(l1*l1)-v3/(l3*l3))/epsilon;
	}
	else
	{
		//1、3和两个圆求交点
		double ang13=AngPoint(v1,v3);
		double rot13=cosine(l1,l13,l3);
		CrossV13[0]=RotPoint(v1,l1,ang13+rot13);
		CrossV13[1]=RotPoint(v1,l1,ang13-rot13);
		(CrossV13[0]-v2).length()<(CrossV13[1]-v2).length()? CrossI21=CrossV13[0]:CrossI21=CrossV13[1]; //13-2
	}
	//3
	if (l2+l3<l23)
	{
		double delta=1.0/(l2*l2)+1.0/(l3*l3);
		CrossI31=(v2/(l2*l2)+v3/(l3*l3))/delta;	//求切点坐标
		CrossI32=(v2/(l2*l2)+v3/(l3*l3))/delta;	//并赋值
	}
	else if(l2-l3>l23 || l2-l3<-l23)
	{
		double epsilon=1.0/(l2*l2)-1.0/(l3*l3);
		CrossI31=(v2/(l2*l2)-v3/(l3*l3))/epsilon;	//求内含切点坐标并赋值
		CrossI32=(v2/(l2*l2)-v3/(l3*l3))/epsilon;
	}
	else
	{
		//2、3和两个圆求交点
		double ang23=AngPoint(v2,v3);
		double rot23=cosine(l2,l23,l3);
		CrossV23[0]=RotPoint(v2,l2,ang23+rot23);
		CrossV23[1]=RotPoint(v2,l2,ang23-rot23);
		(CrossV23[0]-v1).length()<(CrossV23[1]-v1).length()? CrossI31=CrossV23[0]:CrossI31=CrossV23[1]; //23-1
	}
	
	out=(CrossI11+CrossI21+CrossI31)/3;		//最近的三点求质心

	return true;
};
//N个Beacon坐标的求定位点
//入口：N个圆心坐标 v1,v2,v3,v4,v5,v6  N个到beacon的距离 l1,l2,l3,l4,l5,l6
//出口：out
//返回：bool 成功标志
#define MAXCOUNT 15	//定义最大beacon数
typedef struct	//定义三顶点 p1,p2,p3
{
	int p1;
	int p2;
	int p3;
}TRI_NUMBER;

inline bool SameTriP(std::vector<TRI_NUMBER> *tri,TRI_NUMBER n)	//找三角形
{
	if (n.p1==n.p2 || n.p2==n.p3 || n.p1==n.p3) return true;	//三个顶点互相不相等
	bool bFind=false;
	for (unsigned int i=0; i<tri[0].size(); i++)
	{
		TRI_NUMBER h=tri[0][i];
		bool bP1=(h.p1==n.p1 || h.p1==n.p2 || h.p1==n.p3); //第一个三角形第一顶点与另个三角形三个顶点是否有相同点
	    bool bP2=(h.p2==n.p1 || h.p2==n.p2 || h.p2==n.p3); //第一个三角形第二顶点与另个三角形三个顶点是否有相同点
		bool bP3=(h.p3==n.p1 || h.p3==n.p2 || h.p3==n.p3); //第一个三角形第三顶点与另个三角形三个顶点是否有相同点
		if (bP1 && bP2 && bP3)	//若找到三个完全相同的点
		{
			bFind=true;
			break;
		}
	}
	return bFind;
};

bool GetLocation(int N,CVector2 v[],double l[],CVector2 &out)	//算法
{
	std::vector<TRI_NUMBER> tri;
	std::vector<CVector2> Triout;
	for (unsigned int i=0; i<N; i++)
		for (unsigned int j=0; j<N; j++)
			for (unsigned int k=0; k<N; k++)
			{
				TRI_NUMBER n;
				n.p1=i;
				n.p2=j;
				n.p3=k;				
				if (!SameTriP(&tri,n))
				{
					tri.push_back(n);
				}
			}

	for (unsigned int i=0; i<tri.size(); i++)
	{
		TRI_NUMBER h=tri[i];
		CVector2 outp;
		GetTriLocation(v[h.p1],v[h.p2],v[h.p3],l[h.p1],l[h.p2],l[h.p3],outp);	//三点定位
		Triout.push_back(outp);
	}
	
	CVector2 sum=CVector2(0,0);	//权值
	double delta=0.0;
	for (unsigned int i=0; i<tri.size(); i++)
	{
		TRI_NUMBER h=tri[i];
		double w=0.00001;
		double alf=cosine((v[h.p1]-v[h.p2]).length(),(v[h.p1]-v[h.p3]).length(),(v[h.p2]-v[h.p3]).length())*(180/PI);
		double r=1.0;	//权值（5,6权值较低）
		if (h.p1>=5) r*=0.75;
		if (h.p2>=5) r*=0.75;
		if (h.p3>=5) r*=0.75;

		if (!(alf<15 || alf>165))	//根据角度赋权值（非过小或过大）
			w=1.0/((l[h.p1]+l[h.p2]+l[h.p3])*(l[h.p1]+l[h.p2]+l[h.p3]))*r;
			sum +=Triout[i]*w;
			delta +=w;
	}
	out=sum/delta;	//值
	return true;
};


double gaussrand()	//生成高斯分布
{
	static double V1, V2, S;
	static int phase = 0;
	double X;
	if(phase == 0)
	{
		do{
			double U1 = (double)rand()/RAND_MAX;
			double U2 = (double)rand()/RAND_MAX;
			V1 = 2*U1-1;
			V2 = 2*U2-1;
			S = V1*V1+V2*V2;
		}while(S >= 1 || S == 0);
		X = V1*sqrt(-2*log(S)/S);
	}
	else
		X = V2*sqrt(-2*log(S)/S);
		phase = 1-phase;
	return X;
}

//生成符合正态分布的一个随机数,均值为0,方差为1
double sampleNormal()
{
	double u = ((double) rand()/(RAND_MAX))*2-1;
	double v = ((double) rand()/(RAND_MAX))*2-1;
	double r = u*u+v*v;
	if (r == 0 || r > 1)
	return sampleNormal();
	double c = sqrt(-2*log(r)/r);
	return u*c;
} 

//协方差R = cov(randn(1,N))
double covN(unsigned int n)
{
	double *v=new double[n];
	for (unsigned int i=0; i<n; i++) v[i]=sampleNormal();

	double con=0;								//初值
	for (unsigned int i=0; i<n; i++) con+=v[i];	//求和
	con/=n;										//均值

	double sumx=0;
	for (unsigned int i=0; i<n; i++) sumx+=(v[i]-con)*(v[i]-con);	//求和
	double conv=sumx/n;

	delete [] v;
	return conv;
}

//kalman filter算法
//入口r1[]数组,返回计算结果
double kalmanfilter(unsigned int N,double r1[])
{
	if (N<1) return 0;
	double *Kg = new double[N];
	double *p  = new double[N];
	double *x  = new double[N];
	for (unsigned int i=0; i<N; i++) x[i] = 0;	//用来记录温度的最优化估算值

	x[0] = r1[0];                 //为x(k)的初赋值
	p[0] = 2;                     //x(1)对应的协方差,根据经验赋值
    double Q = covN(N);           //过程噪声的协方差
	double R = covN(N);           //测量噪声的协方差

	for (int k = 1; k<N ; k++)		//循环里是kalman filter的具体过程
		{
			x[k] = x[k-1];
			p[k] = p[k-1]+Q;
			Kg[k] = p[k]/(p[k]+R);		//Kg:Kalman Gain卡尔曼增益
			x[k] = x[k]+Kg[k]*(r1[k]-x[k]);
			p[k] = (1-Kg[k])*p[k];
		}
    double result=x[N-1];
	delete []Kg;
	delete []p;
	delete []x;
	return result;
}

//这个模块起到平滑滤波的作用
//入口x[],返回Smooth_Result
double SmoothFilter(unsigned int N,double x[])
{
	if (N<1) return 0;
	if (N<4) return x[N-1];
	double *Smooth_Result=new double[N];
	double Filter_Width = 3;	//滤波器带宽,经验的均值
	for (unsigned int i=0; i<N; i++) Smooth_Result[i]= 0;	//用来存放滤波后的各个采样点的值
	for (unsigned i = Filter_Width; i<N; i++)
	{
		double Rssi_Sum = 0;
		for (unsigned int j = i-Filter_Width; j<i; j++)
			Rssi_Sum = x[j]+Rssi_Sum;
		
		Smooth_Result[i] = Rssi_Sum/Filter_Width;	//每一个点的采样值等于这个点之前的filter_width长度的采样点平均值
	}
	double Result=Smooth_Result[N-1];
	delete []Smooth_Result;
	return Result;
}

static double calculateAccuracy(int txPower, double rssi)  {	//新RSSI求距离衰减公式
    if (rssi == 0) {
        return -1.0; // if we cannot determine accuracy, return -1.
    }
    double ratio = rssi*1.0/txPower;
    if (ratio < 1.0) {
        return pow(ratio,10);
    }
    else {
        double accuracy = (0.89976)*pow(ratio,7.7095) + 0.111;
        return accuracy;
    }
}

//N 点数, 顶点向量, r RSSI, A 偏斜量, n 环境参数, 输出坐标点, 计数器---------------------几何算法开始
//bool 返回失败
bool TriLocation(unsigned int N,CVector2 *v,double *r,double *A,double *M, bool *bM,double n,CVector2 &out,int nCount)
{
	if (N<1) return false;
	if (N==1) {out=v[0]; return true;}	//返回本身

	double *D=new double[N];
	double *sortD=new double[N];
	CVector2 *sortv=new CVector2[N];

	//求Beacon距离
	for (unsigned int i=0; i<N; i++)
	{
		if (bM[i])
			  D[i]=M[i];
		else
			  //D[i] = calculateAccuracy(A[i],r[i]);
			  D[i] = (0.89976)*pow(r[i]*1.0/A[i],7.7095) + 0.111;
		      //D[i]=pow(10,(r[i]-A[i])/(-10.0*n));	//RSSI衰减公式求距离
		sortD[i]=D[i];	//赋值给新数组
		sortv[i]=v[i];	//赋值给新数组
	}

	//搜到两点时
	if (N==2)
	{
		double delta=1.0/D[0]+1.0/D[1];
				out=(v[0]/D[0]+v[1]/D[1])/delta;	//加权质心
		delete []D;
		delete []sortD;
		delete []sortv;
		return true;
	}

	//搜到三点时
	if (N==3)
	{
		GetTriLocation(v[0],v[1],v[2],D[0],D[1],D[2],out);	//三点定位
		delete []D;
		delete []sortD;
		delete []sortv;
		return true;
	}

	/*for (unsigned int i=0; i<N; i++)
	{
	if (D[i]<=6)
		D[i]=(D[i]/0.9053)-0.52;
	else if (D[i]>6 || D[i]<=11)
		D[i]=(D[i]/0.9904)-0.1436;
	else if (D[i]>11 || D[i]<=20)
		D[i]=(D[i]/0.9913)-0.27;
	else
		D[i]=(D[i]/0.9992)-0.04;
	}*/

	//beacon选择,根据距离排序
	for (int i=0; i<N-2; i++)
		for (int  j=N-2; j>=i; j--)
		{
			if (sortD[j]>sortD[j+1])
			{
				CVector2 temp=sortv[j];
				sortv[j]=sortv[j+1];
				sortv[j+1]=temp;
				double tempd=sortD[j];
				sortD[j]=sortD[j+1];
				sortD[j+1]=tempd;
			}
		}


	svv[0]=sortv[0];	//画beacon点位
	svv[1]=sortv[1];
	svv[2]=sortv[2];
	svv[3]=sortv[3];
	svv[4]=sortv[4];
	svv[5]=sortv[5];

	if (N>6) N=6;
	
	if (!GetLocation(N,sortv,sortD,out))
	{
		//用此算法算不出来时,使用加权质心法
		double delta=0;
		CVector2 sum=CVector2(0,0);
		for (unsigned int i=0; i<N; i++)
		{
			delta +=1.0/sortD[i];
			sum +=sortv[i]/sortD[i];
		}
		out =sum/delta;
	}
   delete []D;
   delete []sortD;
   delete []sortv;
   return true;
}//---------------------几何算法结束

//N 点数, 顶点向量, r RSSI, A 偏斜量, n 环境参数, 输出坐标点, 计数器---------------------加权质心开始
//bool 返回失败
bool WcaLocation(unsigned int N,CVector2 *v,double *r,double *A,double *M, bool *bM,double n,CVector2 &out,int nCount)
{
	if (N<1) return false;
	if (N==1) {out=v[0]; return true;}	//返回本身

	double *D=new double[N];
	double *sortD=new double[N];
	CVector2 *sortv=new CVector2[N];

	//求Beacon距离
	for (unsigned int i=0; i<N; i++)
	{
		if (bM[i])
			  D[i]=M[i];
		else
			  D[i] = calculateAccuracy(A[i],r[i]);
		      //D[i]=pow(10,(r[i]-A[i])/(-10.0*n));	//RSSI衰减公式求距离
		sortD[i]=D[i];	//赋值给新数组
		sortv[i]=v[i];	//赋值给新数组
	}

	for (unsigned int i=0; i<N; i++)
	{
	if (D[i]<=6)
		D[i]=0.9053*(D[i]+0.52);
	else if (D[i]>6 || D[i]<=11)
		D[i]=0.9904*(D[i]+0.52);
	else if (D[i]>11 || D[i]<=20)
		D[i]=0.9913*(D[i]+0.27);
	else
		D[i]=0.9992*(D[i]+0.04);
	}

	//搜到两点时
	if (N==2)
	{
		double delta=1.0/D[0]+1.0/D[1];
				out=(v[0]/D[0]+v[1]/D[1])/delta;	//加权质心
		delete []D;
		delete []sortD;
		delete []sortv;
		return true;
	}

	//beacon选择,根据距离排序
	for (int i=0; i<N-2; i++)
		for (int  j=N-2; j>=i; j--)
		{
			if (sortD[j]>sortD[j+1])
			{
				CVector2 temp=sortv[j];
				sortv[j]=sortv[j+1];
				sortv[j+1]=temp;
				double tempd=sortD[j];
				sortD[j]=sortD[j+1];
				sortD[j+1]=tempd;
			}
		}

	if (N>8) N=8;
		//使用加权质心法
		double delta=0;
		CVector2 zeta=CVector2(0,0);
		for (unsigned int i=0; i<N; i++)
		{
			delta += 1.0/sortD[i];
			zeta += sortv[i]/sortD[i];
		}
		out =zeta/delta;

   delete []D;
   delete []sortD;
   delete []sortv;
   return true;
 }//---------------------加权质心结束

#define ADD_CLEAR_TIME 3000		//增加Beacon清除时间3秒
#define DELAY_CLEAR_TIME 3000	//Beacon存在最大时间3秒
//#define NULL 0
#define SAFE_DELETE(x) if(NULL!=x) {delete x; x=NULL;}
#define KALMAN_COUNT 2
#define SMOOTH_COUNT 3	//链表出去的数
CTriLoaction::CTriLoaction(void)
{
	m_nCount=0;
	m_UpTime=0;
}

CTriLoaction::~CTriLoaction(void)
{
	//释放内存
	std::map<std::string,std::vector<BEACON_VALUE>*>::iterator it;
	for(it=m_mapBeacon.begin(); it!=m_mapBeacon.end(); it++)
	{
		std::vector<BEACON_VALUE> *arraybeacon=(std::vector<BEACON_VALUE>*)(it->second);
		arraybeacon->clear();
		delete arraybeacon;
	};
}

//超过清除间隙,清除
bool CTriLoaction::TimeOutClear(std::vector<BEACON_VALUE> *arraybeacon,unsigned int nowtime,double ClearTime)
{
	if (arraybeacon->size()<1) return true;
	unsigned int intervaltime=nowtime-arraybeacon[0][arraybeacon->size()-1].time;
	if (intervaltime>ClearTime)
	{
		arraybeacon->clear();
		return true;
	}
	return false;
}

void CTriLoaction::SetScanning(unsigned int N,BEACON_VALUE *beacon)
{ 
	//添加becean链表
	unsigned int nowtime=0;
   
	for (unsigned int i=0; i<N; i++)
	{
		//找出beacon ID号的链表
		std::map<std::string,std::vector<BEACON_VALUE>*>::iterator it=m_mapBeacon.find(beacon[i].ID);	
		nowtime=beacon[i].time;	//beacon时间
		//beacon[i].A=-68;		//A的值*

		if (it==m_mapBeacon.end())
		{
			//新增加beacon链表
			std::vector<BEACON_VALUE>* pVec=new std::vector<BEACON_VALUE>;
			pVec->push_back(beacon[i]);
			m_mapBeacon[beacon[i].ID]=pVec;
		}
		else 
		{
			//判断时间是否超过清除间隙
			TimeOutClear(((std::vector<BEACON_VALUE>*)(it->second)),nowtime,ADD_CLEAR_TIME);
			//新增加beacon链表
			((std::vector<BEACON_VALUE>*)(it->second))[0].push_back(beacon[i]);
		};
	}

	std::map<std::string,std::vector<BEACON_VALUE>*>::iterator it;
	
	for(it=m_mapBeacon.begin(); it!=m_mapBeacon.end(); it++)
	{
		std::vector<BEACON_VALUE>* arraybeacon=(std::vector<BEACON_VALUE>*)(it->second);
		//挤出链表前面的beacon
		while(arraybeacon->size()>SMOOTH_COUNT)	arraybeacon->erase(arraybeacon[0].begin());
		//清除最后超过清除间隙的链表
	 if (TimeOutClear(arraybeacon,nowtime,DELAY_CLEAR_TIME))
		{
			m_mapBeacon.erase(it);	//清除Map指针
			it=m_mapBeacon.begin();	//重新开始检查
		}
	};
};

bool CTriLoaction::Location(double *outx,double *outy)
{
	std::map<std::string,std::vector<BEACON_VALUE>*>::iterator it;
	
	std::vector<BEACON_VALUE> beacon;	//新建链表
	for(it=m_mapBeacon.begin(); it!=m_mapBeacon.end(); it++)
	{
	    double r=0;
		int Num=(it->second)[0].size();
		if (Num==0) continue;	//点数是零时
		double *pNormal=NULL;
		double *pKalman=NULL;
		double *pSmooth=NULL;
	
		pNormal=new double[Sample_KalmanNum];
	    pKalman=new double[Sample_KalmanNum];
		pSmooth=new double[Sample_KalmanNum];

		if (Num<2)	//卡尔曼滤波启动
		{
			for (int i=0; i<Num; i++)
				pSmooth[i]=(it->second)[0][i].r;		//第一组数的第二行的r值
		}
		else if (Num<4)	//平滑滤波启动
		{
			for (int i=0; i<Num; i++)
				pNormal[i]=sampleNormal()*2*2+it->second[0][i].r;	//方差2

			for (int i=0; i<Num; i++)
			{
				pSmooth[i]=kalmanfilter(i+1,pNormal);
			}
		}
		else
		{
			for (int i=0; i<Num; i++)
				pNormal[i]=sampleNormal()*2*2+it->second[0][i].r;	//方差2

			for (int i=0; i<Num; i++)
			{
				pKalman[i]=kalmanfilter(i+1,pNormal);
				//pSmooth[i]=SmoothFilter(i+1,pKalman);
				pSmooth[i]=pKalman[i];
			}
		}
		
		BEACON_VALUE value=(it->second)[0][Num-1];
		value.r=pSmooth[Num-1];
		beacon.push_back(value);
	
		SAFE_DELETE(pNormal);
		SAFE_DELETE(pKalman);
		SAFE_DELETE(pSmooth);
	};
    
    if (beacon.empty()) {
        
        return false;
    }

	CVector2 out;
	CVector2 outfree;
	
	unsigned int N=beacon.size();
	CVector2 *v=new CVector2[N];
	double *r=new double[N];
	double *A=new double[N];
	double *M=new double[N];
	bool *bM=new bool[N];
	for (unsigned int i=0; i<N; i++)
	{
		v[i].x=beacon[i].x;
		v[i].y=beacon[i].y;
		r[i]=beacon[i].r;
		A[i]=beacon[i].A;
		M[i]=beacon[i].M;
		bM[i]=beacon[i].bM;
	}
	bool result;

	if (M[1]-M[0]<0.4)	//判断区域
	{
		TriLocation(N,v,r,A,M,bM,m_Parameter,outfree,m_nCount);
	}
	else
		WcaLocation(N,v,r,A,M,bM,m_Parameter,outfree,m_nCount);


	if (beacon[N-1].time-m_UpTime<10000 && m_nCount!=0)	//10000=10秒,像人类一样奔跑
	{
		if ((outfree-m_UpLocation).length() > 15)	//一跳距离超过15米，则判断为非正常人类
		{
			outfree=m_UpLocation;
		}
		else if (bM[N-1]==1)		//1：有距离-IOS
			outfree = (outfree-m_UpLocation)/2 + m_UpLocation;	//缩减
		else
			outfree = (outfree-m_UpLocation)/8 + m_UpLocation;
	}

	m_UpLocation=outfree;
	m_UpTime=beacon[N-1].time;

	if (m_nCount % 3 == 0)	//刷新频率
	{
		outRefresh=outfree;
	}
	out=outRefresh;

	m_nCount++;

	*outx=out.x;
	*outy=out.y;
	delete[] v;
	delete[] r;
	delete[] A;
	delete[] M;
	delete[] bM;
	return result;
};

void  CTriLoaction::setParametern(double n)	//环境参数衰减变量n赋值
{
	m_Parameter=n;
};