/**
 * @file tft.h
 * @author Jordi Gauchía (jgauchia@gmx.es)
 * @brief TFT definition and functions
 * @version 0.1.8
 * @date 2024-04
 */

#ifndef TFT_H
#define TFT_H

#define CALIBRATION_FILE "/TouchCalData1"
bool repeatCalib = false;
uint8_t brightnessLevel = 255;
#define LVGL_BKG 0x10A3

#ifdef CUSTOMBOARD
#include <LGFX_CUSTOMBOARD.hpp>
#endif

#ifdef MAKERF_ESP32S3
#include <LGFX_MakerFabs_Parallel_S3.hpp>
#endif

#include <LGFX_TFT_eSPI.hpp>

static TFT_eSPI tft;


/**
 * @brief Set the TFT brightness
 *
 * @param brightness -> 0..255
 */
void setBrightness(uint8_t brightness)
{
  if (brightness <= 255)
  {
    ledcWrite(0, brightness);
    brightnessLevel = brightness;
  }
}

/**
 * @brief Get the TFT brightness
 *
 * @return int -> brightness value 0..255
 */
uint8_t getBrightness()
{
  return brightnessLevel;
}

/**
 * @brief Turn on TFT Sleep Mode for ILI9488
 *
 */
void tftOn()
{
  tft.writecommand(0x11);
  setBrightness(255);
}

/**
 * @brief Turn off TFT Wake up Mode for ILI9488
 *
 */
void tftOff()
{
  tft.writecommand(0x10);
  setBrightness(0);
}

/**
 * @brief Touch calibrate
 *
 */
void touchCalibrate()
{
  uint16_t calData[8];
  uint8_t calDataOK = 0;

  if (SPIFFS.exists(CALIBRATION_FILE))
  {
    if (repeatCalib)
      SPIFFS.remove(CALIBRATION_FILE);
    else
    {
      File f = SPIFFS.open(CALIBRATION_FILE, "r");
      if (f)
      {
        if (f.readBytes((char *)calData, 16) == 16)
          calDataOK = 1;
        f.close();
      }
      else
        log_v("Error opening touch configuration");
    }
  }

  if (calDataOK && !repeatCalib)
    tft.setTouchCalibrate(calData);
  else
  {
    tft.drawCenterString("TOUCH THE ARROW MARKER.", 160, tft.height() >> 1, &fonts::DejaVu18);
    tft.calibrateTouch(calData, TFT_WHITE, TFT_BLACK, std::max(tft.width(), tft.height()) >> 3);
    tft.drawCenterString("DONE!", 160, (tft.height() >> 1) + 30, &fonts::DejaVu40);
    delay(500);
    tft.drawCenterString("TOUCH TO CONTINUE.", 160, (tft.height() >> 1) + 100, &fonts::DejaVu18);

    File f = SPIFFS.open(CALIBRATION_FILE, "w");
    if (f)
    {
      f.write((const unsigned char *)calData, 16);
      f.close();
    }

    uint16_t touchX, touchY;
    while (!tft.getTouch(&touchX, &touchY))
    {
    };
  }
}

/**
 * @brief Init tft display
 *
 */
void initTFT()
{
  tft.init();
  tft.setRotation(8);
  tft.initDMA();
  tft.startWrite();
  tft.fillScreen(TFT_BLACK);
  tft.endWrite();

  gpio_set_drive_capability(GPIO_NUM_33, GPIO_DRIVE_CAP_3);
  ledcAttachPin(TFT_BL, 0);
  ledcSetup(0, 5000, 8);
  ledcWrite(0, 255);
#ifndef MAKERF_ESP32S3
  touchCalibrate();
#endif
}

#endif