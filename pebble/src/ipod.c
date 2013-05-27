#include "pebble_os.h"
#include "pebble_app.h"
#include "pebble_fonts.h"

#include "main_menu.h"
#include "library_menus.h"
#include "marquee_text.h"

#define MY_UUID { 0x24, 0xCA, 0x78, 0x2C, 0xB3, 0x1F, 0x49, 0x04, 0x83, 0xE9, 0xCA, 0x51, 0x9C, 0x60, 0x10, 0x97 }
PBL_APP_INFO(MY_UUID,
             "iPod Control", "KB",
             1, 0, /* App version */
             DEFAULT_MENU_ICON,
             APP_INFO_STANDARD_APP);

Window window;

void handle_init(AppContextRef ctx) {
    window_init(&window, "iPod");
    window_stack_push(&window, true /* Animated */);
    main_menu_init(&window);
    init_library_menus();
    resource_init_current_app(&APP_RESOURCES);
    app_timer_send_event(ctx, 33, 0);
}

void handle_timer(AppContextRef app_ctx, AppTimerHandle handle, uint32_t cookie) {
    marquee_text_layer_tick();
    app_timer_send_event(app_ctx, 33, 0);
}


void pbl_main(void *params) {
    PebbleAppHandlers handlers = {
        .init_handler = &handle_init,
        .timer_handler = &handle_timer,
        .messaging_info = (PebbleAppMessagingInfo){
            .buffer_sizes = {
                .inbound = 124,
                .outbound = 256
            }
        }
    };
    app_event_loop(params, &handlers);
}