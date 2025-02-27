#pragma once

#define LOG(format, ...)                                                       \
  do {                                                                         \
    constexpr size_t __LOG_BUFFER_SIZE = 4096;                                 \
    char __log_buffer[__LOG_BUFFER_SIZE];                                      \
    snprintf(__log_buffer, sizeof(__log_buffer), "%s:%d | " format, __FILE__,  \
             __LINE__, ##__VA_ARGS__);                                         \
    std::cout << __log_buffer << std::endl;                                    \
  } while (0);
