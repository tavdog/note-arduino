#ifndef MOCK_SERIAL_ARDUINO_HPP
#define MOCK_SERIAL_ARDUINO_HPP

#include <stddef.h>
#include <stdint.h>

#include "NoteSerial.hpp"

struct MakeNoteSerial_Parameters {
    MakeNoteSerial_Parameters(
        void
    ) :
        invoked(0),
        serial_channel(nullptr),
        baud_rate(0),
        result(nullptr)
    { }
    void reset (
        void
    ) {
        invoked = 0;
        serial_channel = nullptr;
        baud_rate = 0;
        result = nullptr;
    }
    size_t invoked;
    NoteSerial::channel_t serial_channel;
    size_t baud_rate;
    NoteSerial * result;
};

struct NoteSerialAvailable_Parameters {
    NoteSerialAvailable_Parameters(
        void
    ) :
        invoked(0),
        result(0)
    { }
    void reset (
        void
    ) {
        invoked = 0;
        result = 0;
    }
    size_t invoked;
    size_t result;
};

struct NoteSerialReceive_Parameters {
    NoteSerialReceive_Parameters(
        void
    ) :
        invoked(0),
        result('\0')
    { }
    void reset (
        void
    ) {
        invoked = 0;
        result = '\0';
    }
    size_t invoked;
    char result;
};

struct NoteSerialReset_Parameters {
    NoteSerialReset_Parameters(
        void
    ) :
        invoked(0),
        result(false)
    { }
    void reset (
        void
    ) {
        invoked = 0;
        result = false;
    }
    size_t invoked;
    bool result;
};

struct NoteSerialTransmit_Parameters {
    NoteSerialTransmit_Parameters(
        void
    ) :
        invoked(0),
        buffer(nullptr),
        size(0),
        flush(false),
        result(0)
    { }
    void reset (
        void
    ) {
        invoked = 0;
        buffer = nullptr;
        size = 0;
        flush = false;
        result = 0;
    }
    size_t invoked;
    uint8_t * buffer;
    size_t size;
    bool flush;
    size_t result;
};

extern MakeNoteSerial_Parameters make_note_serial_Parameters;
extern NoteSerialAvailable_Parameters noteSerialAvailable_Parameters;
extern NoteSerialReceive_Parameters noteSerialReceive_Parameters;
extern NoteSerialReset_Parameters noteSerialReset_Parameters;
extern NoteSerialTransmit_Parameters noteSerialTransmit_Parameters;

#endif // MOCK_SERIAL_ARDUINO_HPP
