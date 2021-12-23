/*#define N 12

int buttonPins[N];
int ledPins[N];
bool states[N];
bool ledLightup[N];
String purposeList[N] = { "MKS管理",
                          "討論/讀書/來坐坐",
                          "零星使用",
                          "物品寄放",
                          "部課/沙龍/部聚",
                          "課程/專題",
                          "比賽",
                          "校務",
                          "系上活動",
                          "學術部",
                          "個人/其他"
                         };
*/

int buttonPins[12] = {3, 5, 7, 9, 11, 31, 15, 17, 19, 21, 23, 25};
int ledPins[12] = {24, 22, 20, 18, 16, 14, 12, 10, 8, 6, 4, 2};//{2, 4, 6, 8, 10, 12, 14, 16, 18, 20, 22, 24};
bool states[12] = {true};
bool ledLightup[12] = {false};
String purposeList[12] = {
    "MKS管理",
    "討論/讀書/來坐坐",
    "零星使用",
    "物品寄放",
    "部課/沙龍/部聚",
    "其他",
    "課程/專題",
    "比賽",
    "校務",
    "系上活動",
    "學術部",
    "個人/其他"
};

void reset() {
    for (int i = 0; i < 12; ++i) {
        states[i] = true;
        ledLightup[i] = false;
    }
}
void setPins() {
    for (int i = 0; i < 12; ++i) {
        pinMode(buttonPins[i], INPUT);
        pinMode(ledPins[i], OUTPUT);
    }
}

void update() {
    for(int i = 0; i < 12; ++i) {
        if (digitalRead(buttonPins[i])) {
            if (!states[i]) {
                //Serial.println(String(i+1) + "_up");
                states[i] = true;
            }
        }
        else {
            if (states[i]) {
                //Serial.println(String(i+1) + "_down");
                ledLightup[i] = !ledLightup[i];
                states[i] = false;
            }
        }
        digitalWrite(ledPins[i], ledLightup[i]);
    }
}
