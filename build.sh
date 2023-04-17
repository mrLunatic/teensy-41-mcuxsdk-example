cmake --build ./build
arm-none-eabi-objcopy -O ihex ./bin/Sandbox.elf ./bin/Sandbox.hex
