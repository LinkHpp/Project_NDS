#!/bin/sh

grit flyer.png -ftb -fh! -gTFF00FF -gt -gB8 -m!


for file in *.bin; do
    mv -- "$file" "${file%.bin}"
done

mv *.pal *.img ../nitrofiles/sprite

grit nfl.png -ftb -fh! -gTFF00FF -gt -gB8 -mR8 -mLs
grit bg0.png -ftb -fh! -gTFF00FF -gt -gB8 -mR8 -mLs
grit bg1.png -ftb -fh! -gTFF00FF -gt -gB8 -mR8 -mLs
grit bg2.png -ftb -fh! -gTFF00FF -gt -gB8 -mR8 -mLs
grit bg3.png -ftb -fh! -gTFF00FF -gt -gB8 -mR8 -mLs
grit tilemap.png -ftb -fh! -gTFF00FF -gt -gB8 -mR8 -mLs
grit flyer.png -ftb -fh! -gTFF00FF -gt -gB8 -mR8 -mLs

for file in *.bin; do
    mv -- "$file" "${file%.bin}"
done

mv *.pal *.img *.map ../nitrofiles/bg
