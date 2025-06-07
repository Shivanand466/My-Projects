//CPL Assignment-Implimentation of bigint(1024 bit)
#include<stdio.h>
#include<string.h>
#include<ctype.h>
#define NUMLEN 309

typedef enum{FALSE,TRUE} boolean;
typedef enum{FAILURE,SUCCESS} status_code;

//STRUCTURE TO REPRESENT AN INTEGER
typedef struct bigint_tag
{
    char sign;
    char str[NUMLEN];
}bigint;

//FUNCION TO INITIALISE INPUT STRING
void initialise(bigint *num)
{
    num->str[0]='\0';
    num->sign='+';
}

//FUNCTION TO GET INPUT OF THE STRING AND STORE IT WITH LEADING ZEROES
status_code get(bigint *num)
{
    status_code sc=SUCCESS;
    printf("Enter number (with or without sign):");
    scanf("%s",num->str);
    int i,j;
    if(num->str[0]=='+'||num->str[0]=='-')
    {
        num->sign=num->str[0];
        num->str[0]='0';
    }
    
    if(strlen(num->str)<NUMLEN)
    {
        for(i=0;i<strlen(num->str) && sc==SUCCESS;i++)
        {
            if(!isdigit(num->str[i]))
            {
                sc=FAILURE;
            }
        }
    
        for(j=i;j<NUMLEN;j++) num->str[j]='0';
    
        while(i>0)
        {
            i--;
            j--;
            num->str[j]=num->str[i];
            num->str[i]='0';
        }
    }
    else
    {
        sc=FAILURE;
    }
    return sc;
}

//FUNCTION TO PRINT INTEGER WITH SIGN AND WITH NO LEADING ZEROES
void print(bigint num)
{
    int i;
    printf("%c",num.sign);
    for(i=0;i<NUMLEN-1 && num.str[i]=='0';i++){}
    while(i<NUMLEN)
    {
        printf("%c",num.str[i]);
        i++;
    }
    printf("\n");
}

//HELPER FUNCTION TO ADD TWO INTEGERS IRRSPECTIVE OF THEIR SIGN
status_code sum(bigint a,bigint b,bigint *s)
{
    status_code sc=SUCCESS;
    int i,carry=0;
    for(i=NUMLEN-1;i>=0;i--)
    {
        s->str[i]='0'+(a.str[i]-'0')+(b.str[i]-'0')+carry;
        
        if(!isdigit(s->str[i]))
        {
            s->str[i]=s->str[i]-10;
            carry=1;
        }
        else 
        {
            carry=0;
        }
    }
    if(carry==1) sc=FAILURE;
    return sc;
}

//HELPER FUNCTION TO SUBTRACT TWO INTEGERS IRRSPECTIVE OF THEIR SIGN
status_code dif(bigint a,bigint b,bigint *s)
{
    status_code sc=SUCCESS;
    int i,borrow=0;
    for(i=NUMLEN-1;i>=0;i--)
    {
        s->str[i]='0'+(a.str[i]-'0')-(b.str[i]-'0')-borrow;
        
        if(!isdigit(s->str[i]))
        {
            s->str[i]=s->str[i]+10;
            borrow=1;
        }
        else 
        {
            borrow=0;
        }
    }
    if(borrow==1) sc=FAILURE;
    return sc;
}

//MAIN ADDITION FUNCTION THAT USES HELPER FUNCTIONS ACCORDING TO SIGN
status_code add(bigint a,bigint b,bigint *s)
{
    status_code sc;
    if(a.sign==b.sign)
    {
        s->sign=a.sign;
        sc=sum(a,b,s);
    }
    else
    {
        if(strcmp(a.str,b.str)>0)
        {
            s->sign=a.sign;
            sc=dif(a,b,s);
        }
        else
        {
            s->sign=b.sign;
            sc=dif(b,a,s);
        }
    }
    return sc;
}

//MAIN SUBTRACTION FUNCTION THAT USES HELPER FUNCTIONS ACORDING TO SIGN
status_code sub(bigint a,bigint b,bigint *d)
{
    status_code sc;
    if(b.sign=='+')
    {
        b.sign='-';
    }
    else
    {
        b.sign='+';
    }
    sc=add(a,b,d);
    return sc;
}

//FUNCTION TO MULTIPLY TWO INTEGERS USING TEMPERORY INTEGER ARRAY
status_code multiply(bigint a,bigint b,bigint *m)
{
    status_code sc=SUCCESS;
    int temp[NUMLEN],prod,i,j,k,carry;
    for(i=0;i<NUMLEN;i++)
    {
        temp[i]=0;
    }
    
    for(i=NUMLEN-1; i>=0 && sc!=FAILURE ;i--)
    {
        k=i;
        carry=0;
        for(j=NUMLEN-1;k>=0;j--)
        {
            temp[k]+=((a.str[j]-'0')*(b.str[i]-'0')+carry);
            
            carry=temp[k]/10;
            temp[k]=temp[k]%10;
            k--;
        }
        if(carry!=0) sc=FAILURE;
    }

    if(sc==SUCCESS)
    {
        for(i=0;i<NUMLEN;i++)
        {
            m->str[i]='0'+temp[i];
        }
        if(a.sign==b.sign)
        {
            m->sign='+';
        }
        else
        {
            m->sign='-';
        }
    }
    return sc;
}

int main()
{
    //VARIABLE DECLARATION
    bigint a,b,addition,subtraction,multiplication;
    status_code sc;
    boolean flag;
    
    //TAKING VALID INPUT
    printf("Enter two 309 size bit integers in decimal\n");
    printf("For first number \n");
    do
    {
        initialise(&a);
        sc=get(&a);
        if(sc==FAILURE)
        {
             printf("INVALID INPUT \nTRY AGIAN \n");
             flag=FALSE;
        }
        else
        {
            flag=TRUE;
        }
    }while(flag==FALSE);

    printf("For second number \n");
    do
    {
        initialise(&b);
        sc=get(&b);
        if(sc==FAILURE)
        {
             printf("INVALID INPUT \nTRY AGIAN \n");
             flag=FALSE;
        }
        else
        {
            flag=TRUE;
        }
    }while(flag==FALSE);
    
    printf("FIRST NUMBER(a):");print(a);
    printf("SECOND NUMBER(b):");print(b);
    printf("OUTPUT \n");
    
    //ADDITION
    sc=add(a,b,&addition);
    printf("ADDITION(a+b):");
    if(sc==SUCCESS)
    {
        print(addition);
    }
    else
    {
        printf("Overflow Error \n");
    }

    //SUBTRACTION
    sc=sub(a,b,&subtraction);
    printf("SUBTRACTION(a-b):");
    if(sc==SUCCESS)
    {
        print(subtraction);
    }
    else
    {
        printf("Overflow Error \n");
    }
    
    //MULTIPLICATION
    sc=multiply(a,b,&multiplication);
    printf("MULTIPLICATION(a*b):");
    if(sc==SUCCESS)
    {
        print(multiplication);
    }
    else
    {
        printf("Overflow Error \n");
    }

    return 0;
}