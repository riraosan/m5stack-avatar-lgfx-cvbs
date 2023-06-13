#include <Arduino.h>
#include <FS.h>
#include <SD.h>
#include <SPI.h>
#include <M5GFX.h>
#include <LGFX_8BIT_CVBS.h>
#include <Button2.h>
#include <Avatar.h>

using namespace m5avatar;

static LGFX_8BIT_CVBS display;
static M5Canvas sp_avatar(&display);

Avatar avatar(&sp_avatar);

#define TFCARD_CS_PIN 4 // dummy
#define LGFX LGFX_8BIT_CVBS

#define LGFX_ONLY
#define USE_DISPLAY

#define SDU_APP_NAME "STACK-chan"
#define SDU_APP_PATH "/01_STACK-chan.bin"

#include <M5StackUpdater.h>

#define BUTTON_GPIO_NUM 16
Button2 button;

bool bA = false;
bool bB = false;
bool bC = false;

void handler(Button2 &btn)
{
  switch (btn.getType())
  {
  case clickType::single_click:
    Serial.print("single ");
    bB = true;
    break;
  case clickType::double_click:
    Serial.print("double ");
    bC = true;
    break;
  case clickType::triple_click:
    Serial.print("triple ");
    break;
  case clickType::long_click:
    Serial.print("long ");
    bA = true;
    break;
  case clickType::empty:
    break;
  default:
    break;
  }

  Serial.print("click");
  Serial.print(" (");
  Serial.print(btn.getNumberOfClicks());
  Serial.println(")");
}

bool buttonAPressed(void)
{
  bool temp = bA;
  bA = false;

  return temp;
}

bool buttonBPressed(void)
{
  bool temp = bB;
  bB = false;

  return temp;
}

bool buttonCPressed(void)
{
  bool temp = bC;
  bC = false;

  return temp;
}

void ButtonUpdate()
{
  button.loop();
}

void setupButton(void)
{
  button.setClickHandler(handler);
  button.setDoubleClickHandler(handler);
  button.setTripleClickHandler(handler);
  button.setLongClickHandler(handler);
  button.begin(BUTTON_GPIO_NUM);

  SDUCfg.setSDUBtnA(&buttonAPressed);
  SDUCfg.setSDUBtnB(&buttonBPressed);
  SDUCfg.setSDUBtnC(&buttonCPressed);
  SDUCfg.setSDUBtnPoller(&ButtonUpdate);
}

void setupSDUpdater()
{
  setupButton();

  setSDUGfx(&display);
  checkSDUpdater(
      SD,           // filesystem (default=SD)
      MENU_BIN,     // path to binary (default=/menu.bin, empty string=rollback only)
      2000,         // wait delay, (default=0, will be forced to 2000 upon ESP.restart() )
      TFCARD_CS_PIN // (usually default=4 but your mileage may vary)
  );
}

void setup()
{
  M5.begin();

  display.init();
  display.setPivot(display.width() >> 1, display.height() >> 1);

  setupSDUpdater();

  avatar.init(1); // start drawing
  avatar.setScale(1.0);
  avatar.setRotation(0);
  avatar.setSpeechFont(&lgfx::v1::fonts::efontJA_16);
  avatar.setSpeechText("Hello World!");
  avatar.setExpression(Expression::Happy);
}

void loop()
{
  ButtonUpdate();
  if (buttonAPressed())
  {
    avatar.stop();
    display.fillScreen(TFT_BLACK);

    updateFromFS(SD);
    ESP.restart();
  }
}
