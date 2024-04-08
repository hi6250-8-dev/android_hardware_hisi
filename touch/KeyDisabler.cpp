/*
 * Copyright (C) 2024 The LineageOS Project
 *
 * SPDX-License-Identifier: Apache-2.0
 */

#include <android-base/file.h>
#include <android-base/logging.h>
#include <android-base/properties.h>
#include <android-base/strings.h>

#include "KeyDisabler.h"

namespace vendor {
namespace lineage {
namespace touch {
namespace V1_0 {
namespace implementation {

static constexpr const char* kFingerprintNav = "/sys/devices/platform/fingerprint/nav";

KeyDisabler::KeyDisabler() {
    mHasKeyDisabler = !access(kFingerprintNav, F_OK);
}

// Methods from ::vendor::lineage::touch::V1_0::IKeyDisabler follow.
Return<bool> KeyDisabler::isEnabled() {
    std::string buf;

    if (!mHasKeyDisabler) return false;

    if (!android::base::ReadFileToString(kFingerprintNav, &buf)) {
        LOG(ERROR) << "Failed to read " << kFingerprintNav;
        return false;
    }

    return std::stoi(android::base::Trim(buf)) == 0;
}

Return<bool> KeyDisabler::setEnabled(bool enabled) {
    if (!mHasKeyDisabler) return false;

    if (android::base::WriteStringToFile((enabled ? "0" : "1"), kFingerprintNav)) {
        // Restart `fps_hal_ext` service
        SetProperty("persist.sys.lineage_touch.enabled", enabled ? "0" : "1");
    } else {
        LOG(ERROR) << "Failed to write " << kFingerprintNav;
        return false;
    }

    return true;
}

}  // namespace implementation
}  // namespace V1_0
}  // namespace touch
}  // namespace lineage
}  // namespace vendor
