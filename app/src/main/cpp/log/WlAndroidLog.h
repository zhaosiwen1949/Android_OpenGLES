//
// Created by DELL on 2023-09-05.
//

#ifndef ANDROID_OPENGLES_WLANDROIDLOG_H
#define ANDROID_OPENGLES_WLANDROIDLOG_H

#include "android/log.h"

#define LOGD(TAG, FORMAT, ...) __android_log_print(ANDROID_LOG_DEBUG, TAG, FORMAT, ##__VA_ARGS__);
#define LOGE(TAG, FORMAT, ...) __android_log_print(ANDROID_LOG_ERROR, TAG, FORMAT, ##__VA_ARGS__);

#endif //ANDROID_OPENGLES_WLANDROIDLOG_H
