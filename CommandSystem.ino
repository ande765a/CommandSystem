String input = "";
int incomingByte;

int getArgumentCount(String input) {
  int count = 0;
  for(int i = 0; i <= input.length(); i++) {
    if(input.substring(i, i+1) == " " || input.substring(i, i+1) == "\0") {
      count++;
    }
  }
  return count;
}

String getArguments(String input, int index = 0) {
  int count = getArgumentCount(input);
  int lastcount = 0;
  
  String arguments[count];
  int argumentscount = 0;
 
    
  for(int i = 0; i <= input.length(); i++) {
    if(input.substring(i, i+1) == " " || input.substring(i, i+1) == "\0") {
      arguments[argumentscount] = input.substring(lastcount, i);
      argumentscount++;
      lastcount = i+1;
    }
  }
  
  
  return arguments[index];
  //return argumentscount;
}


void setup() {
  Serial.begin(9600);  
  Serial.print("COMMAND: ");
}
void loop() {
  
  
  while(Serial.available() > 0) {
    incomingByte = Serial.read();
    Serial.print(char(incomingByte));
    
    if(incomingByte == 13) {
      Serial.println();
      if(getArguments(input) == "pin") {
        
        
        if(getArgumentCount(input) >= 3 && (getArguments(input, 1) == "LOW" || getArguments(input, 1) == "HIGH")) {
          String pinState = getArguments(input, 1);
          int pinNumb = getArguments(input, 2).toInt();
          int state = (pinState == "HIGH") ? 1 : 0;
          
           
          
          Serial.print("Pin "); Serial.print(pinNumb); Serial.print(" is now: "); Serial.println(pinState);
          
          pinMode(pinNumb, OUTPUT);
          digitalWrite(pinNumb, state); 
        }
        
        
        
      } else if(getArguments(input) == "tone") { //tone [pinNumb] [frequency]
        if(getArgumentCount(input) >= 3) {
          int pinNumb = getArguments(input, 1).toInt();
          
          
          if(getArguments(input, 2) == "none") {
            noTone(pinNumb);
            Serial.print("Tone stopped at pin ");
            Serial.println(pinNumb);
          } else {
            int frequency = getArguments(input, 2).toInt();
            tone(pinNumb, frequency);
            Serial.print("Tone is playing at pin ");
            Serial.print(pinNumb);
            Serial.print(" at ");
            Serial.print(frequency);
            Serial.println("Hz");
          }
          
          
          
        }
      } else {
        Serial.println("Unknown command: " + input);
      }
      input = "";
      Serial.print("COMMAND: ");
    } else if(incomingByte == 127) {
      input = input.substring(0, input.length() - 1);
      Serial.write(8);
      Serial.write(int(' '));
      Serial.write(8);
    } else {
      input += char(incomingByte);
    }
   
    
  }
  
  
}
