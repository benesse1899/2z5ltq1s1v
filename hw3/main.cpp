#include <stdio.h>
#include <vector>
#include "convexhull.h"
#include "divideandconquer.h"

using namespace std;

int main()
{
    //修改zzpengg所寫的讀檔程式
    FILE *inputFile;
    inputFile = fopen("test3.txt","r");
    if(!inputFile)
    {
        printf("檔案開啟失敗");
        exit(1);
    }

    //使用vector儲存座標
    double x,y;
    std::vector<Point> myvector;
    while(fscanf(inputFile,"%lf %lf",&x,&y)!=EOF)
    {
        Point *temp = new Point;
        temp->x=x;
        temp->y=y;
        myvector.push_back(*temp);
    }
    fclose(inputFile);

    //spec保證vector儲存元素為連續的，當陣列使用ok!
    //delete convexHull(&myvector[0], myvector.size());

    cout << "number of points : "<< myvector.size() <<endl;

    //會返回convexhull上的所有點的vector pointer。程式結束前釋放掉vector pointer。
    delete dc(myvector);
    return 0;
}
