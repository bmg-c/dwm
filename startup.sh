#!/usr/bin/env sh

setkblayout engram 			    # Keyboard layout set
xset r rate 340 38 				            # Keyboard repeat rate set
brightnessctl set 180 				        # Default brightness set
dbus-update-activation-environment --all 	# For SSH and else to work
~/scripts/bar/barkillall.sh                 # Kill all lemonbar processes
cpupower-gui ene --pref balance_performance

echo $(( $RANDOM % $(ls ~/wallpapers | wc -l) )) > ~/scripts/.currentwp # Randomize wallpapers
echo $(( $RANDOM % $(ls ~/.secscrwp | wc -l) )) >> ~/scripts/.currentwp

if [ "$(xrandr | grep "HDMI-A-0")" = "HDMI-A-0 disconnected (normal left inverted right x axis y axis)" ] # If external monitor disconnected - load single monitor setup
then
    xrdb ~/.Xresources  # Load HiDPI settings
    ~/scripts/bar/barkillall.sh

    wpchange &
    picom --config ~/.config/picom/picom.conf &
    ~/scripts/bar/bar.sh &
    xrandr --output eDP --primary --mode 2240x1400 --pos 0x0 --rotate normal --output HDMI-A-0 --off --output DisplayPort-0 --off --output DisplayPort-1 --off &
else
    ~/scripts/bar/barkillall.sh

    wpchange &
    picom --config ~/.config/picom/picom.conf &
    ~/scripts/bar/bar.sh &
    ~/scripts/bar/barsecond.sh &
    xrandr --output eDP --primary --mode 2240x1400 --pos 0x1080 --rotate normal --output HDMI-A-0 --mode 1920x1080 --pos 0x0 --rotate normal --output DisplayPort-0 --off --output DisplayPort-1 --off &
fi 
