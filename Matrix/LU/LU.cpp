#include<bits/stdc++.h>
using namespace std;

#define MX   1005
#define LL   long long int
#define PII  pair<int,int>
#define PLL  pair<LL,LL>
#define FAST ios_base::sync_with_stdio(0);cin.tie(0);cout.tie(0);

string str;
int n;
double matA[MX][MX],matB[MX],matX[MX] = {}, matU[MX][MX], matL[MX][MX], matY[MX];

void process_input()
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
                matA[n][pos-1] = sign * val1;
                matU[n][pos-1] = sign * val1;
                i--;
            }
            else
            {
                matA[n][str[i]-'A'] = sign * val1;
                matU[n][str[i]-'A'] = sign * val1;
            }

            sign = 1.0;
            val1 = 0.0;
            val2 = 0.0;
            div = 1.0;
            flag = false;
        }
        else if(str[i]>='a' && str[i]<='z')
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
                matA[n][pos-1] = sign * val1;
                matU[n][pos-1] = sign * val1;
                i--;
            }
            else
            {
                matA[n][str[i]-'a'] = sign * val1;
                matU[n][str[i]-'a'] = sign * val1;
            }

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
    matB[n] = sign * val1;
    return;
}

void input()
{
    while(getline(cin,str))
    {
        //cout<<str<<endl;
        process_input();
        n++;
    }
    return;
}

void print_matrix(double mat[][MX])
{
    for(int i=0; i<n; i++)
    {
        for(int j=0; j<n; j++)  cout << mat[i][j] <<" ";
        cout<< endl;
    }
    return;
}


void forwardElim()
{
    for(int i=0; i<(n-1); i++)
    {
        // make the elements below the pivot elements equal to zero
        for(int j=i+1; j<n; j++)
        {
            double tmp = matU[j][i]/matU[i][i];
            for(int k=0; k<n; k++)
            {
                matU[j][k] = matU[j][k] - (tmp * matU[i][k]);
            }
        }
    }

    cout << "\nThe upper triangular matrix is:" << endl;
    print_matrix(matU);

}

void Upper()
{
    forwardElim();

}

void Lower()
{
    for(int i=0; i<n; i++)
    {
        for(int j=0; j<n; j++)
        {
            double tmp = matA[i][j];
            if(i==j)  matL[i][j] = 1.0;
            else if(i<j) matL[i][j] = 0.0;
            else
            {
                for(int k=0; k<j; k++) tmp = tmp - matU[k][j] * matL[i][k];
                matL[i][j] = tmp / matU[j][j];
            }
        }

    }
    cout << "\nThe Lower Triangular matrix is :" << endl;
    print_matrix(matL);

}



// LUX = b , UX = y, Ly = b

///Solve for x
void backSubstitution(){
    for(int i=n-1; i>=0; i--)
    {
        double tmp = 0.0;
        for(int j=i+1; j<n; j++)    tmp += (matU[i][j] * matX[j]);
        tmp = matY[i] - tmp;
        matX[i] = tmp/matU[i][i];
    }

    cout<<"\nThe solution of the system is:" << endl;
    for(int i=0; i<n; i++)  cout << matX[i] << endl;

}

///Solve for y
void forwardSubstitution(){
    for(int i=0; i<n; i++){
        double tmp = 0.0;
        for(int j=0; j<i; j++) tmp = tmp + matL[i][j] * matY[j];
        tmp = matB[i] - tmp;
        matY[i] = tmp;
    }

}


int main()
{
    FAST;
    cout << std::setprecision(6) << std::fixed;
    freopen("input.txt","r",stdin);
    freopen("output.txt","w",stdout);
    input();
    Upper();
    Lower();
    forwardSubstitution(); //solve y from Ly = b
    backSubstitution();    //solve x from Ux = y



    return  0;
}

