package com.github.fgffmpeg

/**
 * 类说明
 *
 * @author redos
 * @date 2020-02-11
 * @version 1.0.0
 * @mail redos@sina.com
 */
object FgAVUtils {
    fun getFileInfo(filePath: String): String {
        return FgJNIAVUtils.getFileInfo(filePath)
    }

    fun ffmpegMain(
        taskId: Long,
        argv: Array<String>,
        callback: FgJNIAVUtils.FgFFmpegProgressCallback
    ): Int {
        try {
            return FgJNIAVUtils.ffmpegMain(taskId, argv, callback)
        }catch (e: Throwable) {
            e.printStackTrace()
        }
        return -1
    }

    fun copyFile(taskId: Long, srcFilePath: String, trgFilePath: String,
                 startSecond: Long, duration: Long,
                 callback: FgJNIAVUtils.FgFFmpegProgressCallback): Int {
        val argv = arrayOf(
            "ffmpeg",
            "-ss", startSecond.toString(),
            "-i", srcFilePath, "-y",
            "-t", duration.toString(),
            "-c:v", "libx264",
            "-c:a", "aac",
            trgFilePath
            )
        return FgJNIAVUtils.ffmpegMain(taskId, argv, callback)
    }
}