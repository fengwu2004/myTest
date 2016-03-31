// Matrix.cpp: implementation of the CMMatrix class.
//
//////////////////////////////////////////////////////////////////////


#include "CMMatrix.h"
#include "Math.h"
//#include "windows.h"
#include "assert.h"
#include "string.h"

//////////////////////////////////////////////////////////////////////
// �������캯��
//////////////////////////////////////////////////////////////////////
CMMatrix::CMMatrix()
{
	m_nNumColumns = 1;
	m_nNumRows = 1;
	m_pData = NULL;
	bool bSuccess = Init(m_nNumRows, m_nNumColumns);
	assert(bSuccess);
}

//////////////////////////////////////////////////////////////////////
// ָ�����й��캯��
//
// ������
// 1. int nRows - ָ���ľ�������
// 2. int nCols - ָ���ľ�������
//////////////////////////////////////////////////////////////////////
CMMatrix::CMMatrix(int nRows, int nCols)
{
	m_nNumRows = nRows;
	m_nNumColumns = nCols;
	m_pData = NULL;
	bool bSuccess = Init(m_nNumRows, m_nNumColumns);
	assert(bSuccess);
}

//////////////////////////////////////////////////////////////////////
// ָ�����жԾ������¶���
//
// ������
// 1. int nNumRows			- ָ���ľ�������
// 2. int nNumColumns		- ָ���ľ�������
//////////////////////////////////////////////////////////////////////
bool CMMatrix::ReDim(int nNumRows, int nNumColumns)
{
	return Init(nNumRows, nNumColumns);
}

//////////////////////////////////////////////////////////////////////
// ָ��ֵ���캯��
//
// ������
// 1. int nRows - ָ���ľ�������
// 2. int nCols - ָ���ľ�������
// 3. double value[] - һά���飬����ΪnRows*nCols���洢�����Ԫ�ص�ֵ
//////////////////////////////////////////////////////////////////////
CMMatrix::CMMatrix(int nRows, int nCols, double value[])
{
	m_nNumRows = nRows;
	m_nNumColumns = nCols;
	m_pData = NULL;
	bool bSuccess = Init(m_nNumRows, m_nNumColumns);
	assert(bSuccess);

	SetData(value);
}

//////////////////////////////////////////////////////////////////////
// �����캯��
//
// ������
// 1. int nSize - ����������
//////////////////////////////////////////////////////////////////////
CMMatrix::CMMatrix(int nSize)
{
	m_nNumRows = nSize;
	m_nNumColumns = nSize;
	m_pData = NULL;
	bool bSuccess = Init(nSize, nSize);
	assert (bSuccess);
}

//////////////////////////////////////////////////////////////////////
// �����캯��
//
// ������
// 1. int nSize - ������(��)��
// 2. double value[] - һά���飬����ΪnRows*nRows���洢�����Ԫ�ص�ֵ
//////////////////////////////////////////////////////////////////////
CMMatrix::CMMatrix(int nSize, double value[])
{
	m_nNumRows = nSize;
	m_nNumColumns = nSize;
	m_pData = NULL;
	bool bSuccess = Init(nSize, nSize);
	assert (bSuccess);

	SetData(value);
}

//////////////////////////////////////////////////////////////////////
// �������캯��
//
// ������
// 1. const CMMatrix& other - Դ����
//////////////////////////////////////////////////////////////////////
CMMatrix::CMMatrix(const CMMatrix& other)
{
	m_nNumColumns = other.GetNumColumns();
	m_nNumRows = other.GetNumRows();
	m_pData = NULL;
	bool bSuccess = Init(m_nNumRows, m_nNumColumns);
	assert(bSuccess);

	// ��Դ��������ݿ�����Ŀ�������
	memcpy(m_pData, other.m_pData, sizeof(double)*m_nNumColumns*m_nNumRows);
}

//////////////////////////////////////////////////////////////////////
// ��������
//////////////////////////////////////////////////////////////////////
CMMatrix::~CMMatrix()
{
	if (m_pData)
	{
		delete[] m_pData;
		m_pData = NULL;
	}
}

//////////////////////////////////////////////////////////////////////
// ��ʼ������   ��̬����洢�ռ䲢����Ԫ�صĳ�ֵ��Ϊ��
// ������
// 1. int nRows - ָ���ľ�������
// 2. int nCols - ָ���ľ�������
//
// ����ֵ��bool �ͣ���ʼ���ɹ�����true,���򷵻�false
//////////////////////////////////////////////////////////////////////
bool CMMatrix::Init(int nRows, int nCols)
{
	if (m_pData)
	{
		delete[] m_pData;
		m_pData = NULL;
	}

	m_nNumRows = nRows;
	m_nNumColumns = nCols;
	int nSize = nCols*nRows;
	if (nSize < 0)
		return false;

	m_pData = new double[nSize];							// �����ڴ�

	if (m_pData == NULL)
		return false;										// �ڴ����ʧ��
//	if (IsBadReadPtr(m_pData, sizeof(double) * nSize))
//		return false;										// �ڴ治�ɶ�,����false

	memset(m_pData, 0, sizeof(double) * nSize);				// ����Ԫ��ֵ��0

	return true;
}

//////////////////////////////////////////////////////////////////////
// �������ʼ��Ϊ��λ����
//
// ������
// 1. int nSize - ������(��)��
//
// ����ֵ��bool �ͣ���ʼ���Ƿ�ɹ�
//////////////////////////////////////////////////////////////////////
bool CMMatrix::MakeUnitMatrix(int nSize)
{
	if (! Init(nSize, nSize))  //���������Ԫ�س�ʼ��Ϊ�㲻�ɹ��򷵻�false
		return false;

	for (int i=0; i<nSize; ++i)
		for (int j=0; j<nSize; ++j)
			if (i == j)
				m_pData[i*m_nNumColumns+j]=1;

	return true;
}

//////////////////////////////////////////////////////////////////////
// �������Ԫ�ص�ֵת��Ϊ�ַ���
//
// ������
// 1. const CString& sDelim - ����֮��ķָ�����Ĭ��Ϊ�ո�
// 2 bool bLineBreak - ������֮���Ƿ��лس����з���Ĭ��Ϊ��(�л��з�)
//
// ����ֵ��CString �ͣ�ת���õ����ַ���
//////////////////////////////////////////////////////////////////////
/*CString CMMatrix::ToString(const CString& sDelim, bool bLineBreak ) const
{
	CString s=_T("");

	for (int i=0; i<m_nNumRows; ++i)
	{
		for (int j=0; j<m_nNumColumns; ++j)
		{
			CString ss;
			ss.Format(_T("%lf"), GetElement(i, j));
			s += ss;

			if (bLineBreak)
			{
				if (j != m_nNumColumns-1)
					s += sDelim;
			}
			else
			{
				if (i != m_nNumRows-1 || j != m_nNumColumns-1)
					s += sDelim;
			}
		}
		if (bLineBreak)
			if (i != m_nNumRows-1)
				s += _T("\r\n");
	}

	return s;
}*/

//////////////////////////////////////////////////////////////////////
// ������ָ�����и�Ԫ�ص�ֵת��Ϊ�ַ���
//
// ������
// 1. int nRow - ָ���ľ����У�nRow = 0��ʾ��һ��
// 2. const CString& sDelim - ����֮��ķָ�����Ĭ��Ϊ�ո�
//
// ����ֵ��CString �ͣ�ת���õ����ַ���
//////////////////////////////////////////////////////////////////////
/*CString CMMatrix::RowToString(int nRow, const CString& sDelim) const
{
	CString s = _T("");

	if (nRow >= m_nNumRows)
		return s;

	for (int j=0; j<m_nNumColumns; ++j)
	{
		CString ss;
		ss.Format(_T("%f"), GetElement(nRow, j));
		s += ss;
		if (j != m_nNumColumns-1)
			s += sDelim;
	}

	return s;
}

//////////////////////////////////////////////////////////////////////
// ������ָ�����и�Ԫ�ص�ֵת��Ϊ�ַ���
//
// ������
// 1. int nCol - ָ���ľ����У�nCol = 0��ʾ��һ��
// 2. const CString& sDelim - ����֮��ķָ�����Ĭ��Ϊ�ո�
//
// ����ֵ��CString �ͣ�ת���õ����ַ���
//////////////////////////////////////////////////////////////////////
CString CMMatrix::ColToString(int nCol, const CString& sDelim) const
{
	CString s = _T("");

	if (nCol >= m_nNumColumns)
		return s;

	for (int i=0; i<m_nNumRows; ++i)
	{
		CString ss;
		ss.Format(_T("%f"), GetElement(i, nCol));
		s += ss;
		if (i != m_nNumRows-1)
			s += sDelim;
	}

	return s;
}
*/
//////////////////////////////////////////////////////////////////////
// ���þ����Ԫ�ص�ֵ   ����Ԫ��
//
// ������
// 1. double value[] - һά���飬����Ϊm_nNumColumns*m_nNumRows���洢
//                     �����Ԫ�ص�ֵ
//
// ����ֵ����
//////////////////////////////////////////////////////////////////////
void CMMatrix::SetData(double value[])
{
	memset(m_pData, 0, sizeof(double) * m_nNumColumns*m_nNumRows);	// �Ƚ��ڴ��е�ֵ��ʼ��Ϊ0

	memcpy(m_pData, value, sizeof(double)*m_nNumColumns*m_nNumRows);// �������ľ���Ԫ�ؿ������ڴ���
}

//////////////////////////////////////////////////////////////////////
// ����ָ��Ԫ�ص�ֵ   ����Ԫ��
//
// ������
// 1. int nRows - ָ���ľ�������
// 2. int nCols - ָ���ľ�������
// 3. double value - ָ��Ԫ�ص�ֵ
//
// ����ֵ��bool �ͣ�˵�������Ƿ�ɹ�
//////////////////////////////////////////////////////////////////////
bool CMMatrix::SetElement(int nRow, int nCol, double value)
{
	if (nCol < 0 || nCol >= m_nNumColumns || nRow < 0 || nRow >= m_nNumRows)
		return false;						// array bounds error
	if (m_pData == NULL)
		return false;							// bad pointer error
	
	m_pData[nCol + nRow * m_nNumColumns] = value;

	return true;
}


//////////////////////////////////////////////////////////////////////
// ����ָ��Ԫ���ֵ   ���Ԫ��
//
// ������
// 1. int nStartRow  - ��ʼ��,��0����
// 2. int nStartCol  - ��ʼ��,��0����
// 3. int nWidth     - ���ÿ�Ŀ��
// 4. int nHeight    - ���ÿ�ĸ߶�
// 5. CMMatrix mBlock - �������ÿ�ľ���
//
// ����ֵ��bool �ͣ�˵�������Ƿ�ɹ�
//////////////////////////////////////////////////////////////////////
bool CMMatrix::SetBlock(int nStartRow, int nStartCol, int nWidth, int nHeight, CMMatrix mBlock)
{
	int nRow=mBlock.GetNumRows();		// �������ÿ�ľ�������
	int nCol=mBlock.GetNumColumns();	// �������ÿ�ľ�������

	if (nHeight>nRow || nWidth>nCol)
		return false;
	if ((nStartRow+nHeight)>m_nNumRows || (nStartCol+nWidth)>m_nNumColumns)
		return false;

	int i,j;
	int nEndRow=nStartRow+nHeight;
	int nEndCol=nStartCol+nWidth;

	for (i=nStartRow;i<nEndRow;i++)
		for (j=nStartCol;j<nEndCol;j++)
			m_pData[i*m_nNumColumns + j] = mBlock[(i-nStartRow)*nCol+(j-nStartCol)];

	return true;
}

//////////////////////////////////////////////////////////////////////
// ��ȡָ��Ԫ���γɵľ���
//
// ������
// 1. int nStartRow  - ��ʼ��,��0����
// 2. int nStartCol  - ��ʼ��,��0����
// 3. int nWidth     - ����ȡ��Ŀ��
// 4. int nHeight    - ����ȡ��ĸ߶�
// 5. CMMatrix mSource - ���ڻ�ȡ���Դ����
//
// ����ֵ��CMMatrix �ͣ���������ȡ���γɵľ���
//////////////////////////////////////////////////////////////////////
CMMatrix CMMatrix::GetBlock(int nStartRow, int nStartCol, int nWidth, int nHeight, CMMatrix mSource)
{
	int nRow=mSource.GetNumRows();		// ���ڻ�ȡ���Դ��������
	int nCol=mSource.GetNumColumns();	// ���ڻ�ȡ���Դ��������

	// �����ʼ�мӸ߶ȴ���Դ�������������ʼ�мӿ�ȴ���Դ�����������ֱ�ӷ���Դ����
	if ((nStartRow+nHeight)>nRow || (nStartCol+nWidth)>nCol)
		return mSource;

	CMMatrix mBlock(nHeight,nWidth);

	int i,j;
	int nEndRow=nStartRow+nHeight;
	int nEndCol=nStartCol+nWidth;

	for (i=nStartRow;i<nEndRow;i++)
		for (j=nStartCol;j<nEndCol;j++)
			mBlock[(i-nStartRow)*nWidth+(j-nStartCol)]=mSource[i*nCol + j];

	return mBlock;
}

//////////////////////////////////////////////////////////////////////
// ��ȡָ��Ԫ�ص�ֵ
//
// ������
// 1. int nRows - ָ���ľ�������   ������0��ʼ
// 2. int nCols - ָ���ľ�������   ������0��ʼ
//
// ����ֵ��double �ͣ�ָ��Ԫ�ص�ֵ
//////////////////////////////////////////////////////////////////////
double CMMatrix::GetElement(int nRow, int nCol) const
{
	assert(nCol >= 0 && nCol < m_nNumColumns && nRow >= 0 && nRow < m_nNumRows); // array bounds error
	assert(m_pData);							// bad pointer error
	return m_pData[nCol + nRow * m_nNumColumns] ;
}

//////////////////////////////////////////////////////////////////////
// ��ȡ���������
//
// ��������
//
// ����ֵ��int �ͣ����������
//////////////////////////////////////////////////////////////////////
int	CMMatrix::GetNumColumns() const
{
	return m_nNumColumns;
}

//////////////////////////////////////////////////////////////////////
// ��ȡ���������
//
// ��������
//
// ����ֵ��int �ͣ����������
//////////////////////////////////////////////////////////////////////
int	CMMatrix::GetNumRows() const
{
	return m_nNumRows;
}

//////////////////////////////////////////////////////////////////////
// ��ȡ���������
//
// ��������
//
// ����ֵ��double��ָ�룬ָ������Ԫ�ص����ݻ�����
//////////////////////////////////////////////////////////////////////
double* CMMatrix::GetData() const
{
	return m_pData;
}

//////////////////////////////////////////////////////////////////////
// ��ȡָ���е�����
//
// ������
// 1. int nRows - ָ���ľ�������
// 2.  double* pVector - ָ�������и�Ԫ�صĻ�����
//
// ����ֵ��int �ͣ�������Ԫ�صĸ����������������
//////////////////////////////////////////////////////////////////////
int CMMatrix::GetRowVector(int nRow, double* pVector) const
{
	if (pVector)
		delete pVector;

	pVector = new double[m_nNumColumns];
	assert(pVector != NULL);

	for (int j=0; j<m_nNumColumns; ++j)
		pVector[j] = GetElement(nRow, j);

	return m_nNumColumns;
}

//////////////////////////////////////////////////////////////////////
// ��ȡָ���е�����
//
// ������
// 1. int nCols - ָ���ľ�������
// 2.  double* pVector - ָ�������и�Ԫ�صĻ�����
//
// ����ֵ��int �ͣ�������Ԫ�صĸ����������������
//////////////////////////////////////////////////////////////////////
int CMMatrix::GetColVector(int nCol, double* pVector) const
{
	if (pVector)
		delete pVector;

	pVector = new double[m_nNumRows];
	assert(pVector != NULL);

	for (int i=0; i<m_nNumRows; ++i)
		pVector[i] = GetElement(i, nCol);

	return m_nNumRows;
}

//////////////////////////////////////////////////////////////////////
// ���������=��������ֵ
//
// ������
// 1. const CMMatrix& other - ���ڸ�����ֵ��Դ����
//
// ����ֵ��CMMatrix�͵����ã������õľ�����other���
//////////////////////////////////////////////////////////////////////
CMMatrix& CMMatrix::operator=(const CMMatrix& other)
{
	if (&other != this)
	{
		bool bSuccess = Init(other.GetNumRows(), other.GetNumColumns());
		assert(bSuccess);

		// copy the pointer
		memcpy(m_pData, other.m_pData, sizeof(double)*m_nNumColumns*m_nNumRows);
	}

	// finally return a reference to ourselves
	return *this ;
}

//////////////////////////////////////////////////////////////////////
// ���������==���жϾ����Ƿ����
//
// ������
// 1. const CMMatrix& other - ���ڱȽϵľ���
//
// ����ֵ��bool �ͣ���������(����Ԫ�����)�����Ϊtrue������Ϊfalse
//////////////////////////////////////////////////////////////////////
bool CMMatrix::operator==(const CMMatrix& other) const
{
	// ���ȼ���������Ƿ����
	if (m_nNumColumns != other.GetNumColumns() || m_nNumRows != other.GetNumRows())
		return false;

	for (int i=0; i<m_nNumRows; ++i)
	{
		for (int j=0; j<m_nNumColumns; ++j)
		{
			if (GetElement(i, j) != other.GetElement(i, j))
				return false;
		}
	}

	return true;
}

//////////////////////////////////////////////////////////////////////
// ���������!=���жϾ����Ƿ����
//
// ������
// 1. const CMMatrix& other - ���ڱȽϵľ���
//
// ����ֵ��bool �ͣ����������������Ϊtrue������Ϊfalse
//////////////////////////////////////////////////////////////////////
bool CMMatrix::operator!=(const CMMatrix& other) const
{
	return !(*this == other);
}

//////////////////////////////////////////////////////////////////////
// ���������+��ʵ�־���ļӷ�
//
// ������
// 1. const CMMatrix& other - ��ָ��������ӵľ���
//
// ����ֵ��CMMatrix�ͣ�ָ��������other���֮��
//////////////////////////////////////////////////////////////////////
CMMatrix	CMMatrix::operator+(const CMMatrix& other) const
{
	// ���ȼ���������Ƿ����
	assert (m_nNumColumns == other.GetNumColumns() && m_nNumRows == other.GetNumRows());

	// ����������
	CMMatrix	result(*this) ;		// ��������
	// ����ӷ�
	for (int i = 0 ; i < m_nNumRows ; ++i)
	{
		for (int j = 0 ; j <  m_nNumColumns; ++j)
			result.SetElement(i, j, result.GetElement(i, j) + other.GetElement(i, j)) ;
	}

	return result ;
}

//////////////////////////////////////////////////////////////////////
// ���������-��ʵ�־���ļ���
//
// ������
// 1. const CMMatrix& other - ��ָ����������ľ���
//
// ����ֵ��CMMatrix�ͣ�ָ��������other���֮��
//////////////////////////////////////////////////////////////////////
CMMatrix	CMMatrix::operator-(const CMMatrix& other) const
{
	// ���ȼ���������Ƿ����
	assert (m_nNumColumns == other.GetNumColumns() && m_nNumRows == other.GetNumRows());

	// ����Ŀ�����
	CMMatrix	result(*this) ;		// copy ourselves
	// ���м�������
	for (int i = 0 ; i < m_nNumRows ; ++i)
	{
		for (int j = 0 ; j <  m_nNumColumns; ++j)
			result.SetElement(i, j, result.GetElement(i, j) - other.GetElement(i, j)) ;
	}

	return result ;
}

//////////////////////////////////////////////////////////////////////
// ���������*��ʵ�־��������   ������ֵ��������
//
// ������
// 1. double value - ��ָ��������˵�ʵ��
//
// ����ֵ��CMMatrix�ͣ�ָ��������value���֮��
//////////////////////////////////////////////////////////////////////
CMMatrix	CMMatrix::operator*(double value) const
{
	// ����Ŀ�����
	CMMatrix	result(*this) ;		// copy ourselves
	// ��������
	for (int i = 0 ; i < m_nNumRows ; ++i)
	{
		for (int j = 0 ; j <  m_nNumColumns; ++j)
			result.SetElement(i, j, result.GetElement(i, j) * value) ;
	}

	return result ;
}

//////////////////////////////////////////////////////////////////////
// ���������*��ʵ�־���ĳ˷�   ������������
//
// ������
// 1. const CMMatrix& other - ��ָ��������˵ľ���
//
// ����ֵ��CMMatrix�ͣ�ָ��������other���֮��
//////////////////////////////////////////////////////////////////////
CMMatrix	CMMatrix::operator*(const CMMatrix& other) const
{
	// ���ȼ���������Ƿ����Ҫ��   �����������������Ҿ�����������
	assert (m_nNumColumns == other.m_nNumRows);

	// construct the object we are going to return
	CMMatrix	result(m_nNumRows, other.m_nNumColumns) ;

	// ����˷�����
	//
	// [A][B][C]   [G][H]     [A*G + B*I + C*K][A*H + B*J + C*L]
	// [D][E][F] * [I][J] =   [D*G + E*I + F*K][D*H + E*J + F*L]
	//             [K][L]
	//
	double	value ;
	int nOtherCol=other.m_nNumColumns;
	for (int i = 0 ; i < result.m_nNumRows ; ++i)
	{
		for (int j = 0 ; j < nOtherCol ; ++j)
		{
			value = 0.0 ;
			for (int k = 0 ; k < m_nNumColumns ; ++k)
			{
				value += m_pData[k + i * m_nNumColumns] * 
					     other.m_pData[j + k * nOtherCol] ;
			}
			result.m_pData[j + i * nOtherCol] = value ;
		}
	}

	return result ;
}

//////////////////////////////////////////////////////////////////////
// ���������[]��ʵ�ֶԾ���Ԫ�صĴ�ȡ
//
// ������
// 1. int n  ����ȡԪ�ص�λ��
//
// ����ֵ��double�ͣ�����Ԫ�ص�ֵ���ַ
//////////////////////////////////////////////////////////////////////
double & CMMatrix::operator [](int n)
{
	return m_pData[n];
}

//////////////////////////////////////////////////////////////////////
// ������ĳ˷�
//
// ������
// 1. const CMMatrix& AR - ��߸������ʵ������
// 2. const CMMatrix& AI - ��߸�������鲿����
// 3. const CMMatrix& BR - �ұ߸������ʵ������
// 4. const CMMatrix& BI - �ұ߸�������鲿����
// 5. CMMatrix& CR - �˻�����������ʵ������
// 6. CMMatrix& CI - �˻������������鲿����
//
// ����ֵ��bool�ͣ�������˷��Ƿ�ɹ�
//////////////////////////////////////////////////////////////////////
bool CMMatrix::CMul(const CMMatrix& AR, const CMMatrix& AI, const CMMatrix& BR, const CMMatrix& BI, CMMatrix& CR, CMMatrix& CI) const
{
	// ���ȼ���������Ƿ����Ҫ��
	if (AR.GetNumColumns() != AI.GetNumColumns() ||
		AR.GetNumRows() != AI.GetNumRows() ||
		BR.GetNumColumns() != BI.GetNumColumns() ||
		BR.GetNumRows() != BI.GetNumRows() ||
		AR.GetNumColumns() != BR.GetNumRows())
		return false;

	// ����˻�����ʵ��������鲿����
	CMMatrix mtxCR(AR.GetNumRows(), BR.GetNumColumns()), mtxCI(AR.GetNumRows(), BR.GetNumColumns());
	// ���������
    for (int i=0; i<AR.GetNumRows(); ++i)
	{
	    for (int j=0; j<BR.GetNumColumns(); ++j)
		{
			double vr = 0;
			double vi = 0;
            for (int k =0; k<AR.GetNumColumns(); ++k)
			{
                double p = AR.GetElement(i, k) * BR.GetElement(k, j);
                double q = AI.GetElement(i, k) * BI.GetElement(k, j);
                double s = (AR.GetElement(i, k) + AI.GetElement(i, k)) * (BR.GetElement(k, j) + BI.GetElement(k, j));
                vr += p - q;
                vi += s - p - q;
			}
            mtxCR.SetElement(i, j, vr);
            mtxCI.SetElement(i, j, vi);
        }
	}

	CR = mtxCR;
	CI = mtxCI;

	return true;
}

//////////////////////////////////////////////////////////////////////
// �����ת��
//
// ��������
//
// ����ֵ��CMMatrix�ͣ�ָ������ת�þ���
//////////////////////////////////////////////////////////////////////
CMMatrix CMMatrix::Transpose() const
{
	// ����Ŀ�����,����������Դ���������,��������Դ���������
	CMMatrix Trans(m_nNumColumns, m_nNumRows);

	// ת�ø�Ԫ��
	for (int i = 0 ; i < m_nNumRows ; ++i)
	{
		for (int j = 0 ; j < m_nNumColumns ; ++j)
			Trans[i+j*m_nNumRows] = m_pData[j+i*m_nNumColumns];
			//Trans.SetElement(j, i, GetElement(i, j)) ;
	}

	return Trans;
}

//////////////////////////////////////////////////////////////////////
// ʵ���������ȫѡ��Ԫ��˹��Լ����   ���������������Դ����λ��
//
// ��������
//
// ����ֵ��bool�ͣ������Ƿ�ɹ�
//////////////////////////////////////////////////////////////////////
bool CMMatrix::InvertGaussJordan()
{
	int *pnRow, *pnCol,i,j,k,l,u,v;
    double d = 0, p = 0;

	// �����ڴ�
    pnRow = new int[m_nNumColumns];
    pnCol = new int[m_nNumColumns];
	if (pnRow == NULL || pnCol == NULL)
		return false;

	// ��Ԫ
    for (k=0; k<=m_nNumColumns-1; k++)
    { 
		d=0.0;
        for (i=k; i<=m_nNumColumns-1; i++)
		{
			for (j=k; j<=m_nNumColumns-1; j++)
			{ 
				l=i*m_nNumColumns+j; p=fabs(m_pData[l]);
				if (p>d) 
				{ 
					d=p; 
					pnRow[k]=i; 
					pnCol[k]=j;
				}
			}
		}
        
		// ʧ��
		if (d == 0.0)
		{
			delete[] pnRow;
			delete[] pnCol;
			return false;
		}

        if (pnRow[k] != k)
		{
			for (j=0; j<=m_nNumColumns-1; j++)
			{ 
				u=k*m_nNumColumns+j; 
				v=pnRow[k]*m_nNumColumns+j;
				p=m_pData[u]; 
				m_pData[u]=m_pData[v]; 
				m_pData[v]=p;
			}
		}
        
		if (pnCol[k] != k)
		{
			for (i=0; i<=m_nNumColumns-1; i++)
            { 
				u=i*m_nNumColumns+k; 
				v=i*m_nNumColumns+pnCol[k];
				p=m_pData[u]; 
				m_pData[u]=m_pData[v]; 
				m_pData[v]=p;
            }
		}

        l=k*m_nNumColumns+k;
        m_pData[l]=1.0/m_pData[l];
        for (j=0; j<=m_nNumColumns-1; j++)
		{
			if (j != k)
            { 
				u=k*m_nNumColumns+j; 
				m_pData[u]=m_pData[u]*m_pData[l];
			}
		}

        for (i=0; i<=m_nNumColumns-1; i++)
		{
			if (i!=k)
			{
				for (j=0; j<=m_nNumColumns-1; j++)
				{
					if (j!=k)
					{ 
						u=i*m_nNumColumns+j;
						m_pData[u]=m_pData[u]-m_pData[i*m_nNumColumns+k]*m_pData[k*m_nNumColumns+j];
					}
                }
			}
		}

        for (i=0; i<=m_nNumColumns-1; i++)
		{
			if (i!=k)
            { 
				u=i*m_nNumColumns+k; 
				m_pData[u]=-m_pData[u]*m_pData[l];
			}
		}
    }

    // �����ָ����д���
    for (k=m_nNumColumns-1; k>=0; k--)
    { 
		if (pnCol[k]!=k)
		{
			for (j=0; j<=m_nNumColumns-1; j++)
            { 
				u=k*m_nNumColumns+j; 
				v=pnCol[k]*m_nNumColumns+j;
				p=m_pData[u]; 
				m_pData[u]=m_pData[v]; 
				m_pData[v]=p;
            }
		}

        if (pnRow[k]!=k)
		{
			for (i=0; i<=m_nNumColumns-1; i++)
            { 
				u=i*m_nNumColumns+k; 
				v=i*m_nNumColumns+pnRow[k];
				p=m_pData[u]; 
				m_pData[u]=m_pData[v]; 
				m_pData[v]=p;
            }
		}
    }

	// �����ڴ�
	delete[] pnRow;
	delete[] pnCol;

	// �ɹ�����
	return true;
}

//////////////////////////////////////////////////////////////////////
// �����������ȫѡ��Ԫ��˹��Լ����
//
// ������
// 1. CMMatrix& mtxImag - ��������鲿���󣬵�ǰ����Ϊ�������ʵ��
//
// ����ֵ��bool�ͣ������Ƿ�ɹ�
//////////////////////////////////////////////////////////////////////
bool CMMatrix::InvertGaussJordan(CMMatrix& mtxImag)
{
	int *pnRow,*pnCol,i,j,k,l,u,v,w;
    double p,q,s,t,d,b;

	// �����ڴ�
    pnRow = new int[m_nNumColumns];
    pnCol = new int[m_nNumColumns];
	if (pnRow == NULL || pnCol == NULL)
		return false;

	// ��Ԫ
    for (k=0; k<=m_nNumColumns-1; k++)
    { 
		d=0.0;
        for (i=k; i<=m_nNumColumns-1; i++)
		{
			for (j=k; j<=m_nNumColumns-1; j++)
			{ 
				u=i*m_nNumColumns+j;
				p=m_pData[u]*m_pData[u]+mtxImag.m_pData[u]*mtxImag.m_pData[u];
				if (p>d) 
				{ 
					d=p; 
					pnRow[k]=i; 
					pnCol[k]=j;
				}
			}
		}

		// ʧ��
        if (d == 0.0)
        { 
			delete[] pnRow;
			delete[] pnCol;
            return(0);
        }

        if (pnRow[k]!=k)
		{
			for (j=0; j<=m_nNumColumns-1; j++)
            { 
				u=k*m_nNumColumns+j; 
				v=pnRow[k]*m_nNumColumns+j;
				t=m_pData[u]; 
				m_pData[u]=m_pData[v]; 
				m_pData[v]=t;
				t=mtxImag.m_pData[u]; 
				mtxImag.m_pData[u]=mtxImag.m_pData[v]; 
				mtxImag.m_pData[v]=t;
            }
		}

        if (pnCol[k]!=k)
		{
			for (i=0; i<=m_nNumColumns-1; i++)
            { 
				u=i*m_nNumColumns+k; 
				v=i*m_nNumColumns+pnCol[k];
				t=m_pData[u]; 
				m_pData[u]=m_pData[v]; 
				m_pData[v]=t;
				t=mtxImag.m_pData[u]; 
				mtxImag.m_pData[u]=mtxImag.m_pData[v]; 
				mtxImag.m_pData[v]=t;
            }
		}

        l=k*m_nNumColumns+k;
        m_pData[l]=m_pData[l]/d; mtxImag.m_pData[l]=-mtxImag.m_pData[l]/d;
        for (j=0; j<=m_nNumColumns-1; j++)
		{
			if (j!=k)
            { 
				u=k*m_nNumColumns+j;
				p=m_pData[u]*m_pData[l]; 
				q=mtxImag.m_pData[u]*mtxImag.m_pData[l];
				s=(m_pData[u]+mtxImag.m_pData[u])*(m_pData[l]+mtxImag.m_pData[l]);
				m_pData[u]=p-q; 
				mtxImag.m_pData[u]=s-p-q;
            }
		}

        for (i=0; i<=m_nNumColumns-1; i++)
		{
			if (i!=k)
            { 
				v=i*m_nNumColumns+k;
				for (j=0; j<=m_nNumColumns-1; j++)
				{
					if (j!=k)
					{ 
						u=k*m_nNumColumns+j;  
						w=i*m_nNumColumns+j;
						p=m_pData[u]*m_pData[v]; 
						q=mtxImag.m_pData[u]*mtxImag.m_pData[v];
						s=(m_pData[u]+mtxImag.m_pData[u])*(m_pData[v]+mtxImag.m_pData[v]);
						t=p-q; 
						b=s-p-q;
						m_pData[w]=m_pData[w]-t;
						mtxImag.m_pData[w]=mtxImag.m_pData[w]-b;
					}
				}
            }
		}

        for (i=0; i<=m_nNumColumns-1; i++)
		{
			if (i!=k)
            { 
				u=i*m_nNumColumns+k;
				p=m_pData[u]*m_pData[l]; 
				q=mtxImag.m_pData[u]*mtxImag.m_pData[l];
				s=(m_pData[u]+mtxImag.m_pData[u])*(m_pData[l]+mtxImag.m_pData[l]);
				m_pData[u]=q-p; 
				mtxImag.m_pData[u]=p+q-s;
            }
		}
    }

    // �����ָ����д���
    for (k=m_nNumColumns-1; k>=0; k--)
    { 
		if (pnCol[k]!=k)
		{
			for (j=0; j<=m_nNumColumns-1; j++)
            { 
				u=k*m_nNumColumns+j; 
				v=pnCol[k]*m_nNumColumns+j;
				t=m_pData[u]; 
				m_pData[u]=m_pData[v]; 
				m_pData[v]=t;
				t=mtxImag.m_pData[u]; 
				mtxImag.m_pData[u]=mtxImag.m_pData[v]; 
				mtxImag.m_pData[v]=t;
            }
		}

        if (pnRow[k]!=k)
		{
			for (i=0; i<=m_nNumColumns-1; i++)
            { 
				u=i*m_nNumColumns+k; 
				v=i*m_nNumColumns+pnRow[k];
				t=m_pData[u]; 
				m_pData[u]=m_pData[v]; 
				m_pData[v]=t;
				t=mtxImag.m_pData[u]; 
				mtxImag.m_pData[u]=mtxImag.m_pData[v]; 
				mtxImag.m_pData[v]=t;
            }
		}
    }

	// �����ڴ�
	delete[] pnRow;
	delete[] pnCol;

	// �ɹ�����
	return true;
}

//////////////////////////////////////////////////////////////////////
// �Գ��������������
//
// ��������
//
// ����ֵ��bool�ͣ������Ƿ�ɹ�
//////////////////////////////////////////////////////////////////////
bool CMMatrix::InvertSsgj()
{ 
	int i, j ,k, m;
    double w, g, *pTmp;

	// ��ʱ�ڴ�
    pTmp = new double[m_nNumColumns];

	// ���д���
    for (k=0; k<=m_nNumColumns-1; k++)
    { 
		w=m_pData[0];
        if (w == 0.0)
        { 
			delete[] pTmp;
			return false;
		}

        m=m_nNumColumns-k-1;
        for (i=1; i<=m_nNumColumns-1; i++)
        { 
			g=m_pData[i*m_nNumColumns]; 
			pTmp[i]=g/w;
            if (i<=m) 
				pTmp[i]=-pTmp[i];
            for (j=1; j<=i; j++)
              m_pData[(i-1)*m_nNumColumns+j-1]=m_pData[i*m_nNumColumns+j]+g*pTmp[j];
        }

        m_pData[m_nNumColumns*m_nNumColumns-1]=1.0/w;
        for (i=1; i<=m_nNumColumns-1; i++)
			m_pData[(m_nNumColumns-1)*m_nNumColumns+i-1]=pTmp[i];
    }

	// ���е���
    for (i=0; i<=m_nNumColumns-2; i++)
		for (j=i+1; j<=m_nNumColumns-1; j++)
			m_pData[i*m_nNumColumns+j]=m_pData[j*m_nNumColumns+i];

	// ��ʱ�ڴ�����
	delete[] pTmp;

	return true;
}

//////////////////////////////////////////////////////////////////////
// �в����Ⱦ�������İ����ط���
//
// ��������
//
// ����ֵ��bool�ͣ������Ƿ�ɹ�
//////////////////////////////////////////////////////////////////////
bool CMMatrix::InvertTrench()
{ 
	int i,j,k;
    double a,s,*t,*tt,*c,*r,*p;

	// ������Ԫ��
	t = new double[m_nNumColumns];
	// ������Ԫ��
	tt = new double[m_nNumColumns];

	// �ϡ�������Ԫ�ظ�ֵ
	for (i=0; i<m_nNumColumns; ++i)
	{
		t[i] = GetElement(0, i);
	    tt[i] = GetElement(i, 0);
	}

	// ��ʱ������
	c = new double[m_nNumColumns];
	r = new double[m_nNumColumns];
	p = new double[m_nNumColumns];

	// ��Toeplitz���󣬷���
    if (t[0] == 0.0)
    { 
		delete[] t;
		delete[] tt;
		delete[] c;
		delete[] r;
		delete[] p;
		return false;
    }

    a=t[0]; 
	c[0]=tt[1]/t[0]; 
	r[0]=t[1]/t[0];

    for (k=0; k<=m_nNumColumns-3; k++)
    { 
		s=0.0;
        for (j=1; j<=k+1; j++)
			s=s+c[k+1-j]*tt[j];

        s=(s-tt[k+2])/a;
		for (i=0; i<=k; i++)
			p[i]=c[i]+s*r[k-i];

        c[k+1]=-s;
        s=0.0;
        for (j=1; j<=k+1; j++)
          s=s+r[k+1-j]*t[j];
        
		s=(s-t[k+2])/a;
        for (i=0; i<=k; i++)
        { 
			r[i]=r[i]+s*c[k-i];
            c[k-i]=p[k-i];
        }

        r[k+1]=-s;
		a=0.0;
        for (j=1; j<=k+2; j++)
          a=a+t[j]*c[j-1];

        a=t[0]-a;

		// ���ʧ��
        if (a == 0.0)
		{ 
			delete[] t;
			delete[] tt;
			delete[] c;
			delete[] r;
			delete[] p;
			return false;
		}
    }

    m_pData[0]=1.0/a;
    for (i=0; i<=m_nNumColumns-2; i++)
    { 
		k=i+1; 
		j=(i+1)*m_nNumColumns;
        m_pData[k]=-r[i]/a; 
		m_pData[j]=-c[i]/a;
    }

   for (i=0; i<=m_nNumColumns-2; i++)
	{
		for (j=0; j<=m_nNumColumns-2; j++)
		{ 
			k=(i+1)*m_nNumColumns+j+1;
			m_pData[k]=m_pData[i*m_nNumColumns+j]-c[i]*m_pData[j+1];
			m_pData[k]=m_pData[k]+c[m_nNumColumns-j-2]*m_pData[m_nNumColumns-i-1];
		}
	}

    // ��ʱ�ڴ�����
	delete[] t;
	delete[] tt;
	delete[] c;
	delete[] r;
	delete[] p;

	return true;
}
                                               
//////////////////////////////////////////////////////////////////////
// ������ʽֵ��ȫѡ��Ԫ��˹��ȥ��
//
// ��������
//
// ����ֵ��double�ͣ�����ʽ��ֵ
//////////////////////////////////////////////////////////////////////
double CMMatrix::DetGauss()
{ 
	int i,j,k,is,js,l,u,v;
    double f,det,q,d;
    
	// ��ֵ
	f=1.0; 
	det=1.0;
    
	// ��Ԫ
	for (k=0; k<=m_nNumColumns-2; k++)
    { 
		q=0.0;
        for (i=k; i<=m_nNumColumns-1; i++)
		{
			for (j=k; j<=m_nNumColumns-1; j++)
			{ 
				l=i*m_nNumColumns+j; 
				d=fabs(m_pData[l]);
				if (d>q) 
				{ 
					q=d; 
					is=i; 
					js=j;
				}
			}
		}

        if (q == 0.0)
        { 
			det=0.0; 
			return(det);
		}
        
		if (is!=k)
        { 
			f=-f;
            for (j=k; j<=m_nNumColumns-1; j++)
            { 
				u=k*m_nNumColumns+j; 
				v=is*m_nNumColumns+j;
                d=m_pData[u]; 
				m_pData[u]=m_pData[v]; 
				m_pData[v]=d;
            }
        }
        
		if (js!=k)
        { 
			f=-f;
            for (i=k; i<=m_nNumColumns-1; i++)
            {
				u=i*m_nNumColumns+js; 
				v=i*m_nNumColumns+k;
                d=m_pData[u]; 
				m_pData[u]=m_pData[v]; 
				m_pData[v]=d;
            }
        }

        l=k*m_nNumColumns+k;
        det=det*m_pData[l];
        for (i=k+1; i<=m_nNumColumns-1; i++)
        { 
			d=m_pData[i*m_nNumColumns+k]/m_pData[l];
            for (j=k+1; j<=m_nNumColumns-1; j++)
            { 
				u=i*m_nNumColumns+j;
                m_pData[u]=m_pData[u]-d*m_pData[k*m_nNumColumns+j];
            }
        }
    }
    
	// ��ֵ
	det=f*det*m_pData[m_nNumColumns*m_nNumColumns-1];

    return(det);
}

//////////////////////////////////////////////////////////////////////
// ������ȵ�ȫѡ��Ԫ��˹��ȥ��
//
// ��������
//
// ����ֵ��int�ͣ��������
//////////////////////////////////////////////////////////////////////
int CMMatrix::RankGauss()
{ 
	int i,j,k,nn,is,js,l,ll,u,v;
    double q,d;
    
	// ��С�ڵ���������
	nn = m_nNumRows;
    if (m_nNumRows >= m_nNumColumns) 
		nn = m_nNumColumns;

    k=0;

	// ��Ԫ���
    for (l=0; l<=nn-1; l++)
    { 
		q=0.0;
        for (i=l; i<=m_nNumRows-1; i++)
		{
			for (j=l; j<=m_nNumColumns-1; j++)
			{ 
				ll=i*m_nNumColumns+j; 
				d=fabs(m_pData[ll]);
				if (d>q) 
				{ 
					q=d; 
					is=i; 
					js=j;
				}
			}
		}

        if (q == 0.0) 
			return(k);

        k=k+1;
        if (is!=l)
        { 
			for (j=l; j<=m_nNumColumns-1; j++)
            { 
				u=l*m_nNumColumns+j; 
				v=is*m_nNumColumns+j;
                d=m_pData[u]; 
				m_pData[u]=m_pData[v]; 
				m_pData[v]=d;
            }
        }
        if (js!=l)
        { 
			for (i=l; i<=m_nNumRows-1; i++)
            { 
				u=i*m_nNumColumns+js; 
				v=i*m_nNumColumns+l;
                d=m_pData[u]; 
				m_pData[u]=m_pData[v]; 
				m_pData[v]=d;
            }
        }
        
		ll=l*m_nNumColumns+l;
        for (i=l+1; i<=m_nNumColumns-1; i++)
        { 
			d=m_pData[i*m_nNumColumns+l]/m_pData[ll];
            for (j=l+1; j<=m_nNumColumns-1; j++)
            { 
				u=i*m_nNumColumns+j;
                m_pData[u]=m_pData[u]-d*m_pData[l*m_nNumColumns+j];
            }
        }
    }
    
	return(k);
}

//////////////////////////////////////////////////////////////////////
// �Գ��������������˹���ֽ�������ʽ����ֵ
//
// ������
// 1. double* dblDet - ��������ʽ��ֵ
//
// ����ֵ��bool�ͣ�����Ƿ�ɹ�
//////////////////////////////////////////////////////////////////////
bool CMMatrix::DetCholesky(double* dblDet)
{ 
	int i,j,k,u,l;
    double d;
    
	// ���������Ҫ��
	if (m_pData[0] <= 0.0)
		return false;

	// ����˹���ֽ�

    m_pData[0]=sqrt(m_pData[0]);
    d=m_pData[0];

    for (i=1; i<=m_nNumColumns-1; i++)
    { 
		u=i*m_nNumColumns; 
		m_pData[u]=m_pData[u]/m_pData[0];
	}
    
	for (j=1; j<=m_nNumColumns-1; j++)
    { 
		l=j*m_nNumColumns+j;
        for (k=0; k<=j-1; k++)
        { 
			u=j*m_nNumColumns+k; 
			m_pData[l]=m_pData[l]-m_pData[u]*m_pData[u];
		}
        
		if (m_pData[l] <= 0.0)
			return false;

        m_pData[l]=sqrt(m_pData[l]);
        d=d*m_pData[l];
        
		for (i=j+1; i<=m_nNumColumns-1; i++)
        { 
			u=i*m_nNumColumns+j;
            for (k=0; k<=j-1; k++)
				m_pData[u]=m_pData[u]-m_pData[i*m_nNumColumns+k]*m_pData[j*m_nNumColumns+k];
            
			m_pData[u]=m_pData[u]/m_pData[l];
        }
    }
    
	// ����ʽ��ֵ
	*dblDet=d*d;
    
	// �����Ǿ���
    for (i=0; i<=m_nNumColumns-2; i++)
		for (j=i+1; j<=m_nNumColumns-1; j++)
			m_pData[i*m_nNumColumns+j]=0.0;

	return true;
}

//////////////////////////////////////////////////////////////////////
// ��������Ƿֽ⣬�ֽ�ɹ���ԭ���󽫳�ΪQ����
//
// ������
// 1. CMMatrix& mtxL - ���طֽ���L����
// 2. CMMatrix& mtxU - ���طֽ���U����
//
// ����ֵ��bool�ͣ�����Ƿ�ɹ�
//////////////////////////////////////////////////////////////////////
bool CMMatrix::SplitLU(CMMatrix& mtxL, CMMatrix& mtxU)
{ 
	int i,j,k,w,v,ll;
    
	// ��ʼ���������
	if (! mtxL.Init(m_nNumColumns, m_nNumColumns) ||
		! mtxU.Init(m_nNumColumns, m_nNumColumns))
		return false;

	for (k=0; k<=m_nNumColumns-2; k++)
    { 
		ll=k*m_nNumColumns+k;
		if (m_pData[ll] == 0.0)
			return false;

        for (i=k+1; i<=m_nNumColumns-1; i++)
		{ 
			w=i*m_nNumColumns+k; 
			m_pData[w]=m_pData[w]/m_pData[ll];
		}

        for (i=k+1; i<=m_nNumColumns-1; i++)
        { 
			w=i*m_nNumColumns+k;
            for (j=k+1; j<=m_nNumColumns-1; j++)
            { 
				v=i*m_nNumColumns+j;
                m_pData[v]=m_pData[v]-m_pData[w]*m_pData[k*m_nNumColumns+j];
            }
        }
    }
    
	for (i=0; i<=m_nNumColumns-1; i++)
    {
		for (j=0; j<i; j++)
        { 
			w=i*m_nNumColumns+j; 
			mtxL.m_pData[w]=m_pData[w]; 
			mtxU.m_pData[w]=0.0;
		}

        w=i*m_nNumColumns+i;
        mtxL.m_pData[w]=1.0; 
		mtxU.m_pData[w]=m_pData[w];
        
		for (j=i+1; j<=m_nNumColumns-1; j++)
        { 
			w=i*m_nNumColumns+j; 
			mtxL.m_pData[w]=0.0; 
			mtxU.m_pData[w]=m_pData[w];
		}
    }

	return true;
}

//////////////////////////////////////////////////////////////////////
// һ��ʵ�����QR�ֽ⣬�ֽ�ɹ���ԭ���󽫳�ΪR����
//
// ������
// 1. CMMatrix& mtxQ - ���طֽ���Q����
//
// ����ֵ��bool�ͣ�����Ƿ�ɹ�
//////////////////////////////////////////////////////////////////////
bool CMMatrix::SplitQR(CMMatrix& mtxQ)
{ 
	int i,j,k,l,nn,p,jj;
    double u,alpha,w,t;
    
	if (m_nNumRows < m_nNumColumns)
		return false;

	// ��ʼ��Q����
	if (! mtxQ.Init(m_nNumRows, m_nNumRows))
		return false;

	// �Խ���Ԫ�ص�λ��
    for (i=0; i<=m_nNumRows-1; i++)
	{
		for (j=0; j<=m_nNumRows-1; j++)
		{ 
			l=i*m_nNumRows+j; 
			mtxQ.m_pData[l]=0.0;
			if (i==j) 
				mtxQ.m_pData[l]=1.0;
		}
	}

	// ��ʼ�ֽ�

    nn=m_nNumColumns;
    if (m_nNumRows == m_nNumColumns) 
		nn=m_nNumRows-1;

    for (k=0; k<=nn-1; k++)
    { 
		u=0.0; 
		l=k*m_nNumColumns+k;
        for (i=k; i<=m_nNumRows-1; i++)
        { 
			w=fabs(m_pData[i*m_nNumColumns+k]);
            if (w>u) 
				u=w;
        }
        
		alpha=0.0;
        for (i=k; i<=m_nNumRows-1; i++)
        { 
			t=m_pData[i*m_nNumColumns+k]/u; 
			alpha=alpha+t*t;
		}

        if (m_pData[l]>0.0) 
			u=-u;

        alpha=u*sqrt(alpha);
        if (alpha == 0.0)
			return false;

        u=sqrt(2.0*alpha*(alpha-m_pData[l]));
        if ((u+1.0)!=1.0)
        { 
			m_pData[l]=(m_pData[l]-alpha)/u;
            for (i=k+1; i<=m_nNumRows-1; i++)
            { 
				p=i*m_nNumColumns+k; 
				m_pData[p]=m_pData[p]/u;
			}
            
			for (j=0; j<=m_nNumRows-1; j++)
            { 
				t=0.0;
                for (jj=k; jj<=m_nNumRows-1; jj++)
					t=t+m_pData[jj*m_nNumColumns+k]*mtxQ.m_pData[jj*m_nNumRows+j];

                for (i=k; i<=m_nNumRows-1; i++)
                { 
					p=i*m_nNumRows+j; 
					mtxQ.m_pData[p]=mtxQ.m_pData[p]-2.0*t*m_pData[i*m_nNumColumns+k];
				}
            }
            
			for (j=k+1; j<=m_nNumColumns-1; j++)
            { 
				t=0.0;
                
				for (jj=k; jj<=m_nNumRows-1; jj++)
					t=t+m_pData[jj*m_nNumColumns+k]*m_pData[jj*m_nNumColumns+j];
                
				for (i=k; i<=m_nNumRows-1; i++)
                { 
					p=i*m_nNumColumns+j; 
					m_pData[p]=m_pData[p]-2.0*t*m_pData[i*m_nNumColumns+k];
				}
            }
            
			m_pData[l]=alpha;
            for (i=k+1; i<=m_nNumRows-1; i++)
				m_pData[i*m_nNumColumns+k]=0.0;
        }
    }
    
	// ����Ԫ��
	for (i=0; i<=m_nNumRows-2; i++)
	{
		for (j=i+1; j<=m_nNumRows-1;j++)
		{ 
			p=i*m_nNumRows+j; 
			l=j*m_nNumRows+i;
			t=mtxQ.m_pData[p]; 
			mtxQ.m_pData[p]=mtxQ.m_pData[l]; 
			mtxQ.m_pData[l]=t;
		}
	}

	return true;
}

//////////////////////////////////////////////////////////////////////
// һ��ʵ���������ֵ�ֽ⣬�ֽ�ɹ���ԭ����Խ���Ԫ�ؾ��Ǿ��������ֵ
//
// ������
// 1. CMMatrix& mtxU - ���طֽ���U����
// 2. CMMatrix& mtxV - ���طֽ���V����,��������ΪAtA����������,�����Ϊ
//                    ��Ӧ��������ֵ��������λ��������
// 3. double eps - ���㾫�ȣ�Ĭ��ֵΪ0.000001
//
// ����ֵ��bool�ͣ�����Ƿ�ɹ�
//////////////////////////////////////////////////////////////////////
bool CMMatrix::SplitUV(CMMatrix& mtxU, CMMatrix& mtxV, double eps /*= 0.000001*/)
{ 
	int i,j,k,l,it,ll,kk,ix,iy,mm,nn,iz,m1,ks;
    double d,dd,t,sm,sm1,em1,sk,ek,b,c,shh,fg[2],cs[2];
    double *s,*e,*w;

	int m = m_nNumRows;
	int n = m_nNumColumns;

	// ��ʼ��U, V����
	if (! mtxU.Init(m, m) || ! mtxV.Init(n, n))
		return false;

	// ��ʱ������
	int ka = fmax(m, n) + 1;
    s = new double[ka];
    e = new double[ka];
    w = new double[ka];

	// ָ����������Ϊ60
    it=60; 
	k=n;

    if (m-1<n) 
		k=m-1;

    l=m;
    if (n-2<m) 
		l=n-2;
    if (l<0) 
		l=0;

	// ѭ����������
    ll=k;
    if (l>k) 
		ll=l;
    if (ll>=1)
    { 
		for (kk=1; kk<=ll; kk++)
        { 
			if (kk<=k)
            { 
				d=0.0;
                for (i=kk; i<=m; i++)
                { 
					ix=(i-1)*n+kk-1; 
					d=d+m_pData[ix]*m_pData[ix];
				}

                s[kk-1]=sqrt(d);
                if (s[kk-1]!=0.0)
                { 
					ix=(kk-1)*n+kk-1;
                    if (m_pData[ix]!=0.0)
                    { 
						s[kk-1]=fabs(s[kk-1]);
                        if (m_pData[ix]<0.0) 
							s[kk-1]=-s[kk-1];
                    }
                    
					for (i=kk; i<=m; i++)
                    { 
						iy=(i-1)*n+kk-1;
                        m_pData[iy]=m_pData[iy]/s[kk-1];
                    }
                    
					m_pData[ix]=1.0+m_pData[ix];
                }
                
				s[kk-1]=-s[kk-1];
            }
            
			if (n>=kk+1)
            { 
				for (j=kk+1; j<=n; j++)
                { 
					if ((kk<=k)&&(s[kk-1]!=0.0))
                    { 
						d=0.0;
                        for (i=kk; i<=m; i++)
                        { 
							ix=(i-1)*n+kk-1;
                            iy=(i-1)*n+j-1;
                            d=d+m_pData[ix]*m_pData[iy];
                        }
                        
						d=-d/m_pData[(kk-1)*n+kk-1];
                        for (i=kk; i<=m; i++)
                        { 
							ix=(i-1)*n+j-1;
                            iy=(i-1)*n+kk-1;
                            m_pData[ix]=m_pData[ix]+d*m_pData[iy];
                        }
                    }
                    
					e[j-1]=m_pData[(kk-1)*n+j-1];
                }
            }
            
			if (kk<=k)
            { 
				for (i=kk; i<=m; i++)
                { 
					ix=(i-1)*m+kk-1; 
					iy=(i-1)*n+kk-1;
                    mtxU.m_pData[ix]=m_pData[iy];
                }
            }
            
			if (kk<=l)
            { 
				d=0.0;
                for (i=kk+1; i<=n; i++)
					d=d+e[i-1]*e[i-1];
                
				e[kk-1]=sqrt(d);
                if (e[kk-1]!=0.0)
                { 
					if (e[kk]!=0.0)
                    { 
						e[kk-1]=fabs(e[kk-1]);
                        if (e[kk]<0.0) 
							e[kk-1]=-e[kk-1];
                    }

                    for (i=kk+1; i<=n; i++)
                      e[i-1]=e[i-1]/e[kk-1];
                    
					e[kk]=1.0+e[kk];
                }
                
				e[kk-1]=-e[kk-1];
                if ((kk+1<=m)&&(e[kk-1]!=0.0))
                { 
					for (i=kk+1; i<=m; i++) 
						w[i-1]=0.0;
                    
					for (j=kk+1; j<=n; j++)
						for (i=kk+1; i<=m; i++)
							w[i-1]=w[i-1]+e[j-1]*m_pData[(i-1)*n+j-1];
                    
					for (j=kk+1; j<=n; j++)
					{
						for (i=kk+1; i<=m; i++)
                        { 
							ix=(i-1)*n+j-1;
							m_pData[ix]=m_pData[ix]-w[i-1]*e[j-1]/e[kk];
                        }
					}
                }
                
				for (i=kk+1; i<=n; i++)
                  mtxV.m_pData[(i-1)*n+kk-1]=e[i-1];
            }
        }
    }
    
	mm=n;
    if (m+1<n) 
		mm=m+1;
    if (k<n) 
		s[k]=m_pData[k*n+k];
    if (m<mm) 
		s[mm-1]=0.0;
    if (l+1<mm) 
		e[l]=m_pData[l*n+mm-1];

    e[mm-1]=0.0;
    nn=m;
    if (m>n) 
		nn=n;
    if (nn>=k+1)
    { 
		for (j=k+1; j<=nn; j++)
        { 
			for (i=1; i<=m; i++)
				mtxU.m_pData[(i-1)*m+j-1]=0.0;
            mtxU.m_pData[(j-1)*m+j-1]=1.0;
        }
    }
    
	if (k>=1)
    { 
		for (ll=1; ll<=k; ll++)
        { 
			kk=k-ll+1; 
			iz=(kk-1)*m+kk-1;
            if (s[kk-1]!=0.0)
            { 
				if (nn>=kk+1)
				{
					for (j=kk+1; j<=nn; j++)
					{ 
						d=0.0;
						for (i=kk; i<=m; i++)
						{ 
							ix=(i-1)*m+kk-1;
							iy=(i-1)*m+j-1;
							d=d+mtxU.m_pData[ix]*mtxU.m_pData[iy]/mtxU.m_pData[iz];
						}

						d=-d;
						for (i=kk; i<=m; i++)
						{ 
							ix=(i-1)*m+j-1;
							iy=(i-1)*m+kk-1;
							mtxU.m_pData[ix]=mtxU.m_pData[ix]+d*mtxU.m_pData[iy];
						}
					}
				}
                  
				for (i=kk; i<=m; i++)
				{ 
					ix=(i-1)*m+kk-1; 
					mtxU.m_pData[ix]=-mtxU.m_pData[ix];
				}

				mtxU.m_pData[iz]=1.0+mtxU.m_pData[iz];
				if (kk-1>=1)
				{
					for (i=1; i<=kk-1; i++)
						mtxU.m_pData[(i-1)*m+kk-1]=0.0;
				}
			}
            else
            { 
				for (i=1; i<=m; i++)
					mtxU.m_pData[(i-1)*m+kk-1]=0.0;
                mtxU.m_pData[(kk-1)*m+kk-1]=1.0;
            }
		}
    }

    for (ll=1; ll<=n; ll++)
    { 
		kk=n-ll+1; 
		iz=kk*n+kk-1;
        
		if ((kk<=l)&&(e[kk-1]!=0.0))
        { 
			for (j=kk+1; j<=n; j++)
            { 
				d=0.0;
                for (i=kk+1; i<=n; i++)
                { 
					ix=(i-1)*n+kk-1; 
					iy=(i-1)*n+j-1;
                    d=d+mtxV.m_pData[ix]*mtxV.m_pData[iy]/mtxV.m_pData[iz];
                }
                
				d=-d;
                for (i=kk+1; i<=n; i++)
                { 
					ix=(i-1)*n+j-1; 
					iy=(i-1)*n+kk-1;
                    mtxV.m_pData[ix]=mtxV.m_pData[ix]+d*mtxV.m_pData[iy];
                }
            }
        }
        
		for (i=1; i<=n; i++)
			mtxV.m_pData[(i-1)*n+kk-1]=0.0;
        
		mtxV.m_pData[iz-n]=1.0;
    }
    
	for (i=1; i<=m; i++)
		for (j=1; j<=n; j++)
			m_pData[(i-1)*n+j-1]=0.0;
    
	m1=mm; 
	it=60;
    while (true)
    { 
		if (mm==0)
        { 
			ppp(m_pData,e,s,mtxV.m_pData,m,n);
			delete[] s;delete[] e;delete[] w;
            return true;
        }
        if (it==0)
        { 
			ppp(m_pData,e,s,mtxV.m_pData,m,n);
 			delete[] s;delete[] e;delete[] w;
			return false;
        }
        
		kk=mm-1;
		while ((kk!=0)&&(fabs(e[kk-1])!=0.0))
        { 
			d=fabs(s[kk-1])+fabs(s[kk]);
            dd=fabs(e[kk-1]);
            if (dd>eps*d) 
				kk=kk-1;
            else 
				e[kk-1]=0.0;
        }
        
		if (kk==mm-1)
        { 
			kk=kk+1;
            if (s[kk-1]<0.0)
            { 
				s[kk-1]=-s[kk-1];
                for (i=1; i<=n; i++)
                { 
					ix=(i-1)*n+kk-1; 
					mtxV.m_pData[ix]=-mtxV.m_pData[ix];}
				}
				
				while ((kk!=m1)&&(s[kk-1]<s[kk]))
				{ 
					d=s[kk-1]; 
					s[kk-1]=s[kk]; 
					s[kk]=d;
					if (kk<n)
					{
						for (i=1; i<=n; i++)
						{ 
							ix=(i-1)*n+kk-1; 
							iy=(i-1)*n+kk;
							d=mtxV.m_pData[ix]; 
							mtxV.m_pData[ix]=mtxV.m_pData[iy]; 
							mtxV.m_pData[iy]=d;
						}
					}

					if (kk<m)
					{
						for (i=1; i<=m; i++)
						{ 
							ix=(i-1)*m+kk-1; 
							iy=(i-1)*m+kk;
							d=mtxU.m_pData[ix]; 
							mtxU.m_pData[ix]=mtxU.m_pData[iy]; 
							mtxU.m_pData[iy]=d;
						}
					}

					kk=kk+1;
            }
            
			it=60;
            mm=mm-1;
        }
        else
        { 
			ks=mm;
            while ((ks>kk)&&(fabs(s[ks-1])!=0.0))
            { 
				d=0.0;
                if (ks!=mm) 
					d=d+fabs(e[ks-1]);
                if (ks!=kk+1) 
					d=d+fabs(e[ks-2]);
                
				dd=fabs(s[ks-1]);
                if (dd>eps*d) 
					ks=ks-1;
                else 
					s[ks-1]=0.0;
            }
            
			if (ks==kk)
            { 
				kk=kk+1;
                d=fabs(s[mm-1]);
                t=fabs(s[mm-2]);
                if (t>d) 
					d=t;
                
				t=fabs(e[mm-2]);
                if (t>d) 
					d=t;
                
				t=fabs(s[kk-1]);
                if (t>d) 
					d=t;
                
				t=fabs(e[kk-1]);
                if (t>d) 
					d=t;
                
				sm=s[mm-1]/d; 
				sm1=s[mm-2]/d;
                em1=e[mm-2]/d;
                sk=s[kk-1]/d; 
				ek=e[kk-1]/d;
                b=((sm1+sm)*(sm1-sm)+em1*em1)/2.0;
                c=sm*em1; 
				c=c*c; 
				shh=0.0;

                if ((b!=0.0)||(c!=0.0))
                { 
					shh=sqrt(b*b+c);
                    if (b<0.0) 
						shh=-shh;

                    shh=c/(b+shh);
                }
                
				fg[0]=(sk+sm)*(sk-sm)-shh;
                fg[1]=sk*ek;
                for (i=kk; i<=mm-1; i++)
                { 
					sss(fg,cs);
                    if (i!=kk) 
						e[i-2]=fg[0];

                    fg[0]=cs[0]*s[i-1]+cs[1]*e[i-1];
                    e[i-1]=cs[0]*e[i-1]-cs[1]*s[i-1];
                    fg[1]=cs[1]*s[i];
                    s[i]=cs[0]*s[i];

                    if ((cs[0]!=1.0)||(cs[1]!=0.0))
					{
						for (j=1; j<=n; j++)
                        { 
							ix=(j-1)*n+i-1;
							iy=(j-1)*n+i;
							d=cs[0]*mtxV.m_pData[ix]+cs[1]*mtxV.m_pData[iy];
							mtxV.m_pData[iy]=-cs[1]*mtxV.m_pData[ix]+cs[0]*mtxV.m_pData[iy];
							mtxV.m_pData[ix]=d;
                        }
					}

                    sss(fg,cs);
                    s[i-1]=fg[0];
                    fg[0]=cs[0]*e[i-1]+cs[1]*s[i];
                    s[i]=-cs[1]*e[i-1]+cs[0]*s[i];
                    fg[1]=cs[1]*e[i];
                    e[i]=cs[0]*e[i];

                    if (i<m)
					{
						if ((cs[0]!=1.0)||(cs[1]!=0.0))
						{
							for (j=1; j<=m; j++)
							{ 
								ix=(j-1)*m+i-1;
								iy=(j-1)*m+i;
								d=cs[0]*mtxU.m_pData[ix]+cs[1]*mtxU.m_pData[iy];
								mtxU.m_pData[iy]=-cs[1]*mtxU.m_pData[ix]+cs[0]*mtxU.m_pData[iy];
								mtxU.m_pData[ix]=d;
							}
						}
					}
                }
                
				e[mm-2]=fg[0];
                it=it-1;
            }
            else
            { 
				if (ks==mm)
                { 
					kk=kk+1;
                    fg[1]=e[mm-2]; 
					e[mm-2]=0.0;
                    for (ll=kk; ll<=mm-1; ll++)
                    { 
						i=mm+kk-ll-1;
                        fg[0]=s[i-1];
                        sss(fg,cs);
                        s[i-1]=fg[0];
                        if (i!=kk)
                        { 
							fg[1]=-cs[1]*e[i-2];
                            e[i-2]=cs[0]*e[i-2];
                        }
                        
						if ((cs[0]!=1.0)||(cs[1]!=0.0))
						{
							for (j=1; j<=n; j++)
                            { 
								ix=(j-1)*n+i-1;
								iy=(j-1)*n+mm-1;
								d=cs[0]*mtxV.m_pData[ix]+cs[1]*mtxV.m_pData[iy];
								mtxV.m_pData[iy]=-cs[1]*mtxV.m_pData[ix]+cs[0]*mtxV.m_pData[iy];
								mtxV.m_pData[ix]=d;
                            }
						}
                    }
                }
                else
                { 
					kk=ks+1;
                    fg[1]=e[kk-2];
                    e[kk-2]=0.0;
                    for (i=kk; i<=mm; i++)
                    { 
						fg[0]=s[i-1];
                        sss(fg,cs);
                        s[i-1]=fg[0];
                        fg[1]=-cs[1]*e[i-1];
                        e[i-1]=cs[0]*e[i-1];
                        if ((cs[0]!=1.0)||(cs[1]!=0.0))
						{
							for (j=1; j<=m; j++)
                            { 
								ix=(j-1)*m+i-1;
								iy=(j-1)*m+kk-2;
								d=cs[0]*mtxU.m_pData[ix]+cs[1]*mtxU.m_pData[iy];
								mtxU.m_pData[iy]=-cs[1]*mtxU.m_pData[ix]+cs[0]*mtxU.m_pData[iy];
								mtxU.m_pData[ix]=d;
                            }
						}
                    }
                }
            }
        }
    }
    
	// �����ڴ�
    delete[] s;delete[] e;delete[] w;

	return true;
}

//////////////////////////////////////////////////////////////////////
// �ڲ���������SplitUV��������
//////////////////////////////////////////////////////////////////////
void CMMatrix::ppp(double a[], double e[], double s[], double v[], int m, int n)
{ 
	int i,j,p,q;
    double d;

    if (m>=n) 
		i=n;
    else 
		i=m;

    for (j=1; j<=i-1; j++)
    { 
		a[(j-1)*n+j-1]=s[j-1];
        a[(j-1)*n+j]=e[j-1];
    }
    
	a[(i-1)*n+i-1]=s[i-1];
    if (m<n) 
		a[(i-1)*n+i]=e[i-1];
    
	for (i=1; i<=n-1; i++)
	{
		for (j=i+1; j<=n; j++)
		{ 
			p=(i-1)*n+j-1; 
			q=(j-1)*n+i-1;
			d=v[p]; 
			v[p]=v[q]; 
			v[q]=d;
		}
	}
}

//////////////////////////////////////////////////////////////////////
// �ڲ���������SplitUV��������
//////////////////////////////////////////////////////////////////////
void CMMatrix::sss(double fg[2], double cs[2])
{ 
	double r,d;
    
	if ((fabs(fg[0])+fabs(fg[1]))==0.0)
    { 
		cs[0]=1.0; 
		cs[1]=0.0; 
		d=0.0;
	}
    else 
    { 
		d=sqrt(fg[0]*fg[0]+fg[1]*fg[1]);
        if (fabs(fg[0])>fabs(fg[1]))
        { 
			d=fabs(d);
            if (fg[0]<0.0) 
				d=-d;
        }
        if (fabs(fg[1])>=fabs(fg[0]))
        { 
			d=fabs(d);
            if (fg[1]<0.0) 
				d=-d;
        }
        
		cs[0]=fg[0]/d; 
		cs[1]=fg[1]/d;
    }
    
	r=1.0;
    if (fabs(fg[0])>fabs(fg[1])) 
		r=cs[1];
    else if (cs[0]!=0.0) 
		r=1.0/cs[0];

    fg[0]=d; 
	fg[1]=r;
}

//////////////////////////////////////////////////////////////////////
// ������������ֵ�ֽⷨ���ֽ�ɹ���ԭ����Խ���Ԫ�ؾ��Ǿ��������ֵ
//
// ������
// 1. CMMatrix& mtxAP - ����ԭ����Ĺ��������
// 2. CMMatrix& mtxU - ���طֽ���U����
// 3. CMMatrix& mtxV - ���طֽ���V����
// 4. double eps - ���㾫�ȣ�Ĭ��ֵΪ0.000001
//
// ����ֵ��bool�ͣ�����Ƿ�ɹ�
//////////////////////////////////////////////////////////////////////
bool CMMatrix::GInvertUV(CMMatrix& mtxAP, CMMatrix& mtxU, CMMatrix& mtxV, double eps /*= 0.000001*/)
{ 
	int i,j,k,l,t,p,q,f;

	// ��������ֵ�ֽ�
    if (! SplitUV(mtxU, mtxV, eps))
		return false;

	int m = m_nNumRows;
	int n = m_nNumColumns;

	// ��ʼ�����������
	if (! mtxAP.Init(n, m))
		return false;

	// ������������

    j=n;
    if (m<n) 
		j=m;
    j=j-1;
    k=0;
    while ((k<=j)&&(m_pData[k*n+k]!=0.0)) 
		k=k+1;

    k=k-1;
    for (i=0; i<=n-1; i++)
	{
		for (j=0; j<=m-1; j++)
		{ 
			t=i*m+j;	
			mtxAP.m_pData[t]=0.0;
			for (l=0; l<=k; l++)
			{ 
				f=l*n+i; 
				p=j*m+l; 
				q=l*n+l;
				mtxAP.m_pData[t]=mtxAP.m_pData[t]+mtxV.m_pData[f]*mtxU.m_pData[p]/m_pData[q];
			}
		}
	}

    return true;
}

//////////////////////////////////////////////////////////////////////
// Լ���Գƾ���Ϊ�Գ����Խ���ĺ�˹�ɶ��±任��
//
// ������
// 1. CMMatrix& mtxQ - ���غ�˹�ɶ��±任�ĳ˻�����Q
// 2. CMMatrix& mtxT - ������õĶԳ����Խ���
// 3. double dblB[] - һά���飬����Ϊ����Ľ��������ضԳ����Խ�������Խ���Ԫ��
// 4. double dblC[] - һά���飬����Ϊ����Ľ�����ǰn-1��Ԫ�ط��ضԳ����Խ���ĴζԽ���Ԫ��
//
// ����ֵ��bool�ͣ�����Ƿ�ɹ�
//////////////////////////////////////////////////////////////////////
bool CMMatrix::MakeSymTri(CMMatrix& mtxQ, CMMatrix& mtxT, double dblB[], double dblC[])
{ 
	int i,j,k,u;
    double h,f,g,h2;
    
	// ��ʼ������Q��T
	if (! mtxQ.Init(m_nNumColumns, m_nNumColumns) ||
		! mtxT.Init(m_nNumColumns, m_nNumColumns))
		return false;

	if (dblB == NULL || dblC == NULL)
		return false;

	for (i=0; i<=m_nNumColumns-1; i++)
	{
		for (j=0; j<=m_nNumColumns-1; j++)
		{ 
			u=i*m_nNumColumns+j; 
			mtxQ.m_pData[u]=m_pData[u];
		}
	}

    for (i=m_nNumColumns-1; i>=1; i--)
    { 
		h=0.0;
        if (i>1)
		{
			for (k=0; k<=i-1; k++)
            { 
				u=i*m_nNumColumns+k; 
				h=h+mtxQ.m_pData[u]*mtxQ.m_pData[u];
			}
		}

        if (h == 0.0)
        { 
			dblC[i]=0.0;
            if (i==1) 
				dblC[i]=mtxQ.m_pData[i*m_nNumColumns+i-1];
            dblB[i]=0.0;
        }
        else
        { 
			dblC[i]=sqrt(h);
            u=i*m_nNumColumns+i-1;
            if (mtxQ.m_pData[u]>0.0) 
				dblC[i]=-dblC[i];

            h=h-mtxQ.m_pData[u]*dblC[i];
            mtxQ.m_pData[u]=mtxQ.m_pData[u]-dblC[i];
            f=0.0;
            for (j=0; j<=i-1; j++)
            { 
				mtxQ.m_pData[j*m_nNumColumns+i]=mtxQ.m_pData[i*m_nNumColumns+j]/h;
                g=0.0;
                for (k=0; k<=j; k++)
					g=g+mtxQ.m_pData[j*m_nNumColumns+k]*mtxQ.m_pData[i*m_nNumColumns+k];

				if (j+1<=i-1)
					for (k=j+1; k<=i-1; k++)
						g=g+mtxQ.m_pData[k*m_nNumColumns+j]*mtxQ.m_pData[i*m_nNumColumns+k];

                dblC[j]=g/h;
                f=f+g*mtxQ.m_pData[j*m_nNumColumns+i];
            }
            
			h2=f/(h+h);
            for (j=0; j<=i-1; j++)
            { 
				f=mtxQ.m_pData[i*m_nNumColumns+j];
                g=dblC[j]-h2*f;
                dblC[j]=g;
                for (k=0; k<=j; k++)
                { 
					u=j*m_nNumColumns+k;
                    mtxQ.m_pData[u]=mtxQ.m_pData[u]-f*dblC[k]-g*mtxQ.m_pData[i*m_nNumColumns+k];
                }
            }
            
			dblB[i]=h;
        }
    }
    
	for (i=0; i<=m_nNumColumns-2; i++) 
		dblC[i]=dblC[i+1];
    
	dblC[m_nNumColumns-1]=0.0;
    dblB[0]=0.0;
    for (i=0; i<=m_nNumColumns-1; i++)
    { 
		if ((dblB[i]!=0.0)&&(i-1>=0))
		{
			for (j=0; j<=i-1; j++)
            { 
				g=0.0;
				for (k=0; k<=i-1; k++)
					g=g+mtxQ.m_pData[i*m_nNumColumns+k]*mtxQ.m_pData[k*m_nNumColumns+j];

				for (k=0; k<=i-1; k++)
                { 
					u=k*m_nNumColumns+j;
					mtxQ.m_pData[u]=mtxQ.m_pData[u]-g*mtxQ.m_pData[k*m_nNumColumns+i];
                }
            }
		}

        u=i*m_nNumColumns+i;
        dblB[i]=mtxQ.m_pData[u]; mtxQ.m_pData[u]=1.0;
        if (i-1>=0)
		{
			for (j=0; j<=i-1; j++)
            { 
				mtxQ.m_pData[i*m_nNumColumns+j]=0.0; 
				mtxQ.m_pData[j*m_nNumColumns+i]=0.0;
			}
		}
    }

    // ����Գ����ԽǾ���
    for (i=0; i<m_nNumColumns; ++i)
	{
	    for (j=0; j<m_nNumColumns; ++j)
		{
            mtxT.SetElement(i, j, 0);
            k = i - j;
            if (k == 0) 
	            mtxT.SetElement(i, j, dblB[j]);
			else if (k == 1)
	            mtxT.SetElement(i, j, dblC[j]);
			else if (k == -1)
	            mtxT.SetElement(i, j, dblC[i]);
        }
    }

	return true;
}

//////////////////////////////////////////////////////////////////////
// ʵ�Գ����Խ����ȫ������ֵ�����������ļ���
//
// ������
// 1. double dblB[] - һά���飬����Ϊ����Ľ���������Գ����Խ�������Խ���Ԫ�أ�
//    ����ʱ���ȫ������ֵ��
// 2. double dblC[] - һά���飬����Ϊ����Ľ�����ǰn-1��Ԫ�ش���Գ����Խ���ĴζԽ���Ԫ��
// 3. CMMatrix& mtxQ - ������뵥λ�����򷵻�ʵ�Գ����Խ��������ֵ��������
//    �������MakeSymTri������õľ���A�ĺ�˹�ɶ��±任�ĳ˻�����Q���򷵻ؾ���A��
//    ����ֵ�����������е�i��Ϊ������dblB�е�j������ֵ��Ӧ������������
// 4. int nMaxIt - ����������Ĭ��ֵΪ60
// 5. double eps - ���㾫�ȣ�Ĭ��ֵΪ0.000001
//
// ����ֵ��bool�ͣ�����Ƿ�ɹ�
//////////////////////////////////////////////////////////////////////
bool CMMatrix::SymTriEigenv(double dblB[], double dblC[], CMMatrix& mtxQ, int nMaxIt /*= 60*/, double eps /*= 0.000001*/)
{
	int i,j,k,m,it,u,v;
    double d,f,h,g,p,r,e,s;
    
	// ��ֵ
	int n = mtxQ.GetNumColumns();
	dblC[n-1]=0.0; 
	d=0.0; 
	f=0.0;
    
	// ��������

	for (j=0; j<=n-1; j++)
    { 
		it=0;
        h=eps*(fabs(dblB[j])+fabs(dblC[j]));
        if (h>d) 
			d=h;
        
		m=j;
        while ((m<=n-1)&&(fabs(dblC[m])>d)) 
			m=m+1;
        
		if (m!=j)
        { 
			do
            { 
				if (it==nMaxIt)
					return false;

                it=it+1;
                g=dblB[j];
                p=(dblB[j+1]-g)/(2.0*dblC[j]);
                r=sqrt(p*p+1.0);
                if (p>=0.0) 
					dblB[j]=dblC[j]/(p+r);
                else 
					dblB[j]=dblC[j]/(p-r);
                
				h=g-dblB[j];
                for (i=j+1; i<=n-1; i++)
					dblB[i]=dblB[i]-h;
                
				f=f+h; 
				p=dblB[m]; 
				e=1.0; 
				s=0.0;
                for (i=m-1; i>=j; i--)
                { 
					g=e*dblC[i]; 
					h=e*p;
                    if (fabs(p)>=fabs(dblC[i]))
                    { 
						e=dblC[i]/p; 
						r=sqrt(e*e+1.0);
                        dblC[i+1]=s*p*r; 
						s=e/r; 
						e=1.0/r;
                    }
                    else
					{ 
						e=p/dblC[i]; 
						r=sqrt(e*e+1.0);
                        dblC[i+1]=s*dblC[i]*r;
                        s=1.0/r; 
						e=e/r;
                    }
                    
					p=e*dblB[i]-s*g;
                    dblB[i+1]=h+s*(e*g+s*dblB[i]);
                    for (k=0; k<=n-1; k++)
                    { 
						u=k*n+i+1; 
						v=u-1;
                        h=mtxQ.m_pData[u]; 
						mtxQ.m_pData[u]=s*mtxQ.m_pData[v]+e*h;
                        mtxQ.m_pData[v]=e*mtxQ.m_pData[v]-s*h;
                    }
                }
                
				dblC[j]=s*p; 
				dblB[j]=e*p;
            
			} while (fabs(dblC[j])>d);
        }
        
		dblB[j]=dblB[j]+f;
    }
    
	for (i=0; i<=n-1; i++)
    { 
		k=i; 
		p=dblB[i];
        if (i+1<=n-1)
        { 
			j=i+1;
            while ((j<=n-1)&&(dblB[j]<=p))
            { 
				k=j; 
				p=dblB[j]; 
				j=j+1;
			}
        }

        if (k!=i)
        { 
			dblB[k]=dblB[i]; 
			dblB[i]=p;
            for (j=0; j<=n-1; j++)
            { 
				u=j*n+i; 
				v=j*n+k;
                p=mtxQ.m_pData[u]; 
				mtxQ.m_pData[u]=mtxQ.m_pData[v]; 
				mtxQ.m_pData[v]=p;
            }
        }
    }
    
	return true;
}

//////////////////////////////////////////////////////////////////////
// Լ��һ��ʵ����Ϊ���겮�����ĳ������Ʊ任��
//
// ��������
//
// ����ֵ����
//////////////////////////////////////////////////////////////////////
void CMMatrix::MakeHberg()
{ 
	int i,j,k,u,v;
    double d,t;

    for (k=1; k<=m_nNumColumns-2; k++)
    { 
		d=0.0;
        for (j=k; j<=m_nNumColumns-1; j++)
        { 
			u=j*m_nNumColumns+k-1; 
			t=m_pData[u];
            if (fabs(t)>fabs(d))
            { 
				d=t; 
				i=j;
			}
        }
        
		if (d != 0.0)
        { 
			if (i!=k)
            { 
				for (j=k-1; j<=m_nNumColumns-1; j++)
                { 
					u=i*m_nNumColumns+j; 
					v=k*m_nNumColumns+j;
                    t=m_pData[u]; 
					m_pData[u]=m_pData[v]; 
					m_pData[v]=t;
                }
                
				for (j=0; j<=m_nNumColumns-1; j++)
                { 
					u=j*m_nNumColumns+i; 
					v=j*m_nNumColumns+k;
                    t=m_pData[u]; 
					m_pData[u]=m_pData[v]; 
					m_pData[v]=t;
                }
            }
            
			for (i=k+1; i<=m_nNumColumns-1; i++)
            { 
				u=i*m_nNumColumns+k-1; 
				t=m_pData[u]/d; 
				m_pData[u]=0.0;
                for (j=k; j<=m_nNumColumns-1; j++)
                { 
					v=i*m_nNumColumns+j;
                    m_pData[v]=m_pData[v]-t*m_pData[k*m_nNumColumns+j];
                }
                
				for (j=0; j<=m_nNumColumns-1; j++)
                { 
					v=j*m_nNumColumns+k;
                    m_pData[v]=m_pData[v]+t*m_pData[j*m_nNumColumns+i];
                }
            }
        }
    }
}

//////////////////////////////////////////////////////////////////////
// ����겮�����ȫ������ֵ��QR����
//
// ������
// 1. double dblU[] - һά���飬����Ϊ����Ľ���������ʱ�������ֵ��ʵ��
// 2. double dblV[] - һά���飬����Ϊ����Ľ���������ʱ�������ֵ���鲿
// 3. int nMaxIt - ����������Ĭ��ֵΪ60
// 4. double eps - ���㾫�ȣ�Ĭ��ֵΪ0.000001
//
// ����ֵ��bool�ͣ�����Ƿ�ɹ�
//////////////////////////////////////////////////////////////////////
bool CMMatrix::HBergEigenv(double dblU[], double dblV[], int nMaxIt /*= 60*/, double eps /*= 0.000001*/)
{ 
	int m,it,i,j,k,l,ii,jj,kk,ll;
    double b,c,w,g,xy,p,q,r,x,s,e,f,z,y;
    
	int n = m_nNumColumns;

	it=0; 
	m=n;
    while (m!=0)
    { 
		l=m-1;
        while ((l>0)&&(fabs(m_pData[l*n+l-1]) > 
				eps*(fabs(m_pData[(l-1)*n+l-1])+fabs(m_pData[l*n+l])))) 
		  l=l-1;

        ii=(m-1)*n+m-1; 
		jj=(m-1)*n+m-2;
        kk=(m-2)*n+m-1; 
		ll=(m-2)*n+m-2;
        if (l==m-1)
        { 
			dblU[m-1]=m_pData[(m-1)*n+m-1]; 
			dblV[m-1]=0.0;
            m=m-1; 
			it=0;
        }
        else if (l==m-2)
        { 
			b=-(m_pData[ii]+m_pData[ll]);
            c=m_pData[ii]*m_pData[ll]-m_pData[jj]*m_pData[kk];
            w=b*b-4.0*c;
            y=sqrt(fabs(w));
            if (w>0.0)
            { 
				xy=1.0;
                if (b<0.0) 
					xy=-1.0;
                dblU[m-1]=(-b-xy*y)/2.0;
                dblU[m-2]=c/dblU[m-1];
                dblV[m-1]=0.0; dblV[m-2]=0.0;
            }
            else
            { 
				dblU[m-1]=-b/2.0; 
				dblU[m-2]=dblU[m-1];
                dblV[m-1]=y/2.0; 
				dblV[m-2]=-dblV[m-1];
            }
            
			m=m-2; 
			it=0;
        }
        else
        { 
			if (it>=nMaxIt)
				return false;

            it=it+1;
            for (j=l+2; j<=m-1; j++)
				m_pData[j*n+j-2]=0.0;
            for (j=l+3; j<=m-1; j++)
				m_pData[j*n+j-3]=0.0;
            for (k=l; k<=m-2; k++)
            { 
				if (k!=l)
                { 
					p=m_pData[k*n+k-1]; 
					q=m_pData[(k+1)*n+k-1];
                    r=0.0;
                    if (k!=m-2) 
						r=m_pData[(k+2)*n+k-1];
                }
                else
                { 
					x=m_pData[ii]+m_pData[ll];
                    y=m_pData[ll]*m_pData[ii]-m_pData[kk]*m_pData[jj];
                    ii=l*n+l; 
					jj=l*n+l+1;
                    kk=(l+1)*n+l; 
					ll=(l+1)*n+l+1;
                    p=m_pData[ii]*(m_pData[ii]-x)+m_pData[jj]*m_pData[kk]+y;
                    q=m_pData[kk]*(m_pData[ii]+m_pData[ll]-x);
                    r=m_pData[kk]*m_pData[(l+2)*n+l+1];
                }
                
				if ((fabs(p)+fabs(q)+fabs(r))!=0.0)
                { 
					xy=1.0;
                    if (p<0.0) 
						xy=-1.0;
                    s=xy*sqrt(p*p+q*q+r*r);
                    if (k!=l) 
						m_pData[k*n+k-1]=-s;
                    e=-q/s; 
					f=-r/s; 
					x=-p/s;
                    y=-x-f*r/(p+s);
                    g=e*r/(p+s);
                    z=-x-e*q/(p+s);
                    for (j=k; j<=m-1; j++)
                    { 
						ii=k*n+j; 
						jj=(k+1)*n+j;
                        p=x*m_pData[ii]+e*m_pData[jj];
                        q=e*m_pData[ii]+y*m_pData[jj];
                        r=f*m_pData[ii]+g*m_pData[jj];
                        if (k!=m-2)
                        { 
							kk=(k+2)*n+j;
                            p=p+f*m_pData[kk];
                            q=q+g*m_pData[kk];
                            r=r+z*m_pData[kk]; 
							m_pData[kk]=r;
                        }
                        
						m_pData[jj]=q; m_pData[ii]=p;
                    }
                    
					j=k+3;
                    if (j>=m-1) 
						j=m-1;
                    
					for (i=l; i<=j; i++)
                    { 
						ii=i*n+k; 
						jj=i*n+k+1;
                        p=x*m_pData[ii]+e*m_pData[jj];
                        q=e*m_pData[ii]+y*m_pData[jj];
                        r=f*m_pData[ii]+g*m_pData[jj];
                        if (k!=m-2)
                        { 
							kk=i*n+k+2;
                            p=p+f*m_pData[kk];
                            q=q+g*m_pData[kk];
                            r=r+z*m_pData[kk]; 
							m_pData[kk]=r;
                        }
                        
						m_pData[jj]=q; 
						m_pData[ii]=p;
                    }
                }
            }
        }
    }
    
	return true;
}

//////////////////////////////////////////////////////////////////////
// ��ʵ�Գƾ�������ֵ�������������ſɱȷ�
//
// ������
// 1. double dblEigenValue[] - һά���飬����Ϊ����Ľ���������ʱ���
// 2. CMMatrix& mtxEigenVector - ����ʱ������������������е�i��Ϊ��
//    ����ֵ����dblEigenValue�е�i������ֵ��Ӧ����������
// 3. int nMaxIt - ����������Ĭ��ֵΪ60
// 4. double eps - ���㾫�ȣ�Ĭ��ֵΪ0.000001
//
// ����ֵ��bool�ͣ�����Ƿ�ɹ�
//////////////////////////////////////////////////////////////////////
bool CMMatrix::JacobiEigenv(double dblEigenValue[], CMMatrix& mtxEigenVector, int nMaxIt /*= 60*/, double eps /*= 0.000001*/)
{ 
	int i,j,p,q,u,w,t,s,l;
    double fm,cn,sn,omega,x,y,d;
    
	if (! mtxEigenVector.Init(m_nNumColumns, m_nNumColumns))
		return false;

	l=1;
    for (i=0; i<=m_nNumColumns-1; i++)
    { 
		mtxEigenVector.m_pData[i*m_nNumColumns+i]=1.0;
        for (j=0; j<=m_nNumColumns-1; j++)
			if (i!=j) 
				mtxEigenVector.m_pData[i*m_nNumColumns+j]=0.0;
    }
    
	while (true)
    { 
		fm=0.0;
        for (i=1; i<=m_nNumColumns-1; i++)
		{
			for (j=0; j<=i-1; j++)
			{ 
				d=fabs(m_pData[i*m_nNumColumns+j]);
				if ((i!=j)&&(d>fm))
				{ 
					fm=d; 
					p=i; 
					q=j;
				}
			}
		}

        if (fm<eps)
		{
			for (i=0; i<m_nNumColumns; ++i)
				dblEigenValue[i] = GetElement(i,i);
			return true;
		}

        if (l>nMaxIt)  
			return false;
        
		l=l+1;
        u=p*m_nNumColumns+q; 
		w=p*m_nNumColumns+p; 
		t=q*m_nNumColumns+p; 
		s=q*m_nNumColumns+q;
        x=-m_pData[u]; 
		y=(m_pData[s]-m_pData[w])/2.0;
        omega=x/sqrt(x*x+y*y);

        if (y<0.0) 
			omega=-omega;

        sn=1.0+sqrt(1.0-omega*omega);
        sn=omega/sqrt(2.0*sn);
        cn=sqrt(1.0-sn*sn);
        fm=m_pData[w];
        m_pData[w]=fm*cn*cn+m_pData[s]*sn*sn+m_pData[u]*omega;
        m_pData[s]=fm*sn*sn+m_pData[s]*cn*cn-m_pData[u]*omega;
        m_pData[u]=0.0; 
		m_pData[t]=0.0;
        for (j=0; j<=m_nNumColumns-1; j++)
		{
			if ((j!=p)&&(j!=q))
			{ 
				u=p*m_nNumColumns+j; w=q*m_nNumColumns+j;
				fm=m_pData[u];
				m_pData[u]=fm*cn+m_pData[w]*sn;
				m_pData[w]=-fm*sn+m_pData[w]*cn;
			}
		}

        for (i=0; i<=m_nNumColumns-1; i++)
		{
			if ((i!=p)&&(i!=q))
            { 
				u=i*m_nNumColumns+p; 
				w=i*m_nNumColumns+q;
				fm=m_pData[u];
				m_pData[u]=fm*cn+m_pData[w]*sn;
				m_pData[w]=-fm*sn+m_pData[w]*cn;
            }
		}

        for (i=0; i<=m_nNumColumns-1; i++)
        { 
			u=i*m_nNumColumns+p; 
			w=i*m_nNumColumns+q;
            fm=mtxEigenVector.m_pData[u];
            mtxEigenVector.m_pData[u]=fm*cn+mtxEigenVector.m_pData[w]*sn;
            mtxEigenVector.m_pData[w]=-fm*sn+mtxEigenVector.m_pData[w]*cn;
        }
    }
    
	for (i=0; i<m_nNumColumns; ++i)
		dblEigenValue[i] = GetElement(i,i);

	return true;
}

//////////////////////////////////////////////////////////////////////
// ��ʵ�Գƾ�������ֵ�������������ſɱȹ��ط�
//
// ������
// 1. double dblEigenValue[] - һά���飬����Ϊ����Ľ���������ʱ�������ֵ
// 2. CMMatrix& mtxEigenVector - ����ʱ������������������е�i��Ϊ��
//    ����dblEigenValue�е�j������ֵ��Ӧ����������
// 3. double eps - ���㾫�ȣ�Ĭ��ֵΪ0.000001
//
// ����ֵ��bool�ͣ�����Ƿ�ɹ�
//////////////////////////////////////////////////////////////////////
bool CMMatrix::JacobiEigenv2(double dblEigenValue[], CMMatrix& mtxEigenVector, double eps /*= 0.000001*/)
{ 
	int i,j,p,q,u,w,t,s;
    double ff,fm,cn,sn,omega,x,y,d;
    
	if (! mtxEigenVector.Init(m_nNumColumns, m_nNumColumns))
		return false;

	for (i=0; i<=m_nNumColumns-1; i++)
    { 
		mtxEigenVector.m_pData[i*m_nNumColumns+i]=1.0;
        for (j=0; j<=m_nNumColumns-1; j++)
			if (i!=j) 
				mtxEigenVector.m_pData[i*m_nNumColumns+j]=0.0;
    }
    
	ff=0.0;
    for (i=1; i<=m_nNumColumns-1; i++)
	{
		for (j=0; j<=i-1; j++)
		{ 
			d=m_pData[i*m_nNumColumns+j]; 
			ff=ff+d*d; 
		}
	}

    ff=sqrt(2.0*ff);

Loop_0:
    
	ff=ff/(1.0*m_nNumColumns);

Loop_1:

    for (i=1; i<=m_nNumColumns-1; i++)
	{
		for (j=0; j<=i-1; j++)
        { 
			d=fabs(m_pData[i*m_nNumColumns+j]);
            if (d>ff)
            { 
				p=i; 
				q=j;
                goto Loop_2;
            }
        }
	}
        
	if (ff<eps) 
	{
		for (i=0; i<m_nNumColumns; ++i)
			dblEigenValue[i] = GetElement(i,i);
		return true;
	}
    
	goto Loop_0;

Loop_2: 
		
	u=p*m_nNumColumns+q; 
	w=p*m_nNumColumns+p; 
	t=q*m_nNumColumns+p; 
	s=q*m_nNumColumns+q;
    x=-m_pData[u]; 
	y=(m_pData[s]-m_pData[w])/2.0;
    omega=x/sqrt(x*x+y*y);
    if (y<0.0) 
		omega=-omega;
    
	sn=1.0+sqrt(1.0-omega*omega);
    sn=omega/sqrt(2.0*sn);
    cn=sqrt(1.0-sn*sn);
    fm=m_pData[w];
    m_pData[w]=fm*cn*cn+m_pData[s]*sn*sn+m_pData[u]*omega;
    m_pData[s]=fm*sn*sn+m_pData[s]*cn*cn-m_pData[u]*omega;
    m_pData[u]=0.0; m_pData[t]=0.0;
    
	for (j=0; j<=m_nNumColumns-1; j++)
	{
		if ((j!=p)&&(j!=q))
		{ 
			u=p*m_nNumColumns+j; 
			w=q*m_nNumColumns+j;
			fm=m_pData[u];
			m_pData[u]=fm*cn+m_pData[w]*sn;
			m_pData[w]=-fm*sn+m_pData[w]*cn;
		}
	}

    for (i=0; i<=m_nNumColumns-1; i++)
    {
		if ((i!=p)&&(i!=q))
        { 
			u=i*m_nNumColumns+p; 
			w=i*m_nNumColumns+q;
			fm=m_pData[u];
			m_pData[u]=fm*cn+m_pData[w]*sn;
			m_pData[w]=-fm*sn+m_pData[w]*cn;
        }
	}
    
	for (i=0; i<=m_nNumColumns-1; i++)
    { 
		u=i*m_nNumColumns+p; 
		w=i*m_nNumColumns+q;
        fm=mtxEigenVector.m_pData[u];
        mtxEigenVector.m_pData[u]=fm*cn+mtxEigenVector.m_pData[w]*sn;
        mtxEigenVector.m_pData[w]=-fm*sn+mtxEigenVector.m_pData[w]*cn;
	}

	goto Loop_1;
}

//////////////////////////////////////////////////////////////////////
// ������Frobeniusģ
//
// ������
// ��
//
// ����ֵ��double�ͣ�����Frobeniusģ
//////////////////////////////////////////////////////////////////////
double CMMatrix::FrobeniusNorm()
{
	int i,j;
	double dNorm=0;

	for (i=0;i<m_nNumRows;i++)
		for (j=0;j<m_nNumColumns;j++)
			dNorm+=m_pData[i*m_nNumColumns+j]*m_pData[i*m_nNumColumns+j];
	
	dNorm = sqrt(dNorm);

	return dNorm;
}

//////////////////////////////////////////////////////////////////////
// �����ĸ�����
//
// ������
// ��
//
// ����ֵ��CMMatrix�ͣ����ص�ǰ����ķ��ž���
//////////////////////////////////////////////////////////////////////
CMMatrix CMMatrix::Negative()
{
	// ����Ŀ�����
	CMMatrix	result(m_nNumRows,m_nNumColumns) ;	 

	return result-(*this);
}

//////////////////////////////////////////////////////////////////////
// �Ծ������������
//
// ������
// ��
//
// ����ֵ��CMMatrix���ص�ǰ������������ľ���
//////////////////////////////////////////////////////////////////////
CMMatrix CMMatrix::Orthogonal()
{
	CMMatrix	result(m_nNumRows,m_nNumColumns) ;	 


	return result;
}
