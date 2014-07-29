![Adium Tox plugin]
## Installing

Download the binary here.

## Compiling 

### Requirements

* XCode (only tested with 5.0 and above)
* Project-Tox 

### installing project tox

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

If this fails, please see the details here https://github.com/irungentoo/toxcore/blob/master/INSTALL.md#homebrew

