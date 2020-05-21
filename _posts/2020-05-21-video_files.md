# Video basic concepts

Each video file contains two elements:

* Codecs, or "compression-decompression" algorithms which compress the video
* Formats, the type of file the data is compressed to.

## Format/Container

The entire set of storage rules that package a video file’s container, codecs, and metadata.Formats are developed to improve image quality, decrease file sizes, allow for universal playback on a variety of devices, and provide special features such as subtitles.

* AVCHD, sony, advanced video codec high definition
* AVI, microsoft, audio video interlaced
* FLV, adobe
* MPEG, Motion picture experts, Motion Picture Experts Group
* MPEG-4, most popular.
* WMV, microsoft, Windows Media Video
* MOV,Apple
* [MKV](https://www.makemkv.com/aboutmkv/)
* [WebM](https://www.webmproject.org/)

The most popular video format is MP4, also known as MPEG 4. MP4 is a multimedia container for video, audio, and data, including things like subtitles and still images. Make sure you don’t confuse MPEG 4 and MPEG 4 Audio. MPEG 4 has the file extension .MP4, while MPEG 4 Audio has the file extension .M4A and can only contain audio files.

## codecs, compression-decompression

The method a computer uses to determine the amount of change between frames is called the codec
Common used codecs:

* H.264(AVC),1080p,the most widely used video codec used now.
* H.265(HEVC),4k,High Efficiency Video Coding,slowly becoming ubiquitous thanks to the proliferation of 4K content
* [VP9](https://www.webmproject.org/vp9/), compatitor of H.265
* [AV1](https://aomedia.org/av1-features/get-started/),still a highly experimental codec, but is supported by Firefox, Google Chrome, VLC media player, FFmpeg among others

## compression

## Frame rate

The number of frames shown every second.tipycally 24,25,30.
Just like variable bit rate, exporting with a variable frame rate changes the number of frames per second depending on the amount of movement in your video. While theoretically this can save space, not all programs or websites can play back variable frame rate videos, and the audio can fall out-of-sync. To play it safe, stick with a constant frame rate.

## Bit/Data rate

The amount of data that is used for each second of video, measured in kbps.
Bit rates come in two flavors: constant and variable. A constant bit rate (CBR) uses the same amount of data every second, while a variable bit rate (VBR, or ABR, apaptive bit rate) adjusts the amount of data used depending on the complexity of the changes between frames.

## Resolution

The actual size of your video, measured in pixels.

## FFMPEG stuff

time scale, reciprocal of time base,

* tbr,guessed from the video stream and is the value users want to see when they look for the video frame rate
* tbn,AVStream
* tbc,AVCodecContext
* pts, Presentation TimeStamp

## Reference

* [Video compression basics](https://vimeo.com/blog/post/video-compression-basics/)
* [Vimeo Video Compression Guidelines](https://vimeo.com/help/compression)
* [Every Video Format, Codec, and Container Explained](https://medium.com/@api.video/every-video-format-codec-and-container-explained-c831f105c716)
* [Video formats explained](https://www.videomaker.com/article/c10/15362-video-formats-explained)
* [The "codecs" parameter in common media types](https://developer.mozilla.org/en-US/docs/Web/Media/Formats/codecs_parameter)
* [multimedia wiki](https://wiki.multimedia.cx/)
* [FFMPEG tbr,tbn,tbc](http://ffmpeg-users.933282.n4.nabble.com/What-does-the-output-of-ffmpeg-mean-tbr-tbn-tbc-etc-td941538.html)

## Audio

### Channels

### audio codecs

### Data Rate

320 kbit/s?

### Sample rate

48kHZ?

## TODO
