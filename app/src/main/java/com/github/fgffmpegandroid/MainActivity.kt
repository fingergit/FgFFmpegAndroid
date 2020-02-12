package com.github.fgffmpegandroid

import androidx.appcompat.app.AppCompatActivity
import android.os.Bundle
import android.util.Log
import com.github.fgffmpeg.FgAVUtils
import com.github.fgffmpeg.FgJNIAVUtils
import kotlinx.android.synthetic.main.activity_main.*
import org.jetbrains.anko.doAsync
import java.io.File

class MainActivity : AppCompatActivity() {

    override fun onCreate(savedInstanceState: Bundle?) {
        super.onCreate(savedInstanceState)
        setContentView(R.layout.activity_main)

        val filePath = getDemoFile()
        val outputFile = File(this.cacheDir, "output.mp4")

        FgJNIAVUtils.printCodecs()

        btnStartTranscode.setOnClickListener {
            sample_text.text = FgAVUtils.getFileInfo(filePath)

            doAsync {
                val ret = FgAVUtils.ffmpegMain(1,
                    arrayOf("ffmpeg", "-i", filePath, "-y",
                    "-c:v", "libx264", "-c:a", "aac", "-strict",
                    "experimental", "-b:a", "192k", "-shortest",
                    outputFile.absolutePath
                    ),
                    FgJNIAVUtils.FgFFmpegProgressCallback { taskId, status, frames, totalFrames ->
                        Log.i("MainActivity", String.format("taskId: %d, status: %d, frames: %d, totalFrames: %d",
                            taskId, status, frames, totalFrames))
                        runOnUiThread {
                            if (totalFrames > 0) {
                                progressBar.progress = (frames.toDouble() * 100.0 / totalFrames).toInt()
                            }
                        }
                    })
            }
        }

        btnCopyFile.setOnClickListener {
            sample_text.text = FgAVUtils.getFileInfo(filePath)

            doAsync {
                val ret = FgAVUtils.copyFile(2, filePath, outputFile.absolutePath, 2, 2,
                    FgJNIAVUtils.FgFFmpegProgressCallback { taskId, status, frames, totalFrames ->
                        Log.i("MainActivity", String.format("taskId: %d, status: %d, frames: %d, totalFrames: %d",
                            taskId, status, frames, totalFrames))
                        runOnUiThread {
                            if (totalFrames > 0) {
                                progressBar.progress = (frames.toDouble() * 100.0 / totalFrames).toInt()
                            }
                        }
                    })
            }
        }
    }

    private fun getDemoFile(): String {
        try {
            val inputStream = resources.assets.open("demo.mp4")
            val tempFile = File(this.cacheDir, "demo.mp4")
            tempFile.writeBytes(inputStream.readBytes())

            inputStream.close()
            val len = tempFile.length()
            return tempFile.absolutePath
        } catch (e: Exception) {
            e.printStackTrace()
        }

        return ""
    }

}
