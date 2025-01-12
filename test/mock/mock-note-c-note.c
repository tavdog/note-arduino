#include "mock-parameters.hpp"

NoteDebug_Parameters noteDebug_Parameters;
NoteDebugSyncStatus_Parameters noteDebugSyncStatus_Parameters;
NoteDeleteResponse_Parameters noteDeleteResponse_Parameters;
NoteNewCommand_Parameters noteNewCommand_Parameters;
NoteNewRequest_Parameters noteNewRequest_Parameters;
NoteRequest_Parameters noteRequest_Parameters;
NoteRequestResponse_Parameters noteRequestResponse_Parameters;
NoteResponseError_Parameters noteResponseError_Parameters;
NoteSetFnDebugOutput_Parameters noteSetFnDebugOutput_Parameters;
NoteSetFnDefault_Parameters noteSetFnDefault_Parameters;
NoteSetFnI2C_Parameters noteSetFnI2C_Parameters;
NoteSetFnSerial_Parameters noteSetFnSerial_Parameters;
NoteSetUserAgent_Parameters noteSetUserAgent_Parameters;

void
MockNoteDeleteResponse (
    J * response_
) {
    // Record invocation(s)
    ++noteDeleteResponse_Parameters.invoked;

    // Stash parameter(s)
    noteDeleteResponse_Parameters.response = response_;
}

bool
MockNoteResponseError (
    J * rsp_
) {
    // Record invocation(s)
    ++noteResponseError_Parameters.invoked;

    // Stash parameter(s)
    noteResponseError_Parameters.rsp = rsp_;

    // Return user-supplied result
    return noteResponseError_Parameters.result;
}

void
NoteDebug(
    const char * message_
) {
    // Record invocation(s)
    ++noteDebug_Parameters.invoked;

    // Stash parameter(s)
    noteDebug_Parameters.message = message_;
    if (message_) {
        noteDebug_Parameters.message_cache = message_;
    }
}

bool
NoteDebugSyncStatus(
    int poll_frequency_ms_,
    int max_level_
) {
    // Record invocation(s)
    ++noteDebugSyncStatus_Parameters.invoked;

    // Stash parameter(s)
    noteDebugSyncStatus_Parameters.pollFrequencyMs = poll_frequency_ms_;
    noteDebugSyncStatus_Parameters.maxLevel = max_level_;

    // Return user-supplied result
    return noteDebugSyncStatus_Parameters.result;
}

J *
NoteNewCommand(
    const char * request_
) {
    // Record invocation(s)
    ++noteNewCommand_Parameters.invoked;

    // Stash parameter(s)
    noteNewCommand_Parameters.request = request_;
    if (request_) {
        noteNewCommand_Parameters.request_cache = request_;
    }

    // Return user-supplied result
    return noteNewCommand_Parameters.result;
}

J *
NoteNewRequest(
    const char * request_
) {
    // Record invocation(s)
    ++noteNewRequest_Parameters.invoked;

    // Stash parameter(s)
    noteNewRequest_Parameters.request = request_;
    if (request_) {
        noteNewRequest_Parameters.request_cache = request_;
    }

    // Return user-supplied result
    return noteNewRequest_Parameters.result;
}

bool
NoteRequest(
    J * req_
) {
    // Record invocation(s)
    ++noteRequest_Parameters.invoked;

    // Stash parameter(s)
    noteRequest_Parameters.req = req_;

    // Return user-supplied result
    return noteRequest_Parameters.result;
}

J *
NoteRequestResponse(
    J * req_
) {
    // Record invocation(s)
    ++noteRequestResponse_Parameters.invoked;

    // Stash parameter(s)
    noteRequestResponse_Parameters.req = req_;

    // Return user-supplied result
    return noteRequestResponse_Parameters.result;
}

void
NoteSetFnDebugOutput(
    debugOutputFn fn_
) {
    // Record invocation(s)
    ++noteSetFnDebugOutput_Parameters.invoked;

    // Stash parameter(s)
    noteSetFnDebugOutput_Parameters.fn = fn_;
}

void
NoteSetFnDefault(
    mallocFn malloc_fn_,
    freeFn free_fn_,
    delayMsFn delay_fn_,
    getMsFn millis_fn_
) {
    // Record invocation(s)
    ++noteSetFnDefault_Parameters.invoked;

    // Stash parameter(s)
    noteSetFnDefault_Parameters.mallocfn = malloc_fn_;
    noteSetFnDefault_Parameters.freefn = free_fn_;
    noteSetFnDefault_Parameters.delayfn = delay_fn_;
    noteSetFnDefault_Parameters.millisfn = millis_fn_;
}

void
NoteSetFnI2C(
    uint32_t i2c_addr_,
    uint32_t i2c_max_,
    i2cResetFn reset_fn_,
    i2cTransmitFn transmit_fn_,
    i2cReceiveFn receive_fn_
) {
    // Record invocation(s)
    ++noteSetFnI2C_Parameters.invoked;

    // Stash parameter(s)
    noteSetFnI2C_Parameters.i2caddr = i2c_addr_;
    noteSetFnI2C_Parameters.i2cmax = i2c_max_;
    noteSetFnI2C_Parameters.resetfn = reset_fn_;
    noteSetFnI2C_Parameters.transmitfn = transmit_fn_;
    noteSetFnI2C_Parameters.receivefn = receive_fn_;
}

void
NoteSetFnSerial(
    serialResetFn reset_fn_,
    serialTransmitFn write_fn_,
    serialAvailableFn avail_fn_,
    serialReceiveFn read_fn_
) {
    // Record invocation(s)
    ++noteSetFnSerial_Parameters.invoked;

    // Stash parameter(s)
    noteSetFnSerial_Parameters.resetfn = reset_fn_;
    noteSetFnSerial_Parameters.writefn = write_fn_;
    noteSetFnSerial_Parameters.availfn = avail_fn_;
    noteSetFnSerial_Parameters.readfn = read_fn_;
}

void
NoteSetUserAgent(
    char * agent_
) {
    // Record invocation(s)
    ++noteSetUserAgent_Parameters.invoked;

    // Stash parameter(s)
    noteSetUserAgent_Parameters.agent = agent_;
    if (agent_) {
        noteSetUserAgent_Parameters.agent_cache = agent_;
    }
}
