#include "NoteI2c_Arduino.hpp"
#include "TestFunction.hpp"
#include "mock/mock-arduino.hpp"
#include "mock/mock-parameters.hpp"

#include <string.h>

// Compile command: g++ -Wall -Wextra -Wpedantic mock/mock-arduino.cpp mock/mock-note-c-note.c ../src/NoteI2c_Arduino.cpp NoteI2c_Arduino.test.cpp -std=c++14 -I. -I../src -DMOCK && ./a.out || echo "Tests Result: $?"

int test_notei2c_arduino_constructor_invokes_twowire_parameter_begin_method()
{
  int result;

  // Arrange
  twoWireBegin_Parameters.reset();

  // Action
  NoteI2c_Arduino notei2c(Wire);

  // Assert
  if (twoWireBegin_Parameters.invoked)
  {
    result = 0;
  }
  else
  {
    result = static_cast<int>('i' + '2' + 'c');
    std::cout << "FAILED] near line: <" << __LINE__ << ">" << std::endl;
    std::cout << "\ttwoWireBegin_Parameters.invoked == " << !!twoWireBegin_Parameters.invoked << ", EXPECTED: " << true << std::endl;
    std::cout << "[";
  }

  return result;
}

int test_notei2c_arduino_receive_requests_response_data_from_notecard()
{
  int result;

  // Arrange
  const uint16_t EXPECTED_ADDRESS = 0x17;
  const uint8_t REQUEST_SIZE = 13;
  uint8_t response_buffer[32];
  uint32_t actual_response_size;

  twoWireBeginTransmission_Parameters.reset();
  twoWireWriteByte_Parameters.reset();
  twoWireEndTransmission_Parameters.reset();
  twoWireEndTransmission_Parameters.results = {0};
  NoteI2c_Arduino notei2c(Wire);

  // Action
  notei2c.receive(
    EXPECTED_ADDRESS,
    response_buffer,
    REQUEST_SIZE,
    &actual_response_size
  );

  // Assert
  if (
      twoWireBeginTransmission_Parameters.address == EXPECTED_ADDRESS
   && twoWireWriteByte_Parameters.write_buffer[0] == 0
   && twoWireWriteByte_Parameters.write_buffer[1] == REQUEST_SIZE
   && twoWireEndTransmission_Parameters.invoked
  )
  {
    result = 0;
  }
  else
  {
    result = static_cast<int>('i' + '2' + 'c');
    std::cout << "FAILED] near line: <" << __LINE__ << ">" << std::endl;
    std::cout << "\ttwoWireBeginTransmission_Parameters.address == 0x" << std::hex << static_cast<int>(twoWireBeginTransmission_Parameters.address) << ", EXPECTED: 0x" << EXPECTED_ADDRESS << std::dec << std::endl;
    std::cout << "\ttwoWireWriteByte_Parameters.write_buffer[0] == " << static_cast<int>(twoWireWriteByte_Parameters.write_buffer[0]) << ", EXPECTED: " << 0 << std::endl;
    std::cout << "\ttwoWireWriteByte_Parameters.write_buffer[1] == " << static_cast<int>(twoWireWriteByte_Parameters.write_buffer[1]) << ", EXPECTED: " << static_cast<int>(REQUEST_SIZE) << std::endl;
    std::cout << "\ttwoWireEndTransmission_Parameters.invoked == " << !!twoWireEndTransmission_Parameters.invoked << ", EXPECTED: " << true << std::endl;
    std::cout << "[";
  }

  return result;
}

int test_notei2c_arduino_receive_will_retry_transmission_on_i2c_failure()
{
  int result;

  // Arrange
  const uint16_t EXPECTED_RESULT = 0x17;
  const uint8_t REQUEST_SIZE = 13;
  uint8_t response_buffer[32];
  uint32_t actual_response_size;

  twoWireBeginTransmission_Parameters.reset();
  twoWireWriteByte_Parameters.reset();
  twoWireEndTransmission_Parameters.reset();
  twoWireEndTransmission_Parameters.results = {1,0};
  NoteI2c_Arduino notei2c(Wire);

  // Action
  notei2c.receive(
    EXPECTED_RESULT,
    response_buffer,
    REQUEST_SIZE,
    &actual_response_size
  );

  // Assert
  if (
      twoWireBeginTransmission_Parameters.invoked > 1
   && twoWireWriteByte_Parameters.invoked > 2
   && twoWireEndTransmission_Parameters.invoked > 1
  )
  {
    result = 0;
  }
  else
  {
    result = static_cast<int>('i' + '2' + 'c');
    std::cout << "FAILED] near line: <" << __LINE__ << ">" << std::endl;
    std::cout << "\ttwoWireBeginTransmission_Parameters.invoked == " << twoWireBeginTransmission_Parameters.invoked << ", EXPECTED: > 1" << std::endl;
    std::cout << "\ttwoWireWriteByte_Parameters.invoked == " << twoWireWriteByte_Parameters.invoked << ", EXPECTED: > 2" << std::endl;
    std::cout << "\ttwoWireEndTransmission_Parameters.invoked == " << twoWireEndTransmission_Parameters.invoked << ", EXPECTED: > 1" << std::endl;
    std::cout << "[";
  }

  return result;
}

int test_notei2c_arduino_receive_will_not_retry_transmission_on_i2c_success()
{
  int result;

  // Arrange
  const uint16_t EXPECTED_RESULT = 0x17;
  const uint8_t REQUEST_SIZE = 13;
  uint8_t response_buffer[32];
  uint32_t actual_response_size;

  twoWireBeginTransmission_Parameters.reset();
  twoWireWriteByte_Parameters.reset();
  twoWireEndTransmission_Parameters.reset();
  twoWireEndTransmission_Parameters.results = {0};
  NoteI2c_Arduino notei2c(Wire);

  // Action
  notei2c.receive(
    EXPECTED_RESULT,
    response_buffer,
    REQUEST_SIZE,
    &actual_response_size
  );

  // Assert
  if (
      twoWireBeginTransmission_Parameters.invoked == 1
   && twoWireWriteByte_Parameters.invoked == 2
   && twoWireEndTransmission_Parameters.invoked == 1
  )
  {
    result = 0;
  }
  else
  {
    result = static_cast<int>('i' + '2' + 'c');
    std::cout << "FAILED] near line: <" << __LINE__ << ">" << std::endl;
    std::cout << "\ttwoWireBeginTransmission_Parameters.invoked == " << twoWireBeginTransmission_Parameters.invoked << ", EXPECTED: " << 1 << std::endl;
    std::cout << "\ttwoWireWriteByte_Parameters.invoked == " << twoWireWriteByte_Parameters.invoked << ", EXPECTED: " << 2 << std::endl;
    std::cout << "\ttwoWireEndTransmission_Parameters.invoked == " << twoWireEndTransmission_Parameters.invoked << ", EXPECTED: " << 1 << std::endl;
    std::cout << "[";
  }

  return result;
}

int test_notei2c_arduino_receive_will_only_retry_i2c_transmission_thrice()
{
  int result;

  // Arrange
  const uint16_t EXPECTED_RESULT = 0x17;
  const uint8_t REQUEST_SIZE = 13;
  uint8_t response_buffer[32];
  uint32_t actual_response_size;

  twoWireBeginTransmission_Parameters.reset();
  twoWireWriteByte_Parameters.reset();
  twoWireEndTransmission_Parameters.reset();
  twoWireEndTransmission_Parameters.results = {1,1,1,1,0};
  NoteI2c_Arduino notei2c(Wire);

  // Action
  notei2c.receive(
    EXPECTED_RESULT,
    response_buffer,
    REQUEST_SIZE,
    &actual_response_size
  );

  // Assert
  if (
      twoWireBeginTransmission_Parameters.invoked == 3
   && twoWireWriteByte_Parameters.invoked == 6
   && twoWireEndTransmission_Parameters.invoked == 3
  )
  {
    result = 0;
  }
  else
  {
    result = static_cast<int>('i' + '2' + 'c');
    std::cout << "FAILED] near line: <" << __LINE__ << ">" << std::endl;
    std::cout << "\ttwoWireBeginTransmission_Parameters.invoked == " << twoWireBeginTransmission_Parameters.invoked << ", EXPECTED: " << 3 << std::endl;
    std::cout << "\ttwoWireWriteByte_Parameters.invoked == " << twoWireWriteByte_Parameters.invoked << ", EXPECTED: " << 6 << std::endl;
    std::cout << "\ttwoWireEndTransmission_Parameters.invoked == " << twoWireEndTransmission_Parameters.invoked << ", EXPECTED: " << 3 << std::endl;
    std::cout << "[";
  }

  return result;
}

int test_notei2c_arduino_receive_reads_response_data_from_notecard()
{
  int result;

  // Arrange
  const uint16_t EXPECTED_ADDRESS = 0x17;
  const uint8_t REQUEST_SIZE = 13;
  const char * EXPECTED_RESPONSE = "Test Passed!";
  uint8_t response_buffer[32];
  uint32_t bytes_remaining;

  twoWireBeginTransmission_Parameters.reset();
  twoWireWriteByte_Parameters.reset();
  twoWireEndTransmission_Parameters.reset();
  twoWireRequestFrom_Parameters.reset();
  twoWireRequestFrom_Parameters.result = (REQUEST_SIZE + NoteI2c::REQUEST_HEADER_SIZE);
  twoWireRead_Parameters.reset();
  twoWireRead_Parameters.results = {0, REQUEST_SIZE, 'T', 'e', 's', 't', ' ', 'P', 'a', 's', 's', 'e', 'd', '!', '\0'};
  NoteI2c_Arduino notei2c(Wire);

  // Action
  notei2c.receive(
    EXPECTED_ADDRESS,
    response_buffer,
    REQUEST_SIZE,
    &bytes_remaining
  );

  // Assert
  if (
      twoWireRequestFrom_Parameters.address == EXPECTED_ADDRESS
   && twoWireRequestFrom_Parameters.quantity == (REQUEST_SIZE + NoteI2c::REQUEST_HEADER_SIZE)
   && !memcmp(response_buffer, EXPECTED_RESPONSE, REQUEST_SIZE)
  )
  {
    result = 0;
  }
  else
  {
    result = static_cast<int>('i' + '2' + 'c');
    std::cout << "FAILED] near line: <" << __LINE__ << ">" << std::endl;
    std::cout << "\ttwoWireRequestFrom_Parameters.address == 0x" << std::hex << static_cast<int>(twoWireRequestFrom_Parameters.address) << ", EXPECTED: 0x" << EXPECTED_ADDRESS << std::dec << std::endl;
    std::cout << "\ttwoWireRequestFrom_Parameters.quantity == " << twoWireRequestFrom_Parameters.quantity << ", EXPECTED: " << (REQUEST_SIZE + NoteI2c::REQUEST_HEADER_SIZE) << std::endl;
    std::cout << "\tresponse_buffer == \"" << response_buffer << "\"" << ", EXPECTED: " << EXPECTED_RESPONSE << std::endl;
    std::cout << "[";
  }

  return result;
}

int test_notei2c_arduino_receive_updates_available_parameter_with_remaining_bytes()
{
  int result;

  // Arrange
  const uint16_t EXPECTED_ADDRESS = 0x17;
  const uint8_t REQUEST_SIZE = 8;
  uint8_t response_buffer[32];
  uint32_t bytes_remaining;

  twoWireBeginTransmission_Parameters.reset();
  twoWireWriteByte_Parameters.reset();
  twoWireEndTransmission_Parameters.reset();
  twoWireRequestFrom_Parameters.reset();
  twoWireRequestFrom_Parameters.result = (REQUEST_SIZE + NoteI2c::REQUEST_HEADER_SIZE);
  twoWireRead_Parameters.reset();
  twoWireRead_Parameters.results = {5, REQUEST_SIZE, 'T', 'e', 's', 't', ' ', 'P', 'a', 's'};
  NoteI2c_Arduino notei2c(Wire);

  // Action
  notei2c.receive(
    EXPECTED_ADDRESS,
    response_buffer,
    REQUEST_SIZE,
    &bytes_remaining
  );

  // Assert
  if ( bytes_remaining == 5 )
  {
    result = 0;
  }
  else
  {
    result = static_cast<int>('i' + '2' + 'c');
    std::cout << "FAILED] near line: <" << __LINE__ << ">" << std::endl;
    std::cout << "\tbytes_remaining == " << bytes_remaining << ", EXPECTED: " << 5 << std::endl;
    std::cout << "[";
  }

  return result;
}

int test_notei2c_arduino_receive_does_not_request_or_read_i2c_when_trasmission_error_occurs()
{
  int result;

  // Arrange
  const uint16_t EXPECTED_ADDRESS = 0x17;
  const uint8_t REQUEST_SIZE = 13;
  uint8_t response_buffer[32];
  uint32_t bytes_remaining;

  twoWireBeginTransmission_Parameters.reset();
  twoWireWriteByte_Parameters.reset();
  twoWireEndTransmission_Parameters.reset();
  twoWireEndTransmission_Parameters.results = {1,1,1};
  twoWireRequestFrom_Parameters.reset();
  twoWireRequestFrom_Parameters.result = (REQUEST_SIZE + NoteI2c::REQUEST_HEADER_SIZE);
  twoWireRead_Parameters.reset();
  twoWireRead_Parameters.results = {0, REQUEST_SIZE, 'T', 'e', 's', 't', ' ', 'P', 'a', 's', 's', 'e', 'd', '!', '\0'};
  NoteI2c_Arduino notei2c(Wire);

  // Action
  notei2c.receive(
    EXPECTED_ADDRESS,
    response_buffer,
    REQUEST_SIZE,
    &bytes_remaining
  );

  // Assert
  if (
      !twoWireRequestFrom_Parameters.invoked
   && !twoWireRead_Parameters.invoked
  )
  {
    result = 0;
  }
  else
  {
    result = static_cast<int>('i' + '2' + 'c');
    std::cout << "FAILED] near line: <" << __LINE__ << ">" << std::endl;
    std::cout << "\ttwoWireRequestFrom_Parameters.invoked == " << !!twoWireRequestFrom_Parameters.invoked << ", EXPECTED: " << false << std::endl;
    std::cout << "\ttwoWireRead_Parameters.invoked == " << !!twoWireRead_Parameters.invoked << ", EXPECTED: " << false << std::endl;
    std::cout << "[";
  }

  return result;
}

int test_notei2c_arduino_receive_will_not_attempt_to_read_when_i2c_port_request_from_returns_zero()
{
  int result;

  // Arrange
  const uint16_t EXPECTED_ADDRESS = 0x17;
  const uint8_t REQUEST_SIZE = 13;
  uint8_t response_buffer[32];
  uint32_t bytes_remaining;

  twoWireBeginTransmission_Parameters.reset();
  twoWireWriteByte_Parameters.reset();
  twoWireEndTransmission_Parameters.reset();
  twoWireRequestFrom_Parameters.reset();
  twoWireRequestFrom_Parameters.result = 0;
  twoWireRead_Parameters.reset();
  twoWireRead_Parameters.results = {0, REQUEST_SIZE, 'T', 'e', 's', 't', ' ', 'P', 'a', 's', 's', 'e', 'd', '!', '\0'};
  NoteI2c_Arduino notei2c(Wire);

  // Action
  notei2c.receive(
    EXPECTED_ADDRESS,
    response_buffer,
    REQUEST_SIZE,
    &bytes_remaining
  );

  // Assert
  if (
      twoWireRequestFrom_Parameters.invoked
   && !twoWireRead_Parameters.invoked
  )
  {
    result = 0;
  }
  else
  {
    result = static_cast<int>('i' + '2' + 'c');
    std::cout << "FAILED] near line: <" << __LINE__ << ">" << std::endl;
    std::cout << "\ttwoWireRequestFrom_Parameters.invoked == " << !!twoWireRequestFrom_Parameters.invoked << ", EXPECTED: " << true << std::endl;
    std::cout << "\ttwoWireRead_Parameters.invoked == " << !!twoWireRead_Parameters.invoked << ", EXPECTED: " << false << std::endl;
    std::cout << "[";
  }

  return result;
}

int test_notei2c_arduino_receive_will_not_attempt_to_read_when_i2c_port_request_from_returns_value_other_than_buffer_size_plus_note_i2c_request_header_size()
{
  int result;

  // Arrange
  const uint16_t EXPECTED_ADDRESS = 0x17;
  const uint8_t REQUEST_SIZE = 13;
  uint8_t response_buffer[32];
  uint32_t bytes_remaining;

  twoWireBeginTransmission_Parameters.reset();
  twoWireWriteByte_Parameters.reset();
  twoWireEndTransmission_Parameters.reset();
  twoWireRequestFrom_Parameters.reset();
  twoWireRequestFrom_Parameters.result = sizeof(response_buffer);
  twoWireRead_Parameters.reset();
  twoWireRead_Parameters.results = {0, REQUEST_SIZE, 'T', 'e', 's', 't', ' ', 'P', 'a', 's', 's', 'e', 'd', '!', '\0'};
  NoteI2c_Arduino notei2c(Wire);

  // Action
  notei2c.receive(
    EXPECTED_ADDRESS,
    response_buffer,
    REQUEST_SIZE,
    &bytes_remaining
  );

  // Assert
  if (
      twoWireRequestFrom_Parameters.invoked
   && !twoWireRead_Parameters.invoked
  )
  {
    result = 0;
  }
  else
  {
    result = static_cast<int>('i' + '2' + 'c');
    std::cout << "FAILED] near line: <" << __LINE__ << ">" << std::endl;
    std::cout << "\ttwoWireRequestFrom_Parameters.invoked == " << !!twoWireRequestFrom_Parameters.invoked << ", EXPECTED: " << true << std::endl;
    std::cout << "\ttwoWireRead_Parameters.invoked == " << !!twoWireRead_Parameters.invoked << ", EXPECTED: " << false << std::endl;
    std::cout << "[";
  }

  return result;
}

int test_notei2c_arduino_receive_will_not_read_full_response_when_i2c_over_serial_protocol_returns_value_other_than_buffer_size()
{
  int result;

  // Arrange
  const uint16_t EXPECTED_ADDRESS = 0x17;
  const uint8_t REQUEST_SIZE = 13;
  uint8_t response_buffer[32];
  uint32_t bytes_remaining;

  twoWireBeginTransmission_Parameters.reset();
  twoWireWriteByte_Parameters.reset();
  twoWireEndTransmission_Parameters.reset();
  twoWireRequestFrom_Parameters.reset();
  twoWireRequestFrom_Parameters.result = (REQUEST_SIZE + NoteI2c::REQUEST_HEADER_SIZE);
  twoWireRead_Parameters.reset();
  twoWireRead_Parameters.results = {0, sizeof(response_buffer), 'T', 'e', 's', 't', ' ', 'P', 'a', 's', 's', 'e', 'd', '!', '\0'};
  NoteI2c_Arduino notei2c(Wire);

  // Action
  notei2c.receive(
    EXPECTED_ADDRESS,
    response_buffer,
    REQUEST_SIZE,
    &bytes_remaining
  );

  // Assert
  if (
      twoWireRequestFrom_Parameters.invoked
   && twoWireRead_Parameters.invoked == 2
  )
  {
    result = 0;
  }
  else
  {
    result = static_cast<int>('i' + '2' + 'c');
    std::cout << "FAILED] near line: <" << __LINE__ << ">" << std::endl;
    std::cout << "\ttwoWireRequestFrom_Parameters.invoked == " << !!twoWireRequestFrom_Parameters.invoked << ", EXPECTED: " << true << std::endl;
    std::cout << "\ttwoWireRead_Parameters.invoked == " << twoWireRead_Parameters.invoked << ", EXPECTED: " << 2 << std::endl;
    std::cout << "[";
  }

  return result;
}

int test_notei2c_arduino_receive_returns_nullptr_on_success()
{
  int result;

  // Arrange
  const uint16_t EXPECTED_ADDRESS = 0x17;
  const uint8_t REQUEST_SIZE = 13;
  const char * EXPECTED_RESPONSE = "Test Passed!";
  uint8_t response_buffer[32];
  uint32_t bytes_remaining;

  twoWireBeginTransmission_Parameters.reset();
  twoWireWriteByte_Parameters.reset();
  twoWireEndTransmission_Parameters.reset();
  twoWireRequestFrom_Parameters.reset();
  twoWireRequestFrom_Parameters.result = (REQUEST_SIZE + NoteI2c::REQUEST_HEADER_SIZE);
  twoWireRead_Parameters.reset();
  twoWireRead_Parameters.results = {0, REQUEST_SIZE, 'T', 'e', 's', 't', ' ', 'P', 'a', 's', 's', 'e', 'd', '!', '\0'};
  NoteI2c_Arduino notei2c(Wire);

  // Action
  const char * const ACTUAL_RESULT = notei2c.receive(
    EXPECTED_ADDRESS,
    response_buffer,
    REQUEST_SIZE,
    &bytes_remaining
  );

  // Assert
  if (
      !memcmp(response_buffer, EXPECTED_RESPONSE, REQUEST_SIZE)
   && ACTUAL_RESULT == nullptr
  )
  {
    result = 0;
  }
  else
  {
    result = static_cast<int>('i' + '2' + 'c');
    std::cout << "FAILED] near line: <" << __LINE__ << ">" << std::endl;
    std::cout << "\tresponse_buffer == \"" << response_buffer << "\"" << ", EXPECTED: " << EXPECTED_RESPONSE << std::endl;
    std::cout << "\tACTUAL_RESULT == " << ACTUAL_RESULT << ", EXPECTED: 0 (nullptr)" << std::endl;
    std::cout << "[";
  }

  return result;
}

int test_notei2c_arduino_receive_returns_error_message_on_i2c_transmission_failure_1()
{
  int result;

  // Arrange
  const uint16_t EXPECTED_ADDRESS = 0x17;
  const uint8_t REQUEST_SIZE = 13;
  const char * EXPECTED_RESULT = "i2c: data too long to fit in transmit buffer {io}";
  uint8_t response_buffer[32];
  uint32_t bytes_remaining;

  twoWireBeginTransmission_Parameters.reset();
  twoWireWriteByte_Parameters.reset();
  twoWireEndTransmission_Parameters.reset();
  twoWireEndTransmission_Parameters.results = {1,1,1};
  twoWireRequestFrom_Parameters.reset();
  twoWireRequestFrom_Parameters.result = (REQUEST_SIZE + NoteI2c::REQUEST_HEADER_SIZE);
  twoWireRead_Parameters.reset();
  twoWireRead_Parameters.results = {0, REQUEST_SIZE, 'T', 'e', 's', 't', ' ', 'P', 'a', 's', 's', 'e', 'd', '!', '\0'};
  NoteI2c_Arduino notei2c(Wire);

  // Action
  const char * const ACTUAL_RESULT = notei2c.receive(
    EXPECTED_ADDRESS,
    response_buffer,
    REQUEST_SIZE,
    &bytes_remaining
  );

  // Assert
  if (
      ACTUAL_RESULT
   && !memcmp(ACTUAL_RESULT, EXPECTED_RESULT, strlen(EXPECTED_RESULT))
  )
  {
    result = 0;
  }
  else
  {
    result = static_cast<int>('i' + '2' + 'c');
    std::cout << "FAILED] near line: <" << __LINE__ << ">" << std::endl;
    std::cout << "\tACTUAL_RESULT == " << ACTUAL_RESULT << ", EXPECTED: " << EXPECTED_RESULT << std::endl;
    std::cout << "[";
  }

  return result;
}

int test_notei2c_arduino_receive_returns_error_message_on_i2c_transmission_failure_2()
{
  int result;

  // Arrange
  const uint16_t EXPECTED_ADDRESS = 0x17;
  const uint8_t REQUEST_SIZE = 13;
  const char * EXPECTED_RESULT = "i2c: received NACK on transmit of address {io}";
  uint8_t response_buffer[32];
  uint32_t bytes_remaining;

  twoWireBeginTransmission_Parameters.reset();
  twoWireWriteByte_Parameters.reset();
  twoWireEndTransmission_Parameters.reset();
  twoWireEndTransmission_Parameters.results = {2,2,2};
  twoWireRequestFrom_Parameters.reset();
  twoWireRequestFrom_Parameters.result = (REQUEST_SIZE + NoteI2c::REQUEST_HEADER_SIZE);
  twoWireRead_Parameters.reset();
  twoWireRead_Parameters.results = {0, REQUEST_SIZE, 'T', 'e', 's', 't', ' ', 'P', 'a', 's', 's', 'e', 'd', '!', '\0'};
  NoteI2c_Arduino notei2c(Wire);

  // Action
  const char * const ACTUAL_RESULT = notei2c.receive(
    EXPECTED_ADDRESS,
    response_buffer,
    REQUEST_SIZE,
    &bytes_remaining
  );

  // Assert
  if (
      ACTUAL_RESULT
   && !memcmp(ACTUAL_RESULT, EXPECTED_RESULT, strlen(EXPECTED_RESULT))
  )
  {
    result = 0;
  }
  else
  {
    result = static_cast<int>('i' + '2' + 'c');
    std::cout << "FAILED] near line: <" << __LINE__ << ">" << std::endl;
    std::cout << "\tACTUAL_RESULT == " << ACTUAL_RESULT << ", EXPECTED: " << EXPECTED_RESULT << std::endl;
    std::cout << "[";
  }

  return result;
}

int test_notei2c_arduino_receive_returns_error_message_on_i2c_transmission_failure_3()
{
  int result;

  // Arrange
  const uint16_t EXPECTED_ADDRESS = 0x17;
  const uint8_t REQUEST_SIZE = 13;
  const char * EXPECTED_RESULT = "i2c: received NACK on transmit of data {io}";
  uint8_t response_buffer[32];
  uint32_t bytes_remaining;

  twoWireBeginTransmission_Parameters.reset();
  twoWireWriteByte_Parameters.reset();
  twoWireEndTransmission_Parameters.reset();
  twoWireEndTransmission_Parameters.results = {3,3,3};
  twoWireRequestFrom_Parameters.reset();
  twoWireRequestFrom_Parameters.result = (REQUEST_SIZE + NoteI2c::REQUEST_HEADER_SIZE);
  twoWireRead_Parameters.reset();
  twoWireRead_Parameters.results = {0, REQUEST_SIZE, 'T', 'e', 's', 't', ' ', 'P', 'a', 's', 's', 'e', 'd', '!', '\0'};
  NoteI2c_Arduino notei2c(Wire);

  // Action
  const char * const ACTUAL_RESULT = notei2c.receive(
    EXPECTED_ADDRESS,
    response_buffer,
    REQUEST_SIZE,
    &bytes_remaining
  );

  // Assert
  if (
      ACTUAL_RESULT
   && !memcmp(ACTUAL_RESULT, EXPECTED_RESULT, strlen(EXPECTED_RESULT))
  )
  {
    result = 0;
  }
  else
  {
    result = static_cast<int>('i' + '2' + 'c');
    std::cout << "FAILED] near line: <" << __LINE__ << ">" << std::endl;
    std::cout << "\tACTUAL_RESULT == " << ACTUAL_RESULT << ", EXPECTED: " << EXPECTED_RESULT << std::endl;
    std::cout << "[";
  }

  return result;
}

int test_notei2c_arduino_receive_returns_error_message_on_i2c_transmission_failure_4()
{
  int result;

  // Arrange
  const uint16_t EXPECTED_ADDRESS = 0x17;
  const uint8_t REQUEST_SIZE = 13;
  const char * EXPECTED_RESULT = "i2c: unknown error on TwoWire::endTransmission() {io}";
  uint8_t response_buffer[32];
  uint32_t bytes_remaining;

  twoWireBeginTransmission_Parameters.reset();
  twoWireWriteByte_Parameters.reset();
  twoWireEndTransmission_Parameters.reset();
  twoWireEndTransmission_Parameters.results = {4,4,4};
  twoWireRequestFrom_Parameters.reset();
  twoWireRequestFrom_Parameters.result = (REQUEST_SIZE + NoteI2c::REQUEST_HEADER_SIZE);
  twoWireRead_Parameters.reset();
  twoWireRead_Parameters.results = {0, REQUEST_SIZE, 'T', 'e', 's', 't', ' ', 'P', 'a', 's', 's', 'e', 'd', '!', '\0'};
  NoteI2c_Arduino notei2c(Wire);

  // Action
  const char * const ACTUAL_RESULT = notei2c.receive(
    EXPECTED_ADDRESS,
    response_buffer,
    REQUEST_SIZE,
    &bytes_remaining
  );

  // Assert
  if (
      ACTUAL_RESULT
   && !memcmp(ACTUAL_RESULT, EXPECTED_RESULT, strlen(EXPECTED_RESULT))
  )
  {
    result = 0;
  }
  else
  {
    result = static_cast<int>('i' + '2' + 'c');
    std::cout << "FAILED] near line: <" << __LINE__ << ">" << std::endl;
    std::cout << "\tACTUAL_RESULT == " << ACTUAL_RESULT << ", EXPECTED: " << EXPECTED_RESULT << std::endl;
    std::cout << "[";
  }

  return result;
}

int test_notei2c_arduino_receive_returns_error_message_on_i2c_transmission_failure_5()
{
  int result;

  // Arrange
  const uint16_t EXPECTED_ADDRESS = 0x17;
  const uint8_t REQUEST_SIZE = 13;
  const char * EXPECTED_RESULT = "i2c: timeout {io}";
  uint8_t response_buffer[32];
  uint32_t bytes_remaining;

  twoWireBeginTransmission_Parameters.reset();
  twoWireWriteByte_Parameters.reset();
  twoWireEndTransmission_Parameters.reset();
  twoWireEndTransmission_Parameters.results = {5,5,5};
  twoWireRequestFrom_Parameters.reset();
  twoWireRequestFrom_Parameters.result = (REQUEST_SIZE + NoteI2c::REQUEST_HEADER_SIZE);
  twoWireRead_Parameters.reset();
  twoWireRead_Parameters.results = {0, REQUEST_SIZE, 'T', 'e', 's', 't', ' ', 'P', 'a', 's', 's', 'e', 'd', '!', '\0'};
  NoteI2c_Arduino notei2c(Wire);

  // Action
  const char * const ACTUAL_RESULT = notei2c.receive(
    EXPECTED_ADDRESS,
    response_buffer,
    REQUEST_SIZE,
    &bytes_remaining
  );

  // Assert
  if (
      ACTUAL_RESULT
   && !memcmp(ACTUAL_RESULT, EXPECTED_RESULT, strlen(EXPECTED_RESULT))
  )
  {
    result = 0;
  }
  else
  {
    result = static_cast<int>('i' + '2' + 'c');
    std::cout << "FAILED] near line: <" << __LINE__ << ">" << std::endl;
    std::cout << "\tACTUAL_RESULT == " << ACTUAL_RESULT << ", EXPECTED: " << EXPECTED_RESULT << std::endl;
    std::cout << "[";
  }

  return result;
}

int test_notei2c_arduino_receive_returns_error_message_on_unexpected_i2c_transmission_failure()
{
  int result;

  // Arrange
  const uint16_t EXPECTED_ADDRESS = 0x17;
  const uint8_t REQUEST_SIZE = 13;
  const char * EXPECTED_RESULT = "i2c: unknown error encounter during I2C transmission {io}";
  uint8_t response_buffer[32];
  uint32_t bytes_remaining;

  twoWireBeginTransmission_Parameters.reset();
  twoWireWriteByte_Parameters.reset();
  twoWireEndTransmission_Parameters.reset();
  twoWireEndTransmission_Parameters.results = {6,6,6};
  twoWireRequestFrom_Parameters.reset();
  twoWireRequestFrom_Parameters.result = (REQUEST_SIZE + NoteI2c::REQUEST_HEADER_SIZE);
  twoWireRead_Parameters.reset();
  twoWireRead_Parameters.results = {0, REQUEST_SIZE, 'T', 'e', 's', 't', ' ', 'P', 'a', 's', 's', 'e', 'd', '!', '\0'};
  NoteI2c_Arduino notei2c(Wire);

  // Action
  const char * const ACTUAL_RESULT = notei2c.receive(
    EXPECTED_ADDRESS,
    response_buffer,
    REQUEST_SIZE,
    &bytes_remaining
  );

  // Assert
  if (
      ACTUAL_RESULT
   && !memcmp(ACTUAL_RESULT, EXPECTED_RESULT, strlen(EXPECTED_RESULT))
  )
  {
    result = 0;
  }
  else
  {
    result = static_cast<int>('i' + '2' + 'c');
    std::cout << "FAILED] near line: <" << __LINE__ << ">" << std::endl;
    std::cout << "\tACTUAL_RESULT == " << ACTUAL_RESULT << ", EXPECTED: " << EXPECTED_RESULT << std::endl;
    std::cout << "[";
  }

  return result;
}

int test_notei2c_arduino_receive_returns_error_message_on_serial_over_i2c_protocol_failure_to_respond()
{
  int result;

  // Arrange
  const uint16_t EXPECTED_ADDRESS = 0x17;
  const uint8_t REQUEST_SIZE = 13;
  const char * EXPECTED_RESULT = "serial-over-i2c: no response to read request {io}";
  uint8_t response_buffer[32];
  uint32_t bytes_remaining;

  twoWireBeginTransmission_Parameters.reset();
  twoWireWriteByte_Parameters.reset();
  twoWireEndTransmission_Parameters.reset();
  twoWireRequestFrom_Parameters.reset();
  twoWireRead_Parameters.reset();
  twoWireRead_Parameters.results = {0, REQUEST_SIZE, 'T', 'e', 's', 't', ' ', 'P', 'a', 's', 's', 'e', 'd', '!', '\0'};
  NoteI2c_Arduino notei2c(Wire);

  // Action
  const char * const ACTUAL_RESULT = notei2c.receive(
    EXPECTED_ADDRESS,
    response_buffer,
    REQUEST_SIZE,
    &bytes_remaining
  );

  // Assert
  if (
      ACTUAL_RESULT
   && !memcmp(ACTUAL_RESULT, EXPECTED_RESULT, strlen(EXPECTED_RESULT))
  )
  {
    result = 0;
  }
  else
  {
    result = static_cast<int>('i' + '2' + 'c');
    std::cout << "FAILED] near line: <" << __LINE__ << ">" << std::endl;
    std::cout << "\tACTUAL_RESULT == " << ACTUAL_RESULT << ", EXPECTED: " << EXPECTED_RESULT << std::endl;
    std::cout << "[";
  }

  return result;
}

int test_notei2c_arduino_receive_returns_error_message_on_serial_over_i2c_protocol_unexpected_raw_byte_count()
{
  int result;

  // Arrange
  const uint16_t EXPECTED_ADDRESS = 0x17;
  const uint8_t REQUEST_SIZE = 13;
  const char * EXPECTED_RESULT = "serial-over-i2c: unexpected raw byte count {io}";
  uint8_t response_buffer[32];
  uint32_t bytes_remaining;

  twoWireBeginTransmission_Parameters.reset();
  twoWireWriteByte_Parameters.reset();
  twoWireEndTransmission_Parameters.reset();
  twoWireRequestFrom_Parameters.reset();
  twoWireRequestFrom_Parameters.result = sizeof(response_buffer);
  twoWireRead_Parameters.reset();
  twoWireRead_Parameters.results = {0, REQUEST_SIZE, 'T', 'e', 's', 't', ' ', 'P', 'a', 's', 's', 'e', 'd', '!', '\0'};
  NoteI2c_Arduino notei2c(Wire);

  // Action
  const char * const ACTUAL_RESULT = notei2c.receive(
    EXPECTED_ADDRESS,
    response_buffer,
    REQUEST_SIZE,
    &bytes_remaining
  );

  // Assert
  if (
      ACTUAL_RESULT
   && !memcmp(ACTUAL_RESULT, EXPECTED_RESULT, strlen(EXPECTED_RESULT))
  )
  {
    result = 0;
  }
  else
  {
    result = static_cast<int>('i' + '2' + 'c');
    std::cout << "FAILED] near line: <" << __LINE__ << ">" << std::endl;
    std::cout << "\tACTUAL_RESULT == " << ACTUAL_RESULT << ", EXPECTED: " << EXPECTED_RESULT << std::endl;
    std::cout << "[";
  }

  return result;
}

int test_notei2c_arduino_receive_returns_error_message_on_serial_over_i2c_protocol_unexpected_protocol_byte_count()
{
  int result;

  // Arrange
  const uint16_t EXPECTED_ADDRESS = 0x17;
  const uint8_t REQUEST_SIZE = 13;
  const char * EXPECTED_RESULT = "serial-over-i2c: unexpected protocol byte count {io}";
  uint8_t response_buffer[32];
  uint32_t bytes_remaining;

  twoWireBeginTransmission_Parameters.reset();
  twoWireWriteByte_Parameters.reset();
  twoWireEndTransmission_Parameters.reset();
  twoWireRequestFrom_Parameters.reset();
  twoWireRequestFrom_Parameters.result = (REQUEST_SIZE + NoteI2c::REQUEST_HEADER_SIZE);
  twoWireRead_Parameters.reset();
  twoWireRead_Parameters.results = {5, 8, 'T', 'e', 's', 't', ' ', 'P', 'a', 's'};
  NoteI2c_Arduino notei2c(Wire);

  // Action
  const char * const ACTUAL_RESULT = notei2c.receive(
    EXPECTED_ADDRESS,
    response_buffer,
    REQUEST_SIZE,
    &bytes_remaining
  );

  // Assert
  if (
      ACTUAL_RESULT
   && !memcmp(ACTUAL_RESULT, EXPECTED_RESULT, strlen(EXPECTED_RESULT))
  )
  {
    result = 0;
  }
  else
  {
    result = static_cast<int>('i' + '2' + 'c');
    std::cout << "FAILED] near line: <" << __LINE__ << ">" << std::endl;
    std::cout << "\tACTUAL_RESULT == " << ACTUAL_RESULT << ", EXPECTED: " << EXPECTED_RESULT << std::endl;
    std::cout << "[";
  }

  return result;
}

int test_notei2c_arduino_reset_invokes_begin_method_on_constructor_twowire_parameter()
{
  int result;

  // Arrange
  const uint16_t DEVICE_ADDRESS = 0x17;
  NoteI2c_Arduino notei2c(Wire);
  twoWireBegin_Parameters.reset();

  // Action
  notei2c.reset(DEVICE_ADDRESS);

  // Assert
  if (twoWireBegin_Parameters.invoked)
  {
    result = 0;
  }
  else
  {
    result = static_cast<int>('i' + '2' + 'c');
    std::cout << "FAILED] near line: <" << __LINE__ << ">" << std::endl;
    std::cout << "\ttwoWireBegin_Parameters.invoked == " << !!twoWireBegin_Parameters.invoked << ", EXPECTED: " << true << std::endl;
    std::cout << "[";
  }

  return result;
}

int test_notei2c_arduino_reset_returns_true()
{
  int result;

  // Arrange
  const uint16_t DEVICE_ADDRESS = 0x17;
  NoteI2c_Arduino notei2c(Wire);
  twoWireBegin_Parameters.reset();

  // Action
  const bool ACTUAL_RESULT = notei2c.reset(DEVICE_ADDRESS);

  // Assert
  if (ACTUAL_RESULT)
  {
    result = 0;
  }
  else
  {
    result = static_cast<int>('i' + '2' + 'c');
    std::cout << "FAILED] near line: <" << __LINE__ << ">" << std::endl;
    std::cout << "\tACTUAL_RESULT == " << ACTUAL_RESULT << ", EXPECTED: " << true << std::endl;
    std::cout << "[";
  }

  return result;
}

#if not defined(WIRE_HAS_END)

int test_notei2c_arduino_reset_does_not_invoke_end_method_on_constructor_twowire_parameter_ifndef_WIRE_HAS_END()
{
  int result;

  // Arrange
  const uint16_t DEVICE_ADDRESS = 0x17;
  NoteI2c_Arduino notei2c(Wire);
  twoWireBegin_Parameters.reset();
  twoWireEnd_Parameters.reset();

  // Action
  notei2c.reset(DEVICE_ADDRESS);

  // Assert
  if (!twoWireEnd_Parameters.invoked)
  {
    result = 0;
  }
  else
  {
    result = static_cast<int>('i' + '2' + 'c');
    std::cout << "FAILED] near line: <" << __LINE__ << ">" << std::endl;
    std::cout << "\ttwoWireEnd_Parameters.invoked == " << !!twoWireEnd_Parameters.invoked << ", EXPECTED: " << false << std::endl;
    std::cout << "[";
  }

  return result;
}

#else // defined(WIRE_HAS_END)

int test_notei2c_arduino_reset_invokes_end_method_on_constructor_twowire_parameter_ifdef_WIRE_HAS_END()
{
  int result;

  // Arrange
  const uint16_t DEVICE_ADDRESS = 0x17;
  NoteI2c_Arduino notei2c(Wire);
  twoWireBegin_Parameters.reset();
  twoWireEnd_Parameters.reset();

  // Action
  notei2c.reset(DEVICE_ADDRESS);

  // Assert
  if (twoWireEnd_Parameters.invoked)
  {
    result = 0;
  }
  else
  {
    result = static_cast<int>('i' + '2' + 'c');
    std::cout << "FAILED] near line: <" << __LINE__ << ">" << std::endl;
    std::cout << "\ttwoWireEnd_Parameters.invoked == " << !!twoWireEnd_Parameters.invoked << ", EXPECTED: " << true << std::endl;
    std::cout << "[";
  }

  return result;
}

#endif // not defined(WIRE_HAS_END)

int test_notei2c_arduino_transmit_translates_parameters_for_arduino_two_wire()
{
  int result;

  // Arrange
  const uint16_t EXPECTED_ADDRESS = 0x17;
  uint8_t write_buffer[17] = {'H','e','l','l','o',',',' ','N','o','t','e','c','a','r','d','!','\0'};
  const uint8_t REQUEST_SIZE = sizeof(write_buffer);

  twoWireBeginTransmission_Parameters.reset();
  twoWireWriteByte_Parameters.reset();
  twoWireWriteByte_Parameters.result = 1;
  twoWireWriteBuffer_Parameters.reset();
  twoWireWriteBuffer_Parameters.result = REQUEST_SIZE;
  twoWireEndTransmission_Parameters.reset();
  twoWireEndTransmission_Parameters.results = {0};
  NoteI2c_Arduino notei2c(Wire);

  // Action
  notei2c.transmit(
    EXPECTED_ADDRESS,
    write_buffer,
    REQUEST_SIZE
  );

  // Assert
  if (
      twoWireBeginTransmission_Parameters.address == EXPECTED_ADDRESS
   && twoWireWriteByte_Parameters.write_buffer[0] == REQUEST_SIZE
   && !memcmp(twoWireWriteBuffer_Parameters.buffer, write_buffer, REQUEST_SIZE)
   && twoWireEndTransmission_Parameters.invoked
  )
  {
    result = 0;
  }
  else
  {
    result = static_cast<int>('i' + '2' + 'c');
    std::cout << "FAILED] near line: <" << __LINE__ << ">" << std::endl;
    std::cout << "\ttwoWireBeginTransmission_Parameters.address == 0x" << std::hex << static_cast<int>(twoWireBeginTransmission_Parameters.address) << ", EXPECTED: 0x" << EXPECTED_ADDRESS << std::dec << std::endl;
    std::cout << "\ttwoWireWriteByte_Parameters.write_buffer[0] == " << static_cast<int>(twoWireWriteByte_Parameters.write_buffer[0]) << ", EXPECTED: " << static_cast<int>(REQUEST_SIZE) << std::endl;
    std::cout << "\ttwoWireWriteBuffer_Parameters.buffer == \"" << twoWireWriteBuffer_Parameters.buffer << "\", EXPECTED: \"" << write_buffer << "\"" << std::endl;
    std::cout << "\ttwoWireEndTransmission_Parameters.invoked == " << !!twoWireEndTransmission_Parameters.invoked << ", EXPECTED: " << true << std::endl;
    std::cout << "[";
  }

  return result;
}

int test_notei2c_arduino_transmit_returns_nullptr_on_success()
{
  int result;

  // Arrange
  const uint16_t EXPECTED_ADDRESS = 0x17;
  uint8_t write_buffer[17] = {'H','e','l','l','o',',',' ','N','o','t','e','c','a','r','d','!','\0'};
  const uint8_t REQUEST_SIZE = sizeof(write_buffer);

  twoWireBeginTransmission_Parameters.reset();
  twoWireWriteByte_Parameters.reset();
  twoWireWriteByte_Parameters.result = 1;
  twoWireWriteBuffer_Parameters.reset();
  twoWireWriteBuffer_Parameters.result = REQUEST_SIZE;
  twoWireEndTransmission_Parameters.reset();
  twoWireEndTransmission_Parameters.results = {0};
  NoteI2c_Arduino notei2c(Wire);

  // Action
  const char * const ACTUAL_RESULT = notei2c.transmit(
    EXPECTED_ADDRESS,
    write_buffer,
    REQUEST_SIZE
  );

  // Assert
  if ( ACTUAL_RESULT == nullptr )
  {
    result = 0;
  }
  else
  {
    result = static_cast<int>('i' + '2' + 'c');
    std::cout << "FAILED] near line: <" << __LINE__ << ">" << std::endl;
    std::cout << "\tACTUAL_RESULT == " << ACTUAL_RESULT << ", EXPECTED: 0 (nullptr)" << std::endl;
    std::cout << "[";
  }

  return result;
}

int test_notei2c_arduino_transmit_returns_error_message_on_i2c_transmission_failure1()
{
  int result;

  // Arrange
  const uint16_t EXPECTED_ADDRESS = 0x17;
  uint8_t write_buffer[17] = {'H','e','l','l','o',',',' ','N','o','t','e','c','a','r','d','!','\0'};
  const uint8_t REQUEST_SIZE = sizeof(write_buffer);
  const char * EXPECTED_RESULT = "i2c: data too long to fit in transmit buffer {io}";

  twoWireBeginTransmission_Parameters.reset();
  twoWireWriteByte_Parameters.reset();
  twoWireWriteBuffer_Parameters.reset();
  twoWireEndTransmission_Parameters.reset();
  twoWireEndTransmission_Parameters.results = {1};
  NoteI2c_Arduino notei2c(Wire);

  // Action
  const char * const ACTUAL_RESULT = notei2c.transmit(
    EXPECTED_ADDRESS,
    write_buffer,
    REQUEST_SIZE
  );

  // Assert
  if (
      ACTUAL_RESULT
   && !memcmp(ACTUAL_RESULT, EXPECTED_RESULT, strlen(EXPECTED_RESULT))
  )
  {
    result = 0;
  }
  else
  {
    result = static_cast<int>('i' + '2' + 'c');
    std::cout << "FAILED] near line: <" << __LINE__ << ">" << std::endl;
    std::cout << "\tACTUAL_RESULT == " << ACTUAL_RESULT << ", EXPECTED: " << EXPECTED_RESULT << std::endl;
    std::cout << "[";
  }

  return result;
}

int test_notei2c_arduino_transmit_returns_error_message_on_i2c_transmission_failure2()
{
  int result;

  // Arrange
  const uint16_t EXPECTED_ADDRESS = 0x17;
  uint8_t write_buffer[17] = {'H','e','l','l','o',',',' ','N','o','t','e','c','a','r','d','!','\0'};
  const uint8_t REQUEST_SIZE = sizeof(write_buffer);
  const char * EXPECTED_RESULT = "i2c: received NACK on transmit of address {io}";

  twoWireBeginTransmission_Parameters.reset();
  twoWireWriteByte_Parameters.reset();
  twoWireWriteBuffer_Parameters.reset();
  twoWireEndTransmission_Parameters.reset();
  twoWireEndTransmission_Parameters.results = {2};
  NoteI2c_Arduino notei2c(Wire);

  // Action
  const char * const ACTUAL_RESULT = notei2c.transmit(
    EXPECTED_ADDRESS,
    write_buffer,
    REQUEST_SIZE
  );

  // Assert
  if (
      ACTUAL_RESULT
   && !memcmp(ACTUAL_RESULT, EXPECTED_RESULT, strlen(EXPECTED_RESULT))
  )
  {
    result = 0;
  }
  else
  {
    result = static_cast<int>('i' + '2' + 'c');
    std::cout << "FAILED] near line: <" << __LINE__ << ">" << std::endl;
    std::cout << "\tACTUAL_RESULT == " << ACTUAL_RESULT << ", EXPECTED: " << EXPECTED_RESULT << std::endl;
    std::cout << "[";
  }

  return result;
}

int test_notei2c_arduino_transmit_returns_error_message_on_i2c_transmission_failure3()
{
  int result;

  // Arrange
  const uint16_t EXPECTED_ADDRESS = 0x17;
  uint8_t write_buffer[17] = {'H','e','l','l','o',',',' ','N','o','t','e','c','a','r','d','!','\0'};
  const uint8_t REQUEST_SIZE = sizeof(write_buffer);
  const char * EXPECTED_RESULT = "i2c: received NACK on transmit of data {io}";

  twoWireBeginTransmission_Parameters.reset();
  twoWireWriteByte_Parameters.reset();
  twoWireWriteBuffer_Parameters.reset();
  twoWireEndTransmission_Parameters.reset();
  twoWireEndTransmission_Parameters.results = {3};
  NoteI2c_Arduino notei2c(Wire);

  // Action
  const char * const ACTUAL_RESULT = notei2c.transmit(
    EXPECTED_ADDRESS,
    write_buffer,
    REQUEST_SIZE
  );

  // Assert
  if (
      ACTUAL_RESULT
   && !memcmp(ACTUAL_RESULT, EXPECTED_RESULT, strlen(EXPECTED_RESULT))
  )
  {
    result = 0;
  }
  else
  {
    result = static_cast<int>('i' + '2' + 'c');
    std::cout << "FAILED] near line: <" << __LINE__ << ">" << std::endl;
    std::cout << "\tACTUAL_RESULT == " << ACTUAL_RESULT << ", EXPECTED: " << EXPECTED_RESULT << std::endl;
    std::cout << "[";
  }

  return result;
}

int test_notei2c_arduino_transmit_returns_error_message_on_i2c_transmission_failure4()
{
  int result;

  // Arrange
  const uint16_t EXPECTED_ADDRESS = 0x17;
  uint8_t write_buffer[17] = {'H','e','l','l','o',',',' ','N','o','t','e','c','a','r','d','!','\0'};
  const uint8_t REQUEST_SIZE = sizeof(write_buffer);
  const char * EXPECTED_RESULT = "i2c: unknown error on TwoWire::endTransmission() {io}";

  twoWireBeginTransmission_Parameters.reset();
  twoWireWriteByte_Parameters.reset();
  twoWireWriteBuffer_Parameters.reset();
  twoWireEndTransmission_Parameters.reset();
  twoWireEndTransmission_Parameters.results = {4};
  NoteI2c_Arduino notei2c(Wire);

  // Action
  const char * const ACTUAL_RESULT = notei2c.transmit(
    EXPECTED_ADDRESS,
    write_buffer,
    REQUEST_SIZE
  );

  // Assert
  if (
      ACTUAL_RESULT
   && !memcmp(ACTUAL_RESULT, EXPECTED_RESULT, strlen(EXPECTED_RESULT))
  )
  {
    result = 0;
  }
  else
  {
    result = static_cast<int>('i' + '2' + 'c');
    std::cout << "FAILED] near line: <" << __LINE__ << ">" << std::endl;
    std::cout << "\tACTUAL_RESULT == " << ACTUAL_RESULT << ", EXPECTED: " << EXPECTED_RESULT << std::endl;
    std::cout << "[";
  }

  return result;
}

int test_notei2c_arduino_transmit_returns_error_message_on_i2c_transmission_failure5()
{
  int result;

  // Arrange
  const uint16_t EXPECTED_ADDRESS = 0x17;
  uint8_t write_buffer[17] = {'H','e','l','l','o',',',' ','N','o','t','e','c','a','r','d','!','\0'};
  const uint8_t REQUEST_SIZE = sizeof(write_buffer);
  const char * EXPECTED_RESULT = "i2c: timeout {io}";

  twoWireBeginTransmission_Parameters.reset();
  twoWireWriteByte_Parameters.reset();
  twoWireWriteBuffer_Parameters.reset();
  twoWireEndTransmission_Parameters.reset();
  twoWireEndTransmission_Parameters.results = {5};
  NoteI2c_Arduino notei2c(Wire);

  // Action
  const char * const ACTUAL_RESULT = notei2c.transmit(
    EXPECTED_ADDRESS,
    write_buffer,
    REQUEST_SIZE
  );

  // Assert
  if (
      ACTUAL_RESULT
   && !memcmp(ACTUAL_RESULT, EXPECTED_RESULT, strlen(EXPECTED_RESULT))
  )
  {
    result = 0;
  }
  else
  {
    result = static_cast<int>('i' + '2' + 'c');
    std::cout << "FAILED] near line: <" << __LINE__ << ">" << std::endl;
    std::cout << "\tACTUAL_RESULT == " << ACTUAL_RESULT << ", EXPECTED: " << EXPECTED_RESULT << std::endl;
    std::cout << "[";
  }

  return result;
}

int test_notei2c_arduino_transmit_returns_error_message_on_unexpected_i2c_transmission_failure()
{
  int result;

  // Arrange
  const uint16_t EXPECTED_ADDRESS = 0x17;
  uint8_t write_buffer[17] = {'H','e','l','l','o',',',' ','N','o','t','e','c','a','r','d','!','\0'};
  const uint8_t REQUEST_SIZE = sizeof(write_buffer);
  const char * EXPECTED_RESULT = "i2c: unknown error encounter during I2C transmission {io}";

  twoWireBeginTransmission_Parameters.reset();
  twoWireWriteByte_Parameters.reset();
  twoWireWriteBuffer_Parameters.reset();
  twoWireEndTransmission_Parameters.reset();
  twoWireEndTransmission_Parameters.results = {6};
  NoteI2c_Arduino notei2c(Wire);

  // Action
  const char * const ACTUAL_RESULT = notei2c.transmit(
    EXPECTED_ADDRESS,
    write_buffer,
    REQUEST_SIZE
  );

  // Assert
  if (
      ACTUAL_RESULT
   && !memcmp(ACTUAL_RESULT, EXPECTED_RESULT, strlen(EXPECTED_RESULT))
  )
  {
    result = 0;
  }
  else
  {
    result = static_cast<int>('i' + '2' + 'c');
    std::cout << "FAILED] near line: <" << __LINE__ << ">" << std::endl;
    std::cout << "\tACTUAL_RESULT == " << ACTUAL_RESULT << ", EXPECTED: " << EXPECTED_RESULT << std::endl;
    std::cout << "[";
  }

  return result;
}

int main(void)
{
  TestFunction tests[] = {
      {test_notei2c_arduino_constructor_invokes_twowire_parameter_begin_method, "test_notei2c_arduino_constructor_invokes_twowire_parameter_begin_method"},
      {test_notei2c_arduino_receive_requests_response_data_from_notecard, "test_notei2c_arduino_receive_requests_response_data_from_notecard"},
      {test_notei2c_arduino_receive_will_retry_transmission_on_i2c_failure, "test_notei2c_arduino_receive_will_retry_transmission_on_i2c_failure"},
      {test_notei2c_arduino_receive_will_not_retry_transmission_on_i2c_success, "test_notei2c_arduino_receive_will_not_retry_transmission_on_i2c_success"},
      {test_notei2c_arduino_receive_will_only_retry_i2c_transmission_thrice, "test_notei2c_arduino_receive_will_only_retry_i2c_transmission_thrice"},
      {test_notei2c_arduino_receive_reads_response_data_from_notecard, "test_notei2c_arduino_receive_reads_response_data_from_notecard"},
      {test_notei2c_arduino_receive_updates_available_parameter_with_remaining_bytes, "test_notei2c_arduino_receive_updates_available_parameter_with_remaining_bytes"},
      {test_notei2c_arduino_receive_does_not_request_or_read_i2c_when_trasmission_error_occurs, "test_notei2c_arduino_receive_does_not_request_or_read_i2c_when_trasmission_error_occurs"},
      {test_notei2c_arduino_receive_will_not_attempt_to_read_when_i2c_port_request_from_returns_zero, "test_notei2c_arduino_receive_will_not_attempt_to_read_when_i2c_port_request_from_returns_zero"},
      {test_notei2c_arduino_receive_will_not_attempt_to_read_when_i2c_port_request_from_returns_value_other_than_buffer_size_plus_note_i2c_request_header_size, "test_notei2c_arduino_receive_will_not_attempt_to_read_when_i2c_port_request_from_returns_value_other_than_buffer_size_plus_note_i2c_request_header_size"},
      {test_notei2c_arduino_receive_will_not_read_full_response_when_i2c_over_serial_protocol_returns_value_other_than_buffer_size, "test_notei2c_arduino_receive_will_not_read_full_response_when_i2c_over_serial_protocol_returns_value_other_than_buffer_size"},
      {test_notei2c_arduino_receive_returns_nullptr_on_success, "test_notei2c_arduino_receive_returns_nullptr_on_success"},
      {test_notei2c_arduino_receive_returns_error_message_on_i2c_transmission_failure_1, "test_notei2c_arduino_receive_returns_error_message_on_i2c_transmission_failure_1"},
      {test_notei2c_arduino_receive_returns_error_message_on_i2c_transmission_failure_2, "test_notei2c_arduino_receive_returns_error_message_on_i2c_transmission_failure_2"},
      {test_notei2c_arduino_receive_returns_error_message_on_i2c_transmission_failure_3, "test_notei2c_arduino_receive_returns_error_message_on_i2c_transmission_failure_3"},
      {test_notei2c_arduino_receive_returns_error_message_on_i2c_transmission_failure_4, "test_notei2c_arduino_receive_returns_error_message_on_i2c_transmission_failure_4"},
      {test_notei2c_arduino_receive_returns_error_message_on_i2c_transmission_failure_5, "test_notei2c_arduino_receive_returns_error_message_on_i2c_transmission_failure_5"},
      {test_notei2c_arduino_receive_returns_error_message_on_unexpected_i2c_transmission_failure, "test_notei2c_arduino_receive_returns_error_message_on_unexpected_i2c_transmission_failure"},
      {test_notei2c_arduino_receive_returns_error_message_on_serial_over_i2c_protocol_failure_to_respond, "test_notei2c_arduino_receive_returns_error_message_on_serial_over_i2c_protocol_failure_to_respond"},
      {test_notei2c_arduino_receive_returns_error_message_on_serial_over_i2c_protocol_unexpected_raw_byte_count, "test_notei2c_arduino_receive_returns_error_message_on_serial_over_i2c_protocol_unexpected_raw_byte_count"},
      {test_notei2c_arduino_receive_returns_error_message_on_serial_over_i2c_protocol_unexpected_protocol_byte_count, "test_notei2c_arduino_receive_returns_error_message_on_serial_over_i2c_protocol_unexpected_protocol_byte_count"},
      {test_notei2c_arduino_reset_invokes_begin_method_on_constructor_twowire_parameter, "test_notei2c_arduino_reset_invokes_begin_method_on_constructor_twowire_parameter"},
      {test_notei2c_arduino_reset_returns_true, "test_notei2c_arduino_reset_returns_true"},
#if not defined(WIRE_HAS_END)
      {test_notei2c_arduino_reset_does_not_invoke_end_method_on_constructor_twowire_parameter_ifndef_WIRE_HAS_END, "test_notei2c_arduino_reset_does_not_invoke_end_method_on_constructor_twowire_parameter_ifndef_WIRE_HAS_END"},
#else // defined(WIRE_HAS_END)
      {test_notei2c_arduino_reset_invokes_end_method_on_constructor_twowire_parameter_ifdef_WIRE_HAS_END, "test_notei2c_arduino_reset_invokes_end_method_on_constructor_twowire_parameter_ifdef_WIRE_HAS_END"},
#endif // not defined(WIRE_HAS_END)
      {test_notei2c_arduino_transmit_translates_parameters_for_arduino_two_wire, "test_notei2c_arduino_transmit_translates_parameters_for_arduino_two_wire"},
      {test_notei2c_arduino_transmit_returns_nullptr_on_success, "test_notei2c_arduino_transmit_returns_nullptr_on_success"},
      {test_notei2c_arduino_transmit_returns_error_message_on_i2c_transmission_failure1, "test_notei2c_arduino_transmit_returns_error_message_on_i2c_transmission_failure1"},
      {test_notei2c_arduino_transmit_returns_error_message_on_i2c_transmission_failure2, "test_notei2c_arduino_transmit_returns_error_message_on_i2c_transmission_failure2"},
      {test_notei2c_arduino_transmit_returns_error_message_on_i2c_transmission_failure3, "test_notei2c_arduino_transmit_returns_error_message_on_i2c_transmission_failure3"},
      {test_notei2c_arduino_transmit_returns_error_message_on_i2c_transmission_failure4, "test_notei2c_arduino_transmit_returns_error_message_on_i2c_transmission_failure4"},
      {test_notei2c_arduino_transmit_returns_error_message_on_i2c_transmission_failure5, "test_notei2c_arduino_transmit_returns_error_message_on_i2c_transmission_failure5"},
      {test_notei2c_arduino_transmit_returns_error_message_on_unexpected_i2c_transmission_failure, "test_notei2c_arduino_transmit_returns_error_message_on_unexpected_i2c_transmission_failure"},
  };

  return TestFunction::runTests(tests, (sizeof(tests) / sizeof(TestFunction)));
}
