/**
 * @file compass.h
 * @author Jordi Gauchía (jgauchia@jgauchia.com)
 * @brief  Compass screen events
 * @version 0.1.6
 * @date 2023-06-14
 */

bool widget_selected = false;

/**
 * @brief Update compass heading label
 *
 * @param event
 */
static void update_heading(lv_event_t *event)
{
#ifdef ENABLE_COMPASS
    lv_obj_t *compass = (lv_obj_t*)lv_event_get_current_target(event);
    lv_label_set_text_fmt(compass, "%5d\xC2\xB0", heading);
    lv_img_set_angle(compass_img, -(heading * 10));
#endif
}

/**
 * @brief Update latitude label
 *
 * @param event
 */
static void update_latitude(lv_event_t *event)
{
    lv_obj_t *lat = (lv_obj_t*)lv_event_get_target(event);
    lv_label_set_text_static(lat, Latitude_formatString(GPS.location.lat()));
}

/**
 * @brief Update longitude label
 *
 * @param event
 */
static void update_longitude(lv_event_t *event)
{
    lv_obj_t *lon = (lv_obj_t*)lv_event_get_target(event);
    lv_label_set_text_static(lon, Longitude_formatString(GPS.location.lng()));
}

/**
 * @brief Upate altitude label
 *
 * @param event
 */
static void update_altitude(lv_event_t *event)
{
    lv_obj_t *alt = (lv_obj_t*)lv_event_get_target(event);
    lv_label_set_text_fmt(altitude, "%4d m.", (int)GPS.altitude.meters());
}

/**
 * @brief Update speed label
 *
 * @param event
 */
static void update_speed(lv_event_t *event)
{
    lv_obj_t *speed = (lv_obj_t*)lv_event_get_target(event);
    lv_label_set_text_fmt(speed, "%3d Km/h", (int)GPS.speed.kmph());
}

/**
 * @brief Unselect widget
 *
 * @param event
 */
static void unselect_widget(lv_event_t *event)
{
    lv_obj_t *obj = (lv_obj_t*)lv_event_get_target(event);
    if (widget_selected)
    {
        unselect_obj(obj);
        lv_obj_add_flag(tiles, LV_OBJ_FLAG_SCROLLABLE);
        widget_selected = false;
    }
}

/**
 * @brief Drag widget event
 *
 * @param event
 */
static void drag_widget(lv_event_t *event)
{
    // lv_obj_clear_flag(tiles, LV_OBJ_FLAG_SCROLLABLE);

    lv_obj_t *obj = (lv_obj_t*)lv_event_get_target(event);
    if (!widget_selected)
    {
        select_obj(obj);
        lv_obj_clear_flag(tiles, LV_OBJ_FLAG_SCROLLABLE);
        widget_selected = true;
    }

    lv_indev_t *indev = lv_indev_get_act();
    if (indev == NULL)
        return;

    lv_point_t vect;
    lv_indev_get_vect(indev, &vect);

    lv_coord_t x = lv_obj_get_x(obj) + vect.x;
    lv_coord_t y = lv_obj_get_y(obj) + vect.y;
    lv_coord_t width = lv_obj_get_width(obj);
    lv_coord_t height = lv_obj_get_height(obj);

    // Limit drag area
    if (x > 0 && y > 0 && (x + width) < 320 && (y+height) < 380)
    {
        lv_obj_set_pos(obj, x, y);

        char *widget = (char *)lv_event_get_user_data(event);
        save_widget_pos(widget, x, y);
    }
}
