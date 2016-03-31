// Matrix.h: interface for the CMMatrix class.
//
//////////////////////////////////////////////////////////////////////
#if!defined(CMMATRIX_H)
#define CMMATRIX_H
#pragma once

class CMMatrix  
{
	// 公有接口函数
public:
	int	m_nNumColumns;			// 矩阵列数
	int	m_nNumRows;				// 矩阵行数
	double*	m_pData;			// 矩阵数据缓冲区

	// 构造与析构
	CMMatrix();										// 基础构造函数
	CMMatrix(int nRows, int nCols);					// 指定行列构造函数
	CMMatrix(int nRows, int nCols, double value[]);	// 指定数据构造函数
	CMMatrix(int nSize);								// 方阵构造函数
	CMMatrix(int nSize, double value[]);				// 指定数据方阵构造函数
	CMMatrix(const CMMatrix& other);					// 拷贝构造函数
	bool ReDim(int nNumRows,int nNumColumns);		// 对已经定义的矩阵按照新的指定行列进行重定义
	bool	Init(int nRows, int nCols);				// 初始化矩阵	
	bool	MakeUnitMatrix(int nSize);				// 将方阵初始化为单位矩阵
	virtual ~CMMatrix();								// 析构函数

	// 输入与显示

	// 将矩阵转换为字符串
//	CString ToString(const CString& sDelim, bool bLineBreak = TRUE) const;
	// 将矩阵的指定行转换为字符串
//	CString RowToString(int nRow, const CString& sDelim) const;
	// 将矩阵的指定列转换为字符串
//	CString ColToString(int nCol, const CString& sDelim) const;

	// 元素与值操作
	bool	SetElement(int nRow, int nCol, double value);	// 设置指定元素的值
	double	GetElement(int nRow, int nCol) const;			// 获取指定元素的值
	// 设置矩阵指定块的值
	bool SetBlock(int nStartRow,int nStartCol,int nWidth,int nHeight,CMMatrix mBlock);
	// 获取源矩阵指定块所形成的矩阵
	CMMatrix GetBlock(int nStartRow, int nStartCol, int nWidth, int nHeight, CMMatrix mSource);

	void    SetData(double value[]);						// 设置矩阵的值
	int		GetNumColumns() const;							// 获取矩阵的列数
	int		GetNumRows() const;								// 获取矩阵的行数
	int     GetRowVector(int nRow, double* pVector) const;	// 获取矩阵的指定行矩阵
	int     GetColVector(int nCol, double* pVector) const;	// 获取矩阵的指定列矩阵
	double* GetData() const;								// 获取矩阵的值

	// 数学操作
	CMMatrix& operator=(const CMMatrix& other);
	bool operator==(const CMMatrix& other) const;
	bool operator!=(const CMMatrix& other) const;
	CMMatrix	operator+(const CMMatrix& other) const;
	CMMatrix	operator-(const CMMatrix& other) const;
	CMMatrix	operator*(double value) const;
	CMMatrix	operator*(const CMMatrix& other) const;

	// 重载[]运算符,可以采用该重载对矩阵元素赋值或获取矩阵元素,如对第i行第j列元素,则n=(i-1)*m_nNumColumns+(j-1)
	double & operator [](int n);

	CMMatrix Negative();			// 返回每个矩阵元素反号的矩阵

	double FrobeniusNorm();		// 求矩阵的Frobenius模
	CMMatrix Orthogonal();		// 正交化

	// 复矩阵乘法
	bool CMul(const CMMatrix& AR, const CMMatrix& AI, const CMMatrix& BR, const CMMatrix& BI, CMMatrix& CR, CMMatrix& CI) const;
	CMMatrix Transpose() const;	// 矩阵的转置

	// 算法

	
	bool InvertGaussJordan();					// 实矩阵求逆的全选主元高斯－约当法
	bool InvertGaussJordan(CMMatrix& mtxImag);	// 复矩阵求逆的全选主元高斯－约当法
	bool InvertSsgj();							// 对称正定矩阵的求逆
	bool InvertTrench();                        // 托伯利兹矩阵求逆的埃兰特方法
	double DetGauss();                          // 求行列式值的全选主元高斯消去法
	int RankGauss();							// 求矩阵秩的全选主元高斯消去法
	bool DetCholesky(double* dblDet);			// 对称正定矩阵的乔里斯基分解与行列式的求值
	bool SplitLU(CMMatrix& mtxL, CMMatrix& mtxU); // 矩阵的三角分解
	bool SplitQR(CMMatrix& mtxQ);				// 一般实矩阵的QR分解
	// 一般实矩阵的奇异值分解
	bool SplitUV(CMMatrix& mtxU, CMMatrix& mtxV, double eps = 0.000001);    
	
	// 求广义逆的奇异值分解法
	bool GInvertUV(CMMatrix& mtxAP, CMMatrix& mtxU, CMMatrix& mtxV, double eps = 0.000001);
	// 约化对称矩阵为对称三对角阵的豪斯荷尔德变换法
	bool MakeSymTri(CMMatrix& mtxQ, CMMatrix& mtxT, double dblB[], double dblC[]);
	// 实对称三对角阵的全部特征值与特征向量的计算
	bool SymTriEigenv(double dblB[], double dblC[], CMMatrix& mtxQ, int nMaxIt = 60, double eps = 0.000001);
	// 约化一般实矩阵为赫申伯格矩阵的初等相似变换法
	void MakeHberg();
	// 求赫申伯格矩阵全部特征值的QR方法
	bool HBergEigenv(double dblU[], double dblV[], int nMaxIt = 60, double eps = 0.000001);

	// 求实对称矩阵特征值与特征向量的雅可比法
	bool JacobiEigenv(double dblEigenValue[], CMMatrix& mtxEigenVector, int nMaxIt = 60, double eps = 0.000001);
	// 求实对称矩阵特征值与特征向量的雅可比过关法
	bool JacobiEigenv2(double dblEigenValue[], CMMatrix& mtxEigenVector, double eps = 0.000001);

	//
	// 保护性数据成员
	//
protected:

	//
	// 内部函数
	//
private:
	void ppp(double a[], double e[], double s[], double v[], int m, int n);
	void sss(double fg[2], double cs[2]);

};

#endif