# M5Stack-Avatar for CRT Display(Composite)

[![Powered By PlatformIO](https://img.shields.io/badge/powered-PlatformIO-brightgreen)](https://platformio.org/)



## Features

* :neutral_face:     Draw avatar face
* :smile:            Expression(Happy, Angry, Sad etc.)
* :smiley_cat:       Customize face
* :kiss:             Lip sync
* :art:              Color Palette
* :arrows_clockwise: Move, Zoom and Rotation
* :two:              Compatible with M5Stack Core2
* Output to Composite Video Signal(CVBS)

## Installation

### Prerequisites

* USB Driver is installed throwgh [Getting Started: Installing the USB Driver](http://www.m5stack.com/assets/docs/)
* Any of IDE is set up
  * This library is confirmed on __Arduino IDE__ and __Platform IO__ for now

### Using Arduino IDE

* On Arduino IDE, Select "Sketch > Include Library > Manage Libraries..."
* Search "m5stack avatar"
* Select "M5Stack_Avatar" from the results then click "Install"
* The library gets installed

### Using Platform IO

* Initialize your Platform IO project
```sh
mkdir my-avatar
cd my-avatar
platformio init -d . -b m5stack-core-esp32
```
* Install the library and its dependency
```sh
platformio lib install M5Unified
platformio lib install M5Stack-Avatar-lgfx-cvbs
```
* The library gets downloaded from repository to .piolibdeps directory

## Usage

```cpp

#include <M5GFX.h>
#include <LGFX_8BIT_CVBS.h>
#include <Avatar.h>

using namespace m5avatar;

static LGFX_8BIT_CVBS display;
static M5Canvas sp_avatar(&display);

Avatar avatar(&sp_avatar);

void setup()
{
  M5.begin();

  display.init();
  display.setPivot((display.width() >> 1), display.height() >> 1);

  avatar.init(1); // start drawing
  avatar.setScale(1.0);
  avatar.setRotation(0);
  avatar.setSpeechFont(&fonts::Font0);
  avatar.setSpeechText("Hello World!");
  avatar.setExpression(Expression::Happy);
}

void loop()
{
  // avatar's face updates in another thread
  // so no need to loop-by-loop rendering
}
```

### Further usage

see `examples` directory.
