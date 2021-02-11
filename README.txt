arduino sketch and scripts for readout of an BME280 pressure-humidity-temperature sensor

check at which USB-port the device ist attached ( e.g. /dev/ttyUSB0 )

use screen for the writing process, start using

    ./pipeTO.sh /dev/ttyUSB0 > logfile.txt

start measurement (and configure correct time) using the script

    ./start.sh /dev/ttyUSB0

in another shell afterwards! 

( if not working use : echo -n 'c' > /dev/ttyUSB0 )

check output in logfile using tail -f

ten seconds delay between measurements

output format:

    unixtime pressure humidity temperature
