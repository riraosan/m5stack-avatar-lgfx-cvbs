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
  display.setPivot((display.width() >> 1) - 35, display.height() >> 1);

  avatar.init(1); // start drawing
}

  void loop()
  {
    // avatar's face updates in another thread
    // so no need to loop-by-loop rendering
}

