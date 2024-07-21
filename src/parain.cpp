#include "../includes/global.h"
#include "../includes/prototype.h"
string reshape(string in)
{
    int sz=in.size();
    int i,j,jmax,szc;

    szc=0;
    for(j=0;j<sz;j++){
        if(in[j]!=' ' && in[j]!='\t' && in[j]!='#')
            szc=szc+1;
        if(in[j]=='#')
            break;    
    }
    jmax=j;
    i=0;
    string rt(szc,'*');

    for(j=0;j<jmax;j++){
        if(in[j]!=' ' && in[j]!='\t')
         {rt[i]=in[j];i=i+1;}    
    }
    return rt;
}
string get_name(string in)
{
    int sz=in.size();
    int i,j;

    i=0;
    while(i<sz && in[i]!='=')
    {
        i=i+1;
    }
    string rt(i,'*');

    for (j = 0; j < i; ++j)
    {
        rt[j]=in[j];
    }
    return rt;
}

double get_value(string in)
{
    int sz=in.size();
    int i,j;
    double rt;

    i=0;
    while(i<sz && in[i]!='=')
    {
        i=i+1;
    }
    i=i+1;
    string c(sz-i,'*');
    for (j = i; j < sz; ++j)
    {
        c[j-i]=in[j];
    }
    sscanf(c.c_str(),"%lf",&rt);
    return rt;
}

void set_input_para(const char *file, vector<string> s, double *p){
    int i,para_sz,tot;
    double tt;    
    string ou;
    ifstream fp_in;

    fp_in.open(file,fstream::in);
    if (!fp_in.is_open())
    {
        fprintf(stderr, "%s\n", "Please provide the correct path of inputing parameters!");
        exit(-1);
    }
    para_sz=s.size();
    vector<int> status(para_sz,0);
    tot=0;
    while(!fp_in.eof())
    {
        getline(fp_in,ou);
        ou=reshape(ou);
        if(ou[0]!='#' && ou!="")
        {                        
            tt=get_value(ou);
            ou=get_name(ou);
            for (int i = 0; i < para_sz; ++i)
            {
                if(s[i]==ou) 
                  {
                    p[i]=tt;
                    status[i]+=1;
                    if(status[i]>1)
                    {
                        cout<<"Error! Double initialize "<<&ou[i]<<endl;
                        exit(-1);
                    }
                    else
                    {
                        tot+=1;
                        break;
                    }
                  }
            }
        }
    }
    if (tot<para_sz)
    {
        cout<<"Error! Some parameters haven't been initialized"<<endl;
        exit(-1);
    }
    fp_in.close();
}
