// SPDX-License-Identifier: Apache-2.0

#ifndef EDM4NA64_TEST_WRITE_EVENTS_H
#define EDM4NA64_TEST_WRITE_EVENTS_H

// Data model
#include "edm4na64/EventCollection.h"
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

  //auto events = edm4na64::EventCollection();
  // =============== event loop ================================
  for (unsigned i = 0; i < nevents; ++i) {
    auto eframe = podio::Frame();
    auto events = edm4na64::EventCollection();
    
    std::cout << " --- processing event " << i << std::endl;

    auto event = events.create();
    event.setId(i);
    event.setTrigger(2026);
    event.setEvType(0x200);   
     
    int randomHits = std::rand() % 13;
    auto raw_hits = edm4na64::CaloHitCollection();
    for (unsigned j = 0; j < randomHits; ++j) {
      
      auto raw_hit = raw_hits.create();
      raw_hit.setId(j);
      raw_hit.setEDep(10*j);
      raw_hit.setEDepError(1.23);
      raw_hit.setTime(125497);
      raw_hit.setTimeStddev(1214.2);
      event.addToCaloHits(raw_hit);
    }

    

    //-------- print hits for debugging:
    std::cout << "\n Event " << i
              << " of type " << events.getValueTypeName() << "\n\n"
              << events << " Hits \n" << raw_hits << std::endl;

    eframe.put(std::move(events), "Events");
    eframe.put(std::move(raw_hits), "CaloHits");
    eframe.putParameter("EventType", "test");
    writer.writeFrame(eframe, "events");
    
    //===============================================================================

  }
  //eframe.put(std::move(events), "Events");
  //eframe.putParameter("EventType", "test");
  //writer.writeFrame(eframe, "events");

  writer.finish();
}

#endif
