/**
 * @file addWaypoint.hpp
 * @author Jordi Gauchía (jgauchia@gmx.es)
 * @brief  Add Waypoint functions
 * @version 0.1.8
 * @date 2024-06
 */

#ifndef ADDWAYPOINT_HPP
#define ADDWAYPOINT_HPP

#include "globalGpxDef.h"
#include "SD.h"
#include "FS.h"
#include "tft.hpp"
#include "storage.hpp"
#include "lvgl.h"

extern wayPoint addWpt;
static const char* wptFile PROGMEM = "/WPT/waypoint.gpx";

void openGpxFile(const char* gpxFilename);

#endif
