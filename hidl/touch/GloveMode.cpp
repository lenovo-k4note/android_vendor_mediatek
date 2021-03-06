/*
 * Copyright (C) 2019 The LineageOS Project
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *      http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#include <android-base/logging.h>
#include <utils/Errors.h>
#include "GloveMode.h"

#include <fstream>

namespace vendor {
namespace lineage {
namespace touch {
namespace V1_0 {
namespace lenovo {

static constexpr const char *kTouchGlovePath = "/sys/lenovo_tp_gestures/tpd_glove_status";

// Methods from ::vendor::lineage::touch::V1_0::IGloveMode follow.
Return<bool> GloveMode::isEnabled() {
    int result;

    std::ifstream file(kTouchGlovePath);
    if (!file.is_open()) {
        LOG(ERROR) << "Failed to open " << kTouchGlovePath << ", error=" << errno
                   << " (" << strerror(errno) << ")";
        return false;
    }

    file >> result;
    return !file.fail() && result > 0;
}

Return<bool> GloveMode::setEnabled(bool enabled) {
    std::ofstream file(kTouchGlovePath);
    if (!file.is_open()) {
        LOG(ERROR) << "Failed to open " << kTouchGlovePath << ", error=" << errno
                   << " (" << strerror(errno) << ")";
        return false;
    }
    file << (enabled ? "1" : "0");
    return !file.fail();
}

}  // namespace lenovo
}  // namespace V1_0
}  // namespace touch
}  // namespace lineage
}  // namespace vendor
