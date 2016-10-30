#include <MicroBit.h>
#include "CalliopeDemo.h"

extern MicroBit uBit;

void onButtonA(MicroBitEvent event) { uBit.display.print("A"); }
void onButtonB(MicroBitEvent event) { uBit.display.print("B"); }
void onButtonAB(MicroBitEvent event) { uBit.display.print("A+B"); }
void onButton0(MicroBitEvent event) { uBit.display.print("0"); }
void onButton1(MicroBitEvent event) { uBit.display.print("1"); }
void onButton2(MicroBitEvent event) { uBit.display.print("2"); }
void onButton3(MicroBitEvent event) { uBit.display.print("3"); }

void onShake(MicroBitEvent event) { uBit.display.print("S"); }
void onFaceUp(MicroBitEvent event) { uBit.display.print("+"); }
void onFaceDown(MicroBitEvent event) { uBit.display.print("-"); }
void onTiltUp(MicroBitEvent event) { uBit.display.print("U"); }
void onTiltDown(MicroBitEvent event) { uBit.display.print("D"); }
void onTiltLeft(MicroBitEvent event) { uBit.display.print("L"); }
void onTiltRight(MicroBitEvent event) { uBit.display.print("R"); }

void testBoard() {
    KeyValuePair *firstTime = uBit.storage.get("initial");

    if (firstTime != NULL) return;
    uint8_t done = 1;
    uBit.storage.put("initial", &done, sizeof(int));

    uBit.serial.send("display\r\n");
    uBit.display.clear();
    uBit.display.print(Full);
    for (int i = 255; i > 0; i -= 2) {
        uBit.display.setBrightness(i);
        uBit.sleep(3);
    }
    uBit.sleep(3);
    for (int i = 0; i < 255; i += 2) {
        uBit.display.setBrightness(i);
        uBit.sleep(3);
    }

    uBit.serial.send("accelerometer\r\n");
    for (int i = 0; i < 10; i++) {
        uBit.accelerometer.getX();
        uBit.accelerometer.getY();
        uBit.accelerometer.getZ();
    }
    uBit.display.print(Tick);
    uBit.sleep(80);

    uBit.serial.send("RGB led\r\n");
    uBit.rgb.off();
    uBit.rgb.setColour(255, 0, 0, 0);
    uBit.sleep(100);
    uBit.rgb.off();
    uBit.rgb.setColour(0, 255, 0, 0);
    uBit.sleep(100);
    uBit.rgb.off();
    uBit.rgb.setColour(0, 0, 255, 0);
    uBit.sleep(100);
    uBit.rgb.off();


    uBit.serial.send("sound\r\n");
    uBit.soundmotor.setSoundSilentMode(true);
    uBit.soundmotor.soundOn(500);
    uBit.sleep(100);
    uBit.soundmotor.soundOn(2000);
    uBit.sleep(100);
    uBit.soundmotor.soundOn(3000);
    uBit.sleep(100);
    uBit.soundmotor.soundOff();

    uBit.display.clear();

    // we need to trigger touch sensing
    uBit.io.P0.isTouched();
    uBit.io.P1.isTouched();
    uBit.io.P2.isTouched();
    uBit.io.CAL_P22.isTouched();

    uBit.messageBus.listen(MICROBIT_ID_BUTTON_A, MICROBIT_BUTTON_EVT_CLICK, onButtonA);
    uBit.messageBus.listen(MICROBIT_ID_BUTTON_B, MICROBIT_BUTTON_EVT_CLICK, onButtonB);
    uBit.messageBus.listen(MICROBIT_ID_BUTTON_AB, MICROBIT_BUTTON_EVT_CLICK, onButtonAB);
    uBit.messageBus.listen(MICROBIT_ID_IO_P0, MICROBIT_EVT_ANY, onButton0);
    uBit.messageBus.listen(MICROBIT_ID_IO_P1, MICROBIT_EVT_ANY, onButton1);
    uBit.messageBus.listen(MICROBIT_ID_IO_P2, MICROBIT_EVT_ANY, onButton2);
    uBit.messageBus.listen(CALLIOPE_ID_IO_P22, MICROBIT_EVT_ANY, onButton3);

    uBit.messageBus.listen(MICROBIT_ID_GESTURE, MICROBIT_ACCELEROMETER_EVT_SHAKE, onShake);
    uBit.messageBus.listen(MICROBIT_ID_GESTURE, MICROBIT_ACCELEROMETER_EVT_FACE_UP, onFaceUp);
    uBit.messageBus.listen(MICROBIT_ID_GESTURE, MICROBIT_ACCELEROMETER_EVT_FACE_DOWN, onFaceDown);
    uBit.messageBus.listen(MICROBIT_ID_GESTURE, MICROBIT_ACCELEROMETER_EVT_TILT_UP, onTiltUp);
    uBit.messageBus.listen(MICROBIT_ID_GESTURE, MICROBIT_ACCELEROMETER_EVT_TILT_DOWN, onTiltDown);
    uBit.messageBus.listen(MICROBIT_ID_GESTURE, MICROBIT_ACCELEROMETER_EVT_TILT_LEFT, onTiltLeft);
    uBit.messageBus.listen(MICROBIT_ID_GESTURE, MICROBIT_ACCELEROMETER_EVT_TILT_RIGHT, onTiltRight);

    while (1) uBit.sleep(100);
}