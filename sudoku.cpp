#include<iostream>
#include<vector>
#include<fstream>
#include<string.h>


using namespace std;


class Cell
{
private:

    int val;
    int row;
    int col;
public:
    vector<int> PossVal;
    int PossValArray[10];
    Cell()
    {
        val=0;
        row=-1;
        col =-1;
        for(int i=1;i<10;i++)
        {
            PossVal.push_back(i);
        }
        for(int j=0;j<10;j++)
            PossValArray[j]=1;

    }
    void showcell()
    {

        cout<<"The cell at ("<<row+1<<","<<col+1<<")"<<"has the value"<<val<<endl;

    }
    void setval(int i, int k, int d)
    {
        row=i;
        col=k;
        val=d;

        if((val>0)&&(val<10))
        {
            PossVal.clear();
            for(int j=0;j<10;j++)
                PossValArray[j]=0;
            PossValArray[val]=1;
        }

    }
    void setval(int i)
    {
        val=i;

        if((val>0)&&(val<10))
        {
            PossVal.clear();
            for(int j=0;j<10;j++)
                PossValArray[j]=0;
            PossValArray[val]=1;
        }

    }
    int giveval()
    {
        return val;
    }
    int boxrow()
    {
        int a= row/3;
        return a*3;
    }
    int boxcol()
    {
        int a= col/3;
        return a*3;
    }

};

class Table
{
public:

    Cell c[9][9];

    void get_table()
    {
        int data;
        fstream infile("input.txt");
        if(infile.is_open())
        {

            infile>>data;
            for(int i=0;i<9;i++)
            {
                for(int j=0;j<9;j++)
                {
                    c[i][j].setval(i,j,data);
                    if(!(infile>>data))
                        break;
                    else
                        continue;
                }

            }

            infile.close();
        }
        show_table();
    }
    void show_table()
    {
        static int cnt=0;
        ofstream outfile;
        if(cnt==0)
        {
            outfile.open("exout.txt",ios::trunc);
        }
        else
            outfile.open("exout.txt",ios::app);
        if(outfile.is_open())
        {
            outfile.seekp(0,ios::end);
            for(int row=0;row<9;row++)
            {
                for(int col=0;col<9;col++)
                {
                    outfile<<c[row][col].giveval()<<" ";
                    if(col==2||col==5)
                        outfile<<" | ";

                }
                if(row==2||row==5)
                    outfile<<endl<<"-----------------------"<<endl;
                outfile<<endl;

            }
            outfile<<endl<<endl<<"***************************************************"<<endl;

            /*
            for(int i=0;i<9;i++)
            {
                for(int j=0;j<9;j++)
                {
                    for(int k=0;k<c[i][j].PossVal.size();k++)
                    {
                        outfile<<c[i][j].PossVal[k]<<" ";
                    }
                    outfile<<endl;
                    for(int m=0;m<10;m++)
                        outfile<<c[i][j].PossValArray[m];
                    outfile<<endl;
                }
                // outfile<<endl;
            }
*/
            outfile.flush();
            outfile.close();
            cnt++;
        }
    }
    void update_possible_vals()
    {


        for(int row=0;row<9;row++)
        {
            for(int col=0;col<9;col++)
            {
                if(c[row][col].giveval()==0)
                {
                    for(int i=1;i<10;i++)
                    {
                        c[row][col].PossVal.push_back(i);
                    }
                    for(int j=0;j<10;j++)
                        c[row][col].PossValArray[j]=1;

                    //row scan

                    for(int i=0;i<9;i++)
                    {
                        if(c[row][i].giveval()!=0&&c[row][col].PossValArray[c[row][i].giveval()] ==1)
                        {

                            c[row][col].PossValArray[c[row][i].giveval()]=0;

                        }

                    }

                    //col scan

                    for(int i=0;i<9;i++)
                    {
                        if(c[i][col].giveval()!=0&&c[row][col].PossValArray[c[i][col].giveval()] ==1)
                        {

                            c[row][col].PossValArray[c[i][col].giveval()]=0;

                        }
                    }


                    //Box scan

                    for(int i=c[row][col].boxrow();i<(c[row][col].boxrow()+3);i++)
                    {
                        for(int j=c[row][col].boxcol();j<(c[row][col].boxcol()+3);j++)
                        {
                            if(c[i][j].giveval()!=0&&c[row][col].PossValArray[c[i][j].giveval()] ==1)
                            {

                                c[row][col].PossValArray[c[i][j].giveval()]=0;

                            }
                        }
                    }




                    c[row][col].PossVal.clear();
                    for(int elem=1;elem<10;elem++)
                    {
                        if(c[row][col].PossValArray[elem]==1)
                            c[row][col].PossVal.push_back(elem);
                    }



                }
            }
        }
    }
    int solve_cell()
    {

        ofstream outfile;
        outfile.open("exout.txt",ios::app);
        int cnt=0;
        for(int row=0;row<9;row++)
        {
            for(int col=0;col<9;col++)
            {

                if(c[row][col].PossVal.size()==1)
                {

                    c[row][col].setval(c[row][col].PossVal.back());

                    //outfile<<"Set Cells with single possible values"<<c[row][col].giveval()<<"at ("<<row+1<< ","<<col+1<<")"<<endl;

                    cnt++;

                }

            }
        }
        outfile.flush();
        outfile.close();
        return cnt;
    }
    int solve_num()
    {
        ofstream outfile;
        outfile.open("exout.txt",ios::app);
        for(int row=0;row<9;row++)
        {
            for(int col=0;col<9;col++)
            {

                if(c[row][col].giveval()==0)
                {


                    for(int i=0;i<c[row][col].PossVal.size();i++)
                    {


                        //row scan

                        int cnt=0;
                        for(int j=0;j<9;j++)
                        {

                            if(  c[row][j].PossValArray[c[row][col].PossVal[i]]==1 )
                                cnt++;

                        }
                        if(cnt==1)
                        {
                            c[row][col].setval(c[row][col].PossVal[i]);
               //             outfile<<"Setting the value "<<c[row][col].PossVal[i]<<"for("<<row+1<< ","<<col+1<<") using row scan w.r.t num"<<endl;
                            return cnt;
                        }

                        //col scan

                        cnt=0;
                        for(int j=0;j<9;j++)
                        {

                            if(  c[j][col].PossValArray[c[row][col].PossVal[i]]==1 )
                                cnt++;

                        }
                        if(cnt==1)
                        {
                            c[row][col].setval(c[row][col].PossVal[i]);
                    //        outfile<<"Setting the value"<<c[row][col].PossVal[i]<<"for ("<<row+1<< ","<<col+1<<") using col scan w.r.t num"<<endl;
                            return cnt;
                        }



                        //Box scan
                        cnt=0;
                        for(int k=c[row][col].boxrow();k<(c[row][col].boxrow()+3);k++)
                        {
                            for(int j=c[row][col].boxcol();j<(c[row][col].boxcol()+3);j++)
                            {

                                if(  c[k][j].PossValArray[c[row][col].PossVal[i]]==1 )
                                    cnt++;

                            }
                        }
                        if(cnt==1)
                        {
                            c[row][col].setval(c[row][col].PossVal[i]);
                       //      outfile<<"Setting the value"<<c[row][col].PossVal[i]<<"for ("<<row+1<< ","<<col+1<<") using box scan w.r.t num"<<endl;
                            return cnt;
                        }

                    }
                }
            }

        }
        outfile.flush();
        outfile.close();

        return 0;
    }
    int validate()
    {
        int digits[10]={0};
        for(int row=0;row<9;row++)
        {
            for(int col=0;col<9;col++)
            {
                if(c[row][col].giveval()==0)
                {
                    if(c[row][col].PossVal.size()==0)
                        return -1;
                    else
                        return 0;
                }
                digits[c[row][col].giveval()]++;

            }
        }
        for(int i=1;i<10;i++)
        {
            if(digits[i]!=9)
                return -1;
        }


        return 1;


    }
    void minguess(int& minRow,int& minCol )
    {
        int temp=10;
        for(int row=0;row<8;row++)
        {
            for (int col=0;col<8;col++)
            {
                if(c[row][col].PossVal.size()!=0)
                {
                    if(c[row][col].PossVal.size()<=temp)
                    {
                        temp=c[row][col].PossVal.size();
                        minRow=row;
                        minCol=col;

                    }

                }

            }
        }
    }

    int solvetable()
    {
        int i=0;
        int j=0;
        int k;
        do
        {
            do
            {

                i=solve_cell();
                update_possible_vals();

            }while(i>0);

            do
            {

                j=solve_num();
                update_possible_vals();

            }while(j>0);

            if(i==0&&j==0&&validate()==0)
            {
                ofstream outfile;
                outfile.open("exout.txt",ios::app);
              // outfile<<"**********Entering guessing mode***********************************************"<<endl;


                int row=0;
                int col=0;
                int res,m;
                do
                {

                    minguess(row,col);
                    m=c[row][col].PossVal.size();
                    for(int n=0;n<c[row][col].PossVal.size();n++)
                    {

                        int temp[9][9];
                        for(int e=0;e<9;e++)
                        {
                            for (int f=0;f<9;f++)
                            {
                                temp[e][f]=c[e][f].giveval();

                            }
                        }
                        c[row][col].setval(c[row][col].PossVal[n]);
                     //   outfile<<"The guessed value is "<<c[row][col].giveval()<<"at ("<<row+1<<","<<col+1<<")"<<"with size"<<m<<endl;
                        update_possible_vals();
                        res=solvetable();
                        if(res==1)
                            return 1;
                        else
                        {
                            for(int e=0;e<9;e++)
                            {
                                for (int f=0;f<9;f++)
                                {
                                    c[e][f].setval(temp[e][f]);

                                }
                            }

                            update_possible_vals();
                           }

                   // outfile<<"The guessed value failed"<<endl;
                     }
                    return -1;
                }while(1);

                outfile.flush();
                outfile.close();
            }
        }while(validate()==0);

        k= validate();
        if(k==-1)
        {
           return -1;
        }
        if(k==1)
        {
            cout<<"Success you have your answer"<<endl;
            return 1;
        }


    }

};

int main()
{

    Table t;
    t.get_table();
    t.show_table();
    t.update_possible_vals();
    t.solvetable();
    t.show_table();

    
}



