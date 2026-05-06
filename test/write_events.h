// SPDX-License-Identifier: Apache-2.0

#ifndef EDM4NA64_TEST_WRITE_EVENTS_H
#define EDM4NA64_TEST_WRITE_EVENTS_H

// Data model
#include "edm4na64/CaloHitCollection.h"

// STL
#include <iostream>
#include <vector>

// podio specific includes
#include "podio/Frame.h"

template <class WriterT>
void write(std::string outfilename) {
  std::cout << "start processing" << std::endl;

  WriterT writer(outfilename);

  unsigned nevents = 10;

  // =============== event loop ================================
  for (unsigned i = 0; i < nevents; ++i) {
    std::cout << " --- processing event " << i << std::endl;
    auto event = podio::Frame();

    auto raw_hits = edm4na64::CaloHitCollection();
    auto raw_hit = raw_hits.create();
    raw_hit.setId(42);
    raw_hit.setEDep(1242.3);
    raw_hit.setEDepError(1.23);
    raw_hit.setTime(125497);
    raw_hit.setTimeStddev(1214.2);

    //-------- print hits for debugging:
    std::cout << "\n collection:  "
              << "CaloHit"
              << " of type " << raw_hits.getValueTypeName() << "\n\n"
              << raw_hits << std::endl;

    event.put(std::move(raw_hits), "CaloHit");

    //===============================================================================

    event.putParameter("EventType", "test");

    writer.writeFrame(event, "events");
  }

  writer.finish();
}

#endif
