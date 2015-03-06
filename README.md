Face'n'feature detection
========================

Detect faces and features in images to help cropping them.

It's a simple wrapper over the Haar Cascade classifier of
[OpenCV](http://opencv.org/). For mobile, you should consider using the LBP
classifier. It's faster but not as acurate as the Haar classifier.


Install
-------

```
apt-get install build-essential cmake libopencv-dev
cmake -DCMAKE_BUILD_TYPE=Release .
make
```


Usage
-----

```
fnf-detect <image>
```

It will output one face/feature per line, with:

```
<x> <y> <w> <h> <type>
<x> is the X coordinate (from the left)
<y> is the Y coordinate (from the top)
<w> is the width
<h> is the height
<type> is face, profile or feature
```


Examples
--------

```
$ ./fnf-detect image.jpg
302 302 1559 708 face
```

It can be a lot faster to make a thumbnail of an image and extract faces and
features from it, and then extrapolate the coordinates. It's just a small bit
less accurate:

```
$ convert image.jpg -resize '25%' thumbnail.jpg

$ identify image.jpg
image.jpg JPEG 3648x2736 3648x2736+0+0 8-bit DirectClass 2.199MB 0.000u 0:00.000

$ identify thumbnail.jpg
thumbnail.jpg JPEG 912x684 912x684+0+0 8-bit DirectClass 172KB 0.000u 0:00.000

$ time ./fnf-detect image.jpg
2251 1013 352 352 face
./fnf-detect image.jpg  1,39s user 0,03s system 454% cpu 0,312 total

$ time ./fnf-detect thumbnail.jpg
563 253 88 88 face
./fnf-detect thumbnail.jpg  0,16s user 0,03s system 189% cpu 0,101 total

$ echo $((563 * 4)) $((253 * 4)) $((88 * 4)) $((88 * 4))
2252 1012 352 352
```

For testing:

```
for file in in/*; do
  name=$(basename "$file")
  out="out/$name"
  cp "$file" "$out"
  ./fnf-detect "$file" | while read x y w h t; do
    echo $out $t
    mogrify -gravity NorthWest -region "${w}x${h}+${x}+${y}" \
      -bordercolor red -border 4 "$out"
  done
done
```

Inspiration
-----------

* [facedetect](http://www.thregr.org/~wavexx/software/facedetect/)
* [thumbor](https://github.com/thumbor/thumbor/wiki/Detection-algorithms)


Credits
-------

Copyright af83 (c) 2015

Released under the MIT license
