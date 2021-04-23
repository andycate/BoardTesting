#include <Arduino.h>
#include <Wire.h>

#include <Adafruit_MCP9600.h>

Adafruit_MCP9600 mcp1;
Adafruit_MCP9600 mcp2;
Adafruit_MCP9600 mcp3;
Adafruit_MCP9600 mcp4;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(57600);
  while(!Serial);
  Serial.println("BEGIN");

  Wire.begin();

  if(!mcp1.begin(0x60)) {
    Serial.println("0x60 Sensor not found");
  }
  if(!mcp2.begin(0x61)) {
    Serial.println("0x61 Sensor not found");
  }
  if(!mcp3.begin(0x62)) {
    Serial.println("0x62 Sensor not found");
  }
  if(!mcp4.begin(0x63)) {
    Serial.println("0x63 Sensor not found");
  }

  /* START SET I2C CLOCK FREQ */
  // Wire.setClock(85000);
  #define CLOCK_STRETCH_TIMEOUT 15000
  IMXRT_LPI2C_t *port = &IMXRT_LPI2C1;
  port->MCCR0 = LPI2C_MCCR0_CLKHI(55) | LPI2C_MCCR0_CLKLO(59) |
    LPI2C_MCCR0_DATAVD(25) | LPI2C_MCCR0_SETHOLD(40);
  port->MCFGR1 = LPI2C_MCFGR1_PRESCALE(2);
  port->MCFGR2 = LPI2C_MCFGR2_FILTSDA(5) | LPI2C_MCFGR2_FILTSCL(5) |
    LPI2C_MCFGR2_BUSIDLE(3000); // idle timeout 250 us
  port->MCFGR3 = LPI2C_MCFGR3_PINLOW(CLOCK_STRETCH_TIMEOUT * 12 / 256 + 1);

  port->MCCR1 = port->MCCR0;
	port->MCFGR0 = 0;
	port->MFCR = LPI2C_MFCR_RXWATER(1) | LPI2C_MFCR_TXWATER(1);
	port->MCR = LPI2C_MCR_MEN;
  /* END SET I2C CLOCK FREQ */

  mcp1.setADCresolution(MCP9600_ADCRESOLUTION_18);
  mcp1.setThermocoupleType(MCP9600_TYPE_K);
  mcp1.setFilterCoefficient(0);
  mcp1.enable(true);

  mcp2.setADCresolution(MCP9600_ADCRESOLUTION_18);
  mcp2.setThermocoupleType(MCP9600_TYPE_K);
  mcp2.setFilterCoefficient(0);
  mcp2.enable(true);

  mcp3.setADCresolution(MCP9600_ADCRESOLUTION_18);
  mcp3.setThermocoupleType(MCP9600_TYPE_K);
  mcp3.setFilterCoefficient(0);
  mcp3.enable(true);

  mcp4.setADCresolution(MCP9600_ADCRESOLUTION_18);
  mcp4.setThermocoupleType(MCP9600_TYPE_K);
  mcp4.setFilterCoefficient(0);
  mcp4.enable(true);
}

void loop() {
  // put your main code here, to run repeatedly:
  Serial.print(mcp1.readThermocouple());
  Serial.print(",");
  Serial.print(mcp2.readThermocouple());
  Serial.print(",");
  Serial.print(mcp3.readThermocouple());
  Serial.print(",");
  Serial.print(mcp4.readThermocouple());
  Serial.println();
  delay(50);
}
