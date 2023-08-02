#ifndef RELAYS_H
#define RELAYS_H

#define RELAY_KALORIFER_GPIO 4

void StartRelay(unsigned int duration);
void StopRelay();

void SetupRelays();
void loopRelays();

#endif