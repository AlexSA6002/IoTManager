#pragma once

#include <Arduino.h>

#include <OneWire.h>

#include "OneWireScanner.h"
#include "Utils/StringUtils.h"

class OneWireAddress {
   public:
    OneWireAddress(uint8_t* addr_ptr) {
        memcpy(&_addr[0], addr_ptr, sizeof(_addr[0]) * 8);
    }

    OneWireAddress(const String& addr) {
        for (size_t i = 0; i < 8; i++) {
            String b = addr.substring(i * 2, (i * 2) + 2);
            _addr[i] = decodeHex(b[0]) * 16 + decodeHex(b[1]);
        }
    }

    uint8_t at(size_t index) {
        return _addr[index];
    }

    const uint8_t* get() {
        return &_addr[0];
    }

    const String asString() {
        String res = "";
        for (size_t i = 0; i < 8; i++) {
            if (_addr[i] < 0x10) {
                res += '0';
            }
            res += String(_addr[i], HEX);
        }
        return res;
    }

    bool equals(const uint8_t* addr_ptr) const {
        uint8_t i = 0;
        while (_addr[i] != *(addr_ptr + i)) {
            if (++i == 8) return false;
        }
        return true;
    }

   private:
    uint8_t _addr[8];
};

class OneBusItem {
   public:
    OneBusItem(uint8_t* addr_ptr, const String& desc) : _addr{addr_ptr} {
        _desc = strdup(desc.c_str());
    }

    ~OneBusItem() {
        free(_desc);
    }

    const bool equals(uint8_t* addr_ptr) {
        return _addr.equals(addr_ptr);
    }

    OneWireAddress* getAddress() {
        return &_addr;
    }

    const String getAddUrl() {
        String res;
        String addr = _addr.asString();
        res += "<a href='/config?add=";
        res += addr;
        res += "'>";
        res += addr;
        res += "</a>";
        return res;
    }

   private:
    OneWireAddress _addr;
    char* _desc;
};

const String getFamily(uint8_t family);

class OneWireBus {
   public:
    OneWireBus();
    ~OneWireBus();
    bool attached();
    void attach(uint8_t pin);
    OneWire* get();
    void addItem(uint8_t addr[8]);
    const String asJson();

   private:
    OneWire* _bus;
    std::vector<OneBusItem*> _items;
};

extern OneWireBus oneWire;
