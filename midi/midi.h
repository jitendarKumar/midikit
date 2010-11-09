#ifndef MIDIKIT_MIDI_H
#define MIDIKIT_MIDI_H

/**
 * Channel Voice Messages
 * (Status has 4 bits & is followed by a 4 bit channel number.)
 */
//@{

/**
 * Note Off event.
 * This message is sent when a note is released (ended).
 */
#define MIDI_STATUS_NOTE_OFF 0x8

/**
 * Note On event. 
 * This message is sent when a note is depressed (start). 
 */
#define MIDI_STATUS_NOTE_ON 0x9

/**
 * Polyphonic Key Pressure (Aftertouch). 
 * This message is most often sent by pressing down on the
 * key after it "bottoms out".
 */
#define MIDI_STATUS_POLYPHONIC_KEY_PRESSURE 0xa

/**
 * Control Change. 
 * This message is sent when a controller value changes.
 * Controllers include devices such as pedals and levers. 
 */
#define MIDI_STATUS_CONTROL_CHANGE 0xb

/**
 * Program Change.
 * This message sent when the patch number changes.
 */
#define MIDI_STATUS_PROGRAM_CHANGE 0xc

/**
 * Channel Pressure (After-touch).
 * This message is most often sent by pressing down on the key
 * after it "bottoms out". This message is different from polyphonic
 * after-touch. Use this message to send the single greatest pressure
 * value (of all the current depressed keys).
 */
#define MIDI_STATUS_CHANNEL_PRESSURE 0xd

/**
 * Pitch Wheel Change.
 */
#define MIDI_STATUS_PITCH_WHEEL_CHANGE 0xe

//@}

/**
 * System Common Messages
 * (Status has eight bits.)
 */
//@{

/**
 * System Exclusive.
 * This message makes up for all that MIDI doesn't support.
 */
#define MIDI_STATUS_SYSTEM_EXCLUSIVE 0xf0

/**
 * MIDI Time Code Quarter Frame.
 * (What is this?)
 */
#define MIDI_STATUS_TIME_CODE_QUARTER_FRAME 0xf1

/**
 * Song Position Pointer.
 */
#define MIDI_STATUS_SONG_POSITION_POINTER 0xf2

/**
 * Song Select. 
 * The Song Select specifies which sequence or song is to be played.
 */
#define MIDI_STATUS_SONG_SELECT 0xf3

/**
 * Undefined. (Reserved)
 */
#define MIDI_STATUS_UNDEFINED0 0xf4

/**
 * Undefined. (Reserved)
 */
#define MIDI_STATUS_UNDEFINED1 0xf5

/**
 * Tune Request.
 * Upon receiving a Tune Request, all analog synthesizers should tune
 * their oscillators.
 */
#define MIDI_STATUS_TUNE_REQUEST 0xf6

/**
 * End of Exclusive.
 * Used to terminate a System Exclusive dump (see above).
 */
#define MIDI_STATUS_END_OF_EXCLUSIVE 0xf7

//@}

/**
 * System Real-Time Messages
 * (Status has eight bits.)
 */
//@{

/**
 * Timing Clock.
 * Sent 24 times per quarter note when synchronization is required.
 */
#define MIDI_STATUS_TIMING_CLOCK 0xf8

/**
 * Undefined. (Reserved)
 */
#define MIDI_STATUS_UNDEFINED2 0xf9

/**
 * Start.
 * Start the current sequence playing.
 * (This message will be followed with Timing Clocks).
 */
#define MIDI_STATUS_START 0xfa

/**
 * Continue.
 * Continue at the point the sequence was Stopped.
 */
#define MIDI_STATUS_CONTINUE 0xfb

/**
 * Stop.
 * Stop the current sequence.
 */
#define MIDI_STATUS_STOP 0xfc

/**
 * Undefined. (Reserved)
 */
#define MIDI_STATUS_UNDEFINED3 0xfd

/**
 * Active Sensing.
 * Use of this message is optional. When initially sent,
 * the receiver will expect to receive another Active Sensing
 * message each 300ms (max), or it will be assume that the
 * connection has been terminated. At termination, the receiver
 * will turn off all voices and return to normal (non-active
 * sensing) operation.
 */
#define MIDI_STATUS_ACTIVE_SENSING 0xfe

/**
 * Reset.
 * Reset all receivers in the system to power-up status.
 * This should be used sparingly, preferably under manual control.
 * In particular, it should not be sent on power-up.
 */
#define MIDI_STATUS_RESET 0xff
 
//@}

/**
/**
 * MIDI channel enumeration
 */
//@{
#define MIDI_CHANNEL_1  0x0
#define MIDI_CHANNEL_2  0x1
#define MIDI_CHANNEL_3  0x2
#define MIDI_CHANNEL_4  0x3
#define MIDI_CHANNEL_5  0x4
#define MIDI_CHANNEL_6  0x5
#define MIDI_CHANNEL_7  0x6
#define MIDI_CHANNEL_8  0x7
#define MIDI_CHANNEL_9  0x8
#define MIDI_CHANNEL_10 0x9
#define MIDI_CHANNEL_11 0xa
#define MIDI_CHANNEL_12 0xb
#define MIDI_CHANNEL_13 0xc
#define MIDI_CHANNEL_14 0xd
#define MIDI_CHANNEL_15 0xe
#define MIDI_CHANNEL_16 0xf
//@}

/**
 * MIDIMessage property type enumeration
 */
//@{
#define MIDI_STATUS          0x00
#define MIDI_CHANNEL         0x01
#define MIDI_SYSTEM          0x02
#define MIDI_KEY             0x03
#define MIDI_VELOCITY        0x04
#define MIDI_CONTROL         0x05
#define MIDI_VALUE           0x06
#define MIDI_PROGRAM         0x07
#define MIDI_VALUE_LSB       0x08
#define MIDI_VALUE_MSB       0x09
#define MIDI_MANUFACTURER_ID 0x0a
#define MIDI_NOTHING         0xff
//@}

typedef unsigned char MIDIKey;
typedef unsigned int  MIDIValue;
typedef MIDIValue     MIDIMessageStatus;

#endif