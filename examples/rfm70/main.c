#include <rfm70.h>

RFM70 radio;

void main(void) {

    rfm70_initialize(&radio, 0, 0, 0, 0);

}
