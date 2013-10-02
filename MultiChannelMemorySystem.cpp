#include <stdint.h>

#include "MultiChannelMemorySystem.h"

namespace SST_HybridSim
{

MultiChannelMemorySystem::MultiChannelMemorySystem(const string &dev, const string &sys, const string &pwd, const string &trc, unsigned megsOfMemory)
{
	//hs = new HybridSim::HybridSystem(1, "");
	hs = HybridSim::getMemorySystemInstance(1, "");

	read_cb = new HybridSim::Callback<MultiChannelMemorySystem, void, uint, uint64_t, uint64_t>(this, &MultiChannelMemorySystem::read_complete);
	write_cb = new HybridSim::Callback<MultiChannelMemorySystem, void, uint, uint64_t, uint64_t>(this, &MultiChannelMemorySystem::write_complete);
	hs->RegisterCallbacks(read_cb, write_cb);

	this->ReadDone = NULL;
	this->WriteDone = NULL;
}

bool MultiChannelMemorySystem::addTransaction(bool isWrite, uint64_t addr)
{
	return hs->addTransaction(isWrite, addr);
}

void MultiChannelMemorySystem::update()
{
	hs->update();
}

void MultiChannelMemorySystem::printStats()
{
	// TODO: Confirm printState() is only called at the end of simulation.
	hs->printLogfile();
}

bool MultiChannelMemorySystem::willAcceptTransaction()
{
	return hs->WillAcceptTransaction();
}

bool MultiChannelMemorySystem::willAcceptTransaction(uint64_t addr)
{
	// There is no special version for addresses in hybridsim.
	return hs->WillAcceptTransaction();
}

void MultiChannelMemorySystem::RegisterCallbacks( TransactionCompleteCB *readDone, TransactionCompleteCB *writeDone,
	void (*reportPower)(double bgpower, double burstpower, double refreshpower, double actprepower))
{
	this->ReadDone = readDone;
	this->WriteDone = writeDone;

	// Ignoring the power callback for now.
}

void MultiChannelMemorySystem::read_complete(uint id, uint64_t addr, uint64_t cycle)
{
	if (ReadDone)
	{
		(*ReadDone)(id, addr, cycle);
	}
}

void MultiChannelMemorySystem::write_complete(uint id, uint64_t addr, uint64_t cycle)
{
	if (WriteDone)
	{
		(*WriteDone)(id, addr, cycle);
	}
}

MultiChannelMemorySystem *getMemorySystemInstance(const string &dev, const string &sys, const string &pwd, const string &trc, unsigned megsOfMemory)
{
	return new MultiChannelMemorySystem(dev, sys, pwd, trc, megsOfMemory);
}

}

