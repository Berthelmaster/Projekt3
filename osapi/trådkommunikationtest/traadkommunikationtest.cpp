#include "T1_webApp.hpp"
#include "T2_coffeeOrderHandler.hpp"
#include "T3_localUI.hpp"
#include "T4_timeSetting.hpp"



int main (int argc, char *argv[]){

UART* u;

T2_coffeOrderHandler coh(10, u);
T1_webApp wa(10, coh.getmsgQ());
T3_LocalUI lui(coh.getmsgQ(), u);
T4_timeSetting ts(coh.getmsgQ());

coh.setmsgQ(wa.getmsgQ());

osapi::Thread t2(&coh);
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
