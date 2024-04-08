/*
 * Copyright (C) 2024 The LineageOS Project
 *
 * SPDX-License-Identifier: Apache-2.0
 */

#pragma once

#include <vendor/lineage/touch/1.0/IKeyDisabler.h>

namespace vendor {
namespace lineage {
namespace touch {
namespace V1_0 {
namespace implementation {

using android::sp;
using android::hardware::Return;

class KeyDisabler : public IKeyDisabler {
  public:
    KeyDisabler();

    // Methods from ::vendor::lineage::touch::V1_0::IKeyDisabler follow.
    Return<bool> isEnabled() override;
    Return<bool> setEnabled(bool enabled) override;

  private:
    bool mHasKeyDisabler;
};

}  // namespace implementation
}  // namespace V1_0
}  // namespace touch
}  // namespace lineage
}  // namespace vendor
