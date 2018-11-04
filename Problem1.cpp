#include<bits/stdc++.h>
using namespace std;

#define MX   1001

string str;
int n;
double matrixA[MX][MX],matrixB[MX],matSol[MX];

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
                matrixA[n][pos-1] = sign * val1;
                i--;
            }
            else    matrixA[n][str[i]-'a'] = sign * val1;

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

void getInput()
{
    while(getline(cin,str))
    {
        process_equations();
        n++;
    }
    return;
}

void print_matrix()
{
    for(int i=0; i<n; i++)
    {
        for(int j=0; j<n; j++)  cout << matrixA[i][j] << " ";
        cout << "| "<< matrixB[i] << endl;
    }
    return;
}


void forwardElim(){
    for(int i=0; i<(n-1); i++)
    {
        // Pivotisation
        int pos = i;
        for(int j=i+1; j<n; j++)
        {
            if(abs(matrixA[pos][i])<abs(matrixA[j][i]))   pos = j;
        }
        for(int j=0; j<n; j++)  swap(matrixA[i][j],matrixA[pos][j]);
        swap(matrixB[i],matrixB[pos]);

        if(matrixA[i][i]==0.0)
        {
            if(matrixB[i]>0.0) cout << "The system is inconsistent." << endl;
            else    cout << "The system may have infinitely many solutions." << endl;
            return;
        }

        // make the elements below the pivot elements equal to zero
        for(int j=i+1; j<n; j++)
        {
            double tmp = matrixA[j][i]/matrixA[i][i];
            for(int k=0; k<n; k++)
            {
                matrixA[j][k] = matrixA[j][k] - (tmp * matrixA[i][k]);
            }
            matrixB[j] = matrixB[j] - (tmp * matrixB[i]);
        }
    }

    cout << "\nThe current matrix after forward elimination is:" << endl;
    print_matrix();

}

void backSub(){
    for(int i=n-1; i>=0; i--)
    {
        double tmp = 0.0;
        for(int j=i+1; j<n; j++)    tmp += (matrixA[i][j] * matSol[j]);
        tmp = matrixB[i] - tmp;
        matSol[i] = tmp/matrixA[i][i];
    }

    cout<<"\nThe solution of the system is:" << endl;
    for(int i=0; i<n; i++)  cout << matSol[i] << endl;

}

void gaussianElimination()
{

    forwardElim();
    backSub();
}

int main()
{
    cout << std::setprecision(4) << std::fixed;
    freopen("input.txt","r",stdin);
    freopen("output1.txt","w",stdout);

    getInput();
    cout << "The Augmented matrix:" << endl;
    print_matrix();
    gaussianElimination();

    return  0;
}
