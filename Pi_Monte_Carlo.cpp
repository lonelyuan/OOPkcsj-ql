#include <iostream>
#include <ctime>
#define _USE_MATH_DEFINES
#include <cmath>
using namespace std;


struct Point{ float x,y; };


class Pi_Monte_Carlo{
    private:
        double Pi; //圆周率的值，随便初始化一个值

        float epsilon; // 精度
        Point* p_list; // 点坐标数组
        int N; // N:数组长度

    public:
        Pi_Monte_Carlo(int p_size = 1000, float e = 1e-6){
            Pi = 0, N = p_size, epsilon = e;
            p_list = (Point*)malloc(sizeof(Point) * N);//开辟数组空间
            srand(time(0)); // 随机数初始化
        }
        // void get_stat();// 打印信息
        void solve(); // 主迭代函数

        void get_p(Point* p); //填充p
        bool check_p(Point* p); //检查p
};

// void Pi_Monte_Carlo::get_stat(){
//     printf("Pi:%f\n", Pi);
//     printf("%f,%f\n", p_list[0].x, p_list[0].y);
// }

void Pi_Monte_Carlo::get_p(Point* p){
    float xx = rand()/(float)RAND_MAX, yy = rand()/(float)RAND_MAX; //范围[0,1]
    p->x = xx;
    p->y = yy;
}
bool Pi_Monte_Carlo::check_p(Point* p){
    float dx = p->x - 0.5, dy = p->y - 0.5; // 到(0.5,0.5)的距离
    // printf("%f %f    ", dx, dy);
    if (dx * dx + dy * dy <= 0.5*0.5) //距离平方
        return true;
    else
        return false;
}

void Pi_Monte_Carlo::solve(){
    long n = 0, m = 0; // n:击中数（在圆内的点） m:总点数（m<=N）
    double pi = 0;
    do{
        Pi = pi;
        for (int i = 0; i < N; i++) //生成N个随机点
        {
            // Point *p = new Point;
            // p_list[i] = get_p(p);
            get_p(&p_list[i]);
            m++;
            if (check_p(&p_list[i])) n++;
        }
        pi = 4*(double)n / (double)m;

        printf("m: %d, n: %d, new_pi:%f, old_pi: %f\n", m, n, pi, Pi);
    } while (abs(pi - Pi) >= epsilon); // 边界条件：是否到精度
    Pi = pi;
    printf("final_Pi:%f\n", Pi);
    // get_stat();
}


int main(){
    // Point p={1,2};
    // printf("%f",p.x);

    Pi_Monte_Carlo P = Pi_Monte_Carlo();
    P.solve();
}



// double getPi()
// {
//     srand(time(0));
//     const double TIMES = 1e6;
//     double hints = 0;
//     for(int i=0;i<TIMES;i++){
//         double x = rand() /(double)RAND_MAX;
//         double y = rand() / (double)RAND_MAX;
//         if(x*x + y *y <= 1.0){ //落在圆内 概率为1/4*pi*r^2 / r^2 = pi / 4
//             hints++;
//             // printf("++\n");
//         }
//     }
//     double pi = (hints / TIMES) * 4;
//     return pi;
// }

// int main(){
//     printf("%f",getPi());
//     return 0;
// }
