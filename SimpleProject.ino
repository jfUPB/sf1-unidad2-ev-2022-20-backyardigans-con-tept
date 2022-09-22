String btnState(uint8_t btnState){
  if(btnState == HIGH){
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
    pinMode(ledBlue, OUTPUT);
    pinMode(ledYellow, OUTPUT);
    pinMode(ledGreen, OUTPUT);
    digitalWrite(ledBlue, LOW);
    digitalWrite(ledYellow, LOW);
    digitalWrite(ledGreen, LOW);
    pinMode(button1Pin, INPUT_PULLUP);
    pinMode(button2Pin, INPUT_PULLUP);
    pinMode(button3Pin, INPUT_PULLUP);
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
            digitalWrite(ledYellow, HIGH);
        }
        else if (command == "led1OFF")
        {
            digitalWrite(ledYellow, LOW);
        }

        if (command == "led2ON") 
        {
            digitalWrite(ledBlue, HIGH);
        }
        else if (command == "led2OFF")
        {
            digitalWrite(ledBlue, LOW);
        }

        if (command == "led3ON") 
        {
            digitalWrite(ledGreen, HIGH);
        }
        else if (command == "led3OFF")
        {
            digitalWrite(ledGreen, LOW);
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

