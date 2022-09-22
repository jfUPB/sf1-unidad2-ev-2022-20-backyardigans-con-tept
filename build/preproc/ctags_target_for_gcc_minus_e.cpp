# 1 "/home/fercosmiking/sf1-unidad2-ev-2022-20-backyardigans-con-tept/SimpleProject.ino"
String btnState(uint8_t btnState){
  if(btnState == 0x1){
    return "OFF";
  }
  else return "ON";
}

void task()
{
  enum class TaskStates
  {
    INIT,
    WAIT_COMMANDS
  };
  static TaskStates taskState = TaskStates::INIT;
  constexpr uint8_t ledBlue = 26;
  constexpr uint8_t ledYellow = 27;
  constexpr uint8_t ledGreen = 25;
  constexpr uint8_t button1Pin = 12;
  constexpr uint8_t button2Pin = 33;
  constexpr uint8_t button3Pin = 32;


  switch (taskState)
  {
  case TaskStates::INIT:
  {
    Serial.begin(115200);
    pinMode(ledBlue, 0x03);
    pinMode(ledYellow, 0x03);
    pinMode(ledGreen, 0x03);
    digitalWrite(ledBlue, 0x0);
    digitalWrite(ledYellow, 0x0);
    digitalWrite(ledGreen, 0x0);
    pinMode(button1Pin, 0x05);
    pinMode(button2Pin, 0x05);
    pinMode(button3Pin, 0x05);
    taskState = TaskStates::WAIT_COMMANDS;
    break;
  }
  case TaskStates::WAIT_COMMANDS:
  {
    if (Serial.available() > 0)
    {
      String command = Serial.readStringUntil('\n');

        if (command == "led1ON")
        {
            digitalWrite(ledYellow, 0x1);
        }
        else if (command == "led1OFF")
        {
            digitalWrite(ledYellow, 0x0);
        }

        if (command == "led2ON")
        {
            digitalWrite(ledBlue, 0x1);
        }
        else if (command == "led2OFF")
        {
            digitalWrite(ledBlue, 0x0);
        }

        if (command == "led3ON")
        {
            digitalWrite(ledGreen, 0x1);
        }
        else if (command == "led3OFF")
        {
            digitalWrite(ledGreen, 0x0);
        }

        if (command = "readBUTTONS")
        {
        //Serial.print(" btn1: ");
        Serial.print(btnState(digitalRead(button1Pin)).c_str());
        //Serial.print(" btn2: ");
        Serial.print(btnState(digitalRead(button2Pin)).c_str());
        //Serial.print(" btn3: ");
        Serial.print(btnState(digitalRead(button3Pin)).c_str());
        Serial.print('\n');
      }
    }
    break;
  }
  default:
  {
    break;
  }
  }
}


void setup()
{
  task();
}

void loop()
{
  task();
}
