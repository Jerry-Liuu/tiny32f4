
#ifndef __BSP_SYS_H__
#define __BSP_SYS_H__


#define ASSERT                      (0)
#define ERROR                       (1)
#define WARN                        (2)
#define INFO                        (3)
#define DEBUG                       (4)
#define VERBOSE                     (5)

#define MSG_TAG                              "App:"

#define log_a(...)       elog_a(MSG_TAG, __VA_ARGS__)
#define log_e(...)       elog_e(MSG_TAG, __VA_ARGS__)
#define log_w(...)       elog_w(MSG_TAG, __VA_ARGS__)
#define log_i(...)       elog_i(MSG_TAG, __VA_ARGS__)
#define log_d(...)       elog_d(MSG_TAG, __VA_ARGS__)
#define log_v(...)       elog_v(MSG_TAG, __VA_ARGS__)

#define elog_a(tag, ...)     elog_assert(tag, __VA_ARGS__)
#define elog_e(tag, ...)     elog_error(tag, __VA_ARGS__)
#define elog_w(tag, ...)     elog_warn(tag, __VA_ARGS__)
#define elog_i(tag, ...)     elog_info(tag, __VA_ARGS__)
#define elog_d(tag, ...)     elog_debug(tag, __VA_ARGS__)
#define elog_v(tag, ...)     elog_verbose(tag, __VA_ARGS__)

#define elog_assert(tag, ...) \
        lib_printf_log(ASSERT, tag, __FILE__, __FUNCTION__, __LINE__, __VA_ARGS__)
#define elog_error(tag, ...) \
        lib_printf_log(ERROR, tag, __FILE__, __FUNCTION__, __LINE__, __VA_ARGS__)
#define elog_warn(tag, ...) \
        lib_printf_log(WARN, tag, __FILE__, __FUNCTION__, __LINE__, __VA_ARGS__)
#define elog_info(tag, ...) \
        lib_printf_log(INFO, tag, __FILE__, __FUNCTION__, __LINE__, __VA_ARGS__)
#define elog_debug(tag, ...) \
        lib_printf_log(DEBUG, tag, __FILE__, __FUNCTION__, __LINE__, __VA_ARGS__)
#define elog_verbose(tag, ...) \
        lib_printf_log(VERBOSE, tag, __FILE__, __FUNCTION__, __LINE__, __VA_ARGS__)
                
extern int32_t sleep(uint32_t nus);
extern int32_t Sleep(uint32_t nms);

typedef void(*printf_log)(uint8_t level, const char *tag, const char *file, const char *func,
        const long line, const char *format,...);
extern printf_log lib_printf_log;
#endif

