int ntc_pin[5]={A0,A1,A2,A3,A4};

#define vd_power_pin 2        // 5V for the voltage divider
#define nominal_resistance 10000       //Nominal resistance at 25⁰C
#define nominal_temeprature 25   // temperature for nominal resistance (almost always 25⁰ C)
#define samplingrate 50    // Number of samples 
#define beta 3380  // The beta coefficient or the B value of the thermistor (us
#define Rref 10000   //Value of  resistor used for the voltage divider
int samples = 0, i, sensors_num = 0;
float temperature, average;

void setup(void)
{
  pinMode(vd_power_pin, OUTPUT);
  pinMode(A0,INPUT);
  pinMode(A1,INPUT);
  pinMode(A2,INPUT);
  pinMode(A3,INPUT);
  pinMode(A4,INPUT);
  Serial.begin(9600);   //initialize serial communication at a baud rate of 9600  
  Serial.print("S1\t\t\tS2\t\t\tS3\t\t\tS4\t\t\tS5");
  Serial.print("\n");
}

void loop(void)
{

  samples = 0,temperature=0;
 
  // take voltage readings from the voltage divider
  digitalWrite(vd_power_pin, HIGH);
  for (i = 0 ; i < 5 ; i++)
  {
    for (int j = 0; j < samplingrate; j++)
    {
      samples += analogRead(ntc_pin[i]);
      delay(10);
    }
    digitalWrite(vd_power_pin, LOW);
    average = 0;
    average = samples / samplingrate;

    // Calculate NTC resistance
    average = 1023 / average - 1;
    average = Rref / average;

    temperature = average / nominal_resistance;     // (R/Ro)
    temperature = log(temperature);                  // ln(R/Ro)
    temperature /= beta;                   // 1/B * ln(R/Ro)
    temperature += 1.0 / (nominal_temeprature + 273.15); // + (1/To)
    temperature = 1.0 / temperature;                 // Invert
    temperature -= 273.15;                         // convert absolute temp to C
   // temperature +=.48;

    Serial.print(temperature);
    Serial.print(" \xC2\xB0"); // shows degree symbol
    Serial.print("C");
    Serial.print("\t\t");
    delay(100);
  }
  Serial.print("\n");

}
