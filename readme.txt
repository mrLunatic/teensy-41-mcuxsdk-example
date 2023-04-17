Simple project to build apps for teensy4.1 by mcuxsdk

Steps:
1. Install mcuxsdk (https://github.com/nxp-mcuxpresso/mcux-sdk)
2. Set env variable MCUX_SDK_HOME to root of mcuxsdk project (contains core, examples, middleware and other projects)
3. Install arm-none-eabi-gcc (tested on 12.2.1)
4. Clone this repo
5. Run 'prepare.sh' script
6. Run 'build.sh' script
7. Flash ./bin/Sandbox.hex by teensy utility
