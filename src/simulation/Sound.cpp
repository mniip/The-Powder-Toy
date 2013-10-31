#include <simulation/Sound.h>
#include <list>
#include <math.h>
#include <pthread.h>

std::list<Sound::Note> queue;
pthread_mutex_t Sound::Mutex;

void Sound::AddNote(int duration, double frequency, double volume)
{
	if(queue.size()<128)
	{
		pthread_mutex_lock(&Sound::Mutex);
		Sound::Note n;
		n.duration = duration;
		n.left = duration;
		n.frequency = frequency;
		n.volume = volume;
		n.offset = 0;
		queue.push_back(n);
		pthread_mutex_unlock(&Sound::Mutex);
	}
}

void Sound::ClearNotes()
{
	pthread_mutex_lock(&Sound::Mutex);
	queue.clear();
	pthread_mutex_unlock(&Sound::Mutex);
}

void Sound::UpdateNotes()
{
	pthread_mutex_lock(&Sound::Mutex);
	for(std::list<Sound::Note>::iterator iter = queue.begin(), end = queue.end(); iter != end;)
	{
		if(iter->left)
		{
			iter->left--;
			iter++;
		}
		else
			iter = queue.erase(iter);
	}
	pthread_mutex_unlock(&Sound::Mutex);
}

double sfrac(double x)
{
	return (int)x > x-.5f?-1.f:1.f;
}

void Sound::Callback(void *udata, Uint8 *s, int len)
{
	signed char *stream = (signed char *)s;
	pthread_mutex_lock(&Sound::Mutex);
	for(;len;len--)
	{
		double v=0;
		for(std::list<Sound::Note>::iterator iter = queue.begin(), end = queue.end(); iter != end; iter++)
		{
			v += sfrac(iter->offset*iter->frequency/SAMPLES)*iter->volume;
			iter->offset++;			
		}
		*stream = v;
		stream++;
	}
	pthread_mutex_unlock(&Sound::Mutex);
}
