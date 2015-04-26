package rtmidi;

#if cpp
import cpp.Lib;
#elseif neko
import neko.Lib;
#end

class RTMidiOut {
  private var obj: Float;
  public function new() {
    obj = rtmidi_out_create();
  }

  public function close() {
    rtmidi_out_destroy(obj);
    obj = 0;
  }

  public function getPortCount(): Int {
    return rtmidi_out_getportcount(obj);
  }

  public function openPort(port: Int) {
    rtmidi_out_openport(obj, port);
  }

  public function closePort() {
    rtmidi_out_closeport(obj);
  }

  public function getPortName(port: Int): String {
    return rtmidi_out_getportname(obj, port);
  }

  public function sendMessage(msg: Array<Int>)  {
    return rtmidi_out_sendmessage(obj, msg);
  }

  private static var rtmidi_out_create = Lib.load("rtmidi", "rtmidi_out_create", 0);
  private static var rtmidi_out_destroy = Lib.load("rtmidi", "rtmidi_out_destroy", 1);
  private static var rtmidi_out_getportcount = Lib.load("rtmidi", "rtmidi_out_getportcount", 1);
  private static var rtmidi_out_openport = Lib.load("rtmidi", "rtmidi_out_openport", 2);
  private static var rtmidi_out_closeport = Lib.load("rtmidi", "rtmidi_out_closeport", 1);
  private static var rtmidi_out_getportname = Lib.load("rtmidi", "rtmidi_out_getportname", 2);
  private static var rtmidi_out_sendmessage = Lib.load("rtmidi", "rtmidi_out_sendmessage", 2);
}
