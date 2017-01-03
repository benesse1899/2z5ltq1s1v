#include <stdio.h>
#include <vector>
#include "convexhull.h"
#include "divideandconquer.h"

using namespace std;

int main()
{
    //�ק�zzpengg�Ҽg��Ū�ɵ{��
    FILE *inputFile;
    inputFile = fopen("test3.txt","r");
    if(!inputFile)
    {
        printf("�ɮ׶}�ҥ���");
        exit(1);
    }

    //�ϥ�vector�x�s�y��
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

    //spec�O��vector�x�s�������s�򪺡A��}�C�ϥ�ok!
    //delete convexHull(&myvector[0], myvector.size());

    cout << "number of points : "<< myvector.size() <<endl;

    //�|��^convexhull�W���Ҧ��I��vector pointer�C�{�������e����vector pointer�C
    delete dc(myvector);
    return 0;
}
