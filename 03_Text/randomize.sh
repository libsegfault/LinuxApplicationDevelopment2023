#!/bin/bash

delay=${1:-0.01}

art=$(cat)
tput clear

width=$(echo "$art" | head -n 1 | wc -m)
height=$(echo "$art" | wc -l)

positions=($(seq 1 $((width * height)) | shuf))

for pos in "${positions[@]}"; do
  x=$(( (pos - 1) % width + 1 ))
  y=$(( (pos - 1) / width + 1 ))
  char="${art:((y-1)*width+(x-1)):1}"
  if [ "$char" != " " ]; then
    tput cup $((y-1)) $((x-1))
    echo -n "$char"
    sleep $delay
  fi
done

tput cup $height $width
echo
