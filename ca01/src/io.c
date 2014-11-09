#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "io.h"
#include "encrypt.h"

void read_all(const char * fname, char ** buf_p, size_t * len_p) {
  char * buf;
  size_t len;
  FILE * f;

  f = fopen(fname, "r");

  // determine length
  fseek(f, 0, SEEK_END);
  len = (size_t) ftell(f);
  fseek(f, 0, SEEK_SET);

  buf = (char *) malloc(len);
  fread(buf, 1, len, f);

  fclose(f);

  *len_p = len;
  *buf_p = buf;
}

void extract_input(const char *fname, char **key_p, char **plain_text_p) {
  char *fbuf;
  size_t key_len, plain_text_len, flen;

  read_all(fname, &fbuf, &flen);

  // convert all characters to ones in char_set
  to_char_set(fbuf, flen);

  key_len = (size_t) (strchr(fbuf, '\n') - fbuf);
  plain_text_len = flen - key_len - 1;

  // expand key to the same length as plain_text
  *key_p = (char *) malloc(plain_text_len + 1);
  for (size_t i = 0; i < plain_text_len; i += key_len) {
    if (i + key_len <= plain_text_len) {
      strncpy(*key_p + i, fbuf, key_len);
    } else {
      strncpy(*key_p + i, fbuf, plain_text_len - i);
    }
  }

  *plain_text_p = (char *) malloc(plain_text_len + 1);
  strncpy(*plain_text_p, fbuf + key_len + 1, plain_text_len);

  // TODO: zero-out fbuf (with code that can't be optimized out by compiler)
  // before freeing
  free(fbuf);

  // append '\0' to produce safe-string that can be handled by standard string
  // functions
  (*key_p)[plain_text_len] = '\0';
  (*plain_text_p)[plain_text_len] = '\0';
}

void write_result(const char *fname, const char *plain_text, const char *key, const char *cipher_text) {
  FILE *f;
  f = fopen(fname, "w");
  fprintf(f, "Plain text: %s\n", plain_text);
  fprintf(f, "Key:        %s\n", key);
  fprintf(f, "Encrypted:  %s\n", cipher_text);
  fclose(f);
}

