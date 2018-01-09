(
var out;
//me llega el OSC
if ()

)
OSCdef

NetAddr.localAddr

(
OSCFunc.trace(true);
)

(
var switch = "test";
var s;
OSCFunc.trace(false);

o = OSCFunc(
	{ arg msg, time, addr, recvPort;
		switch = msg[1];

}, '/csv/T1', n);


(

t = Task({
    loop {
        switch.postln;
		if (switch < 0, {s = Synth("synth1");});
		if (switch >= 0 , {s = Synth("synth2");});
		2.wait;
		s.free;
    }
}).play;
)

)


(
SynthDef("synth1", {| freq = 440, out = 0 |
	Out.ar(out, Mix(SinOsc.ar([freq, freq+1], 0, 0.1)));
}).add;

SynthDef("synth2", {| freq = 440, out = 0 |
    Out.ar(out, Mix(LFSaw.ar([freq, freq+1], 0, 0.1)));
}).add;

SynthDef("synth3", {| freq = 440, out = 0 |
    Out.ar(out, Mix(Pulse.ar([freq, freq+1], 0, 0.1)));
}).add;

)

o = OSCFunc({ arg msg, time, addr, recvPort; [msg, time, addr, recvPort].postln; }, '/goodbye', n);

