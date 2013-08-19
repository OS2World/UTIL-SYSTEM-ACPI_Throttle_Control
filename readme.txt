ACPIThrottle is a quick and dirty attempt to make user of throttling to reduce power usage and heat creation on 
systems running ACPI (ACPI installed from eCS 2.0 or from the Betazone).  Source code is included, I have compiled
with Open Watcom 1.7a, GCC 3.5.5, and GCC 4.3.2... I think it will compile unchanged with the Visualage Compilers.
The basic functions are based off of the idle time of the CPU, this code I pulled from EDM2 which in turn was 
pulled from the SMP addendum.inf in the OS2 Toolkit.  Setgetthrtl.exe and setgetstate.exe should be in the path or
in the same directory as ACPIThrottle.exe.  Uniprocessor systems will see errors but they should not be an issue
so long as at least one line shows successful.  I am currently running it from my startup.cmd as detached, but when
first run I suggest running it in a session so that the status can be seen initialy.  If setgetthrtl.exe is run with
no parameters you can check to see if it is doing anything (same with setgetstate.exe).  
ACPIThrottle.exe will accept a parameter for how many seconds to wait between checks (1-9).  The initial code that this
was taken from required a parameter, I changed it to default to 5.  I have found that 4 seems to be the best, less than
4 seconds seems to cause CPU usage to bounce a bit due to running setgetthrtl.exe.


By: Andy Willis 