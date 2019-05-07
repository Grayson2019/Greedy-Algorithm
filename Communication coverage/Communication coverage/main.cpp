//
//  main.cpp
//  Communication coverage
//
//  Created by 杨浩 on 2019/5/7.
//  Copyright © 2019 Grayson. All rights reserved.
//

#include <iostream>
#include <math.h>
using namespace std;
// 声明小岛坐标结构体
typedef struct{
    float x; // 横坐标
    float y; // 纵坐标
    float left; // 左端点
    float right; // 右端点
}islePoint;

// 声明基站坐标结构体
typedef struct BaseStation{
    float x;
    float y = 0;
}BSPoint;
BSPoint BS[10];
int BSIndex = 0;
bool cmp(islePoint pointA, islePoint pointB){
    return pointA.x < pointB.x;
}

void findInterval(islePoint *a, int d){
    double range = sqrt(pow(d, 2) - pow(a->y, 2));
    a->left = a->x - range;
    a->right = a->x + range;
}

int main(int argc, const char * argv[]) {
    int isleAmount; // 小岛的数量
    int d; // 基站覆盖范围的半径
    cin >> isleAmount;
    cin >> d;
    islePoint isle[isleAmount];

    for (int i = 0; i < isleAmount; i++) {
        cin >> isle[i].x;
        cin >> isle[i].y;
    }
    // 对islePoint结构体 以横坐标x为比较指标 升序排序
    sort(isle, isle+isleAmount, cmp);
    findInterval(&isle[0], d);
    
    for (int i = 0; i < isleAmount-1; i++) {
        findInterval(&isle[i+1], d);
        if (isle[i].right < isle[i+1].left) {
            BS[BSIndex].x = isle[i].right;
            BSIndex++;
            continue;
        }
        if (isle[i].right <= isle[i+1].right){
            isle[i+1].right = isle[i].right;
        }
        if (isle[i].left >= isle[i+1].left) {
            isle[i+1].left = isle[i].left;
        }
    }
    BS[BSIndex].x = isle[isleAmount-1].right;
    cout << BSIndex+1 << "\n";
    for (int i = 0; i < 10; i++) {
        if (BS[i].x == 0) {
            break;
        }
        cout << BS[i].x << " " << BS[i].y << "\n";
    }
}
