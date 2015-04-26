// clang++ -o pooling -I ../project/lib/rtmidi-2.1.0/ -L ../project/lib/rtmidi-2.1.0/ -lrtmidi pooling.cc

#include <iostream>
#include <cstdlib>
#include <signal.h>
#include "RtMidi.h"

bool done;
static void finish(int ignore) {
  done = true;
}

int main() {
  RtMidiIn *midiin = new RtMidiIn();
  std::vector<unsigned char> message;
  int nBytes, i;
  double stamp;
  // Check available ports.
  unsigned int nPorts = midiin->getPortCount();
  if (nPorts == 0) {
    std::cout << "No ports available!\n";
    goto cleanup;
  }
  midiin->openPort(0);
  // Don't ignore sysex, timing, or active sensing messages.
  midiin->ignoreTypes(false, false, false);
  // Install an interrupt handler function.
  done = false;
  (void) signal(SIGINT, finish);

  // Periodically check input queue.
  std::cout << "Reading MIDI from port ... quit with Ctrl-C.\n";

  while (!done) {
    stamp = midiin->getMessage(&message);
    nBytes = message.size();
    for (i=0; i<nBytes; i++) {
      std::cout << "Byte " << i << " = " << (int)message[i] << ", ";
    }
    if (nBytes > 0) {
      std::cout << "stamp = " << stamp << std::endl;
    }
  }

  // Clean up
 cleanup:
  delete midiin;
  return 0;
}
