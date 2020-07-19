#include "Collection/Sensors.h"

#include "Global.h"
#include "PrintMessage.h"

const static char* MODULE = "Sensors";

namespace Sensors {

std::vector<BaseSensor*> _items;

BaseSensor* last() {
    return _items.at(_items.size() - 1);
}

BaseSensor* add(SensorType_t type, const String& name, const String& assign) {
    BaseSensor* item;
    switch (type) {
        case SENSOR_ADC:
            item = new AnalogSensor{name, assign};
            break;
        case SENSOR_DALLAS:
            item = new DallasSensor{name, assign};
            break;
        default:
            break;
    }

    _items.push_back(item);
    return last();
}

void update() {
    for (BaseSensor* item : _items) {
        String name = item->getName();

        if (item->hasValue()) {
            String value = item->getValue();
            runtime.write(name, value, item->getValueType());
        }
    }
}
}  // namespace Sensors