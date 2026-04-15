/*
 * SPDX-FileCopyrightText: 2021-2026 The LineageOS Project
 * SPDX-License-Identifier: Apache-2.0
 */

#define LOG_TAG "vendor.lineage.touch-service.blackberry"

#include "GloveMode.h"

#include <android-base/file.h>
#include <android-base/logging.h>
#include <android-base/strings.h>

namespace aidl {
namespace vendor {
namespace lineage {
namespace touch {

static const std::string kGloveModePath =
        "/sys/devices/virtual/tp_device/tp_glove/glove_enable";

ndk::ScopedAStatus GloveMode::getEnabled(bool* _aidl_return) {
    std::string val;

    if (!::android::base::ReadFileToString(kGloveModePath, &val)) {
        PLOG(ERROR) << "Failed to read glove_enable";
        *_aidl_return = false;
        return ndk::ScopedAStatus::ok();
    }

    val = ::android::base::Trim(val);
    *_aidl_return = (val == "0x1" || val == "1");
    return ndk::ScopedAStatus::ok();
}

ndk::ScopedAStatus GloveMode::setEnabled(bool enabled) {
    std::string val = enabled ? "1" : "0";

    if (!::android::base::WriteStringToFile(val, kGloveModePath)) {
        PLOG(ERROR) << "Failed to write glove_enable";
    }

    return ndk::ScopedAStatus::ok();
}

}  // namespace touch
}  // namespace lineage
}  // namespace vendor
}  // namespace aidl
