#ifndef MIDIKIT_MIDI_UTIL_H
#define MIDIKIT_MIDI_UTIL_H
#include <sys/select.h>

typedef unsigned int MIDIVarLen;
int MIDIUtilReadVarLen( MIDIVarLen * value, size_t size, unsigned char * buffer, size_t * read );
int MIDIUtilWriteVarLen( MIDIVarLen * value, size_t size, unsigned char * buffer, size_t * written );

struct MIDIRunloopSource {
  int nfds;
  fd_set readfds;
  fd_set writefds;
  struct timespec timeout;
  struct timespec remain;
  int (*read)( void * info, int nfds, fd_set * readfds );
  int (*write)( void * info, int nfds, fd_set * writefds );
  int (*idle)( void * info, struct timespec * idletime );
  void * info;
};

int MIDIRunloopSourceWait( struct MIDIRunloopSource * source );

struct MIDIRunloop;

struct MIDIRunloop * MIDIRunloopCreate();
void MIDIRunloopDestroy( struct MIDIRunloop * runloop );
void MIDIRunloopRetain( struct MIDIRunloop * runloop );
void MIDIRunloopRelease( struct MIDIRunloop * runloop );

int MIDIRunloopAddSource( struct MIDIRunloop * runloop, struct MIDIRunloopSource * source );
int MIDIRunloopRemoveSource( struct MIDIRunloop * runloop, struct MIDIRunloopSource * source );

int MIDIRunloopStart( struct MIDIRunloop * runloop );
int MIDIRunloopStop( struct MIDIRunloop * runloop );
int MIDIRunloopStep( struct MIDIRunloop * runloop );

#endif
