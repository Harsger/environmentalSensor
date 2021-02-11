#!/bin/bash

connectionVia=$1

echo " setting time ... "
echo -n $(date +T%s) > ${connectionVia}
echo " done "

sleep 1

echo " start continous readout ... "
echo -n 'c' > ${connectionVia}
echo " done "


