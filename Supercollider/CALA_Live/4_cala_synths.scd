//TUBES

(
SynthDef(\dt1_test, {
	arg
	d1=40, d2=60,
	atk=0, rel=1,
	dens=1,
	filtermix=0.33, room=3, damp=0.5, freqs=80,
	pos=0, amp=0.05, width=2,
	detune=1.5;
	var sig,env,filtersig, source, shift, filtershift;
	source = Dust.ar(dens);
	shift = TwoTube.ar(source,1,0.99,d1,d2);
	env = EnvGen.kr(Env.new([0,1,0],[atk,rel],[1,-1]),doneAction:2);
	shift = PitchShift.ar(shift, pitchRatio: 0.1);
	shift =FreqShift.ar(shift, freqs*detune);
	shift = FreeVerb.ar(shift,filtermix,room,damp);
	shift = BPF.ar(shift,440,1);
	sig = shift *env;
	//sig=PanX.ar(4,shift,pos,amp,width);
	Out.ar(1,sig!4);
}).add;
)




//SINES INFINITY

(
SynthDef.new(\sine1,{
	arg freq=440,atk=0.005,rel=0.3,amp=1,pos=0;
	var sig, env;
	sig = SinOsc.ar(freq);
	sig = FreeVerb.ar(sig,0.5,2,0.5);
	env = EnvGen.kr(Env.new([0,1,0],[atk,rel],[1,-1]),doneAction:2);
	sig = sig * env;
	sig = PanX.ar(4,sig,pos,amp);
	Out.ar(1,sig);
}).add;
)



///BASS AFTER FREE SWIMING
(
SynthDef(\noclip,{
	arg freq,attack=0.5, release=1,mix=0.1,room=2.0,damp=0.1,mulf=0.5, pos=0,amp=0.5, width=2;
	var source, env,filter,sig;
	source = SinOsc.ar(freq,0,0.7);
	env = EnvGen.kr(Env.perc(attack, release, 0.7, 5),doneAction: 2);
	source = FreeVerb.ar(source,mix,room,damp,mulf);
	sig = source * env;
	//sig = PanX.ar(4,sig,pos,amp,width);
	Out.ar(1,sig!4);
}).add;
)

