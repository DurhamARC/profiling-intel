#include <VT.h>
#include <cmath>
#include <iostream>
#include <map>
#include <mpi.h>
#include <string>

namespace {
  std::map<std::string, const int> itac_handles;
}

void trace_in(const std::string &trace) {
  if (itac_handles.count(trace) == 0) {
    int new_handle;
    VT_funcdef(trace.c_str(), VT_NOCLASS, &new_handle);
    itac_handles.insert({trace, new_handle});
  }

  VT_begin(itac_handles[trace]);
}

void trace_out(const std::string &trace) {
  VT_end(itac_handles[trace]);
}

void do_fancy_physics() {
  float aggregator = 0;
  for (int i = 0; i < 100'000'000; ++i) {
    aggregator += sin(i);
  }
  std::cout << "Result: " << aggregator << std::endl;
}

int main(int argc, char *argv[]) {
  const std::array<std::string, 3> phases{"alpha", "beta", "gamma"};
  for (const auto &phase : phases) {
    trace_in(phase);
    do_fancy_physics();
    trace_out(phase);
  }
  return 0;
}


