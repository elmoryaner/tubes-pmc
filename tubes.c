/*  Nama: Kadhan Dalilurahman, Elmo Ryaner Panggabean, Maheswara Apta Adiyatma
    NIM : 13220001, 13220012, 18320005
    Program Minimisasi Logika 
    Referensi: https://arxiv.org/abs/1410.1059 */

#include <stdio.h>
#include <stdlib.h>
#include <math.h>

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

// Fungsi main
int main()
{
    int k, l, m, n, x, y, LogicProbe;

    // Input jumlah variabel
    printf("Masukkan jumlah variabel: ");
    scanf("%d",&NumberOfVariable);
    while(NumberOfVariable<=0)
    {
        printf("Jumlah variabel harus lebih besar dari 0.\n\n");
        printf("Masukkan jumlah variabel: ");
        scanf("%d",&NumberOfVariable);
    }

    printf("Berapa banyak minterm (termasuk Don't Care)?\n");
    scanf("%d",&NumberOfAllMinterm);
    while(NumberOfAllMinterm>pow(2,NumberOfVariable) || NumberOfAllMinterm<=0)
    {
        printf("Banyak minterm tidak boleh lebih besar dari 2^%d atau lebih kecil dari 1.\n",NumberOfVariable);
        printf("Berapa banyak minterm? (termasuk Don't Care)?\n");
        scanf("%d",&NumberOfAllMinterm);
    }

    printf("Berapa banyak minterm Don't-Care?\n");
    scanf("%d",&NumberOfDontCare);    
    while(NumberOfDontCare>=NumberOfAllMinterm || NumberOfDontCare<0)
    {
        printf("Banyak Don't-Care tidak boleh lebih besar daripada jumlah semua minterm atau lebih kecil dari 0.\n");
        printf("Berapa banyak minterm? (termasuk Don't Care)?\n");
        scanf("%d",&NumberOfDontCare);
    }

    MintermIndicesDecimal=(int *)malloc(NumberOfAllMinterm*sizeof(int));
    MintermIndicesDecimal_DontCare=(int *)malloc(NumberOfDontCare*sizeof(int));

    for(i=0;i<NumberOfAllMinterm;i++)
    {
        if(i==0)
            printf("Masukkan minterm pertama (dari kecil ke besar):");
        else
            printf("Masukkan minterm ke-%d (dari kecil ke besar):",i+1);

        scanf("%d",&MintermIndicesDecimal[i]);
        if(i!=0 && MintermIndicesDecimal[i]<=MintermIndicesDecimal[i-1])
        {
            printf("Bilangan tidak berurutan, silakan masukkan ulang.\n\n");
            i=-1;
        }
        else if(MintermIndicesDecimal[i]>=pow(2,NumberOfVariable))
        {
            printf("\nBilangan harus lebih kecil dari %d.\n\n",pow(2,NumberOfVariable));
            i=-1;
        }
    }

    if(NumberOfDontCare!=0)
    {
        printf("\n\nManakah minterm yang Don't-Care?\n\n");
        for(i=0;i<NumberOfDontCare;i++)
        {
            if(i==0)
                printf("Masukkan minterm Don't-Care pertama (dari kecil ke besar):");
            else
                printf("Masukkan minterm Don't-Care ke-%d (dari kecil ke besar):",i+1);

            scanf("%d",&MintermIndicesDecimal_DontCare[i]);
            if(i!=0 && MintermIndicesDecimal_DontCare[i]<=MintermIndicesDecimal_DontCare[i-1])
            {
                printf("Bilangan tidak berurutan, silakan masukkan ulang.\n\n");
                i=-1;
            }
            else if(MintermIndicesDecimal[i]>=pow(2,NumberOfVariable))
            {
                printf("\nBilangan harus lebih kecil dari %d.\n\n",pow(2,NumberOfVariable));
                i=-1;
            }
        }
    }

    // Konversi desimal ke biner
    Minterm_Binary=(int **)malloc(NumberOfAllMinterm*sizeof(int*));
    for(i=0;i<=NumberOfAllMinterm;i++)
    {
        Minterm_Binary[i]=(int *)malloc((NumberOfVariable+4)*sizeof(int));
    }

    DecimalToBinary();

    for(i=0;i<NumberOfAllMinterm;i++)
    {
        Minterm_Binary[i][NumberOfVariable]=OneCounter(Minterm_Binary[i],NumberOfVariable);
        Minterm_Binary[i][NumberOfVariable+1]=0;
        /* '0' berarti belum dikelompokkan, '1' berarti sudah dikelompokkan dengan term-term lain */
        Minterm_Binary[i][NumberOfVariable+2]=MintermIndicesDecimal[i];
        /* this is its original minterm */
        Minterm_Binary[i][NumberOfVariable+3]=MintermIndicesDecimal[i];
    }

    // Inisialisasi kolom pertama untuk pengelompokkan
    Column=(int ****)malloc((NumberOfVariable+1)*sizeof(int***));
    for(i=0;i<NumberOfVariable+1;i++)
    {
        Column[i]=(int ***)malloc((NumberOfVariable+1-i)*sizeof(int**));
        /* Column[i] berisi semua term di kolom ke-(i+1) */
    }
    for(i=0;i<NumberOfVariable+1;i++)
    {
        for(j=0;j<NumberOfVariable+1-i;j++)
        {
            Column[i][j]=(int**)malloc(Combination(NumberOfVariable,i,j)*sizeof(int*));
            /* Column[i][j] berisi semua term dengan j banyak '1' di indeks biner pada kolom ke-(i+1) */
            for(k=0;k<Combination(NumberOfVariable,i,j);k++)
            {
                Column[i][j][k]=NULL;
            }
        }
    }

    for(i=0;i<NumberOfVariable+1;i++)
    {
        for(j=0,k=0;j<NumberOfAllMinterm;j++)
        {
            if(Minterm_Binary[j][NumberOfVariable]==i)
            {
                Column[0][i][k++]=Minterm_Binary[j];
                /* Inisialisasi kolom pengelompokkan pertama */
            }
        }
    }

    // Melakukan pengelompokkan
    for(i=0;i<NumberOfVariable+1;i++)
    {
        if(Groupable)
        {
            Groupable=0;
            for(j=0;j<NumberOfVariable-i;j++)
            {
                int p,position;
                m=0;
                for(k=0;k<Combination(NumberOfVariable,i,j);k++)
                {
                    if(Column[i][j][k]!=NULL)
                    {
                        for(l=0;l<Combination(NumberOfVariable,i,j+1);l++)
                        {
                            if(Column[i][j+1][l]!=NULL && Column[i][j+1][l][NumberOfVariable+2+i]>Column[i][j][k][NumberOfVariable+2+i] && IsPowerOfTwo(Column[i][j+1][l][NumberOfVariable+2+i]-Column[i][j][k][NumberOfVariable+2+i]))
                            {
                                LogicProbe=0-i;
                                /* LogicProbe berfungsi untuk memeriksa apakah kedua term memiliki posisi '-' yang sama (direpresentasikan dengan '2') */
                                for(n=1;n<=i;n++)
                                {
                                    for(p=1;p<=i;p++)
                                    {
                                        if(Column[i][j+1][l][NumberOfVariable+1+n]==Column[i][j][k][NumberOfVariable+1+p])
                                        {
                                            LogicProbe++;
                                        }
                                    }
                                }
                                if(LogicProbe==0)
                                {
                                    Groupable=1;

                                    Column[i][j][k][NumberOfVariable+1]=1;
                                    Column[i][j+1][l][NumberOfVariable+1]=1;
                                    Column[i+1][j][m]=(int *)malloc((NumberOfVariable+4+i+pow(2,i+1))*sizeof(int));
                                    
                                    for(n=0;n<=NumberOfVariable+1+i;n++)
                                    {
                                        Column[i+1][j][m][n]=Column[i][j][k][n];
                                    }
                                    
                                    Column[i+1][j][m][NumberOfVariable+3+i]=Column[i][j][k][NumberOfVariable+2+i];
                                    
                                    for(n=NumberOfVariable+4+i;n<NumberOfVariable+4+i+pow(2,i+1);n++)
                                    {
                                        Column[i+1][j][m][n]=0;
                                    }

                                    position=log((Column[i][j+1][l][NumberOfVariable+2+i]-Column[i][j][k][NumberOfVariable+2+i]))/log(2);
                                    
                                    Column[i+1][j][m][NumberOfVariable-1-position]=2;
                                    Column[i+1][j][m][NumberOfVariable+1]=0;
                                    Column[i+1][j][m][NumberOfVariable+2+i]=position;
                                    
                                    for(p=0;p<pow(2,i);p++)
                                    {
                                        Column[i+1][j][m][NumberOfVariable+4+i+p]=Column[i][j][k][NumberOfVariable+3+i+p];
                                    }
                                    
                                    for(p=pow(2,i);p<pow(2,i+1);p++)
                                    {
                                        Column[i+1][j][m][NumberOfVariable+4+i+p]=Column[i][j+1][l][NumberOfVariable+3+i+p-(int)pow(2,i)];
                                    }
                                    m++;
                                }
                            }
                        }
                    }
                }
            }
        }
    }

    // NumberCounter: menghitung berapa kali setiap indeks desimal muncul
    NumberCounter=(int *)malloc(pow(2,NumberOfVariable)*sizeof(int));
    for(i=0;i<pow(2,NumberOfVariable);i++)
    NumberCounter[i]=0;
    
    // Menyimpan Prime Implicants (duplikat akan dihapus)
    PI_Index=(int **)malloc(NumberOfAllMinterm*sizeof(int*));
    for(i=0;i<NumberOfAllMinterm;i++)
    {
        PI_Index[i]=(int *)malloc(3*sizeof(int));
    }
    for(i=0;i<NumberOfVariable+1;i++)
    {
        for(j=0;j<NumberOfVariable+1-i;j++)
        {
            for(k=0;k<Combination(NumberOfVariable,i,j);k++)
            {
                if(Column[i][j][k]!=NULL && Column[i][j][k][NumberOfVariable+1]==0)
                {
                    LogicProbe=0-pow(2,i);
                    /* Mengecek apakah PI merupakan duplikat*/
                    for(l=k-1;l>=0;l--)
                    if(LogicProbe!=0)
                    {
                        {
                            LogicProbe=0-pow(2,i);
                            for(m=0;m<pow(2,i);m++)
                            {
                                for(n=0;n<pow(2,i);n++)
                                {    
                                    if(Column[i][j][l][NumberOfVariable+3+i+m]==Column[i][j][k][NumberOfVariable+3+i+n])
                                    {
                                        LogicProbe++;
                                    }
                                }
                            }
                        }
                    }
                    if(LogicProbe!=0)
                    {
                        PI_Index[NumberOfPI][0]=i;
                        PI_Index[NumberOfPI][1]=j;
                        PI_Index[NumberOfPI][2]=k;
                       
                        NumberOfPI++;

                        for(l=0;l<pow(2,i);l++)
                        {
                            NumberCounter[Column[i][j][k][NumberOfVariable+3+i+l]]++;
                        }
                    }
                }
            }
        }
    }

    /* Hapus minterm yang Don't Care */
    for(i=0;i<NumberOfDontCare;i++)
        NumberCounter[MintermIndicesDecimal_DontCare[i]]=0;
    EPI_Index=(int **)malloc(NumberOfAllMinterm*sizeof(int*));

    /* Pada chart PI, akan dicari minterm yang hanya muncul sekali lalu dipilih
    prime implicant yang berisi minterm tersebut sebagai EPI. Selanjutnya diset NumberCounter
    minterm tersebut ke 0 */
    for(i=0;i<pow(2,NumberOfVariable);i++)
    {
        if(NumberCounter[i]==1)
        {
            for(j=0;j<NumberOfPI;j++)
            {
                for(k=0;k<pow(2,PI_Index[j][0]);k++)
                {
                    if(Column[PI_Index[j][0]][PI_Index[j][1]][PI_Index[j][2]][NumberOfVariable+3+PI_Index[j][0]+k]==i)
                    {
                        EPI_Index[NumberOfEPI]=PI_Index[j];
                        for(l=0;l<pow(2,PI_Index[j][0]);l++)
                        {
                            NumberCounter[Column[PI_Index[j][0]][PI_Index[j][1]][PI_Index[j][2]][NumberOfVariable+3+PI_Index[j][0]+l]]=0;
                        }
                        NumberOfEPI++;
                        k=pow(2,PI_Index[j][0]);
                    }
                }
            }
        }
    }

    /* Membuat Reduced PI Chart */
    NumberOfRemainingMT=0;
    for(i=0;i<pow(2,NumberOfVariable);i++)
        if(NumberCounter[i]!=0)
            NumberOfRemainingMT++;
    ReducedPIChart_X=(int *)malloc(NumberOfRemainingMT*sizeof(int));
    for(i=0;i<NumberOfRemainingMT;i++)
        ReducedPIChart_X[i]=-1;
    ReducedPIChart_Y=(int **)malloc(NumberOfPI*sizeof(int*));
    for(i=0;i<NumberOfPI;i++)
        ReducedPIChart_Y[i]=NULL;
    ReducedPIChart=(int **)malloc(NumberOfRemainingMT*sizeof(int*));

    /* Baris pertama ini berisi sisa minterm dalam bentuk desimal */
    for(i=0,j=0;j<pow(2,NumberOfVariable);j++)
    {
        if(NumberCounter[j]!=0)
        {
            ReducedPIChart_X[i]=j;
            i++;
        }
    }
    
    /* Kolom pertama ini berisi sisa Prime Implicant */
    NumberOfRemainingPI=0;
    for(i=0;i<NumberOfPI;i++)
    {
        for(j=0;j<pow(2,PI_Index[i][0]);j++)
        {
            if(NumberCounter[Column[PI_Index[i][0]][PI_Index[i][1]][PI_Index[i][2]][NumberOfVariable+3+PI_Index[i][0]+j]]!=0)
            {
                j=pow(2,PI_Index[i][0]);
                ReducedPIChart_Y[NumberOfRemainingPI]=PI_Index[i];
                NumberOfRemainingPI++;
            }
        }
    }
    
    /* ReducedPIChart[i][j] merupakan isi dari Reduced PI Chart ('1' dipilih, '0' tidak dipilih) */
    if(NumberOfRemainingPI!=0)
    {
        for(i=0;i<NumberOfRemainingMT;i++)
            ReducedPIChart[i]=(int *)malloc(NumberOfRemainingPI*sizeof(int));
        for(i=0;i<NumberOfRemainingMT;i++)
            for(j=0;j<NumberOfRemainingPI;j++)
                ReducedPIChart[i][j]=0;
        for(i=0;i<NumberOfRemainingPI;i++)
        {
            for(j=0;j<pow(2,ReducedPIChart_Y[i][0]);j++)
            {
                for(k=0;k<NumberOfRemainingMT;k++)
                {
                    if(Column[ReducedPIChart_Y[i][0]][ReducedPIChart_Y[i][1]][ReducedPIChart_Y[i][2]][NumberOfVariable+3+ReducedPIChart_Y[i][0]+j]==ReducedPIChart_X[k])
                    {
                        ReducedPIChart[k][i]=1;
                    }
                }
            }
        }

        /* Memilih EPI dari Reduced PI Chart */
        For=(int *)malloc(NumberOfRemainingMT*sizeof(int)); /* For[i] digunakan di fungsi 'Recursion_For_Loop(int m)' */
        for(i=0;i<NumberOfRemainingMT;i++)
        {
            For[i]=-1;
        }
        for(i=0;i<NumberOfRemainingMT;i++)
        {
            NumberOfPossibleEPI=NumberOfPossibleEPI*NumberCounter[ReducedPIChart_X[i]];
        }
        Potential_EPI=(int **)malloc(NumberOfPossibleEPI*sizeof(int*));
        for(i=0;i<NumberOfPossibleEPI;i++)
        {
            Potential_EPI[i]=(int *)malloc(NumberOfRemainingMT*sizeof(int));
        }
        Recursion_For_Loop(NumberOfRemainingMT-1);
        NoOfPIForEPI=(int *)malloc(NumberOfPossibleEPI*sizeof(int)); 
        
        /* NoOfPIForEPI[i] akan menghitung berapa banyak PIs di setiap kombinasi yang memenuhi semua minterm */
        for(i=0;i<NumberOfPossibleEPI;i++)
            NoOfPIForEPI[i]=0;
        for(i=0;i<NumberOfPossibleEPI;i++)
        {
            for(j=0;j<NumberOfRemainingMT;j++)
            {
                if(Potential_EPI[i][j]!=-1)
                {
                    NoOfPIForEPI[i]++;
                    for(k=j+1;k<NumberOfRemainingMT;k++)
                    if(Potential_EPI[i][k]==Potential_EPI[i][j])
                    Potential_EPI[i][k]=-1;
                }
            }
        }

        /* Mencari kombinasi yang memerlukan jumlah PI paling sedikit untuk mencakup semua minterm */
        for(i=1;i<NumberOfPossibleEPI;i++)
            if(NoOfPIForEPI[i]<NoOfPIForEPI[MinimumNo])
                MinimumNo=i;
        for(i=0;i<NumberOfRemainingMT;i++)
            if(Potential_EPI[MinimumNo][i]!=-1)
                EPI_Index[NumberOfEPI++]=ReducedPIChart_Y[Potential_EPI[MinimumNo][i]];

        /* Mencetak hasil minimisasi */
        printf("\nHasil minimisasi:\n");
        printf("\n ");
        for(x=0;x<NumberOfEPI;x++)
        {
            for(y=0;y<NumberOfVariable;y++)
            {
                if(Column[EPI_Index[x][0]][EPI_Index[x][1]][EPI_Index[x][2]][y]==1)
                    printf("%c",65+y);
                else if(Column[EPI_Index[x][0]][EPI_Index[x][1]][EPI_Index[x][2]][y]==0)
                    printf("%c'",65+y);
            }
            if(x<NumberOfEPI-1)
                printf("+");
        }
        return 0;
    }
    else
    {
        printf("\n\nHasil minimisasi:\n");
        printf("\n ");
        for(x=0;x<NumberOfEPI;x++)
        {
            for(y=0;y<NumberOfVariable;y++)
            {
                if(Column[EPI_Index[x][0]][EPI_Index[x][1]][EPI_Index[x][2]][y]==1)
                    printf("%c",65+y);
                else if(Column[EPI_Index[x][0]][EPI_Index[x][1]][EPI_Index[x][2]][y]==0)
                    printf("%c'",65+y);
            }
            if(x<NumberOfEPI-1)
                printf("+");
        }
        return 0;
    }
}
