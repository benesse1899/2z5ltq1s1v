#include <iostream>
#include <fstream> /*read from file*/
#include <vector>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

using namespace std;
void quicksort(int *,int *);
void quicksort_vector(std::vector<double*>::iterator,std::vector<double*>::iterator);

int main()
{
    std::vector<double*> coord_ptr;

    /*讀取資料*/
    ifstream myfile;
    myfile.open("test.txt");
    if (myfile.is_open())
    {
        string line;
        char oneline[80],*del;
        while (!myfile.eof())
        {
            double* pair=new double[3]; //放x,y,rank
            int x=0;
            getline(myfile,line); //Read one line
            strcpy(oneline,line.c_str());
            del = strtok(oneline," "); //split it by whitespace
            while(del!=NULL)
            {
                pair[x++] = atof(del); //convert string to float,save it in a double array
                del = strtok(NULL," ");
            }
            coord_ptr.push_back(pair);//save a float pair
        }
        myfile.close();
    }

    //顯示原始資料
    cout <<"以x排序前"<<endl<<"==="<<endl;
    printf("%8s %8s\n","x","y");
    for (std::vector<double*>::iterator it= coord_ptr.begin(); it != coord_ptr.end(); ++it)
    {
        printf("%8.2lf,%8.2lf\n",(*it)[0],(*it)[1]);
    }
    cout <<endl;

    //排序
    quicksort_vector(coord_ptr.begin(),coord_ptr.end()-1);

    //計算rank
    for (std::vector<double*>::iterator it= coord_ptr.begin(); it != coord_ptr.end(); ++it)
    {
        double it_rank=0;
        for (std::vector<double*>::iterator it2= coord_ptr.begin(); it2 != it; ++it2)
        {
            if ((*it)[1]>(*it2)[1]) it_rank++;
        }
        (*it)[2]=it_rank;

    }
    cout <<endl;

    //顯示結果
    cout <<"以x排序後"<<endl<<"==="<<endl;
    printf("%8s %8s %8s\n","x","y","rank");
    int rank_avg=0,rank_max=INT_MIN,rank_min=INT_MAX;
    for (std::vector<double*>::iterator it= coord_ptr.begin(); it != coord_ptr.end(); ++it)
    {
        int temp=(double)((*it)[2]);
        rank_avg+=temp;
        if (temp>rank_max) rank_max=temp;
        if (temp<rank_min) rank_min=temp;
        printf("%8.2lf,%8.2lf %8.0lf\n",(*it)[0],(*it)[1],(*it)[2]);
    }
    cout <<endl;
    cout << "平均rank:" << (double)rank_avg/coord_ptr.size() <<endl;
    cout << "最大rank:" << rank_max <<endl;
    cout << "最小rank:" << rank_min <<endl;

    //釋放記憶體
    for (std::vector<double*>::iterator it = coord_ptr.begin(); it != coord_ptr.end(); ++it)
    {
        delete[] *it;
    }
    return 0;
}



/*
reference:
https://rosettacode.org/wiki/Sorting_algorithms/Quicksort
*/
void quicksort(int * f,int * l)
{
    if (f>=l) return; //array lenth must larger than 1
    int pivot = *f;
    int* left=f;
    int* right=l;
    while(left<=right)
    {
        while (*left<pivot) left++;
        while (*right>pivot) right--;
        if(left<=right)
        {
            swap(*left,*right);
            left++;
            right--;
        }
    }
    quicksort(f,right);
    quicksort(left,l);
    return;
}

//仿造原先的quicksort打造vector版
void quicksort_vector(std::vector<double*>::iterator f,std::vector<double*>::iterator l)
{
    if (f>=l) return; //array lenth must larger than 1
    double pivot = (*f)[0]; //取得x座標
    std::vector<double*>::iterator left=f;
    std::vector<double*>::iterator right=l;
    while(left<=right)
    {
        while ((*left)[0]<pivot) left++;
        while ((*right)[0]>pivot) right--;
        if(left<=right)
        {
            swap(*left,*right);
            left++;
            right--;
        }
    }
    quicksort_vector(f,right);
    quicksort_vector(left,l);
    return;
}
