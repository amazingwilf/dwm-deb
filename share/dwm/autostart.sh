#!/usr/bin/env bash

killall -9 picom slstatus
feh --bg-fill /usr/share/backgrounds/debian5.jpg
picom -b
slstatus &
