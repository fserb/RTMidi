import RTMidi;

class TestApp {
    public static function main(){
        var t = new flash.text.TextField();
        t.text = Std.string(RTMidi.sampleMethod(16));
        flash.Lib.current.addChild(t);
    }
}
