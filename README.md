# Muty

A simple, fast OSC (Open sound control) controller in Qt.

With "Push To Talk", "Continues" and "Push To Mute" support.

## What it is:

- It's a OSC controller
- It's just a float number OSC switcher.

## What it isn't:

- It's not music-production-specific software, with `liblo` you may control almost anything in OSC.

## Usage

### Download, clone, compile, install:

```bash
# Make sure you have liblo and Qt6 installed.
git clone git@github.com:moodyhunter/Muty.git
cd Muty; mkdir build; cd build
cmake .. -DCMAKE_BUILD_TYPE=Release
cmake --build .
# Enjoy!
# ./Muty
```

### Adjust settings

- Click "Settings", change the address and port accordingly.
- Path is the target OSC path (See https://en.wikipedia.org/wiki/Open_Sound_Control for more information)
- For now, "Min Value" is 100 and "Max Value" is 0 (this is strange!)
  - Push "SWITCH" to change current value to "Min"
  - Release "SWITCH" to change current value to "Max"
  - Press "HOLD" down to hold current value as "Min"
  - Release "HOLD" to restore to "Max" value
- Press "INVERT" to swap the "Min" and "Max" mentioned above.

## License

GPLv3

