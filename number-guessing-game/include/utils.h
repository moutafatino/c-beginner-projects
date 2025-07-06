#ifndef _UTILS_H
#define _UTILS_H
/**
 * @brief Get an integer value from the user within a specified range.
 * @param min The minimum valid value (inclusive).
 * @param max The maximum valid value (inclusive).
 * @param format The format string for the prompt.
 * @param ... Additional arguments for the format string.
 *
 */
int get_int_value(int min, int max, const char *format, ...);

#endif
