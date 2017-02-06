#!/bin/bash

# Lab LinuxInfo
# Brother Jones, CS 345, Operating Systems
# Brady Field

############################################################################
#
# Summary:
#    Displays various system information on the current machine running
#    Linux
#
############################################################################
# CPU model
echo "What is the CPU type and model?"
printf "   $(grep -m 1 "model name" /proc/cpuinfo | cut -d':' -f2)\n\n"

# processor information
echo "How many processors on this system?"
P=$(grep "physical id" /proc/cpuinfo | tail -1 | cut -d':' -f2)
P=$(echo "$P+1" | bc) # turn string into a number for comparison
# siblings will help with multithread
S=$(grep "siblings" /proc/cpuinfo | tail -1 | cut -d':' -f2)
C=$(grep "cpu cores" /proc/cpuinfo | tail -1 | cut -d':' -f2) 
printf "    $P processor"
if [ $P -gt "1" ]
then
printf "s" # more than 1 processor?
fi

printf " with"
printf "$C cores each "
# hyperthreading
if [ $S == $C ]
then
printf "(not hyperthreaded)\n\n"
else
printf "(hyperthreaded)\n\n"
fi

# version
echo "What version of the Linux kernel is being used?"
printf "    $(cat /proc/version | cut -d' ' -f1-3)$(cat /proc/version | cut -d')' -f5 | cut -d' ' -f1-8)\n\n"
# uptime
echo "How long has it been since the system was last booted?"
printf "    $(uptime | cut -d' ' -f3-5)  $(uptime | cut -d' ' -f6 | cut -d',' -f1)\n\n"
# execution
echo "How much CPU execution time has been spent in user, system and idle modes?"
# awk is nice for variables
awk '/^cpu[^0-3]/{printf "    USER: %.2f seconds\n    SYSTEM: %.2f seconds\n    IDLE: %.2f seconds\n\n", ($2+$3) * .01, $4  * .01, $5 * .01;}' /proc/stat
# memory
echo "How much memory is on the machine?"
printf "    $(grep "MemTotal:" /proc/meminfo)\n\n"
echo "How much memory is currently available?"
printf "    $(grep "MemFree:" /proc/meminfo)\n\n"
# awk works better than grep for chopping out multiple spacing issues
echo "How many kBytes have been read and written to the disk since the last reboot?"
iostat -k | awk '/^sda[^0-9]/{printf "    Read: %s kB\n    Written: %s kB\n\n",$5,$6;}'

# various stats
echo "How many processes have been created since the last reboot?"
printf "    Processes created: $(grep "processes" /proc/stat | cut -d' ' -f2)\n\n"
echo "How many context switches have been performed since the last reboot?"
printf "    Context switches: $(grep "ctxt" /proc/stat | cut -d' ' -f2)\n\n"
echo "What is the current load average for the last 1, 5 and 15 minutes?"
printf "    Load average:$(uptime | cut -d':' -f5)\n"
