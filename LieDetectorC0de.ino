// lle_detector_codeDRAFT_copy_20231029005049_copy_20231029183022.ino

void setup(){
    pinMode(redLED,OUTPUT);
    pinMode(greenLED,OUTPUT);
    pinMode(yellowLED,OUTPUT);

    lcd.init();
    lcd.backlight();
    lcd.print("  Lie Detector");
    delay(2000);

    lcd.clear();
    lcd.setCursor(0,0);
    delay(2000);
    lcd.print("Green LED");
    digitalWrite(greenLED,HIGH);
    delay(2000);
    lcd.setCursor(0,1);
    lcd.print("No Change");
    delay(3000);
    digitalWrite(greenLED,LOW);

    lcd.clear();
    lcd.setCursor(0,0);
    delay(2000);
    lcd.print("Red LED");
    digitalWrite(redLED,HIGH);
    delay(2000);
    lcd.setCursor(0,1);
    lcd.print("GSR Change");
    delay(3000);
    digitalWrite(redLED,LOW);

    //calibrating the baseline GSR reading (threshold)
    for(int i=0;i<100;i++)
    {
        sensorValue=analogRead(GSR);
        sum += sensorValue;
        delay(100);
    }
    threshold = sum/100;
    Serial.print("threshold ==");
    Serial.println(threshold);

    lcd.clear();
    lcd.setCursor(0,0);
    lcd.print("GSR Threshold!");
    lcd.setCursor(0,1);
    lcd.print("    ");
    lcd.print(threshold);
    delay(5000);

    lcd.clear();
    lcd.setCursor(0,0);
    lcd.print("IR Threshold!");
    lcd.setCursor(0,1);
    lcd.print(particleSensor.getIR());
    delay(5000);

    lcd.clear();
    lcd.setCursor(0,0);
    lcd.print("Analyzing");
    lcd.setCursor(0,1);
    lcd.print("Signals");
}

void loop(){
    digitalWrite(greenLED,HIGH);
    debug.print("IR!");
    debug.print(particleSensor.getIR());
    debug.print("!");
    debug.println();
    int temp;
    sensorValue=analogRead(GSR);
    Serial.print("sensorValue=");
    Serial.println(sensorValue);
    temp = threshold - sensorValue;
    delay(100);

    //delay(5000);

    if(abs(temp) >= 60){
        if(particleSensor.getIR() < 95000){
            lcd.clear();
            lcd.setCursor(0,0);
            lcd.print("Change");
            lcd.setCursor(0,1);
            lcd.print("Detected");
            delay(2000);

            digitalWrite(greenLED,LOW);
            digitalWrite(redLED,HIGH);
            digitalWrite(yellowLED,HIGH);

            Serial.println("GSR & IR change detected");
            delay(2000);

            digitalWrite(greenLED, LOW);
            digitalWrite(redLED,HIGH);
            digitalWrite(yellowLED,HIGH);

            Serial.println("GSR & IR change detected");
            delay(3000);

            long sum=0;
            for(int i=0;i<100;i++)
            {
                sensorValue=analogRead(GSR);
                sum += sensorValue;
                delay(100);
            }
            threshold = sum/100;
            Serial.print("threshold =");
            Serial.println(threshold);

            lcd.clear();
            lcd.setCursor(0,0);
            lcd.print("GSR Threshold:");
            lcd.setCursor(0,1);
            lcd.print(" ... ");
            lcd.print(threshold);
            delay(3000);

            lcd.clear();
            lcd.setCursor(0,0);
            lcd.print("IR Threshold:");
            lcd.setCursor(0,1);
            lcd.print(particleSensor.getIR());
            delay(3000);
        }
    }
}