//
// Created by redos on 2020-02-11.
//

#ifndef MYFFMPEGTEST_FGFFMPEGDEF_H
#define MYFFMPEGTEST_FGFFMPEGDEF_H

typedef void (*FFmpegProgressCB)(int64_t taskId, int status, int64_t frames, int64_t totalFrames);
typedef void (*FFmpegLogCB)(void* ptr, int level, const char* fmt, va_list vl);
typedef void (*FFmpegErrorCB)(int64_t taskId);

#endif //MYFFMPEGTEST_FGFFMPEGDEF_H
