#include <system/vrSound.h>

void VRSound::start() {
	/* we unpause the audio so our audiobuffer gets read */
	mixSetPlay(this->cIndex, true);
	SDL_PauseAudio(0);	
}
void VRSound::pause() {
	/* we unpause the audio so our audiobuffer gets read */
	mixSetPlay(this->cIndex, false);
	SDL_PauseAudio(1);
}
void VRSound::stop() {

}

VRSound::VRSound(string file) {
	printf("Loading sound from file '%s'\n", file.c_str());
	initSDLAudio();
	this->cIndex = OpenSound(file.c_str());
}

VRSound::~VRSound() {
	closeSDLAudio();	
}

void VRSound::setVolume(Uint8 volume) {
	mixSetVolume(this->cIndex, volume);
}
Uint8 VRSound::getMaxVolume() {
	return SDL_MIX_MAXVOLUME;
}

extern "C" {
int audioStarted=0;
void closeSDLAudio(){
	audioStarted--;
	if (audioStarted<=0)
		SDL_CloseAudio();
}
void initSDLAudio() {
	if (audioStarted>0) return;
	audioStarted++;
	SDL_AudioSpec fmt;
	// Set 16-bit stereo audio at 22Khz 
	fmt.freq = 22050;
	fmt.format = AUDIO_S16;
	fmt.channels = 2;
	fmt.samples = 512; /* A good value for games */
	fmt.callback = mixaudio;
	fmt.userdata = NULL;
	/* Open the audio device and start playing sound! */
	if (SDL_OpenAudio(&fmt, NULL) < 0) {
		fprintf(stderr, "Unable to open audio: %s\n", SDL_GetError());
		exit(1);
	}	
}

#define NUM_SOUNDS 10
struct sample {
	Uint8 *data;
	Uint32 dpos;
	Uint32 dlen;
	Uint8 volume;
	bool play;
} sounds[NUM_SOUNDS];

void mixaudio(void *unused, Uint8 *stream, int len) {
	int i;
	Uint32 amount;
	printf("volume = ");
	for (i=0; i<NUM_SOUNDS; ++i) {
		if (!sounds[i].play) continue;
		amount = (sounds[i].dlen-sounds[i].dpos);
		if (amount > (unsigned int)len ) {
			amount = len;
		}
		printf("%d\t", sounds[i].volume);
		SDL_MixAudio(stream,
				&sounds[i].data[sounds[i].dpos], amount, 
				sounds[i].volume);
		sounds[i].dpos += amount;
	}
	printf("\n");
	fflush(stdout);
}
void mixSetVolume(int index, Uint8 volume) {
	if (index<0) return;
	sounds[index].volume = volume;
}

void mixSetPlay(int index, bool play) {
	if (index<0) return;
	sounds[index].play = play;
}

int OpenSound(const char *file) {
	int index;
	SDL_AudioSpec wave;
	Uint8 *data;
	Uint32 dlen;
	SDL_AudioCVT cvt;

	/* Look for an empty (or finished) sound slot */
	for (index=0; index<NUM_SOUNDS; ++index) {
		if (sounds[index].dpos == sounds[index].dlen) {
			break;
		}
	}
	if (index == NUM_SOUNDS)
		return -1;

	/* Load the sound file and convert it to 16-bit stereo at 22kHz */
	if ( SDL_LoadWAV(file, &wave, &data, &dlen) == NULL) {
		fprintf(stderr, "Couldn't load %s: %s\n", file, SDL_GetError());
		return -1;
	}
	SDL_BuildAudioCVT(&cvt, wave.format, wave.channels,
			wave.freq, 
			AUDIO_S16, 2, 22050);
	cvt.buf = (Uint8 *) malloc(dlen*cvt.len_mult);
	memcpy(cvt.buf, data, dlen);
	cvt.len = dlen;
	SDL_ConvertAudio(&cvt);
	SDL_FreeWAV(data);

	/* Put the sound data in the slot (it starts playing immediately) */
	if (sounds[index].data) {
		free(sounds[index].data);
	}
	SDL_LockAudio();
	sounds[index].data = cvt.buf;
	sounds[index].dlen = cvt.len_cvt;
	sounds[index].dpos = 0;
	SDL_UnlockAudio();
	//Sets the maximum volume, by default
	sounds[index].volume = SDL_MIX_MAXVOLUME;
	sounds[index].play = false;
	
	return index;
}

}

