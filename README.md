# bus-tracker
Department of Electrical and Computer Engineering
North South University

 

Junior Design Project

Bus Service Automation


Mohammad Rashedul Alam		ID # 1511384642
Sakib Mukter					ID # 1520268042
Muhammad Abeer Tahmeed		ID # 1510963042
Kawcher Ahmed				 ID # 1520667642


Faculty Advisor:
Mirza Mohammad Lutfe Elahi
ECE Department
Senior Lecturer
Summer, 2018


Declaration

This is to declare that no part of this report or the project has been previously submitted elsewhere for the fulfillment of any other degree or program. Proper acknowledgement has been provided for any material that has been taken from previously published sources in the bibliography section of this report.

.........................................................
Mohammad Rashedul Alam 
ECE Department
North South University, Bangladesh


........................................................ 
Sakib Mukter 
ECE Department
North South University, Bangladesh


......................................................... 
Muhammad Abeer Tahmeed 
ECE Department
North South University, Bangladesh


......................................................... 
Kawcher Ahmed 
ECE Department
North South University, Bangladesh

 
Approval
The Junior Design Project entitled “Bus Service Automation” by Mohammad Rashedul Alam (ID#1511384642), Sakib Mukter (ID#1520268042), Muhammad Abeer Tahmeed (ID#1510963042) and Kawcher Ahmed (ID#1520667642) has been accepted as satisfactory and approved for partial fulfillment of the requirement of BS in CSE degree program on May, 2017.

Supervisor’s Signature


Mirza Mohammad Lutfe Elahi
Senior Lecturer
Department of Electrical and Computer Engineering
North South University
Dhaka, Bangladesh.



Department Chair’s Signature


Dr. Shazzad Hosain
Associate Professor
Department of Electrical and Computer Engineering
North South University
Dhaka, Bangladesh.


Acknowledgement


First of all, we would like to express our profound gratitude to our honorable course instructor, Mirza Mohammad Lutfe Elahi, for his constant and meticulous supervision, valuable suggestions, his patience and encouragement to complete the project. 
We would also like to thank the ECE department of North South University for providing us with the opportunity to have an industrial level design experience as part of our curriculum for the undergraduate program.
Finally, we would like to thank our families and everybody who supported us and provided with guidance for the completion of this project.
 
Abstract


Automatic Fare Collection and Bus Tracking System implemented by RFID card and GPS. RFID card is given to the passenger and when passenger gets into the bus he has to point the card in the RFID reader and after reaching destination he will again point in the RFID. System will automatically calculate the fare and deduct the money automatically. Hence people do not have to carry the money and they don’t have the problem in giving the right change to conductor.  All the record will be updated automatically in the server continuously. An App will monitor the bus for amount of path taken by bus, status, number of passengers, distance information. App will continuously track the bus. It overcomes all the problems faced in bus with IOT based monitor system.
 
Table of Contents
Chapter 1	1
Project Overview	1
1.1 Introduction	2
1.2 Our proposed project	2
1.3 Description of the idea:	2
1.4 Difficulty	3
1.5 Motivation	3
1.6 Summary	4
Chapter 2	5
Related work	5
2.1 Introduction	6
2.2 Research and publications RFID Fare System	6
2.2.1 RFID-BASED AUTOMATIC BUS TICKETING: FEATURES AND TRENDS:	6
Chapter 3	7
Structure of the system	7
3.1 Introduction	8
3.2 Procedure and Functionality	8
3.2.1 Procedure	8
3.2.2 Functions	9
3.3 Equipment and Schematic Diagrams	11
3.4 Summary	12
Chapter 4	13
Modules used in this system	13
4.1 Introduction	14
4.2 RC522 RFID Module 13.56MHz	14
4.3 GPS Module (NEO-6M)	15
4.4 LCD Display (16x2)	15
4.5 ESP8266 WIFI Module	16
4.6 Summary	17
Chapter 5	18
Mechanical Description	18
5.1 Introduction	19
5.2 Mechanical measurements and explanations	19
5.3 Summary	19
Chapter 6	20
Design Impact	20
6.1 Introduction	21
6.2 Economic impact	21
6.3 Social impact	21
6.4 Manufacturability	21
6.5 Sustainability	21
6.6 Summary	21
Chapter 7	22
Results and Discussion	22
7.1 Introduction	23
7.2 Complete System:	23
7.2.1 App:	24
7.3 Limitations	24
7.4 Summary	24
Chapter 8	25
Project Budget & Timeline	25
8.1 Introduction	26
8.2 Project Budget	26
8.3 Project Timeline	27
Chapter 9	28
Conclusion	28
Bibliography	30
 








Chapter 1
Project Overview

 
1.1 Introduction
In our country especially in Dhaka there are so many buses which need lots of conductors to conduct the bus. It is a hassle. It consumes so many times and creates chaos among conductor and passengers.
People wait for buses for long time. But when the bus arrives, most of the time there are no seats available. It costs time, money and many more. So, we would like to introduce our idea about this hassle through our project. The project is Bus System Automation. So there will be no conductor needed to collect the fares and check for the vacant seats. Passengers have their RFID as their currency. There will be a device in the bus. When passengers will get in the bus they have to punch their RFID and the device will read the data and send it to server to start as his\her journey. Then it will update how many seats are available. And when passengers get down from the bus they will punch their RFID again and the device will calculate his/her fare through Google Map API. It will calculate the fare through distance covered. So if someone have emergency to get down from the bus, the fare will be shown as how much distance he covered. So it will be fair enough for passengers. People can also see when the bus will arrive and how many seats are available through our Android app. The Android app immediately get updated with the device in the bus.

1.2 Our proposed project
The main idea of our project is to reduce the hassle people go through using public transportation system in Bangladesh. Our aim is to design the bus management and tracking in such a way that will ensure good customer experience.

1.3 Description of the idea:
Automated fare collection (AFC) systems are used in many urban public transport systems around the world. As the designation suggests, these are typically designed with the specific purpose of automating the ticketing system, easing public transport use for passengers and adding efficiency to revenue collection operations. In addition, AFC systems are used to enable integrated ticketing across different public trans-port modes and operators in urban areas. This chapter gives you an introduction about the Internet of Things and its real time applications. The main idea behind this project is to collect the fare automatically using the Internet of Things in a cost efficient manner. Internet of Things allows objects to sensed and controlled remotely across existing network infrastructure.


Capability of the System:
•	The System will collect fare
•	Track Bus
•	Show passenger list
•	Calculate fare
•	Provide trip list for Bus owners


1.4 Difficulty
The level of difficulty for this project is to moderate. There are a lot of reference and documentation available for the components used in this system. Getting the project together is a challenge as there are different modules working together. The memory indexing and accessing of NFC card is a bit tricky as we need to use block and bits to store and get data manually. 


1.5 Motivation
Technology has always been developed very rapidly by and for the able people. Our objective is to design, develop and build a RFID based ticketing system that will provide a useful and efficient means of transportation for the people of a busy city like Dhaka. It can be used in over populated cities like Dhaka, where people face unfairness in fare. Bus automation system gives the way to pay the actual bus fare for a particular distance.
Also, an apps can helps people to see the bus location so that they can go to the bus counter in time. By the apps people can see the available seats in the bus. People need not to quarrel with bus driver for the bus fare. The system will reduce the road accident that happens because of lack of awareness.
Development in this field can open up boundless possibilities and a new era in transportation in mega cities. It can result in many new applications that can be very useful and have a great impact on the living style of the people.
1.6 Summary
In this chapter, we have briefly described the basics of RFID based bus automation system, existing bus automation system, and the main idea on which our project will be built. We have described the capabilities of the RFID bus automation system, what motivated us to design and build this system, and our accomplishments in here. The following chapters describe the theory and details of the components used the mechanical description, designs, and the overall structure of the system.
 



















Chapter 2
Related work

 
2.1 Introduction
Literature review was carried out throughout the whole project to gain knowledge and improve the skills needed to complete this project. The main sources for this project are previous related projects, research thesis, books, journals and online tutorials. This chapter focuses on the basic concepts and all fundamental theories which related to this project and the drawbacks of the current system.

2.2 Research and publications RFID Fare System
Some research and publication related to Bus fare system is discussed in following:


2.2.1 RFID-BASED AUTOMATIC BUS TICKETING: FEATURES AND TRENDS:
This paper is on the bus ticketing system. Recent advancements in various technologies have made remarkable developments in various fields for public welfare and public transport is one such area. In the near future public bus transport system with advanced technologies like Radio Frequency Identification Device (RFID), GSM, GPS, ZigBee and RF modules will gain spotlight due to their advantage of higher convenience and greater life standards as compared to the conventional bus systems. In this paper, a comprehensive review of all several proposed bus ticketing and bus information methods has been presented in detail. The study brings out improved solution in terms of cost, convenience, user satisfaction and future implementation. The choice of working modules and their efficient performance has been discussed along with the highlighted importance of the need of technology for welfare of common public and visually impaired.
 




Chapter 3
Structure of the system

 
3.1 Introduction
The whole system consists of a microcontroller controlling bunch of modules for the system. The GPS module gives the location to the microcontroller. Which then process and transmits it to app via Google API. RFID module check and collects fare from passengers NFC cards.


3.2 Procedure and Functionality
The system does the following procedure and has these functions.


3.2.1 Procedure
	








						
						Fig. 3.2.1 Workflow diagram of the Arduino  
As NFC card are scanned the passenger info gets stores and the fare starts till he gets down and fare is calculated according to that. GPS keeps info of the location and send to the App.
3.2.2 Functions
The functions include:
•	Track Bus
•	Show Distance and Passenger List
•	Recharge Balance
•	Pay with NFC card
•	Check Passenger List
•	Track Daily Passenger 

3.2.3 Workflow and Algorithms
 
Figure 3.2.3: System Flow diagram
Fig (3.2.3) shows how the components of the system are inter-related and communicating with one another.
•	GPS sensor module receives the coordinate from satellite. Then Arduino calculates the position of the system (BUS).
•	RFID module check for NFC cards. NFC cards are read by the module and send the data from the card to the Arduino.
•	LCD displays the info and balance of users which it receives from the Arduino.
•	Android App is constantly checking the status and location of Bus. The App let users know where the bus is and how many seats are vacant.
•	WIFI Module sends data packets from Arduino to the network. WIFI module keeps the system connected to internet.
3.2.3.1 Outline of the workflow
 

3.3 Equipment and Schematic Diagrams
The following electrical components were used in this project.
•	Microcontroller (Arduino Uno)
•	LCD Module 
•	RFID Module 
•	GPS Module
•	Google API
•	Mobile App
•	WIFI Module
 
Fig.3.3. Block diagram of complete System
Fig (3.3) shows the complete system. Arduino is connected with GPS, RFID and LCD module. RFID Module scans RFID cards and reads or writes cards. GPS module constantly keeps track of the longitude and latitude and sends the info to the mobile App. LCD displays the info as passenger gets on and off of the bus. Google API shows the location in the App.
3.4 Summary
In this chapter, we have described how the system works. The RFID info is sent to microcontroller. The process is to show info and collect fare. WIFI, GPS Module keeps the microcontroller connected to App and send Location. Detailed description of the equipment used will be given in following chapters.


























Chapter 4
Modules used in this system

 
4.1 Introduction
The different modules used in our system and their functions are described in this chapter. 
The following modules have been used in the construction of the robot:	
•	RFID Module (MFRC-522)
•	GPS Module (NEO-6M)
•	LCD Display (16x2)


4.2 RC522 RFID Module 13.56MHz
This low cost MFRC522 based RFID Reader Module is easy to use and can be used in a wide range of applications. The MFRC522 is a highly integrated reader/writer IC for contactless communication at 13.56 MHz
Package contents
•	    1 x Mifare RC522 Card Read Antenna RF Module
•	    1x RFID plain white Card
•	    1x RFID FOB
•	    1x 8pin right angle header pins
•	    1x 8pin straight header pins
 
	Fig. 4.1.RFID Module 	

4.3 GPS Module (NEO-6M)
The NEO-6M GPS module is a well-performing complete GPS receiver with a built-in 25 x 25 x 4mm ceramic antenna, which provides a strong satellite search capability. With the power and signal indicators, you can monitor the status of the module. Thanks to the data backup battery, the module can save the data when the main power is shut down accidentally. Its 3mm mounting holes can ensure easy assembly on your aircraft, which thus can fly steadily at a fixed position, return to Home automatically, and automatic waypoint flying, etc. Or you can apply it on your smart robot car for automatic returning or heading to a certain destination, making it a real "smart" bot!
 
Fig.4.2. GPS Module NEO-6M


4.4 LCD Display (16x2)
LCD (Liquid Crystal Display) screen is an electronic display module and find a wide range of applications. A 16x2 LCD display is very basic module and is very commonly used in various devices and circuits. These modules are preferred over seven segments and other multi segment LEDs. The reasons being: LCDs are economical; easily programmable; have no limitation of displaying special & even custom characters (unlike in seven segments), animations and so on.
A 16x2 LCD means it can display 16 characters per line and there are 2 such lines. In this LCD each character is displayed in 5x7 pixel matrix. This LCD has two registers, namely, Command and Data.
 
Fig. 4.3: LCD Display 16x2

4.5 ESP8266 WIFI Module
ESP8266 offers a complete and self-contained Wi-Fi networking solution, allowing it to either host the application or to offload all Wi-Fi networking functions from another application processor.
When ESP8266 hosts the application, and when it is the only application processor in the device, it is able to boot up directly from an external flash. It has integrated cache to improve the performance of the system in such applications, and to minimize the memory requirements.
Alternately, serving as a Wi-Fi adapter, wireless internet access can be added to any microcontroller-based design with simple connectivity through UART interface or the CPU AHB bridge interface.
 
Figure 4.4: ESP8266 WIFI Module
4.6 Summary
In this chapter, we have described the different modules used in our system- RC522 RFID Module, GPS Module, LCD Module, and WIFI Module.




 










Chapter 5
Mechanical Description

 
5.1 Introduction
The mechanical construction of the device is described in detail in this chapter. The mechanical part of the device has been designed and made from scratch entirely by us. We designed this device with Arduino, breadboard, wires, modules etc. We have used 5 mm thick PVC boards for the construction of the body. The mechanical measurements and explanations of the constructions are discussed below.

5.2 Mechanical measurements and explanations 
The device has a base which is 5 mm thick. The two breadboards are connected with base. The Arduino is placed beside the breadboards on the base. There is a RFID reader which will read the information of the passengers. There is a Wifi module, GPS module in our device. We will place these modules with Arduino. The display is placed on the breadboard. When RFID reader reads data from the card then it will send the information via Wifi module to the server. GPS module helps us to locate the location of the bus and calculate fares.

5.3 Summary
In this chapter, the mechanical construction of the device has been described in detail. Detailed explanation of how each of the mechanical components works has also been given here.
 


 



Chapter 6
Design Impact

 
6.1 Introduction
The different ways in which our designed project leaves an impact, and how its manufacturability and sustainability is discussed in this chapter.

6.2 Economic impact
This device allows the passengers to get their bus services without any hassle. This could save up time and could positively affect the economy. It can be used by passengers during office hours which can save much more time. Economic impact would not be that significant, Still, an automatic bus system could be used for saving time, money etc. Thus it can be expected to affect the economy in a positive way.

6.3 Social impact
Our project can be put to all kind of city bus services. It can be used to ensure vacant seats, save time and so on. It can open up a new era in bus services. Thus we can say that it is expected to have a remarkable social impact.

6.4 Manufacturability
The device requires components which are widely available. The mechanical design is simple and has been precisely documented. Thus it would not be a complex system to manufacture. 

6.5 Sustainability
Our device has been made using breadboard, PVC and all parts are rigid and fixed strongly to each other so there is very little chance of the components breaking down, loosening, or falling apart. The design is expected to be durable and resistant to pressure or stress of any kind. The device has been designed so that it can even move without difficulty. Thus it is expected to sustain for a long period of time.
6.6 Summary 
The different aspects of this project’s impact and its manufacturability and sustainability have been discussed in this chapter.



 



Chapter 7
Results and Discussion 
7.1 Introduction
The results and findings of our project are discussed in this chapter. We identified the radio frequency of our RFID cards which is used to track individual. By the wifi module we will access internet to connect with our server and app. The GPS module works with the help of Google Map API. By the help of Google Map API we can easily calculate the distance covered and the fare.

7.2 Complete System:  
 	 

7.2.1 App:	
					 





7.3 Limitations
Our project has some limitations like it doesn’t have unlimited balance for passengers. For this project we have to connect with the internet all time. If the internet doesn’t work then the device won’t work properly. Because the Google Map API cannot trace your location and distance you have covered. Other limitation is, if someone forget to punch the RFID before get down from the bus then it will continue to counting the fare.   

7.4 Summary
In this chapter, we have described and discussed the results of our project, which tracing the location of passengers and calculate the distance covered through Google Map API. 


 



Chapter 8
Project Budget & Timeline









8.1 Introduction
The project timeline duration and budget will be discussed in this chapter.

8.2 Project Budget 
Hardware Parts	Price (Tk)
Arduino	500
RC522 RFID Card Reader/Detector 	235
ESP8266 Wi-Fi Module	245
GPS Module	1400
LCD	200
Total	2580
   		    Table 1: Budgets of “Bus Service Automation Process” Project
 









Figure 8.1: Project Budget


8.3 Project Timeline
WBS	Task Name	Start Date	Finish Date	Duration
1	Project Design	1-Jun	7-Jun	6
2	Project Report	9-Jul	12-Jul	4
3	Hardware Testing	12-Jul	14-Jul	2
4	Hardware Assemble	15-Jul	18-Jul	3
5	Hardware Prototype Testing	18-Jul	21-Jul	3
6	Building App	22-Jul	24-Jul	2
7	System Testing	25-Jul	26-Jul	1
8	Connecting to App	27-Jul	29-Jul	2
9	Final System Construction	30-Jul	12-Aug	1
10	Testing and Debugging System	13-Aug	17-Aug	4
11	Project Demonstration		18-Aug	

Table 2: Time table of “Bus Service Automation” Project

Figure 8.2: Project Timeline
















Chapter 9
Conclusion










In this project, we have focused on two things – RFID based bus ticketing and an apps to see the location of the bus and available seats in the bus.
The fare collection problem has been eliminated Moreover, the project phase is completed successfully by using smart card .This project is made with pre-planning, that it provides flexibility in operation. This innovation has made more desirable and economical. This project “AUTOMATIC BUS FARE COLLECTION SYSTEM USING RFID “ is designed with the hope that it is very much economical and helpful for passengers and as well as conductors during Journey.




 






















  Bibliography
 
[1] EPCTM Radio-Frequency Identification Protocols Class-1 Generation-2 RFID Protocol for Communications at 860 MHz – 960 MHz Version 1.10, EPCglobal Inc, 2006.
[2] Dobkin, Daniel M. “The RF in RFID,” Elsevier Inc., 2008.
[3] Ng, Mun Leng. Leong, Kin Seong. Cole, Peter H. Analysis of Constraints in Small UHF RFID Tag Design, 2005.
[4] Nikitin, P. V. and K. V. S. Rao, Theory and measurement of backscattering from RFID tags, IEEE Antennas and Propagation Magazine, vol. 48, no. 6, pp. 212-218, December 2006.
[5] Nikitin, P. V., K. V. S. Rao, and R.D. Martinez, “Differential RCS of RFID tag,” Electronics Letters, April 12, 2007, Vol. 43, No. 8.
[6] Nikitin, P. V., K. V. S. Rao, and S. Lazar, “An overview of near field UHF RFID,” IEEE RFID 2007 Conference, March 2007.
[7] Rao, K. V. Seshagiri, Pavel V. Nikitin, and Sander F. Lam. “Antenna Design for UHF RFID Tags: A Review and a Practical Application.” IEEE Transactions on Antennas and Propagation, VOL. 53, NO. 12, December 2005.
[8] S. Dontharaju, S. Tung, A. K. Jones, L. Mats, J. Panuski, J. T. Cain, and M. H. Mickle, “The Unwinding of a Protocol,” IEEE Applications & Practice, RFID Series, Vol. 1, No. 1, pp. 4 - 10, April 2007.
[9] Jones, A. K., Dontharaju, S., Mats, L., Cain, J. T., and Mickle, M. H., “Exploring RFID Prototyping in the Virtual Laboratory,” MSE Conference, 2007.
[10] Sweeney, Patrick J.  RFID for Dummies, pp.119-138. Wiley Publishing Inc, 2005.
[11] : A. Oudah 2016 IOP Conf. Ser.: Mater. Sci. Eng. 114 012146.
[12] Mandeep K., Manjeet S., Neeraj M. and Parvinder S. S.: RFID technology principles, advantages, limitations & its applications. In: Proceedings of the International Journal of Computer and Electrical Engineering, 2011, February Vol.3, No.1, 1793-8163.
[13] Kaushal M. A., Harshil M. G., Priyank J. S.: Automatic Ticket Vending via Messaging Service ATVMS. In: International Journal of Computer Applications, Volume 42, No.17, March 2012.
[14] Punit D., Benjamin L., Devin T.: RFID navigation system for the visually impaired. In: A Major Qualifying Project submitted to the faculty of Worcester Polytechnic Institute for the Degree of Bachelor of Science, April 25, 2012.
[15] N. Nandini, S. Pavithra, G. Sindhuja, K. Sukanya: Embedded based passenger infotainment system. In: International Journal of Electrical, Electronics and Data Communication, ISSN (p): 2320- 2084, Volume-1, Issue-1, March 2013. iMEC-APCOMS 2015 IOP Publishing IOP Conf. Series: Materials Science and Engineering 114 (2016) 012146 doi:10.1088/1757-899X/114/1/012146 9
[16] G. Lavanya, Preethy W., Shameem A., Sushmitha R.: Passenger bus alert system for easy navigation of blind. In: Proceedings of the International Conference on Circuits, Power and Computing Technologies ICCPCT, March 2013.
[17] Nandhini a, Sunitha. (2017). Automatic Bus Fare Collection System using RFID. International Journal of Advanced Research in Computer Engineering & Technology. Volume 6. 218-223.

