#include <stdio.h>
#include <stdlib.h>
#include <string.h>

extern double f1(double);
extern double f2(double);
extern double f3(double);
extern double csqrt(double);

double (*mas[4]) (double) = {NULL, f1, f2, f3};

double q;
int iter=0;

double F(double x,double s,double f(double),double g(double))
{
    return s * (f(x) - g(x));
}

void root(double f(double), double g(double), double a, double b, double eps1){
    iter++;
    double s, c;
    if(f(a) - g(a) < 0)
        s = 1;
    else
        s = -1;
    double q1=F(a,s,f,g);
    double q2=F(b,s,f,g);
    c=(a*q2-b*q1)/(q2-q1);
    if(F(c,s,f,g)>-eps1 && F(c,s,f,g)<eps1){
        q=c;
    }
    else {
        root(f, g, c, b, eps1);
    }
}

double integral(double f(double),double a,double b,double eps2){
    double n,sum=0,t,h;
    n = (b - a) * csqrt(b - a)/ csqrt(eps2);
    t=n;
    h=(b-a)/n;
    sum+=(f(a)+f(b))/2;
    for(int i=1;i<n;i++){
        sum+=f(a+i*h);
    }
    sum*=h;
    return sum;
}


int main(int argc,char **argv) {
    double eps = 0.001;
    double eps2 = 0.00001;
    for(int i=1;i<argc;i++){
        if(strcmp(argv[i],"-res")==0) {
            printf("\tРешение задачи\n");
            double x1, x2, x3;
            int i1, i2, i3;
            iter = 0;
            root(f1, f3, -4.5, -3.5, eps);
            x1 = q;
            i1 = iter;
            iter = 0;
            root(f2, f1, -1, -0.1, eps);
            x2 = q;
            i2 = iter;
            iter = 0;
            root(f2, f3, -2, -1, eps);
            x3 = q;
            i3 = iter;
            double S;
            S = integral(f1, x1, x2, eps2) - integral(f2, x3, x2, eps2) - integral(f3, x1, x3, eps2);
            printf("f1(x) пересекает f2(x) в точке x = %lf, y = %lf\n", x2, f1(x2));
            printf("Число итераций = %d\n", i1);
            printf("f1(x) пересекает f3(x) в точке x = %lf, y = %lf\n", x1, f1(x1));
            printf("Число итераций = %d\n", i2);
            printf("f2(x) пересекает f3(x) в точке x = %lf, y = %lf\n", x3, f2(x3));
            printf("Число итераций = %d\n", i3);
            printf("Площадь графика, ограниченного функциями S = %lf\n", S);
        }
        else if(strcmp(argv[i],"-tf")==0){
            int namb;
            double x;
            printf("\tПроверка функции\n");
            printf("Введите аргументы: \nНомер функци = ");
            scanf("%d",&namb);
            printf("Аргумент функции = ");
            scanf("%lf",&x);
            printf("f%d(%lf) = %lf\n",namb,x,mas[namb](x));
        }
        else if(strcmp(argv[i],"-tr")==0){
            int n1,n2;
            double r;
            printf("\tПроверка корней функции\n");
            printf("Введите аргументы(через пробел): \nНомера функций = ");
            scanf("%d%d",&n1,&n2);
            root(mas[n1],mas[n2],-5,-0.1,eps);
            r=q;
            printf("Решение уравнения f%d(x)=f%d(x) : x = %lf\n",n1,n2,r);
        }
        else if(strcmp(argv[i],"-ti")==0){
            int namb;
            double a,b,integ;
            printf("Проверка интеграла функции\n");
            printf("Введите аргументы: \nНомер функци = ");
            scanf("%d",&namb);
            printf("Введите границы отрезка [a,b](через пробел) ");
            scanf("%lf %lf",&a,&b);
            integ=integral(mas[namb],a,b,eps2);
            printf("Определенный интеграл функции f%d(x) на отрезке [%lf,%lf] = %lf\n",namb,a,b,integ);
        }
        else if(strcmp(argv[i],"-f")==0) {
            printf("Функции, поставленные в задаче:\n");
            printf("f1(x) = exp(x)+2\n");
            printf("f2(x) = -1/x\n");
            printf("f3(x) = -2(x+1)/3\n");
        }
        else if(strcmp(argv[i],"-help")==0){
            printf("-res        Выводит ответ на поставленную задачу\n");
            printf("-tf         Выводит значение f(x)\n");
            printf("-tr         Выводит значение корня уравнения f(x)=g(x)\n");
            printf("-ti         Выводит значение определенного интеграла функции f(x) на [a,b]\n");
            printf("-help       Выводит на экран ключи и их описание\n");
            printf("-f          Выводит на экран функции, поставленные в задаче\n");
        }
        else{
            printf("Неизвестный ключ %s\n",argv[i]);
            printf("Введите -help для получения информации о ключах\n");
        }
    }

    return 0;
}
