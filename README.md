# Project 4 README

Student 1: Tho Nguyen (921017457)

## Project Status
This the current status of the project unfinished.

## Known Issues
The project fails to function properly in KML MakeFile, all of the Transportation Planning and Command Lines.

## Code References

## Generative AI Use
I used ChatGPT for Prompt 1 and Prompt 2

### Prompt 1
How can I calculate the minutes and second with a given location of latitude and longitude? 

### Response 1
To calculate the minutes and seconds from a latitude or longitude value, you typically convert the fractional part of the degree into minutes and seconds. Here's how you can do it in C++:

cpp
Copy code
#include <iostream>
#include <cmath>

void decimalToDMS(double decimal, int& degrees, int& minutes, int& seconds) {
    // Extract the degrees
    degrees = static_cast<int>(decimal);

    // Calculate the remaining fractional part
    double fractionalPart = std::abs(decimal - degrees);

    // Convert the fractional part to minutes (60 minutes in a degree)
    double minutesDecimal = fractionalPart * 60;

    // Extract the minutes
    minutes = static_cast<int>(minutesDecimal);

    // Calculate the remaining fractional part for seconds
    double secondsDecimal = (minutesDecimal - minutes) * 60;

    // Round to the nearest integer for seconds
    seconds = static_cast<int>(secondsDecimal + 0.5); // Adding 0.5 for proper rounding
}

int main() {
    // Example latitude and longitude values
    double latitude = 38.6000000000; // Example latitude value
    double longitude = -121.7800000000; // Example longitude value

    // Variables to store degrees, minutes, and seconds
    int latDegrees, latMinutes, latSeconds;
    int lonDegrees, lonMinutes, lonSeconds;

    // Convert latitude to degrees, minutes, and seconds
    decimalToDMS(latitude, latDegrees, latMinutes, latSeconds);

    // Convert longitude to degrees, minutes, and seconds
    decimalToDMS(longitude, lonDegrees, lonMinutes, lonSeconds);

    // Output the results
    std::cout << "Latitude: " << latDegrees << "d " << latMinutes << "' " << latSeconds << "\" N" << std::endl;
    std::cout << "Longitude: " << lonDegrees << "d " << lonMinutes << "' " << lonSeconds << "\" W" << std::endl;

    return 0;
}
This code defines a function decimalToDMS that takes a decimal degree value and calculates the equivalent degrees, minutes, and seconds. The main function demonstrates how to use this function to convert latitude and longitude values.

### Chagnes 1
I was having issues figuring out how to solve / get an idea for the Command Line portion. Specifically the Node portion where we had to give the information for minutes seconds and degrees based on the node we retrieved.
I added the given void function to my program in order to help me execute the information by calling it with my given variables.
void decimalToDMS(double decimal, int& degrees, int& minutes, int& seconds) {
    // Extract the degrees
    degrees = static_cast<int>(decimal);

    // Calculate the remaining fractional part
    double fractionalPart = std::abs(decimal - degrees);

    // Convert the fractional part to minutes (60 minutes in a degree)
    double minutesDecimal = fractionalPart * 60;

    // Extract the minutes
    minutes = static_cast<int>(minutesDecimal);

    // Calculate the remaining fractional part for seconds
    double secondsDecimal = (minutesDecimal - minutes) * 60;

    // Round to the nearest integer for seconds
    seconds = static_cast<int>(secondsDecimal + 0.5); // Adding 0.5 for proper rounding
}

### Prompt 2
How can i check which direction its should be based on the latitude and longitude degrees? So like south north east or west

### Response 2
To determine the direction (North, South, East, or West) based on latitude and longitude degrees, you can follow these guidelines:

Latitude:

If the latitude is positive, it is in the northern hemisphere.
If the latitude is negative, it is in the southern hemisphere.
Longitude:

If the longitude is positive, it is in the eastern hemisphere.
If the longitude is negative, it is in the western hemisphere.
Combining these rules, you can determine the direction:

If latitude is positive, it's in the northern hemisphere.
If longitude is positive, it's in the eastern hemisphere.
If longitude is negative, it's in the western hemisphere.
If latitude is negative, it's in the southern hemisphere.
If longitude is positive, it's in the eastern hemisphere.
If longitude is negative, it's in the western hemisphere.
Here's how you can implement it in C++:

cpp
Copy code
#include <iostream>
#include <string>

std::string getDirection(double latitude, double longitude) {
    if (latitude >= 0) {
        if (longitude >= 0) {
            return "North-East";
        } else {
            return "North-West";
        }
    } else {
        if (longitude >= 0) {
            return "South-East";
        } else {
            return "South-West";
        }
    }
}

int main() {
    double latitude = 38.8977;
    double longitude = -77.0365;

    std::string direction = getDirection(latitude, longitude);
    std::cout << "The location is in the " << direction << " direction." << std::endl;

    return 0;
}
This code will output:

csharp
Copy code
The location is in the North-West direction.
You can adjust the latitude and longitude values to test different directions.

### Changes 2
I was confused on how to figure out which direction it would be based on the latitude and longitude data.
So I added this to my based off the response I recieved.
if(LatDeg < 0){
    LatDirection = "S";
}
else{
    LatDirection = "N";
}

if(LonDeg < 0){
    LonDirection = "W";
}
else{
    LonDirection = "E";
}