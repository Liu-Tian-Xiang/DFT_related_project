#!/bin/bash
echo 'make gif'

#echo ./Pic/data_rho`seq -s .png\ ./Pic/data_rho $1 $2`.png
#sh mkgif 1 8 rho
if [ -f ./picture/data_$3$1.png ]; then
convert -delay 0.05 ./picture/data_$3`seq -s .png\ ./picture/data_$3 $1 $2`.png -loop 0 $3.gif
fi

exit 0
