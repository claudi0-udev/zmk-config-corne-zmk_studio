#include <zephyr/kernel.h>
#include <zmk/display.h>
#include <zmk/event_manager.h>
#include <zmk/events/position_state_changed.h>
#include <zmk/widgets/layer_status.h>
#include <zmk/widgets/battery_status.h>
#include <zmk/widgets/output_status.h>
#include <zmk/widgets/wpm_status.h>
#include <lvgl.h>

static lv_obj_t *key_label;
static char key_text[32] = "Tecla: -";

static const char *get_corne_key_label(uint32_t pos) {
    static const char *corne_labels[42] = {
        // Fila 0
        "ESC", "Q", "W", "E", "R", "T",   "Y", "U", "I", "O", "P", "BSPC",
        // Fila 1
        "SHIFT", "A", "S", "D", "F", "G",   "H", "J", "K", "L", ";", "'",
        // Fila 2
        "CTRL", "Z", "X", "C", "V", "B",   "N", "M", ",", ".", "/", "DEL",
        // Thumb cluster
        "ALT/TAB", "LWR", "SPACE",   "ENTER", "RSE", "RALT"
    };
    if (pos < 42) {
        return corne_labels[pos];
    }
    return "?";
}

static int last_key_listener_cb(const zmk_event_t *eh) {
    const struct zmk_position_state_changed *ev = as_zmk_position_state_changed(eh);
    if (ev && ev->state) {
        const char *name = get_corne_key_label(ev->position);
        snprintf(key_text, sizeof(key_text), "Tecla: %s", name);
        if (key_label) {
            lv_label_set_text(key_label, key_text);
        }
    }
    return ZMK_EV_EVENT_BUBBLE;
}

ZMK_LISTENER(custom_last_key_listener, last_key_listener_cb);
ZMK_SUBSCRIPTION(custom_last_key_listener, zmk_position_state_changed);

static struct zmk_widget_battery_status battery_widget;
static struct zmk_widget_output_status output_widget;
static struct zmk_widget_layer_status layer_widget;

lv_obj_t *zmk_display_status_screen() {
    lv_obj_t *screen = lv_obj_create(NULL);

    zmk_widget_battery_status_init(&battery_widget, screen);
    lv_obj_align(zmk_widget_battery_status_obj(&battery_widget), LV_ALIGN_TOP_RIGHT, 0, 0);

    zmk_widget_output_status_init(&output_widget, screen);
    lv_obj_align(zmk_widget_output_status_obj(&output_widget), LV_ALIGN_TOP_LEFT, 0, 0);

    zmk_widget_layer_status_init(&layer_widget, screen);
    lv_obj_align(zmk_widget_layer_status_obj(&layer_widget), LV_ALIGN_BOTTOM_LEFT, 0, 0);

    key_label = lv_label_create(screen);
    lv_label_set_text(key_label, key_text);
    lv_obj_align(key_label, LV_ALIGN_CENTER, 0, 0);

    return screen;
}
