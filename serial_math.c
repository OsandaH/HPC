#include <iostream>
#include <math.h>

void function(){
    int id;
    float salary;
    double price;
    char code;

    printf("size of int: %u", sizeof(char));
}

void mathfns(double x, double y, double theta){
    // ceil
    printf("ceil value of %.2f is: %.2f",x,ceil(x));
    //floor
    printf("\nFloor value of %.2f is: %.2f",x,floor(x));
    //absolute value
    printf("\nabsolute value of %.2f is: %f",x,fabs(x));
    // ln value
    printf("\nlog (%.2f)= %.2f",x,log(x));
    //log 10
    printf("\nlog_10 (%.2f)= %.2f",x,log10(x));
    // returns the remainder 
    printf("\nremainder of (%.2f/ %.2f)= %.2f",x,y,fmod(x,y));
    //square root
    printf("\nsquare root of %.2f is %.2f",x,sqrt(x));
    //power
    printf("\n(%.2f)^%.2f= %.2f",x,y,pow(x,y));
    //exponential e^x
    printf("\ne^(%.2f) = %.2f",y,exp(y));
    
    //degree to radian
    double THETA = (M_PI/180)*theta;
    //sine
    printf("\nSine value of %.1f degrees = %.2f",theta, sin(THETA));
    //cos
    printf("\nCos value of %.1f degrees = %.2f",theta, cos(THETA));
    //sine inverse asin,acos,atan 
    printf("\nSine inverse value of %.1f  = %.2f",0.5, asin(0.5));

}

int main(){
    // function();
    //mathfns(double x, double y, double theta)
    mathfns(100,3,30);
    return 0;
}
