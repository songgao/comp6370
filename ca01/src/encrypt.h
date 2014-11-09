#ifndef H_ENCRYPT
#define H_ENCRYPT

#include <stdbool.h>

extern const char *char_set;
extern const size_t char_set_len;

// returns the index of c in char_set, or -1 if not in char_set
int ind(const char c);

// make sure all characters in plain_text are in char_set
void to_char_set(char * plain_text, const size_t len);

static inline bool is_passthrough(const char c) {
  return c == '\n';
}

// returns index of encrypted character
// caller should make sure c is in char_set
static inline size_t encrypt_char(const char c, const char key, const char previous_cipher) {
  return (ind(c) + ind(key) + previous_cipher) % char_set_len;
}

// encrypts plain text in buf and return cipher text ('\0' terminated)
// caller should make sure plain_text passed to_char_set
char * encipher(const char * key, char * buf);

#endif
