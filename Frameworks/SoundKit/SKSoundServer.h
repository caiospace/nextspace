/* -*- mode: objc -*- */
/*
  Project: SoundKit framework.

  Copyright (C) 2019 Sergii Stoian

  This application is free software; you can redistribute it and/or
  modify it under the terms of the GNU General Public
  License as published by the Free Software Foundation; either
  version 2 of the License, or (at your option) any later version.

  This application is distributed in the hope that it will be useful,
  but WITHOUT ANY WARRANTY; without even the implied warranty of
  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
  Library General Public License for more details.

  You should have received a copy of the GNU General Public
  License along with this library; if not, write to the Free
  Software Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA 02111 USA.
*/

#import <pulse/pulseaudio.h>
#import <Foundation/Foundation.h>

@class SKSoundOut;
@class SKSoundIn;

@class PACard;
@class PASink;
@class PASource;
@class PASinkInput;

typedef enum NSInteger {
  SKServerNoConnnectionState,	// PA_CONTEXT_UNCONNECTED
  SKServerConnectingState,	// PA_CONTEXT_CONNECTING
  SKServerAuthorizingState,	// PA_CONTEXT_AUTHORIZING
  SKServerSettingNameState,	// PA_CONTEXT_SETTING_NAME
  SKServerReadyState,		// PA_CONTEXT_READY
  SKServerFailedState,		// PA_CONTEXT_FAILED
  SKServerTerminatedState,	// PA_CONTEXT_TERMINATED
  SKServerInventoryState
} SKConnectionState;

extern NSString *SKServerStateDidChangeNotification;
extern NSString *SKDeviceDidAddNotification;
extern NSString *SKDeviceDidChangeNotification;
extern NSString *SKDeviceDidRemoveNotification;

@interface SKSoundServer : NSObject
{
  // Define our pulse audio loop and connection variables
  pa_mainloop		*_pa_loop;
  pa_mainloop_api	*_pa_api;
  pa_operation		*_pa_op;

  // SKSoundDevice
  NSMutableArray        *cardList;
  // SKSoundOut
  NSMutableArray        *sinkList;
  NSMutableArray        *sourceList;
  // SKSoundStream
  NSMutableArray        *clientList;
  NSMutableArray        *sinkInputList;
  NSMutableArray        *sourceOutputList;
  NSMutableArray        *savedStreamList; // sink-input* or source-output*
}

@property (readonly) pa_context        *pa_ctx;
@property (readonly) SKConnectionState status;

@property (readonly) NSString *userName;  // User name of the daemon process
@property (readonly) NSString *hostName;  // Host name the daemon is running on
@property (readonly) NSString *name;      // Server package name (usually "pulseaudio")
@property (readonly) NSString *version;   // Version string of the daemon
@property (readonly) NSString *defaultSinkName;
@property (readonly) NSString *defaultSourceName;


+ (id)sharedServer;

- (id)initOnHost:(NSString *)hostName;
- (void)disconnect;

- (SKSoundOut *)defaultOutput;
- (NSArray *)outputList;

@end

@interface SKSoundServer (PulseAudio)

// Server
- (void)updateConnectionState:(NSNumber *)state;
- (void)updateServer:(NSValue *)value;
// Card
- (void)updateCard:(NSValue *)value;
- (PACard *)cardWithIndex:(NSUInteger)index;
- (void)removeCardWithIndex:(NSNumber *)index;
// Sink
- (void)updateSink:(NSValue *)value;
- (PASink *)sinkWithIndex:(NSUInteger)index;
- (PASink *)sinkWithName:(NSString *)name;
- (void)removeSinkWithIndex:(NSNumber *)index;
// TODO: Source
- (void)updateSource:(NSValue *)value;
- (PASource *)sourceWithIndex:(NSUInteger)index;
- (PASource *)sourceWithName:(NSString *)name;
- (void)removeSourceWithIndex:(NSNumber *)index;
// Sink Input
- (void)updateSinkInput:(NSValue *)value;
- (PASinkInput *)sinkInputWithIndex:(NSUInteger)index;
- (void)removeSinkInputWithIndex:(NSNumber *)index;
// TODO: Source Output
- (void)updateSourceOutput:(NSValue *)value;
- (void)removeSourceOutputWithIndex:(NSNumber *)index;
// Client
- (void)updateClient:(NSValue *)value;
- (void)removeClientWithIndex:(NSNumber *)index;
// Restored Stream
- (void)updateStream:(NSValue *)value;

@end