package;

#if cpp
import cpp.Lib;
#elseif neko
import neko.Lib;
#end

#if (android && openfl)
import openfl.utils.JNI;
#end


class SampleExtension {
	
	
	public static function sampleMethod (inputValue:Int):Int {
		
		#if (android && openfl)
		
		var resultJNI = sampleextension_sample_method_jni(inputValue);
		var resultNative = sampleextension_sample_method(inputValue);
		
		if (resultJNI != resultNative) {
			
			throw "Fuzzy math!";
			
		}
		
		return resultNative;
		
		#else
		
		return sampleextension_sample_method(inputValue);
		
		#end
		
	}
	
	
	private static var sampleextension_sample_method = Lib.load ("sampleextension", "sampleextension_sample_method", 1);
	
	#if (android && openfl)
	private static var sampleextension_sample_method_jni = JNI.createStaticMethod ("org.haxe.extension.SampleExtension", "sampleMethod", "(I)I");
	#end
	
	
}