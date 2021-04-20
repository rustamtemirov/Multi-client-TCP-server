unsigned long int longScanf(char *string, unsigned long long len_max)
{
    unsigned long int current_size = len_max;

    if (string != NULL)
    {
        int c = EOF;
        unsigned long int i = 0;
        while ((c = getchar()) != '\n' && c != EOF)
        {
            string[i++] = (char)c;

            //if reached the max len then realloc size
            {
                if (i == current_size)
                {
                    current_size = i + len_max;
                    string = realloc(string, current_size);
                }
            }
        }
        string[i] = '\0'; // terminator
        current_size = i;
    }
    return current_size;
}

int sendAll(int network_socket, const char *string, int string_length)
{

    int bytes_sent;

    while (string_length > 0)
    {
        bytes_sent = send(network_socket, string, string_length, 0);
        if (bytes_sent == -1)
            return -1;

        string += bytes_sent;
        string_length -= bytes_sent;
    }

    return 1;
}

int recvAll(int network_socket, char *string, int string_length)
{
    int count = 0;
    int dataLength = 0;
    int currentSize = string_length;
    int oldSize = currentSize;
    dataLength = recv(network_socket, string + count, 100000, 0);
    i += dataLength;
    while (dataLength > currentSize)
    {
        dataLength = recv(network_socket, string + count, 100000, 0);
        count += dataLength;
        oldSize = currentSize;
        currentSize += 100000;
        char *newBuffer = malloc(currentSize);
        memcpy(newBuffer, string, oldSize);
        free(string);
        string = newBuffer;
    }
    return count;
}

void reverse(char *string, int len)
{
    char *begin, *end, temp;
    begin = string;
    end = string;
    for (int i = 0; i < len - 1; i++)
        end++;
    for (int i = 0; i < len / 2; i++)
    {
        temp = *end;
        *end = *begin;
        *begin = temp;

        begin++;
        end--;
    }
}
