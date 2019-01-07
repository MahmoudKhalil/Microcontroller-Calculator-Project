#include "rtc.h"

#define GPIO_PF0_T0CCP0         0x00050007

int hrs;
int mins;
bool update = true;

void RTCMain(void) {
    PortFInit();
    Timer0Init();
    LCDInit();

    TimerEnable(TIMER0_BASE, TIMER_A);

    while(1) {
        if(update) {
            update = false;
            LCDCommand(0x01);
            unsigned char* hrsChars = ParseRTC(hrs);
            LCDCharData(hrsChars, 2);
            LCDData(':');
            unsigned char* minsChars = ParseRTC(mins);
            LCDCharData(minsChars, 2);
        }
    }
}

void PortFInit(void) {
    SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOF);
    while(!SysCtlPeripheralReady(SYSCTL_PERIPH_GPIOF));

    HWREG(GPIO_PORTF_BASE  + GPIO_O_LOCK) = GPIO_LOCK_KEY;
    HWREG(GPIO_PORTF_BASE  + GPIO_O_CR) |= GPIO_PIN_0;

    GPIOPinTypeGPIOInput(GPIO_PORTF_BASE, GPIO_PIN_0);

    GPIOPinConfigure(GPIO_PF0_T0CCP0);
    GPIOPinTypeTimer(GPIO_PORTF_BASE, GPIO_PIN_0);
}

void Timer0Init(void) {
    SysCtlPeripheralEnable(SYSCTL_PERIPH_TIMER0);
    while(!SysCtlPeripheralReady(SYSCTL_PERIPH_TIMER0));

    TimerDisable(TIMER0_BASE, TIMER_A);

    TimerConfigure(TIMER0_BASE, TIMER_CFG_PERIODIC);

    TimerLoadSet(TIMER0_BASE, TIMER_A, 16000000 * 60);

    TimerIntClear(TIMER0_BASE , TIMER_TIMA_TIMEOUT);

    TimerIntRegister(TIMER0_BASE, TIMER_A, Timer0AIntHandler);

    //Get current time
    time_t rawtime;
    struct tm * timeinfo;

    time ( &rawtime );
    timeinfo = localtime ( &rawtime );

    hrs = timeinfo->tm_hour;
    mins = timeinfo->tm_min;

    TimerIntEnable(TIMER0_BASE , TIMER_TIMA_TIMEOUT);
}

void Timer0AIntHandler(void) {
    TimerIntClear(TIMER0_BASE , TIMER_TIMA_TIMEOUT);
    mins++;
    if(mins >= 60) {
        hrs++;
        mins = 0;
        if(hrs >= 24) {
            hrs = 0;
        }
    }

    update = true;
}