#include "convert2int.h"

/**
 * @brief
 *
 * @param num
 * @return int
 */
int convert2int(const char *num)
{
    char *result = malloc(sizeof(char) * 512);
    for (int i = 0; i < strlen(num) - 2; i++)
    {
        result[i] = num[i + 1];
    }
    int n = atoi(result);
    free(result);
    return n;
}