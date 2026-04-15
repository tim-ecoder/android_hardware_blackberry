/*
 * SPDX-FileCopyrightText: 2019-2026 The LineageOS Project
 * SPDX-License-Identifier: Apache-2.0
 */

#define LOG_TAG "vendor.lineage.touch-service.blackberry"

#include "KeyDisabler.h"

#include <android-base/file.h>
#include <android-base/logging.h>
#include <android-base/strings.h>

namespace aidl {
namespace vendor {
namespace lineage {
namespace touch {

static constexpr const char* kControlPath =
        "/sys/devices/virtual/tp_device/tp_button/button_enable";

ndk::ScopedAStatus KeyDisabler::getEnabled(bool* _aidl_return) {
    std::string val;

    if (!::android::base::ReadFileToString(kControlPath, &val)) {
        PLOG(ERROR) << "Failed to read button_enable";
        *_aidl_return = false;
        return ndk::ScopedAStatus::ok();
    }

    val = ::android::base::Trim(val);
    // button_enable=0 means keys disabled → return true
    *_aidl_return = (val == "0x0" || val == "0");
    return ndk::ScopedAStatus::ok();
}

ndk::ScopedAStatus KeyDisabler::setEnabled(bool enabled) {
    std::string val = enabled ? "0" : "1";

    if (!::android::base::WriteStringToFile(val, kControlPath)) {
        PLOG(ERROR) << "Failed to write button_enable";
    }

    return ndk::ScopedAStatus::ok();
}

}  // namespace touch
}  // namespace lineage
}  // namespace vendor
}  // namespace aidl
