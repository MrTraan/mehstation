# mehstation


`mehstation` is a multi-launcher frontend fully driven by a gamepad/keyboard.

You configure your platforms (Native, Emulators, ...) and the executables to launch on these platforms (binary, ROMs, ...) and you'll have an interface usable to launch everything using a gamepad controller or a keyboard.

## Video

[![mehstation youtube video](http://img.youtube.com/vi/g_kv_a5fako/0.jpg)](http://www.youtube.com/watch?v=g_kv_a5fako)

## Features

  * Clean and beautiful interface
  * Display screenshots, play videos, show description of executables
  * Multi-platform: Linux, Windows.
  * Easy configuration with mehstation-config
  * Automatic scraping of games resources
  * Import configuration from EmulationStation
  * Automatic detection and visual mapping of gamepads.

## Configuration

To configure your mehstation, the easiest solution is to use the dedicated tool shipped with mehstation called [mehstation-config](https://github.com/remeh/mehstation-config). The usage of this configuration tool is documented in the [mehstation wiki](https://github.com/remeh/mehstation/wiki).

## Developer infos

mehstation is developed in C with SDL2, glib, ffmpeg and SQLite3.
Please free to contribute and to send any pull requests.

## How to compile

The dependencies are:

```
cmake
glib
SDL2, SDL2_ttf, SDL2_image
SQLite3
ffmpeg
```

Manual:

```
cmake .
make -j
```

The binary `mehstation ` will be created and ready to launch.
Please create an issue if you have a problem compiling mehstation.

For further infos, see the [compilation chapters in the wiki](https://github.com/remeh/mehstation/wiki).


## License

mehstation, created by Rémy 'remeh' Mathieu, is under the terms of the MIT License.
