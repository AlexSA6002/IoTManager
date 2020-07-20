#include "Cmd.h"

#include "Collection/Sensors.h"
#include "Collection/Widgets.h"

// analog adc 0 Аналоговый#вход,#% Датчики any-data 1 1023 1 100 1
void cmd_analog() {
    String name = sCmd.next();
    String pin = sCmd.next();
    String descr = sCmd.next();
    String page = sCmd.next();
    String templat = sCmd.next();

    String in_min = sCmd.next();
    String in_max = sCmd.next();
    String out_min = sCmd.next();
    String out_max = sCmd.next();

    String order = sCmd.next();

    auto *item = (ADCSensor *)Sensors::add(SensorType_t::ADC, name, pin);
    item->setMap(in_min.toInt(), in_max.toInt(), out_min.toInt(), out_max.toInt());

    Widgets::createWidget(descr, page, order, templat, name);
}