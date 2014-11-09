#include <string.h>
#include <stdlib.h>
#include "encrypt.h"

const char *char_set = " ABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789.";
const size_t char_set_len = 38;

int ind(const char c) {
  if (c >= 'A' && c <= 'Z') {
    return c - 'A' + 1;
  } else if (c >= '0' && c <= '9') {
    return c - '0' + 27;
  } else if (c == ' ') {
    return 0;
  } else if (c == '.') {
    return 37;
  } else {
    return -1;
  }
}

void to_char_set(char * plain_text, const size_t len) {
  int i;
  for(i = 0; i < len; ++i) {
    if(plain_text[i] >= 'a' && plain_text[i] <= 'z') {
      plain_text[i] -= 'a' - 'A';
    }
    if (-1 == ind(plain_text[i]) && '\n' != plain_text[i]) {
      plain_text[i] = '.';
    }
  }
}

char * encipher(const char * key, char * plain_text) {
  char *buf = (char *) malloc(strlen(plain_text) + 1);
  char *p_buf = buf;
  const char *p_plain_text = plain_text, *p_key = key;
  size_t previous_cipher = 0;

  for(; *p_plain_text != '\0'; ++p_plain_text, ++p_buf) {
    if (is_passthrough(*p_plain_text)) {
      // for passthrough characters, nothing's changed; neither does p_key
      // increase
      *p_buf = *p_plain_text;
      continue;
    }

    previous_cipher = encrypt_char(*p_plain_text, *p_key, previous_cipher);
    *p_buf = char_set[previous_cipher];

    ++p_key;
  }

  *p_buf = '\0';

  return buf;
}

