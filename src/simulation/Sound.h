#include <SDL/SDL.h>
#include <pthread.h>
#define SAMPLES 44100
namespace Sound
{
	typedef struct
	{
		int duration;
		int left;
		double frequency;
		double volume;
		int offset;
	} Note;
	extern pthread_mutex_t Mutex;
	void AddNote(int duration, double frequency, double volume);
	void ClearNotes();
	void UpdateNotes();
	void Callback(void *udata, Uint8 *stream, int len);
}
