#ifndef SEARCH_TREE_LOGGER_H
#define SEARCH_TREE_LOGGER_H

#include <iostream>

// log levels
#define LOG_LEVEL_INFO 1
#define LOG_LEVEL_WARN 2
#define LOG_LEVEL_ERR  4

// used log level
#define LOG_LEVEL LOG_LEVEL_INFO | LOG_LEVEL_WARN | LOG_LEVEL_ERR

#define LOG_INFO(log_msg)                   \
    if ((LOG_LEVEL & LOG_LEVEL_INFO) > 0)   \
        printf("[INFO] %s\n", log_msg);

#define LOG_WARN(log_msg)                   \
    if ((LOG_LEVEL & LOG_LEVEL_WARN) > 0)   \
        printf("[WARN] %s\n", log_msg)

#define LOG_ERR(log_msg)                    \
    if ((LOG_LEVEL & LOG_LEVEL_ERR) > 0)    \
        printf("[ERROR] %s\n", log_msg);

#endif //SEARCH_TREE_LOGGER_H
