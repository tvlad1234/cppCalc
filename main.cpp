///Calculator cu 5 functii, care respecta ordinea efectuarii operatiilor
///Semne: +-*/^()
///Vlad Tomoiaga, 2020
#include <iostream>
#include <cstring>
#include <cmath>
using namespace std;

void elim(double x[], int &n, int p)
{
    for(int i=p;i<n;i++)
        x[i]=x[i+1];
    n--;
}
int nrcif(int n)
{
    int c=0;
    while(n)
    {
        c++;
        n=n/10;
    }
    return c;
}


double calc(int ns, int nx, char s[], double x[])
{
    int i,j;
    double r;
    //rezolvam puterile
    for(i=ns;i>=1;i--)
        if(s[i]=='^')
        {
            x[i]=pow(x[i],x[i+1]);
            strcpy(s+i,s+1+i);
            elim(x,nx,i+1);
            i++;
            ns--;
        }

   //rezolvam inmultirile si impartirile
    for(i=1;i<=ns;i++)
    {
        if(s[i]=='*')
        {
            x[i]=x[i]*x[i+1];
            strcpy(s+i,s+1+i);
            elim(x,nx,i+1);
            i--;
            ns--;
        }
        else if(s[i]=='/')
            {
                 x[i]=x[i]/x[i+1];
                 strcpy(s+i,s+1+i);
                 elim(x,nx,i+1);
                 i--;
                 ns--;
            }
    }

    /*
    for(i=1;i<=nx;i++)
        cout<<x[i]<<' ';
    cout<<endl;
    for(i=1;i<=ns;i++)
        cout<<s[i]<<' ';
    cout<<endl;
    */

    //la final facem adunarile si scaderile
    j=1;
    r=x[1];
    for(i=2;i<=nx;i++)
    {
        if(s[j]=='+')
            r=r+x[i];
        else r=r-x[i];
        j++;
    }
    return r;
}

void stergeValori(int &n, double x[], int poz, int k)
{
    for(int i=poz;i<n-k+1;i++)
        x[i]=x[i+k];
    n=n-k;
}

void paranteza(int &ns, int &nx, char s[], double x[])
{
    int close=strchr(s,')')-s;
    int open;
    for(open=close;s[open]!='(';open--);
    char sp[10]; strcpy(sp, " ");
    int nxp=1,nsp=0;
    double xp[50]={0},r;
    nsp=close-open;
    strncat(sp,s+open+1,nsp-1);
    //cout<<sp<<endl;
    nsp++;
    //cout<<open<<' '<<close<<endl;
    for(int i=open;i<close;i++)
        xp[nxp++]=x[i];
  // for(int i=1;i<=nxp;i++)
      //  cout<<xp[i]<<' ';
   // cout<<endl;
    r=calc(nsp,nxp,sp,xp);
    //cout<<r<<endl;
    stergeValori(nx,x,open+1,nsp-2);
    strcpy(s+open,s+close+1);
    //cout<<s<<endl;
    x[open]=r;
}

int main()
{
    char p[100];
    int i,nx=1,ns=0;
    double x[50]={0},f;
    char s[50];

    cin.getline(p,100);
    //punem numerele in x si semnele in s
    for(i=0;i<strlen(p);i++)
    {
        while(p[i]==' ')
            i++;
        while(isdigit(p[i]))
        {
            x[nx]=x[nx]*10+(p[i]-'0');
            i++;
        }
        ///cand dam de virgula, citim nr de dupa virgula, calc. partea fr si o adaugam la numar
        if(p[i]=='.' || p[i]==',')
        {
            i++;
            f=0;
            while(isdigit(p[i]))
            {
                f=f*10+(p[i]-'0');
                i++;
            }
            x[nx]=x[nx]+f/(pow(10,nrcif(f)));
        }
        if(strchr("+-*/^()", p[i]))
        {
            s[++ns]=p[i];
            if(p[i]!='(' && p[i]!=')')
                nx++;
        }

    }
    if(x[nx])
        nx++;
    s[ns+1]=0;
    //cout<<ns<<endl;
   // for(i=1;i<=nx;i++)
        //cout<<x[i]<<' ';
   // cout<<endl;
   // cout<<ns<<endl;
   //cout<<s<<endl;

    while(strchr(s,'('))
        paranteza(ns,nx,s,x);
    //for(i=1;i<=nx;i++)
        //cout<<x[i]<<' ';
   //cout<<endl;
    cout<<"= "<<calc(ns, nx, s, x)<<endl;
    //cout<<nx<<' '<<ns<<endl;
    return 0;
}
