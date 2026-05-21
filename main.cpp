#include <iostream>
#include <iomanip>
#include <string>

using namespace std;

const int AIR_QUALITY_LIMIT = 400;
const float MIN_TEMPERATURE = 20.0;
const float MAX_TEMPERATURE = 30.0;

float readDHT11Temperature() { return 25.0; }
float readDHT11Humidity() { return 55.0; }

float readLM35Temperature() { return 24.5; }
float readDS18B20Temperature() { return 25.2; }

bool readRainSensor() { return false; }
bool readMoistureSensor() { return false; }
bool readWaterLevelSensor() { return false; }

int readMQ135() { return 250; }

bool readLDR() { return true; }

int readBMP180Pressure() { return 101325; }
float readBMP180Altitude() { return 45.6; }

bool readWindSensor() { return false; }

void openWindow() {
    cout << "\nWINDOW STATUS : OPEN\n";
}

void closeWindow() {
    cout << "\nWINDOW STATUS : CLOSED\n";
}

struct SensorData {
    float temperature;
    float humidity;

    float backupTemperature1;
    float backupTemperature2;

    bool rain;
    bool moisture;
    bool highWater;

    int airQuality;

    bool sunlight;

    int pressure;
    float altitude;

    bool highWind;
};

SensorData readSensors() {

    SensorData data;

    data.temperature = readDHT11Temperature();
    data.humidity = readDHT11Humidity();

    data.backupTemperature1 = readLM35Temperature();
    data.backupTemperature2 = readDS18B20Temperature();

    data.rain = readRainSensor();
    data.moisture = readMoistureSensor();
    data.highWater = readWaterLevelSensor();

    data.airQuality = readMQ135();

    data.sunlight = readLDR();

    data.pressure = readBMP180Pressure();
    data.altitude = readBMP180Altitude();

    data.highWind = readWindSensor();

    return data;
}

void displayData(const SensorData& data) {

    cout << "\nSENSOR REPORT\n\n";

    cout << fixed << setprecision(1);

    cout << "Temperature : " << data.temperature << " C\n";
    cout << "Humidity    : " << data.humidity << " %\n";

    cout << "Rain        : "
         << (data.rain ? "Detected" : "No Rain") << "\n";

    cout << "Air Quality : "
         << data.airQuality << "\n";

    cout << "Light       : "
         << (data.sunlight ? "Bright" : "Dark") << "\n";

    cout << "Wind        : "
         << (data.highWind ? "High" : "Normal") << "\n";
}

bool shouldOpenWindow(const SensorData& data) {

    float finalTemperature = data.temperature;

    if (finalTemperature <= 0)
        finalTemperature = data.backupTemperature1;

    if (data.rain)
        return false;

    if (data.highWind)
        return false;

    if (data.highWater)
        return false;

    if (data.moisture)
        return false;

    if (data.airQuality > AIR_QUALITY_LIMIT)
        return false;

    if (data.sunlight)
        return true;

    if (finalTemperature >= MIN_TEMPERATURE &&
        finalTemperature <= MAX_TEMPERATURE)
        return true;

    return false;
}

int main() {

    cout << "\nAUTOMATIC CLIMATE SENSITIVE WINDOW SYSTEM\n";

    SensorData data = readSensors();

    displayData(data);

    bool windowOpen = shouldOpenWindow(data);

    cout << "\nSYSTEM DECISION\n";

    if (windowOpen)
        openWindow();
    else
        closeWindow();

    cout << "\nExecution Completed\n";

    return 0;
}
