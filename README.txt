- Goal:
	The Goal of this Project is to create a Visual-Novel completely
	defined by configuration files. So that anyone who wants to create his/her
	own VN just can modify these files and has a complete different VN.
	
	Planned Features: (x = not implemented yet, I = implemented)
		- configuration and scenes with JSON-files   (x)
		- easy conditions for the scenes             (I)
		- advanced conditions for the scenes         (x)
		- audio-support                              (x)
		- multiple background-images                 (I)
		- effects for the characters                 (x)
		- some more advanced effects for the sprites (x)

- Current State:
	At the moment this Project is still far away from being finished and everything
	is still hardcoded and very bug ridden (see Known bugs).

- HowTo compile:
	To compile the Conversation-engine, the project has to be linked
	against the following libs:
		- sfml-graphics (v. 1.6)
		- sfml-window   (v. 1.6)
		- sfml-system   (v. 1.6)
	or their static equivalents. The Include-directory from sfml-1.6 must be known too.
	
	The same applies for the simple-VN itself. The only difference is that
	the directory "header_files" of the Conversation-engine must be known too. 
	
	I've also included a Eclipse Project File, where you only have to adjust the paths.
	
- HowTo run the simple-VN:
	Because currently every scene/menu is hardcoded (see the CMainMenue.cpp and CGame.cpp)
	you need the "Data.zip" to run the actual simple-VN with it's current testing scenes.
	Just unzip it in the same folder where the binary is.
	
- Known bugs:
	- when fading to a scene with a color and a sprite, the color fade over the sprite, making it invisible
	- crashes when changing form one scene with a sprite to another one with a sprite
	- not really a bug, but the "interface" for the conversation-engine isn't very good and it's easy to create memory leaks because of this.
	
	- please report any bug you encounter :)