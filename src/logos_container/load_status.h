#ifndef LOAD_STATUS_H
#define LOAD_STATUS_H

#include <string>

namespace LogosCore {

// ── The load-status line ─────────────────────────────────────────────────────
//
// launch() returning true means SPAWNED: the OS made a process. Whether the
// module's plugin actually loaded behind it is a fact only the child knows, and
// it reports it by writing exactly one of these to its stdout:
//
//     @logos-load-status ok
//     @logos-load-status failed <reason>
//
// stdout rather than a fourth inherited pipe because the container already
// reads it line by line on every platform — no new OS handle, no new flag, and
// compatible in both directions: an old host just has an Unknown verdict, and
// an old container just logs a line.
constexpr const char* kLoadStatusPrefix = "@logos-load-status";
constexpr const char* kLoadStatusOk     = "ok";
constexpr const char* kLoadStatusFailed = "failed";

enum class LoadVerdict {
    Loaded,   // the child reported that its plugin loaded
    Failed,   // the child reported a failure, or died before reporting anything
    Unknown,  // alive and silent at the deadline: nothing was learned either way
};

struct LoadOutcome {
    LoadVerdict verdict = LoadVerdict::Unknown;
    // Set for Failed, and phrased to be readable on its own: it is what the
    // daemon logs and what reaches a modules_state consumer as the reason an
    // `error` state was entered.
    std::string reason;
};

} // namespace LogosCore

#endif // LOAD_STATUS_H
