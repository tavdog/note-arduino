#include "mock/NoteI2c_Mock.hpp"

#include "NoteI2c_Arduino.hpp"

MakeNoteI2c_Parameters make_note_i2c_Parameters;
NoteI2cReceive_Parameters noteI2cReceive_Parameters;
NoteI2cReset_Parameters noteI2cReset_Parameters;
NoteI2cTransmit_Parameters noteI2cTransmit_Parameters;

NoteI2c *
make_note_i2c (
    NoteI2c::bus_t i2c_bus_
)
{
    // Record invocation(s)
    ++make_note_i2c_Parameters.invoked;

    // Stash parameter(s)
    make_note_i2c_Parameters.i2c_bus = i2c_bus_;

    // Return user-supplied result
    return make_note_i2c_Parameters.result;
}

NoteI2c_Arduino::NoteI2c_Arduino (
    TwoWire & i2c_bus_
) :
    _i2cPort(i2c_bus_)
{

}

const char *
NoteI2c_Arduino::receive (
    uint16_t device_address_,
    uint8_t * buffer_,
    uint16_t requested_byte_count_,
    uint32_t * available_
) {
    // Record invocation(s)
    ++noteI2cReceive_Parameters.invoked;

    // Stash parameter(s)
    noteI2cReceive_Parameters.device_address = device_address_;
    noteI2cReceive_Parameters.buffer = buffer_;
    noteI2cReceive_Parameters.requested_byte_count = requested_byte_count_;
    noteI2cReceive_Parameters.available = available_;

    // Return user-supplied result
    return noteI2cReceive_Parameters.result;
}

bool
NoteI2c_Arduino::reset (
    uint16_t device_address_
) {
    // Record invocation(s)
    ++noteI2cReset_Parameters.invoked;

    // Stash parameter(s)
    noteI2cReset_Parameters.device_address = device_address_;

    // Return user-supplied result
    return noteI2cReset_Parameters.result;
}

const char *
NoteI2c_Arduino::transmit (
    uint16_t device_address_,
    uint8_t * buffer_,
    uint16_t size_
) {
    // Record invocation(s)
    ++noteI2cTransmit_Parameters.invoked;

    // Stash parameter(s)
    noteI2cTransmit_Parameters.device_address = device_address_;
    noteI2cTransmit_Parameters.buffer = buffer_;
    noteI2cTransmit_Parameters.size = size_;

    // Return user-supplied result
    return noteI2cTransmit_Parameters.result;
}
