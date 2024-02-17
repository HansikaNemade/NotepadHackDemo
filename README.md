
# Notepad Controller (Notepad Hack Demo)

NotepadDemo is a Windows application built using the Win32 SDK, designed tocontrol and modify the behavior of a running Notepad instance without directly interacting with the Notepad window. There is a simple  interaction between the application user Interface and the targeted 
 Notepad Instance.   


## Features

- GUI Interface : Develop a Windows GUI application using the Win32 API that provides user controls to interact with the Notepad process. This interface could include buttons, sliders, text fields, etc., for controlling various aspects of the Notepad behavior.

- Control Buttons : Add buttons to the application interface for controlling Notepad. These buttons can include options to move Notepad in different directions (up, down, left, right), change its size, change its icon, font, and name.

- Identifying Notepad Process : Implement functionality to identify the running Notepad process. You can achieve this by enumerating through the list of running processes and checking for processes with the name "notepad.exe".
- Window Positioning : Allow the user to control the position of the Notepad window by providing options to increase and decrease it horizontally and vertically on the screen.
- 	Window Movement :  Allow the user to control the position of the Notepad window by providing options to move in different directions (up, down, left, right) on the screen
- Window Resizing : Enable the user to resize the Notepad window with new width and height dimensions which was set in the code.
- Icon Modification : Enable users to change the icon of the Notepad window. This can acchive by calling 'LoadIcon' function to load a new icon from a file or a resource, and then use the 'SendMessage' function with the WM_SETICON message to set the new icon for the Notepad window.
- Window Renaming : Allow users to change the title or name of the Notepad window. This can be done using 'SetWindowText' function to change the text of the window title.
- User Interface: Designed a user-friendly interface for the application with clear labels and intuitive controls for each feature.


## Vedio

[https://github.com/HansikaNemade/NotepadHackDemo/issues/1#issue-2140066442](https://github.com/HansikaNemade/NotepadHackDemo/assets/103547922/7db69e7d-e559-4ebd-a284-4317334884bf)

## Acknowledgements

 - [Astromedicomp](https://astromedicomp.org/) and [Marshalling Void](https://www.youtube.com/@marshallingvoid/videos) played a crucial role in Understanding the concepts of C / C++ programming languages and Win32 Components. I am deeply thankful to them for their invaluable teachings and hands-on exercises which makes my foundation strong to Understanding my skills to new heights.

 - [Programming Windows](https://shalabh.synthasite.com/resources/Programming%20Windows%20-%20Charles%20Petzold.pdf) This book helped a lot for understanding about the win32 components how they has implement in code.

 - [Windows reference pages](https://learn.microsoft.com/en-us/windows/win32/apiindex/windows-api-list) This pages is to understand the new feature or Components of the Technology

