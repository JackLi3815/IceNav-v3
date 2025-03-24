/**
 * @file storage.hpp
 * @author Jordi Gauchía (jgauchia@jgauchia.com)
 * @brief  Storage definition and functions
 * @version 0.2.0_alpha
 * @date 2025-03
 */

 #ifndef STORAGE_HPP
 #define STORAGE_HPP
 
 #include "esp_spiffs.h"
 #include "esp_err.h"
 #include "driver/sdmmc_host.h"
 #include "driver/sdspi_host.h"
 #include "sdmmc_cmd.h"
 
 class Storage
 {
 private:
     bool isSdLoaded;
     static const uint32_t sdFreq = 40000000;
     sdmmc_card_t* card;
 
 public:
     Storage();
 
     esp_err_t initSD();
     esp_err_t initSPIFFS();
     bool getSdLoaded() const;
 };
 
 #endif