package;

#if cpp
import cpp.Lib;
#elseif neko
import neko.Lib;
#end

class RTMidi {
	public static function sampleMethod (inputValue:Int):Int {
		return sampleextension_sample_method(inputValue);
	}

	private static var sampleextension_sample_method = Lib.load ("rtmidi", "sampleextension_sample_method", 1);
}
