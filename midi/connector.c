#include <stdlib.h>
#include <stdio.h>
#include "connector.h"

typedef int (*RelayFn)( void *, struct MIDIMessage *  );
typedef int (*ConnectFn)( void *, struct MIDIConnector * );
typedef int (*InvalidateFn)( void *, struct MIDIConnector * );

extern struct MIDIConnectorTargetDelegate MIDIDeviceInConnectorDelegate;
extern struct MIDIConnectorSourceDelegate MIDIDeviceOutConnectorDelegate;
extern struct MIDIConnectorSourceDelegate MIDIDeviceThruConnectorDelegate;

extern struct MIDIConnectorTargetDelegate MIDIDriverSendConnectorDelegate;
extern struct MIDIConnectorSourceDelegate MIDIDriverReceiveConnectorDelegate;

struct MIDIConnector {
  size_t refs;
  void * target;
  void * source;
  struct MIDIConnectorTargetDelegate * target_delegate;
  struct MIDIConnectorSourceDelegate * source_delegate;
};

static int _target_connect( struct MIDIConnector * connector ) {
  if( connector->target != NULL &&
      connector->target_delegate != NULL &&
      connector->target_delegate->connect != NULL )
    return (connector->target_delegate->connect)( connector->target, connector );
  return 0;
}

static int _source_connect( struct MIDIConnector * connector ) {
  if( connector->source != NULL &&
      connector->source_delegate != NULL &&
      connector->source_delegate->connect != NULL )
    return (connector->source_delegate->connect)( connector->source, connector );
  return 0;
}

static int _target_invalidate( struct MIDIConnector * connector ) {
  if( connector->target != NULL &&
      connector->target_delegate != NULL &&
      connector->target_delegate->invalidate != NULL )
    return (connector->target_delegate->invalidate)( connector->target, connector );
  return 0;
}

static int _source_invalidate( struct MIDIConnector * connector ) {
  if( connector->source != NULL &&
      connector->source_delegate != NULL &&
      connector->source_delegate->invalidate != NULL )
    return (connector->source_delegate->invalidate)( connector->source, connector );
  return 0;
}

struct MIDIConnector * MIDIConnectorCreate() {
  struct MIDIConnector * connector = malloc( sizeof( struct MIDIConnector ) );
  if( connector != NULL ) {
    connector->refs = 1;
    connector->target = NULL;
    connector->source = NULL;
    connector->target_delegate = NULL;
    connector->source_delegate = NULL;
  }
  return connector;
}

void MIDIConnectorDestroy( struct MIDIConnector * connector ) {
  _source_invalidate( connector );
  _target_invalidate( connector );
  free( connector );
}

void MIDIConnectorRetain( struct MIDIConnector * connector ) {
  connector->refs++;
}

void MIDIConnectorRelease( struct MIDIConnector * connector ) {
  if( ! --connector->refs ) {
    MIDIConnectorDestroy( connector );
  }
}

int MIDIConnectorDetachTarget( struct MIDIConnector * connector ) {
  connector->target = NULL;
  connector->target_delegate = NULL;
  return _source_invalidate( connector );
}

int MIDIConnectorAttachTargetWithDelegate( struct MIDIConnector * connector, void * target,
                                           struct MIDIConnectorTargetDelegate * delegate ) {
  _target_invalidate( connector );
  connector->target = target;
  connector->target_delegate = delegate;
  _target_connect( connector );
  return 0;
}

int MIDIConnectorDetachSource( struct MIDIConnector * connector ) {
  connector->source = NULL;
  connector->source_delegate = NULL;
  return _target_invalidate( connector );
}

int MIDIConnectorAttachSourceWithDelegate( struct MIDIConnector * connector, void * source,
                                           struct MIDIConnectorSourceDelegate * delegate ) {
  _source_invalidate( connector );
  connector->source = source;
  connector->source_delegate = delegate;
  _source_connect( connector );
  return 0;
}

int MIDIConnectorAttachToDeviceIn( struct MIDIConnector * connector, struct MIDIDevice * device ) {
  return MIDIConnectorAttachTargetWithDelegate( connector, device,
                                                &MIDIDeviceInConnectorDelegate );
}

int MIDIConnectorAttachToDriver( struct MIDIConnector * connector, struct MIDIDriver * driver ) {
  return MIDIConnectorAttachTargetWithDelegate( connector, driver,
                                                &MIDIDriverSendConnectorDelegate );
}

int MIDIConnectorAttachFromDeviceOut( struct MIDIConnector * connector, struct MIDIDevice * device ) {
  return MIDIConnectorAttachSourceWithDelegate( connector, device,
                                                &MIDIDeviceOutConnectorDelegate );
}

int MIDIConnectorAttachFromDeviceThru( struct MIDIConnector * connector, struct MIDIDevice * device ) {
  return MIDIConnectorAttachSourceWithDelegate( connector, device,
                                                &MIDIDeviceThruConnectorDelegate );
}

int MIDIConnectorAttachFromDriver( struct MIDIConnector * connector, struct MIDIDriver * driver ) {
  return MIDIConnectorAttachSourceWithDelegate( connector, driver,
                                                &MIDIDriverReceiveConnectorDelegate );
}

int MIDIConnectorRelay( struct MIDIConnector * connector, struct MIDIMessage * message ) {
  if( connector->target == NULL ||
      connector->target_delegate == NULL ||
      connector->target_delegate->relay == NULL )
    return 1;
  return (connector->target_delegate->relay)( connector->target, message );
}