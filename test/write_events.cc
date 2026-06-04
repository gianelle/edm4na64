// SPDX-License-Identifier: Apache-2.0

#include "write_events.h"

#include <podio/podioVersion.h>
#if PODIO_BUILD_VERSION >= PODIO_VERSION(0, 99, 0)
#include <podio/ROOTWriter.h>
#include <podio/SIOWriter.h>
#include <podio/RNTupleWriter.h>
#else
#include <podio/ROOTFrameWriter.h>
#endif

int main(int argc, char *argv[]) {

  write<podio::ROOTWriter>("edm4na64_events.root");
//  write<podio::RNTupleWriter>("edm4na64_eventsRNT.root");
//  write<podio::SIOWriter>("edm4na64_events.sio");

}

