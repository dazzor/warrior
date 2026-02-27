#pragma once
#define LGFX_USE_V1
#include <LovyanGFX.hpp>

// Example of configuration for using LovyanGFX with custom settings on ESP32.
/* Please duplicate this file, give it a new name, and modify the settings to suit your environment.
The created files can be used by including them in the user program.。
You can place the copied files in the lgfx_user folder of the library and use them, 
but please note that they may be deleted when the library is updated.
If you want to operate it safely, please create a backup or place it in your user project folder.
//*/
/// Create a class that performs custom settings by deriving it from LGFX_Device.
class LGFX : public lgfx::LGFX_Device {
/*The class name can be changed from "LGFX" to a different name.
When using it with AUTODETECT, "LGFX" is already in use, so please change it to a name other than LGFX.
Also, if you are using multiple panels simultaneously, please give each one a different name.
 ※ If you change the class name, you must also change the constructor name to match the new class name.

You can choose the name freely, but considering the possibility of increased settings in the future,
for example, if you configure an ILI9341 with SPI connection on an ESP32 DevKit-C,
you could name it: LGFX_DevKitC_SPI_ILI9341
By using names like this and ensuring that the file name and class name match, 
it becomes easier to use the code without confusion.
//*/

// Prepare an instance that matches the type of panel you want to connect.
//lgfx::Panel_GC9A01      _panel_instance;
//lgfx::Panel_GDEW0154M09 _panel_instance;
//lgfx::Panel_HX8357B     _panel_instance;
//lgfx::Panel_HX8357D     _panel_instance;
//lgfx::Panel_ILI9163     _panel_instance;
//  lgfx::Panel_ILI9341     _panel_instance;
//lgfx::Panel_ILI9342     _panel_instance;
//lgfx::Panel_ILI9481     _panel_instance;
//lgfx::Panel_ILI9486     _panel_instance;
//lgfx::Panel_ILI9488     _panel_instance;
//lgfx::Panel_IT8951      _panel_instance;
//lgfx::Panel_RA8875      _panel_instance;
//lgfx::Panel_SH110x      _panel_instance; // SH1106, SH1107
//lgfx::Panel_SSD1306     _panel_instance;
//lgfx::Panel_SSD1327     _panel_instance;
//lgfx::Panel_SSD1331     _panel_instance;
//lgfx::Panel_SSD1351     _panel_instance; // SSD1351, SSD1357
//lgfx::Panel_SSD1963     _panel_instance;
//lgfx::Panel_ST7735      _panel_instance;
//lgfx::Panel_ST7735S     _panel_instance;
lgfx::Panel_ST7789      _panel_instance;
//lgfx::Panel_ST7796      _panel_instance;


// Prepare an instance that matches the type of bus used to connect the panel.
  lgfx::Bus_SPI       _bus_instance;   // SPI bus instance
//lgfx::Bus_I2C       _bus_instance;   // I2C bus instance (ESP32 only)
//lgfx::Bus_Parallel8 _bus_instance;   // 8-bit parallel bus instance (ESP32 only)

// If backlight control is possible, an instance will be created. (Delete it if not needed.)
  lgfx::Light_PWM     _light_instance;

// Prepare an instance that matches the type of touchscreen. (Delete if not needed.)
//lgfx::Touch_CST816S          _touch_instance;
//  lgfx::Touch_FT5x06           _touch_instance; // FT5206, FT5306, FT5406, FT6206, FT6236, FT6336, FT6436
//lgfx::Touch_GSL1680E_800x480 _touch_instance; // GSL_1680E, 1688E, 2681B, 2682B
//lgfx::Touch_GSL1680F_800x480 _touch_instance;
//lgfx::Touch_GSL1680F_480x272 _touch_instance;
//lgfx::Touch_GSLx680_320x320  _touch_instance;
//lgfx::Touch_GT911            _touch_instance;
//lgfx::Touch_STMPE610         _touch_instance;
//lgfx::Touch_TT21xxx          _touch_instance; // TT21100
lgfx::Touch_XPT2046          _touch_instance;

public:

  // We create a constructor and perform various settings here.
  // If you change the class name, please also specify the same name for the constructor.
  LGFX(void)
  {
    { // We will configure the bus control settings.
      auto cfg = _bus_instance.config();    // Retrieves the structure used for bus configuration.

// SPI bus settings
      cfg.spi_host = SPI3_HOST; //VSPI_HOST;     // Select the SPI to use.  ESP32-S2,C3 : SPI2_HOST or SPI3_HOST / ESP32 : VSPI_HOST or HSPI_HOST
      // ※ Due to the ESP-IDF version update, the use of VSPI_HOST and HSPI_HOST is now deprecated. If you encounter errors, please use SPI2_HOST and SPI3_HOST instead.
      cfg.spi_mode = 0;             // Set the SPI communication mode (0 to 3).
      cfg.freq_write = 40000000;    // SPI clock frequency during transmission (maximum 80MHz, rounded to a value obtained by dividing 80MHz by an integer)
      cfg.freq_read  = 16000000;    // SPI clock during reception
      cfg.spi_3wire  = true;        // Set to true if receiving data via the MOSI pin.
      cfg.use_lock   = true;        // Set to true if you want to use transaction locks.
      cfg.dma_channel = SPI_DMA_CH_AUTO; // Set the DMA channel to be used (0=No DMA / 1=Channel 1 / 2=Channel 2 / SPI_DMA_CH_AUTO=Automatic setting)
      // ※ With the ESP-IDF version update, using SPI_DMA_CH_AUTO (automatic setting) for the DMA channel is now recommended. Specifying channels 1 or 2 is no longer recommended.
      cfg.pin_sclk = 14;            // Set the SPI SCLK pin number.
      cfg.pin_mosi = 13;            // Set the SPI MOSI pin number.
      cfg.pin_miso = 12;            // Set the SPI MISO pin number (-1 = disable)
      cfg.pin_dc   = 2;            // Set the SPI D/C pin number (-1 = disable)
     // When using the SPI bus, which is shared with the SD card, be sure to configure the MISO pin; do not omit it.
//*/
/*
// I2C bus settings
      cfg.i2c_port    = 0;          // 使用するI2Cポートを選択 (0 or 1)
      cfg.freq_write  = 400000;     // 送信時のクロック
      cfg.freq_read   = 400000;     // 受信時のクロック
      cfg.pin_sda     = 21;         // SDAを接続しているピン番号
      cfg.pin_scl     = 22;         // SCLを接続しているピン番号
      cfg.i2c_addr    = 0x3C;       // I2Cデバイスのアドレス
//*/
/*
// 8-bit parallel bus settings
      cfg.i2s_port = I2S_NUM_0;     // 使用するI2Sポートを選択 (I2S_NUM_0 or I2S_NUM_1) (ESP32のI2S LCDモードを使用します)
      cfg.freq_write = 20000000;    // 送信クロック (最大20MHz, 80MHzを整数で割った値に丸められます)
      cfg.pin_wr =  4;              // WR を接続しているピン番号
      cfg.pin_rd =  2;              // RD を接続しているピン番号
      cfg.pin_rs = 15;              // RS(D/C)を接続しているピン番号
      cfg.pin_d0 = 12;              // D0を接続しているピン番号
      cfg.pin_d1 = 13;              // D1を接続しているピン番号
      cfg.pin_d2 = 26;              // D2を接続しているピン番号
      cfg.pin_d3 = 25;              // D3を接続しているピン番号
      cfg.pin_d4 = 17;              // D4を接続しているピン番号
      cfg.pin_d5 = 16;              // D5を接続しているピン番号
      cfg.pin_d6 = 27;              // D6を接続しているピン番号
      cfg.pin_d7 = 14;              // D7を接続しているピン番号
//*/

      _bus_instance.config(cfg);    // The settings will be applied to the bus.
      _panel_instance.setBus(&_bus_instance);      // Set the bus onto the panel.
    }

    { // Configure the display panel settings.
      auto cfg = _panel_instance.config();    // Retrieves the structure used for display panel settings.

      cfg.pin_cs           =    15;  // The pin number to which CS is connected.   (-1 = disable)
      cfg.pin_rst          =    -1;  // The pin number to which RST is connected.  (-1 = disable)
      cfg.pin_busy         =    -1;  // The pin number to which BUSY is connected. (-1 = disable)

      // ※ The following settings have general default values ​​set for each panel, so if you are unsure about any item, try commenting it out.

      cfg.panel_width      =   240;  // The actual displayable width
      cfg.panel_height     =   320;  // The actual displayable height
      cfg.offset_x         =     0;  // Panel X-direction offset amount
      cfg.offset_y         =     0;  // Panel Y-direction offset amount
      cfg.offset_rotation  =     0;  // Rotation direction value offset: 0-7 (4-7 are vertically inverted)
      cfg.dummy_read_pixel =     8;  // Number of dummy read bits before pixel readout
      cfg.dummy_read_bits  =     1;  // The number of dummy read bits before reading data other than pixels.
      cfg.readable         =  true;  // Set to true if data can be read.
      cfg.invert           = false;  // Set to true if the panel's brightness and darkness are reversed.
      cfg.rgb_order        = false;  // Set to true if the red and blue colors on the panel are reversed.
      cfg.dlen_16bit       = false;  // Set this to true for panels that transmit data in 16-bit units via 16-bit parallel or SPI interfaces.
      cfg.bus_shared       =  true;  // Set this to true if the SD card shares the bus (bus control will be performed by functions such as drawJpgFile).

// The following settings should only be configured if the display is misaligned with drivers that have a variable number of pixels, such as the ST7735 or ILI9163.
//    cfg.memory_width     =   240;  // The maximum width supported by the driver IC.
//    cfg.memory_height    =   320;  // The maximum height supported by the driver IC.

      _panel_instance.config(cfg);
    }

//*
    { // Configure the backlight control settings. (Delete if not needed)
      auto cfg = _light_instance.config();    // Retrieves the structure for backlight settings.

      cfg.pin_bl = 21;              // The pin number to which the backlight is connected.
      cfg.invert = false;           // Set to true to invert the backlight brightness.
      cfg.freq   = 44100;           // Backlight PWM frequency
      cfg.pwm_channel = 7;          // The channel number of the PWM to be used.

      _light_instance.config(cfg);
      _panel_instance.setLight(&_light_instance);  // バックライトをパネルにセットします。
    }
//*/

//*
    { // Configure the touchscreen control settings. (Delete if not needed.)
      auto cfg = _touch_instance.config();

      cfg.x_min      = 0;    // The minimum X value (raw value) obtained from the touchscreen.
      cfg.x_max      = 239;  // The maximum X value (raw value) obtained from the touchscreen.
      cfg.y_min      = 0;    // The minimum Y-value (raw value) obtained from the touchscreen.
      cfg.y_max      = 319;  // The maximum Y-value (raw value) obtained from the touchscreen.
      cfg.pin_int    = 36;   // The pin number to which INT is connected.(IRQ)
      cfg.bus_shared = true; // Set to true if the same bus is used for both the screen and the device.
      cfg.offset_rotation = 0;// Adjustment for cases where the display and touch orientation do not match. Set a value between 0 and 7.

// For SPI connection
      cfg.spi_host = HSPI_HOST;// Select the SPI to use. (HSPI_HOST or VSPI_HOST)
      cfg.freq = 1000000;     // Set the SPI clock.
      cfg.pin_sclk = 25;     // The pin number to which SCLK is connected.
      cfg.pin_mosi = 32;     // The pin number to which MOSI is connected
      cfg.pin_miso = 39;     // The pin number to which MISO is connected
      cfg.pin_cs   =  33;     //   The pin number to which CS is connected.

// For I2C connection
//      cfg.i2c_port = 1;      // 使用するI2Cを選択 (0 or 1)
//      cfg.i2c_addr = 0x38;   // I2C device address number
//      cfg.pin_sda  = 25;     // SDAが接続されているピン番号
//      cfg.pin_scl  = 32;     // SCLが接続されているピン番号
//      cfg.freq = 400000;     // I2Cクロックを設定

      _touch_instance.config(cfg);
      _panel_instance.setTouch(&_touch_instance);  // Install the touchscreen onto the panel.。
    }
//*/

    setPanel(&_panel_instance); // Set the panels to be used.
  }
};

