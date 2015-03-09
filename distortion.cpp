#include "distortion.h"
#include <math.h>
#include <fstream>

#define DEFAULT_PROG "Default"
#define UNIQUE_ID 'rgmd'

#define EFFECT_NAME "Distortion"
#define PRODUCT_STRING "Distortion"
#define VENDOR_STRING "TOBY STOKES"
#define VENDOR_VERSION 1

#define MAX_GAIN 1

AudioEffect* createEffectInstance(audioMasterCallback audioMaster)
{
	return new distortion (audioMaster);
}

// Constructor
distortion::distortion(audioMasterCallback audiomaster)
: AudioEffectX(audioMaster, 1,3)
{
	setNumInputs(1);
	setNumOutputs(1);
	setUniqueID(UNIQUE_ID);
	canProcessReplacing();

	gain = 0.5;

	logfile.open("distortion.log");
	resume();

	vst_strncpy(programName,DEFAULT_PROG,kVstMaxProgNameLen);
}
// Destructor
distortion::~distortion()
{
	logfile.close();
}

// Processing
void distortion::processReplacing(float** inputs, float** outputs, VstInt32 sampleFrames)
{
	float *in = inputs[0];
	float *out = outputs[0];
	float x;
	for (int frame_idx=0;frame_idx<=sampleFrames;frame_idx++)
	{
		x = in[frame_idx];
		out[frame_idx] = (x/abs(x))*(1 - exp((x*x)/abs(x)));
		logfile << "In sample " << in[frame_idx] << " Out sample "<< out[frame_idx] << "\n";		
	}
}


// Plugin name set/get
void distortion::setProgramName(char* name)
{
	vst_strncpy(programName, name, kVstMaxProgNameLen);
}
void distortion::getProgramName(char* name)
{
	vst_strncpy(name, programName, kVstMaxProgNameLen);
}

//Parameters
void distortion::setParameter(VstInt32 index, float value)
{
	gain = value*MAX_GAIN;
}

float distortion::getParameter(VstInt32 index)
{
	float param = 0.0;
	param = gain/MAX_GAIN;
	return param;
}

void distortion::getParameterName(VstInt32 index, char* label)
{
	vst_strncpy(label,"Gain",kVstMaxParamStrLen);
}

void distortion::getParameterDisplay(VstInt32 index, char* text)
{
	dB2string(gain, text, kVstMaxParamStrLen);
}

void distortion::getParameterLabel(VstInt32 index, char* label)
{
	vst_strncpy(label, "dB", kVstMaxParamStrLen);
}

//VST host functions
bool distortion::getEffectName(char* name) {
    vst_strncpy (name, EFFECT_NAME, kVstMaxEffectNameLen);
    return true;
}
bool distortion::getProductString(char* text) {
    vst_strncpy (text, PRODUCT_STRING, kVstMaxProductStrLen);
    return true;
}
bool distortion::getVendorString(char* text) {
    vst_strncpy (text, VENDOR_STRING, kVstMaxVendorStrLen);
    return true;
}
VstInt32 distortion::getVendorVersion() {
    return VENDOR_VERSION;
}
