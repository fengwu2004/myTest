// Matrix.h: interface for the CMMatrix class.
//
//////////////////////////////////////////////////////////////////////
#if!defined(CMMATRIX_H)
#define CMMATRIX_H
#pragma once

class CMMatrix  
{
	// ���нӿں���
public:
	int	m_nNumColumns;			// ��������
	int	m_nNumRows;				// ��������
	double*	m_pData;			// �������ݻ�����

	// ����������
	CMMatrix();										// �������캯��
	CMMatrix(int nRows, int nCols);					// ָ�����й��캯��
	CMMatrix(int nRows, int nCols, double value[]);	// ָ�����ݹ��캯��
	CMMatrix(int nSize);								// �����캯��
	CMMatrix(int nSize, double value[]);				// ָ�����ݷ����캯��
	CMMatrix(const CMMatrix& other);					// �������캯��
	bool ReDim(int nNumRows,int nNumColumns);		// ���Ѿ�����ľ������µ�ָ�����н����ض���
	bool	Init(int nRows, int nCols);				// ��ʼ������	
	bool	MakeUnitMatrix(int nSize);				// �������ʼ��Ϊ��λ����
	virtual ~CMMatrix();								// ��������

	// ��������ʾ

	// ������ת��Ϊ�ַ���
//	CString ToString(const CString& sDelim, bool bLineBreak = TRUE) const;
	// �������ָ����ת��Ϊ�ַ���
//	CString RowToString(int nRow, const CString& sDelim) const;
	// �������ָ����ת��Ϊ�ַ���
//	CString ColToString(int nCol, const CString& sDelim) const;

	// Ԫ����ֵ����
	bool	SetElement(int nRow, int nCol, double value);	// ����ָ��Ԫ�ص�ֵ
	double	GetElement(int nRow, int nCol) const;			// ��ȡָ��Ԫ�ص�ֵ
	// ���þ���ָ�����ֵ
	bool SetBlock(int nStartRow,int nStartCol,int nWidth,int nHeight,CMMatrix mBlock);
	// ��ȡԴ����ָ�������γɵľ���
	CMMatrix GetBlock(int nStartRow, int nStartCol, int nWidth, int nHeight, CMMatrix mSource);

	void    SetData(double value[]);						// ���þ����ֵ
	int		GetNumColumns() const;							// ��ȡ���������
	int		GetNumRows() const;								// ��ȡ���������
	int     GetRowVector(int nRow, double* pVector) const;	// ��ȡ�����ָ���о���
	int     GetColVector(int nCol, double* pVector) const;	// ��ȡ�����ָ���о���
	double* GetData() const;								// ��ȡ�����ֵ

	// ��ѧ����
	CMMatrix& operator=(const CMMatrix& other);
	bool operator==(const CMMatrix& other) const;
	bool operator!=(const CMMatrix& other) const;
	CMMatrix	operator+(const CMMatrix& other) const;
	CMMatrix	operator-(const CMMatrix& other) const;
	CMMatrix	operator*(double value) const;
	CMMatrix	operator*(const CMMatrix& other) const;

	// ����[]�����,���Բ��ø����ضԾ���Ԫ�ظ�ֵ���ȡ����Ԫ��,��Ե�i�е�j��Ԫ��,��n=(i-1)*m_nNumColumns+(j-1)
	double & operator [](int n);

	CMMatrix Negative();			// ����ÿ������Ԫ�ط��ŵľ���

	double FrobeniusNorm();		// ������Frobeniusģ
	CMMatrix Orthogonal();		// ������

	// ������˷�
	bool CMul(const CMMatrix& AR, const CMMatrix& AI, const CMMatrix& BR, const CMMatrix& BI, CMMatrix& CR, CMMatrix& CI) const;
	CMMatrix Transpose() const;	// �����ת��

	// �㷨

	
	bool InvertGaussJordan();					// ʵ���������ȫѡ��Ԫ��˹��Լ����
	bool InvertGaussJordan(CMMatrix& mtxImag);	// �����������ȫѡ��Ԫ��˹��Լ����
	bool InvertSsgj();							// �Գ��������������
	bool InvertTrench();                        // �в����Ⱦ�������İ����ط���
	double DetGauss();                          // ������ʽֵ��ȫѡ��Ԫ��˹��ȥ��
	int RankGauss();							// ������ȵ�ȫѡ��Ԫ��˹��ȥ��
	bool DetCholesky(double* dblDet);			// �Գ��������������˹���ֽ�������ʽ����ֵ
	bool SplitLU(CMMatrix& mtxL, CMMatrix& mtxU); // ��������Ƿֽ�
	bool SplitQR(CMMatrix& mtxQ);				// һ��ʵ�����QR�ֽ�
	// һ��ʵ���������ֵ�ֽ�
	bool SplitUV(CMMatrix& mtxU, CMMatrix& mtxV, double eps = 0.000001);    
	
	// ������������ֵ�ֽⷨ
	bool GInvertUV(CMMatrix& mtxAP, CMMatrix& mtxU, CMMatrix& mtxV, double eps = 0.000001);
	// Լ���Գƾ���Ϊ�Գ����Խ���ĺ�˹�ɶ��±任��
	bool MakeSymTri(CMMatrix& mtxQ, CMMatrix& mtxT, double dblB[], double dblC[]);
	// ʵ�Գ����Խ����ȫ������ֵ�����������ļ���
	bool SymTriEigenv(double dblB[], double dblC[], CMMatrix& mtxQ, int nMaxIt = 60, double eps = 0.000001);
	// Լ��һ��ʵ����Ϊ���겮�����ĳ������Ʊ任��
	void MakeHberg();
	// ����겮�����ȫ������ֵ��QR����
	bool HBergEigenv(double dblU[], double dblV[], int nMaxIt = 60, double eps = 0.000001);

	// ��ʵ�Գƾ�������ֵ�������������ſɱȷ�
	bool JacobiEigenv(double dblEigenValue[], CMMatrix& mtxEigenVector, int nMaxIt = 60, double eps = 0.000001);
	// ��ʵ�Գƾ�������ֵ�������������ſɱȹ��ط�
	bool JacobiEigenv2(double dblEigenValue[], CMMatrix& mtxEigenVector, double eps = 0.000001);

	//
	// ���������ݳ�Ա
	//
protected:

	//
	// �ڲ�����
	//
private:
	void ppp(double a[], double e[], double s[], double v[], int m, int n);
	void sss(double fg[2], double cs[2]);

};

#endif