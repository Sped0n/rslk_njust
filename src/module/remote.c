#include "remote.h"

#define IR_RXD GPIO_PORT_P5, GPIO_PIN7
#define IR_Remote GPIO_PORT_P4, GPIO_PIN4
#define REMOTE_ID 0
uint8_t IRcount = 0;
uint16_t IRCapValue1 = 0;
uint16_t IRCapValue2 = 0;
uint16_t IRCapValue = 0;

uint8_t key = 0;

void remote_init(void) {

    GPIO_setAsPeripheralModuleFunctionInputPin(IR_RXD, GPIO_PRIMARY_MODULE_FUNCTION); //reuse port
    /* timer config */
    Timer_A_ContinuousModeConfig continuousModeConfig =
            {
                    TIMER_A_CLOCKSOURCE_SMCLK,           // SMCLK Clock Source
                    TIMER_A_CLOCKSOURCE_DIVIDER_12,       // SMCLK/12 = 1MHz
                    TIMER_A_TAIE_INTERRUPT_ENABLE,       // overflow interrupt
                    TIMER_A_SKIP_CLEAR                   // timer reset
            };
    Timer_A_configureContinuousMode(TIMER_A2_BASE, &continuousModeConfig); //continuous counter mode
    /* Timer_A capture mode */
    Timer_A_CaptureModeConfig captureModeConfig1 =
            {
                    TIMER_A_CAPTURECOMPARE_REGISTER_2,        // CC Register 2
                    TIMER_A_CAPTUREMODE_RISING_AND_FALLING_EDGE,// posedge and negedge
                    TIMER_A_CAPTURE_INPUTSELECT_CCIxA,        // CCIxB Input Select
                    TIMER_A_CAPTURE_SYNCHRONOUS,              // synchronized capture
                    TIMER_A_CAPTURECOMPARE_INTERRUPT_ENABLE,  // interrupt capture
                    TIMER_A_OUTPUTMODE_OUTBITVALUE            // output value
            };
    Timer_A_initCapture(TIMER_A2_BASE, &captureModeConfig1);
    //interrupt flag reset
    Timer_A_clearCaptureCompareInterrupt(TIMER_A2_BASE, TIMER_A_CAPTURECOMPARE_REGISTER_2);
    Timer_A_clearInterruptFlag(TIMER_A2_BASE);

    Interrupt_enableInterrupt(INT_TA2_N);
    Timer_A_startCounter(TIMER_A2_BASE, TIMER_A_CONTINUOUS_MODE);

    GPIO_setAsOutputPin(IR_Remote);
    GPIO_setOutputLowOnPin(IR_Remote);
}

// remote status
// [7]: get synchronized data
// [6]: get button status
// [5]: keep flag
// [4]: 0 for capture posedge, 1 for capture negedge
// [3:0]: overflow timer

uint8_t Romsta; // guide flag
uint32_t RmtRec = 0; // data from IR remote
uint8_t RmtCnt = 0; // times of button being pressed

void TA2_N_IRQHandler(void) {
    /* overflow interrupt */
    if (Timer_A_getEnabledInterruptStatus(TIMER_A2_BASE)) {
        Timer_A_clearInterruptFlag(TIMER_A2_BASE);
        // have already got data
        if (Romsta & 0x80) {
            IRcount++;
            Romsta &= ~0X10; // reset posedge captured flag
            if ((Romsta & 0X03) == 0X00)
                Romsta |= 1 << 6; // data collected flag
            if ((Romsta & 0X0F) < 2)
                Romsta++;
            else {
                Romsta &= ~(1 << 7); //reset guide flag
                Romsta &= 0XF0;    //reset counter
            }
        }
    }
    /* capture interrupt */
    if (Timer_A_getCaptureCompareEnabledInterruptStatus(TIMER_A2_BASE, TIMER_A_CAPTURECOMPARE_REGISTER_2)) {
        Timer_A_clearCaptureCompareInterrupt(TIMER_A2_BASE, TIMER_A_CAPTURECOMPARE_REGISTER_2);
        /* capture negedge */
        if (Timer_A_getSynchronizedCaptureCompareInput(TIMER_A2_BASE, TIMER_A_CAPTURECOMPARE_REGISTER_2,
                                                       TIMER_A_READ_CAPTURE_COMPARE_INPUT)
            == TIMER_A_CAPTURECOMPARE_INPUT_LOW) {
            IRCapValue2 = Timer_A_getCaptureCompareCount(TIMER_A2_BASE, TIMER_A_CAPTURECOMPARE_REGISTER_2);
            IRCapValue = IRCapValue2 - IRCapValue1 + IRcount * 65536;
            IRcount = 0;
            /* receive guide flag */
            if (Romsta & 0x80) {
                if (IRCapValue > 300 && IRCapValue < 800)// 560us
                {
                    RmtRec <<= 1;
                    RmtRec |= 0;
                } else if (IRCapValue > 1400 && IRCapValue < 1800)    // 1680us
                {
                    RmtRec <<= 1;
                    RmtRec |= 1;
                } else if (IRCapValue > 2200 && IRCapValue < 2600)    // 2.5ms
                {
                    RmtCnt++;
                    Romsta &= 0XF0;
                }
            }
                /* receive synchronized flag*/
            else if (IRCapValue > 4200 && IRCapValue < 4700)        // 4.5ms
            {
                Romsta |= 1 << 7;    // receive synchronized flag successfully
                RmtCnt = 0;        // reset RmtCnt
                RmtRec = 0;
            }
            Romsta &= ~(1 << 4);
        }
            /* capture posedge */
        else {
            IRCapValue1 = Timer_A_getCaptureCompareCount(TIMER_A2_BASE, TIMER_A_CAPTURECOMPARE_REGISTER_2);
            Romsta |= 0x10;
            IRcount = 0;
        }
    }
}

uint8_t remote_scan(void) {
    uint8_t sta = 0;
    uint8_t t1, t2;
    if (Romsta & 0x40) {
        t1 = RmtRec >> 24;// get address true form
        t2 = (RmtRec >> 16) & 0xff;// get address one's complement
        if ((t1 == (uint8_t) ~t2) && t1 == REMOTE_ID)//check remote ID and input
        {
            t1 = RmtRec >> 8;
            t2 = RmtRec;
            if (t1 == (uint8_t) ~t2) sta = t1;//input correct
        }
        if ((sta == 0) || ((Romsta & 0X80) == 0))// input error/button is not pressed
        {
            // reset
            Romsta &= ~(1 << 6);
            RmtCnt = 0;
        }
    }
    return sta;
}