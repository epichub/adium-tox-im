#Adium Tox plugin
## Installing

If you simply want the newest pre-compiled version, ownload the binary [here](https://github.com/epichub/adium-tox-im/releases).

If you want to compile your own fresh brew of the plugin, continue reading.

## Compiling 

### Requirements

* XCode (only tested with 5.0 and above)
* Project-Tox 
* Adium source code. <https://trac.adium.im/wiki/GettingNewestAdiumSource>

### installing project tox

### How to build
1. Download Adium source-code.
2. Compile Adium
3. Install project tox

   Either

   ```bash
   brew tap Tox/tox
   brew install --HEAD libtoxcore
   ```

   Or

   ```bash
   cd <project directory>
   git submodule update
   cd Project-Tox
   autoreconf -i
   ./configure
   make
   make install
   ```

4. Set the Variable "ADIUM" in "User-Defined" settings under the "ToxPlugin" target build settings to your Adium source path.
5. Compile the plugin.


If this fails, please see the details here <https://github.com/irungentoo/toxcore/blob/master/INSTALL.md#homebrew>
