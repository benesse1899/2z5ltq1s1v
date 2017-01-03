#include "divideandconquer.h"

using namespace std;

void show_vect(std::vector<Point> &arr)
{
    cout << "arr:";
    for (std::vector<Point>::iterator iter = arr.begin(); iter != arr.end(); ++iter)
    {
        cout << "(" << iter->x << ","<< iter->y << ")"<<" ";
    }
    cout <<endl;
}

int dc_compare_by_x(const void *vp1, const void *vp2)
{
    Point *p1 = (Point *)vp1;
    Point *p2 = (Point *)vp2;

    return (p2->x>= p1->x) ? 1 : -1;
}


std::vector<Point>* dc(std::vector<Point> &arr)
{
    //arr�Ӥp���i���Φ���Ӷ��X
    if (arr.size() < 3 )
    {

        /*cout << "Cannot divide! ";
        show_vect(arr);*/
        std::vector<Point> *arr_temp= new std::vector<Point>(arr.begin(),arr.end());
        return arr_temp;
    }

    //�D�n�\��

    //�Hx�Ƨ�arr
    qsort(&arr[0], arr.size(), sizeof(Point), dc_compare_by_x);

    //�H����Ƭ����j�A�ƻs�즳���Xarr�A���j����ӷs���X�A�禡�����ɺR���C
    int middle=arr.size()/2+1;
    std::vector<Point> arr_a(&arr[0], &arr[middle]);
    std::vector<Point> arr_b(&arr[middle], &arr[arr.size()]);

    //��ӷs���X�i��dc�Უ�ͷs��vector pointer
    std::vector<Point> *arr_a_= dc(arr_a);
    std::vector<Point> *arr_b_= dc(arr_b);

    //�q�@�U
    cout << "---Before merging---\n";
    cout << "  left array:";
    show_vect(*arr_a_);
    cout << " right array:";
    show_vect(*arr_b_);
    cout <<endl;

    //�X��arr_a_ �M arr_b_����arr_ab�A�M��R�����vector pointer�Carr_ab�禡�����ɺR��
    std::vector<Point> arr_ab;
    arr_ab.reserve(arr_a_->size()+arr_b_->size());
    arr_ab.insert(arr_ab.end(),arr_a_->begin(),arr_a_->end());
    arr_ab.insert(arr_ab.end(),arr_b_->begin(),arr_b_->end());
    delete arr_a_;
    delete arr_b_;

    //�q�@�U
    cout << "---After merging---\n";
    cout << "merged array:";
    show_vect(arr_ab);
    cout << endl;

    //���ͷs��Convexhull�C�ק�geeksforgeek convexhull�禡�A�Ϩ��^vector pointer
    return convexHull(&arr_ab[0], arr_ab.size());
}
