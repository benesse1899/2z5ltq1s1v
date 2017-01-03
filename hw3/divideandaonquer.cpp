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
    //arr太小不可分割成兩個集合
    if (arr.size() < 3 )
    {

        /*cout << "Cannot divide! ";
        show_vect(arr);*/
        std::vector<Point> *arr_temp= new std::vector<Point>(arr.begin(),arr.end());
        return arr_temp;
    }

    //主要功能

    //以x排序arr
    qsort(&arr[0], arr.size(), sizeof(Point), dc_compare_by_x);

    //以中位數為分隔，複製原有集合arr，分隔成兩個新集合，函式結束時摧毀。
    int middle=arr.size()/2+1;
    std::vector<Point> arr_a(&arr[0], &arr[middle]);
    std::vector<Point> arr_b(&arr[middle], &arr[arr.size()]);

    //兩個新集合進行dc後產生新的vector pointer
    std::vector<Point> *arr_a_= dc(arr_a);
    std::vector<Point> *arr_b_= dc(arr_b);

    //秀一下
    cout << "---Before merging---\n";
    cout << "  left array:";
    show_vect(*arr_a_);
    cout << " right array:";
    show_vect(*arr_b_);
    cout <<endl;

    //合併arr_a_ 和 arr_b_成為arr_ab，然後刪除兩個vector pointer。arr_ab函式結束時摧毀
    std::vector<Point> arr_ab;
    arr_ab.reserve(arr_a_->size()+arr_b_->size());
    arr_ab.insert(arr_ab.end(),arr_a_->begin(),arr_a_->end());
    arr_ab.insert(arr_ab.end(),arr_b_->begin(),arr_b_->end());
    delete arr_a_;
    delete arr_b_;

    //秀一下
    cout << "---After merging---\n";
    cout << "merged array:";
    show_vect(arr_ab);
    cout << endl;

    //產生新的Convexhull。修改geeksforgeek convexhull函式，使其返回vector pointer
    return convexHull(&arr_ab[0], arr_ab.size());
}
