#include "yaapt.pb.h"

#include "pico/cyw43_arch.h"
#include "pico/stdlib.h"
#include "pico/time.h"
#include <pb_encode.h>

void blink_poll(int delay) {
  static bool is_on = false;
  static uint32_t next_toggle_ms = 0;

  uint32_t now_ms = to_ms_since_boot(get_absolute_time());
  if (now_ms >= next_toggle_ms) {
    next_toggle_ms = now_ms + delay;

    is_on = !is_on;
    cyw43_arch_gpio_put(CYW43_WL_GPIO_LED_PIN, is_on);
  }
}

void send_msg_interval(const uint8_t* buf, int delay) {
  static bool send = false;
  static uint32_t next_send_ms = 0;

  uint32_t now_ms = to_ms_since_boot(get_absolute_time());
  if (now_ms >= next_send_ms) {
    next_send_ms = now_ms + delay;
    send = !send;
    printf("%s", buf);
  }
}

void pack_msg(uint8_t* buf) {
  SimpleMessage msg = { 42 };
  pb_ostream_t stream = pb_ostream_from_buffer(buf, sizeof(buf));
  pb_encode(&stream, SimpleMessage_fields, &msg);
}

int main() {
  uint8_t buf[64] = { 0 };

  stdio_init_all();

  if (cyw43_arch_init() != 0) {
    printf("cyw43 init failed\n");
  }

  while (true) {
    cyw43_arch_poll();
    pack_msg(buf);
    send_msg_interval(buf, 5000);
    bzero(buf, sizeof(buf));
    blink_poll(5000);
    cyw43_arch_wait_for_work_until(make_timeout_time_ms(1000));
  }
}
