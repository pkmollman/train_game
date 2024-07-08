
Client Board
- Notes: Need a power regression from score to min
- Need a mechanism for client IR score read to not score multiple on one ball transmit, aka double scoring
- Dip switches for assigning client ID on client Arduino

Host Board


Game Menu
	

Calibrate function


Game Loop
- Power On
	- Prompt Main Menu
		- Main Menu Item 1
			- Calibrate
		- Main Menu Item 2
			- Demo
				-  randomly assign points to player trains
				- race till win
				- reset to menu prompt
		- Main Menu Item 3
			- New Race
				-  Ready Set Go indicator
				- flag servos drop
				- ball servos open
				- train power delay
				- score detected, start power min
				- accept score bonus power
				- check for win
				- detect win, throw flag servo of winner
				- Win Noise
				- reset to menu prompt


 #Hardware
- Arduino 3/4s
- IR Send/Recieve Pairs
- Servos
	- Flag Servo for each train on display 
		- this shows winner
	- Ball retainer Servo on each lane
		- This is a board that stops ball from falling to player
		- release on new game start
- Power block
	- Each display train has a power distro
		- This takes the 5v arduino input logic and translates 110 to train voltage
			- Train voltage is up to5v - 16v
	- each player lane has a arduino and LED Input and output
	- 





