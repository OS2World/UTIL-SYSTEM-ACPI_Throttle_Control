#define INCL_BASE

  #include <os2.h>
  #include <stdio.h>
  #include <stdlib.h>
  #include <string.h>

/* #define DEBUG 1 */

  APIRET APIENTRY DosPerfSysCall(ULONG ulCommand, ULONG ulParm1,
                                 ULONG ulParm2, ULONG ulParm3);

  #define ORD_DOS32PERFSYSCALL       976
#ifndef CMD_KI_RDCNT
  #define CMD_KI_RDCNT           	(0x63)

  typedef struct _CPUUTIL {
    ULONG ulTimeLow;     /* Low 32 bits of time stamp      */
    ULONG ulTimeHigh;    /* High 32 bits of time stamp     */
    ULONG ulIdleLow;     /* Low 32 bits of idle time       */
    ULONG ulIdleHigh;    /* High 32 bits of idle time      */
    ULONG ulBusyLow;     /* Low 32 bits of busy time       */
    ULONG ulBusyHigh;    /* High 32 bits of busy time      */
    ULONG ulIntrLow;     /* Low 32 bits of interrupt time  */
    ULONG ulIntrHigh;    /* High 32 bits of interrupt time */
   } CPUUTIL;

  typedef CPUUTIL *PCPUUTIL;
#endif

  /* Convert 8-byte (low, high) time value to double */
  #define LL2F(high, low) (4294967296.0*(high)+(low))

  /* This is a 1 processor example */
  int main (int argc, char *argv[])
  {
     APIRET      rc;
     int         i, iter, sleep_sec, cputhrtl50;
     double      ts_val, ts_val_prev;
     double      idle_val, idle_val_prev;
     double      busy_val, busy_val_prev;
     double      intr_val, intr_val_prev;
     CPUUTIL     CPUUtil;

     if ((argc < 2) || (*argv[1] < '1') || (*argv[1] > '9')) {
     sleep_sec =5;
     } else
     sleep_sec = *argv[1] - '0';

     DosSetPriority(PRTYS_THREAD, PRTYC_FOREGROUNDSERVER, 15L, 0L);

     cputhrtl50 = 100;
     iter = 0;
     do {
         rc = DosPerfSysCall(CMD_KI_RDCNT,(ULONG) &CPUUtil,0,0);
         if (rc) {
             fprintf(stderr, "CMD_KI_RDCNT failed rc = %d\n",rc);
             exit(1);
         }
         ts_val = LL2F(CPUUtil.ulTimeHigh, CPUUtil.ulTimeLow);
         idle_val = LL2F(CPUUtil.ulIdleHigh, CPUUtil.ulIdleLow);
         busy_val = LL2F(CPUUtil.ulBusyHigh, CPUUtil.ulBusyLow);
         intr_val = LL2F(CPUUtil.ulIntrHigh, CPUUtil.ulIntrLow);

         if (iter > 0) {
             double  ts_delta = ts_val - ts_val_prev;
#ifdef DEBUG
             printf("idle: %4.2f%%  busy: %4.2f%%  intr: %4.2f%%\n",
                    (idle_val - idle_val_prev)/ts_delta*100.0,
                    (busy_val - busy_val_prev)/ts_delta*100.0,
                    (intr_val - intr_val_prev)/ts_delta*100.0);
#endif

         if (((idle_val - idle_val_prev)/ts_delta*100.0) > 70){
         if (((idle_val - idle_val_prev)/ts_delta*100.0) > 80){
         if (((idle_val - idle_val_prev)/ts_delta*100.0) > 90){
             if (cputhrtl50 != 15){
             system( "setgetthrtl 0 15");
             system( "setgetthrtl 1 15");
             system( "setgetstate 0 1");
             system( "setgetstate 1 1");
             cputhrtl50 = 15;}} else
             if (cputhrtl50 != 25){
             system( "setgetthrtl 0 25");
             system( "setgetthrtl 1 25");
             system( "setgetstate 0 1");
             system( "setgetstate 1 1");
             cputhrtl50 = 25;}} else
             if (cputhrtl50 != 50){
             system( "setgetthrtl 0 50");
             system( "setgetthrtl 1 50");
             system( "setgetstate 0 1");
             system( "setgetstate 1 1");
             cputhrtl50 = 50;}}


         if (((idle_val - idle_val_prev)/ts_delta*100.0) < 50){
         if (((idle_val - idle_val_prev)/ts_delta*100.0) < 40){
         if (((idle_val - idle_val_prev)/ts_delta*100.0) < 30){
             if (cputhrtl50 != 100){
             system( "setgetthrtl 0 100");
             system( "setgetthrtl 1 100");
             system( "setgetstate 0 0");
             system( "setgetstate 1 0");
             cputhrtl50 = 100;}} else
             if (cputhrtl50 != 75){
             system( "setgetthrtl 0 85");
             system( "setgetthrtl 1 85");
             system( "setgetstate 0 0");
             system( "setgetstate 1 0");
             cputhrtl50 = 75;}} else
             if (cputhrtl50 != 50){
             system( "setgetthrtl 0 75");
             system( "setgetthrtl 1 75");
             system( "setgetstate 0 0");
             system( "setgetstate 1 0");
             cputhrtl50 = 50;}}

         }

         ts_val_prev = ts_val;
         idle_val_prev = idle_val;
         busy_val_prev = busy_val;
         intr_val_prev = intr_val;

         iter = 1;
         DosSleep(1000*sleep_sec);

     } while (1);
return 0;
  }
