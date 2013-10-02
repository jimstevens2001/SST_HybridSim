#include "SST_HybridSim.h"

int main()
{
	SST_HybridSim::MultiChannelMemorySystem *ds = SST_HybridSim::getMemorySystemInstance("", "", "", "", 0);
	ds->update();

	return 0;
}
