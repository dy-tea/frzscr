#include <stdlib.h>
#include <errno.h>
#include <stdio.h>
#include <string.h>
#include <signal.h>

#include "utils.h"
#include "common.h"

void rotate_image(void *dest, const void *src, int w, int h,
                  int bytes_per_pixel, enum wl_output_transform transform) {
    uint8_t *d = dest;
    const uint8_t *s = src;
    int x, y, new_x, new_y;

    switch (transform) {
    case WL_OUTPUT_TRANSFORM_NORMAL:
        memcpy(dest, src, w * h * bytes_per_pixel);
        break;

    case WL_OUTPUT_TRANSFORM_90:
        for (y = 0; y < h; y++) {
            for (x = 0; x < w; x++) {
                new_x = h - 1 - y;
                new_y = x;

                memcpy(d + (new_y * h + new_x) * bytes_per_pixel,
                       s + (y * w + x) * bytes_per_pixel,
                       bytes_per_pixel);
            }
        }
        break;

    case WL_OUTPUT_TRANSFORM_180:
        for (y = 0; y < h; y++) {
            for (x = 0; x < w; x++) {
                new_x = w - 1 - x;
                new_y = h - 1 - y;

                memcpy(d + (new_y * w + new_x) * bytes_per_pixel,
                       s + (y * w + x) * bytes_per_pixel,
                       bytes_per_pixel);
            }
        }
        break;

    case WL_OUTPUT_TRANSFORM_270:
        for (y = 0; y < h; y++) {
            for (x = 0; x < w; x++) {
                new_x = y;
                new_y = w - 1 - x;

                memcpy(d + (new_y * h + new_x) * bytes_per_pixel,
                       s + (y * w + x) * bytes_per_pixel,
                       bytes_per_pixel);
            }
        }
        break;

    case WL_OUTPUT_TRANSFORM_FLIPPED:
        for (y = 0; y < h; y++) {
            for (x = 0; x < w; x++) {
                new_x = w - 1 - x;
                new_y = y;

                memcpy(d + (new_y * w + new_x) * bytes_per_pixel,
                       s + (y * w + x) * bytes_per_pixel,
                       bytes_per_pixel);
            }
        }
        break;

    case WL_OUTPUT_TRANSFORM_FLIPPED_90:
        for (y = 0; y < h; y++) {
            for (x = 0; x < w; x++) {
                new_x = y;
                new_y = x;

                memcpy(d + (new_y * h + new_x) * bytes_per_pixel,
                       s + (y * w + x) * bytes_per_pixel,
                       bytes_per_pixel);
            }
        }
        break;

    case WL_OUTPUT_TRANSFORM_FLIPPED_180:
        for (y = 0; y < h; y++) {
            for (x = 0; x < w; x++) {
                new_x = x;
                new_y = h - 1 - y;

                memcpy(d + (new_y * w + new_x) * bytes_per_pixel,
                       s + (y * w + x) * bytes_per_pixel,
                       bytes_per_pixel);
            }
        }
        break;

    case WL_OUTPUT_TRANSFORM_FLIPPED_270:
        for (y = 0; y < h; y++) {
            for (x = 0; x < w; x++) {
                new_x = h - 1 - y;
                new_y = w - 1 - x;

                memcpy(d + (new_y * h + new_x) * bytes_per_pixel,
                       s + (y * w + x) * bytes_per_pixel,
                       bytes_per_pixel);
            }
        }
        break;
    }
}

bool str_to_ulong(const char *str, unsigned long *res) {
    char *endptr = NULL;

    errno = 0;
    unsigned long res_tmp = strtoul(str, &endptr, 10);

    if (errno == 0 && *endptr == '\0') {
        *res = res_tmp;
        return true;
    } else if (errno != 0) {
        EERR("failed to convert %s to number", str);
        return false;
    } else {
        ERR("failed to convert %s to number: Invalid character %c", str, *endptr);
        return false;
    }
}

bool is_valid_signal(int sig) {
    sigset_t set;
    sigemptyset(&set);
    return sigaddset(&set, sig) == 0;
}

// some bs
uint32_t get_bytes_per_pixel(uint32_t format) {
    switch (format) {
        case WL_SHM_FORMAT_RGB888:
        case WL_SHM_FORMAT_BGR888:
            return 3;
        case WL_SHM_FORMAT_RGB565:
        case WL_SHM_FORMAT_BGR565:
        case WL_SHM_FORMAT_ARGB4444:
        case WL_SHM_FORMAT_XRGB4444:
            return 2;
        case WL_SHM_FORMAT_ARGB8888:
        case WL_SHM_FORMAT_XRGB8888:
        case WL_SHM_FORMAT_XBGR2101010:
        default:
            return 4;
    }
}
