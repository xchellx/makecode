# makecode
makecode is a cli that prints PrimeHack's mods ported to Gecko codes.

## Table of Contents
- [Info](#info)
- [Building](#building)
- [Credits](#credits)
- [License](#license)

## Info
PrimeHack has modifications that you can enable at runtime to do things like unlock hypermode difficulty, disable bloom
, etc. This tool is a port of these mods to Gecko codes. It can print a code based on the game and region.

makecode can print code(s) to the format for Dolphin (`[Gecko]\n$Code Name\ncode`), Ocarina (`GAMEID\nGame Name\n\n
Code Name\ncode`), and raw (`code`).

## Building
Simply run `./compile.sh` at root directory of project. This script uses GCC to compile the sources. It also computes
the md5, sha1, and sha256 hash of the compiled result afterwards using `md5sum`, `sha1sum`, and `sha256sum`. You can
pass `asan` as the first argument to the script to build a debug build with AddressSanitizer (this isn't supported on a
Windows build) with all warnings to be printed. For building for Windows, run `./compile.sh` with MSYS2 MinGW x64 or
run `.\compile.bat`.

## Credits
- Shio, SirMangler, and many others for their work on PrimeHack, a modification of Dolphin Emulator to allow for FPS
controls and other things on the Metroid Prime series [here](https://github.com/shiiion/dolphin).

## License
```
MIT License

Copyright (c) 2022 Yonder

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
SOFTWARE.

```
