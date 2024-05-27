# OpenToolbar
OpenToolbar is a Linux application to manage Lenovo Laptops' settings, like official application on Windows. Works only on command-line currently.

<u>**Settings:**</u>
- **Conservation Mode:** _Limit battery to %60._
- **Fn Lock:** _Turn on/off fn lock._
- **Touchpad:** _Turn on/off touchpad._
- **Usb charging:** _Manage always on usb port._

<u>**Disclaimer:**</u> OpenToolbar is not affiliated with Lenovo in any way.

# Installation

## Debian/Ubuntu
You can download ".deb" file from releases tab or from command-line:
```
wget https://github.com/ztrahmet/OpenToolbar/releases/download/v0.1.0/opentoolbar-0.1.0-amd64.deb
sudo dpkg -i opentoolbar-0.1.0-amd64.deb
```
## Compile from source
```
git clone https://github.com/ztrahmet/OpenToolbar.git
mkdir -p OpenToolbar/build
cd OpenToolbar/build
cmake .. && sudo make install
```
to uninstall:
```
sudo make uninstall
```
