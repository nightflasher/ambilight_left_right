void setup()
{
  SerialUSB.begin(38400);
}

  //arduno
  uint8_t outputs[] = {3, 5, 6, 9, 10, 11};

#define NROUTPUTS (sizeof(outputs))
uint8_t values[NROUTPUTS];

void loop()
{
  WaitForPrefix();

  for (uint8_t i = 0; i < NROUTPUTS; i++)
  {
    while(!SerialUSB.available());
    values[i] = SerialUSB.read();
  }

  for (uint8_t i = 0; i < NROUTPUTS; i++)
    analogWrite(outputs[i], values[i]);
}

//boblightd needs to send 0x55 0xAA before sending the channel bytes
void WaitForPrefix()
{
  uint8_t first = 0, second = 0;
  while (second != 0x55 || first != 0xAA)
  {
    while (!SerialUSB.available());
    second = first;
    first = SerialUSB.read();
  }
}
