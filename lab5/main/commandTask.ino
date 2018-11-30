// Command Task

/*
Command
The command function shall accept a pointer to void with a return of void.
The pointer in the task argument will be re-cast as a pointer to the command task’s data
structure type before it can be dereferenced.
The task shall be scheduled whenever a command has been received by the system or
when an outgoing message must be formatted in preparation for transmission to the
remote computer.
*/

/*
Receive
When a command has been received by the system, the task must verify that the
received message is valid. If valid, it is acted upon; if invalid, an error response must
be sent to the SatelliteComms task.
The legal commands and their interpretation are specified in Appendix C.
Transmit
When a message is to be transmitted, the Command task must build the message
body. The message body is then sent to the SatelliteComms task for transmission.
After the message has been interpreted and verified as correct or an outgoing message has
been built and forwarded to the SatelliteComms task, the Command task shall be deleted
*/

/*

The Commands and Responses for the embedded application task from earth are given as
follows.
S
The S command indicates START mode. The command shall start the embedded
tasks by directing the hardware to initiate all the measurement tasks. In doing so, the
command shall enable all the interrupts.
P
The P command indicates STOP mode. This command shall stop the embedded tasks
by terminating any running measurement tasks. Such an action shall disable any data
collecting interrupts.
D
The D command enables or disables the display.
T<payload>
The T command transmits the thrust command to the satellite.
M<payload>
The M command. The M command requests the return of the most recent value(s) of
the specified data.
The M response. The M response returns of the most recent value(s) of the specified
data.
A <sp command>
The A response acknowledges the receipt of the identified command.
E
The E error response is given for incorrect commands or non-existent commands. 

*/
