#include "Arduino.h"
#include <EEPROM.h>
#include "eeprom.h"

#include "../config.h"

void eeprom_save_endpoints(float *endpoints) {
    EEPROM.put(0, endpoints);
}

void eeprom_get_endpoints(float *endpoints) {
    float eeprom_endpoints[3];
    EEPROM.get(0, eeprom_endpoints);

    // check if eeprom data is valid
    if (eeprom_endpoints[0] < 500 || eeprom_endpoints[0] > 2500 || isnan(eeprom_endpoints[0])) {
        eeprom_save_endpoints(endpoints);
        return;
    }

    memcpy(endpoints, eeprom_endpoints, sizeof(eeprom_endpoints));
}