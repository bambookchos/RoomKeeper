#include "filter_row.h"


void Filter_row::sendMe(int value) {
   emit me(this, value);
}

void Filter_row::sendDataChanged(int value) {
   emit currentDataChanged(itemData(value).toInt());
}

