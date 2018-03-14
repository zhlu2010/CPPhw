#include <iostream>
#include <math.h>
#include <iomanip>
#include <ctime>
using namespace std;
class JulianDate {
private:
    static int EPOCH;
    int mon, day, year, hour, min, second;
    // this representation would make difference VERY UGLY
    // diff between Jan. 1 2001 12:03:04  and Feb 26 2028 11:19:02
    double jday; // number of days since epoch
public:
    JulianDate(int y,int m, int d ,  int h, int min, int s): year(y),mon(m),day(d),hour(h), min(min), second(s){
        jday = 367*year-trunc(7*(year+trunc((mon+9)/12))/4)+trunc((275*mon)/9)+day+1721013.5-0.5*sign(100*year+mon-190002.5)+0.5;
        }
    JulianDate(){
        time_t now = time(0);
        tm *ltm = localtime(&now);
        year = 1900 + ltm->tm_year;
        mon = 1 + ltm->tm_mon;
        day =  ltm->tm_mday ;
        hour =  ltm->tm_hour ;
        min = ltm->tm_min ;
        second = ltm->tm_sec;
        jday = 367*year-trunc(7*(year+trunc((mon+9)/12))/4)+trunc((275*mon)/9)+day+1721013.5-0.5*sign(100*year+mon-190002.5)+0.5;
    }
    int sign(double i){
        if(i>0) return 1;
        else return -1;
    }
    double getJday(){
        return jday;
    }
    friend double operator - (JulianDate a, JulianDate b){
        return a.jday-b.jday;
    }
    friend JulianDate operator + (JulianDate a, int b){
        int i,j,k,l,n,jd;
        jd = a.jday+b;
        l = jd+68569;
        n = 4* l/146097;
        l =  l-(146097*n+3)/4;
        i= 4000*(l+1)/1461001;
        l= l-1461*i/4+31;
        j= 80*l/2447;
        k= l-2447*j/80;
        l= j/11;
        j= j+2-12*l;
        i= 100*(n-49)+i+l;
        return JulianDate(i,j,k,a.hour,a.min,a.second);
    }
    friend ostream& operator <<(ostream&s , JulianDate a){
        s<<"("<<a.year<<","<<a.mon<<","<<a.day<<","<<a.hour<<","<<a.min<<","<<a.second<<")"<<"\n";
    }
    double getYear(){
        return year;
    }
    double getMonth(){
        return mon;
    }
    double getDay(){
        return day;
    }
    double getHour(){
        return hour;
    }
    double getMin(){
        return min;
    }
    double getSec(){
        return second;
    }
};
int main() {
    JulianDate newyear(2018, 1, 1, 0,0,0);
    JulianDate valentine(2018, 2, 14, 12,0,0);
    JulianDate today; // get it from the system time: time(nullptr)
    // localtime

    double days = valentine - newyear;
    JulianDate due = today + 7;
    cout << due << '\n';

    cout << "\nyear: " << newyear.getYear()
         << "\nmonth: " << newyear.getMonth()
         << "\nday: " << newyear.getDay()
         << "\nhour: " << newyear.getHour()
         << "\nmin: " << newyear.getMin()
         << "\nsec: " << newyear.getSec() << '\n';

    return 0;
}