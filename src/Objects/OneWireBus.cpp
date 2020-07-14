#include "Sensors/OneWireBus.h"

OneWireBus onewire;

const String getFamily(uint8_t family) {
    String res;
    switch (family) {
        case 0x10:
            res = F("DS1820(S)");
            break;
        case 0x28:
            res = F("DS18B20");
            break;
        case 0x22:
            res = F("DS1822");
            break;
        case 0x3B:
            res = F("DS1825");
            break;
        case 0x42:
            res = F("DS28EA00");
            break;
        default:
            res = F("-");
    }
    return res;
};

OneWireBus::OneWireBus() : _pin{0}, _bus{nullptr} {};

OneWireBus::~OneWireBus() {
    delete _bus;
}

void OneWireBus::addItem(uint8_t addr[8]) {
    for (size_t i = 0; i < _items.size(); i++) {
        OneBusItem* item = &_items.at(i);
        if (item->equals(addr)) {
            return;
        }
    }
    _items.push_back(
        OneBusItem(&addr[0], getFamily(addr[0]).c_str()));
}

const String OneWireBus::asJson() {
    char buf[16];
    String res = "{\"onewire\":[";
    for (size_t i = 0; i < _items.size(); i++) {
        OneBusItem* item = &_items.at(i);
        res += "{\"num\":";
        res += itoa(i + 1, buf, DEC);
        res += ",\"url\":\"";
        res += item->getAddUrl();
        res += "\"";
        res += ",\"family\":\"";
        res += getFamily(item->getAddress().at(0));
        res += "\"";
        res += i < _items.size() - 1 ? "}," : "}";
    }
    res += "]}";
    return res;
};

OneWire* OneWireBus::get() {
    return _bus;
}

bool OneWireBus::attached() {
    return _bus != nullptr;
}

void OneWireBus::attach(uint8_t pin) {
    if (_bus) {
        delete _bus;
    }
    _bus = new OneWire(pin);
}
