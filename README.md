# HideTaskbar

A simple utility that hides your taskbar. Must be run after `explorer.exe`, i.e. after the taskbar window has been created.

## Motivation

I use a tiling window manager on windows and do not see the need for the taskbar since I will never use it. Since there is no native way to hide the taskbar completely, I created this simple application.

When will this be a native windows feature?

![Windows Settings](https://github.com/user-attachments/assets/e19b80f1-f8a1-4d7d-ae00-5002ff6ee987)

## Usage

You can download the latest [release here](https://github.com/sinjs/HideTaskbar/releases/) or compile from source.

If you run the application without any command line arguments, it will run in the background and try to hide the taskbar window every second.

**Hint:** You can move the exe into your startup folder to make it run on boot

You can run the application with the following arguments:

- `--hide`: Hides the task bar and then exits
- `--show`: Shows the task bar and then exist
