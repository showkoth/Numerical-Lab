#include<bits/stdc++.h>
using namespace std;

#define MX   101
#define LL   long long int

string str;
int n;
double matrixA[MX][MX],matrixAdj[MX][MX],matInverse[MX][MX],matrixB[MX],matX[MX];

void process_equations()
{
    int len = str.size();
    double val1 = 0.0,val2 = 0.0,div = 1.0,sign = 1.0;
    bool flag = false;

    for(int i=0; str[i]; i++)
    {
        if(str[i]>='A' && str[i]<='Z')
        {
            if(val1 == 0.0 && val2 == 0.0)  val1 = 1.0;
            val1 += (val2/div);

            if((i+1)<len && str[i+1]!=' ')
            {
                i++;
                int pos = 0;
                while(1)
                {
                    if(i>=len || str[i]==' ')   break;
                    pos = (pos * 10) + (str[i] - '0');
                    i++;
                }
                matrixA[n][pos-1] = sign * val1;
                i--;
            }
            else    matrixA[n][str[i]-'A'] = sign * val1;

            sign = 1.0;
            val1 = 0.0;
            val2 = 0.0;
            div = 1.0;
            flag = false;
        }

        else if(str[i]==' ' || str[i]=='=')    continue;
        else if(str[i]=='-')    sign = -1.0;
        else if(str[i]=='+')    sign = 1.0;
        else if(str[i]=='.')    flag = true;
        else
        {
            if(flag)
            {
                val2 = (val2 * 10.0) + (str[i] - '0');
                div *= 10.0;
            }
            else    val1 = (val1 * 10.0) + (str[i] - '0');
        }
    }
    val1 += (val2/div);
    matrixB[n] = sign * val1;
    return;
}

void print_matrix(double matrix[MX][MX],int r,int c)
{
    for(int i=0; i<r; i++)
    {
        for(int j=0; j<c; j++)  cout << matrix[i][j] << " ";
        cout << endl;
    }
    return;
}

void getInput()
{
    while(getline(cin,str))
    {
        process_equations();
        n++;
    }
    return;
}



/// Function to get cofactor of tmat[p][q] in tmp[][].
void doCofactor(double tmat[MX][MX],double tmp[MX][MX],int p,int q,int tn)
{
    int r = 0,c = 0;
    for(int i=0; i<tn; i++)
    {
        for(int j=0; j<tn; j++)
        {
            if(i!=p && j!=q)
            {
                tmp[r][c++] = tmat[i][j];
                if(c==(tn-1))
                {
                    r++;
                    c = 0;
                }
            }
        }
    }
    return;
}

// Recursive function for finding determinant of matrix.
double getDeterminant(double tmat[MX][MX],int tn)
{
    if(tn == 1) return  tmat[0][0];

    double tmp[MX][MX],det = 0.0,sign = 1.0;

    /// Iterate for each element of first row
    for(int i=0; i<tn; i++)
    {
        doCofactor(tmat,tmp,0,i,tn);

        det += (sign * tmat[0][i] * getDeterminant(tmp,tn-1));

        sign = -sign;
    }
    return  det;
}

void getAdjoint()
{
    if(n == 1)
    {
        matrixAdj[0][0] = 1.0;
        return;
    }

    /// tmp is used to store cofactors
    double tmp[MX][MX],sign = 1.0;

    for(int i=0; i<n; i++)
    {
        for(int j=0; j<n; j++)
        {
            doCofactor(matrixA,tmp,i,j,n);

            /// sign of matrixAdj[j][i] positive if sum of row and column indexes is even.
            sign = ((i+j)%2==0) ? 1.0 : -1.0;

            matrixAdj[j][i] = sign * getDeterminant(tmp,n-1);
        }
    }

    cout << "\nThe Adjoint matrix is:" << endl;
    print_matrix(matrixAdj,n,n);

    return;
}

/// Function to calculate and store inverse, returns false if matrix is singular
bool getInverse()
{
    double det = getDeterminant(matrixA,n);
    cout << "\nThe Determinant is = " << det << endl;

    if(det == 0)
    {
        cout << "\nSingular matrix, so can't find its inverse" << endl;
        return false;
    }

    for(int i=0; i<n; i++)
    {
        for(int j=0; j<n; j++)
        {
            matInverse[i][j] = matrixAdj[i][j] / det;
        }

    }

    cout << "\nThe Inverse matrix is:" << endl;
    print_matrix(matInverse,n,n);

    return true;
}

void multiply()
{
    for(int i=0; i<n; i++)
    {
        for(int j=0; j<n; j++)
        {
            matX[i] += (matInverse[i][j] * matrixB[j]);
        }
    }

    cout << "\nThe values of the variables are:" << endl;
    for(int i=0; i<n; i++)  cout << matX[i] << endl;

    return;
}

int main()
{
    cout << std::setprecision(4) << std::fixed;
    freopen("input.txt","r",stdin);
    freopen("output2.txt","w",stdout);

    getInput();
    cout << "Original matrix:" << endl;
    print_matrix(matrixA,n,n);

    getAdjoint();

    if(getInverse())    multiply();

    return  0;
}

