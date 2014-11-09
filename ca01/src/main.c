#include <unistd.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

#include "encrypt.h"
#include "io.h"

bool opts(int argc, char ** argv, char **in_name_p, char **out_name_p) {
  bool successful = true;
  int c;
  extern char *optarg;
  extern int optopt;

  *in_name_p = *out_name_p = NULL;

  while((c = getopt(argc, argv, ":i:o:h")) != -1) {
    switch(c) {
      case 'i':
        *in_name_p = optarg;
        break;
      case 'o':
        *out_name_p = optarg;
        break;
      case ':':
        fprintf(stderr, "Option -%c requires an operand\n", optopt);
        successful = false;
        break;
      case 'h':
        successful = false;
        break;
      case '?':
        fprintf(stderr, "Unrecognized option: -%c\n", optopt);
        successful = false;
        break;
    }
  }

  if (!*in_name_p) {
    *in_name_p = "plain.txt";
  }

  if (!*out_name_p) {
    *out_name_p = "result.txt";
  }

  return successful;
}

void usage(char *exe) {
  fprintf(stderr, "Usage: %s [-i input_namefile] [-o output_filename]\n", exe);
  fprintf(stderr, "       %s -h (print this message)\n", exe);
}

int main(int argc, char ** argv) {
  char *in, *out;

  char *key, *plain_text;

  if (!opts(argc, argv, &in, &out)) {
    usage(argv[0]);
    return 1;
  }

  extract_input(in, &key, &plain_text);

  char * cipher_text = encipher(key, plain_text);

  write_result(out, plain_text, key, cipher_text);

  free(plain_text);
  free(key);
  free(cipher_text);

  return 0;
}
