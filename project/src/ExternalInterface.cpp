#ifndef STATIC_LINK
#define IMPLEMENT_API
#endif

#if defined(HX_WINDOWS) || defined(HX_MACOS) || defined(HX_LINUX)
#define NEKO_COMPATIBLE
#endif


#include <hx/CFFI.h>
#include "RtMidi.h"

value rtmidi_in_create() {
  RtMidiIn *midiin = new RtMidiIn();
  return alloc_float((intptr_t)midiin);
}

value rtmidi_in_destroy(value obj) {
  RtMidiIn *midiin = (RtMidiIn *)(intptr_t)val_float(obj);
  delete midiin;
  return alloc_null();
}

value rtmidi_in_getportcount(value obj) {
  RtMidiIn *midiin = (RtMidiIn *)(intptr_t)val_float(obj);
  return alloc_int(midiin->getPortCount());
}

value rtmidi_in_openport(value obj, value port) {
  RtMidiIn *midiin = (RtMidiIn *)(intptr_t)val_float(obj);
  midiin->openPort(val_int(port));
  return alloc_null();
}

value rtmidi_in_ignoretypes(value obj, value sysex, value time, value sense) {
  RtMidiIn *midiin = (RtMidiIn *)(intptr_t)val_float(obj);
  midiin->ignoreTypes(val_bool(sysex), val_bool(time), val_bool(sense));
  return alloc_null();
}

value rtmidi_in_getmessage(value obj) {
  RtMidiIn *midiin = (RtMidiIn *)(intptr_t)val_float(obj);
  std::vector<unsigned char> message;
  double stamp = midiin->getMessage(&message);
  // ignore stamp for now
  value ret = alloc_array(message.size());
  for (int i = 0; i < message.size(); ++i) {
    val_array_set_i(ret, i, alloc_int(message[i]));
  }
  return ret;
}

DEFINE_PRIM(rtmidi_in_create, 0);
DEFINE_PRIM(rtmidi_in_destroy, 1);
DEFINE_PRIM(rtmidi_in_getportcount, 1);
DEFINE_PRIM(rtmidi_in_openport, 2);
DEFINE_PRIM(rtmidi_in_ignoretypes, 4);
DEFINE_PRIM(rtmidi_in_getmessage, 1);


extern "C" void rtmidi_main () {

  val_int(0); // Fix Neko init

}
DEFINE_ENTRY_POINT (rtmidi_main);



extern "C" int rtmidi_register_prims () { return 0; }
