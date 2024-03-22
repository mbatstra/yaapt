#ifndef YAAPT_H
#define YAAPT_H

#include "yaapt.pb.h"

void   decode_message(uint8_t* buf, SimpleMessage* msg, size_t len);
size_t encode_message(uint8_t* buf, SimpleMessage* msg);
bool   test();

#endif // YAAPT_H
