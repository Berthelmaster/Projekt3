#include "T1_webApp.hpp"
#include "T2_coffeeOrderHandler.hpp"
#include "T3_localUI.hpp"
#include "T4_timeSetting.hpp"


int main (int argc, char *argv[]){

T2_coffeOrderHandler cof(10);
T1_webApp wa(10, cof.getmsgQ());
T3_LocalUI lui(cof.getmsgQ());
T4_timeSetting ts(cof.getmsgQ());

cof.setmsgQ(wa.getmsgQ());

osapi::Thread t2(&cof);
osapi::Thread t1(&wa);
osapi::Thread t3(&lui);
osapi::Thread t4(&ts);

t2.start();
t1.start();
t3.start();
t4.start();

t2.join();
t1.join();
t3.join();
t4.join();
}
