/*
 * Copyright (C) 2024 The LineageOS Project
 *
 * SPDX-License-Identifier: Apache-2.0
 */

#include <dlfcn.h>
#include <hardware/hardware.h>
#include <stdlib.h>
#include <string.h>

#define LOG_TAG "libshims_hardware"
#include <cutils/log.h>

extern "C" {

static typeof(hw_get_module_by_class)* hw_get_module_by_class_real = NULL;

int hw_get_module_by_class(const char* class_id, const char* inst,
                           const struct hw_module_t** module) {
    if (!hw_get_module_by_class_real) {
        hw_get_module_by_class_real = reinterpret_cast<typeof(hw_get_module_by_class)*>(
                dlsym(RTLD_NEXT, "hw_get_module_by_class"));
    }

    if (hw_get_module_by_class_real) {
        if (class_id && strcmp(class_id, "hisupl.hi1102") == 0) {
            return hw_get_module_by_class_real("hisupl", "hi1102", module);
        } else if (strcmp(class_id, "gps47531") == 0) {
            return hw_get_module_by_class_real("gps", "47531", module);
        }

        return hw_get_module_by_class_real(class_id, inst, module);
    }

    /*
     * If we could not find hw_get_module_by_class, print an error and bail out,
     * we should not pretend everything's fine and return default_value.
     */
    ALOGE("Could not find hw_get_module_by_class, aborting");
    abort();

    return 0;
}
}
