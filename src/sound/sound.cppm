module;

#define MINIMP3_IMPLEMENTATION
#include <minimp3/minimp3_ex.h>


export module openhomm.sound;

import <SDL2/SDL.h>;
//import <SDL2/SDL_audio.h>;
import <iostream>;


export
{
	typedef struct privateAudioDevice
	{
		SDL_AudioDeviceID device;
		SDL_AudioSpec want;
		uint8_t audioEnabled;
	} PrivateAudioDevice;

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

			const char* filename = "C:\\Users\\Alexe\\source\\1.WAV";
			const char* mp3filename = "C:\\Users\\Alexe\\source\\2.mp3";


			newAudio = (Audio*)calloc(1, sizeof(Audio));

			newAudio->next = NULL;
			newAudio->loop = 0;
			newAudio->fade = 0;
			newAudio->free = 1;
			newAudio->volume = SDL_MIX_MAXVOLUME / 2;

			SDL_AudioSpec sst;

			// SDL_LoadWAV("Powerup5.wav", &wavSpec, &wavBuffer, &wavLength);
			//if (SDL_LoadWAV(filename, &(newAudio->audio), &(newAudio->bufferTrue), &(newAudio->lengthTrue)) == NULL)


			

			if (SDL_LoadWAV(filename, &sst, &(newAudio->bufferTrue), &(newAudio->lengthTrue)) == NULL)
			{
				printf("Error load file");
				free(newAudio);
				return;
			}

			mp3dec_t mp3d;
			mp3dec_file_info_t info;

			if (mp3dec_load(&mp3d, mp3filename, &info, NULL, NULL))
			{
				printf("Error load mp3\n");
			}

			printf("MP3\n");
			std::cout << info.channels << std::endl;
			std::cout << info.samples << std::endl;
			std::cout << info.hz << std::endl;
			std::cout << info.layer << std::endl;
			std::cout << info.avg_bitrate_kbps << std::endl;

			Audio* mp3Audio = (Audio*)calloc(1, sizeof(Audio));
			mp3Audio->next = NULL;
			mp3Audio->loop = 0;
			mp3Audio->fade = 0;
			mp3Audio->free = 1;
			mp3Audio->volume = SDL_MIX_MAXVOLUME / 2;

			SDL_AudioSpec mp3sdl;// , have;
			//SDL_AudioDeviceID dev;

			SDL_memset(&mp3sdl, 0, sizeof(mp3sdl)); /* or SDL_zero(want) */
			mp3sdl.freq = info.hz;
			mp3sdl.format = AUDIO_S16LSB;// 32784;// AUDIO_F32; // AUDIO_S16
			mp3sdl.channels = info.channels;
			mp3sdl.samples = 4096;
			mp3sdl.callback = NULL;

			mp3Audio->audio = mp3sdl;
			mp3Audio->bufferTrue = (uint8_t*)info.buffer;
			mp3Audio->lengthTrue = (uint32_t)info.samples;

			(mp3Audio->audio).callback = NULL;
			(mp3Audio->audio).userdata = NULL;




			//  int16_t * buffer;
			//	size_t samples; /* channels included, byte size = samples*sizeof(mp3d_sample_t) */
			//	int channels;
			//  int hz;
			//  int layer ;
			//  int avg_bitrate_kbps;
			//} mp3dec_file_info_t;


			// uint8_t **buffer bufferTrue    int16_t
			// uint32_t length lengthTrue


			SDL_AudioSpec want;// , have;
			//SDL_AudioDeviceID dev;

			SDL_memset(&want, 0, sizeof(want)); /* or SDL_zero(want) */
			want.freq = 44100;
			want.format = AUDIO_S16LSB;// 32784;// AUDIO_F32; // AUDIO_S16
			want.channels = 2;
			want.samples = 4096;
			want.callback = NULL;
			//dev = SDL_OpenAudioDevice(NULL, 0, &want, &have, SDL_AUDIO_ALLOW_FORMAT_CHANGE);
			newAudio->audio = want;

			printf("WAV\n");
			std::cout << newAudio->audio.freq << std::endl;
			std::cout << newAudio->audio.format << std::endl;
			std::cout << newAudio->audio.channels << std::endl;
			std::cout << newAudio->audio.samples << std::endl;
			std::cout << newAudio->lengthTrue << std::endl;


			(newAudio->audio).callback = NULL;
			(newAudio->audio).userdata = NULL;
			
			int mod = 2;

			if (mod == 1) {
				SDL_AudioDeviceID deviceId = SDL_OpenAudioDevice(NULL, 0, &newAudio->audio, NULL, 0);
				std::cout << "DeviceID: " << deviceId << std::endl;

				int success = SDL_QueueAudio(deviceId, newAudio->bufferTrue, newAudio->lengthTrue);
				SDL_PauseAudioDevice(deviceId, 0);

				SDL_Delay(3000);

				SDL_CloseAudioDevice(deviceId);
				SDL_FreeWAV(newAudio->bufferTrue);
			}
			else if (mod == 2) {
				SDL_AudioDeviceID deviceId = SDL_OpenAudioDevice(NULL, 0, &mp3Audio->audio, NULL, 0);
				std::cout << "DeviceID: " << deviceId << std::endl;

				int success = SDL_QueueAudio(deviceId, mp3Audio->bufferTrue, mp3Audio->lengthTrue);
				SDL_PauseAudioDevice(deviceId, 0);

				SDL_Delay((4 * 60 + 2) * 1000);

				SDL_CloseAudioDevice(deviceId);
				SDL_FreeWAV(mp3Audio->bufferTrue);
			}
			else if (mod == 3)
			{
				SDL_AudioDeviceID deviceId = SDL_OpenAudioDevice(NULL, 0, &mp3Audio->audio, NULL, 0);
				std::cout << "DeviceID: " << deviceId << std::endl;

				SDL_AudioDeviceID deviceId2 = SDL_OpenAudioDevice(NULL, 0, &newAudio->audio, NULL, 0);
				std::cout << "DeviceID: " << deviceId2 << std::endl;

				SDL_QueueAudio(deviceId, newAudio->bufferTrue, newAudio->lengthTrue);
				SDL_QueueAudio(deviceId2, mp3Audio->bufferTrue, mp3Audio->lengthTrue);
				
				SDL_PauseAudioDevice(deviceId, 0);

				SDL_Delay((4 * 60 + 2) * 1000);

				SDL_CloseAudioDevice(deviceId);
				SDL_FreeWAV(mp3Audio->bufferTrue);
			}

		}

		~Sound()
		{

		}

		void loadMedia()
		{
			//mp3dec_t mp3d;
			//mp3dec_file_info_t info;

			const char* filename = "C:\\Users\\Alexe\\source\\1.WAV";
			//const char* filename = "C:\\Users\\Alexe\\source\\2.mp3";
			//int res = mp3dec_detect(filename);
			//std::cout << res << std::endl;

			//typedef struct
			//{
			//	int16_t mp3d_sample_t* buffer;
			//	size_t samples; /* channels included, byte size = samples*sizeof(mp3d_sample_t) */
			//	int channels, hz, layer, avg_bitrate_kbps;
			//} mp3dec_file_info_t;

			/*
			if (mp3dec_load(&mp3d, filename, &info, NULL, NULL))
			{
				std::cout << "Error Load" << std::endl;
			}
			else
			{
				std::cout << "Load" << std::endl;
			}
			*/
			/*
			
			newAudio->next = NULL;
			newAudio->loop = 0;
			newAudio->fade = 0;
			newAudio->free = 1;
			newAudio->volume = SDL_MIX_MAXVOLUME / 2;

			// SDL_LoadWAV("Powerup5.wav", &wavSpec, &wavBuffer, &wavLength);
			if (SDL_LoadWAV(filename, &(newAudio->audio), &(newAudio->bufferTrue), &(newAudio->lengthTrue)) == NULL)
			{
				printf("Error load file");
				free(newAudio);
				return;
			}

			newAudio->buffer = newAudio->bufferTrue;
			newAudio->length = newAudio->lengthTrue;
			(newAudio->audio).callback = NULL;
			(newAudio->audio).userdata = NULL;
			*/
			// newAudio = createAudio(filename, loop, volume);
		}

	
				
	protected:
		Uint32 audio_len;
		Audio* newAudio;
		bool opened = false;
	};
};

