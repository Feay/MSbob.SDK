	  ----------------------------------------
	  Microsoft Bob Version 1.O README File
			
		      January, 1995
	  ----------------------------------------

	  (C) Copyright Microsoft Corporation, 1995


This document provides complementary or late-breaking
technical information about Microsoft Bob.


------------------------
How to Use This Document
------------------------

To view README on screen in Windows Notepad, maximize
the Notepad window.

To print README, open it in Windows Write, Microsoft
Word, or another word processor. Then select the entire
document and format the text in 10-point Courier before
printing.

------------------------
Contents
------------------------

ATI/Mach32 Video Driver Incompatibilities
Backup Can't Restore Bob Files
Checkbook
Cirrus Logic Video Driver Incompatibility
E-Mail
Financial Guide
General Notes about Running Bob
Getting Technical Help
Hardware that Is Incompatible with DMF disks
Household Manager
Increasing SmartDrive Cache for Better Performance
Launching Windows Files from Bob Home Program Starters
Letter Writer
Making Backup Copies of the Bob Disks
Modem Troubleshooting
Print Troubleshooting
Running E-Mail and Windows 95
Running Bob with Windows for Workgroups
   Network Drivers
Screen/Display Troubleshooting
Sound Too Low with Soundblaster
Using Large Fonts

-----------------------------------------
ATI/Mach32 Video Driver Incompatibilities
-----------------------------------------

1. When Bob tries to draw certain colors on the screen when you
   are using the 24-bit (16.7 million colors) Mach32 video driver
   with the ATI video card, Bob will crash. The workaround for
   this problem is to change to the 256-color Mach32 video driver.

2. If you have problems running Bob while using a Mach8
   video driver that comes with the ATI Ultra video card, in any
   resolution, the workaround is to use the 640x480 resolution,
   256-color SuperVGA driver that comes with Windows. (This is
   your safest choice, as the higher resolution SuperVGA drivers
   also may not work with the ATI Ultra video card and Bob.)

3. If you experience "out of memory" errors and/or Bob has screen/
   display problems when you are using an ATI video driver,
   try the following:

   a. Click the Windows Notepad (it is part of the Accessories
      group in the Windows Program Manager) and press Enter.

   b. Click "File," and then click "Open" in the File menu that
      drops down.

   c. Type the following (exactly as it appears here):
   
      c:\windows\system.ini

      Click OK and the system.ini file appears.

   d. Scroll down until you find the following line:

      [mach]
      DeviceBitmap=on
  
      Note that there may be other lines under [mach].

   e. Delete "on" and type "off" so that the DeviceBitmap 
      line looks like this:

      [mach]
      DeviceBitmap=off

   f. Exit Notepad, clicking "Yes" to save the file. 

   g. Exit Windows and restart Windows and then start Bob to see
      if this cleared up the display problems. If you still experience
      the same problems, please contact your printer dealer for help.

-------------------------------
Backup Can't Restore Bob Files
-------------------------------

Backup only knows how to restore your Bob files into the 
directory in which Bob is originally installed. This means that
if you uninstall Bob and then install it in a different directory
(or a second hard disk), Backup will not be able to restore your
files that were created under the old directory. 
  

---------
Checkbook
---------

The application for Pay On-Line service that you can print out in
Checkbook has an incorrect zip code (60532-9729). Please cross out
the incorrect zip code on the application and write in this zip code:

60532-3128

-----------------------------------------
Cirrus Logic Video Driver Incompatibility
-----------------------------------------

If you are using a Cirrus Logic video driver and are experiencing
problems running Bob, you probably need to update your video driver.
To update your driver, do the following:

1. Sign out of and exit Microsoft Bob.

2. Exit Windows.

3. At the MS-DOS prompt (C:\), type the following (exactly as it appears
   here, paying particular attention to spaces):

   copy c:\windows\system\ 256_1280.drv  c:\windows\system\256_1280.bak
			
   If your computer tells you "file not found" after you type the
   sentence above, try typing this:

   copy c:\windows\system\ 64k_1024.drv  c:\windows\system\256_1280.bak

4. You should see a message saying "1 file copied." Now type the
   following:

   copy c:\msbob\*.drv c:\windows\system

5. Start Windows, and then open and sign in to Microsoft Bob. Your
   display should look OK.


------
E-Mail
------

1. If you print a Quick Note mail message that is more that a single
   page of text (approximately 55-60 lines of text), only the first
   page will print.

2. Note that you won't be able to scroll more than one page of text of
   the original mail message that you are replying to or forwarding. 


----------------
Financial Guide
----------------

1. If the Financial Guide prints to the wrong printer or doesn't 
   print at all, it may be that it is printing to the default printer,
   even though you chose a different printer. Open the Windows Control
   Panel and click on Printers. You can now set the default printer you
   want to print to. Try printing again.

2. If you have wide enough columns, the Financial Guide will 
   automatically print in landscape mode. If the Financial Guide gives
   you an error message when you try to print, click Ignore and it should
   print correctly. This error only occurs when your list is wide enough
   to require landscape printing.

3. If you experience problems when cutting, copying, or pasting in the 
   Financial Guide, it is most likely because you are cutting, copying,
   or pasting Notes. Try to avoid this.

4. Lists can sometimes lose the way they are supposed to be ordered. If
   your list looks like it's sorted incorrectly, simply click the "Sort
   This List" button.
   

----------------------------------
General Notes about Running Bob
----------------------------------

1. Do not attempt to run multiple instances of a Bob
   program. Doing so will degrade performance and/or cause
   display problems.

2. If your computer runs low on graphics memory, you may experience
   different types of graphics problems in Bob, most often in
   the personal guide balloons. In low graphics memory
   situations, when you see weird display problems, it's best to exit
   Bob, exit Windows, and restart Windows.

3. Don't remove any files in the \MSBOB directory or any of its
   subdirectories in File Manager (in other words, do not remove
   anything by hand) or you may experience technical problems. 
   Furthermore, if you want to delete anything in Bob, go to the
   appropriate program and delete it there. For example, you would
   open the Letter Writer to delete a particular letter.


-----------------------
Getting Technical Help
-----------------------

For technical help, contact your designated support provider. To
find out who your designated support provider is, refer to the
Bob Magazine, which came with your Bob disks.
 

---------------------------------------------
Hardware that Is Incompatible with DMF disks
---------------------------------------------

The disks that come in the Microsoft Bob box are Distribution Media
Format (DMF) disks. This special kind of disk can store more information
than a regular high-density disk. Most 1.44 MB or 2.88 MB floppy drives
should be able to read the Bob DMF disks, EXCEPT:

   * SCSI floppy drives, including Flopticals
   * Floppy drives attached via older MicroSolutions Compaticards
   * Apple Macintosh floppy drives (even via SoftPC)
   * Early Gateway 2000 Handbook or Colorbook notebooks

If your computer has one of the listed floppy drives *and* it could
not read the Bob disks, please contact the Microsoft Support Network
for a non-DMF disk set.

-----------------
Household Manager
-----------------

1. If the Household Manager prints to the wrong printer or doesn't
   print at all, it may be that it is printing to the default printer,
   even though you chose a different printer. Open the Windows Control
   Panel and click on Printers. You can now set the default printer you
   want to print to. Try printing again.

2. If you have wide enough columns, the Household Manager will 
   automatically print in landscape mode. If the Household Manager gives
   you an error message when you try to print, click Ignore and it should
   print correctly. This error only occurs when your list is wide enough
   to require landscape printing.

3. If you experience problems when cutting, copying, or pasting in the 
   Household Manager, it is most likely because you are cutting, copying,
   or pasting Notes. Try to avoid this.

4. Lists can sometimes lose the way they are supposed to be ordered. If
   your list looks like it's sorted incorrectly, simply click the "Sort
   This List" button.

--------------------------------------------------
Increasing SmartDrive Cache for Better Performance
--------------------------------------------------

You can often get better performance from Bob by changing
the size of your SmartDrive cache. Also note that creating a
permanent swapfile can sometimes help performance. To find out
how to change your SmartDrive cache or create a permanent
swapfile, please refer to your Windows documentation.

------------------------------------------------------
Launching Windows Files from Bob Home Program Starters
------------------------------------------------------

If you want to launch a particular file when you launch a Windows
program from a Bob Home program starter, do the following:

1. Click "Other options" in any room.

2. Click "Add something," "Program," and then "Or browse on your own."

3. Similar to creating a program item in Program Manager, type a
   description for what you are launching. 

4. Press TAB key and fill in the pathname for your program executable 
   (.EXE), followed by a space, and then the pathname for your file.
   For example:

   c:\winword\winword.exe c:\directory\filename.doc

   If you do not know the pathname for your program executable, click
   "Browse the file system" to look for it.

5. Type a path for the working directory (optional) and click OK.

You should now have a program starter with the icon for your Windows
program on it. When you click this program starter, it will open
the specified program and the specified file. For more information on
creating program items, see your Windows manual.

-------------
Letter Writer
-------------

If the borders on your letters look wrong (e.g., they are boxed in 
by extra lines), and you are printing on an HP DeskJet, you may
need an updated printer driver. There is a known problem with printing
borders using version 4.10 of the HP DeskJet driver. Please contact
your printer dealer for an updated printer driver.
 

----------------------------------------
Making Backup Copies of the Bob Disks
----------------------------------------

The Bob disks use Distribution Media Format (DMF). DMF 
increases the capacity of a 3.5-inch floppy disk, reducing
the number of disks needed to install Bob and speeding
up the installation process.

But, because DMF is a read-only format, you cannot use 
MS-DOS DiskCopy, Microsoft Windows Copy Disk (File Manager), 
or any other method to make backup copies of the Bob disks.
Instead, use the original set of Bob disks as your backup; 
store them in a safe place after installing Bob.

Also, DO NOT do any of the following:

1. Write or copy anything to a Bob disk when it is in the
   floppy drive. This will destroy the disk.

2. Because DMF is a new format, many existing utilities, such 
   as Norton Disk Doctor, Microsoft ScanDisk, MS-DOS DiskCopy,
   and Microsoft Windows Copy Disk do not recognize DMF. You 
   should NOT use disk utilities to examine a DMF formatted 
   disk, as these utilities can corrupt the DMF disk. 

---------------------
Modem Troubleshooting
---------------------

If you are having problems connecting to E-Mail, you may not have
the correct modem settings. Please try the following:

Choose a lower baud rate by clicking "Other Options," and "Change
Modem Settings." Click a lower baud rate and try connecting again.
If you are still having problems, please contact your designated
support provider. To find out who your designated support provider
is, please refer to the Bob Magazine that came with your Bob disks.

---------------------
Print Troubleshooting
---------------------

If you use the following checklists and you still can't print,
look for a "Troubleshooting" section in your printer's manual
for more help.

If you turn on your printer and nothing happens:

* Is your printer plugged firmly into your computer and into a
  power outlet? If you're using a power strip, it must be 
  plugged in and turned on, too.

* Is your printer on? A button labeled "On Line" should be lit.
  If the light isn't on, press the "On Line" button.

My printer is on, but it won't print or it takes a long time to
print:

* Do you need to add paper, or is the paper jammed?

* Is the correct printer selected? You can check by finding
  "Print" in any program (usually under "Other Options"). When
  you see the printing balloon, click "Set up printer." The
  name in the "Default Printer" box should match your printer.
  If you don't know which printer to look for, check your printer
  manual or contact your printer manufacturer for that information.

  If the correct printer isn't on the list, look for printing
  topics in the index of your Windows manual to find out how to
  add it.

* Do you have a lot of pictures in your document? If so, try printing
  one page at a time, or take out some of the pictures.

Part of the document is cut off when I print:

* Part of your document may have spilled over into the printer's
  non-printing area (the part of the paper the printer can't use).
  Try making the margins bigger until you solve the problem. Click
  "Other Options," and then click "Change Margins."

------------------------------
Running E-Mail and Windows 95
------------------------------

Bob installs a 16-bit MAPI DLL that will overwrite the 32-bit
MAPI DLL that is installed as part of Windows 95. This won't 
affect the 32-bit mail component of Windows 95, but may affect 
any 16-bit MAPI clients that you are using under Windows 95.
 

----------------------------------------------------
Running Bob with Windows for Workgroups version 3.11
----------------------------------------------------

To help improve Bob's performance when running on Windows for
Workgroups version 3.11, try one or more of the following:

*  If you are running Windows for Workgroups version 3.11
   or higher on an 8MB (or lower) computer, start Windows with
   "win /n," so that the network drivers do not load. 

*  If you have 32-bit file access turned on under "386 Enhanced"
   in the Windows Control Panel, try turning it off, or reduce the
   size of the cache to 512K. To turn it off, do the following:
   
   a) Open the Windows Control Panel, which is in the Main group
      in Program Manager.

   b) Double-click the "386 Enhanced" icon.

   c) Click "Virtual Memory" button, and then "Change" button.

   d) Click the "Use 32-Bit File Access" checkbox so that it is 
      clear (i.e., deselected).

   e) Click OK and then click "Restart Your Computer." Be sure to
      close other programs before restarting your computer.


------------------------------
Screen/Display Troubleshooting
------------------------------

If you encounter problems with your screen/display, such as
missing pieces of words, incomplete balloons, or anything else
that looks strange or incorrect, try the following:

1. Sign out of Bob and close Bob. 

2. Close Windows and restart your computer by pressing the
   Ctrl+Alt+Delete keys at the same time.

3. Restart Windows, and then open and sign into Bob.

If your display still looks weird to you, your video driver (which
is the software that makes your monitor display your programs) may
not work correctly with Bob. Please contact your designated
support provider for help. To find out who your designated support
provider is, please refer to the Bob Magazine that came with your
Bob disks.

-------------------------------
Sound Too Low with Soundblaster
-------------------------------

If you are using a Soundblaster audio/sound card, you may find that
sound volume in Bob is too low. However, it may be the correct
level in your other programs. If sound is too low, do the following:

1. Sign into Bob and click "Other Options" in any room.

2. Click "Advanced Features," and then "Change Audio Volume."

3. Drag the audio slider with the mouse towards "Loud," and then click OK.

4. Click some buttons to see if sound is loud enough for you. If it
   is still too low, repeat steps 1-4 until it is at the right volume.

-----------------
Using Large Fonts
-----------------

If you are using a "large fonts" video driver, which makes the writing
on your screen larger than normal, and you experience any problems
with your display/screen when using Bob, you may need to switch to
another video driver when using Bob. Refer to your Bob Magazine or
Windows manual for more details on how to change video drivers.