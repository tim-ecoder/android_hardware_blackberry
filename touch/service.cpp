/*
 * SPDX-FileCopyrightText: 2021-2026 The LineageOS Project
 * SPDX-License-Identifier: Apache-2.0
 */

#define LOG_TAG "vendor.lineage.touch-service.blackberry"

#include "GloveMode.h"
#include "KeyDisabler.h"

#include <android-base/logging.h>
#include <android/binder_manager.h>
#include <android/binder_process.h>

using aidl::vendor::lineage::touch::GloveMode;
using aidl::vendor::lineage::touch::KeyDisabler;

int main() {
    ABinderProcess_setThreadPoolMaxThreadCount(0);

    std::shared_ptr<GloveMode> glovemode = ndk::SharedRefBase::make<GloveMode>();
    const std::string gloveInstance = std::string(GloveMode::descriptor) + "/default";
    binder_status_t status =
            AServiceManager_addService(glovemode->asBinder().get(), gloveInstance.c_str());
    CHECK_EQ(status, STATUS_OK) << "Failed to add service " << gloveInstance << " " << status;

    std::shared_ptr<KeyDisabler> keydisabler = ndk::SharedRefBase::make<KeyDisabler>();
    const std::string keyInstance = std::string(KeyDisabler::descriptor) + "/default";
    status = AServiceManager_addService(keydisabler->asBinder().get(), keyInstance.c_str());
    CHECK_EQ(status, STATUS_OK) << "Failed to add service " << keyInstance << " " << status;

    ABinderProcess_joinThreadPool();
    return EXIT_FAILURE;  // should not reach
}
