#include "Messages.h"

#include "Global.h"
#include "Consts.h"
#include "Config.h"
#include "Broadcast.h"
#include "Devices.h"
#include "NetworkManager.h"
#include "Utils/SysUtils.h"

static const char* MODULE = "Messages";

namespace Messages {

void loop() {
    if (!Broadcast::received()->available()) {
        return;
    }
    process(Broadcast::received());
}

// TODO Очередь отправки
void announce() {
    String data;
    data += getChipId();
    data += ";";
    data += config.general()->getBroadcastName();
    data += ";";
    data += NetworkManager::getHostIP().toString();
    data += ";";

    Broadcast::send(HEADER_ANNOUNCE, data);
}

String getValue(const String& data, char separator, size_t index) {
    size_t found = 0;
    int strIndex[] = {0, -1};
    size_t maxIndex = data.length() - 1;

    for (size_t i = 0; i <= maxIndex && found <= index; i++) {
        if (data.charAt(i) == separator || i == maxIndex) {
            found++;
            strIndex[0] = strIndex[1] + 1;
            strIndex[1] = (i == maxIndex) ? i + 1 : i;
        }
    }

    return found > index ? data.substring(strIndex[0], strIndex[1]) : "";
}

void process(StringQueue* queue) {
    String buf;
    queue->pop(buf);
    if (getValue(buf, ';', 0).equals(HEADER_ANNOUNCE)) {
        Devices::add(getValue(buf, ';', 1).c_str(), getValue(buf, ';', 2).c_str(), getValue(buf, ';', 3).c_str());
    } else if (getValue(buf, ';', 0).equals(HEADER_MQTT_SETTINGS)) {
        config.mqtt()->loadString(getValue(buf, ';', 1).c_str());
        perform_mqtt_restart_flag = true;
    } else {
        pm.error("unknown");
    }
}

}  // namespace Messages
