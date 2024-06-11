## AIM: <br>
The goal was to build a client server architecture through <b><i>multithreaded socket programming</i></b> where any number of prisoners (or clients) could connect to the server and through random guesses and get out of the prison (or program).
<br><br>

## LANGUAGE:
C++ <br><br>

## OS: 
Windows 11 <br><br>

## LIBRARIES USED:  
- iostream 
- WS2tcpip.h 
- thread 
- cstdlib 
- with build dependency of ws2_32.lib (used for <b>windows socket programming</b>)<br><br>

## INSTRUCTIONS
- Here you will find three files - Server, Prisoner Client and Count Client. 
- Firstly, with help of Visual Studio build the solution of Server and then run it using local windows 
debugger. 
- Among the two the KRSSGtask1client and the KRSSGCountClient make sure you first run the 
KRSSGCountClient which is necessary for smooth running of the program.  
- In the same way with the help of the visual studio first build the solution of the count client and then 
run it using the local windows debugger.  
- Next build the solution of the KRSSGtask1client.sln. Now go to the <br><b>
KRSSGtask1client>x64>Debug>KRSSGtask1client.exe executable file.  </b>
<br><br>
Now <i><b>run the number of clients you have previously entered in the count_client</b></i>. Wait for it to end 
the execution and provide you the escape order.