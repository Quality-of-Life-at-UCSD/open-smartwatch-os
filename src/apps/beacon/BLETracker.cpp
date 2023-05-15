#include "./apps/beacon/BLETracker.h"

#include <string>
#include <vector>
#include <BLEDevice.h>



BLETracker::BLETracker() {
    BLEDevice::init("Open Smartwatch");
}
BLETracker::~BLETracker()
{
    for(Device* device : this->devices)
        delete device;
}

void BLETracker::pair(BLEAddress address)
{
    this->devices.push_back(new Device(address));
}
bool BLETracker::unpair(BLEAddress address)
{
    for(auto ite = this->devices.cbegin(); ite != this->devices.cend(); ite++)
        if((*ite)->client->getPeerAddress().equals(address))
        {
            delete *ite;
            this->devices.erase(ite);
            return true;
        }
    return false;
}
int BLETracker::getNumberOfDevices()
{
    return this->devices.size();
}
int32_t BLETracker::getAvgRssi(BLEAddress address)
{
    for(Device* device : this->devices)
        if(device->client->getPeerAddress().equals(address))
            return device->rssis.avg();
    return 0;
}

void BLETracker::ping()
{
    for(Device* device : this->devices)
        device->ping();
}
void BLETracker::ping(BLEAddress address)
{
    for(Device* device : this->devices)
        if(device->client->getPeerAddress().equals(address))
        {
            device->ping();
            return;
        }
}
void BLETracker::ring(BLEAddress address)
{
    for(Device* device : this->devices)
        if(device->client->getPeerAddress().equals(address))
        {
            device->ring();
            return;
        }
}
void BLETracker::tick()
{
    for(Device* device : this->devices)
        device->tick();
}