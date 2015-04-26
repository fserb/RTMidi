#ifndef STATIC_LINK
#define IMPLEMENT_API
#endif

#if defined(HX_WINDOWS) || defined(HX_MACOS) || defined(HX_LINUX)
#define NEKO_COMPATIBLE
#endif


#include <hx/CFFI.h>
#include "RtMidi.h"

AutoGCRoot* callback_root = NULL;

value rtmidi_in_create() {
  RtMidiIn *midiin = new RtMidiIn();
  return alloc_float((intptr_t)midiin);
}

value rtmidi_in_destroy(value obj) {
  RtMidiIn *midiin = (RtMidiIn *)(intptr_t)val_float(obj);
  delete midiin;
  if (callback_root) {
    delete callback_root;
    callback_root = NULL;
  }
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

value rtmidi_in_getportname(value obj, value port) {
  RtMidiIn *midiin = (RtMidiIn *)(intptr_t)val_float(obj);
  return alloc_string(midiin->getPortName(val_int(port)).c_str());
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

void _rtmidi_in_callback(double deltatime,
                         std::vector<unsigned char> *message,
                         void *userData) {
  int top = 0;
  gc_set_top_of_stack(&top, true);

  value ret = alloc_array(message->size());
  for (int i = 0; i < message->size(); ++i) {
    val_array_set_i(ret, i, alloc_int((*message)[i]));
  }
  val_call1(callback_root->get(), ret);
  gc_set_top_of_stack(0,true);
}

value rtmidi_in_setcallback(value obj, value func) {
  RtMidiIn *midiin = (RtMidiIn *)(intptr_t)val_float(obj);
  callback_root = new AutoGCRoot(func);
  midiin->setCallback(&_rtmidi_in_callback);
  return alloc_null();
}

value rtmidi_in_cancelcallback(value obj) {
  RtMidiIn *midiin = (RtMidiIn *)(intptr_t)val_float(obj);
  midiin->cancelCallback();
  if (callback_root) {
    delete callback_root;
    callback_root = NULL;
  }
  return alloc_null();
}

value rtmidi_out_create() {
  RtMidiOut *midiout = new RtMidiOut();
  return alloc_float((intptr_t)midiout);
}

value rtmidi_out_destroy(value obj) {
  RtMidiOut *midiout = (RtMidiOut *)(intptr_t)val_float(obj);
  delete midiout;
  return alloc_null();
}

value rtmidi_out_getportcount(value obj) {
  RtMidiOut *midiout = (RtMidiOut *)(intptr_t)val_float(obj);
  return alloc_int(midiout->getPortCount());
}

value rtmidi_out_openport(value obj, value port) {
  RtMidiOut *midiout = (RtMidiOut *)(intptr_t)val_float(obj);
  midiout->openPort(val_int(port));
  return alloc_null();
}

value rtmidi_out_getportname(value obj, value port) {
  RtMidiOut *midiout = (RtMidiOut *)(intptr_t)val_float(obj);
  return alloc_string(midiout->getPortName(val_int(port)).c_str());
}

value rtmidi_out_sendmessage(value obj, value msg) {
  RtMidiOut *midiout = (RtMidiOut *)(intptr_t)val_float(obj);

  std::vector<unsigned char> message;

  int size = val_array_size(msg);
  for (int i = 0; i < size; ++i) {
    message.push_back(val_int(val_array_i(msg, i)));
  }

  midiout->sendMessage(&message);
  return alloc_null();
}

DEFINE_PRIM(rtmidi_in_create, 0);
DEFINE_PRIM(rtmidi_in_destroy, 1);
DEFINE_PRIM(rtmidi_in_getportcount, 1);
DEFINE_PRIM(rtmidi_in_openport, 2);
DEFINE_PRIM(rtmidi_in_getportname, 2);
DEFINE_PRIM(rtmidi_in_ignoretypes, 4);
DEFINE_PRIM(rtmidi_in_getmessage, 1);
DEFINE_PRIM(rtmidi_in_setcallback, 2);
DEFINE_PRIM(rtmidi_in_cancelcallback, 1);
DEFINE_PRIM(rtmidi_out_create, 0);
DEFINE_PRIM(rtmidi_out_destroy, 1);
DEFINE_PRIM(rtmidi_out_getportcount, 1);
DEFINE_PRIM(rtmidi_out_openport, 2);
DEFINE_PRIM(rtmidi_out_getportname, 2);
DEFINE_PRIM(rtmidi_out_sendmessage, 2);

extern "C" void rtmidi_main () {

  val_int(0); // Fix Neko init

}
DEFINE_ENTRY_POINT (rtmidi_main);



extern "C" int rtmidi_register_prims () { return 0; }
