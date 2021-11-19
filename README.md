# Shutter

C code to run on embededd linux systems and control remote controllable shutters with a hacked remote trough GPIOs

---
# Prequisites
You'll need a router flashed with openwrt with at least 6 accesible GPIOs and cron and any ftp server (optional, but highly recommended) installed (for hosting the timetable); at least 1 remote controlled shutter/other appliance, a remote paired to the appliance(s) and 5 opto-isolators (reed relays are fine too). You'll also need to do some soldering as well as cross-compiling the program.

## Hardware (Soldering required)
First you need to wire up the opto-isolators in paralel to the pushbuttons on the remote (As most remotes have them multiplexed connecting the GPIOs directly to the MCU on the remote is not guaranteed to work.) You'll have to experiment with the polarity of the opto-isolators, there's no way I know to tell which should connect where without an oscilloscope/signal analyzer, but resoldering 10 joints is not a big deal. Here's a simplified schematic of what you need to do: 
![Screenshot from 2021-11-19 00-30-00](https://user-images.githubusercontent.com/66648475/142525719-07685def-26b9-439b-a9ab-1a7f121b1b3e.png)
3.3V is 3.3V on the router, MCU reset is the reset pin of the microcontroller on your remote (look for it in the part's datasheet). You need to use any GPIO available to you, but take note which connects to which button, we'll use that later. You also need to connect the remote's ground plane with the router's ground.

## Macros
You also have some macros you'll need to change (and an enum too) to customize the code to your setup.

In main.c:
`FILEPATH` is the path (including filename) to your schedule file (more about it later)
`N_of_Shutters` is how many shutters (appliences) you want to controll
`rolltimelist` is a list containing the time it takes for your shutters to roll down from 0 to 100% in seconds (note that it's a few seconds shorter than the time it takes to roll up) Their index is one less than the channel they are programmed to (channel 0 is usually broadcast).

In shutter.h enum buttons:
`typedef enum buttons:` each action should be equal to the number of the GPIO pin connected to the button

In moving.c :
`RESETPIN`: replace gpio2 in the path with the gpio you connected reset to.

## Schedule file
The schedule file contains a weekly schedule for shutter raising and lowering. An example schedule.txt is provided with the program. It is advised that the router should serve it via FTP. Just be careful not to write windows-style newlines into it, that makes the program go crazy and stuck in an infinite loop.
You can have any number of channels in the schedule file, but you need a table for every day, and in every table all shutters need to have all values in the table. A shutter can be deactivated either by decreasing the roll-percentage to zero or to give it an invalid time of lowering/raising.
The table form (columns separated by | characters) is neccesary as well as the names of the days in full caps.

## Cron configuration
You need to configure cron to call the program in fixed intervalls. Since the rolling of shutters takes quite some time, an intervall shorter than the rolltime of all shutters in sequence will make more instances of the program which can lead to undocumented behaviour. Fortunately there are plenty of cron examples online.

## rc.local
The shell script `/etc/rc.local` is run each time the router is powered on. We'll use this to write a script that enables all of our GPIOs and sets them HIGH (all pins are driven in an inverse logic), for example:
```sh
# exporting available GPIOs to be used by program shutter
GPIOBASE=`cat /sys/class/gpio/gpiochip*/base | head -n1`
set -- 1 2 17 18 19 20 21 # these are the GPIO pins I want to innitialize

cd /sys/class/gpio
for i in $@; do
 echo $i > export; echo out >gpio$i/direction; echo 1 > gpio$i/value
done
```

## NTP
In order to have the exact local time, you'll have to make sure you are connected to a working NTP server. 

# Compiling
As a last step you'll need a cross-compiling enviroment. Follow this guide on https://openwrt.org/docs/guide-developer/toolchain/crosscompile: set up an Openwrt buildroot enviroment, compile the suitable toolchain, export enviroment variables, use the compiled GCC to compile the code. 
You're done! Now upload the code to the router, make it executable and there you have it! 
