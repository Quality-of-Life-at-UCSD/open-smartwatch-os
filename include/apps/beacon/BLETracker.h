#ifndef OSW_APP_BLEBEACON_H
#define OSW_APP_BLEBEACON_H

#include <string>
#include <vector>

#include <BLEClient.h>
#include <BLEDevice.h>

class BLETracker {
    private:
        class CircularArray {
            private:
                int size;
                int32_t* data;
                int ind;
            public:
                CircularArray(int size) : size(size), data(new int32_t[size]), ind(0)
                {}
                ~CircularArray()
                {
                    delete data;
                }
                void add(int32_t n)
                {
                    data[ind++] = n;
                    if(ind == size)
                        ind = 0;
                }
                int32_t get(int ind)
                {
                    return data[ind];
                }
                int32_t sum()
                {
                    int32_t sum = 0;
                    for(int i = 0; i < size; i++)
                        sum += data[i];
                    return sum;
                }
                int32_t avg()
                {
                    return sum()/size;
                }
        };
        typedef struct device {
            BLEAddress address;
            BLEClient* client;
            CircularArray rssis;
            device(BLEAddress address) : address(address), rssis(CircularArray(10)) {
                client = BLEDevice::createClient();
            };
            ~device()
            {
                if(!client->isConnected())
                    client->disconnect();
                delete client;
            };
            void tick()
            {
                if(!client->isConnected())
                    client->connect(address, BLE_ADDR_TYPE_PUBLIC);
            };
            void ping()
            {
                if(client->isConnected())
                    rssis.add(client->getRssi());
            };
            void ring()
            {

            }
        } Device;

        std::vector<Device*> devices;
    public:
        BLETracker();
        ~BLETracker();

        void pair(BLEAddress address);
        bool unpair(BLEAddress address);
        int getNumberOfDevices();
        BLEAddress** getDevices();
        int32_t getAvgRssi(BLEAddress address);

        void ping();
        void ping(BLEAddress address);
        void ring(BLEAddress address);
        void tick();
};
#endif