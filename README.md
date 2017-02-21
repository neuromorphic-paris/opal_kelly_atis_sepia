![opalKellyAtisSepia](opalKellyAtisSepiaBanner.png "The Opal Kelly ATIS Sepia banner")

# Opal Kelly ATIS Sepia

Opal Kelly ATIS Sepia is an extension to the [Sepia](https://github.com/neuromorphic-paris/sepia) library to read events from an ATIS with an Opal Kelly shield.

# Installation

## Dependencies

Opal Kelly ATIS Sepia depends on the [Sepia](https://github.com/neuromorphic-paris/sepia) library, which can be installed by executing the following commands from a terminal:
```sh
git clone https://github.com/neuromorphic-paris/sepia.git
cd sepia && premake4 install && cd .. && rm -rf sepia
```

## Install

To install the source, go to the *opalKellyAtisSepia* directory and run `premake4 install`.
The firmwares are installed in */usr/local/share* and the Opal Kelly Front Panel files in */usr/local/include* and */usr/local/lib*. You need to be connected to the Vision Institute local network for this step to work, as it implies downloading close-source resources.

## Uninstall

To uninstall the library, run `premake4 uninstall` from the *opalKellyAtisSepia* directory.

## Test

To test the library, run the following commands:
  - Go to the *opalKellyAtisSepia* directory and run `premake4 gmake && cd build && make`.
  - Run the executable *Release/opalKellyAtisSepiaTest*.

# User guides and documentation

User guides and code documentation are held in the [wiki](https://github.com/neuromorphic-paris/opalKellyAtisSepia/wiki).

# License

See the [LICENSE](LICENSE.md) file for license rights and limitations (MIT).
