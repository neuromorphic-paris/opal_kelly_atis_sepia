#!/bin/sh
set -e
cd -P -- "$(dirname -- "$0")"
rm -rf resources
curl 134.157.180.96/opal_kelly_atis_sepia.tar.xz | tar xJ
if [ "$OSTYPE" = 'linux-gnu' ]; then
    sudo cp resources/libopalkellyfrontpanel.dylib /usr/lib/
    sudo cp resources/libudev.so.0 /usr/lib/
    sudo ldconfig
    sudo cp resources/opalkelly.rules /etc/udev/rules.d/
    sudo udevadm control --reload-rules
fi
