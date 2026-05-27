// SPDX-License-Identifier: Apache-2.0

#ifndef EDM4NA64_TEST_READ_EVENTS_H__
#define EDM4NA64_TEST_READ_EVENTS_H__

// test data model
#include "edm4na64/EventCollection.h"
#include "edm4na64/CaloHitCollection.h"

// podio specific includes
#include "podio/Frame.h"
#include "podio/podioVersion.h"

// STL
#include <cassert>
#include <exception>
#include <iostream>
#include <vector>


void processEvent(const podio::Frame& event, unsigned eventNum) {
  auto& evt = event.get<edm4na64::EventCollection>("Events");
  /*
  for (auto i = cluster.Hits_begin(), \
         end = cluster.Hits_end(); i!=end; ++i){
      std::cout << i->energy() << std::endl;
    } 
  auto& raw_hits = <edm4na64::CaloHitCollection>evt[0].getCaloHits();
  */

    std::cout << "Process event: " << evt[0].getId() << " " << std::endl;
    const auto& calo_hits = evt[0].getCaloHits();
    evt.print();
    //-------- print particles for debugging:

    std::cout << "\n Calo collection: " 
              << " has " << calo_hits.size() << " elements"  << std::endl;
    //-------------------------------

   for (auto i = calo_hits.begin(), 
         end = calo_hits.end(); i!=end; ++i){
      std::cout << i->getEDep() << std::endl;
    }
    

    // check a few things (to be completed ...)
    if ( evt[0].getTrigger() != 2026 )
      throw std::runtime_error("wrong Trigger for the event - should be 2026 ");

   /* 
   for (auto i = cluster.Hits_begin(), \
         end = cluster.Hits_end(); i!=end; ++i){
      std::cout << i->energy() << std::endl;
    }
   */
  //===============================================================================

  const auto& evtType = event.getParameter<std::string>("EventType");
#if PODIO_BUILD_VERSION >= PODIO_VERSION(1, 0, 0)
  std::cout << "Event Type: " << evtType.value_or("EventType does not exist in Frame as parameter") << std::endl;
#else
  std::cout << "Event Type: " << evtType.value() << std::endl;
#endif

}

template <typename ReaderT>
void read_events(const std::string& filename) {
  ReaderT reader;
  reader.openFile(filename);

  unsigned nEvents = reader.getEntries("events");
  for (unsigned i = 0; i < nEvents; ++i) {
    std::cout << "reading event " << i << std::endl;
    const auto event = podio::Frame(reader.readNextEntry("events"));
    processEvent(event, i);
  }
}

#endif
