

//TUBES
(
Pdef(
	\tubelive,
	Pbind(
	\instrument, \dt1_test,
	\dur,2.5,
	//	\dur,Pwhite(0,0.5,inf).trace,
	//\freqs, Pwhite(80,100,inf).trace,
	\freq,400,
	\d1, 20,
	\d2, Pwhite(11,17,inf).trace,
	//\harmonic,Pexprand(0,50,inf),
	\atk, Pwhite(0.4,0.7,inf),
	\rel,Pwhite(10,12,inf),
	\amp,Pwhite(0.1,0.5,inf),
	\pos, Pwhite(-0.8,0.8,inf),
	);
).play;
)


///SINES INFINITY
(
Pdef(
	\sinelive,
	Pbind(
	\instrument, \sine1,
	\dur,Pwhite(0.05,0.5, inf),
	\midinote,Pseq([0],inf),
	\harmonic,Pexprand(1,100,inf),
	\atk, Pwhite(2.0,3.0,inf),
	\rel,Pwhite(5.0,10,inf),
	\amp,Pexprand(0.02,0.03,inf),
	\pos, Pwhite(-0.8,0.8,inf),
	);
).play;
)


//BASS AFTER free swimn

(
Pdef(
	\pulselive,
	Pbind(
	\instrument, \noclip,
	\dur, 0.8,
		\freq, Pseq([70,80,90,60,80,90,70,60],inf),
	\harmonic,100,
	\attack,0.5,
	//\pos,Pwhite(0,1,inf),
	\release,1,
	\amp,1,
	);
).play;
)






