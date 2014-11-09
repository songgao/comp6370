#ifndef H_FILE
#define H_FILE

void read_all(const char *fname, char **buf_p, size_t *len_p);

// extract key and plain text from file, and store '\0' terminated strings in
// *key_p and *plain_text_p
void extract_input(const char *fname, char **key_p, char **plain_text_p);

void write_result(const char *fname,
    const char *plain_text, const char *key, const char *cipher_text);

#endif
