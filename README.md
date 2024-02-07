# KeyLoggr

Simple C++ Application for real time key visualisation.

## Screenshots

https://github.com/chirag-droid/KeyLoggr/assets/81347541/6a3f9dcd-c841-4fce-96ce-0a68a670b29a

## Building from source

Only `MSVC` compiler is supported. Recommended way is to use `Visual Studio` or `CLion` and select `MSVC` toolchain.
Both IDE have first party CMake support.

```
git clone https://github.com/chirag-droid/KeyLoggr.git
cd KeyLoggr
```

Either use CMake GUI or command line.

```
cmake -B build/
cmake --build build/
```
This will build the application inside `build/`

## Installation

Recommended way is to build from source. Since windows defender will flag the application as virus.

Or install pre compiled app from [releases](https://github.com/chirag-droid/KeyLoggr/releases)

## Licence

The project is licenced under GPL-3. See `Copying` for details.
