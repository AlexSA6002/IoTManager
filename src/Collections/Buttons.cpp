#include "Collection/Buttons.h"

#include "StringConsts.h"

#include "PrintMessage.h"

static const char* MODULE = TAG_BUTTON;

Buttons buttons;

Button* Buttons::add(const ButtonType_t type, const String& name, const String& assign, const String& value, const String& inverted) {
    Button* item;

    switch (type) {
        case BUTTON_VIRTUAL:
            item = new VirtualButton(name, assign);
            break;
        case BUTTON_GPIO:
            item = new PinButton(name, assign);
            break;
        case BUTTON_SCEN:
            item = new ScenButton(name, assign);
            break;
        case BUTTON_SCEN_LINE:
            // String str = assign;
            // while (str.length()) {
            //     if (str == "") {
            //         return;
            //     }
            //     //line1,
            //     String tmp = selectToMarker(str, ",");
            //     //1,
            //     String number = deleteBeforeDelimiter(tmp, "e");
            //     number.replace(",", "");
            //     int number_int = number.toInt();

            //     Scenario::enableBlock(number_int, state);
            //     str = deleteBeforeDelimiter(str, ",");
            // }
            break;
    }

    item->setInverted(inverted.toInt());
    item->setValue(value);

    _list.push_back(item);
    return last();
}

Button* Buttons::last() {
    return _list.at(_list.size() - 1);
}

Button* Buttons::get(const String name) {
    for (auto item : _list) {
        if (name.equals(item->getName())) {
            return item;
        }
    }
    return NULL;
}

Button* Buttons::at(size_t num) {
    return _list.at(num);
}

size_t Buttons::count() {
    return _list.size();
}
