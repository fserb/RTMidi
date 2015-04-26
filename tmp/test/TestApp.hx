import flash.Lib;

import flash.events.Event;
import RTMidi;

class TestApp  {
  public var midi: RTMidi;

  public static function main() {
    new TestApp();
  }

  public function new() {
    midi = new RTMidi();

    var ports = midi.getPortCount();
    trace("Ports: " + ports);

    midi.openPort(0);
    midi.setCallback(cb);
    midi.ignoreTypes(false, false, false);

    // Lib.current.stage.addEventListener(Event.ENTER_FRAME, frame);
  }

  function cb(msg:Array<Int>) {
    trace(msg);
  }

  // public function frame(ev) {
  //   var msg: Array<Int> = midi.getMessage();
  //   if (msg.length == 0) return;
  //   trace(msg);

  // }
}
