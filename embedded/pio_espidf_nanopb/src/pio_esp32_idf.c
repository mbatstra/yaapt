#include "stdio.h"
#include "unistd.h"

#include "pb_decode.h"
#include "pb_encode.h"
#include "yaapt.pb.h"

#include "test.h"


void app_main() {
  int status = 0;

  uint8_t buffer[256];
  pb_ostream_t ostream;
  pb_istream_t istream;
  size_t written;

  SimpleMessage original = SimpleMessage_init_zero;
  original.number = 45;

  ostream = pb_ostream_from_buffer(buffer, sizeof(buffer));

  TEST(pb_encode(&ostream, &SimpleMessage_msg, &original));

  written = ostream.bytes_written;

  istream = pb_istream_from_buffer(buffer, written);

  SimpleMessage decoded = SimpleMessage_init_zero;

  TEST(pb_decode(&istream, &SimpleMessage_msg, &decoded));

  TEST(decoded.number == 45);

  printf("hello\n");
  write(1, "test\n", 5);
}
