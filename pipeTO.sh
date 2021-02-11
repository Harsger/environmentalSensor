#!/bin/bash

connectionVia=$1

echo -n " configuering port ... "
stty -F ${connectionVia} cs8 9600 ignbrk -brkint -icrnl -imaxbel -opost -onlcr -isig -icanon -iexten -echo -echoe -echok -echoctl -echoke noflsh -ixon -crtscts
echo " done "

echo " start output : "
tail -f ${connectionVia}
