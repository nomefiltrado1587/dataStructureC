#include <stdio.h>

int main(){
    int n = 5;
    double a = 2,v=1;

    for (int i = 0;i<n;i++){
        v = v*a;
    }

    printf("%lf",v);
}