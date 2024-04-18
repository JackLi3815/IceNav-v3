/**
 * @file main_scr.h
 * @author Jordi Gauchía (jgauchia@jgauchia.com)
 * @brief  LVGL - Main Screen
 * @version 0.1.6
 * @date 2023-06-14
 */

/**
 * @brief Main Screen Tiles
 *
 */
static lv_obj_t *compass_tile;
static lv_obj_t *nav_tile;
static lv_obj_t *map_tile;
static lv_obj_t *sat_track_tile;

/**
 * @brief Compass Tile screen objects
 *
 */
static lv_obj_t *compass_heading;
static lv_obj_t *compass_img;
static lv_obj_t *latitude;
static lv_obj_t *longitude;
static lv_obj_t *altitude;
static lv_obj_t *speed_label;

/**
 * @brief Satellite Tracking Tile screen objects
 *
 */
lv_obj_t *pdop_label;
lv_obj_t *hdop_label;
lv_obj_t *vdop_label;
lv_obj_t *alt_label;
static lv_style_t style_radio;
static lv_style_t style_radio_chk;
static uint32_t active_gnss = 0;

/**
 * @brief Main screen events include
 *
 */
#include "gui/screens/Main/events/main_scr.h"
#include "gui/screens/Main/events/compass.h"
#include "gui/screens/Main/events/map.h"
#include "gui/screens/Main/events/sattrack.h"

/**
 * @brief Create Main Screen
 *
 */
void create_main_scr()
{
    mainScreen = lv_obj_create(NULL);
    // lv_obj_set_size(mainScreen, TFT_WIDTH, TFT_HEIGHT);

    // Main Screen Tiles
    tiles = lv_tileview_create(mainScreen);
    compass_tile = lv_tileview_add_tile(tiles, 0, 0, LV_DIR_RIGHT);
    map_tile = lv_tileview_add_tile(tiles, 1, 0, LV_DIR_LEFT | LV_DIR_RIGHT);
    nav_tile = lv_tileview_add_tile(tiles, 2, 0, LV_DIR_LEFT | LV_DIR_RIGHT);
    sat_track_tile = lv_tileview_add_tile(tiles, 3, 0, LV_DIR_LEFT);
    lv_obj_set_size(tiles, TFT_WIDTH, TFT_HEIGHT - 25);
    lv_obj_set_pos(tiles, 0, 25);
    static lv_style_t style_scroll;
    lv_style_init(&style_scroll);
    lv_style_set_bg_color(&style_scroll, lv_color_hex(0xFFFFFF));
    lv_obj_add_style(tiles, &style_scroll, LV_PART_SCROLLBAR);
    // Main Screen Events
    // lv_obj_add_event_cb(tiles, get_act_tile, LV_EVENT_SCROLL_END, NULL);
    // lv_obj_add_event_cb(tiles, scroll_tile, LV_EVENT_SCROLL_BEGIN, NULL);

    // Compass Tile

    // Compass Widget
    lv_obj_t *compass_widget = lv_obj_create(compass_tile);
    lv_obj_set_size(compass_widget, 200, 200);
    lv_obj_set_pos(compass_widget, compass_pos_x, compass_pos_y);
    lv_obj_clear_flag(compass_widget, LV_OBJ_FLAG_SCROLLABLE);
    lv_obj_t *arrow_img = lv_img_create(compass_widget);
    lv_img_set_src(arrow_img, "F:/arrow.bin");
    lv_obj_align(arrow_img, LV_ALIGN_CENTER, 0, -30);

    LV_IMG_DECLARE(bruj);
    compass_img = lv_img_create(compass_widget);
    lv_img_set_src(compass_img, &bruj);
    lv_obj_align(compass_img, LV_ALIGN_CENTER, 0, 0);
    lv_img_set_pivot(compass_img, 100, 100);
    compass_heading = lv_label_create(compass_widget);
    lv_obj_set_size(compass_heading, 150, 38);
    lv_obj_align(compass_heading, LV_ALIGN_CENTER, 0, 20);
    lv_obj_set_style_text_font(compass_heading, &lv_font_montserrat_48, 0);
    lv_label_set_text_static(compass_heading, "-----\xC2\xB0");
    unselect_obj(compass_widget);
    // lv_obj_add_event_cb(compass_widget, drag_widget, LV_EVENT_PRESSING, (char*)"Compass_");
    // lv_obj_add_event_cb(compass_widget, unselect_widget, LV_EVENT_RELEASED, NULL);

    // Position widget
    lv_obj_t *position_widget = lv_obj_create(compass_tile);
    lv_obj_set_size(position_widget, 190, 40);
    lv_obj_set_pos(position_widget, coord_pos_x, coord_pos_y);
    lv_obj_clear_flag(position_widget, LV_OBJ_FLAG_SCROLLABLE);
    lv_obj_t *pos_img = lv_img_create(position_widget);
    lv_img_set_src(pos_img, "F:/pin.bin");
    lv_obj_align(pos_img, LV_ALIGN_LEFT_MID, -15, 0);
    latitude = lv_label_create(position_widget);
    lv_obj_set_style_text_font(latitude, &lv_font_montserrat_16, 0);
    lv_label_set_text_static(latitude, Latitude_formatString(GPS.location.lat()));
    lv_obj_align(latitude, LV_ALIGN_TOP_LEFT, 25, -12);
    longitude = lv_label_create(position_widget);
    lv_obj_set_style_text_font(longitude, &lv_font_montserrat_16, 0);
    lv_label_set_text_static(longitude, Longitude_formatString(GPS.location.lng()));
    lv_obj_align(longitude, LV_ALIGN_TOP_LEFT, 25, 3);
    unselect_obj(position_widget);
    // lv_obj_add_event_cb(position_widget, drag_widget, LV_EVENT_PRESSING, (char*)"Coords_");
    // lv_obj_add_event_cb(position_widget, unselect_widget, LV_EVENT_RELEASED, NULL);

    // Altitude widget
    lv_obj_t *altitude_widget = lv_obj_create(compass_tile);
    lv_obj_set_size(altitude_widget, 140, 40);
    lv_obj_set_pos(altitude_widget, alt_pos_x, alt_pos_y);
    lv_obj_clear_flag(altitude_widget, LV_OBJ_FLAG_SCROLLABLE);
    lv_obj_t *altit_img = lv_img_create(altitude_widget);
    lv_img_set_src(altit_img, "F:/altit.bin");
    lv_obj_align(altit_img, LV_ALIGN_LEFT_MID, -15, 0);
    altitude = lv_label_create(altitude_widget);
    lv_obj_set_style_text_font(altitude, &lv_font_montserrat_24, 0);
    lv_label_set_text_static(altitude, "0000 m.");
    lv_obj_align(altitude, LV_ALIGN_CENTER, 10, 0);
    unselect_obj(altitude_widget);
    // lv_obj_add_event_cb(altitude_widget, drag_widget, LV_EVENT_PRESSING, (char*)"Altitude_");
    // lv_obj_add_event_cb(altitude_widget, unselect_widget, LV_EVENT_RELEASED, NULL);

    // Speed widget
    lv_obj_t *speed_widget = lv_obj_create(compass_tile);
    lv_obj_set_size(speed_widget, 190, 40);
    lv_obj_set_pos(speed_widget, speed_pos_x, speed_pos_y);
    lv_obj_clear_flag(speed_widget, LV_OBJ_FLAG_SCROLLABLE);
    lv_obj_t *speed_img = lv_img_create(speed_widget);
    lv_img_set_src(speed_img, "F:/speed.bin");
    lv_obj_align(speed_img, LV_ALIGN_LEFT_MID, -10, 0);
    speed_label = lv_label_create(speed_widget);
    lv_obj_set_style_text_font(speed_label, &lv_font_montserrat_24, 0);
    lv_label_set_text_static(speed_label, "0 Km/h");
    lv_obj_align(speed_label, LV_ALIGN_CENTER, 0, 0);
    unselect_obj(speed_widget);
    // lv_obj_add_event_cb(speed_widget, drag_widget, LV_EVENT_PRESSING, (char*)"Speed_");
    // lv_obj_add_event_cb(speed_widget, unselect_widget, LV_EVENT_RELEASED, NULL);

    //     // Compass Tile Events
    //     // lv_obj_add_event_cb(compass_heading, update_heading, LV_EVENT_VALUE_CHANGED, NULL);
    //     // lv_obj_add_event_cb(latitude, update_latitude, LV_EVENT_VALUE_CHANGED, NULL);
    //     // lv_obj_add_event_cb(longitude, update_longitude, LV_EVENT_VALUE_CHANGED, NULL);
    //     // lv_obj_add_event_cb(altitude, update_altitude, LV_EVENT_VALUE_CHANGED, NULL);
    //     // lv_obj_add_event_cb(speed_label, update_speed, LV_EVENT_VALUE_CHANGED, NULL);

    //     // Map Tile Events
    //     // lv_obj_add_event_cb(map_tile, update_map, LV_EVENT_REFRESH, NULL);
    //     // lv_obj_add_event_cb(mainScreen, get_zoom_value, LV_EVENT_GESTURE, NULL);

    // Navigation Tile
    // TODO
    lv_obj_t *todolabel = lv_label_create(nav_tile);
    lv_obj_set_style_text_font(todolabel, &lv_font_montserrat_20, 0);
    lv_label_set_text_static(todolabel, "NAVIGATION SCREEN -> TODO");
    lv_obj_center(todolabel);

    // Navitagion Tile Events
    // TODO

    // Satellite Tracking Tile
    lv_obj_t *info_grid = lv_obj_create(sat_track_tile);
    lv_obj_set_size(info_grid, 90, 175);
    lv_obj_set_flex_align(info_grid, LV_FLEX_ALIGN_START, LV_FLEX_ALIGN_CENTER, LV_FLEX_ALIGN_CENTER);
    lv_obj_set_style_pad_row(info_grid, 5, 0);
    lv_obj_clear_flag(info_grid, LV_OBJ_FLAG_SCROLLABLE);
    lv_obj_set_flex_flow(info_grid, LV_FLEX_FLOW_COLUMN);
    static lv_style_t style_grid;
    lv_style_init(&style_grid);
    lv_style_set_bg_opa(&style_grid, LV_OPA_0);
    lv_style_set_border_opa(&style_grid, LV_OPA_0);
    lv_obj_add_style(info_grid, &style_grid, LV_PART_MAIN);

    pdop_label = lv_label_create(info_grid);
    lv_label_set_text_fmt(pdop_label, "PDOP:\n%s", pdop.value());

    hdop_label = lv_label_create(info_grid);
    lv_label_set_text_fmt(hdop_label, "HDOP:\n%s", hdop.value());

    vdop_label = lv_label_create(info_grid);
    lv_label_set_text_fmt(vdop_label, "VDOP:\n%s", vdop.value());

    alt_label = lv_label_create(info_grid);
    lv_label_set_text_fmt(alt_label, "ALT:\n%4dm.", (int)GPS.altitude.meters());

    satbar_1 = lv_chart_create(sat_track_tile);
    lv_obj_set_size(satbar_1, TFT_WIDTH, 55);
    lv_chart_set_div_line_count(satbar_1, 6, 0);
    lv_chart_set_range(satbar_1, LV_CHART_AXIS_PRIMARY_Y, 0, 60);
    satbar_ser1 = lv_chart_add_series(satbar_1, lv_palette_main(LV_PALETTE_GREEN), LV_CHART_AXIS_PRIMARY_Y);
    lv_chart_set_type(satbar_1, LV_CHART_TYPE_BAR);
    lv_chart_set_point_count(satbar_1, (MAX_SATELLLITES_IN_VIEW / 2));
    lv_obj_set_pos(satbar_1, 0, 175);

    satbar_2 = lv_chart_create(sat_track_tile);
    lv_obj_set_size(satbar_2, TFT_WIDTH, 55);
    lv_chart_set_div_line_count(satbar_2, 6, 0);
    lv_chart_set_range(satbar_2, LV_CHART_AXIS_PRIMARY_Y, 0, 60);
    satbar_ser2 = lv_chart_add_series(satbar_2, lv_palette_main(LV_PALETTE_GREEN), LV_CHART_AXIS_PRIMARY_Y);
    lv_chart_set_type(satbar_2, LV_CHART_TYPE_BAR);
    lv_chart_set_point_count(satbar_2, (MAX_SATELLLITES_IN_VIEW / 2));
    lv_obj_set_pos(satbar_2, 0, 260);

#ifdef MULTI_GNSS
    lv_style_init(&style_radio);
    lv_style_set_radius(&style_radio, LV_RADIUS_CIRCLE);

    lv_style_init(&style_radio_chk);
    lv_style_set_bg_image_src(&style_radio_chk, NULL);

    lv_obj_t *gnss_sel = lv_obj_create(sat_track_tile);
    lv_obj_set_flex_flow(gnss_sel, LV_FLEX_FLOW_ROW);
    lv_obj_set_size(gnss_sel, TFT_WIDTH, 50);
    lv_obj_set_pos(gnss_sel, 0, 330);
    static lv_style_t style_sel;
    lv_style_init(&style_sel);
    lv_style_set_bg_opa(&style_sel, LV_OPA_0);
    lv_style_set_border_opa(&style_sel, LV_OPA_0);
    lv_obj_add_style(gnss_sel, &style_sel, LV_PART_MAIN);

    lv_obj_t *gps = lv_checkbox_create(gnss_sel);
    lv_checkbox_set_text_static(gps, "GPS     ");
    lv_obj_add_flag(gps, LV_OBJ_FLAG_EVENT_BUBBLE);
    lv_obj_add_style(gps, &style_radio, LV_PART_INDICATOR);
    lv_obj_add_style(gps, &style_radio_chk, LV_PART_INDICATOR | LV_STATE_CHECKED);

    lv_obj_t *glonass = lv_checkbox_create(gnss_sel);
    lv_checkbox_set_text_static(glonass, "GLONASS  ");
    lv_obj_add_flag(glonass, LV_OBJ_FLAG_EVENT_BUBBLE);
    lv_obj_add_style(glonass, &style_radio, LV_PART_INDICATOR);
    lv_obj_add_style(glonass, &style_radio_chk, LV_PART_INDICATOR | LV_STATE_CHECKED);

    lv_obj_t *beidou = lv_checkbox_create(gnss_sel);
    lv_checkbox_set_text_static(beidou, "BEIDOU");
    lv_obj_add_flag(beidou, LV_OBJ_FLAG_EVENT_BUBBLE);
    lv_obj_add_style(beidou, &style_radio, LV_PART_INDICATOR);
    lv_obj_add_style(beidou, &style_radio_chk, LV_PART_INDICATOR | LV_STATE_CHECKED);

    lv_obj_add_state(lv_obj_get_child(gnss_sel, 0), LV_STATE_CHECKED);

    // GNSS Selection Event
    // lv_obj_add_event_cb(gnss_sel, active_gnss_event, LV_EVENT_CLICKED, &active_gnss);
#endif

    // Satellite Tracking Event
    // lv_obj_add_event_cb(sat_track_tile, update_sattrack, LV_EVENT_VALUE_CHANGED, NULL);
}
