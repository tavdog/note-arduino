#ifndef MOCK_I2C_ARDUINO_HPP
#define MOCK_I2C_ARDUINO_HPP

#include <stddef.h>
#include <stdint.h>

#include "NoteI2c.hpp"

struct MakeNoteI2c_Parameters {
    MakeNoteI2c_Parameters(
        void
    ) :
        invoked(0),
        i2c_bus(nullptr),
        result(nullptr)
    { }
    void reset (
        void
    ) {
        invoked = 0;
        i2c_bus = nullptr;
        result = nullptr;
    }
    size_t invoked;
    NoteI2c::bus_t i2c_bus;
    NoteI2c * result;
};

struct NoteI2cReceive_Parameters {
    NoteI2cReceive_Parameters(
        void
    ) :
        invoked(0),
        device_address(0),
        buffer(nullptr),
        requested_byte_count(0),
        available(nullptr),
        result(nullptr)
    { }
    void reset (
        void
    ) {
        invoked = 0;
        device_address = 0;
        buffer = nullptr;
        requested_byte_count = 0;
        available = nullptr;
        result = nullptr;
    }
    size_t invoked;
    uint16_t device_address;
    uint8_t * buffer;
    uint16_t requested_byte_count;
    uint32_t * available;
    const char * result;
};

struct NoteI2cReset_Parameters {
    NoteI2cReset_Parameters(
        void
    ) :
        invoked(0),
        device_address(0),
        result(false)
    { }
    void reset (
        void
    ) {
        invoked = 0;
        device_address = 0;
        result = false;
    }
    size_t invoked;
    uint16_t device_address;
    bool result;
};

struct NoteI2cTransmit_Parameters {
    NoteI2cTransmit_Parameters(
        void
    ) :
        invoked(0),
        device_address(0),
        buffer(nullptr),
        size(0),
        result(nullptr)
    { }
    void reset (
        void
    ) {
        invoked = 0;
        device_address = 0;
        buffer = nullptr;
        size = 0;
        result = nullptr;
    }
    size_t invoked;
    uint16_t device_address;
    uint8_t * buffer;
    uint16_t size;
    const char * result;
};

extern MakeNoteI2c_Parameters make_note_i2c_Parameters;
extern NoteI2cReceive_Parameters noteI2cReceive_Parameters;
extern NoteI2cReset_Parameters noteI2cReset_Parameters;
extern NoteI2cTransmit_Parameters noteI2cTransmit_Parameters;

#endif // MOCK_I2C_ARDUINO_HPP
