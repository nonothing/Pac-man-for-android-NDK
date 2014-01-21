#ifndef _OSLSound_
#define _OSLSound_

#include <SLES/OpenSLES.h>
#include <SLES/OpenSLES_Android.h>
#include "Sound/OSLContext.h"
class AAsset;
class AAssetManager;
/**
 * The canonical WAVE format starts with the RIFF header
 */
typedef struct {
  char  riff[4];				// Contains the letters "RIFF" in ASCII form
  	  	  	  	  	  	  	    // (0x52494646 big-endian form).
  unsigned int riffSize;		// 36 + SubChunk2Size, or more precisely:
								// 4 + (8 + SubChunk1Size) + (8 + SubChunk2Size)
								// This is the size of the rest of the chunk
								// following this number.  This is the size of the
								// entire file in bytes minus 8 bytes for the
								// two fields not included in this count:
								// ChunkID and ChunkSize.

  char  wave[4];				// Contains the letters "WAVE"
  	  	  	  	  	  	  	  	//(0x57415645 big-endian form).

  char  fmt[4];					// Contains the letters "fmt"
  	  	  	  	  	  	  	  	// (0x666d7420 big-endian form).

  unsigned int fmtSize;			// 16 for PCM.  This is the size of the
  	  	  	  	  	  	  	  	// rest of the Subchunk which follows this number.

  unsigned short format; 	    // PCM = 1 (i.e. Linear quantization)Values other than 1 indicate some form of compression.
  unsigned short channels;      // Mono = 1, Stereo = 2, etc.
  unsigned int samplesPerSec;	// Sampling rate (8000, 44100, etc.)
  unsigned int bytesPerSec;     // samplesPerSec * channels * bitsPerSample/8

  unsigned short blockAlign;    // NumChannels * BitsPerSample/8
  	  	  	  	  	  	  	  	// The number of bytes for one sample including all channels.

  unsigned short bitsPerSample; // 8 bits = 8, 16 bits = 16, etc.
  char  data[4];				// 'data'
  unsigned int dataSize;		// The actual sound data.
}BasicWAVEHeader;

class OSLPlayer;
class OSLContext;
class OSLSound
{


public:
	void load( char* filename);
	BasicWAVEHeader header;
	AAsset* openFile(char * path);
	long dataSize;
	char* readWAVFull(AAssetManager *mgr, BasicWAVEHeader* header);
	void GenSources();
	void LogHeaders();
	char*  buf ;

	char filename[64];

	virtual ~OSLSound();
	OSLSound( OSLContext * context);
	OSLSound( OSLContext * context, char * path);

	virtual void setVolume(float volume);
	virtual float getVolume();

	virtual void play( bool isLoop);
	virtual void pause();
	virtual void stop();
	SLuint32 state();

	bool isActive();
	virtual bool isPlaying();
	virtual bool isPaused();
	virtual bool isStopped();
    void setLoop(bool loop);
    bool isLooping();
    long getSize();
    char * getBuffer();
protected:
    float volume;
    void setVolumePlayer();
    OSLPlayer * player;
    AAssetManager *mgr;
	OSLContext * context;

};

#endif
