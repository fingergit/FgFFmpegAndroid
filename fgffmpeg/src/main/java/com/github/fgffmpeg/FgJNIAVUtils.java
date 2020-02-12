package com.github.fgffmpeg;

/**
 * 类说明
 *
 * @author redos
 * @version 1.0.0
 * @date 2020-02-10
 * @mail redos@sina.com
 */
public class FgJNIAVUtils {
    static {
        System.loadLibrary("ffmpeg");
        System.loadLibrary("FgFFmpeg-lib");
    }

    public native static String getFileInfo(String filePath);
    public native static int ffmpegMain(long taskId, String[] argv, FgFFmpegProgressCallback callback);
    public native static void printCodecs();

    public interface FgFFmpegProgressCallback {
        public void OnProgress(long taskId, int status, long frames, long totalFrames);
    }
}
