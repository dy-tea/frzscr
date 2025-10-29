#ifndef COMMON_H
#define COMMON_H

extern int log_enable_debug;

#define DEBUG(fmt, ...) \
    do { \
        if (log_enable_debug) { \
            fprintf(stderr, "DEBUG: "fmt"\n", ##__VA_ARGS__); \
        } \
    } while(0)

#define WARN(fmt, ...) fprintf(stderr, "WARN: "fmt"\n", ##__VA_ARGS__)
#define EWARN(fmt, ...) fprintf(stderr, "WARN: "fmt": %s\n", ##__VA_ARGS__, strerror(errno))

#define ERR(fmt, ...) fprintf(stderr, "ERROR: "fmt"\n", ##__VA_ARGS__)
#define EERR(fmt, ...) fprintf(stderr, "ERROR: "fmt": %s\n", ##__VA_ARGS__, strerror(errno))

#define DIE(fmt, ...) \
    do { \
        fprintf(stderr, "ERROR: "fmt"\n", ##__VA_ARGS__); exit(1); \
    } while (0)
#define EDIE(fmt, ...) \
    do { \
        fprintf(stderr, "ERROR: "fmt": %s\n", ##__VA_ARGS__, strerror(errno)); exit(1); \
    } while (0)

#define STREQ(a, b) (strcmp((a), (b)) == 0)

#define _3(a, b) a##b
#define _2(a, b) _3(a, b)
#define _ _2(_dummy_param_, __COUNTER__)

#endif /* #ifndef COMMON_H */

