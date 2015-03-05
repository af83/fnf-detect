#/bin/bash

files=in/*

for file in $files; do
  name=$(basename "$file")
  out="out/$name"
  cp "$file" "$out"
  ./fnf-detect "$file" | while read x y w h t; do
    echo "$out $x $y $w $h $t" >> out/log
    if [ "$t" != "feature" ]; then
      mogrify -gravity NorthWest -region "${w}x${h}+${x}+${y}" \
        -bordercolor red -border 4 "$out"
    fi
  done
done

# grep face out/log | awk '{ print $1 }' | xargs feh
