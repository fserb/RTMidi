package;

#if cpp
import cpp.Lib;
#elseif neko
import neko.Lib;
#end

class RTMidi {
	private var obj: Float;
	public function new() {
		obj = rtmidi_in_create();
	}

	public function close() {
		rtmidi_in_destroy(obj);
		obj = 0;
	}

	public function getPortCount(): Int {
		return rtmidi_in_getportcount(obj);
	}

	public function openPort(port: Int) {
		rtmidi_in_openport(obj, port);
	}

	public function ignoreTypes(sysex: Bool, time: Bool, sense: Bool) {
		rtmidi_in_ignoretypes(obj, sysex, time, sense);
	}

	public function getMessage(): Array<Int> {
		return rtmidi_in_getmessage(obj);
	}

	private static var rtmidi_in_create = Lib.load("rtmidi", "rtmidi_in_create", 0);
	private static var rtmidi_in_destroy = Lib.load("rtmidi", "rtmidi_in_destroy", 1);
	private static var rtmidi_in_getportcount = Lib.load("rtmidi", "rtmidi_in_getportcount", 1);
	private static var rtmidi_in_openport = Lib.load("rtmidi", "rtmidi_in_openport", 2);
	private static var rtmidi_in_ignoretypes = Lib.load("rtmidi", "rtmidi_in_ignoretypes", 4);
	private static var rtmidi_in_getmessage = Lib.load("rtmidi", "rtmidi_in_getmessage", 1);
}
