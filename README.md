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
<type> is face, profile, body or feature
```


Examples
--------

```
$ ./fnf-detect image.jpg
302 302 1559 708 face
```


Credits
-------

Copyright af83 (c) 2015

Released under the MIT license
