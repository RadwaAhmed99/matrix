#include "matrix.h"

using namespace std;

void cpyData(valarray<int>&, const valarray<int>&);
valarray<int> data;
int row, col;

Matrix::Matrix() //default constructor
{
}

Matrix::Matrix(const Matrix& mat)
{
    row = mat.row;
    col = mat.col;
    cpyData(data, mat.data);
}

Matrix::Matrix(int r, int c, int num[])  //parameterize constructor
{
    row = r;
    col = c;
    data.resize (row * col);
    for (int i = 0; i < row * col; i++)
        data [i] = num [i];
}

Matrix::Matrix(int r, int c, valarray<int>& myData) //parameterize constructor
{
    row = r;
    col = c;
    data = myData;
}
/*mutator member functions used to change data members*/
void Matrix::setRow (int r)
{
    row = r;
}
void Matrix::setCol (int c)
{
    col = c;
}
void Matrix::setData(int d[], int arr_sz)
{

    if(arr_sz == row*col)
        for(int i=0; i < row * col; i++)
            data[i] = d[i];

    else
        cout << "Size Error!!\n";
}
/*accessor member functions used to read the data*/
int Matrix::getRow ()
{
    return row;
}

int Matrix::getCol()
{
    return col;
}

int Matrix::getData(int idx)
{
    return data[idx];
}

Matrix Matrix::operator+ (Matrix& mat)  //add two matrix if they have the same dimensions
{
    if(mat.getRow() != row || mat.getCol() != col)
    {
        cout << "Size Error!!\n";
        Matrix ret(row, col, data);
        return ret;
    }

    Matrix ret;
    ret.setRow(row);
    ret.setCol(col);
    ret.data.resize(ret.row * ret.col);
    for(int i=0; i < row * col; i++)
    {
        ret.data[i] = data[i] + mat.getData(i);
    }

    return ret;
}

Matrix Matrix::operator- (Matrix& mat)  //subtract two matrix if they have the same dimensions
{
    if(mat.getRow() != row || mat.getCol() != col)
    {
        cout << "Size Error!!\n";
        Matrix ret(row, col, data);
        return ret;
    }

    Matrix ret;
    ret.setRow(row);
    ret.setCol(col);
    ret.data.resize(ret.row * ret.col);

    for(int i=0; i < row * col; i++)
    {
        ret.data[i] = data[i] - mat.getData(i);
    }

    return ret;
}

Matrix Matrix::operator*  (Matrix& mat)  //multiply two matrix if column in the first matrix equal row in the second one
{
    if(mat.getRow() != col)
    {
        cout << "Size Error!!\n";
        Matrix ret(row, col, data);
        return ret;
    }
    Matrix ret;
    ret.setRow(row);
    ret.setCol(mat.col);
    ret.data.resize(ret.row * ret.col);

    int sum = 0;
    int cnt = 0;
    for(int l = 0; l < row; l++)
    {
        for(int j = 0; j < mat.col; j++)
        {
            int col_ctr = j;
            for(int k = 0; k < col; k++)
            {
                sum += data[k + l * col] * mat.data[col_ctr];
                col_ctr += mat.col;
                if(k == col - 1)
                {
                    ret.data[cnt] = sum;
                    sum = 0;
                    cnt++;
                }
            }
        }
    }
    return ret;
}

Matrix Matrix::operator+ (int scalar)  //add matrix to a number
{
    Matrix ret;
    ret.setRow(row);
    ret.setCol(col);
    ret.data.resize(ret.row * ret.col);
    for(int i = 0; i < row * col; i++)
    {
        ret.data[i] = data[i] + scalar;
    }
    return ret;
}

Matrix Matrix::operator- (int scalar) //subtract matrix to a number
{
    Matrix ret;
    ret.setRow(row);
    ret.setCol(col);
    ret.data.resize(ret.row * ret.col);
    for(int i = 0; i < row * col; i++)
    {
        ret.data[i] = data[i] - scalar;
    }
    return ret;
}

Matrix Matrix::operator* (int scalar)  //multiply matrix to a number
{
    Matrix ret;
    ret.setRow(row);
    ret.setCol(col);
    ret.data.resize(ret.row * ret.col);
    for(int i = 0; i < row * col; i++)
    {
        ret.data[i] = data[i] * scalar;
    }
    return ret;
}

Matrix Matrix::operator+= (Matrix& mat)  //add two matrices if they have the same dimension and return the answer in the first one
{
    if(mat.getRow() != row || mat.getCol() != col)
    {
        cout << "Size Error!!\n";
        Matrix ret(row, col, data);
        return ret;
    }
    Matrix ret;
    ret.setRow(row);
    ret.setCol(col);
    ret.data.resize(ret.row * ret.col);

    for(int i=0; i < row * col; i++)
    {
        ret.data[i] = data[i] + mat.getData(i);
        data [i] = ret.data [i];
    }

    return *this;
}

Matrix Matrix::operator-= (Matrix& mat)  //subtract two matrices if they have the same dimension and return the answer in the first one
{
    if(mat.getRow() != row || mat.getCol() != col)
    {
        cout << "Size Error!!\n";
        Matrix ret(row, col, data);
        return ret;
    }
    Matrix ret;
    ret.setRow(row);
    ret.setCol(col);
    ret.data.resize(ret.row * ret.col);

    for(int i=0; i < row * col; i++)
    {
        ret.data[i] = data[i] - mat.getData(i);
        data [i] = ret.data [i];
    }

    return *this;
}
Matrix Matrix::operator+= (int scalar) //add a matrix to number and return the answer in the same matrix
{
    Matrix ret;
    ret.setRow(row);
    ret.setCol(col);
    ret.data.resize(ret.row * ret.col);
    for(int i = 0; i < row * col; i++)
    {
        ret.data[i] = data[i] + scalar;
        data [i] = ret.data [i];
    }
    return *this;
}
Matrix Matrix::operator-= (int scalar)  //subtract a matrix to number and return the answer in the same matrix
{
    Matrix ret;
    ret.setRow(row);
    ret.setCol(col);
    ret.data.resize(ret.row * ret.col);
    for(int i = 0; i < row * col; i++)
    {
        ret.data[i] = data[i] - scalar;
        data [i] = ret.data [i];
    }
    return *this;
}

void Matrix::operator++()  // Add 1 to each element in the matrix
{
    Matrix mat;
    mat.setRow(row);
    mat.setCol(col);
    mat.data.resize(mat.row * mat.col);
    for(int i = 0; i < row * col; i++)
    {
        mat.data[i] = data[i]+1;
        data[i] = mat.data[i];
    }
}
void Matrix::operator--()   // Sub 1 from each element in the matrix
{
    Matrix mat;
    mat.setRow(row);
    mat.setCol(col);
    mat.data.resize(mat.row * mat.col);
    for(int i = 0; i < row * col; i++)
    {
        mat.data[i] = data[i]-1;
        data[i] = mat.data[i];
    }
}
bool Matrix::operator==(Matrix mat)  //check if two matrices are equal and return true if equal
{
    if (row == mat.row && col == mat.col)
    {
        for (int i=0 ; i < row * mat.col; i++)
        {
            if (data[i] != mat.data[i])
            {
                //cout<<"Not Equal"<<endl;
                return false;
            }
        }
        //cout<<"Equal"<<endl;
        return true;
    }
    //cout<<"Not Equal"<<endl;
    return false ;
}
bool Matrix::operator!=(Matrix mat)  //check if two matrices are not equal and return True if not equal
{
    if(row != mat.row || col != mat.col)
    {
        //cout<<"Not Equal"<<endl;
        return true;
    }

    else
    {
        for (int i=0 ; i < row * col; i++)
        {
            if (data[i] != mat.data[i])
            {
                //cout<<"Not Equal"<<endl;
                return true;
            }
        }
        //cout<<"Equal"<<endl;
        return false ;
    }
}

bool Matrix::isSquare()  // True if square matrix  (have the same number of rows and columns)
{
    if (row == col)
    {
        //cout<<"square"<<endl;
        return true ;
    }
    //cout<<"Not square"<<endl;
    return false;
}

bool Matrix::isSymetric()  //check if the matrix symmetric or not (if the transpose equal the matrix before transpose or not)
{
    Matrix tran = transpose();
    if(tran.row == row && tran.col == col)
    {
        for (int i = 0 ; i < tran.col * tran.col ; i++)
        {
            if(tran.data[i]==data[i])
            {
                //cout<< "symmetric"<<endl;
                return true;
            }
            else
            {
                //cout<< "Not symmetric"<<endl;
                return false;
            }

        }
    }
    return false;
}

Matrix Matrix::transpose()  //transpose the matrix
{
    Matrix ret;
    ret.setRow(col);
    ret.setCol(row);
    ret.data.resize(ret.row * ret.col);

    for(int j = 0; j < col; j++)
    {
        int col_cnt = j;
        for(int i = 0; i < ret.col; i++)
        {
            ret.data[i + j * ret.col] = data[col_cnt];
            col_cnt += col;
        }
    }

    return ret;
}

bool Matrix::isIdentity() //check if the main diagonal equal 1 and the rest equal zero
{
    if (row == col)
    {
        int cnt = 0;
        for (int i = 0 ; i< row * col ; i++)
        {
            if(cnt == col || (i == 0 && data[i] == 1))
            {
                if(data[i] == 1)
                {
                    cnt = 0;
                    continue;
                }
                else
                {
                    //cout << "Not Identical matrix" << endl;
                    return false;
                }
            }
            else
            {
                if(data[i] != 0)
                {
                    //cout << "Not Identical matrix" << endl;
                    return false;
                }
                else
                    cnt++;
            }
        }
        //cout << "Identical matrix" << endl;
        return true;
    }
    else
    {
        //cout<<"Not Identity matrix"<<endl;
        return false ;
    }
}

void cpyData(valarray<int>& val1, const valarray<int>& val2)   //copy data from valarray to another
{
    val1.resize(val2.size());
    for(int i = 0; i < val2.size(); i++)
    {
        val1[i] = val2[i];
    }
}

Matrix Matrix::operator=(Matrix& mat)  //copy matrix content to the current matrix
{
    row = mat.getRow();
    col = mat.getCol();
    cpyData(data, mat.data);
}

