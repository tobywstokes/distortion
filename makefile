all: distortion.cpp distortion.h
	g++ -Wall -m32 -bundle -o distortion distortion.cpp vstsdk2.4/public.sdk/source/vst2.x/audioeffect.cpp vstsdk2.4/public.sdk/source/vst2.x/audioeffectx.cpp vstsdk2.4/public.sdk/source/vst2.x/vstplugmain.cpp -I vstsdk2.4/public.sdk/source/vst2.x/ -I vstsdk2.4/ 
