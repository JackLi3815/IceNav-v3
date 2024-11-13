/**
 * @file loadWaypoint.hpp
 * @author Jordi Gauchía (jgauchia@gmx.es)
 * @brief  Load Waypoint functions
 * @version 0.1.8
 * @date 2024-11
 */

#ifndef LOADWAYPOINT_HPP
#define LOADWAYPOINT_HPP

#include "SD.h"
#include "FS.h"
#include "tft.hpp"
#include "storage.hpp"
#include "globalGuiDef.h"
#include "globalGpxDef.h"

extern wayPoint loadWpt;

void loadWptFile(String wpt);

#endif