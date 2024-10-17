# PetaKit5D-GUI
A Graphical User Interface for the [PetaKit5D](https://github.com/abcucberkeley/PetaKit5D) image processing pipeline

## Quick Start Guide
Currently Linux (Ubuntu 22.04 and Scientific Linux), Windows (10 or newer), and MacOS (12 or newer) are supported

Detailed explanations for all parameters and step-by-step examples can be found on the wiki: [PetaKit5D-GUI Wiki](https://github.com/abcucberkeley/PetaKit5D-GUI/wiki)

### Installation
   1. Download the latest installer or package release for your operating system from the [releases](https://github.com/abcucberkeley/PetaKit5D-GUI/releases) page

   2. Note: In some cases, the installation may take a long time (10-15 minutes)

   3. Linux:

      1. Ubuntu 22.04:

         1. cd into the directory you downloaded PetaKit5D-GUI_ubuntu2204.deb to

         2. sudo dpkg -i PetaKit5D-GUI_ubuntu2204.deb

         3. Call PetaKit5D-GUI from a terminal

   4. Mac (MacOS 12 or newer):

      1. Double-click the PetaKit5D-GUI_mac.pkg file and you should see an error about an unidentified developer

      2. Currently the Mac installer .pkg needs to be manually approved before it can be run (This may change in the future if there is more demand for the Mac version)
     
      3. Go into System Preferences > Security & Privacy > General
     
      4. At the bottom, you should see "PetaKit5D-GUI_mac.pkg" was blocked from use because it is not from an identified developer.

      5. Click Open Anyway

      6. Click Open

      7. You may be prompted for admin privileges at some point. Type in your password if prompted

      8. Follow the installer's instructions

      9. You may see a bouncing Matlab icon in your taskbar. Do not click this as it can cause the installation to fail

      10. When prompted to choose an installation location for the Matlab Runtime, Leave all values at their default

      11. Search for PetaKit5D-GUI and launch the program

   5. Windows (Windows 10 or newer):

      1. Double-click the PetaKit5D-GUI_windows_setup.exe file

      2. You may get a popup saying "Microsoft Defender SmartScreen prevented an unrecognized app from starting."

      3. If this happens, click More Info > Run anyway

      5. You may be prompted for admin privileges, click Yes

      6. Follow the installer's instructions

      7. Search for PetaKit5D-GUI and launch the program

### Wiki

For further instructions on installation and use of the PetaKit5D-GUI, vist the [PetaKit5D-GUI Wiki](https://github.com/abcucberkeley/PetaKit5D-GUI/wiki)

## Reference

Please cite our software if you find it useful in your work:

Xiongtao Ruan, Matthew Mueller, Gaoxiang Liu, Frederik Görlitz, Tian-Ming Fu, Daniel E. Milkie, Joshua L. Lillvis, Alexander Kuhn, Chu Yi Aaron Herr, Wilmene Hercule, Marc Nienhaus, Alison N. Killilea, Eric Betzig, Srigokul Upadhyayula. Image processing tools for petabyte-scale light sheet microscopy data. Nature Methods (2024). https://doi.org/10.1038/s41592-024-02475-4
