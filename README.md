# Vergr Inhibit
(*also: Zoom Freedesktop Notification Inhibition* – “vergr(ößern)” as a dumb pun on “(to) zoom”)

This provides a library to be loaded into [ZOOM®](https://zoom.us) for automatically enabling “do not disturb” mode on supported desktops (such as [KDE Plasma](https://kde.org/plasma-desktop) 5.16 or newer) when screen sharing.

![Screenshot with KDE Plasma's notification center stating "Do not disturb while ZOOM® is active (Screen share in progress)"](screenshot.png?raw=true "Screen share in progress")

## How to build

This project is configured using `cmake` and is built with [Qt](https://www.qt.io/).

You need to have development packages for Qt 5 DBus and Qt 5 Gui installed to build it, for example `qtbase5-dev`.

Basically:
```
mkdir build
cd build
cmake ..
make
make install
```

It assumes that ZOOM® is installed in `/opt/zoom`, which is the case for the *Ubuntu 16.04+* packages provided by ZOOM® but may be different on your particular setup. You may override this location like so:

```
cmake .. -DZOOM_DIR=/other/path
```

### CMake Options

* `ZOOM_DIR`: The location of the ZOOM® installation, defaults to `/opt/zoom`
* `ZOOM_EXECUTABLE`: The *zoom* binary to launch, defaults to `${ZOOM_DIR}/zoom`
* `ZOOM_QT_LIBDIR`: The folder with ZOOM®'s Qt libraries, defaults to `${ZOOM_DIR}`

## How to use

This library is loaded into the ZOOM® client by means of `LD_PRELOAD`. This is not forwarded by the ZOOM® launcher necessitating a direct launch of the ZOOM® binary. A convenience script for launching ZOOM® this way is provided.

```
vergrzoom.sh
```

Alternatively, you may run it manually (Ubuntu example):
```
LD_PRELOAD=[path to libvergrinhibit.so] LD_LIBRARY_PATH=/opt/zoom /opt/zoom/zoom
```

## How does it work

This library will watch the screen share toolbar window being created. As long as it is there, notifications will be disabled.

Originally, it was attempted to build infrastructure into [KWin](http://invent.kde.org/plasma/kwin) to allow scripting or window rules to inhibit notifications while a certain window was on screen. However, most of these overlays are “override redirect” windows, meaning they bypass the compositor, and so they are opaque to KWin’s scripting and window rule infrastructure.

## License

```
The MIT License (MIT)

Copyright 2021 Kai Uwe Broulik

Permission is hereby granted, free of charge, to any person obtaining
a copy of this software and associated documentation files (the
"Software"), to deal in the Software without restriction, including
without limitation the rights to use, copy, modify, merge, publish,
distribute, sublicense, and/or sell copies of the Software, and to
permit persons to whom the Software is furnished to do so, subject to
the following conditions:

The above copyright notice and this permission notice shall be included
in all copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF
MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.
IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY
CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT,
TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE
SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
```

ZOOM® is a registered trademark of Zoom Video Communications, Inc.
