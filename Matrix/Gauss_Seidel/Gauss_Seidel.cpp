#include<bits/stdc++.h>
#include<iostream>
#include<fstream>
#include<string>
using namespace std;

#define MX   1005
#define LL   long long int
#define PII  pair<int,int>
#define PLL  pair<LL,LL>
#define FAST ios_base::sync_with_stdio(0);cin.tie(0);cout.tie(0);

string str;
int n,itr,v;
double matA[MX][MX],matB[MX],matX[MX];

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
                i--;
            }
            else    matA[n][str[i]-'A'] = sign * val1;

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
                i--;
            }
            else    matA[n][str[i]-'a'] = sign * val1;

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

/*void input()
{
    while(getline(myfile,str))
    {
        //cout<<str<<endl;
        process_input();
        n++;
    }
    return;
} */

void print_mat()
{
    for(int i=0; i<n; i++)
    {
        for(int j=0; j<n; j++)  cout << matA[i][j] << " ";
        cout << "| "<< matB[i] << endl;
    }
    return;
}

void getX(int i){
    double temp = matB[i];
    for(int j=0; j<n; j++) {
            if(i==j) continue;
            temp = temp - matA[i][j]*matX[j];
    }
    matX[i] = temp/matA[i][i];

}

void Gauss_Seidal(int itr){
        for(int i=1; i<=itr; i++){
        printf("iteration %d :\n",i);
        for(int j=0; j<n; j++){
            getX(j);
            printf("%lf ",matX[j]);
        }

        printf("\n");
    }
}


int main()
{
    FAST;
    cout << std::setprecision(6) << std::fixed;
    ifstream myfile ("input.txt");
    //FILE *fp = freopen("input.txt","r",stdin);
    //input();
     while(getline(myfile,str))
    {
        //cout<<str<<endl;
        process_input();
        n++;
    }
    myfile.close();
    printf("Enter the number of iteration: \n");
    cin>>itr;
    printf("Enter the initial guesses: \n");
    for(int i=0; i<n; i++) cin>>matX[i];
    freopen("output.txt","w",stdout);

    Gauss_Seidal(itr);

    return  0;
}

