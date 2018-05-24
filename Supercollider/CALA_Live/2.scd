

{a=HPF.ar(ar(PinkNoise,5e-3),10)*Line.kr(0,1,9);ar(GVerb,({|i|ar(Ringz,a*LFNoise1.kr(0.05+0.1.rand),55*i+60,0.2)}!99).sum,70,99).tanh}.play

(
n=LFNoise1;
Ndef(\x,
	{a=SinOsc.ar(60,
		Ndef(\x).ar*n.ar(0.1,3),n.ar(3,6)).tanh;
		9.do{a=AllpassL.ar(a,0.3,{0.2.rand+0.1}!2,5)};
	a.tanh}).play
)