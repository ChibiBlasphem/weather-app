# Weather App - Test for Shadow

## Technical stack

- Language: C++
- Framework: QtQuick 6.7.2

## Api

This app uses weatherapi.com, to make the app work you'll need to have a key.  
You can create a free account and use the key provided

## How to install and run

- Be sure to have Qt 6.7.2 libs installed locally
- Clone this repository in the folder you want
- CD to this folder
- Create a folder `build` and cd into it
- Configure the project:
```
cmake -DCMAKE_PREFIX_PATH=<path/to/qt/lib> -DCMAKE_EXPORT_COMPILE_COMMANDS:BOOL=TRUE -G Ninja ..
```
- To build run:
```
cmake --build .
```
- You can now execute `./WeatherApp`

## To be improved

- weatherapi.com provided other APIs I didn't use or data from the endpoint I used that I could've displayed
- too much attention given on the "UI part"
- Red paths not managed: errors on request, no ui feedback when loading data or request has failed
