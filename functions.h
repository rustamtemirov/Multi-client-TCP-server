#ifndef HYEHEADER
#define HYEHEADER

#include "functions.c"
#define MAX 1000000

unsigned long int longScanf(char *string, unsigned long long len_max);
int sendAll(int network_socket, const char *string, unsigned long int string_length);
unsigned long int recvAll(int network_socket, char *string, unsigned long int string_length);
void reverse(char *string, int len);

#endif