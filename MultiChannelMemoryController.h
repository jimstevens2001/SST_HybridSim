#ifndef MULTICHANNELMEMORYCONTROLLER_H
#define MULTICHANNELMEMORYCONTROLLER_H

#include "Callback.h"
#include <string>
using std::string;

#include "HybridSim.h"

namespace DRAMSim 
{

	class MultiChannelMemorySystem {
		public: 
			MultiChannelMemorySystem(const string &dev, const string &sys, const string &pwd, const string &trc, unsigned megsOfMemory);

			bool addTransaction(bool isWrite, uint64_t addr);

			void update();
			void printStats();
			bool willAcceptTransaction(); 
			bool willAcceptTransaction(uint64_t addr); 

			void RegisterCallbacks( 
				TransactionCompleteCB *readDone,
				TransactionCompleteCB *writeDone,
				void (*reportPower)(double bgpower, double burstpower, double refreshpower, double actprepower));
		private:
			HybridSim::HybridSystem *hs;

			typedef HybridSim::CallbackBase<void,uint,uint64_t,uint64_t> Callback_t;
			Callback_t *read_cb;
			Callback_t *write_cb;

			void read_complete(uint id, uint64_t addr, uint64_t cycle);
			void write_complete(uint, uint64_t addr, uint64_t cycle);

			TransactionCompleteCB *ReadDone;
			TransactionCompleteCB *WriteDone;
	};
	MultiChannelMemorySystem *getMemorySystemInstance(const string &dev, const string &sys, const string &pwd, const string &trc, unsigned megsOfMemory);
}

#endif

