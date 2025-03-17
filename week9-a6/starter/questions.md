1. How does the remote client determine when a command's output is fully received from the server, and what techniques can be used to handle partial reads or ensure complete message transmission?

The remote client determines when a command’s output is fully received from the server by waiting until it sees an end marker that's EOF character which is sent from the server after the output is finished. Techniques that can be used to handle partial reads are if the sender can send how long the message is so that the receiver knows how many bytes there should be or using some type of character that signals the end of the message.


2. This week's lecture on TCP explains that it is a reliable stream protocol rather than a message-oriented one. Since TCP does not preserve message boundaries, how should a networked shell protocol define and detect the beginning and end of a command sent over a TCP connection? What challenges arise if this is not handled correctly?

A networked shell protocol defines and detects the beginning and end of a command sent over TCP because data is a continuous stream so you have to mark where the messages begin and end or else you could run into many other issues such as messages getting mixed, or only parts of a message being received.

3. Describe the general differences between stateful and stateless protocols.

The general difference between stateful and stateless protocols is that stateful protocols keep track of past requests and each request can rely on past information but with stateless protocols, every request is independent

4. Our lecture this week stated that UDP is "unreliable". If that is the case, why would we ever use it?

Even though UDP is unreliable, it can support things like video, live streams or or and is very fast for these things.

5. What interface/abstraction is provided by the operating system to enable applications to use network communications?

The operating system provides the socket API to enable applications to use network communications by the API letting connect to remote hosts, send/receive data, and help manage network communication. 