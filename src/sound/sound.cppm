module;

#define MINIMP3_IMPLEMENTATION
#include <minimp3/minimp3_ex.h>


export module openhomm.sound;

import <SDL2/SDL.h>;
import <iostream>;


export
{

	typedef struct sound
	{
		uint32_t length;
		uint32_t lengthTrue;
		uint8_t* bufferTrue;
		uint8_t* buffer;
		uint8_t loop;
		uint8_t fade;
		uint8_t free;
		uint8_t volume;

		SDL_AudioSpec audio;

		struct sound* next;
	} Audio;

	struct Sound {
	public:
		Sound(int a)
		{
			//  int16_t * buffer;
			//	size_t samples; /* channels included, byte size = samples*sizeof(mp3d_sample_t) */
			//	int channels;
			//  int hz;
			//  int layer ;
			//  int avg_bitrate_kbps;
			//} mp3dec_file_info_t;


			// uint8_t **buffer bufferTrue    int16_t
			// uint32_t length lengthTrue
		}

		~Sound()
		{

		}

		int loadMedia(const char* filename)
		{
			mp3dec_t mp3d;
			mp3dec_file_info_t info;

			if (mp3dec_load(&mp3d, filename, &info, NULL, NULL))
			{
				printf("Error load mp3\n");
				return -1;
			}

			printf("MP3\n");
			std::cout << info.channels << std::endl;
			std::cout << info.samples << std::endl;
			std::cout << info.hz << std::endl;
			std::cout << info.layer << std::endl;
			std::cout << info.avg_bitrate_kbps << std::endl;

			mp3Audio = (Audio*)calloc(1, sizeof(Audio));
			mp3Audio->next = NULL;
			mp3Audio->loop = 0;
			mp3Audio->fade = 0;
			mp3Audio->free = 1;
			mp3Audio->volume = SDL_MIX_MAXVOLUME / 2;

			SDL_AudioSpec mp3sdl;
			SDL_memset(&mp3sdl, 0, sizeof(mp3sdl));
			mp3sdl.freq = info.hz;
			mp3sdl.format = AUDIO_S16LSB;
			mp3sdl.channels = info.channels;
			mp3sdl.samples = 4096;
			mp3sdl.callback = NULL;

			mp3Audio->audio = mp3sdl;
			mp3Audio->bufferTrue = (uint8_t*)info.buffer;
			mp3Audio->lengthTrue = (uint32_t)info.samples * 2;

			(mp3Audio->audio).callback = NULL;
			(mp3Audio->audio).userdata = NULL;

			return 0;
		}

		void playMedia(int time)
		{
			if (time == 0)
			{
				// All time
				time = mp3Audio->lengthTrue / mp3Audio->audio.freq / 4 * 1000;
			}
			SDL_AudioDeviceID deviceId = SDL_OpenAudioDevice(NULL, 0, &mp3Audio->audio, NULL, 0);
			std::cout << "DeviceID: " << deviceId << std::endl;

			int success = SDL_QueueAudio(deviceId, mp3Audio->bufferTrue, mp3Audio->lengthTrue);
			SDL_PauseAudioDevice(deviceId, 0);

			SDL_Delay(time);

			SDL_CloseAudioDevice(deviceId);
		}

		
		void stopMedia()
		{

		}

		void closeMedia(int id)
		{
			SDL_FreeWAV(mp3Audio->bufferTrue);
			delete(mp3Audio);
		}

		void deleteFromStream()
		{

		}
	
				
	protected:
		// ToDO Audio array for mixer
		Audio *mp3Audio;
		bool opened = false;
	};
};

