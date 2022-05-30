int i,j,temp;
int NumberOfVariable;
int NumberOfAllMinterm,NumberOfDontCare,NumberOfRemainingMT,NumberOfRemainingPI;
int NumberOfPI=0,NumberOfEPI=0,PotEPINo=0,NumberOfPossibleEPI=1,MinimumNo=0,Groupable=1;

int *MintermIndicesDecimal, *MintermIndicesDecimal_DontCare;
int **Minterm_Binary,****Column, **PI_Index,**EPI_Index,*NumberCounter;
int *ReducedPIChart_X,**ReducedPIChart_Y,**ReducedPIChart,*For, **Potential_EPI,*NoOfPIForEPI;

// Fungsi mengubah desimal ke biner
void DecimalToBinary()
{
    int i,j,dividend;
    for(i=0;i<NumberOfAllMinterm;i++)
    {
        dividend=MintermIndicesDecimal[i];
        for(j=NumberOfVariable-1;j>=0;j--)
        {
            Minterm_Binary[i][j]=dividend%2;
            dividend=dividend/2;
        }
    }
}

int IsDontCare(int MT)
{
    int i;
    for(i=0;i<NumberOfDontCare;i++)
        if(MT==MintermIndicesDecimal_DontCare[i])
            return 1;
    return 0;
}

// Fungsi counter
int OneCounter(int *binary, int NumberOfDigit)
{
    int i,count=0;
    for(i=0;i<=NumberOfDigit-1;i++)
    {
        if(binary[i]==1)
            count++;
    }
    return count;
}

// Fungsi kombinasi kolom
int Combination(int n, int ColumnNo, int k)
{
    int Comb,i,NtoK=1,Kto1=1;
    for(i=n;i>=n-k+1-ColumnNo;i--)
    {
        NtoK=i*NtoK;
    }
    for(i=k;i>=1;i--)
    {
        Kto1=i*Kto1;
    }
    Comb=NtoK/Kto1;
    return Comb;
}

// Fungsi untuk memeriksa apakah bilangan merupakan 2^n
int IsPowerOfTwo(int n)
{
    return(ceil(log2(n)) == floor(log2(n)));
}

// Fungsi membuat rekursi dalam for loop
void Recursion_For_Loop(int m)
{
    int n=m;
    for(For[n]=0;For[n]<NumberOfRemainingPI;For[n]++)
    {
        if(ReducedPIChart[NumberOfRemainingMT-1-n][For[n]])
        {
            if(n>0)
            {
                m=n;
                m--;
                Recursion_For_Loop(m);
            }
            else if(n==0)
            {
                for(i=0;i<NumberOfRemainingMT;i++)
                {
                    Potential_EPI[PotEPINo][i]=For[NumberOfRemainingMT-1-i];
                }
                PotEPINo++;
            }
        }
    }
}
