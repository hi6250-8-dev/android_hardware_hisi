/*
 * Copyright (C) 2024 The LineageOS Project
 *
 * SPDX-License-Identifier: Apache-2.0
 */

#define LOG_TAG "vendor.lineage.touch@1.0-service.hisi"

#include <android-base/logging.h>
#include <hidl/HidlTransportSupport.h>

#include "KeyDisabler.h"

using android::OK;
using android::sp;
using android::status_t;
using android::hardware::configureRpcThreadpool;
using android::hardware::joinRpcThreadpool;

using ::vendor::lineage::touch::V1_0::IKeyDisabler;
using ::vendor::lineage::touch::V1_0::implementation::KeyDisabler;

int main() {
    sp<KeyDisabler> keyDisabler;
    status_t status;

    LOG(INFO) << "Touch HAL service is starting.";

    keyDisabler = new KeyDisabler();
    if (keyDisabler == nullptr) {
        LOG(ERROR) << "Can not create an instance of Touch HAL KeyDisabler Iface, exiting.";
        goto shutdown;
    }

    configureRpcThreadpool(1, true /*callerWillJoin*/);

    status = keyDisabler->registerAsService();
    if (status != OK) {
        LOG(ERROR) << "Could not register service for Touch HAL KeyDisabler Iface (" << status
                   << ")";
        goto shutdown;
    }

    LOG(INFO) << "Touch HAL service is ready.";
    joinRpcThreadpool();
    // Should not pass this line

shutdown:
    // In normal operation, we don't expect the thread pool to shutdown
    LOG(ERROR) << "Touch HAL service is shutting down.";
    return 1;
}
