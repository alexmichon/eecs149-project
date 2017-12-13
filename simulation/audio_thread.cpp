#include <audio_thread.h>
#include <mpg123.h>
#include <ao/ao.h>

AudioThread::AudioThread(LedGridLayout *grid, char *filename) {
    strcpy(_filename, filename);
    _canceled = false;
    connect(this, SIGNAL(newBuffer(unsigned char*, int, long)), new TransformThread(grid), SLOT(newBuffer(unsigned char*, int, long)));
}

void AudioThread::run() {
    qDebug("MP3 Init");

    mpg123_handle *mh;
    unsigned char buffer[8192];
    size_t buffer_size = 8192;
    size_t done;
    int err;
    int channels, encoding;
    long rate;

    int driver;
    ao_device *dev;
    ao_sample_format format;

    int refresh_rate = 10;

    ao_initialize();
    driver = ao_default_driver_id();

    mpg123_init();
    mh = mpg123_new(NULL, &err);
    //buffer_size = mpg123_outblock(mh);

    qDebug("MP3 Buffer size: %d", buffer_size);

    mpg123_open(mh, _filename);
    mpg123_getformat(mh, &rate, &channels, &encoding);

    qDebug("MP3 Rate: %d", rate);

    format.bits = mpg123_encsize(encoding) * 8;
    format.rate = rate;
    format.channels = channels;
    format.byte_format = AO_FMT_NATIVE;
    format.matrix = 0;
    dev = ao_open_live(driver, &format, NULL);

    qDebug("bits: %d", format.bits);
    qDebug("channels: %d", format.channels);

    int counter = 0;
    while(mpg123_read(mh, buffer, buffer_size, &done) == MPG123_OK && !_canceled) {
        ao_play(dev, (char *)buffer, done);
        counter++;
        //qDebug("New Buffer");
        //if (counter >= (format.bits * format.rate)/(refresh_rate*buffer_size)) {
            emit newBuffer(buffer, done, rate);
            counter = 0;
        //}
    }

    mpg123_close(mh);
    mpg123_delete(mh);
    mpg123_exit();

    qDebug("MP3 Done");
}

void AudioThread::cancel() {
    _canceled = true;
}
