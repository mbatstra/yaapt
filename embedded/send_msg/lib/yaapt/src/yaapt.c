#include "pb_decode.h"
#include "pb_encode.h"
#include "yaapt.pb.h"
#include "yaapt.h"


bool test()
{
  SimpleMessage msg_original = SimpleMessage_init_zero, msg_decoded = SimpleMessage_init_zero;
  uint8_t       buf[SimpleMessage_size];

  msg_original.number = 42;
  size_t len = encode_message(buf, &msg_original);
  decode_message(buf, &msg_decoded, len);

  return msg_original.number == msg_decoded.number;
}

// TODO: generalize message type with x macro
size_t encode_message(uint8_t* buf, SimpleMessage* msg)
{
  pb_ostream_t ostream = pb_ostream_from_buffer(buf, sizeof(buf));
  if (!pb_encode(&ostream, &SimpleMessage_msg, msg)) {
    exit(1);
  }
  return ostream.bytes_written;
}

void decode_message(uint8_t* buf, SimpleMessage* msg, size_t len)
{
  pb_istream_t istream = pb_istream_from_buffer(buf, len);
  if (!pb_decode(&istream, &SimpleMessage_msg, msg)) {
    exit(1);
  }
}
