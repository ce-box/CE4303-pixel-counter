#include "logging.h"

/**
 * @brief Set the logging path object
 *
 * @param log_path
 */
void set_logging_path(char *log_path)
{
    log_file = log_path;
}

/**
 * @brief
 *
 * @param msg
 */
void logging(char *msg)
{
    FILE *fptr = NULL;
    fptr = fopen(log_file, "a");
    if (fptr == NULL)
    {
        fprintf(stderr, "[Error] Unable to open log file ...\n");
        return;
    }

    char *log_time = time_stamp();
    fprintf(fptr, "%s - %s\n", log_time, msg);
    fclose(fptr);
}

/**
 * @brief
 *
 * @return char*
 */
char *time_stamp()
{
    time_t raw_time;
    struct tm *time_info;
    char *t_stamp = malloc(sizeof(char) * 20);

    time(&raw_time);
    time_info = localtime(&raw_time);

    strftime(t_stamp, strlen("YYYY-DD-MMM HH:MM") + 2, "%Y-%d-%b %H:%M", time_info);
    return t_stamp;
}