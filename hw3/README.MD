# 作業3 Find Convex Hull Readme.md
###### tags: `演算法`

## 作業題目
寫出一個divide and conquer程式解決convex hull problem

其中，找中位數之功能以呼叫quicksort排序後再找出中位數，quicksort必需以自己寫，並以recursive function 實作(同作業1)。

從檔案test1.txt讀入點座標，每列代表一個點座標，x 與y座標間以空格分開，

自行給頂點編號1—n，直到End of file(點數最多2000) (同作業1)

輸出convex hull，

輸出時由x座標最小的頂點(若相同由y座標最小)開始輸出，依逆時針方向依序輸出 編號與座標，最後並輸出convex hull上的頂點總個數。

另外必須輸出最後合併的動作時，左邊與右邊的convex hull，輸出格式同前。


## 整份程式碼修改自[Convex Hull | Set 2 (Graham Scan)](http://www.geeksforgeeks.org/convex-hull-set-2-graham-scan/)

## 以~~stack~~ vector儲存Point
為了在傳遞Point集合時一併傳遞集合大小，使用vector取代stack，受影響的有:
```c++
Point nextToTop(stack<Point> &S)
```
```c++
// Create an empty stack and push first three points
// to it.
stack<Point> S;
S.push(points[0]);
S.push(points[1]);
S.push(points[2]);
```

## convexHull會返回vector
原本的 
`void convexHull(Point points[], int n)`
改為
`std::vector<Point>* convexHull(Point points[], int n);`
函式結束時會回傳vector point，裡面是convex hull上的點

## 加入divide and conquer function
divideandconquer.h
divideandconquer.cpp

## int main()
加入讀檔功能，並以vector儲存Points，結束讀檔後呼叫dc()