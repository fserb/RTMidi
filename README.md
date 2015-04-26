rtmidi haxe port
================

This is a native Haxe extension for [rtmidi](http://www.music.mcgill.ca/~gary/rtmidi).

It comes with precompiled ndlls for Mac, but it should work with all RTMidi
targets (Windows, Mac, Linux).

Currently, only RTMidi Input is done. Output should be easy if someone needs it.

To compile the extension:

```
cd project
haxelib run hxcpp Build.xml -Dmac
haxelib run hxcpp Build.xml -Dwindows
haxelib run hxcpp Build.xml -Dlinux
```

To use it:

1. Add the haxelib dependency (RTMidi)

2. Some code like:

```
function callback(msg: Array<Int>) {
  // msg is an array with the MIDI received bytes
}

static public function main() {
  midi = new RTMidi();
  if (midi.getPortCount() == 0) return;

  midi.openPort(0);
  midi.setCallback(callback);
  midi.ignoreTypes(false, false, false);
}
```
