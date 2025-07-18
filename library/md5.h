#pragma once

// 16 bytes == 128 bit digest
#define MD5_DIGEST_LENGTH 16

struct md5_context_t {
  unsigned int  buf[4];
  unsigned int  bits[2];
  unsigned char in[64];
};

namespace md5 {
  void         init(md5_context_t* context);
  void         update(md5_context_t* context, unsigned char const* buf, unsigned int len);
  void         final(unsigned char digest[MD5_DIGEST_LENGTH], md5_context_t* context);
  unsigned int pseudo_random(unsigned int seed);
} // namespace md5