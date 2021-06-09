#ifndef __ESP32_VS1053_Stream__
#define __ESP32_VS1053_Stream_

#include <Arduino.h>
#include <HTTPClient.h>
#include <VS1053.h>

#include "vs1053b-patches.plg.h"

#define VS1053_INITIALVOLUME          95
#define VS1053_MAXVOLUME              100
#define VS1053_ICY_METADATA           true

#define CONNECT_TIMEOUT_MS            250
#define CONNECT_TIMEOUT_MS_SSL        2500

#define VS1053_USE_HTTP_BUFFER        true
#define VS1053_HTTP_BUFFERSIZE        (size_t)(1024 * 6)          // on stream start - try to wait for this amount of bytes in the buffer
#define VS1053_MAX_RETRIES            5                           // but just start playing after MAX_RETRIES regardless of stored amount

extern void audio_showstation(const char*) __attribute__((weak));
extern void audio_eof_stream(const char*) __attribute__((weak));
extern void audio_showstreamtitle(const char*) __attribute__((weak));


class ESP32_VS1053_Stream {

    public:
        ESP32_VS1053_Stream();
        ~ESP32_VS1053_Stream();

        bool startDecoder(const uint8_t CS, const uint8_t DCS, const uint8_t DREQ);

        bool connecttohost(const String& url);
        bool connecttohost(const String& url, const size_t startrange);
        bool connecttohost(const String& url, const String& user, const String& pwd);
        bool connecttohost(const String& url, const String& user, const String& pwd, const size_t startrange);

        void loop();
        bool isRunning();
        void stopSong();
        uint8_t getVolume();
        void setVolume(const uint8_t vol); /* 0-100 but only range 60-100 is used in web interface */
        String currentCodec();

    private:
        VS1053* _vs1053 = NULL;
        void _loadUserCode();
        void _handleStream(WiFiClient* const stream);
        void _handleChunkedStream(WiFiClient* const stream);
        void _nextChunk(WiFiClient* const stream);
        void _handleChunkedMetaData(WiFiClient* const stream);
};

#endif